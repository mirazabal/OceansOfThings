var  mqtt = require ('mqtt');
var client  = mqtt.connect('mqtt://localhost');

client.on('connect', function () {
  client.publish('presence', 'Hello!', {retain: false, qa: 1});
client.end();
});

