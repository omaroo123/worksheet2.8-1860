//
// Routines to support the portfolio exercise.
//
#ifndef PORTFOLIO_EXERCISE_EXTRA_H
#define PORTFOLIO_EXERCISE_EXTRA_H

// Includes.
#include <stdlib.h>
#include <time.h>

// Parses the command-line arguments; returns -1 after printing a message if there was an error.
int parseCmdLineArgs( int argc, char **argv, int *N, int *nThreads )
{
    if( argc != 3 )
    {
        printf( "ERROR: Two command-line arguments are required: the problem size N and the number of threads to use.\n" );
        return -1;
    }

    *N = atoi( argv[1] );
    if( *N < 1 )
    {
        printf( "ERROR: The problem size N ('%s') should be a positive integer.\n", argv[1] );
        return -1;
    }

    *nThreads = atoi( argv[2] );
    if( *nThreads < 1 )
    {
        printf( "ERROR: The number of threads ('%s') should be a positive integer.\n", argv[2] );
        return -1;
    }

    if( (*N)%(*nThreads) )
    {
        printf( "ERROR: The problem size N=%d must be an exact multiple of the number of threads %d.\n", *N, *nThreads );
        return -1;
    }

    return 0;
}

// Allocates memory for the matrix and vectors, and assigns initial values. Returns -1 on failure.
int initialiseMatrixAndVector( int N, float ***M, float **u, float **v )
{
    // Allocate memory and check for failure.
    *v = (float*) malloc( N*sizeof(float) );
    *u = (float*) malloc( N*sizeof(float) );
    *M = (float**) malloc( N*sizeof(float*) );

    if( *u==NULL || *v==NULL || *M==NULL )
    {
        printf( "ERROR: Could not allocate memory for the vector and matrix.\n" );
        return -1;
    }

    for( int i=0; i<N; i++ )
    {
        (*M)[i] = (float*) malloc( N*sizeof(float) );
        if( (*M)[i]==NULL )
        {
            printf( "ERROR: Could not allocate memory for the matrix rows.\n" );
            return -1;
        }
    }

    // Assign random values to M and u, and clear the vector v.
    srand( time(NULL) );   // Seed the pseudo-random number generator using the system clock.

    for( int i=0; i<N; i++ )
    {
        (*u)[i] = 1.0 * rand() / RAND_MAX;   // Random value in [0,1).
        (*v)[i] = 0.0f;
        for( int j=0; j<N; j++ )
            (*M)[i][j] = 1.0 * rand() / RAND_MAX;
    }

    return 0;
}

// Frees the memory allocated by initialiseMatrixAndVector().
void freeMatrixAndVector( int N, float **M, float *u, float *v )
{
    free( u );
    free( v );

    for( int i=0; i<N; i++ ) free( M[i] );
    free( M );
}

// Displays the matrix and vectors side by side. Only call this for small problem sizes.
void displayProblem( int N, float **M, float *u, float *v )
{
    if( N>12 )   // It is recommended to call this routine only for N<=12, as it is hard to view in a shell otherwise.
    {
        printf( "Cannot display the matrix and vectors: N is too large.\n" );
        return;
    }

    printf( "Displaying in the format MATRIX : VECTOR U : VECTOR V\n" );
    for( int row=0; row<N; row++ )
    {
        for( int col=0; col<N; col++ ) printf( "%.3f ", M[row][col] );
        printf( " :  %.3f  :  %.3f\n", u[row], v[row] );
    }
}

#endif