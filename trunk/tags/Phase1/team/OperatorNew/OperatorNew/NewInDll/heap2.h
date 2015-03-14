
#ifdef NEWINDLL_EXPORTS
#define NEWINDLL_API __declspec(dllexport)
#else
#define NEWINDLL_API __declspec(dllimport)
#endif

class NEWINDLL_API Heap2
{
public:

    static int* p;

    static int* GetMemory()
    {
        return p;
    }
};
