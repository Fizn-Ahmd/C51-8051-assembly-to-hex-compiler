#include<stdio.h>
#include"asmtohex.h"

// This funtion does the strcpy operation //
void copy(char *src, char *dest)
{
    while(*dest) {
        *src = *dest;
        dest++;
        src++;
    }
    *src = *dest;
}

// Removing Spaces if there are any in asaembly file //
void converting_read_lines_from_asm_file(char *str)
{
    while(*str) {
        if(*str == ' ') {
            copy(str, str+1);
            str--;
        }
        str++;
    }
}

// This funtion reverse the given string //
void str_rev(char *str)
{
    char temp, *str2 = str;
    while(*str2)
        str2++;
    str2--;
    while(str < str2) {
        temp = *str2;
        *str2 = *str;
        *str = temp;
        str++;
        str2--;
    }
}

// This funtion coverts the string hexadecimal to integer. eg: '0A' is converted to 10. // 
int converting_string_to_integer(char *str) {
    int i = 0, num = 0;
    while(str[i]) {
        if(str[i] >= '0' && str[i] <= '9') {
            num = (str[i] - 48) | num<<4;
        }
        if(str[i] >= 'A' && str[i] <= 'F') {
            num = (str[i] - 55) | num<<4;
        }
        i++;
    }
    return num;
}

// THis funtion return the sum of array //
int sum(int *arr, int c) {
    int sum = c, i = 0;
    i = 0;
    while(arr[i] != -1) {
        sum = sum + arr[i];
        i++;
    }
    return sum;
}

// Calculating the checksum //
char checksum(char *p, char *q) {
    char s[3], ch;
    int a[40], count = 0;
    int i = 0, j = 0, k = 0;
    while(p[i]) {
        s[j] = p[i];
        j++;
        i++;
        if(j == 2) {
            s[j] = '\0';
            j = 0;
            a[k] = converting_string_to_integer(s);
            k++;
        }
    }
    i=0;
    j=0;
    while(q[i]) {
        s[j] = q[i];
        j++;
        i++;
        if(j == 2) {
            s[j] = '\0';
            j = 0;
            a[k] = converting_string_to_integer(s);
            k++;
            count++;
        }
    }
    a[k] = -1;
    ch = sum(a, count);
    return ch;
}

void writing_to_hex_file(FILE *fs, char *d, char *h) {
    char ch;
    ch = checksum(d,h);
    ch = ~ch;
    ch = ch+1;
    char gi[3], gfx;
    gfx = ch >> 4 & 0x0f;
    if(gfx >=0 && gfx <=9)
        gi[0] = (ch >> 4 & 0x0f) + 48;
    else
        gi[0] = (ch >> 4 & 0x0f) + 55;
    gfx = ch & 0x0F;
    if(gfx >= 0 && gfx <= 9)
        gi[1] = (ch & 0x0F) + 48;
    else
        gi[1] = (ch & 0x0F) + 55;
    gi[2] = '\0';
    int i = 0, count = 0;
    while(h[i]) {
        if(i%2 == 0)
            count++;
        i++;
    }
    fputc(':',fs);
    if(count >= 0 && count <= 9) {
        fputc('0', fs);
        fputc(count+48, fs);
    }
    else if(count >= 10 && count <= 15) {
        fputc('0', fs);
        fputc(count+55, fs);
    }
    else {
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