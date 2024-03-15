#include <iostream>
#include "ImmerBench.hpp"
#include "AbseilFlatHashMapBench.hpp"
#include "UnorderedMapBench.hpp"

int main()
{
    ImmerBench{}.run();
    AbseilFlatHashMapBench{}.run();
    UnorderedMapBench{}.run();
    return 0;
}