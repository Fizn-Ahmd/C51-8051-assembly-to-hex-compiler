#include "../include/asmtohex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  FILE *input_file, *output_file;

  input_file = fopen(argv[1], "r");
  output_file = fopen("a.hex", "w");
  core_convertion_algorithm(input_file, output_file);
}
