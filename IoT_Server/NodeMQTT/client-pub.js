var  mqtt = require ('mqtt');
var client  = mqtt.connect('tcp://10.0.0.4:1883');
 
client.on('connect', function () {
  client.publish('presence', 'Hello!', {retain: false, qa: 1});
client.end();
});

