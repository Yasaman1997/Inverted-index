#ifndef LIST_H
#define LIST_H

#include <sstream>
using std::stringstream;

template < class T >
struct ListNode
{
    T data;
    ListNode( const T & );
    ListNode < T > *next;
};
template < class T >
class List
{
template < class S >
friend List < S > merge( List < S > &, const List < S > & );
    public:
        List();
        void insert( const T & );
        void erase( const T & );
        int size() { return sz; }
        bool find( const T & ) const;
        void show( stringstream & );
        ListNode < T > *root;

    private:
        int sz;
//        ListNode < T > *root;
};


#endif // LIST_H
