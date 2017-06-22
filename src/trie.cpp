#include "trie.h"

TrieNode::TrieNode()
{
    isEnd = sz = 0;
    for( int i = 0 ; i < 256 ; i ++ )
        next[i] = NULL;
}

Trie::Trie()
{
    root = new TrieNode;
}

void Trie :: insert( const Data &d )
{
    List<File> fs=find( d.word );
    if( fs.size()>0 ){
        if(!fs.find(d.file.name))
          fs.insert(d.file.name);
        return;
    }
    TrieNode *p = root;
    for( int i = 0 ; i < d.word.size() ; i ++ )
    {
        if( !p->next[ d.word[i] ] )
            p->next[ d.word[i] ] = new TrieNode();
        p->sz ++;
        p = p->next[ d.word[i] ];
    }
    p->isEnd ++;
    p->files.insert( d.file );
}
void Trie :: erase( const Data &d )
{
    if( !find( d.word ).size() )
        return;
    TrieNode *p = root;
    for( int i = 0 ; i < d.word.size() ; i ++ )
    {
        p->sz --;
        p = p->next[ d.word[i] ];
    }
    p->isEnd --;
    p->files.erase( d.file );
}
void Trie :: RemoveFile( const File f )
{
    RemoveFile( root, f );
}
void Trie :: RemoveFile( TrieNode *p, const File f )
{
    if( !p )
        return;
    if( p->files.find( f ) )
        p->files.erase( f );
    for( int i = 0 ; i < 256 ; i ++ )
        if( p->next[i] )
            RemoveFile( p->next[i], f );
}
void Trie :: inorder( stringstream &sout, int &cnt )
{
    inorder( root, "", sout, cnt );
}
void Trie :: inorder( TrieNode *p, string cur, stringstream &sout, int &cnt )
{
    if( !p )
        return;
    if( p->isEnd )
    {
        sout << cur << " -> ";
        cnt ++;
        p->files.show( sout );
    }
    for( int i = 0 ; i < 256 ; i ++ )
        if( p->next[i] )
            inorder( p->next[i], cur + char(i), sout, cnt );
}
List < File > Trie :: find( const string &str )
{
    return find( root, str, 0 );
}
List < File > Trie :: find( TrieNode *p, const string &str, int idx )
{
    if( !p )
        return List < File >();
    if( idx == str.size() )
        return p->files;
    return find( p->next[ str[idx] ], str, idx+1 );
}
