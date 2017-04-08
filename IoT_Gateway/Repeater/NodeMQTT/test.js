/**
 *  This test suite is meant to be run through gulp (use the `npm run watch`)
 *  script. It will provide you useful feedback while filling out the API in
 *  `index.js`
 * */

var assert = require('assert');
var wagner = require('wagner-core');

describe('Gateway', function() {

	var MQTT_Server;
	var REST_Server;


	before(function() {

		//  Bootstrap server
		models = require('./models')(wagner);
		//  dependencies = require('./dependencies')(wagner);

		// Make models available in tests
		var deps = wagner.invoke(function(NMEA_0183){
			return {
				MQTT_Server : MQTT_Server
			};
		});

		MQTT_Server = deps.MQTT_Server;
		
	});


	beforeEach(function(done) {
		done();
	});
	

	describe('Gateway', function() {

		it('can establish  a connection with clients', function() {
			MQTT_Server.on('clientConnected', function(client) {
				console.log('client connected', client.id);     
			});

			}); 
		});

		it('can receive messages from clients', function() {
			NMEA_0183.findOne({type:"GPGGA"}, function(error, NMEA){
				assert.ifError(error);
				assert.equal(NMEA.data, '456asdasd');
			});
		});

		it('can publish data to connected clients', function() {
			NMEA_0183.findOne({type:"GPGLL"}, function(error,NMEA ){

				assert( NMEA.timestamp_ms + 2000 > new Date().getTime() , 'timestamp took more than 2000 ms... something wrong = ' + gps.timestamp_ms + "  " + new Date().getTime() );
			});

		});

	});
});

