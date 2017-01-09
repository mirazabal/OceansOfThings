#include "CallbackAsyncSerial.h"

using namespace boost::asio;
using namespace serial;

CallbackAsyncSerial::CallbackAsyncSerial(): AsyncSerial()
{

}

CallbackAsyncSerial::~CallbackAsyncSerial()
{

}


CallbackAsyncSerial::CallbackAsyncSerial(std::string const& devname,
        size_t baud_rate,
        serial_port_base::parity opt_parity,
        serial_port_base::character_size opt_csize,
        serial_port_base::flow_control opt_flow,
        serial_port_base::stop_bits opt_stop)
        :AsyncSerial(devname,baud_rate,opt_parity,opt_csize,opt_flow,opt_stop)
{

}

void CallbackAsyncSerial::setCallback(std::function<void (const char*, size_t)> const& callback)
{
    setReadCallback(callback);
}

