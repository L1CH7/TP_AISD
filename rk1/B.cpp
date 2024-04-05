#include <iostream>
#include <string>

template< typename T >
class Stack
{
public:
    Stack()
    :   size_( 0 ), 
        capacity_( 0 ), 
        data_( nullptr )
    {}

    ~Stack() { delete[] data_; }

    bool IsEmpty() const { return size_ == 0; }

    size_t Size() const { return size_; }

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
        if( capacity_ < 8 )
            Reserve( 8 );

        if( size_ == capacity_ )
            Reserve( 2 * capacity_ );

        data_[size_++] = value;
    }

    T Pop()
    {
        if( size_ == 0 )
            return T{ -1 };
        
        return data_[--size_];
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

bool IsStackAnagram( const std::string & src, const std::string & dst )
{
    auto d_it = dst.begin();
    Stack< char > s;
    for( auto s_it = src.begin(); s_it != src.end(); ++s_it )
    {
        s.Push( *s_it );
        while( !s.IsEmpty() && s.Top() == *d_it )
        {
            s.Pop();
            ++d_it;
        }
        
    }
    return s.IsEmpty();
}

void Run( std::istream & is, std::ostream & os )
{
    std::string src, dst;
    is >> src >> dst;
    os << ( IsStackAnagram( src, dst ) ? "YES" : "NO" ) << "\n";
}


#include <sstream>

void TestLogic()
{
    std::cout << "---------Test Logic Begin---------\n";
    {
        std::cout << "TEST 1\n";
        std::stringstream out, in( "STOL SLOT" );
        Run(in, out);
        std::cout << out.str();
        assert(out.str() == "YES\n");
        std::cout << "PASSED\n";
    }
    {
        std::cout << "TEST 2\n";
        std::stringstream out, in( "ABC CAB" );
        Run(in, out);
        std::cout << out.str();
        assert(out.str() == "NO\n");
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