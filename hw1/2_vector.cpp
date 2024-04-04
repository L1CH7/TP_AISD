/**
 * 2.3. Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию. 
 * A[0..n-1] и B[0..m-1]. n >> m. Найдите их пересечение.
 * Требования: Время работы: O(m * log k), где k - позиция элемента B[m-1] в массиве A.
 * В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска элемента B[i-1]. 
 * Внимание! В этой задаче для каждого B[i] сначала нужно определить диапазон для бинарного поиска 
 * размером порядка k с помощью экспоненциального поиска, а потом уже в нем делать бинарный поиск.
 * n, k <= 10000.
 */

#include <iostream>
#include <cassert>
#include <cstdint>
#include <bit>

template< typename T>
struct LessComparator
{
    bool operator()( const T & a, const T & b )
    {
        return a < b;
    }
};

template< typename T >
class Vector
{
public:
    Vector()
    :   size_( 0 ), 
        capacity_( 0 ),
        data_( nullptr )
    {}

    Vector( size_t count, T value = T() )
    :   size_( count ), 
        capacity_( std::bit_ceil( count ) ),
        data_( new T[capacity_ ] )
    {
        for( size_t i = 0; i < size_; ++i )
        {
            data_[i] = value;
        }
    }

    Vector( const Vector & other )
    :   size_( other.size_ ),
        capacity_( other.capacity_ ),
        data_( new T[other.capacity_] )
    {
        for( size_t i = 0; i < other.capacity_; ++i )
            data_[i] = other.data_[i];
    }

    Vector & operator=( const Vector & other )
    {
        if( this == &other )
            return *this;

        if( other.size_ <= capacity_ )
        {
            for( size_t i = 0; i < other.size_; ++i )
            {
                data_[i] = other.data_[i];
            }
            size_ = other.size_;
            return *this;
        }
        
        delete[] data_;

        data_ = new T[other.size_];
        for( size_t i = 0; i < other.size_; ++i )
        {
            data_[i] = other.data_[i];
        }

        size_ = capacity_ = other.size_;
        return *this;

    }

    Vector( Vector && other )
    :   size_( std::move( other.size_ ) ),
        capacity_( std::move( other.capacity_ ) ),
        data_( std::move( other.data_ ) )
    {
        other.size_ = 0;
        other.capacity_ = 0;
        other.data_ = nullptr;
    }

    Vector & operator=( Vector && other )
    {
        delete[] data_;

        data_ = std::move( other.data_ );
        size_ = std::move( other.size_ );
        capacity_ = std::move( other.capacity_ );
        other.size_ = 0;
        other.capacity_ = 0;
        other.data_ = nullptr;
        return *this;
    }

    ~Vector()
    {
        delete[] data_;
    }

    bool IsEmpty() const
    {
        return size_ == 0;
    }

    size_t Size() const
    {
        return size_;
    }

    size_t Capacity() const
    {
        return capacity_;
    }

    T & operator[]( size_t index )
    {
        if( index < 0 || index >= size_ )
            return data_[capacity_ - 1];

        return data_[index];
    }
    
    const T & operator[]( size_t index ) const
    {
        if( index < 0 || index >= size_ )
            return data_[capacity_ - 1];

        return data_[index];
    }

