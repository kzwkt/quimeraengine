//#define _SECURE_SCL 0
//#define _SECURE_SCL_THROWS 0
//#define _HAS_ITERATOR_DEBUGGING 0

#include <windows.h>
#include <boost/random.hpp>
#include <iostream>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <vector>
#include <time.h>
#include <map>
#include <string>
#include <deque>
#include <fstream>

#define MULTIP_DEQ_IT 100
#define MULTIP_DEQ_SZ 10
#define MULTIP_MAP_IT 2000
#define MULTIP_MAP_SZ 2500
#define MULTIP_STR_IT 200
#define MULTIP_STR_SZ 20000
#define MULTIP_VEC_IT 200
#define MULTIP_VEC_SZ 50

#define MAXITER 1

std::ofstream g_outfile;

void ModeCheck()
{
#ifdef _DEBUG
        g_outfile <<"Debug" << std::endl;
#else
        g_outfile <<"Release" << std::endl;
#endif

#ifdef STLPORT
        g_outfile <<"Using STL_PORT" << std::endl;
#else
        g_outfile <<"Using VS2008 STL" <<std::endl;
        g_outfile <<"Secure SCL " <<_SECURE_SCL << std::endl;
        g_outfile <<"Secure SCL Throw " <<_SECURE_SCL_THROWS << std::endl;
        g_outfile <<"Has Iterator Debugging " <<_HAS_ITERATOR_DEBUGGING << std::endl;
        //g_outfile <<"SCL Secure No Warnings " <<_SCL_SECURE_NO_WARNINGS<< std::endl;
#endif
}

typedef boost::function<void (unsigned int, unsigned int)> TestFunction_t;

void TimeFunction(const TestFunction_t &f, 
                                  unsigned int iteration, unsigned int containerSize)
{
        __int64 ctr1 = 0, ctr2 = 0, freq = 0;
        QueryPerformanceCounter((LARGE_INTEGER *)&ctr1);

        f(iteration, containerSize);

        QueryPerformanceCounter((LARGE_INTEGER *)&ctr2);
        QueryPerformanceFrequency((LARGE_INTEGER *)&freq);

        g_outfile
                << iteration <<","
                << containerSize <<","
                << (ctr2 - ctr1) * 1.0 / freq 
                << std::endl;
}

void StressTestVector(unsigned int iteration, unsigned int size)
{
        for(unsigned int i=0; i<iteration; ++i)
        {
                std::vector<int> v;

                v.reserve(size);
                // push back test without reserve
                for(unsigned int i=0; i<size; ++i)
                {
                        v.push_back(0);
                }

                // iterator test by going through all element
                std::vector<int>::iterator itr = v.begin();
                while(v.end() != itr)
                {
                        (*itr)++;
                        ++itr;
                }

                // copy test
                std::vector<int> clone = v;
        }
}

void StressTestMap(unsigned int iteration, unsigned int size)
{
        boost::uniform_int<unsigned int> unif(0,0xFFFFFFFF);

        //! we are using the mt19937 uniform distribution engine
        boost::mt19937 unifEng;
        unifEng.seed((unsigned int)time(NULL));
        
        std::map<unsigned int, unsigned int> m;

        // insert random numbers in the map
        for(unsigned int elementIndex = 0; elementIndex<size; ++elementIndex)
        {
                unsigned int randomInt = unif(unifEng);
                m.insert(std::make_pair(randomInt, randomInt));
        }

        // force the map to find certain number, and erase them
        for(unsigned iterationIndex = 0; iterationIndex<iteration; ++iterationIndex)
        {
                unsigned int randomInt = unif(unifEng);
                std::map<unsigned int, unsigned int>::iterator itr = m.find(randomInt);

                if(itr != m.end())
                {
                        m.erase(itr);
                }
        }
}

void StressTestDeque(unsigned int iteration, unsigned int size)
{
        boost::uniform_int<unsigned int> unif(0,size);

        //! we are using the mt19937 uniform distribution engine
        boost::mt19937 unifEng;
        unifEng.seed((unsigned int)time(NULL));

        std::deque<unsigned int> m;

        // insert random numbers in the map
        for(unsigned int elementIndex = 0; elementIndex<size; ++elementIndex)
        {
                unsigned int randomInt = unif(unifEng);

                if(randomInt % 2 == 0)
                {
                        m.push_front(randomInt);
                }
                else
                {
                        m.push_back(randomInt);
                }
                std::make_heap(m.begin(), m.end());
        }

        // force the map to find certain number, and erase them
        for(unsigned iterationIndex = 0; iterationIndex<iteration; ++iterationIndex)
        {
                unsigned int randomInt = unif(unifEng);

                m.push_back(randomInt);
                std::push_heap(m.begin(), m.end());

                std::pop_heap(m.begin(), m.end());
                m.pop_back();
        }
}

