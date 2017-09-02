#include <sstream>
#include<iostream>
#include<string.h>
#include <vector>
#include <stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PCRE2_CODE_UNIT_WIDTH 8

#include "pcre2.h"
#include "mysql++/mysql++.h"

#include "whitelist.h"

using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define VERSION_SIZE 64         /* Size of buffer for the version strings */
#define VERSION_TYPE PCRE2_UCHAR8
#define PCRE2_CONFIG pcre2_config_8
#define PCRE2_JIT_STACK pcre2_jit_stack_8
#define PCRE2_REAL_GENERAL_CONTEXT pcre2_real_general_context_8
#define PCRE2_REAL_COMPILE_CONTEXT pcre2_real_compile_context_8
#define PCRE2_REAL_MATCH_CONTEXT pcre2_real_match_context_8
#define VERSION_TYPE PCRE2_UCHAR8

static VERSION_TYPE jittarget[VERSION_SIZE];
static VERSION_TYPE version[VERSION_SIZE];
static VERSION_TYPE uversion[VERSION_SIZE];

void RegexMatcherPcre2::config()
{

	if (PCRE2_CONFIG(PCRE2_CONFIG_VERSION, NULL) !=
		PCRE2_CONFIG(PCRE2_CONFIG_VERSION, version) ||

		PCRE2_CONFIG(PCRE2_CONFIG_UNICODE_VERSION, NULL) !=
		PCRE2_CONFIG(PCRE2_CONFIG_UNICODE_VERSION, uversion) ||

		PCRE2_CONFIG(PCRE2_CONFIG_JITTARGET, NULL) !=
		PCRE2_CONFIG(PCRE2_CONFIG_JITTARGET, jittarget) ||

		PCRE2_CONFIG(PCRE2_CONFIG_UNICODE, NULL) != sizeof(uint32_t) ||
		PCRE2_CONFIG(PCRE2_CONFIG_MATCHLIMIT, NULL) != sizeof(uint32_t)) {
		throw("Error in pcre2_config(): bad length");
	}
}

RegexMatcherPcre2::RegexMatcherPcre2()
{
	_optionsCompile = PCRE2_NO_UTF_CHECK;
	_optionsMatch = PCRE2_NOTEMPTY | PCRE2_NOTEMPTY_ATSTART | PCRE2_NO_UTF_CHECK;
}

RegexMatcherPcre2::~RegexMatcherPcre2(void)
{
	//pcre2_code_free(re);
	//pcre2_match_data_free(match_data);
	//pcre2_match_context_free(mcontext);
	//pcre2_jit_stack_free(jit_stack);
}

bool RegexMatcherPcre2::setRegexExpression(const std::string& regexExpression)
{
	bool ret = false;
	int errornumber;
	PCRE2_SIZE erroroffset;

	std::stringstream strmerr;
	std::string strerr;
	do
	{
		if (regexExpression.empty())
		{
			break;
		}

		auto re = pcre2_compile(
			(PCRE2_SPTR)regexExpression.c_str(),               /* the pattern */
			PCRE2_ZERO_TERMINATED, /* indicates pattern is zero-terminated */
			_optionsCompile,                     /* default options */
			&errornumber,          /* for error number */
			&erroroffset,          /* for error offset */
			NULL);                 /* use default compile context */

		if (re == NULL)
		{
			PCRE2_UCHAR buffer[256];
			pcre2_get_error_message(errornumber, buffer, sizeof(buffer));

			cout << "PCRE2 compilation failed at offset: " << erroroffset << " for " << buffer << endl;
			break;
		}

		CodePointer code(re, &::pcre2_code_free);

		auto rc = pcre2_jit_compile(re, PCRE2_JIT_COMPLETE);
		if (rc != 0)
		{
			PCRE2_UCHAR buffer[256];
			pcre2_get_error_message(rc, buffer, sizeof(buffer));

			cout << "PCRE2 pcre2_jit_compile failed, error: " << rc << " for " << buffer << endl;
			break;
		}

		_md._pattern = regexExpression;
		_md._code = code;
		ret = true;
	} while (0);

	return ret;
}

