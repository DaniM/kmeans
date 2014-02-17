#include <cstring>
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include "csvparser.h"

using std::vector;
using std::fstream;
using std::string;
using std::cout;
using std::endl;

vector< vector<double> > parse_csv( const char* filename, const char* delimiters )
{
	vector< vector<double> > v;
	fstream fin( filename, fstream::in );
	if( fin )
	{
		string line;
		while( std::getline( fin,line ) )
		{
			char* str_cpy = new char[ line.size() + 1 ];
			strcpy( str_cpy, line.c_str() );
			char* number = strtok( str_cpy, delimiters );
			vector<double> row;
			while( number != NULL )
			{
				row.push_back( atof( number ) );
				number = strtok( NULL, delimiters );
			}
			if ( row.size() > 0)
			{
				v.push_back( row );
			}
			delete[] str_cpy;
		}
		fin.close();
	}
	else
	{
		cout << "Unable to open the file" << endl;
	}
	return v;
}

void parse_csv( const char* filename, const char* delimiters, vector< vector<double> >& matrix )
{
	matrix.clear();
	fstream fin( filename, fstream::in );
	if( fin )
	{
		string line;
		while( std::getline( fin, line ) )
		{
			char* str_cpy = new char[ line.size() + 1 ];
			char* number = strtok( strcpy( str_cpy, line.c_str() ), delimiters );
			vector<double> row;
			while( number != NULL )
			{
				row.push_back( atof( number ) );
				number = strtok( NULL, delimiters );
			}
			if ( row.size() > 0)
			{
				matrix.push_back( row );
			}
			delete[] str_cpy;
		}
		fin.close( );
	}
	else
	{
		cout << "Unable to open the file" << endl;
	}
}
