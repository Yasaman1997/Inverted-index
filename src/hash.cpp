#include "hash.h"


hash::hash( int tableLength )
{
    if (tableLength <= 0) tableLength = 13;
    array = new LinkedList[ tableLength ];
    length = tableLength;
}

int hash::getHash( string itemKey )
{
    int value = 0;
    for ( int i = 0; i < itemKey.length(); i++ )
        value += itemKey[i];
    return (value * itemKey.length() ) % length;
}

void hash::insertItem( Item * newItem )
{
    int index = getHash( newItem -> key );
    array[ index ].insertItem( newItem );
}

bool hash::removeItem( string itemKey )
{
    int index = getHash( itemKey );
    return array[ index ].removeItem( itemKey );
}

Item * hash::getItemByKey( string itemKey )
{
    int index = getHash( itemKey );
    return array[ index ].getItem( itemKey );
}

void hash::printTable()
{
    cout << "\n\nHash Table:\n";
    for ( int i = 0; i < length; i++ )
    {
        cout << "Bucket " << i + 1 << ": ";
        array[i].printList();
    }
}

void hash::printHistogram()
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

int hash::getLength()
{
    return length;
}

int hash::getNumberOfItems()
{
    int itemCount = 0;
    for ( int i = 0; i < length; i++ )
    {
        itemCount += array[i].getLength();
    }
    return itemCount;
}

hash::~hash()
{
    delete [] array;
}
