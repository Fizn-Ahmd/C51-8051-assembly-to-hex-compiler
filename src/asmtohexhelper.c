#include "../include/asmtohex.h"

#include <ctype.h>

#define MAX_CHECKSUM_SIZE 3
#define MAX_BYTES_IN_A_LINE 16

/* This funtion does the strcpy operation */
void str_cpy(char *src, char *dest) {
  while (*dest) {
    *src = *dest;
    dest++;
    src++;
  }
  *src = *dest;
}

/* Convert the string to lower case */
void str_lower(char *str) {
  for (; *str; ++str)
    *str = tolower(*str);
}

void str_upper(char *str) {
  for (; *str; ++str)
    *str = toupper(*str);
}

/* Removing Spaces if there are any in assembly file */
void remove_spaces_in_string_buffer(char *str) {
  while (*str) {
    if (*str == ' ') {
      str_cpy(str, str + 1);
      str--;
    }
    str++;
  }
}

/* This funtion reverse the given string */
void str_rev(char *str) {
  char temp, *str2 = str;
  while (*str2)
    str2++;
  str2--;
  while (str < str2) {
    temp = *str2;
    *str2 = *str;
    *str = temp;
    str++;
    str2--;
  }
}

/* This funtion coverts the string hexadecimal to integer. eg: '0A' is converted
 * to 10. */
int hex_str_to_int(char *str) {
  int i = 0, num = 0;
  while (str[i]) {
    if (str[i] >= '0' && str[i] <= '9') {
      num = (str[i] - 48) | num << 4;
    }
    if (str[i] >= 'A' && str[i] <= 'F') {
      num = (str[i] - 55) | num << 4;
    }
    i++;
  }
  return num;
}

/* This funtion return the sum of array */
int arr_sum(int *arr, int count) {
  int sum = count, i = 0;
  while (arr[i] != -1) {
    sum = sum + arr[i];
    i++;
  }
  return sum;
}

/* Calculating the checksum */
char checksum(char *addr_str, char *gen_hex_str) {
  char hex_byte[MAX_CHECKSUM_SIZE];
  int hex_val[MAX_BYTES_IN_A_LINE];
  int total_gen_hex_byte = 0;
  int i = 0, j = 0, k = 0;

  while (addr_str[i]) {
    hex_byte[j++] = addr_str[i++];
    if (j == 2) {
      hex_byte[j] = '\0';
      j = 0;
      hex_val[k++] = hex_str_to_int(hex_byte);
    }
  }
  i = 0;
  j = 0;
  while (gen_hex_str[i]) {
    hex_byte[j++] = gen_hex_str[i++];
    if (j == 2) {
      hex_byte[j] = '\0';
      j = 0;
      hex_val[k++] = hex_str_to_int(hex_byte);
      total_gen_hex_byte++;
    }
  }
  hex_val[k] = -1;
  return arr_sum(hex_val, total_gen_hex_byte);
}

/* Writing the generated hex code to the output file */
void write_to_hex_file(FILE *output_fs, char *addr_str, char *hex_gen_str) {
  char chk_sum, tmp_chk_sum;
  char final_checksum[MAX_CHECKSUM_SIZE];

  chk_sum = checksum(addr_str, hex_gen_str);
  chk_sum = ~chk_sum;
  chk_sum += 1;

  tmp_chk_sum = chk_sum >> 4 & 0x0f;
  if (tmp_chk_sum >= 0 && tmp_chk_sum <= 9) {
    final_checksum[0] = (chk_sum >> 4 & 0x0f) + 48;
  } else {
    final_checksum[0] = (chk_sum >> 4 & 0x0f) + 55;
  }

  tmp_chk_sum = chk_sum & 0x0F;
  if (tmp_chk_sum >= 0 && tmp_chk_sum <= 9) {
    final_checksum[1] = (chk_sum & 0x0F) + 48;
  } else {
    final_checksum[1] = (chk_sum & 0x0F) + 55;
  }

  final_checksum[2] = '\0';

  int i = 0, byte_size = 0;
  while (hex_gen_str[i]) {
    if (i % 2 == 0)
      byte_size++;
    i++;
  }

  fputc(':', output_fs);
  if (byte_size >= 0 && byte_size <= 9) {
    fputc('0', output_fs);
    fputc(byte_size + 48, output_fs);
  } else if (byte_size >= 10 && byte_size <= 15) {
    fputc('0', output_fs);
    fputc(byte_size + 55, output_fs);
  } else {
    fputc('1', output_fs);
    fputc('0', output_fs);
  }

  fputs(addr_str, output_fs);
  fputc('0', output_fs);
  fputc('0', output_fs);
  fputs(hex_gen_str, output_fs);
  fputs(final_checksum, output_fs);
  fputc(10, output_fs); // this adds new line
}

