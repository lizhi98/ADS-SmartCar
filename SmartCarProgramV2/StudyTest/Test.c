#include<stdio.h>

int main(void){
    int a[2] = {1,3};
    int *p = &a[0];
    printf("%d",++(*p));
}