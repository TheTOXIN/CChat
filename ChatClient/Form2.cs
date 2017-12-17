using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ChatClient
{
    public partial class Form2 : Form
    {
        public Connector con;
        public Form1 form;

        public Form2()
        {
            InitializeComponent();
            con = Program.connector;
            TopMost = true;

            string res = con.loadInfo();
            string[] info = res.Split(':');

            if (info.Length == 2)
            {
                textBox4.Text = info[0];
                textBox3.Text = info[1];
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string token = "";
            string pas = textBox2.Text.Trim();
            string log = textBox1.Text.Trim();
            
            if (Utill.validateLogin(log, pas))
            {
                User user = new User(log, pas);
                token = Utill.getHesh(log, pas);
                
                con.setInfo(textBox4.Text, textBox3.Text);
                con.getConnect();

                if (!checkBox1.Checked)
                    con.sender(Utill.LOG + token);
                else
                    con.sender(Utill.NEW + Mapper.toString(user));

                string answer = con.receiver();

                if (answer.Equals(Utill.CON))
                {
                    label1.Text = "CONNECT";
                    label1.ForeColor = Color.Green;
                    Program.user = user;
                    this.Hide();
                    form = new Form1();
                    form.StartPosition = this.StartPosition;
                    form.Show();
                }
                else if (answer.Equals(Utill.DIS))
                {
                    label1.Text = "WRONG";
                    label1.ForeColor = Color.Red;
                }
            }
            else
            {
                label1.Text = "INVALID";
                label1.ForeColor = Color.Yellow;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            textBox4.Text = textBox4.Text.Trim();
            textBox4.Text = textBox4.Text.Trim();

            if (Utill.validateAddress(textBox4.Text, textBox3.Text))
            {
                con.saveInfo(textBox4.Text + ":" + textBox3.Text);
                button3_Click(sender, e);
            }
            else
            {
                textBox4.Text = "WRONG";
                textBox3.Text = "VALUE";
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            groupBox1.Visible = !groupBox1.Visible;
            groupBox2.Visible = !groupBox2.Visible;

            if (groupBox1.Visible)
                button3.Text = "ADDRESS";
            else
                button3.Text = "LOGIN";
        }
    }
}