bool RegexMatcherPcre2::IsExistMatchedItem(const char* data, uint64_t length, uint64_t fileOffset) const
{
	bool ret = false;

	auto mcontext = pcre2_match_context_create(NULL);
	MatchContextPointer mcp(mcontext, &::pcre2_match_context_free);

	auto jit_stack = pcre2_jit_stack_create(16 * 1024 * 1024, 16 * 1024 * 1024, NULL);
	JITStackPointer jsp(jit_stack, &::pcre2_jit_stack_free);
	pcre2_jit_stack_assign(mcontext, NULL, jit_stack);

	//std::stringstream strmerr;
	//std::string strerr;

	const pcre2_code *code = _md._code.get();
	pcre2_match_data *match_data = pcre2_match_data_create_from_pattern(code, nullptr);
	MatchDataPointer matchData(match_data, &::pcre2_match_data_free);

	PCRE2_SPTR subjects = (PCRE2_SPTR)data;
	PCRE2_SIZE start_offset = 0;
	PCRE2_SIZE *ovector = nullptr;
	int rc;
	do
	{
		rc = pcre2_jit_match(
			code,                   /* the compiled pattern */
			subjects,              /* the subject string */
			length,       /* the length of the subject */
			start_offset,         /* starting offset in the subject */
			_optionsMatch,              /* options */
			match_data,           /* block for storing the result */
			mcontext);                /* use default match context */
		if (rc == PCRE2_ERROR_NOMATCH)
		{
			//cout << "no matching" << endl;
			break;
		}

		if (rc < 0)
		{
			PCRE2_UCHAR buffer[256];
			pcre2_get_error_message(rc, buffer, sizeof(buffer));

			cout << "PCRE2 Matching error: " << rc << " for " << buffer << endl;
			break;
		}

		ovector = pcre2_get_ovector_pointer(match_data);

		if (ovector[0] == ovector[1])
		{
			if (ovector[0] == length)
			{
				//cout << "空匹配";
				break;
			}
		}

		ret = true;
	} while (0);
	return ret;
}



RegexPair::~RegexPair()
{

}

bool RegexPair::IsExistMatchedItem(const std::string &src, const std::string &dst)
{
	return (_regexs.IsExistMatchedItem(src.c_str(), src.length(), 0) && _regexd.IsExistMatchedItem(dst.c_str(), dst.length(), 0));
}

bool RegexPair::setRegexExpression(const std::string &src, const std::string &dst)
{
	return _regexs.setRegexExpression(src) && _regexd.setRegexExpression(dst);
}



bool WhiteListEml::addInWhiteList(const char *src, const char *dst)
{
	if (!src || !dst || !strlen(src) || !strlen(dst))
	{
		return false;
	}
	std::shared_ptr<RegexPair> rules = std::make_shared<RegexPair>();
	if (rules->setRegexExpression(src, dst))
	{
		_rules_eml.push_back(rules);
		return true;
	}
	return false;
}

