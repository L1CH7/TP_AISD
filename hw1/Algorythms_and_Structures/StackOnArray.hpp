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
