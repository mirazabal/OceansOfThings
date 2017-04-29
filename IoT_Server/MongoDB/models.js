ar mongoose = require('mongoose');
var _ = require('underscore');

module.exports = function(wagner){
	mongoose.connect('mongodb://localhost:27017/test');

	wagner.factory('db', function(){
		return mongoose;
	});

	var NMEA_0183 = mongoose.model('NMEA_0183', require('./NMEA_0183.js'), 'NMEA_0183_Arr');


	var models = {
		NMEA_0183 : NMEA_0183
	};


	// ensure DRY-ness
	_.each(models, function(value,key){
		wagner.factory(key, function(){
			return value;
		});
	});

};







