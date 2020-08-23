
#include "pid.h"


#define __PID_C
PID sPID;
PID *sptr = &sPID;


double  P_DATA 	=     0.18  ;                           //P����
double  I_DATA  =    0.05    ;                        //I����
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

 /**************PID������ʼ��********************************/
void IncPIDInit(void) 
{
    sptr->LastError=0;            //Error[-1]
    sptr->PrevError=0;            //Error[-2]
    sptr->Proportion=P_DATA;      //�������� Proportional Const
    sptr->Integral=I_DATA;        //���ֳ���  Integral Const
    sptr->Derivative=D_DATA;      //΢�ֳ��� Derivative Const
    sptr->SetPoint=134;           //�趨Ŀ��Desired Value
		sptr->SumError = 0;
	
}
/********************����ʽPID�������************************************/
int IncPIDCalc(int NextPoint) 
{
  int iError,iIncpid;                                 //��ǰ���
  iError=sptr->SetPoint-NextPoint;                    //��������
		
  iIncpid=(sptr->Proportion * iError)                 //E[k]��
              -(sptr->Integral * sptr->LastError)     //E[k-1]��
              +(sptr->Derivative * sptr->PrevError);  //E[k-2]��
              
  sptr->PrevError=sptr->LastError;                    //�洢�������´μ���
  sptr->LastError=iError;
  return(iIncpid);                                    //��������ֵ
}
/********************λ��ʽ PID �������************************************/
unsigned int LocPIDCalc(int NextPoint)
{
  int iError,dError;
  iError = sptr->SetPoint - NextPoint; //ƫ��

  sptr->SumError += iError; //����	
	
  dError = iError - sptr->LastError; //΢��
		
  sptr->LastError = iError;
  return(sptr->Proportion * iError //������
  + sptr->Integral * sptr->SumError //������
  + sptr->Derivative * dError); //΢����
}
