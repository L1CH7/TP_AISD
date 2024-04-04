/**
 * Дано множество целых чисел из [0..10^9] размера n. 
 * Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
 * - 10%  перцентиль
 * - медиана
 * - 90%  перцентиль
 * 
 * Требования: к дополнительной памяти: O(n). 
 * Среднее время работы: O(n)
 * Должна быть отдельно выделенная функция partition. 
 * Рекурсия запрещена. 
 * Решение должно поддерживать передачу функции сравнения снаружи.
 * 
 * 
 * Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении. 
 * Описание для случая прохода от начала массива к концу:
 * - Выбирается опорный элемент. Опорный элемент меняется с последним элементом массива.
 * - Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного. 
 *   Затем располагаются элементы, строго бОльшие опорного. 
 *   В конце массива лежат нерассмотренные элементы. 
 *   Последним элементом лежит опорный.
 * - Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
 * - Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
 * - Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j.
 * - Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
 * - В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.
 *
 * 6.4 Реализуйте стратегию выбора опорного элемента “случайный элемент”. 
 * Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
 * 
 */

#include "Algorythms_and_Structures/Vector.hpp"
#include <iostream>
#include <random>

template< typename T >
struct Less
{
    bool operator()( const T & a, const T & b )
    {
        return a < b;
    }
};

template< typename T, typename Comparator >
size_t Partition(Vector< T > & v, size_t l, size_t r ) // right not included
{
    Comparator comp;
    static std::mt19937_64 gen( std::random_device{}() );
    size_t pivot_idx = std::uniform_int_distribution{ l, r - 1 }( gen );
    T pivot = v[pivot_idx];
    std::swap( v[l], v[pivot_idx] );
    size_t i = r - 1;
    for( size_t j = i; j >= l; --j)
    {
        if( comp( pivot, v[j] ) )
        {
            std::swap( v[i], v[j] );
            --i;
        }
    }
    std::swap( v[l], v[i] );
    return i;
}

template< typename T, typename Comparator = Less< T > >
T KthElement(Vector< T > & v, size_t k )
{
    assert( k < v.Size() );
    size_t  l = 0,
            r = v.Size();
    while( l < r )
    {
        size_t pos = Partition< T, Comparator >( v, l, r );
        if( k == pos )
        {
            return v[pos];
        }
        else if( k > pos )
        {
            l = pos + 1;
        }
        else
        {
            r = pos;
        }
    }
    return v[k];
}

void Run( std::istream & is, std::ostream & os )
{
    size_t n = 0;
    is >> n;
    Vector< int32_t > v( n );
    for( size_t i = 0; i < n; ++i )
    {
        is >> v[i];
    }
    double percentils[] = { .1, .5, .9 };
    for( auto p : percentils )
    {
        os << KthElement( v, static_cast< size_t >( v.Size() * p ) ) << '\n';
    }
}

int main()
{
    Run( std::cin, std::cout );
    return 0;
}