using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ChatClient
{
    public class Mapper
    {
        public static string toString(User user)
        {
            return new StringBuilder()
                .Append(user.getToken())
                .Append("|")
                .Append(user.getNickname())
                .Append("|")
                .Append(user.getPassword())
                .ToString();
        }

        public static string toString(Message message)
        {
            return new StringBuilder()
                .Append(message.getSender())
                .Append("|")
                .Append(message.getText())
                .Append("|")
                .Append(message.getDate().ToString())
                .ToString();
        }

        public static User toUser(string str)
        {
            User user = new User();
           
            string[] parse = str.Split('|');
           
            user.setToken(parse[0]);
            user.setNickname(parse[1]);
            user.setPassword(parse[2]);

            return user;
        }

        public static Message toMessage(string str)
        {
            Message message = new Message();

            string[] parse = str.Split('|');
            message.setSender(parse[0]);
            message.setText(parse[2]);
            message.setDate(Convert.ToDateTime(parse[3]));

            return message;
        }
    }
}
