/**
 *  This test suite is meant to be run through gulp (use the `npm run watch`)
 *  script. It will provide you useful feedback while filling out the API in
 *  `index.js`
 * */

var assert = require('assert');
var wagner = require('wagner-core');
var sleep = require('sleep'); 

describe('MQTT and REST calls server', function() {
	
	var MQTT_server;
	var MQTT_client;
	var REST_server;

	before(function() {
		//  Bootstrap server
		models = require('./models')(wagner);
		//  dependencies = require('./dependencies')(wagner);

		// Make models available in tests
		var deps = wagner.invoke(function(MQTT_server ){
			return {
				MQTT_server : MQTT_server,
				MQTT_client : MQTT_client
			};
		});

		MQTT_server = deps.MQTT_server;
		MQTT_client = deps.MQTT_client;	
	});

	beforeEach(function(done) {

		isRunning('redis-server', function(retVal){
			if( retVal == false ){
				console.log('redis-server not running');
				var spawn = require('child_process').spawn;
				function shspawn(command) {
					spawn('sh', ['-c', command], { stdio: 'inherit' });
				} 
				//shspawn('ls -l | grep test | wc -c');
				shspawn('redis-server &');
			}
			done();
		});
	});
	
	function isRunning(process,cb) {
		var checkCommand = 'ps -A | grep ' + process;
		var execOptions = {};

		const exec = require('child_process').exec;		
		exec(checkCommand, execOptions, function( err, stdout ) {
			
			if ( err ) {
				cb(false);
				return;
			}
			if ( stdout ) {
				cb(true);
				return;
				//cb(true, stdout);
			}
			cb(false);
		});
	}


describe('Gateway ', function() {


	it('does accept mqtt client connection', function(done) {
/*
		var client  = mqtt.connect('mqtt://localhost');

		client.on('connect', function (done) {
			console.log('connected');
			client.end();
			done();
		});
*/
		sleep.sleep(10);
	//	assert.equal(1,2);
		done();
	});
/*
	it('has data', function() {

	});

	it('has timestamp', function() {

	});
*/
});
});


/*


describe('Gateway', function() {
	
	var MQTT_Server;
	var REST_Server;

	before(function() {
		console.log("qwer");	
		process.stdout.write("hello: "); 
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

	describe('GPS data', function() {
		it('has a type', function() {
			NMEA_0183.findOne({}, function(error, NMEA){
				assert.ifError(error);
				assert.equal(NMEA.type, 'GPGLL');
			}); 
		});
		it('has data', function() {
			NMEA_0183.findOne({type:"GPGGA"}, function(error, NMEA){
				assert.ifError(error);
				assert.equal(NMEA.data, '456asdasd');
			});
		});
		it('has timestamp', function() {
			NMEA_0183.findOne({type:"GPGLL"}, function(error,NMEA ){

				assert( NMEA.timestamp_ms + 2000 > new Date().getTime() , 'timestamp took more than 2000 ms... something wrong = ' + gps.timestamp_ms + "  " + new Date().getTime() );
			});

			});

	});
});

	
});
*/
