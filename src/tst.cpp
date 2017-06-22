#include "tst.h"

using std::stringstream;
TSTNode::TSTNode()
{
    m = 0;
    isEnd = 0;
    Left = Mid = Right = NULL;
}
TST::TST()
{
    root = NULL;
}

void TST :: insert( const Data &d )
{
    List<File> fs=find( d.word );
    if( fs.size()>0 ){
        if(!fs.find(d.file.name))
          fs.insert(d.file.name);
        return;
    }
    if( !root )
    {
        root = new TSTNode;
        root->m = d.word[0];
    }
    TSTNode *p = root;
    for( int i = 0 ; i < d.word.size() ; )
    {
        if( !p->m )
        {
            p->m = d.word[i];
        }
        else if( p->m == d.word[i] )
        {
            if( !p->Mid )
                p->Mid = new TSTNode;
            p = p->Mid;
            i ++;
        }
        else if( p->m > d.word[i] )
        {
            if( !p->Left )
                p->Left = new TSTNode;
            p = p->Left;
        }
        else if( p->m < d.word[i] )
        {
            if( !p->Right )
                p->Right = new TSTNode;
            p = p->Right;
        }
    }
    p->files.insert( d.file );
    p->isEnd ++;
}
void TST :: erase( const Data &d )
{
    if( !find( d.word ).size() )
        return;
    TSTNode *p = root;
    for( int i = 0 ; i < d.word.size() ; )
    {
        if( p->m == d.word[i] )
        {
            p = p->Mid;
            i ++;
        }
        else if( p->m > d.word[i] )
            p = p->Left;
        else if( p->m < d.word[i] )
            p = p->Right;
    }
    p->isEnd --;
    p->files.erase( d.file );
}
void TST :: RemoveFile( const File f )
{
    RemoveFile( root, f );
}
void TST :: RemoveFile( TSTNode *p, const File f )
{
    if( !p )
        return;
    if( p->files.find( f ) )
        p->files.erase( f );
    RemoveFile( p->Left, f );
    RemoveFile( p->Mid, f );
    RemoveFile( p->Right, f );
}
void TST :: inorder( stringstream &sout, int &cnt )
{
    inorder( root, "", sout, cnt );
}
void TST :: inorder( TSTNode *p, string cur, stringstream &sout, int &cnt )
{
    if( !p )
        return;
    inorder( p->Left, cur, sout, cnt );
    if( p->isEnd )
    {
        sout << cur << " -> ";
        cnt ++;
        p->files.show( sout );
    }
    inorder( p->Mid, cur + p->m, sout, cnt );
    inorder( p->Right, cur, sout, cnt );
}
List < File > TST :: find( const string &str )
{
    return find( root, str, 0 );
}
List < File > TST :: find( TSTNode *p, const string &str, int idx )
{
    if( !p )
        return List < File > ();
    if( idx == str.size() )
        return p->files;
    if( p->m == str[idx] )
        return find( p->Mid, str, idx + 1 );
    else if( p->m > str[idx] )
        return find( p->Left, str, idx );
    return find( p->Right, str, idx );
}