void StressTestString(unsigned int iteration, unsigned int size)
{
        boost::uniform_int<unsigned int> unif(0x61,0x7A);

        //! we are using the mt19937 uniform distribution engine
        boost::mt19937 unifEng;
        unifEng.seed((unsigned int)time(NULL));

        std::string s;

        // insert random numbers in the map
        for(unsigned int elementIndex = 0; elementIndex<size; ++elementIndex)
        {
                unsigned int randomInt = unif(unifEng);
                s += static_cast<char>(randomInt);
        }

        // force the map to find certain number, and erase them
        for(unsigned iterationIndex = 0; iterationIndex<iteration; ++iterationIndex)
        {
                std::string cloneS = s;

                s.find("abcdefghi");
                s.find("jklmnopq");
                s.find("rstuvwxyz");

                std::string concat = s + s;
        }
}

void IterationTestVector()
{
        g_outfile <<std::endl <<__FUNCTION__ << std::endl;

        TimeFunction(
                boost::bind(StressTestVector, _1, _2), 
                10*MULTIP_VEC_IT,10);
        
        TimeFunction(
                boost::bind(StressTestVector, _1, _2), 
                20*MULTIP_VEC_IT,10);
        
        TimeFunction(
                boost::bind(StressTestVector, _1, _2), 
                40*MULTIP_VEC_IT,10);

        TimeFunction(
                boost::bind(StressTestVector, _1, _2), 
                80*MULTIP_VEC_IT,10);

        TimeFunction(
                boost::bind(StressTestVector, _1, _2), 
                160*MULTIP_VEC_IT,10);

        TimeFunction(
                boost::bind(StressTestVector, _1, _2), 
                320*MULTIP_VEC_IT,10);

        TimeFunction(
                boost::bind(StressTestVector, _1, _2), 
                640*MULTIP_VEC_IT,10);

        TimeFunction(
                boost::bind(StressTestVector, _1, _2), 
                1280*MULTIP_VEC_IT,10);

        TimeFunction(
                boost::bind(StressTestVector, _1, _2), 
                2560*MULTIP_VEC_IT,10);

        TimeFunction(
                boost::bind(StressTestVector, _1, _2), 
                5120*MULTIP_VEC_IT,10);
}

void SizeTestVector()
{
        g_outfile <<std::endl <<__FUNCTION__ << std::endl;

        TimeFunction(
                boost::bind(StressTestVector, _1, _2), 
                10*MULTIP_VEC_SZ,100);

        TimeFunction(
                boost::bind(StressTestVector, _1, _2), 
                10*MULTIP_VEC_SZ,200);

        TimeFunction(
                boost::bind(StressTestVector, _1, _2), 
                10*MULTIP_VEC_SZ,400);

        TimeFunction(
                boost::bind(StressTestVector, _1, _2), 
                10*MULTIP_VEC_SZ,800);

        TimeFunction(
                boost::bind(StressTestVector, _1, _2), 
                10*MULTIP_VEC_SZ,1600);

        TimeFunction(
                boost::bind(StressTestVector, _1, _2), 
                10*MULTIP_VEC_SZ,3200);

        TimeFunction(
                boost::bind(StressTestVector, _1, _2), 
                10*MULTIP_VEC_SZ,6400);

        TimeFunction(
                boost::bind(StressTestVector, _1, _2), 
                10*MULTIP_VEC_SZ,12800);

        TimeFunction(
                boost::bind(StressTestVector, _1, _2), 
                10*MULTIP_VEC_SZ,25600);

        TimeFunction(
                boost::bind(StressTestVector, _1, _2), 
                10*MULTIP_VEC_SZ,51200);
}
void IterationTestMap()
{
        g_outfile <<std::endl <<__FUNCTION__ << std::endl;

        TimeFunction(
                boost::bind(StressTestMap, _1, _2), 
                10*MULTIP_MAP_IT,100);

        TimeFunction(
                boost::bind(StressTestMap, _1, _2), 
                20*MULTIP_MAP_IT,100);

        TimeFunction(
                boost::bind(StressTestMap, _1, _2), 
                40*MULTIP_MAP_IT,100);

        TimeFunction(
                boost::bind(StressTestMap, _1, _2), 
                80*MULTIP_MAP_IT,100);

        TimeFunction(
                boost::bind(StressTestMap, _1, _2), 
                160*MULTIP_MAP_IT,100);

        TimeFunction(
                boost::bind(StressTestMap, _1, _2), 
                320*MULTIP_MAP_IT,100);

        TimeFunction(
                boost::bind(StressTestMap, _1, _2), 
                640*MULTIP_MAP_IT,100);

        TimeFunction(
                boost::bind(StressTestMap, _1, _2), 
                1280*MULTIP_MAP_IT,100);

        TimeFunction(
                boost::bind(StressTestMap, _1, _2), 
                2560*MULTIP_MAP_IT,100);

        TimeFunction(
                boost::bind(StressTestMap, _1, _2), 
                5120*MULTIP_MAP_IT,100);
}

