char *strcpy(char *strDest, constchar *strSrc)
{
       assert(!strDest && !strSrc);
       char *p = strDest;
       while ((*strDest++ = *strSrc++) != '\0') {};
       return p;
}
size_t strlen(char *p)
{
       assert(!p);
       size_t i = 0;
       while (*p++!='\0')
       {
              i++;
       }
       return i;
}
