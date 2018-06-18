#ifndef OW_H
#define OW_H

// DDRD  sets digital pins INPUT/OUTPUT
// PORTD sets digital pins HIGH/LOW
#define OW_LOGIC_ZERO PORTD &= ~(1 << PIND5); DDRD |= 1 << PIND5
#define OW_LOGIC_ONE DDRD &= ~(1 << PIND5); PORTD |= 1 << PIND5

#define OW_CMD_READ 0x33
#define OW_CMD_WRITE 0xD5
#define OW_CMD_UNLOCK 0xD1

int ow_read(char* reply_buffer);
int ow_write(uint8_t* key);
int ow_send_byte(uint8_t byte);
uint8_t ow_receive_byte();
int ow_write_byte(uint8_t byte);
void ow_reset();
char num_to_hex(int num);

#endif