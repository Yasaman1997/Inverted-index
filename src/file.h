#ifndef FILE_H
#define FILE_H

#include <string>
using std::string;

struct File
{
    string name;
    int pos;
    File( const string = "", const int =0 );
    bool operator == ( const File & );
    bool operator != ( const File & );
};


#endif // FILE_H
