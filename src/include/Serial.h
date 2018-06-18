#ifndef SERIAL_H
#define SERIAL_H

void serial_init();
int serial_write(char c, FILE *stream);
int serial_read(FILE *stream);

FILE serial_output = FDEV_SETUP_STREAM(serial_write, NULL, _FDEV_SETUP_WRITE);
FILE serial_input = FDEV_SETUP_STREAM(NULL, serial_read, _FDEV_SETUP_READ);


#endif
