#include "HashTable.h"
#include <iostream>
#include <string>
#include <QString>

using namespace std;


HashTable::HashTable( int tableLength )
{
    if (tableLength <= 0) tableLength = 13;
    array = new LinkedList[ tableLength ];
    length = tableLength;
}

int HashTable::hash( Data d )
{
    string itemKey=d.word;
    int value = 0;
    for ( int i = 0; i < itemKey.length(); i++ )
        value += itemKey[i];
    return (value * itemKey.length() ) % length;
}

void HashTable::insertItem( Item * newItem )
{
    int index = hash( newItem -> key );
    List<File> fs= array[ index ].find( newItem->key.word );
    if( fs.size()>0 ){
        if(!fs.find(newItem->key.file.name))
          fs.insert(newItem->key.file.name);
        return;
    }
    newItem->files.insert(newItem->key.file);
    array[ index ].insertItem( newItem );
}

void HashTable::insert( Data d )
{

    Item * temp = new Item();
    temp->key=d;
    temp->next=NULL;
    insertItem(temp);
}


bool HashTable::erase( Data d )
{
    int index = hash( d.word );
    return array[ index ].removeItem( d );
}


List<File> HashTable::find(string s){

    int index = hash( s );
    return array[ index ].find(s);
}

Item * HashTable::getItemByKey( string itemKey )
{
    int index = hash( itemKey );
    return array[ index ].getItem( itemKey );
}

void HashTable::printTable(string &sout, int &cnt )
{
    std::cout << "\n\nHash Table:\n";
    for ( int i = 0; i < length; i++ )
    {
        string s = QString().asprintf("%d", i + 1).toStdString();
        sout = "Bucket " + s + ": \n";
        sout = sout+ array[i].printList(cnt);
    }
}

void HashTable::printHistogram()
{
    cout << "\n\nHash Table Contains ";
    cout << getNumberOfItems() << " Items total\n";
    for ( int i = 0; i < length; i++ )
    {
        cout << i + 1 << ":\t";
        for ( int j = 0; j < array[i].getLength(); j++ )
            cout << " X";
        cout << "\n";
    }
}

int HashTable::getLength()
{
    return length;
}

int HashTable::getNumberOfItems()
{
    int itemCount = 0;
    for ( int i = 0; i < length; i++ )
    {
        itemCount += array[i].getLength();
    }
    return itemCount;
}

HashTable::~HashTable()
{
    delete [] array;
}

