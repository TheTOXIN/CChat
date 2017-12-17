using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Threading;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ChatClient
{
    public partial class Form3 : Form
    {
        public Connector con;
        public User user;
      
        public Form3(User user)
        {
            InitializeComponent();
            this.user = user;

            textBox1.Focus();
            button1.Enabled = false;
            label1.Text = user.getNickname();
            
            con = Program.connector;
            con.sender(Utill.GET + user.getToken());
        }

        public void loadMessages(List<Message> messages)
        {
            label2.Text = "STAND: " + messages.Count; 
            richTextBox1.Clear();

            foreach (Message mes in messages)
            {
                richTextBox1.AppendText(mes.getText() + "\n");
            }

            richTextBox1.SelectionStart = richTextBox1.Text.Length;
            richTextBox1.ScrollToCaret();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            button1.Enabled = !button1.Enabled;

            if (button1.Enabled)
            {
                Program.user.addFriend(user);
                button2.Text = "UNSCRIBE";
                button2.ForeColor = Color.Red;
            }
            else
            {
                Program.user.removeFriend(user);
                button2.Text = "SUBSCRIBE";
                button2.ForeColor = Color.Chartreuse;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text != "")
            {
                textBox1.Text = textBox1.Text.Trim();
                con.sender(Utill.SET + user.getToken() + textBox1.Text);
                con.sender(Utill.GET + user.getToken());
                textBox1.Clear();
            }
        }
    }
}
