
#include "pid.h"


#define __PID_C
PID sPID;
PID *sptr = &sPID;


double  P_DATA 	=     0.18  ;                           //P参数
double  I_DATA  =    0.05    ;                        //I参数
double  D_DATA  =    0.1    ;

void SetPID(u8 pid_num,double num)
{
	switch(pid_num)
	{
		case 1:sptr->Proportion = num;
		break;
		case 2:sptr->Integral = num;
		break;
		case 3:sptr->Derivative = num;
		break;
		default:break;
		}
}

 /**************PID参数初始化********************************/
void IncPIDInit(void) 
{
    sptr->LastError=0;            //Error[-1]
    sptr->PrevError=0;            //Error[-2]
    sptr->Proportion=P_DATA;      //比例常数 Proportional Const
    sptr->Integral=I_DATA;        //积分常数  Integral Const
    sptr->Derivative=D_DATA;      //微分常数 Derivative Const
    sptr->SetPoint=134;           //设定目标Desired Value
		sptr->SumError = 0;
	
}
/********************增量式PID控制设计************************************/
int IncPIDCalc(int NextPoint) 
{
  int iError,iIncpid;                                 //当前误差
  iError=sptr->SetPoint-NextPoint;                    //增量计算
		
  iIncpid=(sptr->Proportion * iError)                 //E[k]项
              -(sptr->Integral * sptr->LastError)     //E[k-1]项
              +(sptr->Derivative * sptr->PrevError);  //E[k-2]项
              
  sptr->PrevError=sptr->LastError;                    //存储误差，用于下次计算
  sptr->LastError=iError;
  return(iIncpid);                                    //返回增量值
}
/********************位置式 PID 控制设计************************************/
unsigned int LocPIDCalc(int NextPoint)
{
  int iError,dError;
  iError = sptr->SetPoint - NextPoint; //偏差

  sptr->SumError += iError; //积分	
	
  dError = iError - sptr->LastError; //微分
		
  sptr->LastError = iError;
  return(sptr->Proportion * iError //比例项
  + sptr->Integral * sptr->SumError //积分项
  + sptr->Derivative * dError); //微分项
}
