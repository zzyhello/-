#ifndef __PID_H
#define __PID_H

#include "sys.h"
#include "usart.h"

void IncPIDInit(void);
int IncPIDCalc(int NextPoint);
unsigned int LocPIDCalc(int NextPoint);

/* 私有宏定义 ----------------------------------------------------------------*/
/*************************************/
//定义PID相关宏
// 这三个参数设定对电机运行影响非常大
/*************************************/

/*#define  P_DATA      0.18                             //P参数
#define  I_DATA      0.05                            //I参数
#define  D_DATA      0.1    
*/


/* 私有类型定义 --------------------------------------------------------------*/
//定义PID结构体
typedef struct 
{
  __IO int      SetPoint;                                 //设定目标 Desired Value
  __IO long     SumError;                                 //误差累计
  __IO double   Proportion;                               //比例常数 Proportional Const
  __IO double   Integral;                                 //积分常数 Integral Const
  __IO double   Derivative;                               //微分常数 Derivative Const
  __IO int      LastError;                                //Error[-1]
  __IO int      PrevError;                                //Error[-2]
}PID;

#ifndef __PID_C
extern  PID sPID;
extern  PID *sptr ;

extern double  P_DATA            ;                       //P参数
extern double  I_DATA             ;                     //I参数
extern double  D_DATA          ;
#endif

#endif

