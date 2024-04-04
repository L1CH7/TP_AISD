#include "Vector.hpp"


#include <sstream>

void TestVector()
{
    std::cout << "---------Test Vector Begin---------\n";
    {
        {
            std::cout << "TEST 1: fill c-tor\n";
            Vector< int32_t > v( 5, 1 );
            std::stringstream ss;
            ss << v;
            assert( ss.str() == "1 1 1 1 1\n" );
            std::cout << "PASSED\n";
        }
        {
            std::cout << "TEST 2: copy c-tor\n";
            Vector< int32_t > v1;
            v1.PushBack( 1 );
            v1.PushBack( 2 );
            v1.PushBack( 3 );
            Vector< int32_t > v2( v1 );
            std::stringstream ss1, ss2;
            ss1 << v1;
            ss2 << v2;
            assert( ss1.str() == ss2.str() && ss1.str() == "1 2 3\n" );
            std::cout << "PASSED\n";
        }
        {
            std::cout << "TEST 3: copy assignment\n";
            Vector< int32_t > v1;
            v1.PushBack( 1 );
            v1.PushBack( 2 );
            v1.PushBack( 3 );
            Vector< int32_t > v2;
            v2.PushBack( 4 );
            assert( v2[0] == 4 );
            v2 = v1;
            std::stringstream ss1, ss2;
            ss1 << v1;
            ss2 << v2;
            assert( ss1.str() == ss2.str() && ss1.str() == "1 2 3\n" );
            std::cout << "PASSED\n";
        }
        {
            std::cout << "TEST 4: move c-tor\n";
            Vector< int32_t > v1;
            v1.PushBack( 1 );
            v1.PushBack( 2 );
            v1.PushBack( 3 );
            Vector< int32_t > v2( std::move( v1 ) );
            std::stringstream ss1, ss2;
            ss1 << v1;
            ss2 << v2;
            assert( ss1.str() == "" && ss2.str() == "1 2 3\n" );
            std::cout << "PASSED\n";
        }
        {
            std::cout << "TEST 5: move assignment\n";
            Vector< int32_t > v1;
            v1.PushBack( 1 );
            v1.PushBack( 2 );
            v1.PushBack( 3 );
            Vector< int32_t > v2;
            v2 = std::move( v1 );
            std::stringstream ss1, ss2;
            ss1 << v1;
            ss2 << v2;
            assert( ss1.str() == "" && ss2.str() == "1 2 3\n" );
            std::cout << "PASSED\n";
        }
    }
    std::cout << "---------Test Vector End---------\n";

}

void TestIterator()
{
    {
        Vector< int > v( 5, 1 );
        for( auto it = v.Begin(); it != v.End(); it++ )
        {
            std::cout << *it << ' ';
        }
        std::cout << '\n';
    }
    {
        Vector< int > v( 5, 2 );
        for( auto it = v.Begin(); it != v.End(); ++it )
        {
            std::cout << *it << ' ';
        }
        std::cout << '\n';
    }
    // {
    //     Vector< int > v( 5, 3 );
    //     for( auto it = v.End(); it != v.Begin(); it-- )
    //     {
    //         std::cout << *it << ' ';
    //     }
    //     std::cout << '\n';
    // }
    // {
    //     Vector< int > v( 5, 4 );
    //     for( auto it = v.End(); it != v.Begin(); --it )
    //     {
    //         std::cout << *it << ' ';
    //     }
    //     std::cout << '\n';
    // }
}

int main()
{
    TestVector();
    TestIterator();
    return 0;
}