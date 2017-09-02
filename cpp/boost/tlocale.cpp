#include <locale> 
#include <iostream> 
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/tokenizer.hpp>
void test1()
{
  std::locale loc;
  std::cout << loc.name() << std::endl;
}

void test2()
{
	std::string s("Xu Junshuai who came from and now in Beijing love programing with cplusplus !");
	std::cout<<s<<std::endl;
	std::cout<<boost::algorithm::to_upper_copy(s)<<std::endl;
	std::cout<<boost::algorithm::to_lower_copy(s)<<std::endl;
	std::cout<<s<<std::endl;
	
	boost::algorithm::to_upper(s);
	std::cout<<s<<std::endl;
	boost::algorithm::to_lower(s);
	std::cout<<s<<std::endl;
	
	
	std::cout << boost::algorithm::erase_first_copy(s, "u") << std::endl; 
	std::cout << boost::algorithm::erase_nth_copy(s, "u", 1) << std::endl; 
	std::cout << boost::algorithm::erase_last_copy(s, "u") << std::endl; 
	std::cout << boost::algorithm::erase_all_copy(s, "u") << std::endl; 
	std::cout << boost::algorithm::erase_head_copy(s, 5) << std::endl; 
	std::cout << boost::algorithm::erase_tail_copy(s, 8) << std::endl; 	
	
	boost::algorithm::erase_first(s, "u");
        std::cout<<s<<std::endl;
	boost::algorithm::erase_nth(s, "u", 1);
	std::cout<<s<<std::endl;
        boost::algorithm::erase_last(s, "u");
	std::cout<<s<<std::endl;
        boost::algorithm::erase_all(s, "u");
	std::cout<<s<<std::endl;
        boost::algorithm::erase_head(s, 5);
	std::cout<<s<<std::endl;
        boost::algorithm::erase_tail(s, 8);
	std::cout<<s<<std::endl;


	boost::iterator_range<std::string::iterator> r = boost::algorithm::find_first(s, "in");
	std::cout<<r<<std::endl;
	r = boost::algorithm::find_last(s,"it");
	std::cout<<r<<std::endl;
	r = boost::algorithm::find_nth(s,"it",3);
	std::cout<<r<<std::endl;
	r = boost::algorithm::find_head(s,5);
	std::cout<<r<<std::endl;
	r = boost::algorithm::find_tail(s,10);
	std::cout<<r<<std::endl;

	std::vector<std::string> vs;
	boost::algorithm::find_all(vs,s,"it");
	for(auto& v : vs){std::cout<<v<<std::endl;}

	r = boost::algorithm::find_first(s,"xys");
	std::cout<<r<<std::endl;




	std::string ss = "123456789Boris Schaling123456789"; 
	std::cout<< boost::algorithm::trim_left_copy_if(ss, boost::algorithm::is_digit()) << std::endl; 
	std::cout<<boost::algorithm::trim_right_copy_if(ss, boost::algorithm::is_digit()) << "." << std::endl; 
	std::cout<<boost::algorithm::trim_copy_if(ss, boost::algorithm::is_digit()) << std::endl; 


	
	bool bflag = false;
	bflag = boost::starts_with(s,"xu");
	std::cout<<"start with "<<(bflag ? "t":"f")<<std::endl;
	bflag = boost::ends_with(s,"!");
	std::cout<<"end with "<<(bflag ? "t":"f")<<std::endl;
	bflag = boost::equals(s,"xjs");
	std::cout<<"equal with "<<(bflag ? "t":"f")<<std::endl;
	bflag = boost::contains(s,"it");
	std::cout<<"contain with "<<(bflag ? "t":"f")<<std::endl;
	bflag = boost::all(s,boost::is_any_of("ibm")&& !boost::is_space() );
	std::cout<<"all with "<<(bflag ? "t":"f")<<std::endl;



	std::vector<std::string> vv;
	vv.push_back("xx");
	vv.push_back("yy");
	vv.push_back("zz");
	std::cout<<boost::algorithm::join(vv,"-")<<std::endl;
	
	
	
	std::cout << boost::algorithm::replace_first_copy(s, "i", "D") << std::endl; 
	std::cout << boost::algorithm::replace_nth_copy(s, "i", 2, "D") << std::endl; 
	std::cout << boost::algorithm::replace_last_copy(s, "i", "D") << std::endl; 
	std::cout << boost::algorithm::replace_all_copy(s, "i", "D") << std::endl; 
	std::cout << boost::algorithm::replace_head_copy(s, 5, "Doris") << std::endl; 
	std::cout << boost::algorithm::replace_tail_copy(s, 8, "Becker") << std::endl;

	std::vector<std::string> vvv;
	boost::algorithm::split(vvv,s,boost::algorithm::is_any_of(" ,;.?!"));
	for(auto &v : vvv){std::cout<<v<<std::endl;} 
}


void test3()
{
	std::string s = "Boris Schaling xu jun shuai"; 
	boost::regex expr("\\w+\\s\\w+"); 
	std::cout << boost::regex_match(s, expr) << std::endl;
	
	boost::regex expr1("(\\w+)\\s(\\w+)"); 
	boost::smatch what; 
	if (boost::regex_search(s, what, expr1)) 
	{ 
		std::cout << what[0] << std::endl; 
		std::cout << what[1] << "=" << what[2] << std::endl; 
	}

	std::string s5 = "Boris Schaling xu jun shuai";
	boost::regex expr5("\\w+");  
	boost::sregex_iterator it5(s5.begin(), s5.end(), expr5);  
	boost::sregex_iterator end5;  
	for (; it5 != end5; ++it5) 
		std::cout << *it5 << std::endl; 

	std::string s6 = "Boris Schaling xu jun shuai";
	boost::regex expr6("\\w+");
	boost::smatch what6;
	std::string::const_iterator start6 = s6.begin();
	std::string::const_iterator end6 = s6.end();
	while ( boost::regex_search(start6, end6, what6, expr6) )  
	{  
		std::cout << what6[0] << std::endl;
		start6 = what6[0].second;  
	}  

	boost::regex expr2("\\s"); 
	std::string fmt2("_"); 
	std::cout << boost::regex_replace(s, expr2, fmt2) << std::endl;

	boost::regex expr3("(\\w+)\\s(\\w+)"); 
	std::string fmt3("\\2 \\1"); 
	std::cout << boost::regex_replace(s, expr3, fmt3) << std::endl; 


	boost::regex expr4("(\\w+)\\s(\\w+)"); 
	std::string fmt4("\\2 \\1"); 
	std::cout << boost::regex_replace(s, expr4, fmt4, boost::regex_constants::format_literal) << std::endl; 	
}

void test4()
{
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer; 
	std::string s = "Boost C++ libraries"; 
	boost::char_separator<char> sep(" "); 
	tokenizer tok(s, sep); 
	for (tokenizer::iterator it = tok.begin(); it != tok.end(); ++it) 
		std::cout << *it << std::endl; 
}


int main() 
{ 
	//test1();
	//test2();
	//test3();
	test4();
	return 0;
} 
