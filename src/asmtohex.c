#include "../include/asmtohex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  FILE *fp, *fs;

  fp = fopen(argv[1], "r");
  fs = fopen("a.hex", "w");
  core_convertion_algorithm(fp, fs);
}
