#pragma once

#include <iostream>
#include <cassert>
#include <cstdint>
#include <bit>

template< typename T >
class Vector
{
public:
    class Iterator
    {
    public:
        Iterator( T * pos = nullptr )
        : pos_( pos )
        {}

        Iterator & operator++()    // prefix
        {
            ++pos_;
            return *this;
        }

        Iterator operator++( int )      // postfix
        {
            Iterator temp = *this;
            pos_++;
            return temp;
        }
        
        Iterator & operator--()    // prefix
        {
            --pos_;
            return *this;
        }

        Iterator operator--( int )      // postfix
        {
            Iterator temp = *this;
            pos_--;
            return temp;
        }

        T & operator*()
        {
            return *pos_;
        }

        const T & operator*() const
        {
            return *pos_;
        }

        T * operator->() const
        {
            return pos_;
        }

        bool operator==( const Iterator & rhs ) const
        {
            return pos_ == rhs.pos_;
        }

        bool operator!=( const Iterator & rhs ) const
        {
            return pos_ != rhs.pos_;
        }

        bool operator<( const Iterator & rhs ) const
        {
            return pos_ < rhs.pos_;
        }

        bool operator>( const Iterator & rhs ) const
        {
            return pos_ > rhs.pos_;
        }

        size_t operator-( const Iterator & rhs )
        {
            if( pos_ > rhs.pos_)
                return pos_ - rhs.pos_;
            
            return rhs.pos_ - pos_;
        }

        Iterator operator+( size_t increment )
        {
            return Iterator{ pos_ + increment };
        }

        Iterator operator-( size_t increment )
        {
            return Iterator{ pos_ - increment };
        }

    protected:
        T * pos_;
    };

public:
    Vector();

    Vector( size_t count, T value = T() );

    Vector( const Vector & other );

    Vector & operator=( const Vector & other );

    Vector( Vector && other );

    Vector & operator=( Vector && other );

    ~Vector();

    bool IsEmpty() const;

    size_t Size() const;

    size_t Capacity() const;

    void Reserve( size_t new_alloc );

    void PushBack( const T & value );

    T PopBack();

    T & Front();

    const T & Front() const;

    T & Back();

    const T & Back() const;

    T & operator[]( size_t index );

    const T & operator[]( size_t index ) const;

    Iterator Begin();

    Iterator End();

    Iterator Begin() const;

    Iterator End() const;

private:
    size_t  size_,
            capacity_;
    T * data_;
};

template< typename T >
Vector< T >::Vector()
:   size_( 0 ), 
    capacity_( 0 ),
    data_( nullptr )
{}

template< typename T >
Vector< T >::Vector( size_t count, T value )
:   size_( count ), 
    capacity_( std::bit_ceil( count ) ),
    data_( new T[capacity_ ] )
{
    for( size_t i = 0; i < size_; ++i )
    {
        data_[i] = value;
    }
}

template< typename T >
Vector< T >::Vector( const Vector & other )
:   size_( other.size_ ),
    capacity_( other.capacity_ ),
    data_( new T[other.capacity_] )
{
    for( size_t i = 0; i < other.capacity_; ++i )
        data_[i] = other.data_[i];
}

template< typename T >
Vector< T > & Vector< T >::operator=( const Vector & other )
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

template< typename T >
Vector< T >::Vector( Vector && other )
:   size_( std::move( other.size_ ) ),
    capacity_( std::move( other.capacity_ ) ),
    data_( std::move( other.data_ ) )
{
    other.size_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
}

template< typename T >
Vector< T > & Vector< T >::operator=( Vector && other )
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

template< typename T >
Vector< T >::~Vector()
{
    delete[] data_;
}

template< typename T >
bool Vector< T >::IsEmpty() const
{
    return size_ == 0;
}

template< typename T >
size_t Vector< T >::Size() const
{
    return size_;
}

template< typename T >
size_t Vector< T >::Capacity() const
{
    return capacity_;
}

template< typename T >
void Vector< T >::Reserve( size_t new_alloc )
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

template< typename T >
void Vector< T >::PushBack( const T & value )
{
    if( capacity_ == 0 )
        Reserve( 8 );

    if( size_ == capacity_ )
        Reserve( 2 * capacity_ );

    data_[size_] = value;
    ++size_;
}

template< typename T >
T Vector< T >::PopBack()
{
    if( size_ == 0 )
        return T{};

    --size_;
    return data_[size_];
}

template< typename T >
T & Vector< T >::Front()
{
    return data_[0];
}

template< typename T >
const T & Vector< T >::Front() const
{
    return data_[0];
}

template< typename T >
T & Vector< T >::Back()
{
    return data_[size_ - 1];
}

template< typename T >
const T & Vector< T >::Back() const
{
    return data_[size_ - 1];
}

template< typename T >
T & Vector< T >::operator[]( size_t index )
{
    if( index < 0 || index >= size_ )
        return data_[capacity_ - 1];

    return data_[index];
}

template< typename T >
const T & Vector< T >::operator[]( size_t index ) const
{
    if( index < 0 || index >= size_ )
        return data_[capacity_ - 1];

    return data_[index];
}

template< typename T >
typename Vector< T >::Iterator Vector< T >::Begin()
{
    return Iterator{ data_ } ;
}

template< typename T >
typename Vector< T >::Iterator Vector< T >::End()
{
    return Iterator{ data_ + size_ }; // past-the-end element; SHOULD NOT be dereferenced
}

template< typename T >
typename Vector< T >::Iterator Vector< T >::Begin() const
{
    return Iterator{ data_ } ;
}

template< typename T >
typename Vector< T >::Iterator Vector< T >::End() const
{
    return Iterator{ data_ + size_ }; // past-the-end element; SHOULD NOT be dereferenced
}


template< typename T >
std::ostream & operator<<( std::ostream & os, const Vector< T > & obj )
{
    for( size_t i = 0; i < obj.Size(); ++i )
    {
        os << obj[i] << ( ( i == obj.Size() - 1 ) ? '\n' : ' ' );
    }
    return os;
}
