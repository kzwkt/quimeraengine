// BoostThreadMutexCond.cpp : Defines the entry point for the console application.
//
/*

condition.cpp
-------------

Calculates one Fibonacci array in one thread until 100 is reached, then another two threads are notified to include
them into the calculation too.

*/

#include "stdafx.h"
#include <iostream>
#include <boost/thread.hpp>


using std::cout;
using std::endl;
using std::dec;
using boost::thread;
using boost::mutex;
using boost::unique_lock;
using boost::lock_guard;
using boost::condition_variable_any;


namespace
{
	// Fibonacci sequence start values
	long prev1 = 1;
	long prev2 = 1;

	// limit to broadcast other threads
	const int LIMIT = 100;

	// flag for disabling/enabling more threads
	bool one_thread_only;
	// condition flag
	condition_variable_any limit_cond;
	// protects flag
	mutex limit_mutex;
}


/**
callable for calculation from the start
**/
struct call_main
{
public:

	void operator()()
	{
		while (true)
		{
			limit_mutex.lock();
			long n = prev1 + prev2;
			cout << "thread id=" << boost::this_thread::get_id();
			cout << "::call_main::():n=" << dec << n << endl;
			prev1 = prev2;
			prev2 = n;
			
			if (n > LIMIT)
			{
				if (one_thread_only)
				{
					one_thread_only = false;
					limit_cond.notify_all();
				}
			}
			if (n < 0) 
			{
				cout << "thread id=" << boost::this_thread::get_id();
				cout << "::Return::():" << endl;
				return;
			}
			limit_mutex.unlock();
			boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
		}
	}
};


/**
callable for broadcasted threads when the limit is reached
**/
struct call_other
{
	void operator()()
	{
		while (true)
		{
			limit_mutex.lock();
			while (one_thread_only == true)
				limit_cond.wait(limit_mutex);
			
			long n = prev1 + prev2;
			if (n < 0) 
			{
				cout << "thread id=" << boost::this_thread::get_id();
				cout << "::Return::():" << endl;
				return;
			}
			cout << "thread id=" << boost::this_thread::get_id();
			cout << "::call_other::():n=" << dec << n << endl;
			prev1 = prev2;
			prev2 = n;
			limit_mutex.unlock();
			boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
		}
	}
};


int main()
{
	one_thread_only = true;
	
	call_main c1;
	call_other c2; 
	thread t1(c1);
	thread t2(c2);
	thread t3(c2);
	
	t1.join();
	t2.join();
	t3.join();

	return EXIT_SUCCESS;
}

