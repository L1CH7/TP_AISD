#include <iostream>
#include <cassert>
#include <cstdint>

template< typename T, typename Comparator = std::less< T > >
void InsertionSort( T * arr, size_t size )
{
    if( size < 2 )
        return;
    size_t i, j;
    T key;
    Comparator comp;
    for( i = 1; i < size; ++i)
    {
        key = arr[i];
        j = i - 1;
        while( j >= 0 && comp( key, arr[j] ) )
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

struct Box
{
    size_t id, x, y, z; // keep sorted

    Box()
    : id( 0 ), x( 0 ), y( 0 ), z( 0 )
    {}

    Box( size_t _id, size_t _x, size_t _y, size_t _z )
    : id( _id ), x( _x ), y( _y ), z( _z )
    {
        Reconstruct();
    }

    void Reconstruct()
    {
        size_t _x = x, _y = y, _z = z;
        x = std::min( _x, std::min( _y, _z ) );
        z = std::max( _x, std::max( _y, _z ) );
        y = _x + _y + _z - x - z;
    }

    bool operator<( const Box & other ) const
    {
        return  x < other.x && 
                y < other.y &&
                z < other.z;
    }
};

void Run( std::istream & is, std::ostream & os )
{
    size_t n = 0;
    is >> n;
    Box * arr = new Box[n];
    for( size_t i = 0; i < n; ++i )
    {
        arr[i].id = i;
        is >> arr[i].x >> arr[i].y >> arr[i].z;
        arr[i].Reconstruct();
    }
    InsertionSort( arr, n );
    for( size_t i = 0; i < n; ++i )
    {
        os << arr[i].id << ( i == n - 1 ? '\n' : ' ');
    }
    delete[] arr;
}

#include <sstream>
void Test()
{
    {
        std::stringstream iss, oss;
        iss << "3\
                2 3 5\
                1 1 1\
                10 4 10";
        Run( iss, oss );
        std::cout << oss.str();
        assert( oss.str() == "1 0 2\n" );
    }
}

int main()
{
    // Run( std::cin, std::cout );
    Test();
    return 0;
}
