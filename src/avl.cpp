#include "avl.h"

#include <iostream>
using namespace std;

AVLNode :: AVLNode()
{
    left = right = NULL;
}
AVLNode :: AVLNode( Data value )
{
    key = value.word;
    bfactor = height = 0;
    files.insert( value.file );
    left = right = parent = NULL;
}

AVLNode & AVLNode :: operator = ( const AVLNode &other )
{
    key = other.key;
    files = other.files;
    height = other.height;
    bfactor = other.bfactor;
    parent = other.parent;
    left = other.left;
    right = other.right;
}

AVL :: AVL()
{
    root = NULL;
}

void AVL :: insert( Data d )
{
    List<File> fs=find( d.word );
    if( fs.size()>0 ){
        if(!fs.find(d.file.name))
          fs.insert(d.file.name);
        return;
    }
    AVLNode *p = root, *tmpRoot = 0;
    while( p )
    {
        tmpRoot = p;
        if( d.word < p->key )
            p = p->left;
        else
            p = p->right;
    }
    if( !root )
        tmpRoot = root = new AVLNode( d );
    else if( d.word < tmpRoot->key )
        tmpRoot->left = new AVLNode( d );
    else
        tmpRoot->right = new AVLNode( d );
    findBalance( tmpRoot );
    balanceTree( tmpRoot );
}

void AVL :: erase( Data d )
{
    if( !find( d.word ).size() )
        return;
    AVLNode *node = root, *parent = 0;
    while( node )
    {
        if( d.word == node->key )
            break;
        parent = node;
        if( d.word < node->key )
            node = node->left;
        else
            node = node->right;
    }
    if( node && node->key == d.word )
    {
        if( node == root )
            deleteNode( root );
        else if( parent->left == node )
            deleteNode( parent->left );
        else
            deleteNode( parent->right );
    }
}

void AVL :: deleteNode( AVLNode *& node )
{
    AVLNode *parent, *tmpNode = node;
    if( !node->right )
        node = node->left;
    else if( !node->left )
        node = node->right;
    else
    {
        tmpNode = node->left;
        parent = node;
        while( tmpNode->right )
        {
            parent = tmpNode;
            tmpNode = tmpNode->right;
        }
        node->key = tmpNode->key;
        if( parent == node )
            parent->left = tmpNode->left;
        else
            parent->right = tmpNode->left;
    }
}

List < File > AVL :: find( string key )
{
    AVLNode *tmp = root;
    while( tmp )
    {
        if( key == tmp->key )
            return tmp->files;
        else if( key < tmp->key )
            tmp = tmp->left;
        else
            tmp = tmp->right;
    }
    return List < File > ();
}

int AVL :: getHeight() const {
    if( root )
        return root->height;
    else
        return 0;
}

void AVL :: findBalance( AVLNode * node )
{
    int leftHeight = 0, rightHeight = 0;
    if( node )
    {
        if( node->left )
            leftHeight = node->left->height;
        else
            leftHeight = 0;
        if( node->right )
            rightHeight = node->right->height;
        else
            rightHeight = 0;
    }
    if( leftHeight > rightHeight )
        node->height = 1 + leftHeight;
    else
        node->height = 1 + rightHeight;
    node->bfactor = rightHeight - leftHeight;
}

void AVL :: balanceTree( AVLNode *& node )
{
    if( node->bfactor > 1 )
        rightBalance( node );
    if( node->bfactor < -1 )
        leftBalance( node );
}

void AVL :: rightBalance( AVLNode *& node )
{
    if( root->right )
    {
        if( root->right->bfactor > 0 )
            leftRotate( root );
        else if( root->right->bfactor < 0 )
        {
            rightRotate( root->right );
            leftRotate( root );
        }
    }
}

void AVL :: leftBalance( AVLNode *& node )
{
    if( node->left )
        if( node->right->bfactor > 0 )
            rightRotate( root );
        else if( node->right->bfactor < 0 )
        {
            leftRotate( node->right );
            rightRotate( node );
        }
}

void AVL :: leftRotate( AVLNode *& node )
{
    AVLNode *tmpNode = node;
    node = node->left;
    tmpNode->left = node->right;
    node->right = tmpNode;
    findBalance( node->left );
    findBalance( node->right );
    findBalance( node );
}

void AVL :: rightRotate( AVLNode *& node )
{
    AVLNode * tmpNode = node;
    node = node->left;
    tmpNode->left = node->right;
    node->right = tmpNode;
    findBalance( node->left );
    findBalance( node->right );
    findBalance( node );
}

void AVL :: RemoveFile( File f )
{
    RemoveFile( root, f );
}

void AVL :: RemoveFile( AVLNode *p, File f )
{
    if( !p )
        return;
    if( p->files.find( f ) )
        p->files.erase( f );
    RemoveFile( p->left, f );
    RemoveFile( p->right, f );
}

void AVL :: inorder( stringstream &sout, int &cnt )
{
    return inorder( root, sout, cnt );
}

void AVL :: inorder( AVLNode *p, stringstream &sout, int &cnt )
{
    if( !p )
        return;
    inorder( p->left, sout, cnt );
    sout << p->key << " -> ";
    cnt ++;
    p->files.show( sout );
    inorder( p->right, sout, cnt );
}
