#include "../include/asmtohex.h"

#include <stdio.h>
#include <string.h>

/* Core Algorithm takes the input file and generate output hex code */
void core_convertion_algorithm(FILE *fp, FILE *fs) {
  char s[100], d[20], h[20], hu[50];
  int j = 0;

  while ((fgets(s, 100, fp)) != NULL) {
    converting_read_lines_from_asm_file(s);
    printf("%s", s);
    if ((strstr(s, "END") != NULL) || (strstr(s, "end") != NULL)) {
      break;
    }
    if ((strstr(s, "CSEGAT")) != NULL) {
      int i = 0, j = 0;
      while (s[i]) {
        if ((s[i] >= '0' && s[i] <= '9')) {
          d[j] = s[i];
          j++;
          i++;
        } else if (s[i] >= 'A' && s[i] <= 'F') {
          d[j] = s[i];
          j++;
          i++;
        } else if (s[i] >= 'a' && s[i] <= 'f') {
          d[j] = s[i];
          j++;
          i++;
        } else {
          i++;
        }
      }
      d[j] = '\0';
      str_rev(d);
      d[4] = '\0';
    }
    if ((strstr(s, "MOV") != NULL) || (strstr(s, "mov") != NULL)) {

      if ((strstr(s, "A,#") != NULL) || (strstr(s, "a,#") != NULL)) {
        if (j >= 32) {
          h[j] = '\0';
          j = 0;
          writing_to_hex_file(fs, d, h);
        }
        h[j++] = '7';
        h[j++] = '4';
        int i = 0;
        while (s[i]) {
          if (s[i] == '#') {
            if ((s[i + 2] != 'x') && (s[i + 2] != 'X')) {
              if (j >= 32) {
                h[j] = '\0';
                j = 0;
                writing_to_hex_file(fs, d, h);
              }
              h[j++] = s[i + 1];
              h[j++] = s[i + 2];
              // h[j++] = '\0';
            } else {
              if (j >= 32) {
                h[j] = '\0';
                j = 0;
                writing_to_hex_file(fs, d, h);
              }
              h[j++] = s[i + 3];
              h[j++] = s[i + 4];
              // h[4] = '\0';
            }
          }
          i++;
        }
      }
      if (((strstr(s, "0,#") != NULL) && (strstr(s, "R0,#") == NULL) &&
           (strstr(s, "r0,#") == NULL)) ||
          (strstr(s, "1,#") != NULL) || (strstr(s, "2,#") != NULL) ||
          (strstr(s, "3,#") != NULL) || (strstr(s, "4,#") != NULL) ||
          (strstr(s, "5,#") != NULL) || (strstr(s, "6,#") != NULL) ||
          (strstr(s, "7,#") != NULL) || (strstr(s, "8,#") != NULL) ||
          (strstr(s, "C,#") != NULL) || (strstr(s, "D,#") != NULL) ||
          (strstr(s, "E,#") != NULL) || (strstr(s, "F,#") != NULL) ||
          (strstr(s, "c,#") != NULL) || (strstr(s, "d,#") != NULL) ||
          (strstr(s, "e,#") != NULL) || (strstr(s, "f,#") != NULL) ||
          (strstr(s, "9,#") != NULL) || (strstr(s, "0A,#") != NULL) ||
          (strstr(s, "a,#") != NULL) || (strstr(s, "0a,#") != NULL) ||
          (strstr(s, "fA,#") != NULL) || (strstr(s, "B,#") != NULL) ||
          (strstr(s, "fa,#") != NULL) || (strstr(s, "b,#") != NULL) ||
          (strstr(s, "1A,#") != NULL) || (strstr(s, "2A,#") != NULL) ||
          (strstr(s, "3A,#") != NULL) || (strstr(s, "4A,#") != NULL) ||
          (strstr(s, "5A,#") != NULL) || (strstr(s, "6A,#") != NULL) ||
          (strstr(s, "7A,#") != NULL) || (strstr(s, "8A,#") != NULL) ||
          (strstr(s, "9A,#") != NULL) || (strstr(s, "AA,#") != NULL) ||
          (strstr(s, "BA,#") != NULL) || (strstr(s, "CA,#") != NULL) ||
          (strstr(s, "DA,#") != NULL) || (strstr(s, "EA,#") != NULL) ||
          (strstr(s, "FA,#") != NULL) || (strstr(s, "aA,#") != NULL) ||
          (strstr(s, "bA,#") != NULL) || (strstr(s, "cA,#") != NULL) ||
          (strstr(s, "dA,#") != NULL) || (strstr(s, "eA,#") != NULL) ||
          (strstr(s, "1a,#") != NULL) || (strstr(s, "2a,#") != NULL) ||
          (strstr(s, "3a,#") != NULL) || (strstr(s, "4a,#") != NULL) ||
          (strstr(s, "5a,#") != NULL) || (strstr(s, "6a,#") != NULL) ||
          (strstr(s, "7a,#") != NULL) || (strstr(s, "8a,#") != NULL) ||
          (strstr(s, "9a,#") != NULL) || (strstr(s, "Aa,#") != NULL) ||
          (strstr(s, "Ba,#") != NULL) || (strstr(s, "Ca,#") != NULL) ||
          (strstr(s, "Da,#") != NULL) || (strstr(s, "Ea,#") != NULL) ||
          (strstr(s, "Fa,#") != NULL) || (strstr(s, "aa,#") != NULL) ||
          (strstr(s, "ba,#") != NULL) || (strstr(s, "ca,#") != NULL) ||
          (strstr(s, "da,#") != NULL) || (strstr(s, "ea,#") != NULL)) {

        if (j >= 32) {
          j = 0;
          writing_to_hex_file(fs, d, h);
        }
        h[j++] = '7';
        h[j++] = '5';
        int i = 0;
        while (s[i]) {
          if (s[i] == '#') {
            if (j >= 32) {
              h[j] = '\0';
              j = 0;
              writing_to_hex_file(fs, d, h);
            }
            h[j++] = s[i - 3];
            h[j++] = s[i - 2];
            if ((s[i + 2] != 'x') && (s[i + 2] != 'X')) {
              if (j >= 32) {
                h[j] = '\0';
                j = 0;
                writing_to_hex_file(fs, d, h);
              }
              h[j++] = s[i + 1];
              h[j++] = s[i + 2];
              // h[j++] = '\0';
            } else {
              if (j >= 32) {
                h[j] = '\0';
                j = 0;
                writing_to_hex_file(fs, d, h);
              }
              h[j++] = s[i + 3];
              h[j++] = s[i + 4];
              // h[j++] = '\0';
            }
          }
          i++;
        }
      }
      if ((strstr(s, "@R0,#") != NULL) || (strstr(s, "@r0,#") != NULL)) {
        if (j >= 32) {
          h[j] = '\0';
          j = 0;
          writing_to_hex_file(fs, d, h);
        }
        h[j++] = '7';
        h[j++] = '6';
        printf("%s", hu);
        int i = 0;
        while (s[i]) {
          if (s[i] == '#') {
            if ((s[i + 2] != 'x') && (s[i + 2] != 'X')) {
              if (j >= 32) {
                h[j] = '\0';
                j = 0;
                writing_to_hex_file(fs, d, h);
              }
              h[j++] = s[i + 1];
              h[j++] = s[i + 2];
              // h[j++] = '\0';
            } else {
              if (j >= 32) {
                h[j] = '\0';
                j = 0;
                writing_to_hex_file(fs, d, h);
              }
              h[j++] = s[i + 3];
              h[j++] = s[i + 4];
              // h[j++] = '\0';
            }
          }
          i++;
        }
      }
      if ((strstr(s, "@R1,#") != NULL) || (strstr(s, "@r1,#") != NULL)) {
        if (j >= 32) {
          h[j] = '\0';
          j = 0;
          writing_to_hex_file(fs, d, h);
        }
        h[j++] = '7';
        h[j++] = '7';
        int i = 0;
        while (s[i]) {
          if (s[i] == '#') {
            if ((s[i + 2] != 'x') && (s[i + 2] != 'X')) {
              if (j >= 32) {
                h[j] = '\0';
                j = 0;
                writing_to_hex_file(fs, d, h);
              }
              h[j++] = s[i + 1];
              h[j++] = s[i + 2];
              // h[j++] = '\0';
            } else {
              if (j >= 32) {
                h[j] = '\0';
                j = 0;
                writing_to_hex_file(fs, d, h);
              }
              h[j++] = s[i + 3];
              h[j++] = s[i + 4];
              // h[j++] = '\0';
            }
          }
          i++;
        }
      }
      if (((strstr(s, "R0,#") != NULL) || (strstr(s, "r0,#") != NULL)) &&
          ((strstr(s, "@R0,#") == NULL) && (strstr(s, "@r0,#") == NULL))) {
        if (j >= 32) {
          h[j] = '\0';
          j = 0;
          writing_to_hex_file(fs, d, h);
        }
        h[j++] = '7';
        h[j++] = '8';
        int i = 0;
        while (s[i]) {
          if (s[i] == '#') {
            if ((s[i + 2] != 'x') && (s[i + 2] != 'X')) {
              if (j >= 32) {
                h[j] = '\0';
                j = 0;
                writing_to_hex_file(fs, d, h);
              }
              h[j++] = s[i + 1];
              h[j++] = s[i + 2];
              // h[j++] = '\0';
            } else {
              if (j >= 32) {
                h[j] = '\0';
                j = 0;
                writing_to_hex_file(fs, d, h);
              }
              h[j++] = s[i + 3];
              h[j++] = s[i + 4];
              // h[j++] = '\0';
            }
          }
          i++;
        }
      }
      if ((strstr(s, "R1,#") != NULL) || (strstr(s, "r1,#") != NULL)) {
        if (j >= 32) {
          h[j] = '\0';
          j = 0;
          writing_to_hex_file(fs, d, h);
        }
        h[j++] = '7';
        h[j++] = '9';
        int i = 0;
        while (s[i]) {
          if (s[i] == '#') {
            if ((s[i + 2] != 'x') && (s[i + 2] != 'X')) {
              if (j >= 32) {
                h[j] = '\0';
                j = 0;
                writing_to_hex_file(fs, d, h);
              }
              h[j++] = s[i + 1];
              h[j++] = s[i + 2];
              // h[4] = '\0';
            } else {
              if (j >= 32) {
                h[j] = '\0';
                j = 0;
                writing_to_hex_file(fs, d, h);
              }
              h[j++] = s[i + 3];
              h[j++] = s[i + 4];
              // h[4] = '\0';
            }
          }
          i++;
        }
      }
      if ((strstr(s, "R2,#") != NULL) || (strstr(s, "r2,#") != NULL)) {
        if (j >= 32) {
          h[j] = '\0';
          j = 0;
          writing_to_hex_file(fs, d, h);
        }
        h[j++] = '7';
        h[j++] = 'A';
        int i = 0;
        while (s[i]) {
          if (s[i] == '#') {
            if ((s[i + 2] != 'x') && (s[i + 2] != 'X')) {
              if (j >= 32) {
                h[j] = '\0';
                j = 0;
                writing_to_hex_file(fs, d, h);
              }
              h[j++] = s[i + 1];
              h[j++] = s[i + 2];
              // h[4] = '\0';
            } else {
              if (j >= 32) {
                h[j] = '\0';
                j = 0;
                writing_to_hex_file(fs, d, h);
              }
              h[j++] = s[i + 3];
              h[j++] = s[i + 4];
              // h[4] = '\0';
            }
          }
          i++;
        }
      }
      if ((strstr(s, "R3,#") != NULL) || (strstr(s, "r3,#") != NULL)) {
        if (j >= 32) {
          h[j] = '\0';
          j = 0;
          writing_to_hex_file(fs, d, h);
        }
        h[j++] = '7';
        h[j++] = 'B';
        int i = 0;
        while (s[i]) {
          if (s[i] == '#') {
            if ((s[i + 2] != 'x') && (s[i + 2] != 'X')) {
              if (j >= 32) {
                h[j] = '\0';
                j = 0;
                writing_to_hex_file(fs, d, h);
              }
              h[j++] = s[i + 1];
              h[j++] = s[i + 2];
              // h[4] = '\0';
            } else {
              if (j >= 32) {
                h[j] = '\0';
                j = 0;
                writing_to_hex_file(fs, d, h);
              }
              h[j++] = s[i + 3];
              h[j++] = s[i + 4];
              // h[4] = '\0';
            }
          }
          i++;
        }
      }
      if ((strstr(s, "R4,#") != NULL) || (strstr(s, "r4,#") != NULL)) {
        if (j >= 32) {
          h[j] = '\0';
          j = 0;
          writing_to_hex_file(fs, d, h);
        }
        h[j++] = '7';
        h[j++] = 'C';
        int i = 0;
        while (s[i]) {
          if (s[i] == '#') {
            if ((s[i + 2] != 'x') && (s[i + 2] != 'X')) {
              if (j >= 32) {
                h[j] = '\0';
                j = 0;
                writing_to_hex_file(fs, d, h);
              }
              h[j++] = s[i + 1];
              h[j++] = s[i + 2];
              // h[4] = '\0';
            } else {
              if (j >= 32) {
                h[j] = '\0';
                j = 0;
                writing_to_hex_file(fs, d, h);
              }
              h[j++] = s[i + 3];
              h[j++] = s[i + 4];
              // h[4] = '\0';
            }
          }
          i++;
        }
      }
      if ((strstr(s, "R5,#") != NULL) || (strstr(s, "r5,#") != NULL)) {
        if (j >= 32) {
          h[j] = '\0';
          j = 0;
          writing_to_hex_file(fs, d, h);
        }
        h[j++] = '7';
        h[j++] = 'D';
        int i = 0;
        while (s[i]) {
          if (s[i] == '#') {
            if ((s[i + 2] != 'x') && (s[i + 2] != 'X')) {
              if (j >= 32) {
                h[j] = '\0';
                j = 0;
                writing_to_hex_file(fs, d, h);
              }
              h[j++] = s[i + 1];
              h[j++] = s[i + 2];
              // h[4] = '\0';
            } else {
              if (j >= 32) {
                h[j] = '\0';
                j = 0;
                writing_to_hex_file(fs, d, h);
              }
              h[j++] = s[i + 3];
              h[j++] = s[i + 4];
              h[j++] = '\0';
            }
          }
          i++;
        }
      }
      if ((strstr(s, "R6,#") != NULL) || (strstr(s, "r6,#") != NULL)) {
        if (j >= 32) {
          h[j] = '\0';
          j = 0;
          writing_to_hex_file(fs, d, h);
        }
        h[j++] = '7';
        h[j++] = 'E';
        int i = 0;
        while (s[i]) {
          if (s[i] == '#') {
            if ((s[i + 2] != 'x') && (s[i + 2] != 'X')) {
              if (j >= 32) {
                h[j] = '\0';
                j = 0;
                writing_to_hex_file(fs, d, h);
              }
              h[j++] = s[i + 1];
              h[j++] = s[i + 2];
              // h[4] = '\0';
            } else {
              if (j >= 32) {
                h[j] = '\0';
                j = 0;
                writing_to_hex_file(fs, d, h);
              }
              h[j++] = s[i + 3];
              h[j++] = s[i + 4];
              // h[4] = '\0';
            }
          }
          i++;
        }
      }
      if ((strstr(s, "R7,#") != NULL) || (strstr(s, "r7,#") != NULL)) {
        if (j >= 32) {
          h[j] = '\0';
          j = 0;
          writing_to_hex_file(fs, d, h);
        }
        h[j++] = '7';
        h[j++] = 'F';
        int i = 0;
        while (s[i]) {
          if (s[i] == '#') {
            if ((s[i + 2] != 'x') && (s[i + 2] != 'X')) {
              if (j >= 32) {
                h[j] = '\0';
                j = 0;
                writing_to_hex_file(fs, d, h);
              }
              h[j++] = s[i + 1];
              h[j++] = s[i + 2];
              // h[4] = '\0';
            } else {
              if (j >= 32) {
                h[j] = '\0';
                j = 0;
                writing_to_hex_file(fs, d, h);
              }
              h[j++] = s[i + 3];
              h[j++] = s[i + 4];
              // h[j++] = '\0';
            }
          }
          i++;
        }
      }
      if ((strstr(s, "0,@") != NULL) || (strstr(s, "1,@") != NULL) ||
          (strstr(s, "2,@") != NULL) || (strstr(s, "3,@") != NULL) ||
          (strstr(s, "4,@") != NULL) || (strstr(s, "5,@") != NULL) ||
          (strstr(s, "6,@") != NULL) || (strstr(s, "7,@") != NULL) ||
          (strstr(s, "8,@") != NULL) || (strstr(s, "9,@") != NULL) ||
          (strstr(s, "B,@") != NULL) || (strstr(s, "C,@") != NULL) ||
          (strstr(s, "D,@") != NULL) || (strstr(s, "E,@") != NULL) ||
          (strstr(s, "F,@") != NULL) || (strstr(s, "a,@") != NULL) ||
          (strstr(s, "b,@") != NULL) || (strstr(s, "c,@") != NULL) ||
          (strstr(s, "d,@") != NULL) || (strstr(s, "e,@") != NULL) ||
          (strstr(s, "0A,@") != NULL) || (strstr(s, "1A,@") != NULL) ||
          (strstr(s, "2A,@") != NULL) || (strstr(s, "3A,@") != NULL) ||
          (strstr(s, "4A,@") != NULL) || (strstr(s, "5A,@") != NULL) ||
          (strstr(s, "6A,@") != NULL) || (strstr(s, "7A,@") != NULL) ||
          (strstr(s, "8A,@") != NULL) || (strstr(s, "9A,@") != NULL) ||
          (strstr(s, "AA,@") != NULL) || (strstr(s, "BA,@") != NULL) ||
          (strstr(s, "CA,@") != NULL) || (strstr(s, "DA,@") != NULL) ||
          (strstr(s, "EA,@") != NULL) || (strstr(s, "FA,@") != NULL) ||
          (strstr(s, "aA,@") != NULL) || (strstr(s, "bA,@") != NULL) ||
          (strstr(s, "cA,@") != NULL) || (strstr(s, "dA,@") != NULL) ||
          (strstr(s, "eA,@") != NULL) || (strstr(s, "fA,@") != NULL) ||
          (strstr(s, "0a,@") != NULL) || (strstr(s, "1a,@") != NULL) ||
          (strstr(s, "2a,@") != NULL) || (strstr(s, "3a,@") != NULL) ||
          (strstr(s, "4a,@") != NULL) || (strstr(s, "5a,@") != NULL) ||
          (strstr(s, "6a,@") != NULL) || (strstr(s, "7a,@") != NULL) ||
          (strstr(s, "8a,@") != NULL) || (strstr(s, "9a,@") != NULL) ||
          (strstr(s, "Aa,@") != NULL) || (strstr(s, "Ba,@") != NULL) ||
          (strstr(s, "Ca,@") != NULL) || (strstr(s, "Da,@") != NULL) ||
          (strstr(s, "Ea,@") != NULL) || (strstr(s, "Fa,@") != NULL) ||
          (strstr(s, "aa,@") != NULL) || (strstr(s, "ba,@") != NULL) ||
          (strstr(s, "ca,@") != NULL) || (strstr(s, "da,@") != NULL) ||
          (strstr(s, "ea,@") != NULL) || (strstr(s, "fa,@") != NULL) ||
          (strstr(s, "f,@") != NULL)) {

        if ((strstr(s, "@R0")) || (strstr(s, "@r0"))) {
          if (j >= 32) {
            h[j] = '\0';
            j = 0;
            writing_to_hex_file(fs, d, h);
          }
          h[j++] = '8';
          h[j++] = '6';
        }
        if ((strstr(s, "@R1")) || (strstr(s, "@r1"))) {
          if (j >= 32) {
            h[j] = '\0';
            j = 0;
            writing_to_hex_file(fs, d, h);
          }
          h[j++] = '8';
          h[j++] = '7';
        }
        int i = 0;
        while (s[i]) {
          if (s[i] == '@') {
            if (j >= 32) {
              h[j] = '\0';
              j = 0;
              writing_to_hex_file(fs, d, h);
            }
            h[j++] = s[i - 3];
            h[j++] = s[i - 2];
            // h[j++] = '\0';
          }
          i++;
        }
      }
      if ((strstr(s, "0,R") != NULL) || (strstr(s, "1,R") != NULL) ||
          (strstr(s, "2,R") != NULL) || (strstr(s, "3,R") != NULL) ||
          (strstr(s, "4,R") != NULL) || (strstr(s, "5,R") != NULL) ||
          (strstr(s, "6,R") != NULL) || (strstr(s, "7,R") != NULL) ||
          (strstr(s, "8,R") != NULL) || (strstr(s, "9,R") != NULL) ||
          (strstr(s, "B,R") != NULL) || (strstr(s, "C,R") != NULL) ||
          (strstr(s, "D,R") != NULL) || (strstr(s, "E,R") != NULL) ||
          (strstr(s, "F,R") != NULL) || (strstr(s, "a,R") != NULL) ||
          (strstr(s, "b,R") != NULL) || (strstr(s, "c,R") != NULL) ||
          (strstr(s, "d,R") != NULL) || (strstr(s, "e,R") != NULL) ||
          (strstr(s, "f,R") != NULL) || (strstr(s, "0,r") != NULL) ||
          (strstr(s, "1,r") != NULL) || (strstr(s, "2,r") != NULL) ||
          (strstr(s, "3,r") != NULL) || (strstr(s, "4,r") != NULL) ||
          (strstr(s, "5,r") != NULL) || (strstr(s, "6,r") != NULL) ||
          (strstr(s, "7,r") != NULL) || (strstr(s, "8,r") != NULL) ||
          (strstr(s, "C,r") != NULL) || (strstr(s, "D,r") != NULL) ||
          (strstr(s, "E,r") != NULL) || (strstr(s, "F,r") != NULL) ||
          (strstr(s, "c,r") != NULL) || (strstr(s, "d,r") != NULL) ||
          (strstr(s, "e,r") != NULL) || (strstr(s, "f,r") != NULL) ||
          (strstr(s, "9,r") != NULL) || (strstr(s, "0A,r") != NULL) ||
          (strstr(s, "fA,r") != NULL) || (strstr(s, "B,r") != NULL) ||
          (strstr(s, "a,r") != NULL) || (strstr(s, "0a,r") != NULL) ||
          (strstr(s, "fa,r") != NULL) || (strstr(s, "b,r") != NULL) ||
          (strstr(s, "0A,R") != NULL) || (strstr(s, "1A,R") != NULL) ||
          (strstr(s, "2A,R") != NULL) || (strstr(s, "3A,R") != NULL) ||
          (strstr(s, "4A,R") != NULL) || (strstr(s, "5A,R") != NULL) ||
          (strstr(s, "6A,R") != NULL) || (strstr(s, "7A,R") != NULL) ||
          (strstr(s, "8A,R") != NULL) || (strstr(s, "9A,R") != NULL) ||
          (strstr(s, "AA,R") != NULL) || (strstr(s, "BA,R") != NULL) ||
          (strstr(s, "CA,R") != NULL) || (strstr(s, "DA,R") != NULL) ||
          (strstr(s, "EA,R") != NULL) || (strstr(s, "FA,R") != NULL) ||
          (strstr(s, "aA,R") != NULL) || (strstr(s, "bA,R") != NULL) ||
          (strstr(s, "cA,R") != NULL) || (strstr(s, "dA,R") != NULL) ||
          (strstr(s, "eA,R") != NULL) || (strstr(s, "fA,R") != NULL) ||
          (strstr(s, "0a,R") != NULL) || (strstr(s, "1a,R") != NULL) ||
          (strstr(s, "2a,R") != NULL) || (strstr(s, "3a,R") != NULL) ||
          (strstr(s, "4a,R") != NULL) || (strstr(s, "5a,R") != NULL) ||
          (strstr(s, "6a,R") != NULL) || (strstr(s, "7a,R") != NULL) ||
          (strstr(s, "8a,R") != NULL) || (strstr(s, "9a,R") != NULL) ||
          (strstr(s, "Aa,R") != NULL) || (strstr(s, "Ba,R") != NULL) ||
          (strstr(s, "Ca,R") != NULL) || (strstr(s, "Da,R") != NULL) ||
          (strstr(s, "Ea,R") != NULL) || (strstr(s, "Fa,R") != NULL) ||
          (strstr(s, "aa,R") != NULL) || (strstr(s, "ba,R") != NULL) ||
          (strstr(s, "ca,R") != NULL) || (strstr(s, "da,R") != NULL) ||
          (strstr(s, "ea,R") != NULL) || (strstr(s, "fa,R") != NULL) ||
          (strstr(s, "1A,r") != NULL) || (strstr(s, "2A,r") != NULL) ||
          (strstr(s, "3A,r") != NULL) || (strstr(s, "4A,r") != NULL) ||
          (strstr(s, "5A,r") != NULL) || (strstr(s, "6A,r") != NULL) ||
          (strstr(s, "7A,r") != NULL) || (strstr(s, "8A,r") != NULL) ||
          (strstr(s, "9A,r") != NULL) || (strstr(s, "AA,r") != NULL) ||
          (strstr(s, "BA,r") != NULL) || (strstr(s, "CA,r") != NULL) ||
          (strstr(s, "DA,r") != NULL) || (strstr(s, "EA,r") != NULL) ||
          (strstr(s, "FA,r") != NULL) || (strstr(s, "aA,r") != NULL) ||
          (strstr(s, "bA,r") != NULL) || (strstr(s, "cA,r") != NULL) ||
          (strstr(s, "dA,r") != NULL) || (strstr(s, "eA,r") != NULL) ||
          (strstr(s, "1a,r") != NULL) || (strstr(s, "2a,r") != NULL) ||
          (strstr(s, "3a,r") != NULL) || (strstr(s, "4a,r") != NULL) ||
          (strstr(s, "5a,r") != NULL) || (strstr(s, "6a,r") != NULL) ||
          (strstr(s, "7a,r") != NULL) || (strstr(s, "8a,r") != NULL) ||
          (strstr(s, "9a,r") != NULL) || (strstr(s, "Aa,r") != NULL) ||
          (strstr(s, "Ba,r") != NULL) || (strstr(s, "Ca,r") != NULL) ||
          (strstr(s, "Da,r") != NULL) || (strstr(s, "Ea,r") != NULL) ||
          (strstr(s, "Fa,r") != NULL) || (strstr(s, "aa,r") != NULL) ||
          (strstr(s, "ba,r") != NULL) || (strstr(s, "ca,r") != NULL) ||
          (strstr(s, "da,r") != NULL) || (strstr(s, "ea,r") != NULL)) {

        if ((strstr(s, "R0")) || (strstr(s, "r0"))) {
          if (j >= 32) {
            h[j] = '\0';
            j = 0;
            writing_to_hex_file(fs, d, h);
          }
          h[j++] = '8';
          h[j++] = '8';
        }
        if ((strstr(s, "R1")) || (strstr(s, "r1"))) {
          if (j >= 32) {
            h[j] = '\0';
            j = 0;
            writing_to_hex_file(fs, d, h);
          }
          h[j++] = '8';
          h[j++] = '9';
        }
        if ((strstr(s, "R2")) || (strstr(s, "r2"))) {
          if (j >= 32) {
            h[j] = '\0';
            j = 0;
            writing_to_hex_file(fs, d, h);
          }
          h[j++] = '8';
          h[j++] = 'A';
        }
        if ((strstr(s, "R3")) || (strstr(s, "r3"))) {
          if (j >= 32) {
            h[j] = '\0';
            j = 0;
            writing_to_hex_file(fs, d, h);
          }
          h[j++] = '8';
          h[j++] = 'B';
        }
        if ((strstr(s, "R4")) || (strstr(s, "r4"))) {
          if (j >= 32) {
            h[j] = '\0';
            j = 0;
            writing_to_hex_file(fs, d, h);
          }
          h[j++] = '8';
          h[j++] = 'C';
        }
        if ((strstr(s, "R5")) || (strstr(s, "r5"))) {
          if (j >= 32) {
            h[j] = '\0';
            j = 0;
            writing_to_hex_file(fs, d, h);
          }
          h[j++] = '8';
          h[j++] = 'D';
        }
        if ((strstr(s, "R6")) || (strstr(s, "r6"))) {
          if (j >= 32) {
            h[j] = '\0';
            j = 0;
            writing_to_hex_file(fs, d, h);
          }
          h[j++] = '8';
          h[j++] = 'E';
        }
        if ((strstr(s, "R7")) || (strstr(s, "r7"))) {
          if (j >= 32) {
            h[j] = '\0';
            j = 0;
            writing_to_hex_file(fs, d, h);
          }
          h[j++] = '8';
          h[j++] = 'F';
        }
        int i = 0;
        while (s[i]) {
          if (s[i] == '@') {
            if (j >= 32) {
              h[j] = '\0';
              j = 0;
              writing_to_hex_file(fs, d, h);
            }
            h[j++] = s[i - 3];
            h[j++] = s[i - 2];
            // h[4] = '\0';
          }
          i++;
        }
      }
    }
  }
  h[j] = '\0';
  writing_to_hex_file(fs, d, h);
  char *g = ":00000001FF";
  fputs(g, fs);
}
