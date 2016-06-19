#include <stdlib.h>
#include <stdio.h>
#include "emmintrin.h"
#include "immintrin.h"
#include "time_meas.h"
#include <malloc.h>


__m128i* x;
__m128i* y;
__m128i* z;
int j;
int N;
time_stats_t ts;

void operation(__m128i* x,__m128i* y, __m128i* z, int N){
    int i;
    for (i=0; i<(N>>3); i+=8){
        z[i]= _mm_slli_epi16(_mm_mulhi_epi16(x[i],y[i]),1);
        z[i+1]= _mm_slli_epi16(_mm_mulhi_epi16(x[i+1],y[i+1]),1);
        z[i+2]= _mm_slli_epi16(_mm_mulhi_epi16(x[i+2],y[i+2]),1);
        z[i+3]= _mm_slli_epi16(_mm_mulhi_epi16(x[i+3],y[i+3]),1);
        z[i+4]= _mm_slli_epi16(_mm_mulhi_epi16(x[i+4],y[i+4]),1);
        z[i+5]= _mm_slli_epi16(_mm_mulhi_epi16(x[i+5],y[i+5]),1);
        z[i+6]= _mm_slli_epi16(_mm_mulhi_epi16(x[i+6],y[i+6]),1);
        z[i+7]= _mm_slli_epi16(_mm_mulhi_epi16(x[i+7],y[i+7]),1);
        
    }
}



int main(int argc, char *argv[]){
    
    if (argc!= 2) {
        printf("fft size(16-4096) test(0-2)!!\n");
        exit(-1);
    }
    
    N = atoi(argv[1]);
    
    x = (__m128i*)memalign(32,(N>>3)*sizeof(int16_t));
    y = (__m128i*)memalign(32,(N>>3)*sizeof(int16_t));
    z = (__m128i*)memalign(32,(N>>3)*sizeof(int16_t));
    reset_meas(&ts);
    start_meas(&ts);
    for (j=0; j<1000; j++){
        operation(x,y,z,N);
    }
    stop_meas(&ts);
    printf("%llu\n", (ts.diff)/1000);
    return(0);
}