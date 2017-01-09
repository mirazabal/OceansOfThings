#include "AsyncSerial.h"

#include <algorithm>
#include <iostream>
#include <mutex>
#include <thread>
#include <string>

#include <boost/bind.hpp>

using namespace std;
using namespace boost;
using namespace boost::asio;
using namespace serial;

namespace serial
{

class AsyncSerialImpl 
{
public:
    AsyncSerialImpl(): io(), port(io),/* backgroundThread(),*/ open(false),error(false) {}

	AsyncSerialImpl(AsyncSerialImpl const&) = delete;
	AsyncSerialImpl& operator=(AsyncSerialImpl const& ) = delete;

    io_service io; ///< Io service object
    serial_port port; ///< Serial port object
	std::unique_ptr<std::thread> backgroundThread; //< Thread that runs read/write operations

	bool open; ///< True if port open
    bool error; ///< Error flag
    mutable std::mutex errorMutex; ///< Mutex for access to error

    /// Data are queued here before they go in writeBuffer
    std::vector<char> writeQueue;
	std::unique_ptr<char> writeBuffer;
	size_t writeBufferSize; ///< Size of writeBuffer
    std::mutex writeQueueMutex; ///< Mutex for access to writeQueue
    char readBuffer[AsyncSerial::readBufferSize]; ///< data being read

    /// Read complete callback
	std::function< void (char const*, size_t) > callback;
};
}


AsyncSerial::AsyncSerial(): pimpl(std::make_unique<AsyncSerialImpl>())
{

}

AsyncSerial::AsyncSerial(const std::string& devname, unsigned int baud_rate,
        serial_port_base::parity opt_parity,
        serial_port_base::character_size opt_csize,
        serial_port_base::flow_control opt_flow,
        serial_port_base::stop_bits opt_stop)
        : pimpl(std::make_unique<AsyncSerialImpl>())
{
    open(devname,baud_rate,opt_parity,opt_csize,opt_flow,opt_stop);
}

void AsyncSerial::open(const std::string& devname, unsigned int baud_rate,
       serial_port_base::parity opt_parity,
       serial_port_base::character_size opt_csize,
       serial_port_base::flow_control opt_flow,
       serial_port_base::stop_bits opt_stop)
{
    if(isOpen()) close();

    setErrorStatus(true);//If an exception is thrown, error_ remains true
    pimpl->port.open(devname);
    pimpl->port.set_option(serial_port_base::baud_rate(baud_rate));
    pimpl->port.set_option(opt_parity);
    pimpl->port.set_option(opt_csize);
    pimpl->port.set_option(opt_flow);
    pimpl->port.set_option(opt_stop);

    //This gives some work to the io_service before it is started
    pimpl->io.post(boost::bind(&AsyncSerial::doRead, this));
	

   pimpl->backgroundThread = std::make_unique<std::thread>( [&](){ pimpl->io.run(); });	

	setErrorStatus(false);//If we get here, no error
    pimpl->open=true; //Port is now open
}

AsyncSerial::~AsyncSerial()
{
    if(isOpen())
    {
        try {
            close();
        } catch(...)
        {
            //Don't throw from a destructor
        }
    }
}

bool AsyncSerial::isOpen() const
{
    return pimpl->open;
}

bool AsyncSerial::errorStatus() const
{
    std::lock_guard<std::mutex> l(pimpl->errorMutex);
    return pimpl->error;
}

void AsyncSerial::close()
{
    if(!isOpen()) return;

    pimpl->open=false;
    pimpl->io.post(boost::bind(&AsyncSerial::doClose, this));
    pimpl->backgroundThread->join(); // .join();
    pimpl->io.reset();
    if(errorStatus())
    {
        throw(boost::system::system_error(boost::system::error_code(),
                "Error while closing the device"));
    }
}

void AsyncSerial::write(const char *data, size_t size)
{
    {
		std::lock_guard<std::mutex> l(pimpl->writeQueueMutex);
        pimpl->writeQueue.insert(pimpl->writeQueue.end(),data,data+size);
    }
    pimpl->io.post(boost::bind(&AsyncSerial::doWrite, this));
}

void AsyncSerial::doRead()
{
    pimpl->port.async_read_some(asio::buffer(pimpl->readBuffer,readBufferSize),
            boost::bind(&AsyncSerial::readEnd,
            this,
            asio::placeholders::error,
            asio::placeholders::bytes_transferred));
}

void AsyncSerial::readEnd(const boost::system::error_code& error, size_t bytes_transferred)
{
    if(error)
    {
        //error can be true even because the serial port was closed.
        //In this case it is not a real error, so ignore
        if(isOpen())
        {
            doClose();
            setErrorStatus(true);
        }
    } else {
        if(pimpl->callback)
		   	pimpl->callback(pimpl->readBuffer, bytes_transferred);
       
	   	doRead();
    }
}

void AsyncSerial::doWrite()
{
    //If a write operation is already in progress, do nothing
    if(pimpl->writeBuffer==0)
    {
		std::lock_guard<std::mutex> l(pimpl->writeQueueMutex);
        pimpl->writeBufferSize=pimpl->writeQueue.size();
        pimpl->writeBuffer.reset( new char[pimpl->writeQueue.size()] );
        copy(pimpl->writeQueue.begin(),pimpl->writeQueue.end(),
                pimpl->writeBuffer.get());
        pimpl->writeQueue.clear();
        async_write(pimpl->port, asio::buffer( pimpl->writeBuffer.get(), pimpl->writeBufferSize) ,
                boost::bind(&AsyncSerial::writeEnd, this, asio::placeholders::error));
    }
}

void AsyncSerial::writeEnd(const boost::system::error_code& error)
{
    if(!error)
    {
		std::lock_guard<std::mutex> l(pimpl->writeQueueMutex);
        if(pimpl->writeQueue.empty())
        {
            pimpl->writeBuffer.reset();
            pimpl->writeBufferSize=0;
            
            return;
        }
        pimpl->writeBufferSize=pimpl->writeQueue.size();
        pimpl->writeBuffer.reset(new char[pimpl->writeQueue.size()]);
        copy(pimpl->writeQueue.begin(),pimpl->writeQueue.end(),
                pimpl->writeBuffer.get());
        pimpl->writeQueue.clear();
        async_write(pimpl->port,asio::buffer(pimpl->writeBuffer.get(),
                pimpl->writeBufferSize),
                boost::bind(&AsyncSerial::writeEnd, this, asio::placeholders::error));
    } else {
        setErrorStatus(true);
        doClose();
    }
}

void AsyncSerial::doClose()
{
    boost::system::error_code ec;
    pimpl->port.cancel(ec);
    if(ec) setErrorStatus(true);
    pimpl->port.close(ec);
    if(ec) setErrorStatus(true);
}

void AsyncSerial::setErrorStatus(bool e)
{
	std::lock_guard<std::mutex> l(pimpl->errorMutex);
    pimpl->error=e;
}

void AsyncSerial::setReadCallback(std::function<void (const char*, size_t)> const& callback)
{
    pimpl->callback = callback;
}

