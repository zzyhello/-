#ifndef __MAIN_H
#define __MAIN_H

#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "lcd.h"
#include "encode.h"
#include "usmart.h"
#include "pid.h"
#include "24cxx.h"	 
#include "touch.h"
#include "lcdtouch.h"

void anticlockwise(void);
void clockwise(void);

#ifndef __MAIN_C
extern uint8_t  start_flagB;
extern uint8_t  start_flagA;
#endif

#endif

