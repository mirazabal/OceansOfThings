// ToDo implement the REST server

var _ = require('underscore');
var mosca = require('mosca')
var  mqtt = require ('mqtt');

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
 


module.exports = function(wagner){

	var MQTT_server = new mosca.Server(moscaSettings);
	MQTT_server.on('ready', setup);


	MQTT_server.on('clientConnected', function(client) {
		console.log('client connected', client.id);  
	});

	MQTT_server.on('published', function(packet, client) {
		console.log('Published ', packet.topic, packet.payload.toString('utf-8') );
	});

	function setup() {
		console.log('Mosca server is up and running')
	}

	wagner.factory('MQTT_server', function(){
		return MQTT_server;
	});


	var MQTT_client = mqtt.connect('mqtt://localhost');
	MQTT_client.on('connect', function (done) {
			console.log('connected');
		});

	var models = {
		MQTT_server : MQTT_server,
		MQTT_client : MQTT_client
	};

	// ensure DRY-ness
	_.each(models, function(value,key){
		wagner.factory(key, function(){
			return value;
		});
	});

};

