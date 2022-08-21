#include "../include/asmtohex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  FILE *input_fs, *output_fs;

  input_fs = fopen(argv[1], "r");
  output_fs = fopen("a.hex", "w");
  core_convertion_algorithm(input_fs, output_fs);
}
