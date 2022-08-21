#ifndef asmtohex
#define asmtohex

#include <stdio.h>
#include <string.h>

#define MAX_HEX_INDEX 32

char checksum(char *, char *);
int arr_sum(int *, int);
int str_to_int(char *);
void str_cpy(char *, char *);
void str_rev(char *);
void str_lower(char *);
void remove_spaces_in_string_buffer(char *);
void write_to_hex_file(FILE *, char *, char *);
void core_convertion_algorithm(FILE *, FILE *);
void check_hex_index(FILE *, char *, char *, int *);
void update_the_gen_hex_str(FILE *, char *, char *, char *, int, int *);
void update_single_byte();
void update_two_bytes(FILE *, char *, char *, char *, int *, char, char, char);
void update_three_bytes(FILE *, char *, char *, char *, int *, char, char);
char check_condition(char *, char);

#endif
