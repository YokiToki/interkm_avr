#ifndef CMD_H
#define CMD_H

typedef struct {
    const char* name;
    int (*exec)(char* reply_buffer, int reply_buffer_size, int argc, char *argv[]);
} cmd_t;

cmd_t *CMD;
int CMD_COUNT;
char* READ_BUFFER;
char* WRITE_BUFFER;
int READ_BUFFER_SIZE;
int WRITE_BUFFER_SIZE;
void cmd_setup(cmd_t* cmd_collection, int cmd_collection_size, char* read_buffer, 
    int read_buffer_size, char* write_buffer, int write_buffer_size);
void cmd_listen();
int cmd_check(char* buffer, int buffer_size, char* reply_buffer, int reply_buffer_size);
int cmd_run(char* buffer, char* reply_buffer, int reply_buffer_size);
int cmd_json_reply(int status, char* cmd, char* reply_buffer);

#endif