void check_hex_index(FILE *fs, char *gen_hex_str, char *addr_str,
                     int *hex_index) {
  if (*hex_index >= MAX_HEX_INDEX) {
    gen_hex_str[*hex_index] = '\0';
    *hex_index = 0;
    write_to_hex_file(fs, addr_str, gen_hex_str);
  }
}

void update_the_gen_hex_str(FILE *fs, char *input_str, char *addr_str,
                            char *gen_hex_str, int i, int *hex_index) {
  if (input_str[i + 2] != 'x') {
    check_hex_index(fs, gen_hex_str, addr_str, hex_index);
    gen_hex_str[(*hex_index)++] = input_str[i + 1];
    gen_hex_str[(*hex_index)++] = input_str[i + 2];
    // h[hex_index++] = '\0';
  } else {
    check_hex_index(fs, gen_hex_str, addr_str, hex_index);
    gen_hex_str[(*hex_index)++] = input_str[i + 3];
    gen_hex_str[(*hex_index)++] = input_str[i + 4];
    // h[4] = '\0';
  }
}

void update_single_byte() {}

void update_two_bytes(FILE *output_fs, char *gen_hex_str, char *input_str,
                      char *addr_str, int *hex_index, char op1, char op2,
                      char symb) {
  check_hex_index(output_fs, gen_hex_str, addr_str, hex_index);
  gen_hex_str[(*hex_index)++] = op1;
  gen_hex_str[(*hex_index)++] = op2;
  int i = 0;
  if (symb == '#') {
    while (input_str[i]) {
      if (input_str[i] == symb) {
        update_the_gen_hex_str(output_fs, input_str, addr_str, gen_hex_str, i,
                               hex_index);
      }
      i++;
    }
  } else if (symb == '@' || symb == 'r') {
    while (input_str[i]) {
      if (input_str[i] == symb) {
        check_hex_index(output_fs, gen_hex_str, addr_str, hex_index);
        gen_hex_str[(*hex_index)++] = input_str[i - 3];
        gen_hex_str[(*hex_index)++] = input_str[i - 2];
      }
      i++;
    }
  }
}

void update_three_bytes(FILE *output_fs, char *gen_hex_str, char *input_str,
                        char *addr_str, int *hex_index, char op1, char op2) {
  check_hex_index(output_fs, gen_hex_str, addr_str, hex_index);
  gen_hex_str[(*hex_index)++] = op1;
  gen_hex_str[(*hex_index)++] = op2;
  int i = 0;
  while (input_str[i]) {
    if (input_str[i] == '#') {
      check_hex_index(output_fs, gen_hex_str, addr_str, hex_index);
      gen_hex_str[(*hex_index)++] = input_str[i - 3];
      gen_hex_str[(*hex_index)++] = input_str[i - 2];
      update_the_gen_hex_str(output_fs, input_str, addr_str, gen_hex_str, i,
                             hex_index);
    }
    i++;
  }
}

