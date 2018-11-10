#include "fcntl.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char ** argv){
    int i = 0;
    int f1 = open(argv[1], O_RDONLY);
    int f2 = open(argv[2], O_RDONLY);

    if (f1 == -1 || f2 == -1){
        printf("can't open file");
        close(f1);
        close(f2);
        return 0;
    }

    struct stat f1Stat, f2Stat;
    if (stat(argv[1], &f1Stat)==-1 || stat(argv[2], &f2Stat)==-1) {
        printf("can't get file info");
        close(f1);
        close(f2);
        return 0;
    }

    int size1 = f1Stat.st_size;
    int size2 = f2Stat.st_size;
    if (size1 != size2){
        printf("files don't match");
        close(f1);
        close(f2);
        return 0;
    }

    int arr1[size1];
    int arr2[size2];
    int rd1 = read(f1, arr1, size1);
    int rd2 = read(f2, arr2, size2);

    for (i=0; i<size1; i++) {
        if (arr1[i] != arr2[i]) {
//            printf("1");
            close(f1);
            close(f2);
            //return 0;
        }
    }
    printf("2");
}