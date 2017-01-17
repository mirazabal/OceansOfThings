

const TeleBot = require('telebot');
const bot = new TeleBot('');



bot.on('text', msg => {
  let fromId = msg.from.id;
  let firstName = msg.from.first_name;
  let reply = msg.message_id;
  return bot.sendMessage(fromId, 'Welcome, ${firstName} cabron!!!!', { reply });
});
 
bot.connect();


