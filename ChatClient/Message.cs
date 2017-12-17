using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ChatClient
{
    public class Message
    {
        public static int COUNT = 0;
        private int id;
        private string text;
        private DateTime date;
        private string sender;

        public Message() { }

        public Message(string text, string sender)
        {
            COUNT++;
            this.id = COUNT;
            this.text = text;
            this.sender = sender;
            this.date = DateTime.Now;
        }

        public int getId()
        {
            return this.id;
        }

        public string getText()
        {
            return this.text;
        }

        public string getSender()
        {
            return this.sender;
        }

        public DateTime getDate()
        {
            return this.date;
        }

        public void setId(int id)
        {
            this.id = id;
        }

        public void setText(string text)
        {
            this.text = text;
        }

        public void setDate(DateTime date)
        {
            this.date = date;
        }

        public void setSender(string sender)
        {
            this.sender = sender;
        }
    }
}
