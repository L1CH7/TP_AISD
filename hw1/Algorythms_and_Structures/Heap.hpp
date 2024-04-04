#pragma once

#include "Vector.hpp"
#include <iostream>

template< typename T, typename Comparator >
class Heap
{
public:
    Heap()
    :   array_()
    {}

    Heap( const Vector< T > & array )
    :   array_( array )
    {
        // make heap from array
        BuildHeap();
    }

    Heap( const Heap & other )
    :   array_( other.array_ )
    {}

    Heap & operator=( const Heap & other )
    {
        // copy vector from another
        array_ = other.array_;
        return *this;
    }

    ~Heap() = default;
    
    Heap( Heap && other ) = delete;

    Heap & operator=( Heap && other ) = delete;

private:
    void BuildHeap()
    {
        for( int64_t i = array_.Size() / 2 - 1; i >= 0; --i )
        {
            // put elements one by another from back on its positions with SiftDown
            SiftDown( i );
        }
    }

    void SiftDown( size_t index )
    {
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;
        // find largest child
        size_t largest = index;
        Comparator comp;
        if( left < array_.Size() && comp( array_[left], array_[index] ) ) // array_[left] < array_[index]
            largest = left;
        if( right < array_.Size() && comp( array_[right], array_[largest] ) ) // array_[right] < array_[largest]
            largest = right;
        // if found => swap and do SiftDown for child
        if( largest != index )
        {
            std::swap( array_[largest], array_[index] );
            SiftDown( largest );
        }
    }

    void SiftUp( size_t index )
    {
        Comparator comp;
        while( index > 0 )
        {
            // find parent
            size_t parent = ( index - 1 ) / 2;
            // if index on its position (index less than parent) => return
            if( !comp( array_[index], array_[parent] ) ) // array_[index] >= array_[parent]
                return;
            // else swap index and parent
            std::swap( array_[index], array_[parent] );
            // next iteration with parent
            index = parent;
        }
    }
    
public:
    void Insert( const T & value )
    {
        array_.PushBack( value );
        SiftUp( array_.Size() - 1 );
    }

    T Extract()
    {
        assert( !array_.IsEmpty() );
        // remember max element
        T extracted = array_.Front();
        // put last element on top of heap
        array_.Front() = array_.Back();
        // remove extracted element
        array_.PopBack();
        // last element is not on its position => SiftDown it
        if( !array_.IsEmpty() )
            SiftDown( 0 );
        return extracted;
    }

    const T & GetTop() const
    {
        return array_.Front();
    }

    bool IsEmpty() const
    {
        return array_.IsEmpty();
    }

    friend std::ostream & operator<<( std::ostream & os, const Heap< T, Comparator > & obj )
    {
        os << obj.array_;
        return os;
    }

protected:
    Vector< T > array_;
};
