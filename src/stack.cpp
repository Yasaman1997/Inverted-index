#include "stack.h"

#include <string>
using std::string;

StackNode::StackNode( string d )
{
    data = d;
    next = NULL;
}

Stack::Stack()
{
    sz = 0;
    root = NULL;
}

void Stack :: push( const string &d )
{
    StackNode *p = new StackNode( d );
    p->next = root;
    root = p;
    sz ++;
}
void Stack :: pop()
{
    root = root->next;
    sz --;
}
string Stack :: top()
{
    return root->data;
}
int Stack :: size()
{
    return sz;
}
