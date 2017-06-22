#ifndef DATA_H
#define DATA_H

#include <string>
#include <file.h>
using std::string;

struct Data
{
    string word;
    File file;
    Data( const string ="", const File =File() );
};


#endif // DATA_H