    void Reserve( size_t new_alloc )
    {
        if( new_alloc <= capacity_ )
            return;

        T * new_data = new T[new_alloc];
        for( size_t i = 0; i < size_; ++i )
        {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_alloc;
    }

    void PushBack( const T & value )
    {
        if( capacity_ == 0 )
            Reserve( 8 );

        if( size_ == capacity_ )
            Reserve( 2 * capacity_ );

        data_[size_] = value;
        ++size_;
    }

    T PopBack()
    {
        if( size_ == 0 )
            return T{ -1 };

        --size_;
        return data_[size_];
    }

    const T & Front() const
    {
        return data_[0];
    }
    
    T & Front()
    {
        return data_[0];
    }

    const T & Back() const
    {
        return data_[size_ - 1];
    }

    T & Back()
    {
        return data_[size_ - 1];
    }

private:
    size_t  size_,
            capacity_;
    T * data_;
};


template< typename T >
std::ostream & operator<<( std::ostream & os, const Vector< T > & obj )
{
    for( size_t i = 0; i < obj.Size(); ++i )
    {
        os << obj[i] << ( ( i == obj.Size() - 1 ) ? '\n' : ' ' );
    }
    return os;
}

template< typename T, typename Comparator >
int32_t BinarySearch( const Vector< T > & arr, T target, size_t begin, size_t end )
{
    
    if( end == 0 )
        return 0;
    Comparator comp;
    size_t left = begin, right = end;
    while( left < right )
    {
        size_t mid = left + ( right - left ) / 2;
        if( comp( target, arr[mid] ) ) // target < arr[mid]
            right = mid - 1;
        else if( comp( arr[mid], target ) ) // target > arr[mid]
            left = mid + 1;
        else
            return mid;
    }
    if( !comp( arr[left], target ) && !comp( target, arr[left] ) ) // target == arr[left]
        return left;

    return -1;
}

template< typename T, typename Comparator >
int32_t ExponentialSearch( const Vector< T > & arr, T target, size_t begin = 0, size_t end = 0 )
{
    if( end == 0 )
        end = arr.Size() - 1;
    Comparator comp;
    if( comp( target, arr[begin] ) || comp( arr[end], target ) ) // target < arr[begin] || target > arr[end]
        return -1;

    if( !comp( arr[begin], target ) && !comp( target, arr[begin] ) ) // target == arr[begin]
        return 0;

    size_t idx = begin + 1;
    while( idx <= end && comp( arr[idx], target ) ) // arr[idx] < target < arr[idx * 2]
    {
        if( !comp( arr[idx], target ) && !comp( target, arr[idx] ) ) // target == arr[idx]
            return idx;

        idx <<= 1;
    }
    return BinarySearch< T, Comparator >( arr, target, idx >> 1, std::min( idx, end ) );
}

template< typename T, typename Comparator >
Vector< T > VectorIntersect( const Vector< T > & big_arr, const Vector< T > & small_arr )
{
    size_t buf_idx = 0;
    Vector< T > intersection;
    for( size_t i = 0; i < small_arr.Size(); ++i ) // auto item : small_arr )
    {
        const T & item = small_arr[i];
        int32_t idx = ExponentialSearch< T, Comparator >( big_arr, item, buf_idx );
        if( idx >= 0 )
        {
            intersection.PushBack( item );
            buf_idx = idx + 1;
        }
    }
    return intersection;
}

void Run( std::istream & in, std::ostream & out )
{
    size_t n = 0, m = 0;
    in >> n >> m;
    Vector< int32_t > arr_a( n );
    for( size_t i = 0; i < n; ++i )
        in >> arr_a[i];

    Vector< int32_t > arr_b( m );
    for( size_t i = 0; i < m; ++i )
        in >> arr_b[i];

    out << VectorIntersect< int32_t, LessComparator< int32_t > >( arr_a, arr_b );
}


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

void TestLogic()
{
    std::cout << "---------Test Logic Begin---------\n";
    {
        std::cout << "TEST 1\n";
        std::stringstream out, in( "5\
                                    3\
                                    0 1 2 3 4\
                                    1 2 3");
        Run(in, out);
        // std::cout << out.str();
        assert(out.str() == "1 2 3\n");
        std::cout << "PASSED\n";
    }
    {
        std::cout << "TEST 2\n";
        std::stringstream out, in( "10\
                                    4\
                                    3 4 5 6 7 8 9 10 11 12\
                                    6 8 10 12\
                                    ");
        Run(in, out);
        // std::cout << out.str();
        assert(out.str() == "6 8 10 12\n");
        std::cout << "PASSED\n";
    }
    {
        std::cout << "TEST 3\n";
        std::stringstream out, in( "9\
                                    4\
                                    3 4 5 6 7 8 9 11 12\
                                    6 8 10 12\
                                    ");
        Run(in, out);
        // std::cout << out.str();
        assert(out.str() == "6 8 12\n");
        std::cout << "PASSED\n";
    }
    {
        std::cout << "TEST 4\n";
        std::stringstream out, in( "15\
                                    10\
                                    1 2 3 4 5 6 8 9 10 11 13 20 30 31 32\
                                    3 7 11 12 13 17 18 20 28 30\
                                    ");
        Run(in, out);
        // std::cout << out.str();
        assert(out.str() == "3 11 13 20 30\n");
        std::cout << "PASSED\n";
    }
    {
        std::cout << "TEST 5\n";
        std::stringstream out, in( "5\
                                    3\
                                    1 2 3 4 5\
                                    -1 1 6");
        Run(in, out);
        // std::cout << out.str();
        assert(out.str() == "1\n");
        std::cout << "PASSED\n";
    }
    std::cout << "---------Test Logic Passed---------\n";
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
    std::mt19937 gen( std::random_device{}() );
    std::cout << "---------Test Random Begin---------\n";
    auto ri = std::uniform_int_distribution< int32_t >{ 1, 5 };
    for( size_t i = 0; i < RANDOM_TEST_ATTEMPTS; ++i )
    {
        std::cout << "Random Test #" << i + 1 << ":";
        const size_t n = std::uniform_int_distribution< size_t >{ 5, 10000 }( gen );
        const size_t m = std::uniform_int_distribution< size_t >{ 2, n / 2 }( gen );
        std::cout << " \tn=" << n << "\tm=" << m << "\n";
        std::vector< int32_t > svec_a( n );
        Vector< int32_t > vec_a( n );
        svec_a[0] = vec_a[0] = ri( gen );
        std::vector< int32_t > svec_b( m );
        Vector< int32_t > vec_b( m );
        svec_b[0] = vec_b[0] = ri( gen );
        for( size_t j = 1; j < n; ++j )
        {
            vec_a[j] = vec_a[j - 1] + ri( gen );
            svec_a[j] = vec_a[j];
        }
        for( size_t j = 1; j < m; ++j )
        {
            vec_b[j] = vec_b[j - 1] + ri( gen );
            svec_b[j] = vec_b[j];
        }
        std::vector< int32_t > svec_i;
        std::set_intersection(  svec_a.begin(), svec_a.end(), 
                                svec_b.begin(), svec_b.end(),
                                std::back_inserter( svec_i ) );
        Vector< int32_t > vec_i = VectorIntersect< int32_t, LessComparator< int32_t > >( vec_a, vec_b );
        std::stringstream std_ss, my_ss;
        std_ss << svec_i;
        my_ss << vec_i;
        assert( std_ss.str() == my_ss.str() && svec_a.size() == n );
        // std::cout << std_ss.str() << my_ss.str() << "PASSED\n";
        std::cout << "PASSED\n";
    }
    std::cout << "---------Test Random Passed---------\n";
}

int main()
{
    TestVector();
    TestLogic();
    TestRandom();
    // Run( std::cin, std::cout );
    return 0;
}
