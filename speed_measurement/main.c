#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>
#include <limits.h>

#define BUFFER_SIZE 256

int main() {
    struct tms tms0, tms1;
    clock_t clk0, clk1;
    double hz = sysconf(_SC_CLK_TCK);

    clk0 = times(&tms0);

    // measurement task
    printf("uint %u\n",  UINT_MAX);
    for(unsigned int i=0; i<10000;) {
    //for(unsigned int i=0; i<=4000000000;) {
        printf("num %u\n",  i);
        i++;
    }


    clk1 = times(&tms1);

    // print result
    printf("clock %.3fhz\n",  hz);
    printf("real  %.3f\n", (clk1 - clk0) / hz);
    printf("user  %.3f\n", (tms1.tms_utime - tms0.tms_utime) / hz);
    printf("sys   %.3f\n", (tms1.tms_stime - tms0.tms_stime) / hz);

    return 0;
}

