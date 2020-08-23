#ifndef __PID_H
#define __PID_H

#include "sys.h"
#include "usart.h"

void IncPIDInit(void);
int IncPIDCalc(int NextPoint);
unsigned int LocPIDCalc(int NextPoint);

/* ˽�к궨�� ----------------------------------------------------------------*/
/*************************************/
//����PID��غ�
// �����������趨�Ե������Ӱ��ǳ���
/*************************************/

/*#define  P_DATA      0.18                             //P����
#define  I_DATA      0.05                            //I����
#define  D_DATA      0.1    
*/


/* ˽�����Ͷ��� --------------------------------------------------------------*/
//����PID�ṹ��
typedef struct 
{
  __IO int      SetPoint;                                 //�趨Ŀ�� Desired Value
  __IO long     SumError;                                 //����ۼ�
  __IO double   Proportion;                               //�������� Proportional Const
  __IO double   Integral;                                 //���ֳ��� Integral Const
  __IO double   Derivative;                               //΢�ֳ��� Derivative Const
  __IO int      LastError;                                //Error[-1]
  __IO int      PrevError;                                //Error[-2]
}PID;

#ifndef __PID_C
extern  PID sPID;
extern  PID *sptr ;

extern double  P_DATA            ;                       //P����
extern double  I_DATA             ;                     //I����
extern double  D_DATA          ;
#endif

#endif

