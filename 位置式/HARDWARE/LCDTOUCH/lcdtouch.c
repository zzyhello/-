#include "lcdtouch.h"
#define __LCDTOUCH_C

u8 num = 0;
double PatameterNum = 0;
u16 widthx = 240;
u8 PNum[4];
u8 SetSpeedFlag = 0;
u8 LFlag = 0;           
u8 i = 0;								//λ��
u8 Lcount = 0;					//С��λ��
u8 CurPFlag = 0;
u8 CurIFlag = 0;
u8 CurDFlag = 0;

//�����Ļ�������Ͻ���ʾ"RST"
void Load_Drow_Dialog(void)
{
	LCD_Clear(WHITE);	//����   
 	POINT_COLOR=BLUE;	//��������Ϊ��ɫ 
	LCD_ShowString(lcddev.width-24,0,200,16,16,"RST");//��ʾ��������
  	POINT_COLOR=RED;	//���û�����ɫ 
}
////////////////////////////////////////////////////////////////////////////////
//���ݴ�����ר�в���
//��ˮƽ��
//x0,y0:����
//len:�߳���
//color:��ɫ
void gui_draw_hline(u16 x0,u16 y0,u16 len,u16 color)
{
	if(len==0)return;
	LCD_Fill(x0,y0,x0+len-1,y0,color);	
}
//��ʵ��Բ
//x0,y0:����
//r:�뾶
//color:��ɫ
void gui_fill_circle(u16 x0,u16 y0,u16 r,u16 color)
{											  
	u32 i;
	u32 imax = ((u32)r*707)/1000+1;
	u32 sqmax = (u32)r*(u32)r+(u32)r/2;
	u32 x=r;
	gui_draw_hline(x0-r,y0,2*r,color);
	for (i=1;i<=imax;i++) 
	{
		if ((i*i+x*x)>sqmax)// draw lines from outside  
		{
 			if (x>imax) 
			{
				gui_draw_hline (x0-i+1,y0+x,2*(i-1),color);
				gui_draw_hline (x0-i+1,y0-x,2*(i-1),color);
			}
			x--;
		}
		// draw lines from inside (center)  
		gui_draw_hline(x0-x,y0+i,2*x,color);
		gui_draw_hline(x0-x,y0-i,2*x,color);
	}
}  
//������֮��ľ���ֵ 
//x1,x2����ȡ��ֵ��������
//����ֵ��|x1-x2|
u16 my_abs(u16 x1,u16 x2)
{			 
	if(x1>x2)return x1-x2;
	else return x2-x1;
}  
//��һ������
//(x1,y1),(x2,y2):��������ʼ����
//size�������Ĵ�ϸ�̶�
//color����������ɫ
void lcd_draw_bline(u16 x1, u16 y1, u16 x2, u16 y2,u8 size,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	if(x1<size|| x2<size||y1<size|| y2<size)return; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		gui_fill_circle(uRow,uCol,size,color);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}   

