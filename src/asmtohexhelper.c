#include "../include/asmtohex.h"

#include <stdio.h>

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
  for ( ; *str; ++str) 
    *str = tolower(*str);
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

/* This funtion coverts the string hexadecimal to integer. eg: '0A' is converted to 10. */
int str_to_int(char *str) {
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
char checksum(char *p, char *q) {
  char s[3], ch;
  int a[40], count = 0;
  int i = 0, j = 0, k = 0;
  while (p[i]) {
    s[j] = p[i];
    j++;
    i++;
    if (j == 2) {
      s[j] = '\0';
      j = 0;
      a[k] = str_to_int(s);
      k++;
    }
  }
  i = 0;
  j = 0;
  while (q[i]) {
    s[j] = q[i];
    j++;
    i++;
    if (j == 2) {
      s[j] = '\0';
      j = 0;
      a[k] = str_to_int(s);
      k++;
      count++;
    }
  }
  a[k] = -1;
  ch = arr_sum(a, count);
  return ch;
}

/* Writing the generated hex code to the output file */
void write_to_hex_file(FILE *fs, char *d, char *h) {
  char ch;
  ch = checksum(d, h);
  ch = ~ch;
  ch = ch + 1;
  char gi[3], gfx;
  gfx = ch >> 4 & 0x0f;
  if (gfx >= 0 && gfx <= 9)
    gi[0] = (ch >> 4 & 0x0f) + 48;
  else
    gi[0] = (ch >> 4 & 0x0f) + 55;

  gfx = ch & 0x0F;

  if (gfx >= 0 && gfx <= 9)
    gi[1] = (ch & 0x0F) + 48;
  else
    gi[1] = (ch & 0x0F) + 55;

  gi[2] = '\0';

  int i = 0, count = 0;
  while (h[i]) {
    if (i % 2 == 0)
      count++;
    i++;
  }

  fputc(':', fs);
  if (count >= 0 && count <= 9) {
    fputc('0', fs);
    fputc(count + 48, fs);
  } else if (count >= 10 && count <= 15) {
    fputc('0', fs);
    fputc(count + 55, fs);
  } else {
    fputc('1', fs);
    fputc('0', fs);
  }

  fputs(d, fs);
  fputc('0', fs);
  fputc('0', fs);
  fputs(h, fs);
  fputs(gi, fs);
  fputc(10, fs);
}

void check_hex_index(FILE *fs, char *gen_hex_str, char *addr_str, int *index) {
  if (*index >= MAX_HEX_INDEX) {
    gen_hex_str[*index] = '\0';
    *index = 0;
    write_to_hex_file(fs, addr_str, gen_hex_str);
  }
}

void update_the_gen_hex_str(FILE *fs, char *input_str, char *addr_str, char *gen_hex_str, int i, int *j) {
  if (input_str[i + 2] != 'x') {
    check_hex_index(fs, gen_hex_str, addr_str, j);
    gen_hex_str[*j++] = input_str[i + 1];
    gen_hex_str[*j++] = input_str[i + 2];
    // h[j++] = '\0';
  } else {
    check_hex_index(fs, gen_hex_str, addr_str, j);
    gen_hex_str[*j++] = input_str[i + 3];
    gen_hex_str[*j++] = input_str[i + 4];
    // h[4] = '\0';
  }
}

void update_single_byte() {

}

void update_two_bytes(FILE *output_fs, char *gen_hex_str, char *input_str, char *addr_str, int *j, char op1, char op2, char symb) {
  check_hex_index(output_fs, gen_hex_str, addr_str, j);
  gen_hex_str[*j++] = op1;
  gen_hex_str[*j++] = op2;
  int i = 0;
  while (input_str[i]) {
    if (input_str[i] == symb) {
      update_the_gen_hex_str(output_fs, input_str, addr_str, gen_hex_str, &i, j);
    }
    i++;
  }
}

void update_three_bytes(FILE *output_fs, char *gen_hex_str, char *input_str,, char *addr_str, int *j, char op1, char op2) {
   check_hex_index(output_fs, gen_hex_str, addr_str, j);
  gen_hex_str[*j++] = op1;
  gen_hex_str[*j++] = op2;
  int i = 0;
  while (input_str[i]) {
    if (input_str[i] == '#') {
      check_hex_index(output_fs, gen_hex_str, addr_str, j);
      gen_hex_str[*j++] = input_str[i - 3];
      gen_hex_str[*j++] = input_str[i - 2];
      update_the_gen_hex_str(output_fs, input_str, addr_str, gen_hex_str, &i, j);
    }
    i++;
  }
}

bool check_condition(char *str, char chr) {
  switch (chr)
  {
  case chr == 'r':
    if ((strstr(input_str, "0,r") != NULL) || (strstr(input_str, "1,r") != NULL) ||
        (strstr(input_str, "2,r") != NULL) || (strstr(input_str, "3,r") != NULL) ||
        (strstr(input_str, "4,r") != NULL) || (strstr(input_str, "5,r") != NULL) ||
        (strstr(input_str, "6,r") != NULL) || (strstr(input_str, "7,r") != NULL) ||
        (strstr(input_str, "8,r") != NULL) || (strstr(input_str, "9,r") != NULL) ||
        (strstr(input_str, "a,r") != NULL) || (strstr(input_str, "b,r") != NULL) ||
        (strstr(input_str, "c,r") != NULL) || (strstr(input_str, "d,r") != NULL) ||
        (strstr(input_str, "e,r") != NULL) || (strstr(input_str, "f,r") != NULL)) {
          return true;
        }
  case chr == '@':
    if ((strstr(input_str, "0,@") != NULL) || (strstr(input_str, "1,@") != NULL) ||
          (strstr(input_str, "2,@") != NULL) || (strstr(input_str, "3,@") != NULL) ||
          (strstr(input_str, "4,@") != NULL) || (strstr(input_str, "5,@") != NULL) ||
          (strstr(input_str, "6,@") != NULL) || (strstr(input_str, "7,@") != NULL) ||
          (strstr(input_str, "8,@") != NULL) || (strstr(input_str, "9,@") != NULL) ||
          (strstr(input_str, "a,@") != NULL) || (strstr(input_str, "b,@") != NULL) ||
          (strstr(input_str, "c,@") != NULL) || (strstr(input_str, "d,@") != NULL) || 
          (strstr(input_str, "e,@") != NULL) || (strstr(input_str, "f,@") != NULL)) {
            return true;
          }
  case chr == '#'
    if ((strstr(input_str, "0,#") != NULL) ||
          (strstr(input_str, "1,#") != NULL) || (strstr(input_str, "2,#") != NULL) ||
          (strstr(input_str, "3,#") != NULL) || (strstr(input_str, "4,#") != NULL) ||
          (strstr(input_str, "5,#") != NULL) || (strstr(input_str, "6,#") != NULL) ||
          (strstr(input_str, "7,#") != NULL) || (strstr(input_str, "8,#") != NULL) ||
          (strstr(input_str, "9,#") != NULL) || (strstr(input_str, "a,#") != NULL) ||
          (strstr(input_str, "b,#") != NULL) || (strstr(input_str, "c,#") != NULL) ||
          (strstr(input_str, "d,#") != NULL) || (strstr(input_str, "e,#") != NULL) ||
          (strstr(input_str, "f,#") != NULL)) {
            return true;
          }
  default:
    return false;
  }
}