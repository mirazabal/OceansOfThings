var mongoose = require('mongoose');

var NMEA_0183Schema = new mongoose.Schema({
	nodeID: { type: String, required: 'true'},
	type: { type: String, required: true },
	data: { type: String, required: 'true'},
	timestamp: {type: Date, default: Date.now}
});

// instructions for virtual functions
/* Returns the timestamp in ms, even though the timestamp is not in ms saved in the database
 * */
	NMEA_0183Schema.virtual('timestamp_ms').get(function() {
	return this.timestamp.getTime();
});

module.exports = NMEA_0183Schema;