int NumScan(u16 x,u16 y)				//��ѡ�еĽ��к�ɫ������ʾ
{
		if(x>220&&x<275&&y>275&&y<515)
		{
			LCD_DrawRectangle(220,460,275,515);
			return 1;
		}
		else if(x>280&&x<335&&y>460&&y<515)
		{
			LCD_DrawRectangle(280,460,335,515);
			return 2;
		}
		else if(x>340&&x<395&&y>275&&y<515)
		{
			LCD_DrawRectangle(340,460,395,515);
			return 3;
		}
		else if(x>220&&x<275&&y>520&&y<575)
		{
			LCD_DrawRectangle(220,520,275,575);
			return 4;
		}
		else if(x>280&&x<335&&y>520&&y<575)
		{
			LCD_DrawRectangle(280,520,335,575);
			return 5;
		}
		else if(x>340&&x<395&&y>520&&y<575)
		{
			LCD_DrawRectangle(340,520,395,575);
			return 6;
		}
		else if(x>220&&x<275&&y>580&&y<635)
		{
			LCD_DrawRectangle(220,580,275,635);
			return 7;
		}
		else if(x>280&&x<335&&y>580&&y<635)
		{
			LCD_DrawRectangle(280,580,335,635);
			return 8;
		}
		else if(x>340&&x<395&&y>580&&y<635)
		{
			LCD_DrawRectangle(340,580,395,635);
			return 9;
		}
		else if(x>280&&x<335&&y>640&&y<695)
		{
			LCD_DrawRectangle(280,640,335,695);
			return 0;
		}
		else if(x>220&&x<275&&y>640&&y<695)         
		{
			LCD_DrawRectangle(220,640,275,695);
			return 10;                   //��ʱ��
		}
		else if(x>340&&x<395&&y>640&&y<695)
		{
			LCD_DrawRectangle(340,640,395,695);
			return 11;									//˳ʱ��
		}
		else if(x>400&&x<455&&y>460&&y<515)
		{
			LCD_DrawRectangle(400,460,455,515);
			return 12;									//ɾ��
		}
		else if(x>400&&x<455&&y>520&&y<575)
		{
			LCD_DrawRectangle(400,520,455,575);
			return 13;									//ȷ������
		}
		else if(x>400&&x<455&&y>580&&y<635)
		{
			LCD_DrawRectangle(400,580,455,635);
			return 14;									//ȷ������
		}
		else if(x>20&&x<170&&y>420&&y<440)
		{
			if(CurPFlag!=1&&CurIFlag!=1&&CurDFlag!=1&&SetSpeedFlag!=1)
			{
			LCD_DrawRectangle(15,410,175,450);	//ѡ���޸�ת��LCD_ShowString(20,420,200,16,24,"Set speed:");
			SetSpeedFlag = 1;
			}
		}
		else if(x>20&&x<150&&y>500&&y<520)
		{
			if(CurPFlag!=1&&CurIFlag!=1&&CurDFlag!=1&&SetSpeedFlag!=1)
			{
			LCD_DrawRectangle(15,490,160,530);
			CurPFlag = 1;											//LCD_ShowString(20,500,200,24,24,"P:");
			}
		}
		else if(x>20&&x<150&&y>540&&y<560)
		{
			if(CurPFlag!=1&&CurIFlag!=1&&CurDFlag!=1&&SetSpeedFlag!=1)
			{
			LCD_DrawRectangle(15,530,160,570);
			CurIFlag = 1;											//LCD_ShowString(20,540,200,24,24,"I:");
			}
		}
		else if(x>20&&x<150&&y>580&&y<600)
		{
			if(CurPFlag!=1&&CurIFlag!=1&&CurDFlag!=1&&SetSpeedFlag!=1)
			{
			LCD_DrawRectangle(15,570,160,610);
			CurDFlag = 1;											//LCD_ShowString(20,580,200,24,24,"D:");
			}
		}
		return 100;
}
void ChangeParameter(double Num)			//�������������ѡ�еĲ��������޸�
{
	int CurSpeedCom = 0;
	if(SetSpeedFlag == 1)
	{
		CurSpeedCom = (int)(Num * 334 / 50);
		sptr->SetPoint = CurSpeedCom;
		printf("sptr->SetPoint:%d",sptr->SetPoint);
		SetSpeedFlag = 0;
	}
	else if(CurPFlag == 1)
	{
		printf("P enter success\r\n");
		if((i-Lcount) == 1)
		{
			Num = Num*10;
		}
		else if((i-Lcount) == 2)
		{
			Num = Num*100;
		}
		SetPNum(Num,(i-Lcount));
		printf("P_DATA:%f\r\n",sptr->Proportion);
		CurPFlag = 0;
	}
	else if(CurIFlag == 1)
	{
		printf("I enter success\r\n");
		if((i-Lcount) == 1)
		{
			Num = Num*10;
		}
		else if((i-Lcount) == 2)
		{
			Num = Num*100;
		}
		SetINum(Num,(i-Lcount));
		printf("I_DATA:%f\r\n",sptr->Integral);
		CurIFlag = 0;
	}
	else if(CurDFlag == 1)
	{
		printf("D enter success\r\n");
		if((i-Lcount) == 1)
		{
			Num = Num*10;
		}
		else if((i-Lcount) == 2)
		{
			Num = Num*100;
		}
		SetDNum(Num,(i-Lcount));
		printf("D_DATA:%f\r\n",sptr->Derivative);
		CurDFlag = 0;
	}
}
void SetParameter(int parameter)				//�޸���ֵ������Ʒ���
{
	
	static u8 time = 0;
	static u8 count = 0; 
	if(time < 1)
	{
		time += 1;
	}
	else
	{
		time = 0;
		if((parameter<=9)&&(parameter>=0))
		{
			if(widthx<=300)
			{
				LCD_ShowxNum(widthx,420,parameter,1,24,0);
				PNum[i] = parameter;
				i++;
				widthx += 20;
				if(LFlag == 0)
				{
					PatameterNum = parameter + PatameterNum*10;
				}
				else if(LFlag == 1)
				{
					if(count == 0)
					{
						PatameterNum = ((double)parameter)/10 + PatameterNum;
						count++;
					}
					else if(count == 1)
					{
						PatameterNum = ((double)parameter)/100 + PatameterNum;
						count = 0;
					}
				}
			}
		}
		if(parameter == 10)       //��ʱ��
		{
			anticlockwise();
		}
		if(parameter == 11)       //˳ʱ��
		{
			clockwise();
		}
		if(parameter == 12)       //delete
		{
			
			if(widthx>240)
			{
				widthx -= 20;
				LCD_ShowxNum(widthx,420,0,1,24,0);
				if(i!=0)
				{
					i -= 1;
					if(PNum[i]==100)
					{
						LFlag = 0;
						count = 0;
					}
					if(LFlag==1)
					{
						if((i-Lcount)==0)
						{
							LFlag = 0;
							Lcount = 0;
						}
						else if((i-Lcount)==1)
						{
							PatameterNum = PatameterNum - PNum[i]*0.1;
						}
						else if((i-Lcount)==2)
						{
							PatameterNum = PatameterNum - PNum[i]*0.01;
						}
					}
					else if(LFlag==0)
					{
						PatameterNum = PatameterNum/10;
					}
					PNum[i]=0;
				}
			}
		}
		if(parameter == 13)   		//change
		{
			LFlag = 0;
			printf("PatameterNum;%f\r\n",PatameterNum);
			ChangeParameter(PatameterNum);
			PatameterNum = 0;
			LCD_ShowxNum(240,420,0,1,24,0);
			LCD_ShowxNum(260,420,0,1,24,0);
			LCD_ShowxNum(280,420,0,1,24,0);
			LCD_ShowxNum(300,420,0,1,24,0);
			PNum[0]=0;PNum[1]=0;PNum[2]=0;PNum[3]=0;
			widthx = 240;
			i = 0;
			count = 0;
		}
		if(parameter == 14)
		{
			if(Lcount == 0)
			{
				Lcount = i;
				LCD_ShowString(widthx,420,200,24,24,".");
					PNum[i] = 100;
					i++;
					widthx += 20;
				LFlag = 1;
			}
		}
	}
}
////////////////////////////////////////////////////////////////////////////////
 //5�����ص����ɫ												 