void SizeTestMap()
{
        g_outfile <<std::endl <<__FUNCTION__ << std::endl;

        TimeFunction(
                boost::bind(StressTestMap, _1, _2), 
                1000*MULTIP_MAP_SZ,10);

        TimeFunction(
                boost::bind(StressTestMap, _1, _2), 
                1000*MULTIP_MAP_SZ,50);

        TimeFunction(
                boost::bind(StressTestMap, _1, _2), 
                1000*MULTIP_MAP_SZ,100);

        TimeFunction(
                boost::bind(StressTestMap, _1, _2), 
                1000*MULTIP_MAP_SZ,200);

        TimeFunction(
                boost::bind(StressTestMap, _1, _2), 
                1000*MULTIP_MAP_SZ,400);

        TimeFunction(
                boost::bind(StressTestMap, _1, _2), 
                1000*MULTIP_MAP_SZ,800);

        TimeFunction(
                boost::bind(StressTestMap, _1, _2), 
                1000*MULTIP_MAP_SZ,1600);

        TimeFunction(
                boost::bind(StressTestMap, _1, _2), 
                1000*MULTIP_MAP_SZ,3200);

        TimeFunction(
                boost::bind(StressTestMap, _1, _2), 
                1000*MULTIP_MAP_SZ,6400);

        TimeFunction(
                boost::bind(StressTestMap, _1, _2), 
                1000*MULTIP_MAP_SZ,12800);
}

void IterationTestString()
{
        g_outfile <<std::endl <<__FUNCTION__ << std::endl;

        TimeFunction(
                boost::bind(StressTestString, _1, _2), 
                10*MULTIP_STR_IT,140);

        TimeFunction(
                boost::bind(StressTestString, _1, _2), 
                20*MULTIP_STR_IT,140);

        TimeFunction(
                boost::bind(StressTestString, _1, _2), 
                40*MULTIP_STR_IT,140);

        TimeFunction(
                boost::bind(StressTestString, _1, _2), 
                80*MULTIP_STR_IT,140);

        TimeFunction(
                boost::bind(StressTestString, _1, _2), 
                160*MULTIP_STR_IT,140);

        TimeFunction(
                boost::bind(StressTestString, _1, _2), 
                320*MULTIP_STR_IT,140);

        TimeFunction(
                boost::bind(StressTestString, _1, _2), 
                640*MULTIP_STR_IT,140);

        TimeFunction(
                boost::bind(StressTestString, _1, _2), 
                1280*MULTIP_STR_IT,140);

        TimeFunction(
                boost::bind(StressTestString, _1, _2), 
                2560*MULTIP_STR_IT,140);

        TimeFunction(
                boost::bind(StressTestString, _1, _2), 
                5120*MULTIP_STR_IT,140);
}

void SizeTestString()
{
        g_outfile <<std::endl <<__FUNCTION__ << std::endl;

        TimeFunction(
                boost::bind(StressTestString, _1, _2), 
                10*MULTIP_STR_SZ,10);

        TimeFunction(
                boost::bind(StressTestString, _1, _2), 
                10*MULTIP_STR_SZ,50);

        TimeFunction(
                boost::bind(StressTestString, _1, _2), 
                10*MULTIP_STR_SZ,100);

        TimeFunction(
                boost::bind(StressTestString, _1, _2), 
                10*MULTIP_STR_SZ,200);

        TimeFunction(
                boost::bind(StressTestString, _1, _2), 
                10*MULTIP_STR_SZ,400);

        TimeFunction(
                boost::bind(StressTestString, _1, _2), 
                10*MULTIP_STR_SZ,800);

        TimeFunction(
                boost::bind(StressTestString, _1, _2), 
                10*MULTIP_STR_SZ,1600);

        TimeFunction(
                boost::bind(StressTestString, _1, _2), 
                10*MULTIP_STR_SZ,3200);

        TimeFunction(
                boost::bind(StressTestString, _1, _2), 
                10*MULTIP_STR_SZ,6400);

        TimeFunction(
                boost::bind(StressTestString, _1, _2), 
                10*MULTIP_STR_SZ,12800);
}

