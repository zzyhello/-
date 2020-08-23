#include "main.h"

void LCD_Map(void);
double CycleNumber = 0;

/* 私有变量 ------------------------------------------------------------------*/
uint16_t time_count=0;        // 时间计数，每20ms增加一
//uint32_t CaptureNumber=0;     // 输入捕获数
uint8_t  start_flag=0;
uint8_t  start_flagB=0;
uint8_t  start_flagA=0;
double encoder_speed=0;

int compareB = 200;
int compareA = 200;

u16 Xco1[430];
u16 Yco1[430];
u16 Xmid[5];
u16 Ymid[5];
double cycleNumber1 = 0;

TIM_OCInitTypeDef TIM_OCInitStrue;
 int main(void)
 {		
	vu8 key=0;	
	delay_init();	    	 //延时函数初始化pi	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200
	KEY_Init();
	LCD_Init();			 	 //LCD初始化
	 
 	TIM1_PWM_Init(899,0);	 //不分频。PWM频率=72000000/900=80Khz
 	TIM8_PWM_Init(899,0);	 //不分频。PWM频率=72000000/900=80Khz

	 
	TIM5_Cap_InitB(0XFFFF,72-1);	//以1Mhz的频率计数 
	TIM4_Cap_InitA(0XFFFF,72-1);
	 
	 //TIM3_Int_Init(4999,7199); //500ms
	TIM3_Int_Init(399,3599);  //20ms
	 
	IncPIDInit();
	 
	usmart_dev.init(SystemCoreClock/1000000);

  start_flag=1; 
	start_flagA=1; 
	start_flagB=0;
	 LCD_Map();
	 
	  	tp_dev.init();       //usmart

	 
	 AT24CXX_Init();			//IIC初始化 
	 
	POINT_COLOR=RED;//设置字体为红色 

		LCD_ShowxNum(240,420,0,1,24,0);
		LCD_ShowxNum(260,420,0,1,24,0);
		LCD_ShowxNum(280,420,0,1,24,0);
		LCD_ShowxNum(300,420,0,1,24,0);
		PNum[0]=0;PNum[1]=0;PNum[2]=0;PNum[3]=0;
		
   	while(1)
	{					
		key=KEY_Scan(0);	//得到键值
		
		LcdTouch();
	   	if(key)
		{						   
			switch(key)
			{				 
				case WKUP_PRES:	//提高转速
					sptr->SetPoint = sptr->SetPoint + 334/25;           //设定目标Desired Value     
					break;
				case KEY2_PRES:	//逆时针
					anticlockwise();
					break;
				case KEY1_PRES:	//降低转速 
					sptr->SetPoint = sptr->SetPoint - 334/50 ;
					break;
				case KEY0_PRES: //顺时针
					clockwise();
					break;
			}
		}
		delay_ms(10);
	}	 
}	 
 void anticlockwise()			////逆时针
{
	if(	start_flagA!=1)
	{
	TIM_SetCompare1(TIM1,0);
	delay_ms(1000);
	TIM_Cmd(TIM1,DISABLE);
	delay_ms(100);
	TIM_Cmd(TIM8,ENABLE);
	start_flag=1; 
	start_flagA=1; 
	start_flagB=0;
	delay_ms(10);
	}
}
void clockwise()				////顺时针
{
	if(start_flagB!=1)
	{
	TIM_SetCompare1(TIM8,0);
	TIM_Cmd(TIM8,DISABLE);
	delay_ms(100);
	TIM_Cmd(TIM1,ENABLE);
  start_flag=1; 
	start_flagA=0; 
	start_flagB=1;
	delay_ms(10);
	}
}

 void LCD_Map(void)
 {
	 double P = 0;
	 double I = 0;
	 double D = 0;
	 int SetCNumber = 0;
	 int TrueCNumber = 0;
	 u8 i = 0;
	 static u8 time = 0;
	 u16 widthi = 240;
	 POINT_COLOR=BLACK;
	 LCD_DrawLine(20,380,460,380);
		LCD_DrawLine(40,390,40,20);
		
		LCD_ShowxNum(20,390,0,1,16,0);
		LCD_ShowxNum(90,390,1,1,16,0);
		LCD_ShowxNum(140,390,2,1,16,0);
		LCD_ShowxNum(190,390,3,1,16,0);
		LCD_ShowxNum(240,390,4,1,16,0);
		LCD_ShowxNum(290,390,5,1,16,0);
		LCD_ShowxNum(340,390,6,1,16,0);
		LCD_ShowxNum(390,390,7,1,16,0);
		LCD_ShowxNum(440,390,8,1,16,0);
	 
		LCD_ShowxNum(20,330,5,1,16,0);
				LCD_DrawLine(35,330,460,330);

		LCD_ShowxNum(20,280,10,2,16,0);
				LCD_DrawLine(35,280,460,280);

		LCD_ShowxNum(20,230,15,2,16,0);
				LCD_DrawLine(35,230,460,230);

		LCD_ShowxNum(20,180,20,2,16,0);
				LCD_DrawLine(35,180,460,180);

		LCD_ShowxNum(20,130,25,2,16,0);
				LCD_DrawLine(35,130,460,130);
		
		LCD_ShowxNum(20,80,30,2,16,0);
				LCD_DrawLine(35,80,460,80);
		
		LCD_ShowxNum(20,30,35,2,16,0);
				LCD_DrawLine(35,30,460,30);
		
		SetCNumber = (sptr->SetPoint)*50/334;
		LCD_ShowString(20,420,200,16,24,"Set speed:");
		LCD_ShowxNum(150,420,SetCNumber,2,24,0);
		
		LCD_ShowString(20,460,200,16,24,"Cur speed:");
		if(start_flagA==1)
		{
			TrueCNumber = compareA*50/334;
			LCD_ShowxNum(150,460,TrueCNumber,2,24,0);
		}
		if(start_flagB==1)
		{
			TrueCNumber = compareB*50/334;
			LCD_ShowxNum(150,460,TrueCNumber,2,24,0);
		}
		
		LCD_ShowString(20,500,200,24,24,"P:");
		LCD_ShowString(20,540,200,24,24,"I:");
		LCD_ShowString(20,580,200,24,24,"D:");
		
		LCD_ShowString(50,500,200,24,24,"0.");
		LCD_ShowString(50,540,200,24,24,"0.");
		LCD_ShowString(50,580,200,24,24,"0.");
		P = sptr->Proportion;
		I = sptr->Integral;
		D = sptr->Derivative;
		LCD_ShowxNum(70,500,(P)*10,1,24,0);
		LCD_ShowxNum(70,540,(I)*10,1,24,0);
		LCD_ShowxNum(70,580,(D)*10,1,24,0);
		LCD_ShowxNum(90,500,(u8)((P)*100)%10,1,24,0);
		LCD_ShowxNum(90,540,(u8)((I)*100)%10,1,24,0);
		LCD_ShowxNum(90,580,(u8)((D)*100)%10,1,24,0);

		LCD_ShowxNum(240,480,1,1,24,0);
		LCD_ShowxNum(300,480,2,1,24,0);
		
		LCD_ShowxNum(360,480,3,1,24,0);
		LCD_ShowxNum(240,540,4,1,24,0);
		LCD_ShowxNum(300,540,5,1,24,0);
		LCD_ShowxNum(360,540,6,1,24,0);
		LCD_ShowxNum(240,600,7,1,24,0);
		LCD_ShowxNum(300,600,8,1,24,0);
		LCD_ShowxNum(360,600,9,1,24,0);
		LCD_ShowxNum(300,660,0,1,24,0);
		
		LCD_ShowString(240,660,200,24,24,"L");  	//逆时针
		LCD_ShowString(360,660,200,24,24,"R");  	//顺时针
		LCD_ShowString(420,480,200,24,24,"D");		//删除
		LCD_ShowString(420,540,200,24,24,"C");		//确定更改
		LCD_ShowString(420,600,200,24,24,".");		// . 的输入
		POINT_COLOR=RED;
		delay_ms(5);
		if(time == 1)
		{
			for(i=0;i<4;i++)
			{
				widthi = widthi + i * 20;
				if(PNum[i]!=100)
				{
					LCD_ShowxNum(widthi,420,PNum[i],1,24,0);
				}
				else if(PNum[i]==100)
				{
					LCD_ShowString(widthi,420,200,24,24,".");
				}
				widthi = 240;
			}
		}
		else
		{
			time = 1;
		}
		if(SetSpeedFlag == 1)
		{
			LCD_DrawRectangle(15,410,175,450);
		}
		else if(CurPFlag == 1)
		{
			LCD_DrawRectangle(15,490,160,530);
		}
		else if(CurIFlag == 1)
		{
			LCD_DrawRectangle(15,530,160,570);
		}
		else if(CurDFlag)
		{
			LCD_DrawRectangle(15,570,160,610);
		}			
 }

 //定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
		uint32_t count;
		double cycleNumber2 = 0;
		double cal;
	static u16 i = 0;
	static u16 x=40;
	static u16 y=0;
	static u16 j=0;
	
	 if(start_flag) // 等待脉冲输出后才开始计时
  {
		if(start_flagB == 1)
		{
      /* 得到编码器计数值，数值越大说明速度越大 */
      count=CaptureNumberB; 
      CaptureNumberB=0;    // 清零，从零开始计数
			CaptureNumberA=0;
			
      /* 计数得到位置式PID的位置数值 */
      compareB=LocPIDCalc(count);      
			
      if(compareB>899)compareB=899;  
      if(compareB<1)compareB=1;
      cal=sptr->SetPoint;
			cycleNumber1 = (cal*50)/334;
      cal=count;
			cycleNumber2 = (cal*50)/334;
			TIM_SetCompare1(TIM1,compareB);	
			if(x<460)	
			{
				x++;
				i++;
				
				if(i==5)
				{
					j++;
					Xco1[j] = (Xmid[0]+Xmid[1]+Xmid[2]+Xmid[3]+Xmid[4])/5;
					Yco1[j] = (Ymid[0]+Ymid[1]+Ymid[2]+Ymid[3]+Ymid[4])/5;
					i=0;
					if(j>0 && j<80)
					{
						LCD_DrawLine(Xco1[j-1],Yco1[j-1],Xco1[j],Yco1[j]);
					}
					if(j==80)
					{
						j=0;
						x=40;
						Xco1[j] = Xco1[89];
						Yco1[j] = Yco1[89];
						LCD_Clear(WHITE);
						LCD_Map();
					}
				}
				Xmid[i] = x;
				y = (380 - (int)(cycleNumber2 * 10));
				Ymid[i] = y;
			}
		}
	 if(start_flagA == 1)
		{
			/* 得到编码器计数值，数值越大说明速度越大 */
      count=CaptureNumberA; 
      CaptureNumberA=0;    // 清零，从零开始计数
			CaptureNumberB=0;
			
      /* 计数得到位置式PID的位置数值 */
      compareA=LocPIDCalc(count);      
			
      if(compareA>899)compareA=899;  
      if(compareA<1)compareA=0;
      cal=sptr->SetPoint;
			cycleNumber1 = (cal*50)/334;
      cal=count;
			cycleNumber2 = (cal*50)/334;
			TIM_SetCompare1(TIM8,compareA);	
			if(x<460)	
			{
				x++;
				i++;
				
				if(i==5)
				{
					j++;
					Xco1[j] = (Xmid[0]+Xmid[1]+Xmid[2]+Xmid[3]+Xmid[4])/5;
					Yco1[j] = (Ymid[0]+Ymid[1]+Ymid[2]+Ymid[3]+Ymid[4])/5;
					i=0;
					if(j>0 && j<80)
					{
						LCD_DrawLine(Xco1[j-1],Yco1[j-1],Xco1[j],Yco1[j]);
					}
					if(j==80)
					{
						j=0;
						x=40;
						Xco1[j] = Xco1[89];
						Yco1[j] = Yco1[89];
						LCD_Clear(WHITE);
						LCD_Map();
					}
				}
				Xmid[i] = x;
				y = (380 - (int)(cycleNumber2 * 10));
				Ymid[i] = y;
			}
		}
		time_count++;         // 每20ms自动增一
    if(time_count==200)
    {	      
				printf("\r\n CaptureNumberA :%d \r\n",CaptureNumberA);
				printf("\r\n CaptureNumberA :%d \r\n",CaptureNumberB);
				printf("\r\n compareB :%d \r\n",compareB);
				printf("\r\n compareA :%d \r\n",compareA);
      time_count=0;      
		}		
  }
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //清除TIMx更新中断标志 
}






