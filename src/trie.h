#ifndef TRIE_H
#define TRIE_H

#include <list.h>
#include <file.h>
#include <data.h>

struct TrieNode
{
    int isEnd, sz;
    TrieNode *next[256];
    List < File > files;
    TrieNode();
};

class Trie
{
    private:
        TrieNode *root;
    public:
        Trie();
        void insert( const Data & );
        void erase( const Data & );
        void RemoveFile( const File );
        void RemoveFile( TrieNode *, const File );
        void inorder( stringstream &, int & );
        void inorder( TrieNode *, string, stringstream &, int & );
        List < File > find( const string & );
        List < File > find( TrieNode *, const string &, int );
};


#endif // TRIE_H
