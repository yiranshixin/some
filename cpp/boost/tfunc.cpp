#include <iostream> 
#include <vector> 
#include <algorithm> 

#include <boost/bind.hpp>
#include <boost/function.hpp>


void add(int i, int j, std::ostream &os) { os << i + j << std::endl; }

void print(int i) { std::cout << i << std::endl;} 

void add(int i, int j) { std::cout << i + j << std::endl;} 

void sub(int i, int j) { std::cout << i - j << std::endl;}

class Add:public std::binary_function<int,int,void>
{
	public:
		void operator()(int i, int j) const{std::cout<<i + j<<std::endl;}
};


bool compare(int i, int j) { return i < j; }


void test_0()
{

        std::vector<int> v;
        v.push_back(1);
        v.push_back(3);
        v.push_back(2);

        std::for_each(v.begin(), v.end(), print);

        std::for_each(v.begin(), v.end(), std::bind1st(Add(),10));

        std::for_each(v.begin(), v.end(), boost::bind(add,100,_1));

        std::for_each(v.begin(), v.end(), boost::bind(sub,1000,_1));
        std::for_each(v.begin(), v.end(), boost::bind(sub,_1,1000));


        std::sort(v.begin(), v.end(), compare);
        std::for_each(v.begin(), v.end(), print);
        std::sort(v.begin(), v.end(), boost::bind(compare, _2, _1));
        std::for_each(v.begin(), v.end(), print);


        std::for_each(v.begin(), v.end(), boost::bind(add, _1,10000, boost::ref(std::cout)));

}



struct world 
{ 
  void hello(std::ostream &os) 
  { 
    os << "Hello, world!" << std::endl; 
  } 
};


void test_1()
{
	boost::function<int(char *)> f;
	f = atoi;
	std::cout<<"atoi(123) = "<<f("123")<<std::endl;
	f = strlen;
	std::cout<<"strlen(123) = "<<f("123")<<std::endl;

	boost::function<void(world*, std::ostream &os)> f1 = &world::hello;
	world w;
	f1(&w,boost::ref(std::cout));
}

int main() 
{ 
	test_0();
	test_1();
	return 0;	
} 
