#include "Memory.h"
#include <iostream>
using namespace std;
Twili::MemoryTracker Twili::g_memoryTracker;


void* operator new(size_t size)
{
    void* p = malloc(size);
    Twili::g_memoryTracker.Add(p,size);
    cout << "allocated: " << size << endl;
    return p;
}

void operator delete(void* address, size_t size)
{
    Twili::g_memoryTracker.Remove(address,size);
    cout << "deallocated: " << size << endl;
    free(address);
}

namespace Twili
{
    void MemoryTracker::Add(void* address, size_t size)
    {
        m_bytesAllocated += size;
        m_numAllocations++;

    }
    void MemoryTracker::Remove(void* address,size_t size)
    {
        m_bytesAllocated -= size;
        m_numAllocations--;
    }

    void MemoryTracker::Display()
    {
        cout << "current bytes allocated: " << m_bytesAllocated << endl;
        cout << "current number of allocations: " << m_numAllocations << endl;
    }

}



