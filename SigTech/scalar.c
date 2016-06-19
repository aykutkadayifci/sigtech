#include <stdio.h>
#include "emmintrin.h"
#include "immintrin.h"
#include "time_meas.h"
#define FIX_MPY(x, y) (short)(((int)x * (int)y)>>15);

int16_t* x;
int16_t* y;
int16_t* z;

int i,j;
int N;
time_stats_t ts;

void operation(int16_t* x,int16_t* y, int16_t* z, int N){
    int i;
    for (i=0; i<N; i+=8){
        z[i] = FIX_MPY(x[i], y[i]);
        z[i+1] = FIX_MPY(x[i+1], y[i+1]);
        z[i+2] = FIX_MPY(x[i+2], y[i+2]);
        z[i+3] = FIX_MPY(x[i+3], y[i+3]);
        z[i+4] = FIX_MPY(x[i+4], y[i+4]);
        z[i+5] = FIX_MPY(x[i+5], y[i+5]);
        z[i+6] = FIX_MPY(x[i+6], y[i+6]);
        z[i+7] = FIX_MPY(x[i+7], y[i+7]);
        
    }
}

int main(int argc, char *argv[]){
    reset_meas(&ts);
    
    N = atoi(argv[1]);
    x = malloc(N*sizeof(int16_t));
    y = malloc(N*sizeof(int16_t));
    z = malloc(N*sizeof(int16_t));
    
    start_meas(&ts);
    
    for (j=0; j<1000; j++){
        operation(x,y,z,N);
    }
    stop_meas(&ts);
    printf("%llu\n", (ts.diff)/1000);
    return(0);
}

