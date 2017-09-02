class string {
private:
       char* buf;
public:
       string();
       ~string();
       string(const char *s);
       string(const string & s);
       string& operator =(const string& s);
};
string::string()
{
       buf = new char[1];
       buf[0] = '\0';
}
string::~string() {
       if (buf)
       {
              delete[] buf;
       }
}
string::string(const char *s)
{
       if (NULL == s)
       {
              buf = new char[1];
              buf[0] = '\0';
       }
       else
       {
              buf = new char[strlen(s) + 1];
              buf[strlen(s)] = '\0';
       }
}
string::string(const string &s)
{
       buf = new char[strlen(s.buf) + 1];
       strcpy(buf, s.buf);
}
string& string::operator =(const string&s)
{
       if (&s == this) return *this;
       delete[]buf;
       buf = new char[strlen(s.buf) + 1];
       strcpy(buf, s.buf);
       return *this;
}
