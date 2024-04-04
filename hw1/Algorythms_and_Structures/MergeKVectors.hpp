#include "Heap.hpp"
#include "Vector.hpp"

template< typename T, typename Comparator >
class VectorHeap
{
public:
    struct Node
    {
        typename Vector< T >::Iterator  current,
                                        end;
        Node()
        :   current( nullptr ),
            end( nullptr )
        {}

        Node( typename Vector< T >::Iterator it1, typename Vector< T >::Iterator it2 )
        :   current( it1 ),
            end( it2 )
        {
            assert( current < end );
        }

        bool IsEmpty() const
        {
            return current == end;
        }

        friend std::ostream & operator<<( std::ostream & os, const Node & obj )
        {
            if( !obj.IsEmpty() )
                os << *obj.current;
            else
                os << "nil";

            return os;
        }
    };

    struct NodeComparator
    {
        bool operator()( const Node & a, const Node & b )
        {
            Comparator comp;
            return comp( *a.current, *b.current );
        }
    };

public:
    VectorHeap( const Vector< Vector< T > > & arrays )
    : heap_()
    {
        for( auto it = arrays.Begin(); it != arrays.End(); ++it )
        {
            Node node( it->Begin(), it->End() );
            if( !node.IsEmpty() )
            {
                heap_.Insert( node );
            }
        }
    }

    // extract and insert if not empty
    T ExtractTop()
    {
        Node top = heap_.ExtractTop();
        assert( !top.IsEmpty() );
        T extracted = *top.current;
        ++top.current;
        if( !top.IsEmpty() )
            heap_.Insert( top );
        return extracted;
    }

    // get access and change value of node
    T ExtractTop2()
    {
        T extracted = *heap_.GetTop().current++;
        if( heap_.GetTop().IsEmpty() )
        {
            // remove empty element
            heap_.ExtractTop();
        }
        else
        {
            // if not empty -> place on its place
            heap_.SiftDown( 0 );
        }
        return extracted;
    }

    bool IsEmpty() const
    {
        return heap_.IsEmpty();
    }

    friend std::ostream & operator<<( std::ostream & os, const VectorHeap & obj )
    {
        os << obj.heap_;
        return os;
    }

private:
    Heap< Node, NodeComparator > heap_;
};

template< typename T, typename Comparator >
Vector< T > MergeVectors( const Vector< Vector< T > > & arrays )
{
    VectorHeap< T, Comparator > v_heap( arrays );
    Vector< T > result;
    while( !v_heap.IsEmpty() )
    {
        result.PushBack( v_heap.ExtractTop2() );
    }
    return result;
}
