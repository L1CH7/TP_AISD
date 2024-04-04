/**
 * 7_2. LSD для long long.
 * Дан массив неотрицательных целых 64-битных чисел. 
 * Количество чисел не больше 10^6. 
 * Отсортировать массив методом поразрядной сортировки LSD по байтам.
 * 3
 * 4 1000000 7
 * 4 7 1000000
 * 
 */

#include "Algorythms_and_Structures/Vector.hpp"
#include <iostream>
#include <cassert>
#include <concepts>
#include <functional>

template< typename T >
// void CountSort( Vector< T > & v, size_t alphabet_size, size_t ( *key )( const T & ) )
// using std::function because lambda that captures can not be converted to function ptr
void CountSort( Vector< T > & v, size_t alphabet_size, std::function< size_t( const T & ) > key )
{
    Vector< size_t > counters( alphabet_size, 0 );
    Vector< T > bucket( v.Size() );
    for( auto it = v.Begin(); it != v.End(); ++it )
    {
        ++counters[key( *it )];
    }
    for( size_t i = 1; i != counters.Size(); ++i )
    {
        counters[i] += counters[i - 1];
    }
    for( int64_t i = v.Size() - 1; i >= 0; --i )
    {
        bucket[ --counters[key( v[i] )] ] = v[i];
    }
    v = std::move( bucket );
}

template< typename T >
concept UnsignedIntegral = std::is_integral< T >::value && !std::is_signed< T >::value; 

template< typename T >
    requires UnsignedIntegral< T >
void LsdSort( Vector< T > & v, size_t base = 2 )
{
    Vector< size_t > bucket( base, 0 );
    size_t digit = 1;
    T max_value = T{};
    for( auto it = v.Begin(); it != v.End(); ++it)
    {
        if( *it > max_value )
            max_value = *it;
    }
    // cycle by digits
    while( max_value / digit > 0 )
    {
    	// lambda returns digit on pos [digit] by base [base]
        CountSort< T >( v, base, [ digit, base ]( const T & value ) -> size_t {
            return static_cast< size_t >( value / digit % base );
        });
        digit *= base;
    }
}

void Run( std::istream & is, std::ostream & os )
{
    size_t n = 0;
    is >> n;
    Vector< uint64_t > v( n );
    for( size_t i = 0; i < n; ++i )
    {
        is >> v[i];
    }
	// according to the task, we need to sort by bytes -> base = 8
    LsdSort( v, 8 );
    os << v;    
}

#include <sstream>
void Test()
{
    {
        std::stringstream iss, oss;
        iss << "10\n 9 4 5 1 8 7 3 2 0 6";
        Run( iss, oss );
        std::cout << oss.str();
        assert( oss.str() == "0 1 2 3 4 5 6 7 8 9\n" );
    }
}

int main()
{
    // Run( std::cin, std::cout );
    Test();
    return 0;
}
