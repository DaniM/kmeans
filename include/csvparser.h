
#ifndef __CSVPARSER_H__
#define __CSVPARSER_H__

#include <vector>

std::vector< std::vector<double> > parse_csv( const char*, const char* );

void parse_csv( const char*, const char*, std::vector< std::vector<double> > & );

#endif