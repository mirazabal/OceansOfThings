/**
 *  This test suite is meant to be run through gulp (use the `npm run watch`)
 *  script. It will provide you useful feedback while filling out the API in
 *  `index.js`
 * */

var assert = require('assert');
var wagner = require('wagner-core');


describe('Mongoose Schemas', function() {

	var NMEA_0183;

	before(function() {

		//  Bootstrap server
		models = require('./models')(wagner);
		//  dependencies = require('./dependencies')(wagner);

		// Make models available in tests
		var deps = wagner.invoke(function(NMEA_0183){
			return {
				NMEA_0183: NMEA_0183
			};
		});

		NMEA_0183 = deps.NMEA_0183;

		NMEA_0183.findOne({}, function(error, user) {
			assert.ifError(error);
		});
	});


	beforeEach(function(done) {
		NMEA_0183.remove({}, function(error){
				assert.ifError(error);
				done();
				});
	});
	

	beforeEach(function(done) {
		var NMEA_0183_Arr = [
		{ 'nodeID': "Node_1", 'type' : 'GPGLL', 'data': 'asdasd'},
		{ 'nodeID': 'Node_1' ,  'type' : 'GPGGA', 'data': '456asdasd'},
		{ 'nodeID': 'Node_1' , 'type' : 'GPRMC', 'data': 'La carta dice el motivo que Roberto'}
		];

		NMEA_0183.create(NMEA_0183_Arr, function(error){
			assert.ifError(error);
			done();
		});
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

