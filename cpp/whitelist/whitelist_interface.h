#ifndef WHITELIST_H
#define WHITELIST_H

#ifdef __cplusplus
extern "C" {
#endif

//初始化句柄
int initWhiteListEx(void **handle, const char *addr, unsigned int port, const char *db, const char *user, const char *passwd);
//成功返回1，失败返回0
int isInWhiteListEml(void *handle, const char *src, const char *dst);
int isInWhiteListIp(void *handle, const char *src, const char *dst);
int isInWhiteListEmlPS(void *handle, const char *src);
int isInWhiteListEmlPD(void *handle, const char *dst);
int isInWhiteListIpPS(void *handle, const char *src);
int isInWhiteListIpPD(void *handle, const char *dst);
int isInWhiteListUrlP(void *handle, const char *src);
int updateWhiteList(void *handle);

//释放句柄
void releaseWhiteList(void *handle);

#ifdef __cplusplus
}
#endif // _cplusplus

#endif // WHITELIST_H
