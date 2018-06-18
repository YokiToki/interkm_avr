#ifndef API_H
#define API_H

int read(char* reply_buffer, int reply_buffer_size, int argc, char *argv[]);
int write(char* reply_buffer, int reply_buffer_size, int argc, char *argv[]);

#endif