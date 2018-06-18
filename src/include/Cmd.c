#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include "Cmd.h"

#define STATUS_OK 200
#define STATUS_BAD_REQUEST 400
#define STATUS_FORBIDDEN 403

void cmd_setup(cmd_t* cmd_collection, int cmd_collection_size, char* read_buffer, 
        int read_buffer_size, char* write_buffer, int write_buffer_size) {
    CMD = cmd_collection;
    CMD_COUNT = cmd_collection_size;
    READ_BUFFER = read_buffer;
    READ_BUFFER_SIZE = read_buffer_size;
    WRITE_BUFFER = write_buffer;
    WRITE_BUFFER_SIZE = write_buffer_size;
}

void cmd_listen() {
    int read_size = 0;

    while(!(read_size > 0 && READ_BUFFER[read_size-1] == '\n') && read_size < READ_BUFFER_SIZE) {
        READ_BUFFER[read_size] = getchar();
        read_size++;
    }

    if(read_size > 0 && cmd_check(READ_BUFFER, read_size, WRITE_BUFFER, WRITE_BUFFER_SIZE)) {
        puts(WRITE_BUFFER);
    }
}

int cmd_check(char* buffer, int buffer_size, char* reply_buffer, int reply_buffer_size) {
    buffer[buffer_size-1] = 0x00;

    int reply_size = cmd_run(buffer, reply_buffer, reply_buffer_size-2);

    if(reply_size > reply_buffer_size) {
        reply_size = -1;
    }
    
    return reply_size;
}

int cmd_run(char* buffer, char* reply_buffer, int reply_buffer_size) {
    reply_buffer[0] = 0x00;

    char* argv[3];
    int argc = 0;
    int reply_size = 0;
    int success = 0;
    int status;
    char* last;

    char* arg = strtok_r(buffer, " ", &last);

    while(arg != NULL && argc < 3) {
        argv[argc] = arg;
        argc++;
        arg = strtok_r(NULL, " ", &last);
    }

    int i;
    for(i = 0; i < CMD_COUNT && !success; i++) {
        if(strcmp(argv[0], CMD[i].name) == 0) {
            success = 1;
            reply_size = CMD[i].exec(reply_buffer, reply_buffer_size, argc, argv);
        }
    }

    if(success) {
        if(reply_size > 0) {
            status = STATUS_OK;
        } else {
            status = STATUS_FORBIDDEN;
        }
    } else {
        status = STATUS_BAD_REQUEST;
        strcpy(reply_buffer, "Bad request");
    }

    reply_size = cmd_json_reply(status, argv[0], reply_buffer);
    
    return reply_size;
}

int cmd_json_reply(int status, char* cmd, char* reply_buffer) {

    char buffer[WRITE_BUFFER_SIZE];

    sprintf(buffer, 
                "{\"status\":%d,\"cmd\":\"%s\",\"reply\":\"%s\"}", 
                status, cmd, reply_buffer);

    strcpy(reply_buffer, buffer);
    return strlen(reply_buffer);
}
