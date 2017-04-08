//console.log(process.pid);
//
////require('daemon')();


//var mosca = require('mosca')
var https = require('http');

/*
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
*/

/*
 
server.on('published', function(packet, client) {
 
	console.log('Published ', packet.topic, packet.payload.toString('utf-8') );
 

// options for GET
var optionsget = {
    host : '52.178.32.138', // here only the domain name
    // (no http/https !)
    port : 80,
    path : '/restdevices.svc/comebacktest/Antifa', // the rest of the url with parameters if needed
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
 
reqGet.end();
reqGet.on('error', function(e) {
    console.error(e);
});

*/


/* HOW TO Make an HTTP Call - POST
 */
// do a POST request
// create the JSON object
jsonObject = JSON.stringify({

"dataValue1":1,
"dataValue2":2,
"dataValue3":3,
"dataValue4":4,
"dataValue5":5,
"longValues":"<1<2<3",
"recordId":"Date(1490443328240)",
"sensorName":"Josep"

});
 
// prepare the header
var postheaders = {
    'Content-Type' : 'application/json',
    'Content-Length' : Buffer.byteLength(jsonObject, 'utf8')
};

// the post options
var optionspost = {
    host : '52.178.32.138',
    port : 80,
    path : '/restdevices.svc/UpdateSensorData/',
    method : 'POST',
    headers : postheaders
};
 
console.info('Options prepared:');
console.info(optionspost);
console.info('Do the POST call');
 
// do the POST call
var reqPost = https.request(optionspost, function(res) {
    console.log("statusCode: ", res.statusCode);
    // uncomment it for header details
  console.log("headers: ", res.headers);
 
    res.on('data', function(d) {
        console.info('POST result:\n');
        process.stdout.write(d);
        console.info('\n\nPOST completed');
    });
});
 
// write the json data
reqPost.write(jsonObject);
reqPost.end();
reqPost.on('error', function(e) {
    console.error(e);
});
 

//});


//function setup() {
//  console.log('Mosca server is up and running')
//}

console.log(process.pid);

