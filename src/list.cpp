#include "list.h"

#include <sstream>
using std::string;
using std::endl;
using std::stringstream;

template < class T >
ListNode < T > :: ListNode( const T &d )
{
    data = d;
    next = NULL;
}
template < class T >
List < T > :: List()
{
    sz = 0;
    root = NULL;
}
template < class T >
void List < T > :: insert( const T &d )
{
    sz ++;
    if( !root )
       root = new ListNode < T > ( d );
    else
    {
        ListNode < T > *p = root;
        while( p->next )
            p = p->next;
        p->next = new ListNode < T > ( d );
    }
}
template < class T >
void List < T > :: erase( const T &d )
{
    ListNode < T > *p = root;
    if( !root )
           return;
    if( root->data == d )
    {
        sz --;
        root = root->next;
    }
    else
    {
        while( p->next && p->next->data != d )
            p = p->next;
        if( p->next->data == d )
        {
            sz --;
            p->next = p->next->next;
        }
    }
}
template < class T >
bool List < T > :: find( const T &d ) const
{
    ListNode < T > *p = root;
    if( !p )
        return false;
    while( p!=NULL && p->data != d )
        p = p->next;
    return p != NULL;
}
template < class T >
void List < T > :: show( stringstream &sout )
{
    ListNode < T > *p = root;
    string sp = "";
    while( p )
    {
        sout << sp << p->data.name;
        sp = ", ";
        p = p->next;
    }
    sout << endl;
}
template < class T >
List < T > merge( List < T > &x, const List < T > &y )
{
    List < T > ans;
    ListNode < T > *p = x.root;
    while( p )
    {
        if( y.find( p->data ) )
            ans.insert( p->data );
        p = p->next;
    }
    return ans;
}
