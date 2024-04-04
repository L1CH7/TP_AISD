/** 
 * 3_3. Реализовать очередь с помощью двух стеков.
 * Требования: Очередь должна быть реализована в виде класса. Стек тоже должен быть реализован в виде класса.
 */

#include <iostream>
#include <cstdint>
#include <cassert>

// Stack implemented on dynamic array
template< typename T >
class Stack
{
public:
    Stack()
    :   size_( 0 ), 
        capacity_( 0 ), 
        data_( nullptr )
    {}
    
    Stack( const Stack & other )
    :   size_( other.size_ ),
        capacity_( other.capacity_ ),
        data_( new T[other.capacity_] )
    {
        for( size_t i = 0; i < other.capacity_; ++i )
            data_[i] = other.data_[i];
    }

    Stack & operator=( const Stack & other )
    {
        if( this == &other )
            return *this;

        while( !IsEmpty() )
        {
            Pop();
        }

        if( other.size_ <= capacity_ )
        {
            for( size_t i = 0; i < other.size_; ++i )
            {
                data_[i] = other.data_[i];
            }
            size_ = other.size_;
            return *this;
        }

        T * buf_arr = new T[other.size_];
        for( size_t i = 0; i < other.size_; ++i )
        {
            buf_arr[i] = other.data_[i];
        }

        size_ = capacity_ = other.size_;
        delete[] data_;
        data_ = buf_arr;
        return *this;

    }

    Stack( Stack && other ) = delete;

    Stack & operator=( Stack && other ) = delete;

    ~Stack()
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

    void Push( const T & value )
    {
        if( capacity_ == 0 )
            Reserve( 8 );

        if( size_ == capacity_ )
            Reserve( 2 * capacity_ );

        data_[size_] = value;
        ++size_;
    }

    T Pop()
    {
        if( size_ == 0 )
            return T{ -1 };
        
        --size_;
        return data_[size_];
    }

    const T & Top() const
    {
        return data_[size_ - 1];
    }
    
    T & Top()
    {
        return data_[size_ - 1];
    }

private:
    size_t  size_,
            capacity_;
    T * data_;
};

template< typename T >
class Queue
{
public:
    Queue()
    :   pusher_(), 
        popper_()
    {}

    Queue( const Queue & other )
    :   pusher_( other.pusher_ ), 
        popper_( other.popper_ )
    {}

    Queue & operator=( const Queue & other )
    {
        pusher_ = other.pusher_;
        popper_ = other.popper_;
        return *this;
    }

    Queue( Queue && other ) = delete;

    Queue & operator=( Queue && other ) = delete;

    // we just need to delete 2 stacks, which already have a destructor, so queue`s destructor is default
    ~Queue() = default;

    bool IsEmpty() const
    {
        return  pusher_.IsEmpty() && 
                popper_.IsEmpty();
    }

    void Push( T data )
    {
        pusher_.Push( data );
    }

    T Pop()
    {
        if( popper_.IsEmpty() )
        {
            while( !pusher_.IsEmpty() )
            {
                popper_.Push( pusher_.Pop() );
            }
        }
        return popper_.Pop();
    }

private:
    Stack< T >  pusher_, 
                popper_;
};

void TestStack()
{
    {
        Stack< int > s;
        s.Push( 5 );
        assert( !s.IsEmpty() );
        assert( s.Top() == 5 );
        assert( s.Pop() == 5 );
        assert( s.Pop() == -1 );
        assert( s.IsEmpty() );
        std::cout << "Stack Test: Functions - OK\n";
    }
    {
        Stack< int > s;
        s.Push( 5 );
        s.Push( 4 );
        Stack< int > s2( s );
        assert( !s.IsEmpty() && !s2.IsEmpty() );
        assert( s.Pop() == s2.Pop() );
        assert( s.Pop() == s2.Pop() );
        assert( s.IsEmpty() && s2.IsEmpty() );
        std::cout << "Stack Test: Copy constructor - OK\n";
    }
    {
        Stack< int > s;
        s.Push( 5 );
        s.Push( 4 );
        Stack< int > s2;
        s2.Push( 10 );
        assert( s2.Top() == 10 );
        s2 = s;
        assert( s2.Top() == 4 );
        assert( !s.IsEmpty() && !s2.IsEmpty() );
        assert( s.Pop() == s2.Pop() );
        assert( s.Pop() == s2.Pop() );
        assert( s.IsEmpty() && s2.IsEmpty() );
        std::cout << "Stack Test: Copy assignment - OK\n";
    }
}

void TestQueue()
{

}

void Run( std::istream & in, std::ostream & out )
{
    size_t n = 0;
    in >> n;
    Queue< int32_t > q;
    for( size_t i = 0; i < n; ++i )
    {
        int32_t command = 0, 
                value = 0;
        in >> command >> value;
        // 2 - pop front
        // 3 - push back
        switch( command )
        {
        case 3: 
            q.Push( value );
            break;

        case 2: 
            if( value != q.Pop() )
            {
                out << "NO\n";
                return;
            }
            break;
        default:
            std::cerr << "wrong command:" << command << "\n";
            exit( 1 );
        }
    }
    out << "YES\n";
}

int main()
{
    TestStack();
    TestQueue();
    // Run( std::cin, std::cout );
    return 0;
}