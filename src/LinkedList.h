#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>
#include <string>
#include <vector>
#include <list.h>
#include <file.h>
#include "data.h"


using namespace std;


struct Item
{
    Data key;
    List<File> files;
    Item * next;
};
class LinkedList
{
private:
    Item * head;

    int length;

public:

    LinkedList();

    void insertItem( Item * newItem );

    bool removeItem( Data d );

    Item * getItem( Data d );

    string printList(int &cnt);

    int getLength();

    ~LinkedList();
    int find(vector<string> l,string s);
    List<File> find(string s);

};

#endif