char check_condition(char *input_str, char chr) {
  switch (chr) {
  case 'r':
    if ((strstr(input_str, "0,r") != NULL) ||
        (strstr(input_str, "1,r") != NULL) ||
        (strstr(input_str, "2,r") != NULL) ||
        (strstr(input_str, "3,r") != NULL) ||
        (strstr(input_str, "4,r") != NULL) ||
        (strstr(input_str, "5,r") != NULL) ||
        (strstr(input_str, "6,r") != NULL) ||
        (strstr(input_str, "7,r") != NULL) ||
        (strstr(input_str, "8,r") != NULL) ||
        (strstr(input_str, "9,r") != NULL) ||
        check_if_not_accumulator(input_str) ||
        (strstr(input_str, "b,r") != NULL) ||
        (strstr(input_str, "c,r") != NULL) ||
        (strstr(input_str, "d,r") != NULL) ||
        (strstr(input_str, "e,r") != NULL) ||
        (strstr(input_str, "f,r") != NULL)) {
      return 1;
    }
  case '@':
    if ((strstr(input_str, "0,@") != NULL) ||
        (strstr(input_str, "1,@") != NULL) ||
        (strstr(input_str, "2,@") != NULL) ||
        (strstr(input_str, "3,@") != NULL) ||
        (strstr(input_str, "4,@") != NULL) ||
        (strstr(input_str, "5,@") != NULL) ||
        (strstr(input_str, "6,@") != NULL) ||
        (strstr(input_str, "7,@") != NULL) ||
        (strstr(input_str, "8,@") != NULL) ||
        (strstr(input_str, "9,@") != NULL) ||
        check_if_not_accumulator(input_str) ||
        (strstr(input_str, "b,@") != NULL) ||
        (strstr(input_str, "c,@") != NULL) ||
        (strstr(input_str, "d,@") != NULL) ||
        (strstr(input_str, "e,@") != NULL) ||
        (strstr(input_str, "f,@") != NULL)) {
      return 1;
    }
  case '#':
    if ((strstr(input_str, "0,#") != NULL) ||
        (strstr(input_str, "1,#") != NULL) ||
        (strstr(input_str, "2,#") != NULL) ||
        (strstr(input_str, "3,#") != NULL) ||
        (strstr(input_str, "4,#") != NULL) ||
        (strstr(input_str, "5,#") != NULL) ||
        (strstr(input_str, "6,#") != NULL) ||
        (strstr(input_str, "7,#") != NULL) ||
        (strstr(input_str, "8,#") != NULL) ||
        (strstr(input_str, "9,#") != NULL) ||
        check_if_not_accumulator(input_str) ||
        (strstr(input_str, "b,#") != NULL) ||
        (strstr(input_str, "c,#") != NULL) ||
        (strstr(input_str, "d,#") != NULL) ||
        (strstr(input_str, "e,#") != NULL) ||
        (strstr(input_str, "f,#") != NULL)) {
      return 1;
    }
  default:
    return 0;
  }
}

char check_if_not_accumulator(char *input_str) {
  if ((strstr(input_str, "0a,#") != NULL) ||
      (strstr(input_str, "1a,#") != NULL) ||
      (strstr(input_str, "2a,#") != NULL) ||
      (strstr(input_str, "3a,#") != NULL) ||
      (strstr(input_str, "4a,#") != NULL) ||
      (strstr(input_str, "5a,#") != NULL) ||
      (strstr(input_str, "6a,#") != NULL) ||
      (strstr(input_str, "7a,#") != NULL) ||
      (strstr(input_str, "8a,#") != NULL) ||
      (strstr(input_str, "9a,#") != NULL) ||
      (strstr(input_str, "aa,#") != NULL) ||
      (strstr(input_str, "ba,#") != NULL) ||
      (strstr(input_str, "ca,#") != NULL) ||
      (strstr(input_str, "da,#") != NULL) ||
      (strstr(input_str, "ea,#") != NULL) ||
      (strstr(input_str, "fa,#") != NULL)) {
    return 1;
  } else {
    return 0;
  }
}
