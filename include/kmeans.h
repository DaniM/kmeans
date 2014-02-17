#ifndef __KMEANS_H__
#define __KMEANS_H__

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdlib>

typedef std::vector< std::vector<double> > Cluster;

//template<typename T> T v_distance( const std::vector<T>&, const std::vector<T>& );

//template<typename T> std::vector<T> v_sum( const std::vector<T>&, const std::vector<T>& );

//template<typename T> void print_vector( const std::vector<double>& );

template<typename T> T v_distance( const std::vector<T>& a, const std::vector<T>& b )
{
	using std::vector;
	typedef typename vector<T>::size_type Size;
	Size size = min( a.size(), b.size() );

	T distance = 0;

	for (Size i = 0; i != size; ++i)
	{
		distance += (a[i] - b[i]) * (a[i] - b[i]);
	}

	return sqrt(distance);
}

template<typename T> std::vector<T> v_sum( const std::vector<T>& a, const std::vector<T>& b )
{
	using std::vector;
	typedef typename vector<T>::size_type Size;
	Size size = min( a.size(), b.size() );

	vector<T> sum( size, 0 );

	for (Size i = 0; i != size; ++i)
	{
		sum[i] = a[i] + b[i];
	}

	return sum;
}

template<typename T> void print_vector(const std::vector<T>& v)
{
	using std::cout;
	using std::endl;
	using std::vector;
	typedef typename vector<T>::size_type Size;
	cout << '[';
	Size size = v.size();
	if( size > 0 )
	{
		for (Size i = 0; i < (size - 1); ++i)
		{
			cout << v[i] << ", ";
		}
		cout << v[ size - 1 ];
	}
	cout << ']';
	cout << endl;
}

template<typename T> void shuffle_vector( std::vector<T>& v )
{
	using std::vector;
	using std::swap;
	typedef typename vector<T>::size_type VSize;
	for ( VSize i = v.size() - 1; i > 0; i-- )
	{
	    swap( v[i], v[ rand( ) % ( i + 1 ) ] );
	}
}

// copy parameters 

std::vector< Cluster > km_expectation( const std::vector< std::vector<double> >&, const std::vector< std::vector<double> >& );

std::vector< std::vector<double> > km_maximization( const std::vector< Cluster >& );

std::vector< std::vector<double> > kmeans( const std::vector< std::vector<double> >& , const std::vector< std::vector<double> >& );

// 

//void km_expectation( const std::vector< std::vector<double> >&, const std::vector< std::vector<double> >&, std::vector< Cluster >& );

//void km_maximization( const std::vector< Cluster >&, std::vector< std::vector<double> >& );

//void kmeans( std::vector< std::vector<double> >& , const std::vector< std::vector<double> > );

#endif