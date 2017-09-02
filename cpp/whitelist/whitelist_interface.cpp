#include "whitelist_interface.h"
#inlcude "whitelist.h"

int initWhiteListEx(void **handle,const char *addr, unsigned int port, const char *db, const char *user, const char *passwd)
{
	int ret = 0;
	WhiteListManger *wlm = NULL;
	do
	{
		if (!handle)
		{
			break;
		}

		if (!addr || !db || !user || !passwd)
		{
			break;
		}

		WhiteListManger *wlm = new WhiteListManger();
		if (!wlm)
		{
			break;
		}

		if (wlm->init(addr, port, db, user, passwd))
		{
			break;
		}
		try
		{
			if (wlm->loadRules())
			{
				*handle = (void *)wlm;
				ret = 1;
			}
		}
		catch (...)
		{
			std::cout << "error in " << __FUNCTION__ << endl;
		}

	} while (0);

	if (!ret && wlm)
	{//初始化失败
		delete wlm;
		wlm = NULL;
	}

	return ret;
}

int isInWhiteListEml(void *handle, const char *src,const char *dst)
{
	int ret = 0;
	WhiteListManger *wlm = NULL;
	do 
	{
		if (!handle || !src || !dst)
		{
			break;
		}

		wlm = static_cast<WhiteListManger *> (handle);

		if (!wlm)
		{
			break;
		}

		try
		{
			ret = wlm->isInWhiteListEml(src, dst) ? 1 : 0;
		}
		catch (...)
		{
			std::cout << "error in " << __FUNCTION__ << endl;
			ret = 0;
		}

	} while (0);

	return ret;
}

int isInWhiteListIp(void *handle, const char *src, const char *dst)
{
	int ret = 0;
	WhiteListManger *wlm = NULL;
	do
	{
		if (!handle || !src || !dst)
		{
			break;
		}

		wlm = static_cast<WhiteListManger *> (handle);

		if (!wlm)
		{
			break;
		}

		try
		{
			ret = wlm->isInWhiteListIp(src, dst) ? 1 : 0;
		}
		catch (...)
		{
			std::cout << "error in " << __FUNCTION__ << endl;
			ret = 0;
		}
	} while (0);

	return ret;
}

int isInWhiteListEmlPS(void *handle, const char *src)
{
	int ret = 0;
	WhiteListManger *wlm = NULL;
	do
	{
		if (!handle || !src)
		{
			break;
		}

		wlm = static_cast<WhiteListManger *> (handle);

		if (!wlm)
		{
			break;
		}

		try
		{
			ret = wlm->isInWhiteListEmlPS(src) ? 1 : 0;
		}
		catch (...)
		{
			std::cout << "error in " << __FUNCTION__ << endl;
			ret = 0;
		}
	} while (0);

	return ret;
}

int isInWhiteListEmlPD(void *handle, const char *dst)
{
	int ret = 0;
	WhiteListManger *wlm = NULL;
	do
	{
		if (!handle || !dst)
		{
			break;
		}

		wlm = static_cast<WhiteListManger *> (handle);

		if (!wlm)
		{
			break;
		}

		try
		{
			ret = wlm->isInWhiteListEmlPD(dst) ? 1 : 0;
		}
		catch (...)
		{
			std::cout << "error in " << __FUNCTION__ << endl;
			ret = 0;
		}
	} while (0);

	return ret;
}

int isInWhiteListIpPS(void *handle, const char *src)
{
	int ret = 0;
	WhiteListManger *wlm = NULL;
	do
	{
		if (!handle || !src)
		{
			break;
		}

		wlm = static_cast<WhiteListManger *> (handle);

		if (!wlm)
		{
			break;
		}

		try
		{
			ret = wlm->isInWhiteListIpPS(src) ? 1 : 0;
		}
		catch (...)
		{
			std::cout << "error in " << __FUNCTION__ << endl;
			ret = 0;
		}
	} while (0);

	return ret;
}

int isInWhiteListIpPD(void *handle, const char *dst)
{
	int ret = 0;
	WhiteListManger *wlm = NULL;
	do
	{
		if (!handle || !dst)
		{
			break;
		}

		wlm = static_cast<WhiteListManger *> (handle);

		if (!wlm)
		{
			break;
		}

		try
		{
			ret = wlm->isInWhiteListIpPD(dst) ? 1 : 0;
		}
		catch (...)
		{
			std::cout << "error in " << __FUNCTION__ << endl;
			ret = 0;
		}
	} while (0);

	return ret;
}

int isInWhiteListUrlP(void *handle, const char *src)
{
	int ret = 0;
	WhiteListManger *wlm = NULL;
	do
	{
		if (!handle || !src)
		{
			break;
		}

		wlm = static_cast<WhiteListManger *> (handle);

		if (!wlm)
		{
			break;
		}

		try
		{
			ret = wlm->isInWhiteListUrlP(src) ? 1 : 0;
		}
		catch (...)
		{
			std::cout << "error in " << __FUNCTION__ << endl;
			ret = 0;
		}
	} while (0);

	return ret;
}


int updateWhiteList(void *handle) 
{
	int ret = 0;
	WhiteListManger *wlm = NULL;
	do
	{
		if (!handle)
		{
			break;
		}

		wlm = static_cast<WhiteListManger *> (handle);

		if (!wlm)
		{
			break;
		}

		try 
		{
			ret = wlm->loadRules() ? 0 : 1;
		}
		catch (...) 
		{
			std::cout << "error in " << __FUNCTION__ << endl;
			ret = 0;
		}
		
	} while (0);

	return ret;
}

void releaseWhiteList(void *handle)
{
	if (handle)
	{
		WhiteListManger *wlm = static_cast<WhiteListManger *> (handle);
		delete wlm;
	}
	handle = NULL;
}
