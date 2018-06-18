#ifndef _MAIN_H_
#define _MAIN_H_
#include <stdio.h>
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include "include/Serial.h"
#include "include/Cmd.h"
#include "include/1Wire.h"
#include "include/Api.h"

#define READ_BUFFER_SIZE 128
#define WRITE_BUFFER_SIZE 512

int main();

#endif