bool WhiteListEml::isInWhiteList(const std::string &src, const std::string &dst)
{
	bool ret = false;
	for (const auto &rule : _rules_eml)
	{
		if (rule->IsExistMatchedItem(src, dst))
		{
			ret = true;
			break;
		}
	}
	return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Interval::Interval() :_start(0), _end(0)
{

}

Interval::Interval(unsigned int s, unsigned int e) : _start(s), _end(e)
{

}

bool Interval::operator <(const Interval & itv)
{
	return _start < itv._start;
}

Interval::Interval(const Interval & other)
{
	_start = other._start;
	_end = other._end;
}

Interval & Interval::operator=(const Interval & other)
{
	_start = other._start;
	_end = other._end;
}

bool Interval::isInScope(unsigned int i)
{
	if (i >= _start && i <= _end)
	{
		return true;
	}
	return false;
}



bool IntervalList::addInInterval(unsigned int src, unsigned int dst)
{
	Interval item(src, dst);
	_intervals.push_back(item);
	return true;
}

bool IntervalList::isInInterval(unsigned int i)
{
	bool ret = false;

	std::vector<Interval>::iterator it;
	for (it = _intervals.begin(); it != _intervals.end(); it++)
	{
		if (it->isInScope(i))
		{
			ret = true;
			break;
		}
	}

	return ret;
}

void IntervalList::generate()
{
	if (_intervals.size() == 0)
	{
		return;
	}

	vector<std::shared_ptr<Interval>> re;
	std::sort(_intervals.begin(), _intervals.end());

	std::vector<Interval>::iterator i, j;
	j = _intervals.begin();
	size_t k = 0;
	for (i = _intervals.begin(), i++; i != _intervals.end(); i++)
	{
		if (j->_end >= i->_start - 1)
		{
			j->_end = std::max(j->_end, i->_end);
		}
		else
		{
			k++;
			j++;
			*j = *i;
		}
	}

	_intervals.resize(++k);

	cout << "interval:" << endl;
	for (const auto &it : _intervals)
	{
		cout << "[" << it._start << "," << it._end << "]" << "\t";
	}
	cout << endl;

	return;
}


IpPair::IpPair()
{

}

IpPair::~IpPair()
{

}

bool IpPair::addInIpPair(unsigned int src, unsigned int dst, bool bType)
{
	bool ret = false;
	if (bType)
	{
		ret = _src.addInInterval(src, dst);
	}
	else
	{
		ret = _dst.addInInterval(src, dst);
	}

	return ret;
}

bool IpPair::isInIpPair(unsigned int src, unsigned int dst)
{
	if (_src.isInInterval(src) && _dst.isInInterval(dst))
	{
		return true;
	}
	return false;
}

void IpPair::generate()
{
	_src.generate();
	_dst.generate();
}



WhiteListIp::WhiteListIp()
{

}

WhiteListIp::~WhiteListIp()
{
}

bool WhiteListIp::addInWhiteList(const char *ipls, const char *ipsd)
{
	if (!ipls || !ipsd || !strlen(ipls) || !strlen(ipsd))
	{
		return false;
	}

	int ret = false;
	std::shared_ptr<IpPair> ipp = std::make_shared<IpPair>();
	std::vector<std::string> ips = split(std::string(ipls), ",");
	std::vector<std::string> ipd = split(std::string(ipsd), ",");

	do
	{
		if (ips.empty() || ipd.empty())
		{
			break;
		}

		int iret = -1;
		unsigned int src, dst;
		std::vector<std::string>::iterator it;
		int sret = 0, dret = 0;
		it = ips.begin();
		for (; it != ips.end(); it++)
		{
			sret = 0, dret = 0;
			iret = getIpScope(*it, src, dst);
			if (iret)
			{//错误
				continue;
			}
			cout << "++ src ip: " << *it << "==> [" << src << "," << dst << "] ";
			if (!ipp->addInIpPair(src, dst, true))
			{
				cout << "failed" << endl;
				continue;
			}
			cout << "success" << endl;
			sret++;
		}

		it = ipd.begin();
		for (; it != ipd.end(); it++)
		{
			//cout << "dst = " << *it << endl;
			iret = getIpScope(*it, src, dst);
			if (iret)
			{//错误
				continue;
			}
			cout << "++ dst ip: " << *it << "==> [" << src << "," << dst << "] ";
			if (!ipp->addInIpPair(src, dst, false))
			{
				cout << "failed" << endl;
				continue;
			}
			cout << "success" << endl;
			dret++;
		}

		if (sret && dret)
		{
			ipp->generate();
			_rules_ip.push_back(ipp);
			ret = true;
		}
	} while (0);

	return ret;
}

bool WhiteListIp::isInWhiteList(unsigned int src, unsigned int dst)
{
	bool ret = false;
	std::vector<std::shared_ptr<IpPair>>::iterator it = _rules_ip.begin();
	for (; it != _rules_ip.end(); it++)
	{
		if ((*it)->isInIpPair(src, dst))
		{
			ret = true;
			break;
		}
	}

	return ret;
}


std::vector<std::string> WhiteListIp::split(std::string str, std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str += pattern;
	int size = str.size();

	for (int i = 0; i < size; i++)
	{
		pos = str.find(pattern, i);
		if (pos < size)
		{
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}

int WhiteListIp::getIpScope(const std::string & strIp, unsigned int & src, unsigned int & dst)
{
	int ret = -1;
	unsigned int ipAddr;
	unsigned int umask = static_cast<unsigned int>(-1);
	do
	{
		if (strIp.empty())
		{
			break;
		}
		size_t pos = strIp.find('/');
		if (string::npos != pos)
		{
			std::string ips(strIp, 0, pos);
			std::string mks(strIp, pos + 1);
			unsigned iips = 0;
			unsigned int imks = atoi(mks.c_str());
			unsigned int isubnet = umask;
			ipAddr = inet_addr(ips.c_str());
			if (ipAddr == INADDR_NONE)
			{
				break;
			}
			iips = ntohl(ipAddr);
			isubnet = isubnet << (32 - imks);

			src = (iips & isubnet) + 1;
			dst = (iips & isubnet) + ~isubnet - 1;
		}
		else
		{
			ipAddr = inet_addr(strIp.c_str());
			if (ipAddr == INADDR_NONE)
			{
				break;;
			}
			src = dst = ntohl(ipAddr);
		}

		ret = 0;
	} while (0);

	return ret;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WhiteListEmlS::HashTable::HashTable()
{
	_data = new char[_len * sizeof(MpqHashTable_t)];
}

WhiteListEmlS::HashTable::~HashTable()
{
	if (_data)
	{
		delete _data;
		_data = nullptr;
	}
}

WhiteListEmlS::WhiteListEmlS()
{

}

WhiteListEmlS::~WhiteListEmlS()
{
}

bool WhiteListEmlS::initWhiteList()
{
	return MPQHashTableInit();
}

bool WhiteListEmlS::addInWhiteList(const char * src)
{
	if (!src || !strlen(src))
	{
		return false;
	}

	bool ret = false;
	std::vector<std::string> urlsv = split(std::string(src), ",");
	unsigned int icount = 0;

	do
	{
		if (urlsv.empty())
		{
			break;
		}

		for (const auto& item : urlsv)
		{
			if (MPQHashTableAdd(item.c_str()))
			{
				icount++;
			}
		}

		if (icount++)
		{
			ret = true;
		}
	} while (0);

	return ret;
}

bool WhiteListEmlS::isInWhiteList(const std::string & src)
{
	if (src.empty())
	{
		return false;
	}

	return MPQHashTableIsExist(src.c_str());
}

void WhiteListEmlS::InitCryptTable()
{
	unsigned long seed = 0x00100001, index1 = 0, index2 = 0, i;

	for (index1 = 0; index1 < 0x100; index1++)
	{
		for (index2 = index1, i = 0; i < 5; i++, index2 += 0x100)
		{
			unsigned long temp1, temp2;
			seed = (seed * 125 + 3) % 0x2AAAAB;
			temp1 = (seed & 0xFFFF) << 0x10;
			seed = (seed * 125 + 3) % 0x2AAAAB;
			temp2 = (seed & 0xFFFF);
			_cryptTable[index2] = (temp1 | temp2);
		}
	}
}

unsigned long WhiteListEmlS::HashString(const char *lpszString, unsigned long dwHashType)
{
	unsigned char *key = (unsigned char *)lpszString;
	unsigned long seed1 = 0x7FED7FED, seed2 = 0xEEEEEEEE;
	int ch;

	while (*key != 0)
	{
		ch = toupper(*key++);

		seed1 = _cryptTable[(dwHashType << 8) + ch] ^ (seed1 + seed2);
		seed2 = ch + seed1 + seed2 + (seed2 << 5) + 3;
	}
	return seed1;
}

bool WhiteListEmlS::MPQHashTableInit()
{
	bool ret = false;
	MpqHashTable_t *pHashTable = NULL;

	InitCryptTable();

	pHashTable = (MpqHashTable_t *)(_rules_emls._data);

	for (int i = 0; i < _rules_emls._len; i++)
	{
		(pHashTable + i)->_nHashA = -1;
		(pHashTable + i)->_nHashB = -1;
		(pHashTable + i)->_bExists = 0;
	}

	return true;
}

bool WhiteListEmlS::MPQHashTableAdd(const char *lpszString)
{
	const unsigned long HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
	unsigned long nHash = HashString(lpszString, HASH_OFFSET);
	unsigned long nHashA = HashString(lpszString, HASH_A);
	unsigned long nHashB = HashString(lpszString, HASH_B);
	unsigned long nHashStart = nHash % (_rules_emls._len);
	unsigned long nHashPos = nHashStart;
	MpqHashTable_t *pHashTable = (MpqHashTable_t *)(_rules_emls._data);

	while ((pHashTable + nHashPos)->_bExists)
	{
		if ((pHashTable + nHashPos)->_nHashA == nHashA && (pHashTable + nHashPos)->_nHashB == nHashB)
			return true;
		nHashPos = (nHashPos + 1) % (_rules_emls._len);

		if (nHashPos == nHashStart)
		{//no buf to store write record
			return false;
		}
	}

	(pHashTable + nHashPos)->_nHashA = nHashA;
	(pHashTable + nHashPos)->_nHashB = nHashB;
	(pHashTable + nHashPos)->_bExists = 1;

	return true;
}

bool WhiteListEmlS::MPQHashTableIsExist(const char *lpszString)
{
	const unsigned long HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
	unsigned long nHash = HashString(lpszString, HASH_OFFSET);
	unsigned long nHashA = HashString(lpszString, HASH_A);
	unsigned long nHashB = HashString(lpszString, HASH_B);
	unsigned long nHashStart = nHash % (_rules_emls._len);
	unsigned long nHashPos = nHashStart;
	MpqHashTable_t *pHashTable = (MpqHashTable_t *)(_rules_emls._data);
	while ((pHashTable + nHashPos)->_bExists)
	{
		if (((pHashTable + nHashPos)->_nHashA == nHashA) &&
			((pHashTable + nHashPos)->_nHashB == nHashB))
		{
			//return nHashPos;
			return true;
		}
		else
		{
			nHashPos = (nHashPos + 1) % (_rules_emls._len);
		}
		if (nHashPos == nHashStart)
		{
			break;
		}
	}
	return false;
}

std::vector<std::string> WhiteListEmlS::split(std::string str, std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str += pattern;
	int size = str.size();

	for (int i = 0; i < size; i++)
	{
		pos = str.find(pattern, i);
		if (pos < size)
		{
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

WhiteListIpS::WhiteListIpS()
{

}

WhiteListIpS::~WhiteListIpS()
{
}

bool WhiteListIpS::addInWhiteList(const char * ipls)
{
	if (!ipls || !strlen(ipls))
	{
		return false;
	}
	int ret = false;
	std::shared_ptr<IntervalList> ipp = std::make_shared<IntervalList>();
	std::vector<std::string> ips = split(std::string(ipls), ",");
	do
	{
		if (ips.empty())
		{
			break;
		}

		int iret = -1;
		unsigned int src, dst;
		std::vector<std::string>::iterator it;
		int sret = 0;
		it = ips.begin();
		for (; it != ips.end(); it++)
		{
			//cout << "src = " << *it << endl;
			sret = 0;
			iret = getIpScope(*it, src, dst);
			if (iret)
			{//错误
				continue;
			}
			cout << "++ src ip: " << *it << "==> [" << src << "," << dst << "] ";
			if (!ipp->addInInterval(src, dst))
			{
				cout << "failed" << endl;
				continue;
			}
			cout << "success" << endl;
			sret++;
		}

		if (sret)
		{
			ipp->generate();
			_rules_ips.push_back(ipp);
			ret = true;
		}
	} while (0);

	return ret;
}

bool WhiteListIpS::isInWhiteList(unsigned int src)
{
	bool ret = false;
	std::vector<std::shared_ptr<IntervalList>>::iterator it = _rules_ips.begin();
	for (; it != _rules_ips.end(); it++)
	{
		if ((*it)->isInInterval(src))
		{
			ret = true;
			break;
		}
	}

	return ret;
}

std::vector<std::string> WhiteListIpS::split(std::string str, std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str += pattern;
	int size = str.size();

	for (int i = 0; i < size; i++)
	{
		pos = str.find(pattern, i);
		if (pos < size)
		{
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}

int WhiteListIpS::getIpScope(const std::string & strIp, unsigned int & src, unsigned int & dst)
{
	int ret = -1;
	unsigned int ipAddr;
	unsigned int umask = static_cast<unsigned int>(-1);
	do
	{
		if (strIp.empty())
		{
			break;
		}
		size_t pos = strIp.find('/');
		if (string::npos != pos)
		{
			std::string ips(strIp, 0, pos);
			std::string mks(strIp, pos + 1);
			unsigned iips = 0;
			unsigned int imks = atoi(mks.c_str());
			unsigned int isubnet = umask;
			ipAddr = inet_addr(ips.c_str());
			if (ipAddr == INADDR_NONE)
			{
				break;
			}
			iips = ntohl(ipAddr);
			isubnet = isubnet << (32 - imks);

			src = (iips & isubnet) + 1;
			dst = (iips & isubnet) + ~isubnet - 1;
		}
		else
		{
			ipAddr = inet_addr(strIp.c_str());
			if (ipAddr == INADDR_NONE)
			{
				break;;
			}
			src = dst = ntohl(ipAddr);
		}

		ret = 0;
	} while (0);

	return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WhiteListUrlS::WhiteListUrlS()
{

}

WhiteListUrlS::~WhiteListUrlS()
{
}

bool WhiteListUrlS::addInWhiteList(const char * urls)
{
	if (!urls || !strlen(urls))
	{
		return false;
	}
	bool ret = false;
	std::vector<std::string> urlsv = split(std::string(urls), ",");
	unsigned int icount = 0;

	do
	{
		if (urlsv.empty())
		{
			break;
		}

		for (const auto &url : urlsv)
		{
			auto iret = _rules_urls.insert(url);
			if (iret.second)
			{
				cout << "add url = " << url << endl;
				icount++;
			}
		}

		if (icount)
		{
			ret = true;
		}

	} while (0);

	return ret;
}

bool WhiteListUrlS::isInWhiteList(const std::string &url)
{
	bool ret = false;
	for (const auto &item : _rules_urls)
	{
		if (std::string::npos != url.find(item))
		{
			ret = true;
			break;
		}
	}
	return ret;
}

std::vector<std::string> WhiteListUrlS::split(std::string str, std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str += pattern;
	int size = str.size();

	for (int i = 0; i < size; i++)
	{
		pos = str.find(pattern, i);
		if (pos < size)
		{
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WhiteListManger::WhiteListManger()
{

}

WhiteListManger::~WhiteListManger()
{

}

int WhiteListManger::init(const std::string &addr, const unsigned int port, const std::string &db, const std::string &user, const std::string &passwd)
{
	_addr = addr;
	_port = port;
	_db = db;
	_user = user;
	_passwd = passwd;

	return 0;
}

bool WhiteListManger::isInWhiteListEml(const std::string &src, const std::string &dst)
{
	bool ret = false;
	do {
		if (src.empty() || dst.empty())
		{
			break;
		}

		if (!_rule_eml)
		{
			break;
		}
		std::shared_ptr<WhiteListEml> rule_eml(_rule_eml);
		ret = rule_eml->isInWhiteList(src, dst);
		cout << "src = " << src << "\ndst = " << dst << "\nret = " << ret << endl;
	} while (0);

	return ret;
}


bool WhiteListManger::isInWhiteListIp(const std::string & src, const std::string & dst)
{
	bool ret = false;

	do
	{
		if (src.empty() || dst.empty())
		{
			break;
		}

		if (!_rule_ip)
		{
			break;
		}

		unsigned int isrc = ntohl(static_cast<unsigned int>(inet_addr(src.c_str())));
		unsigned int idst = ntohl(static_cast<unsigned int>(inet_addr(dst.c_str())));
		std::shared_ptr<WhiteListIp> rule_ip(_rule_ip);

		ret = rule_ip->isInWhiteList(isrc, idst);
		cout << " [" << src << ":" << isrc << "," << dst << ":" << idst << "] ===>" << ret << endl;

	} while (0);

	return ret;
}


bool WhiteListManger::isInWhiteListEmlPS(const std::string & src)
{
	bool ret = false;
	do {
		if (src.empty())
		{
			break;
		}

		if (!_rule_eml_ss)
		{
			break;
		}
		std::shared_ptr<WhiteListEmlS> rule_eml_ss(_rule_eml_ss);
		ret = rule_eml_ss->isInWhiteList(src);
		cout << "src  Eml = " << src << " ===> " << ret << endl;
	} while (0);

	return ret;
}

bool WhiteListManger::isInWhiteListEmlPD(const std::string & dst)
{
	bool ret = false;
	do {
		if (dst.empty())
		{
			break;
		}

		if (!_rule_eml_sd)
		{
			break;
		}
		std::shared_ptr<WhiteListEmlS> rule_eml_sd(_rule_eml_sd);
		ret = rule_eml_sd->isInWhiteList(dst);
		cout << "dst Eml = " << dst << " ===> " << ret << endl;
	} while (0);

	return ret;
}

bool WhiteListManger::isInWhiteListIpPS(const string & src)
{
	bool ret = false;

	do
	{
		if (src.empty())
		{
			break;
		}

		if (!_rule_ip_ss)
		{
			break;
		}
		unsigned int isrc = ntohl(static_cast<unsigned int>(inet_addr(src.c_str())));
		std::shared_ptr<WhiteListIpS> rule_ip_ss(_rule_ip_ss);
		ret = rule_ip_ss->isInWhiteList(isrc);
		cout << " [" << src << ":" << isrc << "] ===>" << ret << endl;

	} while (0);

	return ret;
}

bool WhiteListManger::isInWhiteListIpPD(const string & dst)
{
	bool ret = false;

	do
	{
		if (dst.empty())
		{
			break;
		}

		if (!_rule_ip_sd)
		{
			break;
		}
		unsigned int idst = ntohl(static_cast<unsigned int>(inet_addr(dst.c_str())));
		std::shared_ptr<WhiteListIpS> rule_ip_sd(_rule_ip_sd);
		ret = rule_ip_sd->isInWhiteList(idst);
		cout << " [" << dst << ":" << idst << "] ===>" << ret << endl;

	} while (0);

	return ret;
}

bool WhiteListManger::isInWhiteListUrlP(const string & src)
{
	bool ret = false;

	do
	{
		if (src.empty())
		{
			break;
		}

		if (!_rule_uml_ss)
		{
			break;
		}

		std::shared_ptr<WhiteListUrlS> rule_uml_ss(_rule_uml_ss);
		ret = rule_uml_ss->isInWhiteList(src);
		cout << " [" << src << "] ===>" << ret << endl;
	} while (0);
	return ret;
}

bool WhiteListManger::loadRules()
{
	loadP();
	loadP2P();
	return true;
}

bool WhiteListManger::loadP()
{
	std::cout << _db << " " << _addr << " " << _user << " " << _passwd << endl;
	int ret = false;
	//初始化mysql连接句柄
	bool blink = false;
	std::shared_ptr<WhiteListEmlS> rule_eml_ss = std::make_shared<WhiteListEmlS>();
	std::shared_ptr<WhiteListEmlS> rule_eml_sd = std::make_shared<WhiteListEmlS>();

	std::shared_ptr<WhiteListIpS> rule_ip_ss = std::make_shared<WhiteListIpS>();
	std::shared_ptr<WhiteListIpS> rule_ip_sd = std::make_shared<WhiteListIpS>();

	std::shared_ptr<WhiteListUrlS> rule_uml_ss = std::make_shared<WhiteListUrlS>();

	std::shared_ptr<mysqlpp::Connection> dbConnection = std::make_shared<mysqlpp::Connection>(false);

	do
	{
		dbConnection->set_option(new mysqlpp::SetCharsetNameOption("utf8"));
		
		if (dbConnection->connect(_db.c_str(), _addr.c_str(), _user.c_str(), _passwd.c_str(), 0))
		{
			blink = true;
			cout << "log on mysql successful" << endl;
		}
		else
		{
			cout << dbConnection->error() << endl;
			break;
		}

		mysqlpp::Query queryP = dbConnection->query(_queryP);
		if (mysqlpp::StoreQueryResult resp = queryP.store())
		{
			bool b_eml_s = rule_eml_ss->initWhiteList();
			bool b_eml_d = rule_eml_sd->initWhiteList();
			unsigned int hc = 0, ic = 0, jc = 0, kc = 0, lc = 0;
			mysqlpp::StoreQueryResult::const_iterator it;
			cout << "===========================whitelist-P=========================" << endl;
			for (it = resp.begin(); it != resp.end(); ++it)
			{
				const mysqlpp::Row & row = *it;
				//cout << row[0] << "==" << row[1] << "==" << row[2] << "==" << row[3] << "==" << row[4] << endl;

				if (b_eml_s && rule_eml_ss->addInWhiteList(row[0]))
				{
					hc++;
					cout << "src Mail = " << row[0] << endl;
				}

				if (b_eml_d && rule_eml_sd->addInWhiteList(row[1]))
				{
					ic++;
					cout << "dst Mail = " << row[1] << endl;
				}

				if (rule_ip_ss->addInWhiteList(row[2]))
				{
					jc++;
					cout << "src Ip = " << row[2] << endl;
				}

				if (rule_ip_sd->addInWhiteList(row[3]))
				{
					kc++;
					cout << "dst Ip = " << row[3] << endl;
				}

				if (rule_uml_ss->addInWhiteList(row[4]))
				{
					lc++;
					cout << "url = " << row[4] << endl;
				}

			}

			_rule_eml_ss.swap(rule_eml_ss);
			_rule_eml_sd.swap(rule_eml_sd);
			
			_rule_ip_ss.swap(rule_ip_ss);
			_rule_ip_sd.swap(rule_ip_sd);

			_rule_uml_ss.swap(rule_uml_ss);

			ret = true;
			cout << "rule-p====emls [ " << hc << ":" << ic << " ]" << "===" << " ip = [ " << jc << ":" << kc << " ]" << "===" << "urls = [ " << lc << " ]" << endl;
		}
		else
		{
			cout << "获取查询结果失败-端点！ " << _queryP << " err = " << queryP.error() << endl;
		}
	} while (0);

	//释放连接句柄
	if (blink)
	{
		dbConnection->disconnect();
	}

	dbConnection.reset();

	return ret;
}

bool WhiteListManger::loadP2P()
{
	int ret = -1;
	//初始化mysql连接句柄
	bool blink = false;

	std::shared_ptr<WhiteListEml> rule_eml = std::make_shared<WhiteListEml>();
	std::shared_ptr<WhiteListIp> rule_ip = std::make_shared<WhiteListIp>();

	std::shared_ptr<mysqlpp::Connection> dbConnection = std::make_shared<mysqlpp::Connection>(false);

	do
	{
		dbConnection->set_option(new mysqlpp::SetCharsetNameOption("utf8"));
		if (dbConnection->connect(_db.c_str(), _addr.c_str(), _user.c_str(), _passwd.c_str(), 0))
		{
			blink = true;
			cout << "log on mysql successful" << endl;
		}
		else
		{
			cout << dbConnection->error() << endl;
			break;
		}
		//获取端对端白名单
		mysqlpp::Query queryP2P = dbConnection->query(_queryP2P);
		if (mysqlpp::StoreQueryResult res = queryP2P.store())
		{
			unsigned int ic = 0;
			unsigned int jc = 0;
			mysqlpp::StoreQueryResult::const_iterator it;
			cout << "===========================whitelist-p2p=========================" << endl;
			for (it = res.begin(); it != res.end(); ++it)
			{
				const mysqlpp::Row & row = *it;
				//cout << "==" << row[0] << "==" << row[1] << "==" << row[2] << "==" << row[3] << "==" << endl;
				if (rule_eml->addInWhiteList(row[0], row[1]))
				{
					++ic;
					cout << "src = " << row[0] << "\tdst = " << row[1] << endl;			
				}

				if (rule_ip->addInWhiteList(row[2], row[3]))
				{
					++jc;
					cout << "src = " << row[2] << "\tdst = " << row[3] << endl;			
				}

			}

			_rule_eml.swap(rule_eml);
			_rule_ip.swap(rule_ip);

			ret = true;
			cout << "rule-p2p====eml = " << ic << " ====" << " ip = " << jc << " ====" << endl;
		}
		else
		{
			cout << "获取查询结果失败-端对端！ " << _queryP2P << " err = " << queryP2P.error() << endl;
		}
	} while (0);

	//释放连接句柄
	if (blink)
	{
		dbConnection->disconnect();
	}
	dbConnection.reset();

	return ret;
}
