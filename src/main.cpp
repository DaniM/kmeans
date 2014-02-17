#include <iostream>
#include <ostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstddef>
#include "csvparser.h"
#include "kmeans.h"
#include "xgetopt.h"

using std::string;
using std::vector;
using std::endl;
using std::cout;
using std::ostream;
using std::cerr;

const char* program_name;

void print_usage (ostream& stream, int exit_code)
{
	stream << "Usage: " << program_name << " options [input_samples] [num_centroids]" << endl;
	stream << " -h --help Display this usage information." << endl;
	stream << " -c --centroids filename Centroids initial values. In case this argument is ommited " 
	<< "[num_centroids] samples are selected randomly as initial centroids" << endl;


#ifndef __GNUC__
    stream << " WARNING! Long options are not supported in windows" << endl;
#endif

	exit (exit_code);
}

void print_data( const vector<vector<double> >& data )
{
	typedef vector< vector<double> >::size_type TNumRows;
	TNumRows nRows = data.size();
	for (TNumRows i = 0; i != nRows ; ++i)
	{
		print_vector( data[i] );
	}
}

template<typename T> T string2T( const string& text )
{
    using std::istringstream;
    T value;
    istringstream ss( text );
    return ss >> value ? value : 0;
}

int main(int argc, const char * argv[] )
{
	program_name = argv[0];	
	const char* centroids_file = 0;

	if( argc < 3 )
	{
		print_usage( cerr, 1 );
	}

#ifdef __GNUC__

	const option options[] = 
	{
       	{"help",     no_argument,       0, 'h'},
       	{"centroids",  required_argument, 0, 'c'},
   		{0, 0, 0, 0}
    };

#endif

    int option_index = 0; 
    int next_option;
#ifdef __GNUC__
    while( ( next_option = getopt_long ( argc, const_cast<char**>(argv), "hc:", options, &option_index ) ) != -1 )
#else
    while( ( next_option = getopt ( argc, argv, "hc:" ) ) != -1 )
#endif
    {
    	switch( next_option )
    	{
    		case 'h':
    			print_usage( cout, 0 );
    			break;
    		case 'c':
    			//get the file name
    			centroids_file = optarg;
    			break;
            default:
                cerr << "Unknown option" << endl;
                print_usage( cerr, 1 );
    	}
    }

    vector< vector<double> > centroids;
    if( centroids_file != 0 )
    {
    	parse_csv( centroids_file, ",", centroids );
    	//print_data( centroids );
    }

    //get the input data
    vector<vector<double> > samples;
    if( optind < argc )
    {
    	cout << "reading samples file: (arg "<< optind << ") " << argv[ optind ] << endl;
    	parse_csv( argv[ optind ], ",", samples );
    	//print_data( samples );

    	//is necessary to get the centroids?
        if( centroids.size() == 0 )
        {
            //get num centroids
            if( optind + 1 < argc )
            {
                string s( argv[ optind + 1 ] );
                std::size_t num_centroids = string2T<std::size_t>( s );
                if( num_centroids <= 0 || num_centroids >= samples.size() )
                {
                    cerr << "Wrong number of centroids" << endl;
                    print_usage( cerr, 1 );
                }
                else
                {
                    // select num_centroids randomly
                    // Note: one solution with c++11 could be shuffle the array and return 
                    // the first num_centroids, but let's stick to the good old c++98
                    
                    // a simple shufflin algorithm
                    shuffle_vector( samples );

                    for (std::size_t i = 0; i < num_centroids; ++i)
                    {
                        centroids.push_back( samples[i] );
                    }         
                }
            }
            else
            {
                print_usage( cerr, 1 );
            }
        }
    }
    else
    {
    	print_usage( cout, 1 );
    }

    vector< vector<double> > final_centroids = kmeans( centroids, samples );

    print_data( final_centroids );

	return 0;
}