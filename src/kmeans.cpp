#include "kmeans.h"
#include <algorithm>
#include <limits>
//#include <iostream>

using std::vector;
using std::min;
using std::numeric_limits;

//typedef std::vector< std::vector<double> > Cluster;

vector< Cluster > km_expectation( const vector< vector<double> >& centroids, const vector< vector<double> >& samples)
{
	vector< Cluster > clusters( centroids.size() );

	// min distance
	double minDistance;
	double dist;
	//closest centroid
	typedef vector<double>::size_type Size;

	Size closestCentroid;

	for ( Size i = 0; i != samples.size(); ++i )
	{
		//foreach centroid
		minDistance = v_distance<double>( centroids[0], samples[i] );
		closestCentroid = 0;
		for ( Size j = 1; j < centroids.size(); ++j ) 
		{
			dist = v_distance<double>( centroids[j], samples[i] );
			if( dist < minDistance )
			{
				minDistance = dist;
				closestCentroid = j;
			}
		}

		clusters[closestCentroid].push_back( samples[i] );
	}
	return clusters;
}

vector< vector<double> > km_maximization( const vector< Cluster >& clusters )
{
	typedef vector<Cluster>::size_type Size;
	Size nCentroids = clusters.size();

	vector<vector<double> > centroids;

	//for each cluster, calculate the new centroid
	for ( Size i = 0; i < nCentroids; ++i )
	{
		vector<double> acc = clusters[i][0];
		vector<vector<double> >::size_type nSamples = clusters[i].size();

		for ( vector<vector<double> >::size_type j = 1; j < nSamples; ++j )
		{
			acc = v_sum( acc, clusters[i][j] );
		}

		//normalize
		vector<double>::size_type nComponents = acc.size();
		for ( vector<double>::size_type j = 0; j < nComponents; ++j )
		{
			acc[j] = acc[j] / nSamples;
		}
		centroids.push_back( acc );
	}

	return centroids;
}

vector< vector<double> > kmeans( const vector< vector<double> >& centroids, const vector< vector<double> >& samples)
{
	double diff = numeric_limits<double>::max();
	vector<Cluster> clusters;
	
	//copy values
	vector<vector<double> > current_centroids = centroids;
	vector<vector<double> > new_centroids;

	typedef vector<vector<double> >::size_type Size;
	Size nCentroids = centroids.size();
	
	while( diff > 0.000001 )
	{
		clusters = km_expectation( current_centroids, samples );
		new_centroids = km_maximization( clusters );
		diff = 0;
		//for each centroid calculate the distance between them
		for ( Size i = 0; i < nCentroids; ++i )
		{
			diff += v_distance( current_centroids[i], new_centroids[i] );
		}
		current_centroids = new_centroids;
	}
	return current_centroids;
}

vector< vector<double> > kmeans_its( const vector< vector<double> >& centroids, const vector< vector<double> >& samples, size_t its )
{
	vector<Cluster> clusters;
	
	//copy values
	vector<vector<double> > current_centroids = centroids;
	vector<vector<double> > new_centroids;
	
	size_t it = 0;

	for (size_t i = 0; i < it; ++i )
	{
		clusters = km_expectation( current_centroids, samples );
		new_centroids = km_maximization( clusters );
		current_centroids = new_centroids;
	}

	return current_centroids;
}

// 

//void km_expectation( const std::vector< std::vector<double> >&, const std::vector< std::vector<double> >&, std::vector< Cluster >& );

//void km_maximization( const std::vector< Clusters >&, std::vector< std::vector<double> >& );

//void kmeans( std::vector< std::vector<double> >& , const std::vector< std::vector<double> > );

// explicit instantiation
//template void print_vector<double>( const std::vector<double>& );