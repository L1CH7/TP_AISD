/**
 * Требование для всех вариантов Задачи 5
 * Во всех задачах данного раздела необходимо реализовать
 * и использовать сортировку слиянием в виде шаблонной функции. 
 * Решение должно поддерживать передачу функции сравнения снаружи.
 * Общее время работы алгоритма O(n log n).
 * 
 * 5_4. Закраска прямой 2.
 * На числовой прямой окрасили N отрезков. 
 * Известны координаты левого и правого концов каждого отрезка (Li и Ri). 
 * Найти сумму длин частей числовой прямой, окрашенных ровно в один слой.
 */

#include "Algorythms_and_Structures/Vector.hpp"

#include <iostream>

template< typename T >
using Iterator = typename Vector< T >::Iterator;

template< typename T >
struct Less
{
    bool operator()( const T & a, const T & b )
    {
        return a < b;
    }
};

template< typename T, typename Comparator >
Vector< T > Merge( Iterator< T > begin_a, Iterator< T > end_a,
                   Iterator< T > begin_b, Iterator< T > end_b )
{
    Vector< T > result;
    Comparator comp;
    while( begin_a != end_a && begin_b != end_b )
    {
        if( comp( *begin_a, *begin_b ) )
        {
            result.PushBack( *begin_a );
            ++begin_a;
        }
        else
        {
            result.PushBack( *begin_b );
            ++begin_b;
        }
    }
    while( begin_a != end_a )
    {
        result.PushBack( *begin_a );
        ++begin_a;
    }
    while( begin_b != end_b )
    {
        result.PushBack( *begin_b );
        ++begin_b;
    }
    return result;
}

template< typename T, typename Comparator = Less< T > >
void MergeSort( Iterator< T > begin, Iterator< T > end ) // end isn`t included
{
    if( end - begin < 2 ) // if size = 1
        return;
    
    size_t mid = ( end - begin ) / 2;
    MergeSort< T, Comparator >( begin, begin + mid );
    MergeSort< T, Comparator >( begin + mid, end );
    Vector< T > temp;
    temp = Merge< T, Comparator >( begin, begin + mid, begin + mid, end );

    auto src_it = begin;
    auto temp_it = temp.Begin();
    while( temp_it != temp.End() )
    {
        *src_it++ = std::move( *temp_it++ );
    }
}

int32_t CountOfPaintedOnce( Vector< int32_t > & from, Vector< int32_t > & to )
{
    assert( from.Size() == to.Size() && &from != &to );
    MergeSort< int32_t >( from.Begin(), from.End() );
    MergeSort< int32_t >( to.Begin(), to.End() );
    int32_t overlay = 0, 
            count   = 0, 
            root    = from.Front();
    auto f = from.Begin();
    auto t = to.Begin();
    bool iterator_to_flag = false;
    while( f != from.End() || t != to.End() )
    {
        iterator_to_flag = t != to.End() && (f == from.End() || *t < *f); // true if we get end of interval (pos from to[])
        if( overlay == 1 )
        {
            count += ( iterator_to_flag ? *t : *f ) - root;
        }

        if( !iterator_to_flag )
        {
            root = *f;
            ++f;
            ++overlay;
        }
        else
        {
            root = *t;
            ++t;
            --overlay;
        }
    }
    return count;
}




#include <random>
#include <vector>
#include <algorithm>
const size_t RANDOM_TEST_ATTEMPTS = 15;

template< typename T >
std::ostream & operator<<( std::ostream & os, const std::vector< T > & obj )
{
    for( size_t i = 0; i < obj.size(); ++i )
    {
        os << obj[i] << ( ( i == obj.size() - 1 ) ? '\n' : ' ' );
    }
    return os;
}

void TestRandom()
{
    static std::mt19937 gen( std::random_device{}() );
    std::cout << "---------Test Random Begin---------\n";
    auto ri = std::uniform_int_distribution< int32_t >{ -100, 100 };
    for( size_t i = 0; i < RANDOM_TEST_ATTEMPTS; ++i )
    {
        std::cout << "Random Test #" << i + 1 << ":";
        const size_t n = std::uniform_int_distribution< size_t >{ 5, 10000 }( gen );
        std::cout << " \tn=" << n << "\n";
        std::vector< int32_t > stdvec( n );
        Vector< int32_t > myvec( n );
        for( size_t j = 0; j < n; ++j )
        {
            stdvec[j] = myvec[j] = ri( gen );
        }
        std::sort( stdvec.begin(), stdvec.end() );
        MergeSort< int32_t, std::less< int32_t > >( myvec.Begin(), myvec.End() );
        std::stringstream std_ss, my_ss;
        std_ss << stdvec;
        my_ss << myvec;
        assert( std_ss.str() == my_ss.str() && stdvec.size() == n );
        std::cout << "PASSED\n";
    }
    std::cout << "---------Test Random Passed---------\n";
}

void TestMergeSort()
{
    TestRandom();
    {
        Vector< int32_t > v;
        v.PushBack( 4 );
        v.PushBack( 1 );
        v.PushBack( 7 );
        v.PushBack( 9 );
        v.PushBack( 2 );
        v.PushBack( 5 );
        v.PushBack( 10 );
        v.PushBack( 8 );
        v.PushBack( 3 );
        MergeSort< int32_t >( v.Begin(), v.End() );
        std::stringstream ss1;
        ss1 << v;
        std::cout << v;
        assert( ss1.str() == "1 2 3 4 5 7 8 9 10\n" );
    }
    std::cout << "Merge Sort Test SUCCESS\n";
}

void Run( std::istream & is, std::ostream & os )
{
    size_t n = 0;
    is >> n;
    Vector< int32_t > from( n ), to( n );
    for( size_t i = 0; i < n; ++i )
    {
        is >> from[i] >> to[i];
    }
    os << CountOfPaintedOnce( from, to );
}

#include <sstream>
void TestLogic()
{
    {
        std::stringstream iss, oss;
        iss << "8\
                0 6\
                5 10\
                8 12\
                8 12\
                14 15\
                16 17\
                18 19\
                18 20";
        Run( iss, oss );
        std::cout << oss.str();
        assert( oss.str() == "11" );
    }
    {
        std::stringstream iss, oss;
        iss << "3\
                1 4\
                7 8\
                2 5";
        Run( iss, oss );
        std::cout << oss.str();
        assert( oss.str() == "3" );
    }
}

int main()
{
    // TestMergeSort();
    TestLogic();
    // Run( std::cin, std::cout );
    return 0;
}
