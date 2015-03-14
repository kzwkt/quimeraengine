
#include <vector>
#include <boost/foreach.hpp>
#include <boost/thread.hpp>
#include "InternalDefinitions.h"

class QDllExport Prueba
{
public:

    Prueba()
    {
        std::vector<int> v;
        v.push_back(8);
        v.push_back(9);

        BOOST_FOREACH(int u, v)
        {
            i += u;
        }

        boost::thread thre;
    }

    void func(int x);

    int i;
};
