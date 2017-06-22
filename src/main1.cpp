#include <iostream>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <set>
#include <cstdlib>
#include "Base.cpp"
#include "List.cpp"
#include "AVL.cpp"
#include "TST.cpp"
#include "Trie.cpp"
#include "Driver.cpp"

using namespace std;

int main()
{
	init();
	Data d( "123", File( "456", 10 ) );
	tst.insert( d );
	tst.inorder();
	return 0;
}
