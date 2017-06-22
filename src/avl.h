#ifndef AVL_H
#define AVL_H

#include <string>
#include <sstream>
#include <list.h>
#include <file.h>
#include <data.h>
using std::string;
using std::stringstream;

class AVLNode {
public:
    string key;
    List < File > files;
    int height;
    int bfactor;
    AVLNode();
    AVLNode( Data );
    AVLNode &operator = ( const AVLNode & );
    AVLNode* parent;
    AVLNode* left;
    AVLNode* right;
};

class AVL {
private:
    AVLNode* root;
public:
    AVL();
    void insert( Data );
    void erase( Data );
    void deleteNode( AVLNode *& );
    List < File > find( string );
    int getHeight() const;
    void findBalance( AVLNode * );
    void balanceTree( AVLNode *& );
    void rightBalance( AVLNode *& );
    void leftBalance( AVLNode *& );
    void leftRotate( AVLNode *& );
    void rightRotate( AVLNode *& );
    void RemoveFile( File );
    void RemoveFile( AVLNode *, File );
    void inorder( stringstream &, int & );
    void inorder( AVLNode *, stringstream &, int & );
};


#endif // AVL_H
