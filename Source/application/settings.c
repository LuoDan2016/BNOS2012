/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: helloworld.c
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/01/20
* 功能描述: 应用程序例子.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* 变量声明 ---------------------------------------------------------------------*/
extern volatile INT8U menuflag;     /* 菜单标识为 */
extern volatile INT8U mainmenuflag; /* 主菜单标识 */
extern SYS_TIME datetime;	        /* 系统时间 */
volatile INT16U LcdBLsettime = 45;  /* LCD 背光比较值 */

/*********************************************************************************
** 函数名称: void Settings(void).
** 功能描述: 系统设置.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void Settings(void)
{
	INT8U menucount = 0;
	INT8U setday;
	setday = datetime.day;
	while(1)
	{
		
			/* 按键 KEY_DOWN_EXIT 退出并返回主菜单 */
		if(!KEY_DOWN_EXIT)					
		{
			radio_close();	 /* 关闭FM */
		 	menuflag     = 0;
		    mainmenuflag = 0;
			break;			
		}

		if(!KEY_NEXT)	/* 按键选中增 */
		{
			if(menucount < 9)
			{
				menucount++;
				GUIButton(" EXIT",220,150,70,25,RGB(220,220,220));	 /* 未选中 EXIT */	
				GUIButton("  OK",100,150,70,25,RGB(220,220,220));	 /* 未选中 OK */
				GUIUp(210,52,Black);   	 /* 背光时间按钮恢复 */
				GUIDown(280,52,Black);
				GUIUp(210,78,Black);   	 /* 系统时间 年 按钮恢复 */
				GUIDown(280,78,Black);
				GUIUp(210,104,Black);   /* 系统时间 月 按钮恢复 */
				GUIDown(280,104,Black);
				GUIUp(210,130,Black);   /* 系统时间 日 按钮恢复 */
				GUIDown(280,130,Black);
				OSTimeDly(10);  /* 延时 */	
			}
		}
		if(!KEY_PRE)  /* 按键选中减 */
		{
			if(menucount > 0)
			{
				menucount--;
				GUIButton(" EXIT",220,150,70,25,RGB(220,220,220));	 /* 未选中 EXIT */	
				GUIButton("  OK",100,150,70,25,RGB(220,220,220));	 /* 未选中 OK */
				GUIUp(210,52,Black);   	 /* 背光时间按钮恢复 */
				GUIDown(280,52,Black);
				GUIUp(210,78,Black);   	 /* 系统时间 年 按钮恢复 */
				GUIDown(280,78,Black);
				GUIUp(210,104,Black);   /* 系统时间 月 按钮恢复 */
				GUIDown(280,104,Black);
				GUIUp(210,130,Black);   /* 系统时间 日 按钮恢复 */
				GUIDown(280,130,Black);
				OSTimeDly(10);  /* 延时 */
			}
		}
		if(menucount == 0)	 /* 背光 选中 减少 */
		{
			GUIUp(210,52,Green);
			if(!KEY_ENTER)
			{
				if(LcdBLsettime > 1)
					LcdBLsettime -= 1;
				Lcd_WriteNumlen(3,LcdBLsettime,232,54,String_Color,White,1);	/* 显示 时间 second */
				OSTimeDly(5);  /* 延时 */
			} 
		}
		if(menucount == 1)	 /* 背光 选中 增加*/
		{
			GUIDown(280,52,Green);
			if(!KEY_ENTER)
			{
				if(LcdBLsettime < 300)
					LcdBLsettime += 1;
				Lcd_WriteNumlen(3,LcdBLsettime,232,54,String_Color,White,1);	/* 显示 时间 second */
				OSTimeDly(5);  /* 延时 */
			}  
		}
		if(menucount == 2)	 /* 系统时间年 选中增加*/
		{
			GUIUp(210,78,Green);  
			if(!KEY_ENTER)
			{
				if(datetime.year < 0x9999)
					datetime.year++;
				Lcd_WriteNumlen(4,BcdToBin(datetime.year >> 8)*0x64 +  BcdToBin(datetime.year & 0xff),232,80,String_Color,White,1);	/* 显示 时间 年 */
				OSTimeDly(5);  /* 延时 */
			}  
		}
		if(menucount == 3)	 /* 系统时间年 选中减少*/
		{
			GUIDown(280,78,Green);  
			if(!KEY_ENTER)
			{
				if(datetime.year > 0x0)
					datetime.year--;
				Lcd_WriteNumlen(4,BcdToBin(datetime.year >> 8)*0x64 +  BcdToBin(datetime.year & 0xff),232,80,String_Color,White,1);	/* 显示 时间 年 */
				OSTimeDly(5);  /* 延时 */
			}  
		}
		if(menucount == 4)	 /* 系统时间月 选中减少*/
		{
			GUIUp(210,104,Green);  
			if(!KEY_ENTER)
			{
				if(datetime.mon > 0x1)
					datetime.mon--;
				Lcd_WriteNumlen(2,BcdToBin(datetime.mon),232,106,String_Color,White,1);	/* 显示 时间 月 */
			    OSTimeDly(5);  /* 延时 */
			}  
		}
		if(menucount == 5)	 /* 系统时间月 选中增加*/
		{
			GUIDown(280,104,Green);  
			if(!KEY_ENTER)
			{
				if(datetime.mon < 0x12)
					datetime.mon++;
				Lcd_WriteNumlen(2,BcdToBin(datetime.mon),232,106,String_Color,White,1);	/* 显示 时间 月 */
			    OSTimeDly(5);  /* 延时 */
			}  
		}
			if(menucount == 6)	 /* 系统时间日 选中减少*/
		{
			GUIUp(210,130,Green);  
			if(!KEY_ENTER)
			{
				if(setday > 0x1)
					setday--;
				datetime.day = setday;
				Lcd_WriteNumlen(2,setday,232,132,String_Color,White,1);	/* 显示 时间 日 */
			    OSTimeDly(5);  /* 延时 */
			}  
		}
		if(menucount == 7)	 /* 系统时间日 选中增加*/
		{
			GUIDown(280,130,Green);  
			if(!KEY_ENTER)
			{
				
				if( setday < 31 )
					setday++;
				datetime.day = setday;
				Lcd_WriteNumlen(2,setday,232,132,String_Color,White,1);	/* 显示 时间 日 */
			    OSTimeDly(5);  /* 延时 */
			}  
		}
		if(menucount == 8)	   /* OK */
		{
			GUIButton("  OK",100,150,70,25,RGB(110,110,110));	 /* 未选中 OK */
			if(!KEY_ENTER)
			{
				 menuflag     = 0;
		   		 mainmenuflag = 0;
		 		 break;		
			}  
		}
		if(menucount == 9)	 /* EXIT */
		{
			GUIButton(" EXIT",220,150,70,25,RGB(110,110,110));	 /* 未选中 EXIT */
			if(!KEY_ENTER)
			{
				 menuflag     = 0;
		   		 mainmenuflag = 0;
		 		 break;		
			}  
		}
	}		
}