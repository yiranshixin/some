#ifndef H_PCRE2J
#define H_PCRE2J

#include "pcre2.h"
#include <memory>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

class IRegexMatcher
{
public:
	virtual ~IRegexMatcher(void) {};

	virtual bool setRegexExpression(const std::string &regexExpression) = 0;
	virtual bool IsExistMatchedItem(const char* data, uint64_t length, uint64_t fileOffset) const = 0;
};

class RegexMatcherPcre2 :public IRegexMatcher
{
public:
	static void config();


	RegexMatcherPcre2();
	virtual ~RegexMatcherPcre2(void);

	virtual bool setRegexExpression(const std::string &regexExpression) override;
	virtual bool IsExistMatchedItem(const char* data, uint64_t length, uint64_t fileOffset) const override;

protected:

	typedef std::shared_ptr<pcre2_code> CodePointer;
	typedef std::shared_ptr<pcre2_match_data> MatchDataPointer;
	typedef std::shared_ptr<pcre2_match_context> MatchContextPointer;
	typedef std::shared_ptr<pcre2_jit_stack> JITStackPointer;

	struct MatchData
	{
		CodePointer _code;
		std::string _pattern;
	};

	uint32_t _optionsCompile{ 0 };
	uint32_t _optionsMatch{ 0 };
	MatchData _md;
};

class RegexPair
{
public:
	virtual ~RegexPair();
	bool IsExistMatchedItem(const std::string &sdata, const std::string &dst);
	bool setRegexExpression(const std::string &src, const std::string &dst);
private:
	RegexMatcherPcre2 _regexs;
	RegexMatcherPcre2 _regexd;
};


class WhiteListEml
{
public:
	//WhiteListEml();
	//virtual ~WhiteListEml();
	bool addInWhiteList(const char *src, const char *dst);
	bool isInWhiteList(const std::string &src, const std::string &dst);
private:
	std::vector<std::shared_ptr<RegexPair>> _rules_eml;
};


class Interval
{
public:
	Interval();
	Interval(unsigned int s, unsigned int e);
	Interval(const Interval &other);
	Interval& operator=(const Interval &other);

	bool operator <(const Interval & itv);
	bool isInScope(unsigned int i);
public:
	unsigned int _start;
	unsigned int _end;
};

class IntervalList
{
public:
	bool addInInterval(unsigned int src, unsigned int dst);
	bool isInInterval(unsigned int src);
	void generate();
private:
	std::vector<Interval> _intervals;
};

class IpPair
{
public:
	IpPair();
	virtual ~IpPair();
	bool addInIpPair(unsigned int src, unsigned int dst, bool bType);
	bool isInIpPair(unsigned int src, unsigned int dst);
	void generate();
private:
	IntervalList _src;
	IntervalList _dst;
};

class WhiteListIp
{
public:
	WhiteListIp();
	virtual ~WhiteListIp();
	bool addInWhiteList(const char *ipls, const char *ipsd);
	bool isInWhiteList(unsigned int src, unsigned int dst);

private:
	std::vector<std::string> split(std::string str, std::string pattern);
	int getIpScope(const std::string &strIp, unsigned int &src, unsigned int &dst);
	std::vector<std::shared_ptr<IpPair>> _rules_ip;
};


class WhiteListEmlS
{
public:
	WhiteListEmlS();
	virtual ~WhiteListEmlS();
	bool initWhiteList();
	bool addInWhiteList(const char *src);
	bool isInWhiteList(const std::string &src);

private:
	typedef struct MpqHashTable {
		long _nHashA;
		long _nHashB;
		unsigned int _bExists;
	}MpqHashTable_t;

	typedef struct HashTable
	{
		HashTable();
		virtual ~HashTable();

		unsigned int _len{ 8192 };
		char* _data;
	}HashTable_t;

	unsigned long HashString(const char *lpszString, unsigned long dwHashType);
	void InitCryptTable();

	bool MPQHashTableInit();
	bool MPQHashTableAdd(const char *lpszString);
	bool MPQHashTableIsExist(const char *lpszString);

	std::vector<std::string> split(std::string str, std::string pattern);

	unsigned long _cryptTable[0x500];
	HashTable_t _rules_emls;
};



class WhiteListIpS
{
public:
	WhiteListIpS();
	virtual ~WhiteListIpS();

	bool addInWhiteList(const char *ipls);
	bool isInWhiteList(unsigned int src);

private:
	std::vector<std::string> split(std::string str, std::string pattern);
	int getIpScope(const std::string &strIp, unsigned int &src, unsigned int &dst);
	std::vector<std::shared_ptr<IntervalList>> _rules_ips;
};

class WhiteListUrlS
{
public:
	WhiteListUrlS();
	virtual ~WhiteListUrlS();

	bool addInWhiteList(const char *urls);
	bool isInWhiteList(const std::string &url);

private:
	std::vector<std::string> split(std::string str, std::string pattern);
	std::unordered_set<std::string> _rules_urls;
};


class WhiteListManger
{
public:
	WhiteListManger();
	virtual ~WhiteListManger();
	int init(const std::string& addr, const unsigned int port, const std::string& db, const std::string& user, const std::string& passwd);

	bool isInWhiteListEml(const std::string &src, const std::string &dst);

	bool isInWhiteListIp(const std::string &src, const std::string &dst);

	bool isInWhiteListEmlPS(const std::string &src);
	bool isInWhiteListEmlPD(const std::string &dst);

	bool isInWhiteListIpPS(const string &src);
	bool isInWhiteListIpPD(const string &dst);

	bool isInWhiteListUrlP(const string &src);

	bool loadRules();
private:
	bool loadP2P();
	bool loadP();

private:
	std::string _addr{ "127.0.0.1" };
	unsigned int _port{ 3306 };
	std::string _db{ "ws_dlp" };
	std::string _user{ "root" };
	std::string _passwd{ "tmdlp" };

	std::string _queryP2P{ "select srcMails, destMails, srcIps, destIps from d_white_list_info where type=3" };
	std::string _queryP{ "select srcMails, destMails, srcIps, destIps, urls from d_white_list_info where type=2" };

	std::shared_ptr<WhiteListEml> _rule_eml;
	std::shared_ptr<WhiteListIp> _rule_ip;

	std::shared_ptr<WhiteListEmlS> _rule_eml_ss;
	std::shared_ptr<WhiteListEmlS> _rule_eml_sd;

	std::shared_ptr<WhiteListIpS> _rule_ip_ss;
	std::shared_ptr<WhiteListIpS> _rule_ip_sd;

	std::shared_ptr<WhiteListUrlS> _rule_uml_ss;

private:
	WhiteListManger(const WhiteListManger &);
	WhiteListManger operator=(const WhiteListManger &);
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
