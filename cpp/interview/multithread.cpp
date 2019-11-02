#include <iostream>
#include <fstream>

#include <thread>
#include <mutex>
#include <future>

#include <chrono>

#include <random>

#include <deque>

using namespace std;

//thread
void cb0() 
{
	std::cout << __FUNCTION__ << endl;
	for (int i = 0; i < 10; i++)
	{
		std::cout << i << "\t";
	}
	cout << endl;
	return;
}

void cb1(int n) 
{
	std::cout << __FUNCTION__ << endl;
	for (int i = 0; i < n; i++)
	{
		std::cout << i << "\t";
	}
	cout << endl;
	return;
}

class Cbc {
public:
	void cb2() {
		std::cout << __FUNCTION__ << endl;
		for (int i = 0; i < 10; i++)
		{
			std::cout << i << "\t";
		}
		cout << endl;
		return;
	}

	void cb3(int n) 
	{
		std::cout << __FUNCTION__ << endl;
		for (int i = 0; i < n; i++)
		{
			std::cout << i << "\t";
		}
		cout << endl;
		return;
	}

	void operator()()
	{
		std::cout << __FUNCTION__ << endl;
		for (int i = 0; i < 10; i++)
		{
			std::cout << i << "\t";
		}
		cout << endl;
		return;
	}
};

void test_thread() 
{
	std::thread t0(cb0);
	std::thread t1(cb1, 10);

	Cbc cbc;
	std::thread t2(&Cbc::cb2, &cbc);
	std::thread t3(&Cbc::cb3, &cbc, 10);
	std::thread t4(cbc);

	std::thread t5([](int n){
		std::cout << __FUNCTION__ << endl;
		for (int i = 0; i < n; i++)
		{
			std::cout << i << "\t";
		}
		cout << endl;
		return;
	},10);

	t0.join();
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
}

/////////////////////////////////////////////////////////////////////
//mutex
class Log 
{
public:
	Log(const std::string& logFile)
	{
		m_logstream.open(logFile);
	}

	~Log() 
	{
		m_logstream.close();
	}

	void wLog(const string func, const string& msg)
	{
		std::lock_guard<std::mutex> lc(m_mtx);
		
		m_logstream << "[" << func.c_str() << "]" <<": " << msg.c_str() << std::endl;
		//std::cout << "[" << func.c_str() << "]" << ": " << msg.c_str() << std::endl;

		return;
	}
private:
	fstream m_logstream;
	std::mutex m_mtx;
	static std::once_flag m_once_flag;
};

void test_mutex()
{
	Log log("x.log");
	std::thread t0([&log]() {
		for (int i = 0; i < 10; i++)
		{
			log.wLog(__FUNCTION__, "######");
		}
	});

	std::thread t1([&log]() {
		for (int i = 0; i < 10; i++)
		{
			log.wLog(__FUNCTION__, "******");
		}
	});

	t0.join();
	t1.join();
}

/////////////////////////////////////////////////////////////////////
//once_flag
class Module
{
public:
	Module() {}
	
	~Module() {}
	
	static void init(int i, int j, int k)
	{
		std::cout << "tid = " << std::this_thread::get_id() << std::endl;
		
		static std::once_flag once_init;
		std::call_once(once_init, [](int ii, int jj, int kk) {
			std::cout << "******call_once******" << std::endl;
			std::cout << ii << jj << kk << std::endl;

			m_once++;

			std::cout << "m_once = " << m_once << std::endl;
			
		}, i, j, k);
	}
private:
	static int m_once;
};

int Module::m_once = 0;

void test_callonce() 
{
	std::thread t0(&Module::init, 1, 2, 3);
	std::thread t1(&Module::init, 4, 5, 6);
	std::thread t2(&Module::init, 7, 8, 9);
	
	t0.join();
	t1.join();
	t2.join();
}
/////////////////////////////////////////////////////////////////////
//condition_variable
template<typename T>
class BlockingQueue
{
public:
	BlockingQueue() {}
	~BlockingQueue() {}

	void push(const T& data) 
	{
		std::unique_lock<std::mutex> ul(m_mtx);
		m_data.push_back(data);
		m_cv.notify_one();
	}

	void push(T&& data)
	{
		std::unique_lock<std::mutex> ul(m_mtx);
		m_data.push_back(std::move(data));
		m_cv.notify_one();
	}

