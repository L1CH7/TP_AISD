#include <iostream>
#include <cassert>

class Queue
{
    struct Node
    {
        int value;
        Node * next;
        Node( int value )
        : next( nullptr ), value( value )
        {
        }
    };

public:
    Queue()
    : tail_( nullptr ), head_( nullptr )
    {
    }

public:
    ~Queue()
    {
        Node * cur = head;
        while( cur )
        {
            Node * node = cur;
            cur = cur->next;
            delete node;
        }
    }

public:
    Queue( const Queue & rhs )
    : head_( nullptr ), tail_( nullptr )
    {
        const Node * cur = rhs.head;
        while( cur )
        {
            const Node * node = cur;
            Push(node->value);
            cur = cur->next;
        }
    }

public:
    Queue & operator=( const Queue & rhs )
    {
        while ( !IsEmpty() )
        {
            Pop();
        }
        const Node * cur = rhs.head;
        while( cur )
        {
            const Node * node = cur;
            Push(node->value);
            cur = cur->next;
        }
        return *this;
    }

    Queue( Queue && ) = delete;
    Queue & operator=( Queue && ) = delete;

    bool IsEmpty()
    {
        return head_ == tail_ && head_ == nullptr;
    }
public:
    void Push( int value )
    {
        Node * node = new Node( value );
        if( )
    }

public:
    int Pop()
    {

    }

private:
    Node * head_, * tail_;
};

void TestQueue()
{
    {
        Queue q;
        std::assert( q.IsEmpty() );
    }
    {
        Queue q;
        q.push( 66 );
        std::assert( !q.IsEmpty() );
        std::assert ( q.Pop() == 66 );
        std::assert( q.IsEmpty() );
    }
    std::cout << "testLogic OK" << "\n";
}

void run(std::istream & in = std::cin, std::ostream & out = std::cout)
{
    /* testing... */
}

int main()
{
    Queue q;
    std::assert(true);
    run(std::cin, std::cout);
    return 0;
}