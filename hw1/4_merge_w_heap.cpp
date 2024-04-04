/**
 * 4.1 Слияние массивов.
 * Напишите программу, которая использует кучу для слияния K отсортированных массивов суммарной длиной N.
 * Требования: время работы O(N * logK). Ограничение на размер кучи O(K)..
 * Формат входных данных: Сначала вводится количество массивов K. Затем по очереди 
 * размер каждого массива и элементы массива. Каждый массив упорядочен по возрастанию.
 * Формат выходных данных: Итоговый отсортированный массив.
 */

#include <iostream>
#include <cstdint>
#include <sstream>

#include "Algorythms_and_Structures/Heap.hpp"
#include "Algorythms_and_Structures/Vector.hpp"

template< typename T >
struct Less
{
    bool operator()( const T & a, const T & b )
    {
        return a < b;
    }
};

template< typename T >
struct VectorIterator
{
    typename Vector< T >::Iterator curr;
    typename Vector< T >::Iterator end;

    VectorIterator()
    :   curr(),
        end()
    {}

    VectorIterator( const Vector< T > & vec )
    :   curr( vec.Begin() ),
        end( vec.End() )
    {}
};

template< typename T, typename Comparator >
struct VectorIteratorComparator
{
    Comparator comp;

    bool operator()( const VectorIterator< T > & a, const VectorIterator< T > & b )
    {
        return comp( *a.curr, *b.curr );
    }
};

template< typename T, typename Comparator = Less< T > >
Vector< T > MergeVectors( const Vector< Vector< T > > & arrays )
{
    Vector< VectorIterator< T > > iterator_arrays( arrays.Size() );
    for( size_t i = 0; i < arrays.Size(); ++i )
    {
        iterator_arrays[i] = VectorIterator{ arrays[i] };
    }
    Heap< VectorIterator< T >, VectorIteratorComparator< T, Comparator > > heap( iterator_arrays );
    Vector< T > result;
    while( !heap.IsEmpty() )
    {
        auto extracted = heap.Extract();
        if( extracted.curr == extracted.end )
            continue;
        
        result.PushBack( *extracted.curr );
        ++extracted.curr;
        if( extracted.curr != extracted.end )
            heap.Insert( extracted );
    }
    return result;
}

void Run( std::istream & is, std::ostream & os )
{
    size_t k = 0;
    is >> k;
    Vector< Vector< int32_t > > arrays( k );
    for ( size_t i = 0; i < k; ++i )
    {
        size_t n = 0;
        is >> n;
        Vector< int32_t > arr( n );
        for ( size_t j = 0; j < n; ++j )
        {
            is >> arr[j];
        }
        arrays[i] = arr;

    }
    os << MergeVectors< int32_t >( arrays );
}

void TestLogic()
{
    {
        std::stringstream iss, oss;
        iss << "3\
                3\
                2 4 6\
                2\
                50 90\
                3\
                1 10 70";
        Run(iss, oss);
        std::cout << oss.str();
        assert( oss.str() == "1 2 4 6 10 50 70 90\n");
    }
    {
        std::stringstream iss, oss;
        iss << "7\
                    4\
                5 16 19 20\
                    1\
                7\
                    3\
                2 8 17\
                    4\
                1 13 15 18\
                    2\
                9 10\
                    2\
                4 12\
                    4\
                3 6 11 14";
        Run(iss, oss);
        std::cout << oss.str();
        assert( oss.str() == "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20\n");
    }
}

int main()
{
    TestLogic();
    // Run( std::cin, std::cout );
    return 0;
}
