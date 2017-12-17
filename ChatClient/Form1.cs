using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Threading;

namespace ChatClient
{
    public partial class Form1 : Form
    {
        public Connector con;
        public Form3 form3;
        public Form4 form4;
        public Form5 form5;

        public Form1()
        {
            InitializeComponent();

            con = Program.connector;
            con.getConnect();
            con.sender(Utill.JON + Mapper.toString(Program.user));
            con.thread = new Thread(delegate() { startReceive(); });
            con.thread.Start();

            button1.Focus();
            button2.Enabled = false;

            label1.Text = Program.user.getNickname();
            label4.ForeColor = Color.Green;
            label4.Text = "IP-" + con.ip.ToString() + " PORT-" + con.port;
        }

        public void startReceive()
        {
            while (true)
            {
                try
                {
                    string message  = con.receiver();
                    string type = message.Substring(0, 3);
                    message = message.Substring(3);

                    this.Invoke((MethodInvoker)delegate()
                    {
                        if (type == Utill.SND)
                        {
                            richTextBox1.AppendText(message + "\n");
                            richTextBox1.SelectionStart = richTextBox1.Text.Length;
                            richTextBox1.ScrollToCaret();
                        }
                        else if (type == Utill.JON)
                        {
                            User newUser = Mapper.toUser(message);
                            Program.users.Add(newUser);
                            comboBox1.Items.Add(newUser.getNickname());
                            richTextBox1.AppendText(newUser.getNickname() + " - Join!" + "\n");
                        }
                        else if (type == Utill.GET)
                        {
                            string token = message.Substring(0, 8);
                            message = message.Substring(8);

                            string[] messages = message.Split('|');
                            User recv = Utill.findUserByToken(token);
                            
                            for (int i = 1; i < messages.Length; i++)
                            {
                                recv.addMessage(new Message(messages[i], token));
                            }

                            if (form3 != null)
                                form3.loadMessages(recv.getMessages());
                        }
                    });
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex);
                    showError();
                    return;
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (richTextBox2.Text != "")
            {
                richTextBox2.Text = richTextBox2.Text.Trim();
                string message = Program.user.getNickname() + ": " + richTextBox2.Text + Utill.END;
                con.sender(Utill.SND + message);
                richTextBox2.Clear();
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string name = comboBox1.SelectedItem.ToString();

            if (name != null && name != "")
            {
                User user = Utill.findUserByName(name);
                form3 = new Form3(user);
                form3.Show();
            }
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            form3 = new Form3(Program.user);
            form3.Show();
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            button2.Enabled = true;
        }

        private void авторToolStripMenuItem_Click(object sender, EventArgs e)
        {
            form5 = new Form5();
            form5.Show();
        }

        private void выходToolStripMenuItem_Click(object sender, EventArgs e)
        {
            con.sender(Utill.EXT + Mapper.toString(Program.user));
            
            if (con.thread != null)
                con.thread.Abort();

            Application.Exit();
        }

        private void настройкиToolStripMenuItem_Click(object sender, EventArgs e)
        {
            form4 = new Form4();
            form4.Show();
        }

        private void showError()
        {
            label4.ForeColor = Color.Red;
            label4.Text = "DISCONNECT";
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            выходToolStripMenuItem_Click(sender, e);
        }
    }
}
