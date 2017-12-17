using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ChatClient
{
    public class User
    {
        private string nickname;
        private string password;
        private string token;

        private List<Message> messages = new List<Message>();
        private List<User> friends = new List<User>();

        public User() { }

        public User(string nickname, string password)
        {
            this.nickname = nickname;
            this.password = password;
            this.token = Utill.getHesh(nickname, password);
        }

        public string getNickname()
        {
            return this.nickname;
        }

        public string getPassword()
        {
            return this.password;
        }

        public string getToken()
        {
            return this.token;
        }

        public List<Message> getMessages()
        {
            return this.messages;
        }

        public List<User> getFriends()
        {
            return this.friends;
        }

        public void setToken(string token)
        {
            this.token = token;
        }

        public void setNickname(string nickname)
        {
            this.nickname = nickname;
        }

        public void setPassword(string password)
        {
            this.password = password;
        }

        public bool isFriend(User user)
        {
            return friends.Contains(user);
        }

        public void addMessage(Message message)
        {
            foreach (Message itr in messages)
            {
                if (itr.getText() == message.getText())
                {
                    return;
                }
            }

            messages.Add(message);
        }

        public void addFriend(User user)
        {
            if (!isFriend(user) && user != null)
            {
                friends.Add(user);
            }
        }

        public void removeFriend(User user)
        {
            if (!isFriend(user) && user != null)
            {
                friends.Remove(user);
            }
        }
    }
}
