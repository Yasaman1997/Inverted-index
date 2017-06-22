#ifndef HASH_H
#define HASH_H

#include "linkedlist.h"
class hash
{
private:

    linkedList * array;

    int length;
    int getHash( string itemKey );

public:

    hash( int tableLength = 13 );

    void insertItem( Item * newItem );

    bool removeItem( string itemKey );

    Item * getItemByKey( string itemKey );

    void printTable();

    void printHistogram();

    int getLength();

    int getNumberOfItems();

    ~hash();
};

#endif


