#include <set>
#include <sstream>
#include <fstream>
#include <string>
#include <avl.h>
#include <tst.h>
#include <trie.h>
#include "list.h"
#include "file.h"
#include "HashTable.h"
#include "list.cpp"
#include <QDir>
#include <iostream>
#include <vector>

using namespace std;

AVL avl;
TST tst;
Trie trie;
HashTable hashTable;
List < File > files;
std::vector<string> fileNames;
set < string > StopWords;



int find(string name){
   for(int i=0;i<fileNames.size();i++)
       if(fileNames.at(i)== name)
        return i;
    return -1;
}

void init()
{
	fstream fin( "StopWords.txt", fstream::in );
	string str;
	while( fin >> str )
		StopWords.insert( str );
	fin.close();
}
bool isStopWord( string str )
{
    for( int i = 0 ; i < (int) str.size() ; i ++ )
    {
        if( ispunct( str[i] ) )
            return true;
        str[i] = tolower( str[i] );
    }
	return StopWords.find( str ) != StopWords.end();
}
string ReadFileAndInsert( string path, string file, int Type )
{
    fstream fin( (path+"/"+file).c_str(), fstream::in );
    if( !fin.is_open() )
        return "Err. document not found.";
	Data d;
	int pos = 0;
	while( fin >> d.word )
	{
		if( !isStopWord( d.word ) )
		{
			d.file.name = file;
            d.file.pos = pos;
			if( Type == 1 )
				avl.insert( d );
			else if( Type == 2 )
				tst.insert( d );
			else if( Type == 3 )
				trie.insert( d );
            else if( Type == 4 )
                hashTable.insert( d );
            else if(Type == 5)
            {
                avl.insert( d );
                tst.insert( d );
                trie.insert( d );
                hashTable.insert( d );
            }
		}
	}
	fin.close();
    return file + " successfully added.";
}
string ReadFileAndErase( string path, string file, int Type )
{
    fstream fin( (path+"/"+file).c_str(), fstream::in );
    if( !fin.is_open() )
        return "Err. document not found.";
    Data d;
	int pos = 0;
	while( fin >> d.word )
	{
		if( !isStopWord( d.word ) )
		{
			d.file.name = file;
			d.file.pos = pos;
			if( Type == 1 )
				avl.erase( d );
			else if( Type == 2 )
				tst.erase( d );
			else if( Type == 3 )
				trie.erase( d );
            else if( Type == 4 )
                hashTable.erase( d );
		}
	}
	fin.close();
    return file + " successfully removed from lists.";
}
string Driver( int Type, string path, string cmd )
{

	string a, file, mode, str;
	stringstream ssin( cmd );
	ssin >> a;
	if( a == "add" )
	{
        QDir dir(QString::fromStdString(path));
        if (!dir.exists())
            return "Err. Invalid folder path";
        QFileInfoList list = dir.entryInfoList();
        ssin >> file;
        bool check=false;
        for (int i = 0; i < list.size(); ++i) {
            if(list.at(i).fileName().toStdString() == file)
            {
                 check=true;
                 break;
             }
        }
        if(!check)
            return "Err. Invalid file name";
        string ans = ReadFileAndInsert( path, file, 5 );
        int findPos=find(path+file);
        if( findPos==-1 ){
            files.insert( file );
            fileNames.push_back(path+file);
        }
        else{
            return "Err.file already exist";

        }
        return ans;
	}
	else if( a == "del" )
	{
		ssin >> file;
        int findPos=find(path+file);
        if(  findPos!=-1)
		{
            string ans = ReadFileAndErase( path, file, Type );
			files.erase( file );
            fileNames.erase(fileNames.begin()+findPos);
            return ans;
		}
        else
            return "Err. " + file + " not listed now.";
	}
	else if( a == "update" )
	{
		ssin >> file;
        int findPos=find(path+file);
        if(  findPos!=-1)
        {
		if( Type == 1 )
            avl.RemoveFile( File( file, 0 ) );
		else if( Type == 2 )
			tst.RemoveFile( File( file, 0 ) );
		else if( Type == 3 )
			trie.RemoveFile( File( file, 0 ) );
        else if( Type == 4 )
            ReadFileAndErase(path, file, Type );
        string ans = ReadFileAndInsert( path, file, Type );
        if( ans.substr( 0, 3 ) != "Err" )
            return file + " successfully updated.";
        else
            return ans;
        }
        else
            return "file not exist.";
	}
	else if( a == "list" )
	{
		ssin >> mode;
		if( mode == "-w" )
		{
            stringstream sout;
            int cnt = 0;
			if( Type == 1 )
                avl.inorder( sout, cnt );
			else if( Type == 2 )
                tst.inorder( sout, cnt );
			else if( Type == 3 )
                trie.inorder( sout, cnt );
            else if( Type == 4 ){
                string s="";
                hashTable.printTable(s,cnt);
                sout << s;
            }
            sout << "\nNumber of words = " << cnt << endl;
            return sout.str();
		}
		else if( mode == "-l" )
        {
            stringstream sout;
            files.show( sout );
            if(fileNames.size()==0)
            sout<<"list is empty";
               return sout.str();
        }
        else if( mode == "-f" )
		{
//            string sp = "", str, query = "";
//            query = "dir " + path + " > myDir.txt";
//            system(query.c_str());
//            fstream ss( "myDir.txt", fstream::in );
//            stringstream sout;
//			while( ss >> str )
//                if( str.substr( str.size()-4 ) == ".txt" )
//				{
//                    sout << sp << str.substr( 0, str.size()-4 );
//					sp = ", ";
//				}
//			if( sp == "" )
//                sout << "empty directory";
//            sout << endl;
//            return sout.str();

            QDir dir(QString::fromStdString(path));
            if (!dir.exists())
                return "Err. Invalid folder path";
            dir.setFilter(QDir::Files  | QDir::NoSymLinks);
            dir.setSorting(QDir::Size | QDir::Reversed);

            string temp="";
            QFileInfoList list = dir.entryInfoList();
               for (int i = 0; i < list.size(); ++i) {
                temp=temp+list.at(i).fileName().toStdString();
                if(i!=list.size()-1)
                    temp=temp+",";
               }
            if(temp!="")
               return temp;
            else
                return "folder is empty";
		}
	}
	else if( a == "search" )
	{
		ssin >> mode;
		if( mode == "-w" )
		{
			ssin >> str;
			str = str.substr( 1, str.size()-2 );
            stringstream sout;
			if( Type == 1 )
                avl.find( str ).show( sout );
			else if( Type == 2 )
                tst.find( str ).show( sout );
			else if( Type == 3 )
                trie.find( str ).show( sout );
            else if( Type == 4 )
                hashTable.find( str ).show( sout );
            else
                return "please select command";
            return sout.str();
		}
		else if( mode == "-s" )
		{
			List < File > ans;
			ssin >> str;
            if( str[0] == '\"' )
                str = str.substr(1);
			if( Type == 1 )
				ans = avl.find( str );
			else if( Type == 2 )
				ans = tst.find( str );
			else if( Type == 3 )
				ans = trie.find( str );
            else if( Type == 4 )
                ans = trie.find( str );
			while( ssin >> str )
			{
                if( str[ str.size()-1 ] == '\"' )
                    str = str.substr( 0, str.size()-1 );
				if( !isStopWord( str ) )
				{
					if( Type == 1 )
						ans = merge( ans, avl.find( str ) );
					else if( Type == 2 )
						ans = merge( ans, tst.find( str ) );
					else if( Type == 3 )
						ans = merge( ans, trie.find( str ) );
				}
			}
            stringstream sout;
            ans.show( sout );
            return sout.str();
		}
	}

    else if(cmd == "build"){
        QDir dir(QString::fromStdString(path));
        if (!dir.exists())
            return "Err. Invalid folder path";
        dir.setFilter(QDir::Files | QDir::NoSymLinks);
        dir.setSorting(QDir::Size | QDir::Reversed);

        string temp="";
        QFileInfoList list = dir.entryInfoList();
        int currWordNo=0;
        stringstream sout;
           for (int i = 0; i < list.size(); ++i) {
               QFileInfo fileInfo = list.at(i);
               string ans = ReadFileAndInsert( path, fileInfo.fileName().toStdString(), 5 );
                   files.insert( fileInfo.fileName().toStdString() );
                   fileNames.push_back(path+fileInfo.fileName().toStdString() );
                   temp=temp+ans+"\n";
           }
           avl.inorder(sout,currWordNo);
           return "Build succesfully \n"+temp+"\n"+"Total number of added files is "+QString::number(list.size()).toStdString()
                       +"\nTotal number of words is "+QString::number(currWordNo).toStdString();
    }
	else
	{
        return "Err. Invalid command";
	}
}
