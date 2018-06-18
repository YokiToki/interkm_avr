#include <avr/io.h>
#include <util/delay.h>
#include "1Wire.h"

int ow_read(char* reply_buffer)
{
    int byte, i = 0;
    uint8_t r_byte;

    DDRD &= ~(1 << PIND5); //set PD5 to input
    OW_LOGIC_ONE;

    ow_reset();

    ow_send_byte(OW_CMD_READ);

    for (byte = 0; byte < 8; byte++) {
        r_byte = ow_receive_byte();

        reply_buffer[i] = num_to_hex(r_byte/16);
        i++;
        reply_buffer[i] = num_to_hex(r_byte%16);
        i++;

        if (byte != 7) {
            reply_buffer[i] = ':';
            i++;
        }
    }

    reply_buffer[i++] = 0x00;

    return 0;
}

int ow_write(uint8_t* key)
{
    ow_reset();
    ow_send_byte(OW_CMD_UNLOCK);
    
    ow_reset();
    ow_send_byte(OW_CMD_WRITE);

    int byte;
    for (byte = 0; byte < 8; byte++){
        ow_write_byte(key[byte]);
    }

    ow_reset();
    ow_send_byte(OW_CMD_UNLOCK);

    return 0;
}

int ow_send_byte(uint8_t byte)
{
    int bit;

    for(bit=0; bit<8; bit++){
        if (byte & 1){
            OW_LOGIC_ZERO;
            _delay_us(8);
            OW_LOGIC_ONE;
            _delay_us(72);
        } else {
            OW_LOGIC_ZERO;
            _delay_us(72);
            OW_LOGIC_ONE;
            _delay_us(8);
        }

        byte >>= 1;
    }

    return 0;
}

uint8_t ow_receive_byte()
{
    int bit; 
    uint8_t byte=0;

    for(bit=0; bit<8; bit++){
        OW_LOGIC_ZERO;
        _delay_us(8);
        OW_LOGIC_ONE;
        _delay_us(8);

        if(PIND & 0x20)
            byte |= (1 << bit);

        _delay_us(32);
    }

    return byte;
}

int ow_write_byte(uint8_t byte)
{
    int bit;

    for (bit = 0; bit < 8; bit++){
        if (byte & 1){
            OW_LOGIC_ZERO;
            _delay_us(60);
            OW_LOGIC_ONE;
        } else {
            OW_LOGIC_ZERO;
            OW_LOGIC_ONE;
        }

        byte >>= 1;

        _delay_ms(10);
    }

    return 0;
}

void ow_reset()
{
    OW_LOGIC_ZERO;
    _delay_us(480);
    OW_LOGIC_ONE;
    _delay_us(100); // 120

    while (!bit_is_set(PIND,0)){}
    _delay_us(100);
}


char num_to_hex(int num)
{
    if ((num >= 0) && (num < 10)){
        return num + '0';
    }

    if ((num >= 9) && (num < 16)){
        return num - 10 + 'A';
    }

    return '?';
}
