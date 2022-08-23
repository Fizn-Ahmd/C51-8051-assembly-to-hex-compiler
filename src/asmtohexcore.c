#include "../include/asmtohex.h"

#define MAX_ADDRESS_STRING_SIZE 5
#define MAX_CHAR_TO_READ_EACH_LINE 100

/*
 * core_convertion_algorithm(): This method is the responsible for generating
 * and updating the HEX code.
 *
 * @input_fs: Input file stream.
 * @output_fs: Output file stream
 */
void core_convertion_algorithm(FILE *input_fs, FILE *output_fs) {
  // TODO: make the size of input_str dynamic.
  char input_str[MAX_CHAR_TO_READ_EACH_LINE];
  char addr_str[MAX_ADDRESS_STRING_SIZE];
  char gen_hex_str[MAX_HEX_INDEX];
  int hex_index = 0;

  while ((fgets(input_str, MAX_CHAR_TO_READ_EACH_LINE, input_fs)) != NULL) {
    remove_spaces_in_string_buffer(input_str);
    // Convert the string to lower case as 8051 asm is not case sensitive.
    str_lower(input_str);
    // TODO: Remove Comments before starting the core algo
    // If 'end' is found exit the wile loop.
    if (strstr(input_str, "end") != NULL) {
      break;
    }

    if (strstr(input_str, "csegat") != NULL) {
      int i = 0, addr_index = 0;
      while (input_str[i]) {
        if (input_str[i] == 'x') {
          while (input_str[i]) {
            if ((input_str[i] >= '0' && input_str[i] <= '9')) {
              addr_str[addr_index++] = input_str[i++];
            } else if (input_str[i] >= 'a' && input_str[i] <= 'f') {
              addr_str[addr_index++] = input_str[i++];
            } else {
              i++;
            }
          }
        } else {
          i++;
        }
      }
      while (addr_index < MAX_ADDRESS_STRING_SIZE - 1) {
        addr_str[addr_index++] = '0';
      }
      addr_str[addr_index] = '\0';
      str_upper(addr_str);
    }

    if (strstr(input_str, "mov") != NULL) {
      if ((strstr(input_str, "a,#") != NULL) &&
          !check_if_not_accumulator(input_str)) {
        update_two_bytes(output_fs, gen_hex_str, input_str, addr_str,
                         &hex_index, '7', '4', '#');
      }
      if ((strstr(input_str, "r") == NULL) &&
          (check_condition(input_str, '#'))) {
        update_three_bytes(output_fs, gen_hex_str, input_str, addr_str,
                           &hex_index, '7', '5');
      }
      if (strstr(input_str, "@r0,#") != NULL) {
        update_two_bytes(output_fs, gen_hex_str, input_str, addr_str,
                         &hex_index, '7', '6', '#');
      }
      if (strstr(input_str, "@r1,#") != NULL) {
        update_two_bytes(output_fs, gen_hex_str, input_str, addr_str,
                         &hex_index, '7', '7', '#');
      }
      if ((strstr(input_str, "r0,#") != NULL) &&
          (strstr(input_str, "@r0,#") == NULL)) {
        update_two_bytes(output_fs, gen_hex_str, input_str, addr_str,
                         &hex_index, '7', '8', '#');
      }
      if (strstr(input_str, "r1,#") != NULL) {
        update_two_bytes(output_fs, gen_hex_str, input_str, addr_str,
                         &hex_index, '7', '9', '#');
      }
      if (strstr(input_str, "r2,#") != NULL) {
        update_two_bytes(output_fs, gen_hex_str, input_str, addr_str,
                         &hex_index, '7', 'A', '#');
      }
      if (strstr(input_str, "r3,#") != NULL) {
        update_two_bytes(output_fs, gen_hex_str, input_str, addr_str,
                         &hex_index, '7', 'B', '#');
      }
      if (strstr(input_str, "r4,#") != NULL) {
        update_two_bytes(output_fs, gen_hex_str, input_str, addr_str,
                         &hex_index, '7', 'C', '#');
      }
      if (strstr(input_str, "r5,#") != NULL) {
        update_two_bytes(output_fs, gen_hex_str, input_str, addr_str,
                         &hex_index, '7', 'D', '#');
      }
      if (strstr(input_str, "r6,#") != NULL) {
        update_two_bytes(output_fs, gen_hex_str, input_str, addr_str,
                         &hex_index, '7', 'E', '#');
      }
      if (strstr(input_str, "r7,#") != NULL) {
        update_two_bytes(output_fs, gen_hex_str, input_str, addr_str,
                         &hex_index, '7', 'F', '#');
      }
      if (check_condition(input_str, '@')) {
        if (strstr(input_str, "@r0")) {
          update_two_bytes(output_fs, gen_hex_str, input_str, addr_str,
                           &hex_index, '8', '6', '@');
        }
        if (strstr(input_str, "@r1")) {
          update_two_bytes(output_fs, gen_hex_str, input_str, addr_str,
                           &hex_index, '8', '7', '@');
        }
      }
      if (check_condition(input_str, 'r')) {
        if (strstr(input_str, "r0")) {
          update_two_bytes(output_fs, gen_hex_str, input_str, addr_str,
                           &hex_index, '8', '8', 'r');
        }
        if (strstr(input_str, "r1")) {
          update_two_bytes(output_fs, gen_hex_str, input_str, addr_str,
                           &hex_index, '8', '9', 'r');
        }
        if (strstr(input_str, "r2")) {
          update_two_bytes(output_fs, gen_hex_str, input_str, addr_str,
                           &hex_index, '8', 'A', 'r');
        }
        if (strstr(input_str, "r3")) {
          update_two_bytes(output_fs, gen_hex_str, input_str, addr_str,
                           &hex_index, '8', 'B', 'r');
        }
        if (strstr(input_str, "r4")) {
          update_two_bytes(output_fs, gen_hex_str, input_str, addr_str,
                           &hex_index, '8', 'C', 'r');
        }
        if (strstr(input_str, "r5")) {
          update_two_bytes(output_fs, gen_hex_str, input_str, addr_str,
                           &hex_index, '8', 'D', 'r');
        }
        if (strstr(input_str, "r6")) {
          update_two_bytes(output_fs, gen_hex_str, input_str, addr_str,
                           &hex_index, '8', 'E', 'r');
        }
        if (strstr(input_str, "r7")) {
          update_two_bytes(output_fs, gen_hex_str, input_str, addr_str,
                           &hex_index, '8', 'F', 'r');
        }
      }
    }
  }
  gen_hex_str[hex_index] = '\0';
  write_to_hex_file(output_fs, addr_str, gen_hex_str);
  char *g = ":00000001FF";
  fputs(g, output_fs);
}
