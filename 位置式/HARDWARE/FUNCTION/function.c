

#include "function.h"
	u8 datamap1[1];
	 u8 dataPmap[1];
	 u8 dataImap[1];
	 u8 dataDmap[1];

void ReadParameter(u8 YoN)				////读取掉电保存的参数 1：读取  其它：不读取
{
	if(YoN == 1)
	{
		YoN = 0;
		if(AT24CXX_Check())
		{
			LCD_ShowString(200,700,200,16,16,"Not find");
		}
		else 
		{
			AT24CXX_Read(0,datamap1,1);
			AT24CXX_Read(2,dataPmap,1);
			AT24CXX_Read(3,dataImap,1);
			AT24CXX_Read(4,dataDmap,1);
			sptr->SetPoint = datamap1[0]*334/50;
			sptr->Proportion = (double)dataPmap[0]/100;
			sptr->Integral = (double)dataImap[0]/100;
			sptr->Derivative = (double)dataDmap[0]/100;
			LCD_ShowxNum(200,700,datamap1[0],2,16,0);
		}
	}
}
void SetDirection(u8 dir)					//设置方向  1:顺时针  2:逆时针
{
	if(dir==1)
	{
		clockwise();
	}
	if(dir==0)
	{
		anticlockwise();
	}
}
void SetPNum(u16 ParaNum,u8 count)        	//设置P参数    设置的参数 = ParaNum * 0.1的count次方
{
	u8 CurP_Buffer[1];
	double Num = 0;
	if(count == 1)
	{
		Num = ParaNum * 0.1;
	}
	else if(count == 2)
	{
		Num = ParaNum * 0.01;
	}
	else if(ParaNum == 0)
	{
		Num = ParaNum;
	}
	sptr->Proportion = Num;
	CurP_Buffer[0] = (u8)(Num*100);
		while(AT24CXX_Check())//检测不到24c02
	{
		LCD_ShowString(30,150,200,16,16,"24C02 Check Failed!");
		delay_ms(500);
		LCD_ShowString(30,150,200,16,16,"Please Check!      ");
		delay_ms(500);
	}
	LCD_Fill(150,460,170,280,WHITE); 
 
	AT24CXX_Write(2,(u8*)CurP_Buffer,1);
	
	delay_ms(20);
	AT24CXX_Read(2,dataPmap,1);
	LCD_ShowxNum(70,500,((double)dataPmap[0])/10,1,24,0);
	LCD_ShowxNum(90,500,(u8)((double)dataPmap[0])%10,1,24,0);
}
void SetINum(u16 ParaNum,u8 count)				//设置I参数
{
	u8 CurI_Buffer[1];
		double Num = 0;
	if(count == 1)
	{
		Num = ParaNum * 0.1;
	}
	else if(count == 2)
	{
		Num = ParaNum * 0.01;
	}
	else if(ParaNum == 0)
	{
		Num = ParaNum;
	}
	sptr->Integral = Num;
	CurI_Buffer[0] = (u8)(Num*100);
		while(AT24CXX_Check())//检测不到24c02
	{
		LCD_ShowString(30,150,200,16,16,"24C02 Check Failed!");
		delay_ms(500);
		LCD_ShowString(30,150,200,16,16,"Please Check!      ");
		delay_ms(500);
	}
	LCD_Fill(150,460,170,280,WHITE); 
 
	AT24CXX_Write(3,(u8*)CurI_Buffer,1);
	
	delay_ms(20);
	AT24CXX_Read(3,dataImap,1);
	LCD_ShowxNum(70,540,((double)dataImap[0])/10,1,24,0);
	LCD_ShowxNum(90,540,(u8)((double)dataImap[0])%10,1,24,0);
}
void SetDNum(u16 ParaNum,u8 count)					//设置D参数
{
	u8 CurD_Buffer[1];
		double Num = 0;
	if(count == 1)
	{
		Num = ParaNum * 0.1;
	}
	else if(count == 2)
	{
		Num = ParaNum * 0.01;
	}
	else if(ParaNum == 0)
	{
		Num = ParaNum;
	}
	sptr->Derivative = Num;
	CurD_Buffer[0] = (u8)(Num*100);
		while(AT24CXX_Check())//检测不到24c02
	{
		LCD_ShowString(30,150,200,16,16,"24C02 Check Failed!");
		delay_ms(500);
		LCD_ShowString(30,150,200,16,16,"Please Check!      ");
		delay_ms(500);
	}
	LCD_Fill(150,460,170,280,WHITE); 
 
	AT24CXX_Write(4,(u8*)CurD_Buffer,1);
	
	delay_ms(20);
	AT24CXX_Read(4,dataDmap,1);
	LCD_ShowxNum(70,580,((double)dataDmap[0])/10,1,24,0);
	LCD_ShowxNum(90,580,(u8)((double)dataDmap[0])%10,1,24,0);
}
void SetCycleNum(int CycleNum)						//设置转速
{
	u8 CurSpeed_Buffer[1];
	u16 SetPoint ;
	SetPoint = (CycleNum*334/50);
	sptr->SetPoint = SetPoint;
	CurSpeed_Buffer[0] = CycleNum;
		while(AT24CXX_Check())//检测不到24c02
	{
		LCD_ShowString(30,150,200,16,16,"24C02 Check Failed!");
		delay_ms(500);
		LCD_ShowString(30,150,200,16,16,"Please Check!      ");
		delay_ms(500);
	}
	LCD_Fill(150,460,170,280,WHITE);//清除
	AT24CXX_Write(0,(u8*)CurSpeed_Buffer,1);
	delay_ms(20);
	AT24CXX_Read(0,datamap1,1);
	LCD_ShowxNum(200,700,datamap1[0],2,16,0);

}
