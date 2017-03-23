//console.log(process.pid);
//
////require('daemon')();


var mosca = require('mosca')
var https = require('http');


var backjack = {
  type: 'redis',
  db: 12,
  port: 6379,
  return_buffers: true,
  host: "localhost"
};
 
var moscaSettings = {
  port: 1883,
  backend: backjack,
  persistence: {
    factory: mosca.persistence.Redis
  }
};
 
var server = new mosca.Server(moscaSettings);
server.on('ready', setup);
 
server.on('clientConnected', function(client) {
    console.log('client connected', client.id);     
});
 
server.on('published', function(packet, client) {
 
	var path_ = "/restdevices.svc/comebacktest/"; 
	if(packet.payload.toString('utf-8').indexOf("/n") == -1 )
		path_ += packet.payload.toString('utf-8'); 
	
	var optionsget = {
    host : '52.178.32.138', // here only the domain name
    // (no http/https !)
    port : 80,
    path :  path_, // the rest of the url with parameters if needed
    method : 'GET' // do GET
};
 
console.info('Options prepared:');
console.info(optionsget);
console.info('Do the GET call');
 
// do the GET request
var reqGet = https.request(optionsget, function(res) {
    console.log("statusCode: ", res.statusCode);
    // uncomment it for header details
//  console.log("headers: ", res.headers);
 
 
    res.on('data', function(d) {
        console.info('GET result:\n');
        process.stdout.write(d);
        console.info('\n\nCall completed');
    });
 
});
    
	console.log('Published ', packet.topic, packet.payload.toString('utf-8') );
  
});
 
function setup() {
  console.log('Mosca server is up and running')
}
console.log(process.pid);