	T pop()
	{
		std::unique_lock<std::mutex> ul(m_mtx);
		m_cv.wait(ul, [&]() {
			return !m_data.empty();
		});
		
		T t = std::move(m_data.front());
		m_data.pop_front();

		return std::move(t);
	}
private:
	BlockingQueue(const BlockingQueue&) = delete;
	BlockingQueue& operator=(const BlockingQueue&) = delete;

private:
	mutable std::mutex m_mtx;
	std::condition_variable m_cv;
	std::deque<T> m_data;
};

class CP
{
public:

	void productor()
	{
		for (int i = 0; i < 100;i++)
		{
			std::this_thread::sleep_for(std::chrono::microseconds(1000));
			//std::cout << "c:\t" << i << endl;
			m_blq.push(i);
		}

		return;
	}

	void consumer()
	{
		for (;;)
		{
			int i = m_blq.pop();
			std::cout << "p: [" <<std::this_thread::get_id()<<"]: "<< i << endl;
		}

		return;
	}
private:
	BlockingQueue<int> m_blq;
};

void test_cv() 
{
	CP cp;
	std::thread t0(&CP::productor, &cp);
	std::thread t1(&CP::productor, &cp);
	std::thread t2(&CP::productor, &cp);
	std::thread t3(&CP::productor, &cp);

	std::thread t4(&CP::consumer, &cp);
	std::thread t5(&CP::consumer, &cp);
	t0.join();
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	return;
}

//////////////////////////////////////////////////////////////////////
void test_static_func() 
{
	std::thread::id tid = std::this_thread::get_id();
	std::cout << "*****************tid = " << tid <<"***************" << std::endl;
	unsigned int icpu = std::thread::hardware_concurrency();
	std::cout << "*****************cpu = "<< icpu <<"***************" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout << "*****************first***************" << std::endl;
	auto now = std::chrono::steady_clock::now();
	std::this_thread::sleep_until(now + std::chrono::seconds(5));
	std::cout << "*****************second***************" << std::endl;
	std::this_thread::yield();
	std::cout << "******************third****************" << std::endl;
	return;
}
/////////////////////////////////////////////////////////////////////
//future 支持get,wait,wait_for,wait_until
	//get/wait强制启动，并等待结束
	//wait_*返回值：
		//std::future_status::deferred 尚未启动
		//std::future_status::ready 已完成
		//std::future_status::timeout 启动未完成
	//相当于get

//asyn 主线程获取子线程的返回值
//async 策略：
	//std::launch::async 异步启动,此模式下不调用get/wait也可在future作用域结束时，程序会阻塞等待后台任务结束
	//std::launch::deferred 延迟启动
	//默认参数:async|deferred


int doSomething(char c)
{
	std::default_random_engine dre(c);
	std::uniform_int_distribution<int> id(10, 1000);

	for (int i = 0; i<10; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(id(dre)));
		std::cout.put(c).flush();
	}

	return c;
}

void test_asyn1()
{
	std::future<int> ret1(std::async(doSomething,'.'));

	int ret2 = doSomething('-');

	int ret = ret1.get() + ret2;
	
	std::cout << endl;
	std::cout << "ret = " << ret << endl;
}

void test_asyn2() 
{
	int ret, ret1, ret2;

	auto f1 = std::async([]() {
		return doSomething('.');
	});

	auto f2 = std::async([]() {
		return doSomething('-');
	});

	if (std::future_status::deferred != f1.wait_for(std::chrono::seconds(0)) 
		|| std::future_status::deferred != f2.wait_for(std::chrono::seconds(0)))
	{
		while (std::future_status::ready != f1.wait_for(std::chrono::seconds(0))
			&& std::future_status::ready != f2.wait_for(std::chrono::seconds(0)))
		{
			//do something else;
			std::this_thread::yield();
		}
	}

	cout.put('\n').flush();

	try
	{
		ret1 = f1.get();
		ret2 = f2.get();
		ret = ret1 + ret2;
	}
	catch (const std::exception& e)
	{
		std::cout << "\n exception: " << e.what() << std::endl;
	}

	std::cout << "ret = " << ret << std::endl;
}
/////////////////////////////////////////////////////////////////////
//promise 相当于set

/////////////////////////////////////////////////////////////////////
//task_package 相当于asyn(std::lauch::defered)
void test_packaged_task() 
{
	std::packaged_task<int(char)> task(doSomething);
	std::future<int> f1 = task.get_future();

	//do something else
	task('*');
	//do something else

	int ret = f1.get();
	std::cout.put('\n').flush();
	std::cout << "ret = " << ret << std::endl;
}


/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {
	//test_thread();
	//test_mutex();
	//test_callonce();
	//test_cv();
	//test_static_func();

	//test_asyn1();
	//test_asyn2();
	test_packaged_task();
	return 0;
}

