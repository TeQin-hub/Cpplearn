#include <iostream>

using std::cout;
using std::endl;

struct Node
{
    Node(int data = 0,Node *pre = nullptr,Node *next = nullptr)
    :_data(data)
    ,_pre(pre)
    ,_next(next)
    {
        cout << "Node(int = 0,Node * = nullptr,Node * = nullptr)" << endl;
    }

    ~Node()
    {
        cout << "~Node" << endl;
    }
    int _data;
    Node *_pre;
    Node *_next;
};

class List
{
public:
    List()
    :_head(new Node())
    ,_tail(new Node())
    ,_size(0)
    {
        cout << "List()" << endl;
        _head->_next = _tail;
        _tail->_pre = _head;
    }

    void push_front(int data)
    {
        Node *newNode = new Node(data);
        newNode->_pre = _head;
        newNode->_next = _head->_next;
        _head->_next->_pre = newNode;
        _head->_next = newNode;
        ++_size;
    }

    void push_back(int data)
    {
        Node *newNode = new Node(data);
        newNode->_pre = _tail->_pre;
        newNode->_next = _tail;
        _tail->_pre->_next = newNode;
        _tail->_pre = newNode;
        ++_size;
    }

    void pop_front()
    {   if(_size>0)
        {
            Node *pNode = _head->_next;
            _head->_next = pNode->_next;
            pNode->_next->_pre = _head;
            delete pNode;
            pNode = nullptr;
            --_size;
        }else
        {
            cout << "is empty" << endl;
        }
    }

    void pop_back()
    {
        if(_size>0)
        {
            Node *pNode = _tail->_pre;
            _tail->_pre = pNode->_pre;
            pNode->_pre->_next = _tail;
            delete pNode;
            pNode = nullptr;
            --_size;
        }else
        {
            cout << "is_empty" << endl;
        }
    }

    bool find(int data)
    {
        if(_size>0)
        {
            Node *pNode = _head->_next;
            while(pNode)
            {
                if(pNode->_data==data)
                {
                    return true;
                }
                pNode = pNode->_next;
            }
        }else
        {
            cout << "find is empty" << endl;
        }
        return false;
    }

    void insert(int pos,int data)
    {
        if(pos<0||pos>_size)
        {
            cout << "pos inormal" << endl;
            return;
        }
        Node *pNode = _head;
        while(pos--)
        {
            pNode = pNode->_next;
        }
        Node *ptmp = new Node(data);
        ptmp->_pre = pNode;
        ptmp->_next = pNode->_next;
        pNode->_next->_pre = ptmp;
        pNode->_next = ptmp;
    }
    void display() const
    {
        if(size()>0)
        {
            Node *pNode = _head->_next;
            while(pNode&&pNode!=_tail)
            {
                cout << pNode->_data << " ";
                pNode = pNode->_next;
            }
            cout << endl;
        }else
        {
            cout << "List empty" << endl;
        }
    }

    void erase(int data)
    {
        bool flag = find(data);
        if(flag)
        {
            Node *pNode = _head->_next;
            while(pNode&&pNode!=_tail)
            {
                if(pNode->_data==data)
                {
                    Node *ptmp = pNode->_pre;
                    ptmp->_next = pNode->_next;
                    pNode->_next->_pre = ptmp;
                    delete pNode;
                    pNode = nullptr;
                    --_size;
                    pNode = ptmp;
                }
                pNode = pNode->_next;
            }
        }else
        {
            cout << "can not erase" << endl;
            return;
        }
    }

    ~List()
    {
        cout << "~List()" << endl;
        Node *deleteNode = _head->_next;
        while (deleteNode)
        {
            Node *ptmp = deleteNode->_next;
            delete deleteNode;
            deleteNode = nullptr;
            deleteNode = ptmp;
        }
        delete _head;
        _head = nullptr;
    }

    int size() const
    {
        return _size;
    }
private:
    Node *_head;
    Node *_tail;
    int _size;
};
int main()
{
    List lst;
    lst.display();

    cout << endl
         << "Insert" << endl;
    lst.push_front(1);
    lst.push_front(2);
    lst.push_front(3);
    lst.push_front(4);

    cout << endl
         << "back_Inset" << endl;
    lst.push_back(5);
    lst.push_back(6);
    lst.push_back(7);
    lst.push_back(8);
    lst.display();

    cout << endl
         << "pop_front" << endl;
    lst.pop_front();
    lst.pop_front();
    lst.display();

    cout << endl
         << "pop_back" << endl;
    lst.pop_back();
    lst.pop_back();
    lst.display();

    cout << endl
         << "find()" << endl;
    bool flag = lst.find(7);
    cout << "flsg=" << flag << endl;

    cout << endl
         << "insert" << endl;
    lst.insert(2, 9);
    lst.display();

    cout << endl
         << "erase" << endl;
    lst.erase(9);
    lst.display();
    return 0;
}