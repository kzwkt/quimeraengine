// boostThreadMutex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
	 
	 
using std::cout;
using std::endl;
using std::dec;
using boost::thread;
using boost::mutex;
	 
	 
/**
  calculates Fibonacci array, it is thread safe because 'prev1' and 'prev2' are protected by mutex 'm'
**/
	struct callable
	{
	private:
	 
	    long prev1;
	     
	    long prev2;
	     
	    /**
	    to protect 'prev1' and 'prev2'
	    **/
	    mutex m;
 
	public:
	 
	    callable(long p1, long p2) : prev1(p1), prev2(p2), m()
	    {
	    }
	     
	     
	    void operator()()
	    {
	        while (true)
	        {
	            this->m.lock();
	            long n = this->prev1 + this->prev2;
				if (n < 0) {
					cout << "thread id=" << boost::this_thread::get_id();
					cout << "::RETURN::():" << endl;
					return ;
				}
	            cout << "thread id=" << boost::this_thread::get_id();
	            cout << "::callable::():n=" << dec << n << endl;
	            this->prev1 = this->prev2;
	            this->prev2 = n;
	            this->m.unlock();
	            boost::this_thread::sleep(boost::posix_time::milliseconds(100));
	        }
	    }
	};
	 
	 
	int main()
	{
	    callable c(1, 1);
	 
	    thread t1(boost::ref(c));
	    thread t2(boost::ref(c));
	    thread t3(boost::ref(c));
	    thread t4(boost::ref(c));
	     
	    t1.join();
	    t2.join();
	    t3.join();
	    t4.join();
	 
	    return EXIT_SUCCESS;
	}
