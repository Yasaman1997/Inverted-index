#include "file.h"

using std::string;
File :: File( string name, int pos ) : name(name), pos(pos) {}
bool File :: operator == ( const File &other )
{
    return name == other.name && pos == other.pos;
}
bool File :: operator != ( const File &other )
{
    return !( *this == other );
}
