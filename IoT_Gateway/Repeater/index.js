var MongoClient = require('mongodb').MongoClient
, test = require('assert');


// Connection url
var url = 'mongodb://localhost:27017/test';
// Connect using MongoClient
MongoClient.connect(url, function(err, db) {
  // Get an additional db
	console.log("Into the connect");
	db.close();
});