const u16 POINT_COLOR_TBL[CT_MAX_TOUCH]={RED,GREEN,BLUE,BROWN,GRED};  

//���ݴ��������Ժ���
void ctp_test(void)
{
	u8 t=0;
	u8 i=0;	  	    
 	u16 lastpos[5][2];		//��¼���һ�ε����� 

	tp_dev.scan(0);
		for(t=0;t<CT_MAX_TOUCH;t++)
		{
			if((tp_dev.sta)&(1<<t))
			{
				if(tp_dev.x[t]<lcddev.width&&tp_dev.y[t]<lcddev.height)
				{
					if(lastpos[t][0]==0XFFFF)
					{
						lastpos[t][0] = tp_dev.x[t];
						lastpos[t][1] = tp_dev.y[t];
					}
				//	lcd_draw_bline(lastpos[t][0],lastpos[t][1],tp_dev.x[t],tp_dev.y[t],2,POINT_COLOR_TBL[t]);//����
					lastpos[t][0]=tp_dev.x[t];
					lastpos[t][1]=tp_dev.y[t];
					if(tp_dev.x[t]>(lcddev.width-24)&&tp_dev.y[t]<16)				//�����Ͻ�����
					{
						Load_Drow_Dialog();//���
					}
					num = NumScan(tp_dev.x[t],tp_dev.y[t]);
					SetParameter(num);
				}
			}else lastpos[t][0]=0XFFFF;
		
		delay_ms(20);i++;

	}	
}


void LcdTouch()
{	

 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	delay_ms(150);	 	
	if(tp_dev.touchtype&0X80)ctp_test();	//����������
}




