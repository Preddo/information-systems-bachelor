#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct frame {

    bool flagR ;
    
    bool flagM ;
    
    clock_t lastAcess ;

    int virtualPageIndex ;

} Frame ;

typedef struct listofframes {

    Frame * list ;
    
    int count ;

} ListOfFrames ;

typedef unsigned int VirtualPage ;

typedef struct listofvirtualpages {

    VirtualPage * list ;
    
    unsigned int maxVirtualPages ;

} tpListOfVirtualPages ;

/**
 * 
 */
void inicializeMainMemory( ListOfFrames * mainMemory, unsigned int numFrames ) ;

/**
 * 
 */
void inicializeListOfVirtualPages( tpListOfVirtualPages * ListOfVirtualPages , unsigned int numVirtualPages ) ;

/**
 *
 */
void allocNewFrame( Frame * ListOfFrames, int frameIndex, int virtualPagaIndex ) ;

/**
 * 
 */
void validateFramePageSize( unsigned int frameSize ) ;

/**
 * 
 */
void validateMainMemorySize( unsigned int mainMemorySize ) ;

/**
 * 
 */
int simulaMemoriaVirtual( const char *  algoritmo, const char *  arquivo, unsigned int frameSize, unsigned int mainMemorySize, const char * mode ) ;




