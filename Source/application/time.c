/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: time.c
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/01/20
* 功能描述: 时间及日历处理程序.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* 变量声明 ---------------------------------------------------------------------*/
extern volatile INT8U menuflag; /* 菜单标识为 */
extern volatile INT8U mainmenuflag; /*主菜单标识   */
SYS_TIME datetime;	 /* 系统时间 */

/* 星期字符串 */
INT8U code *WEEKS[7] = 
{
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday"
};

/* 闰年月星期表 */
code INT8U WeekTab[] = {
  (3 << 5) + 31,	//1月 
  (6 << 5) + 29,	//2月 
  (0 << 5) + 31,	//3月 
  (3 << 5) + 30,	//4月 
  (5 << 5) + 31,	//5月 
  (1 << 5) + 30,	//6月 
  (3 << 5) + 31,	//7月 
  (6 << 5) + 31,	//8月 
  (1 << 5) + 30,	//9月 
  (4 << 5) + 31,	//10月 
  (0 << 5) + 30,	//11月 
  (2 << 5) + 31 	//12月 
};  

/*********************************************************************************
** 函数名称: INT8U WeekDay(INT8U c,INT8U y,INT8U m,INT8U d).
** 功能描述: 0000年~9999年星期算法.
** 输入参数: INT8U c,INT8U y,INT8U char m,INT8U d.         
** 输出参数: None.
** 返回参数: (week << 5) | day 返回星期和月天数.
**********************************************************************************/
INT8U WeekDay(INT8U c,INT8U y,INT8U m,INT8U d) 
{ 
  unsigned char week, day; 
  c &= 0x03;                           /* 百年%4 */
  c = c | (c << 2);                    /* 百年%4*5 */
  day = WeekTab[m - 1];                /* 月表 */
  week = day >> 5;                     /*月星期数 */
  day &= 0x1f;                         /*月天数 */
  if ((m < 3) && !((c == 0) | (y & ((y & 0x03) == 0)))){/*平年 */
    if (m == 2) day--;                 /*平年月天数 */
    week++;                            /*平年月表+1 */
  } 
  y = y + (y >> 2);                    /*年+年/4 */
  week = (week + c + y + d + 2) % 7;   /*(星期=百年%4*5+年+年/4+月表+日+2)%7  */
  return (week << 5) | day;            /*返回星期和月天数 */
} 

/*********************************************************************************
** 函数名称: INT8U GetWeekMaxDay(INT16U year,INT8U m,INT8U d).
** 功能描述: 获得最大月天数.
** 输入参数: INT16U year,INT8U m,INT8U d.         
** 输出参数: None.
** 返回参数: WDay Week = WDay >> 5 得到星期,Day  = WDay & 0x1f得到最大月天数.
**********************************************************************************/
INT8U GetWeekMaxDay(INT16U year,INT8U m,INT8U d) 
{ 
	unsigned char c, y; 	           /* 百年和年 */
	unsigned char cx, yx, mx, dx;   
	unsigned char WDay; 

	c    = year >> 8;
	y    = year & 0xff;
	cx   = BcdToBin(c);                /* 百年 */ 
	yx   = BcdToBin(y);                /* 年 */ 
	mx   = BcdToBin(m);                /* 月 */ 
	dx   = BcdToBin(d);                /* 日 */ 
	WDay = WeekDay(cx, yx, mx, dx);    /* 取星期和月天数 */ 
	return WDay;       /* Week = WDay >> 5 得到星期,Day  = WDay & 0x1f得到最大月天数 */
} 

