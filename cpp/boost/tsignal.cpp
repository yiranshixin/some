#include <boost/signals2.hpp>
#include <iostream>

using namespace boost::signals2;

void test_1()
{

        signal<void()> s;
        s.connect([]{ std::cout << "Hello,"; });
        s.connect([]{ std::cout << "world!\n"; });
        s();
}


void test_2()
{
	signal<void()> s;
	s.connect(1, []{ std::cout << ", world!\n"; });
	s.connect(0, []{ std::cout << "Hello"; });
	s();
}

void print_1()
{
	std::cout<<"hello,";
}

void print_2()
{
	std::cout<<" world !"<<std::endl;
}

void test_3()
{
	signal<void()> s;
	s.connect(print_1);
	s.connect(print_2);
	s();
}


void test_4()
{
        signal<void()> s;
        s.connect(print_1);
        s.connect(print_2);
        s();
	s.disconnect(print_1);
	s();
	std::cout<<"slots = "<<s.num_slots()<<std::endl;
	if(!s.empty())
	{
		s.disconnect_all_slots();
	}

	std::cout<<"slots = "<<s.num_slots()<<std::endl;
}

int main()
{
	test_1();
	test_2();
	test_3();
	test_4();
	return 0;
}
 
