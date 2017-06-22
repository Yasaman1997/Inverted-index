#ifndef STACK_H
#define STACK_H
#include <string>
using std::string;

struct StackNode
{
    string data;
    StackNode *next;
    StackNode( string ="" );
};
class Stack
{
    public:
        Stack();
        void push( const string & );
        void pop();
        string top();
        int size();
    private:
        int sz;
        StackNode *root;
};

#endif // STACK_H
