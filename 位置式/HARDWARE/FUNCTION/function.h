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
void SetPNum(u16 ParaNum,u8 count);       // 设置的参数 = ParaNum * 0.1的count次方
void SetINum(u16 ParaNum,u8 count);
void SetDNum(u16 ParaNum,u8 count);
void ReadParameter(u8 YoN);								////读取掉电保存的参数 1：读取  其它：不读取
#endif
