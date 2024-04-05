#include <iostream>
#include <cassert>
#include <cstdint>
#include <bit>

int BinarySearch( int* arr, size_t n, int target )
{
    
    if( n == 0 )
        return 0;
    size_t left = 0, right = n - 1;
    while( left < right )
    {
        size_t mid = ( right + left ) / 2;
        if( target < arr[mid] ) // target < arr[mid]
            right = mid;
        else if( arr[mid] < target ) // target > arr[mid]
            left = mid + 1;
        else
            return mid;
    }

    return left;
}

void Run( std::istream & in, std::ostream & out )
{
    size_t n = 0;
    in >> n;
    int * arr = new int[n];
    for( size_t i = 0; i < n; ++i )
        in >> arr[i];
    int32_t k = 0;
        in >> k;
    out << BinarySearch( arr, n, k ) << "\n";
    delete[] arr;
}


#include <sstream>

void TestLogic()
{
    std::cout << "---------Test Logic Begin---------\n";
    {
        std::cout << "TEST 1\n";
        std::stringstream out, in( "4\
                                    1 3 5 6\
                                    5");
        Run(in, out);
        std::cout << out.str();
        assert(out.str() == "2\n");
        std::cout << "PASSED\n";
    }
    {
        std::cout << "TEST 2\n";
        std::stringstream out, in( "4\
                                    1 3 5 6\
                                    2");
        Run(in, out);
        std::cout << out.str();
        assert(out.str() == "1\n");
        std::cout << "PASSED\n";
    }
    {
        std::cout << "TEST 2\n";
        std::stringstream out, in( "4\
                                    1 3 5 6\
                                    0");
        Run(in, out);
        std::cout << out.str();
        assert(out.str() == "0\n");
        std::cout << "PASSED\n";
    }
    std::cout << "---------Test Logic Passed---------\n";
}

int main()
{
    TestLogic();
    // Run( std::cin, std::cout );
    return 0;
}
