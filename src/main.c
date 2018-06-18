#include "main.h"

char read_buffer[READ_BUFFER_SIZE+1];
char write_buffer[WRITE_BUFFER_SIZE];

int main(void)
{
    cmd_t cmd_read = {
        "read",
        &read
    };

    cmd_t cmd_write = {
        "write",
        &write
    };

    cmd_t cmd_collection[] = {cmd_read, cmd_write};

    int cmd_collection_size = sizeof(cmd_collection)/sizeof(cmd_t);

    cmd_setup(cmd_collection, cmd_collection_size,
            read_buffer, READ_BUFFER_SIZE,
            write_buffer, WRITE_BUFFER_SIZE);

    serial_init();

    stdout = &serial_output;
    stdin  = &serial_input;
  
    while(1) {
        cmd_listen();
    }

    return 0;
}
