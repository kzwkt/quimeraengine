// BoostThread.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <boost/thread.hpp>

using std::cout;
using std::endl;
using std::dec;
using boost::thread;

class Worker 
{
public:
	Worker () {}

	void operator() ()
	{
	// Tareas a realizar por la funci¨®n
		cout << "thread id=" << boost::this_thread::get_id();
		cout << " ejecutando thread desde el functor" << endl;
	}
	void llamada() 
	{
	// Tareas a realizar por la funci¨®n
		cout << "thread id=" << boost::this_thread::get_id();
		cout << " ejecutando thread desde el metodo objeto" << endl;
	}
};

void funcion_sin_arg ()
{
	cout << "thread id=" << boost::this_thread::get_id();
	cout << " ejecutando thread desde la funcion sin parametro" << endl;
}

void funcion_con_arg (int n)
{
	cout << "thread id=" << boost::this_thread::get_id();
	cout << " ejecutando thread desde la funcion con parametro " << n << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Worker w, w1;

	// Creando thread
	thread workerThread (w);
	thread workerThread2 (&Worker::llamada, &w1);
	thread threadFunc1 (funcion_sin_arg);
	thread threadFunc2 (funcion_con_arg, 1);

	// Esperamos que termine los threads
	workerThread.join();
	workerThread2.join();
	threadFunc1.join();
	threadFunc2.join();

	return 0;
}
