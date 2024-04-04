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
