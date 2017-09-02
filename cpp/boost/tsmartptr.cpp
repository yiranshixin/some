#include <boost/scoped_ptr.hpp> 
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <vector>
#include <iostream>
#include <typeinfo>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void test1()
{
	boost::scoped_ptr<int> i(new int);
	*i = 1;
	*i.get() = 2;
	i.reset(new int);
}

void test2()
{
	boost::shared_ptr<int> i1(new int(1)); 
	boost::shared_ptr<int> i2(i1);
	std::cout<<i1.use_count()<<std::endl;
	i1.reset(new int(2));
	std::cout<<i1.use_count()<<std::endl;
}



void test3()
{
	std::vector<boost::shared_ptr<int> > v;
	v.push_back(boost::shared_ptr<int>(new int(1)));
	v.push_back(boost::shared_ptr<int>(new int(2)));
}


void test4()
{
       	//boost::shared_ptr<void> h(open("./tsmartptr",O_RDONLY), close);
        //boost::shared_ptr<void> h(OpenProcess(PROCESS_SET_INFORMATION, FALSE, GetCurrentProcessId()), CloseHandle);
        //SetPriorityClass(h.get(), HIGH_PRIORITY_CLASS);
}

void test5()
{
	auto p1 = boost::make_shared<int>(1);
	std::cout << typeid(p1).name() << '\n';
	auto p2 = boost::make_shared<int[]>(10);
	std::cout << typeid(p2).name() << '\n';
}

int main() 
{
	test1();
	test2();
	test3();
	test4();
	test5();
	
	return 0;
} 
