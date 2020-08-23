#ifndef __ENCODE_H__
#define __ENCODE_H__

#include "sys.h"

//void ENCODER_Init(u16 arr,u16 psc);
void TIM5_Cap_InitB(u16 arr,u16 psc);
void TIM4_Cap_InitA(u16 arr,u16 psc);
#ifndef _ENCODE_C
extern u16 CaptureNumberB ;					//捕获值B
extern u16 CaptureNumberA ;					//捕获值A
#endif

#endif
