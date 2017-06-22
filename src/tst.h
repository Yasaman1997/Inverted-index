#ifndef TST_H
#define TST_H

#include <list.h>
#include <file.h>
#include <data.h>

struct TSTNode
{
    int isEnd;
    char m;
    TSTNode *Left, *Mid, *Right;
    List < File > files;
    TSTNode();
};
class TST
{
    public:
        TST();
        void insert( const Data & );
        void erase( const Data & );
        void RemoveFile( const File );
        void RemoveFile( TSTNode *, const File );
        void inorder( stringstream &, int & );
        void inorder( TSTNode *, string, stringstream &, int & );
        List < File > find( const string & );
        List < File > find( TSTNode *, const string &, int );
    private:
        TSTNode *root;
};


#endif // TST_H
