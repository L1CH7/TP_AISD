#include "Heap.hpp"
#include "Vector.hpp"

#include <iostream>
#include <sstream>
#include <vector>


// template< typename T>
// class std::vector< T >
// {
//     std::vector< T >( const Vector < T > & v )
//     : std::vector< T >( v.Size() )
//     {
//         for( size_t i = 0; i <= v.Size(); ++v )
//             at( i ) = v[i];
//     }
// };

template< typename T >
std::ostream & operator<<( std::ostream & os, const std::vector< T > & obj )
{
    for( size_t i = 0; i < obj.size(); ++i )
    {
        os << obj[i] << ( ( i == obj.size() - 1 ) ? '\n' : ' ' );
    }
    return os;
}

template< typename T>
std::vector< T > ConvertVectors( const Vector< T > & v )
{
    std::vector< T > _v( v.Size(), 0 );
    for( size_t i = 0; i < v.Size(); ++i )
        _v[i] = v[i];
    return _v;
}

template< typename T>
struct LessComparator
{
    bool operator()( const T & a, const T & b )
    {
        return a < b;
    }
};

void TestHeap()
{
    std::cout << "---------Test Heap Behin---------\n";
    typedef Heap< int32_t, LessComparator< int32_t > > MinHeap;
    {
        Vector< int32_t > v;
        v.PushBack( 5 );
        v.PushBack( 50 );
        v.PushBack( 2 );
        v.PushBack( 4 );
        v.PushBack( 15 );
        v.PushBack( 1 );
        v.PushBack( 16 );
        v.PushBack( 6 );
        v.PushBack( 3 );
        v.PushBack( 20 );
        MinHeap h( v );
        std::stringstream ss1;
        std::stringstream ss2;
        while( !h.IsEmpty() )
        {
            ss1 << h.ExtractMin() << ( h.IsEmpty() ? '\n' : ' ' );
        }
        std::vector< int32_t > _v = ConvertVectors( v );
        std::sort( _v.begin(), _v.end() );
        ss2 << _v;
        std::cout << ss1.str() << ss2.str();
        assert( ss1.str() == ss2.str() );
    }
    std::cout << "---------Test Heap End---------\n";
}

int main()
{
    TestHeap();
    return 0;
}