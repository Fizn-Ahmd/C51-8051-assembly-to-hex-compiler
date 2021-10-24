#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"asmtohex.h"

int main(int argc, char *argv[])
{
    FILE *fp, *fs;

    fp = fopen(argv[1],"r");
    fs = fopen("a.hex","w");
    core_convertion_algorithm(fp, fs);
}