/*********************************************************************************
** 函数名称: void CalendarApp(void).
** 功能描述: 万年历处理程序.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void CalendarApp(void)
{
	INT8U weekmaxday,week,maxday;  /* 星期和最大月天数 */
	INT8U disday = 1,disrow = 0,disres = 0;  /* 显示项 */
	INT16U calyear = datetime.year; /* 万年历日期 年 */
	INT8U calmon = datetime.mon;   /* 万年历日期 月 */
	weekmaxday = GetWeekMaxDay(calyear,calmon,0x01);  /* 获得当月1日的星期数 */
	week       = weekmaxday >>5;	 /* 获得星期 */
    maxday     = weekmaxday	& 0x1f;   /* 获得最大月天数 */
	while(1)
	{
		/* 按键 KEY_DOWN_EXIT 退出并返回主菜单 */
		if(!KEY_DOWN_EXIT)
		{
		 	menuflag     = 0;
		    mainmenuflag = 0;
			break;			
		}
		if(disres  == 0)
		{
			GUIDown(320,50,Black);	/* 下一月 恢复颜色 */
			GUIUp(180,50,Black);    /* 上一月  恢复颜色 */
			/* 万年历显示 */
			for(disrow=0;disrow < 6;disrow++)	/* 显示行数 共6列 */
			{
				for(week;week < 7;week++)		 /* 显示行数  */
				{
		
				    if(calyear ==datetime.year && calmon == datetime.mon && disday == datetime.day) /* 今天显示红色 */
						Lcd_WriteNumlen(2,disday,145 + (32 * week),104 + (disrow * 14),Red,White,1);
					else		
						Lcd_WriteNumlen(2,disday,145 + (32 * week),104 + (disrow * 14),Blue,White,1);
					if(disday < maxday)
						disday++;
					else
						break;
				}
				if(disday == maxday)
					break;
				else
					week = 0;
			}
			disres = 1;						
		}
		/* 下一月 */
		if(!KEY_NEXT)
		{
			GUIDown(320,50,Green);	/* 下一月 活动颜色 */
		 	disday = 1,disrow = 0;  /* 显示日期 */
			disres = 0;		        /* 重新显示 */
		  	if(calmon < 12)
		  		calmon++;           /* 月递增 */
			else
			{
				calyear++;
				calmon = 1;
		    }
			weekmaxday = GetWeekMaxDay(calyear,calmon,0x01);  /* 获得当月1日的星期数 */
			week       = weekmaxday >>5;	 /* 获得星期 */
			maxday     = weekmaxday	& 0x1f;   /* 获得最大月天数 */	
			/* 递增显示 */
			Lcd_WriteNumlen(4,BcdToBin(calyear >> 8)*0x64 +  BcdToBin(calyear & 0xff),40+178,54,Blue,White,1);	  /* 年 */
			LCD_Write_String(73+178,54,"/",Blue,White,0);
			Lcd_WriteNumlen(2,BcdToBin(calmon),82+178,54,Blue,White,1);	          /* 月 */	
			LCD_FilledRectangle(144,104,210,88,White);                            /* 擦除显示区域 */	 
		}
		/* 上一月 */
		if(!KEY_PRE)
		{
			GUIUp(180,50,Green);    /* 上一月 活动颜色 */
		 	disday = 1,disrow = 0;  /* 显示日期 */
			disres = 0;		        /* 重新显示 */
		  	if(calmon > 1)
		  		calmon--;           /* 月递增 */
			else
			{
				calyear--;
				calmon = 12;
		    }
			weekmaxday = GetWeekMaxDay(calyear,calmon,0x01);  /* 获得当月1日的星期数 */
			week       = weekmaxday >>5;	 /* 获得星期 */
			maxday     = weekmaxday	& 0x1f;   /* 获得最大月天数 */	
			/* 递增显示 */
			Lcd_WriteNumlen(4,BcdToBin(calyear >> 8)*0x64 +  BcdToBin(calyear & 0xff),40+178,54,Blue,White,1);	  /* 年 */
			LCD_Write_String(73+178,54,"/",Blue,White,0);
			Lcd_WriteNumlen(2,BcdToBin(calmon),82+178,54,Blue,White,1);	          /* 月 */	
			LCD_FilledRectangle(144,104,210,88,White);        /* 擦除显示区域 */	 
		}
	
	}						
}
