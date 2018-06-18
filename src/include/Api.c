#include <stdio.h>
#include <string.h>
#include "1Wire.h"

int read(char* reply_buffer, int reply_buffer_size, int argc, char *argv[]) {
    ow_read(reply_buffer);
    return strlen(reply_buffer);
}

int write(char* reply_buffer, int reply_buffer_size, int argc, char *argv[]) {
    if(argc < 2) {
        strcpy(reply_buffer, "Arguments required");
        return -1;
    }

    // Проверка длины строки и на наличие только разрешенных символов
    if (strlen(argv[1]) != 23 || argv[1][strspn(argv[1], "0123456789ABCDEF:")] != 0x00)
    {
        strcpy(reply_buffer, "Invalid argument");
        return -1;
    }

    uint8_t key[8];
    int length = strlen(argv[1]);
    int i = 0;
    while(i * 3 < length) {
        unsigned int val;
        sscanf(argv[1] + i * 3, "%x", &val);
        key[i] = val;
        i++;
    }
    ow_write(key);
    ow_read(reply_buffer);

    return strlen(reply_buffer);
}