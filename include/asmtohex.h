#ifndef asmtohex
#define asmtohex

#include <stdio.h>

char checksum(char *, char *);
int sum(int *, int);
int converting_string_to_integer(char *);
void copy(char *, char *);
void str_rev(char *);
void writing_to_hex_file(FILE *, char *, char *);
void core_convertion_algorithm(FILE *, FILE *);
void converting_read_lines_from_asm_file(char *);

#endif
