#include "LinkedList.h"


LinkedList::LinkedList()
{
    head = new Item;
    head -> next = NULL;
    length = 0;
}

void LinkedList::insertItem( Item * newItem )
{
    if (!head -> next)
    {
        head -> next = newItem;
        length++;
        return;
    }
    Item * p = head;
    Item * q = head;
    while (q)
    {
        p = q;
        q = p -> next;
    }
    p -> next = newItem;
    newItem -> next = NULL;
    length++;
}

bool LinkedList::removeItem( Data d )
{
    string itemKey=d.word;
    if (!head -> next) return false;
    Item * p = head;
    Item * q = head;
    while (q)
    {
        if (q -> key.word == itemKey)
        {
             q->files.erase(d.file);

            if(q->files.size()!=0){
                return true;
            }
            p -> next = q -> next;
            delete q;
            length--;
            return true;
        }
        p = q;
        q = p -> next;
    }
    return false;
}


Item * LinkedList::getItem( Data d )
{
     string itemKey=d.word;
    Item * p = head;
    Item * q = head;
    while (q)
    {
        p = q;
        if ((p != head) && (p -> key.word == itemKey))
            return p;
        q = p -> next;
    }
    return NULL;
}

string LinkedList::printList(int &cnt)
{
    string sout="";
    vector<string> ll;
    if (length == 0)
    {
        cout << "\n{ }\n";
        return "";
    }
    Item * p = head;
    Item * q = head;
    cout << "\n{ ";
    while (q)
    {
        p = q;
        if (p != head && find(ll,p->key.word)==-1 )
        {
            ll.push_back(p->key.word);
            cout << p -> key.word;
            sout=sout+ p -> key.word+"->";
            stringstream ss;
            p->files.show(ss);
            sout=sout+ss.str()+"";

            if(p -> next !=NULL)
                sout=sout+" , ";
            if (p -> next) cout << ", ";
            else cout << " ";
        }
        q = p -> next;
    }
    cout << "}\n";
    cnt+=ll.size();
    return sout;
}

int LinkedList::getLength()
{
    return length;
}

LinkedList::~LinkedList()
{
    Item * p = head;
    Item * q = head;
    while (q)
    {
        p = q;
        q = p -> next;
        if (q) delete p;
    }
}

int LinkedList::find(vector<string> l,string s){
    for(int i=0;i<l.size();i++)
        if(l.at(i)== s)
         return i;
     return -1;
}

List<File> LinkedList::find(string s){

    if (length == 0)
    {
        return  List<File>();
    }
    Item * p = head;
    Item * q = head;
    while (q)
    {
        p = q;
        if (p != head )
        {
            if(p->key.word == s)
                return p->files;
        }
        q = p -> next;
    }
    return   List<File>();
}



