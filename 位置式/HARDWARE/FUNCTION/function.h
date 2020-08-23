#ifndef __FUNCTION_H
#define __FUNCTION_H


#include "pid.h"
#include "sys.h"
#include "lcd.h"
#include "24cxx.h"	 
#include "delay.h"
#include "main.h"

//void SetCycleNum(int CycleNum,u8 IsStorage);
void SetCycleNum(int CycleNum);
void SetDirection(u8 dir);
void SetPNum(u16 ParaNum,u8 count);
void SetINum(u16 ParaNum,u8 count);
void SetDNum(u16 ParaNum,u8 count);
void ReadParameter(u8 YoN);
#endif
