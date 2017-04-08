// ToDo implement the REST server

var _ = require('underscore');
var mosca = require('mosca')

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
 
var MQTT_Server = new mosca.Server(moscaSettings);

module.exports = function(wagner){

	MQTT_Server.on('ready', setup);

	wagner.factory('MQTT_Server', function(){
		return MQTT_Server;
	});


	// ensure DRY-ness
	_.each(models, function(value,key){
		wagner.factory(key, function(){
			return value;
		});
	});

};

