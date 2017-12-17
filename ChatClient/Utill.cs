using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.RegularExpressions;
using System.Drawing;
using System.Drawing.Text;

namespace ChatClient
{
    public class Utill
    {
        public static string LOG = "LOG";
        public static string CON = "CON";
        public static string DIS = "DIS";
        public static string PST = "PST";
        public static string NEW = "NEW";
        public static string SND = "SND";
        public static string GET = "GET";
        public static string SET = "SET";
        public static string JON = "JON";
        public static string EXT = "EXT";
        public static string END = ";;;";

        public static string getHesh(string log, string pas)
        {
            string res = "";

            string hash = log.GetHashCode().ToString();

            for (int i = 0; i < 4; i++)
            {
                res += hash[i];
                if (i % 2 == 0)
                    if (i < pas.Length)
                        res += pas[i];
                    else
                        res += "@";
                else
                    if (i < log.Length)
                        res += log[i];
                    else
                        res += "@";
            }
 
            return res;
        }

        public static bool validateAddress(string ip, string port)
        {
            if (ip == "" || port == "")
                return false;
            if (!Regex.IsMatch(ip, @"\W+"))
                return false;
            if (!Regex.IsMatch(port, @"\d+"))
                return false;

            return true;
        }

        public static bool validateLogin(string log, string pas)
        {
            if (log.Length < 3 || log.Length > 9)
                return false;
            if (pas.Length < 4 || pas.Length > 9)
                return false;
            if (pas == null || log == null)
                return false;
            if (!Regex.IsMatch(log, @"[\w\d]+"))
                return false;
            if (!Regex.IsMatch(pas, @"[\w\d]+"))
                return false;

            return true;
        }

        public static User findUserByName(string name)
        {
            foreach (User user in Program.users)
            {
                if (user.getNickname().Equals(name))
                {
                    return user;
                }
            }

            return null;
        }

        public static User findUserByToken(string token)
        {
            foreach (User user in Program.users)
            {
                if (user.getToken().Equals(token))
                {
                    return user;
                }
            }

            return null;
        }
    }
}