void IterationTestDeque()
{
        g_outfile <<std::endl <<__FUNCTION__ << std::endl;

        TimeFunction(
                boost::bind(StressTestDeque, _1, _2), 
                10*MULTIP_DEQ_IT,100);

        TimeFunction(
                boost::bind(StressTestDeque, _1, _2), 
                20*MULTIP_DEQ_IT,100);

        TimeFunction(
                boost::bind(StressTestDeque, _1, _2), 
                40*MULTIP_DEQ_IT,100);

        TimeFunction(
                boost::bind(StressTestDeque, _1, _2), 
                80*MULTIP_DEQ_IT,100);

        TimeFunction(
                boost::bind(StressTestDeque, _1, _2), 
                160*MULTIP_DEQ_IT,100);

        TimeFunction(
                boost::bind(StressTestDeque, _1, _2), 
                320*MULTIP_DEQ_IT,100);

        TimeFunction(
                boost::bind(StressTestDeque, _1, _2), 
                640*MULTIP_DEQ_IT,100);

        TimeFunction(
                boost::bind(StressTestDeque, _1, _2), 
                1280*MULTIP_DEQ_IT,100);

        TimeFunction(
                boost::bind(StressTestDeque, _1, _2), 
                2560*MULTIP_DEQ_IT,100);

        TimeFunction(
                boost::bind(StressTestDeque, _1, _2), 
                5120*MULTIP_DEQ_IT,100);
}

void SizeTestDeque()
{
        g_outfile <<std::endl <<__FUNCTION__ << std::endl;

        TimeFunction(
                boost::bind(StressTestDeque, _1, _2), 
                10*MULTIP_DEQ_SZ,10);

        TimeFunction(
                boost::bind(StressTestDeque, _1, _2), 
                10*MULTIP_DEQ_SZ,50);

        TimeFunction(
                boost::bind(StressTestDeque, _1, _2), 
                10*MULTIP_DEQ_SZ,100);

        TimeFunction(
                boost::bind(StressTestDeque, _1, _2), 
                10*MULTIP_DEQ_SZ,200);

        TimeFunction(
                boost::bind(StressTestDeque, _1, _2), 
                10*MULTIP_DEQ_SZ,400);

        TimeFunction(
                boost::bind(StressTestDeque, _1, _2), 
                10*MULTIP_DEQ_SZ,800);

        TimeFunction(
                boost::bind(StressTestDeque, _1, _2), 
                10*MULTIP_DEQ_SZ,1600);

        TimeFunction(
                boost::bind(StressTestDeque, _1, _2), 
                10*MULTIP_DEQ_SZ,3200);

        TimeFunction(
                boost::bind(StressTestDeque, _1, _2), 
                10*MULTIP_DEQ_SZ,6400);

        TimeFunction(
                boost::bind(StressTestDeque, _1, _2), 
                10*MULTIP_DEQ_SZ,12800);
}

int main(int argc, char **argv)
{
        std::string filename;
        
		#ifdef STLPORT
			filename = "TestSTLport.txt";
		#else
            filename = "TestSTL.txt";
		#endif

        g_outfile.open(filename.c_str(), 
                std::ios::out | std::ios::app);

        bool isOpen = g_outfile.is_open();

        ModeCheck();

        for(unsigned int i=0; i<MAXITER; ++i)
        {
                g_outfile << "Iteration "<<i<<std::endl;

				
                IterationTestDeque();
				std::cout << "DEQ IT" << std::endl;
				SizeTestDeque();
				std::cout << "DEQ SZ" << std::endl;

				IterationTestMap();
				std::cout << "MAP IT" << std::endl;
                SizeTestMap();
				std::cout << "MAP SZ" << std::endl;

				IterationTestString();
				std::cout << "STR IT" << std::endl;
                SizeTestString();
				std::cout << "STR SZ" << std::endl;

                IterationTestVector();
				std::cout << "VEC IT" << std::endl;
                SizeTestVector();
				std::cout << "VEC SZ" << std::endl;
        }

        g_outfile.close();

        return 0;
}
