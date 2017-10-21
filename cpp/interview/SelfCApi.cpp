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

void memcpy(void *dst, void *src, size_t len)
{
       assert(!dst || !src || len < 0);
       int pos = 0;
       unsigned char *pdst = (unsigned char*)dst, *psrc = (unsigned char*)src;
       if(src < dst)
       {
              pos = len - 1;
              while(pos > 0)
              {
                     pdst[pos] = psrc[pos];
                     pos--;
              }
       }
       else
       {
              while (pos < len)
              {
                     pdst[pos] = psrc[pos];
                     pos++;
              }
       }
}
