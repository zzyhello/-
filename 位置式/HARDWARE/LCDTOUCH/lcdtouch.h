#ifndef __LCDTOUCH_H
#define __LCDTOUCH_H

#include "main.h"
#include "sys.h"
#include "touch.h"
#include "lcd.h"
#include "delay.h"
#include "usart.h"
#include "pid.h"
#include "function.h"

void LcdTouch(void);


#ifndef __LCDTOUCH_C
extern u8 PNum[4];
extern u8 SetSpeedFlag ;
extern u8 CurPFlag ;
extern u8 CurIFlag ;
extern u8 CurDFlag ;
#endif

#endif
