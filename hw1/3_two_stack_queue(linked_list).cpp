/** 
 * 3_3. Реализовать очередь с помощью двух стеков.
 * Требования: Очередь должна быть реализована в виде класса. Стек тоже должен быть реализован в виде класса.
 */

#include <iostream>
#include <cstdint>
#include <cassert>

template< typename T >
class Stack
{
    struct Node
    {
        T data;
        Node * next;

        Node( T data, Node * next = nullptr )
        :   data( data ), 
            next( next )
        {}
    };

public:
    Stack()
    :   head_( nullptr )
    {}

    Stack( const Stack & other )
    :   Stack()
    {
        Node * before_head = new Node( 0 ),
             * other_ptr = other.head_,
             * curr_ptr = before_head;

        while( other_ptr )
        {
            Node * item = new Node( other_ptr->data );
            curr_ptr->next = item;
            other_ptr = other_ptr->next;
            curr_ptr = curr_ptr->next;
        }
        head_ = before_head->next;
        delete before_head;
    }

    Stack & operator=( const Stack & other )
    {
        while( !IsEmpty() )
        {
            Pop();
        }
 
        Node * before_head = new Node( 0 ),
             * other_ptr = other.head_,
             * curr_ptr = before_head;

        while( other_ptr )
        {
            Node * item = new Node( other_ptr->data );
            curr_ptr->next = item;
            other_ptr = other_ptr->next;
            curr_ptr = curr_ptr->next;
        }
        head_ = before_head->next;
        delete before_head;
        return *this;
    }

    Stack( Stack && other ) = delete;

    Stack & operator=( Stack && other ) = delete;

    ~Stack()
    {
        while( !IsEmpty() )
        {
            Pop();
        }
    }

    bool IsEmpty() const
    {
        return head_ == nullptr;
    }

    T Top() const
    {
        return head_->data;
    }

    void Push( T data )
    {
        Node * temp = new Node( data, head_ );
        head_ = temp;
        // temp = nullptr;
        // delete temp;
    }

    T Pop()
    {
        if( IsEmpty() )
            return -1;
        Node * temp = head_;
        head_ = head_->next;
        T popped = temp->data;
        delete temp;
        return popped;
    }

private:
    Node * head_;
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
            assert(0);
        }
    }
    out << "YES\n";
}

int main()
{
    TestStack();
    TestQueue();
    // char *s = (char*)malloc(1024); strcpy(s, "Hello world!"); printf("string is: %s\n", s);
    // Run( std::cin, std::cout );
    return 0;
}