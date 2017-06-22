#ifndef HashTable_h
#define HashTable_h
#include "LinkedList.h"
#include "data.h"
#include <string>
using namespace std;

class HashTable
{
private:

    LinkedList * array;

    int length;

    int hash( Data d );

public:

    HashTable( int tableLength = 13 );

    void insertItem( Item * newItem );
    void insert(Data d);

    bool erase( Data d );

    Item * getItemByKey( string itemKey );

    void printTable(string &sout, int &cnt );

    void printHistogram();

    int getLength();

    int getNumberOfItems();

    List<File> find(string s);

    ~HashTable();
};

#endif

//*****************************************************************
// End of File
//*****************************************************************
