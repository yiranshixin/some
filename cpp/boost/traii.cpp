#include <boost/scope_exit.hpp>

#include <iostream>
#include <utility>

void foo()
{
	int* i = new int(10);
	BOOST_SCOPE_EXIT(&i)
	{
		delete i;
		i = NULL;
		std::cout<<"after..."<<std::endl;
	}BOOST_SCOPE_EXIT_END
	
	*i = 100;
	std::cout<<"i = "<<*i<<std::endl;
	
}


void foo1()
{
	BOOST_SCOPE_EXIT(void)
        {
		std::cout<<"second"<<std::endl;
        }BOOST_SCOPE_EXIT_END
	
	BOOST_SCOPE_EXIT(void)
        {
		std::cout<<"first"<<std::endl;
	}BOOST_SCOPE_EXIT_END

	std::cout<<"before..."<<std::endl;
}


struct Foo
{
	int v_;

	void foo()
	{
		v_ = 0;
		BOOST_SCOPE_EXIT(this_)
		{
			this_->v_ = 1;
			std::cout<<this_->v_<<std::endl;
		}BOOST_SCOPE_EXIT_END
		std::cout<<v_<<std::endl;
	}
};


template <typename T>
struct scope_exit
{
	scope_exit(T&& t):_t{std::move(t)}{}
	~scope_exit(){ _t(); }
	T _t;
};

template<typename T>
scope_exit<T> make_scope_exit(T&& t){ return scope_exit<T>(std::move(t));}

void cfoo()
{
  int *i = new int{10};
  auto cleanup = make_scope_exit([&i]() mutable { delete i; i = 0; });
  std::cout << *i << '\n';
}

int main(int args, char **argv)
{
	foo();
	foo1();

	Foo f;
	f.foo();

	cfoo();
	return 0;
}
