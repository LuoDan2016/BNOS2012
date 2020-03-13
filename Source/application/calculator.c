/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: calculator.c
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/01/20
* 功能描述: 计算器应用程序.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* 变量声明 ---------------------------------------------------------------------*/
extern volatile INT8U menuflag;     /* 菜单标识为 */
extern volatile INT8U mainmenuflag; /* 主菜单标识 */
extern INT8U*  code btndata[4][4];

/*********************************************************************************
** 函数名称: void Calculator(void).
** 功能描述: 计算器处理函数.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void Calculator(void)
{
	INT8U selflag=0,calflag=0,datalen=0,i,j,caltype = 0; /* 运算定义 */
	INT32U iuputdata = 0,iuputdata1 = 0,iuputdata2 = 0,calres = 0,temp = 0;
	while(1)
	{	/* 按键 KEY_DOWN_EXIT 退出并返回主菜单 */
		if(!KEY_DOWN_EXIT)
		{
		 	menuflag     = 0;
		    mainmenuflag = 0;
		 	break;			
		}
		
		if(selflag == 0 && calflag == 0)
		{
			selflag = 1;
			/* 输入面板显示 */
			for(j=0;j<4;j++)
			{
				for(i=0;i<4;i++)
				{
					if(j==0 && i==0)
						GUIButton(btndata[j][i],42 + 12 * i + 20 * i,56+ 12 * j + 20 * j,30,30,RGB(110,110,110));/* 选中按钮 */
					else			
						GUIButton(btndata[j][i],42 + 12 * i + 20 * i,56+ 12 * j + 20 * j,30,30,RGB(220,220,220));/* 按钮 */	
				}
			}
		}
		/* 下一个数据 */
		if(!KEY_NEXT && calflag < 15)
		{
			if(calflag < 4)
				GUIButton(btndata[0][calflag],42 + 12 * calflag + 20 * calflag,56+ 12 * 0 + 20 * 0,30,30,RGB(220,220,220));/* 选中按钮 */	
			if(calflag >= 4  && calflag <= 7)
				GUIButton(btndata[1][calflag - 4],42 + 12 * (calflag - 4) + 20 * (calflag - 4),56+ 12 * 1 + 20 * 1,30,30,RGB(220,220,220));/* 选中按钮 */	
			if(calflag >= 8  && calflag <= 11)
				GUIButton(btndata[2][calflag - 8],42 + 12 * (calflag - 8) + 20 * (calflag - 8),56+ 12 * 2 + 20 * 2,30,30,RGB(220,220,220));/* 选中按钮 */	
			if(calflag >= 12 && calflag <= 15)
				GUIButton(btndata[3][calflag - 12],42 + 12 * (calflag - 12) + 20 * (calflag - 12),56+ 12 * 3 + 20 * 3,30,30,RGB(220,220,220));/* 选中按钮 */
			calflag++;
			if(calflag < 4)											 
				GUIButton(btndata[0][calflag],42 + 12 * calflag + 20 * calflag,56+ 12 * 0 + 20 * 0,30,30,RGB(110,110,110));/* 选中按钮 */	
			if(calflag >= 4  && calflag <= 7)
				GUIButton(btndata[1][calflag - 4],42 + 12 * (calflag - 4) + 20 * (calflag - 4),56 + 12 * 1 + 20 * 1,30,30,RGB(110,110,110));/* 选中按钮 */	
			if(calflag >= 8  && calflag <= 11)
				GUIButton(btndata[2][calflag - 8],42 + 12 * (calflag - 8) + 20 * (calflag - 8),56 + 12 * 2 + 20 * 2,30,30,RGB(110,110,110));/* 选中按钮 */	
			if(calflag >= 12 && calflag <= 15)
				GUIButton(btndata[3][calflag - 12],42 + 12 * (calflag - 12) + 20 * (calflag - 12),56 + 12 * 3 + 20 * 3,30,30,RGB(110,110,110));/* 选中按钮 */		
			OSTimeDly(10);  /* 延时 */
		}
		/* 上一个数据 */
		if(!KEY_PRE && calflag > 0)
		{
			if(calflag < 4)
				GUIButton(btndata[0][calflag],42 + 12 * calflag + 20 * calflag,56+ 12 * 0 + 20 * 0,30,30,RGB(220,220,220));/* 选中按钮 */	
			if(calflag >= 4  && calflag <= 7)
				GUIButton(btndata[1][calflag - 4],42 + 12 * (calflag - 4) + 20 * (calflag - 4),56+ 12 * 1 + 20 * 1,30,30,RGB(220,220,220));/* 选中按钮 */	
			if(calflag >= 8  && calflag <= 11)
				GUIButton(btndata[2][calflag - 8],42 + 12 * (calflag - 8) + 20 * (calflag - 8),56+ 12 * 2 + 20 * 2,30,30,RGB(220,220,220));/* 选中按钮 */	
			if(calflag >= 12 && calflag <= 15)
				GUIButton(btndata[3][calflag - 12],42 + 12 * (calflag - 12) + 20 * (calflag - 12),56+ 12 * 3 + 20 * 3,30,30,RGB(220,220,220));/* 选中按钮 */
			calflag--;
			if(calflag < 4)
				GUIButton(btndata[0][calflag],42 + 12 * calflag + 20 * calflag,56+ 12 * 0 + 20 * 0,30,30,RGB(110,110,110));/* 选中按钮 */	
			if(calflag >= 4  && calflag <= 7)
				GUIButton(btndata[1][calflag - 4],42 + 12 * (calflag - 4) + 20 * (calflag - 4),56+ 12 * 1 + 20 * 1,30,30,RGB(110,110,110));/* 选中按钮 */	
			if(calflag >= 8  && calflag <= 11)
				GUIButton(btndata[2][calflag - 8],42 + 12 * (calflag - 8) + 20 * (calflag - 8),56+ 12 * 2 + 20 * 2,30,30,RGB(110,110,110));/* 选中按钮 */	
			if(calflag >= 12 && calflag <= 15)
				GUIButton(btndata[3][calflag - 12],42 + 12 * (calflag - 12) + 20 * (calflag - 12),56+ 12 * 3 + 20 * 3,30,30,RGB(110,110,110));/* 选中按钮 */		
			OSTimeDly(10);  /* 延时 */
		}
		/* 确认选择 */
		if(!KEY_ENTER)
		{
			/* 清除 */
			if( calflag == 13)
			{
				LCD_FilledRectangle(180,56,170,127,RGB(230,230,230));	
				LCD_FilledRectangle(182,58,166,123,White);	/* 显示面板 */
				LCD_FilledRectangle(186,148,160,1,RGB(230,230,230));
				/* 操作显示 */
				Lcd_WriteNumlen(1,0,185,100,Black,White,1);	/* 输入数据1 */
				LCD_Write_String(185,149,"=",Black,White,0);
				Lcd_WriteNumlen(1,0,185,165,Black,White,1);	/* 显示结果 */
				/* 清除数据 */
//				selflag=0,calflag=0,datalen=0,i,j,caltype = 0;		
//				iuputdata = 0,iuputdata1 = 0,iuputdata2 = 0,calres = 0,temp = 0;
				Calculator();
			}
			if(datalen <= 9)	/* 输入的是 0 - 9 */
			{	
				if(calflag == 3 || calflag == 7 || calflag == 11 || calflag == 15)
				{
					switch(calflag)
					{
						case 3:
							caltype = 1;   /* "/" */
							LCD_Write_String(185,116,btndata[0][3],Black,White,1);
							break;
						case 7:
							caltype = 2;   /* "*" */
							LCD_Write_String(185,116,btndata[1][3],Black,White,1);
							break;
						case 11:
							caltype = 3;  /* "-" */
							LCD_Write_String(185,116,btndata[2][3],Black,White,1);
							break;
						case 15:
							caltype = 4;  /* "+" */
							LCD_Write_String(185,116,btndata[3][3],Black,White,1);
							break;				
					}
					datalen   = 0;	/* 数据清零 */
					iuputdata = 0;
			
				}
							 /* 输入的是数字 */
				if(calflag != 3 && calflag != 7 && calflag != 11 && calflag != 13 && calflag != 14 && calflag != 15)
				{
					
					if(!(datalen == 0 && calflag == 12))  /* 第一位不为0 */
					{
						/* 输入数据 */
						if(datalen == 0)
						{
							if(calflag < 4)	   /* 输入 1 2 3 */
								iuputdata = (calflag + 1);
							if(calflag >= 4  && calflag <= 6)  /* 输入 4 5 6 */
								iuputdata = (calflag);
							if(calflag >= 8  && calflag <= 10)	/* 输入 7 8 9 */
								iuputdata = (calflag - 1);			
						}
						else
						{	
							
							if(calflag == 12)	  /* 输入 0 */
								iuputdata = iuputdata * 10;	
							if(calflag < 4)		  /* 输入 1 2 3 */
								iuputdata = iuputdata * 10 + (calflag + 1); 
							if(calflag >= 4  && calflag <= 6)
							 	iuputdata = iuputdata * 10 + (calflag);	   /* 输入 4 5 6 */
							if(calflag >= 8  && calflag <= 10)
								iuputdata = iuputdata * 10 + (calflag - 1);	/* 输入 7 8 9 */
						}
						datalen++;	
						if(caltype == 0)
						{
							/* 输入显示 */
							if(calflag < 4)
								LCD_Write_String(177 + datalen * 8,100,btndata[0][calflag],Black,White,1);
							if(calflag >= 4  && calflag <= 7)
								LCD_Write_String(177 + datalen * 8,100,btndata[1][calflag - 4],Black,White,1);
							if(calflag >= 8  && calflag <= 11)
								LCD_Write_String(177 + datalen * 8,100,btndata[2][calflag - 8],Black,White,1);
							if(calflag >= 12 && calflag <= 15)
								LCD_Write_String(177 + datalen * 8,100,btndata[3][calflag - 12],Black,White,1);	
							iuputdata1 = iuputdata;
						}
						else
						{
							/* 输入显示 */
							if(calflag < 4)
								LCD_Write_String(177 + datalen * 8,132,btndata[0][calflag],Black,White,1);
							if(calflag >= 4  && calflag <= 7)
								LCD_Write_String(177 + datalen * 8,132,btndata[1][calflag - 4],Black,White,1);
							if(calflag >= 8  && calflag <= 11)
								LCD_Write_String(177 + datalen * 8,132,btndata[2][calflag - 8],Black,White,1);
							if(calflag >= 12 && calflag <= 15)
								LCD_Write_String(177 + datalen * 8,132,btndata[3][calflag - 12],Black,White,1);	
							iuputdata2 = iuputdata;	
						}
					//	Lcd_WriteNumlen(datalen,iuputdata,185,165,Black,White,1);
					}
				 }
				 /* 按 “=”计算结果 */
				 if(calflag == 14)
				 {
				 		switch(caltype)
						{
							case 1:
								calres = iuputdata1 / iuputdata2;
								break;
							case 2:
								calres = iuputdata1 * iuputdata2;
								break;
							case 3:
								calres = iuputdata1 - iuputdata2;
								break;
							case 4:
								calres = iuputdata1 + iuputdata2;
								break;			
						}
						datalen = 0;
						temp = calres;
						while(temp != 0)	 /* 计算数据长度 */
						{
							temp = temp / 10;
							datalen++;
						}
						if(datalen <= 9)
							Lcd_WriteNumlen(datalen,calres,185,165,Black,White,1);	/* 显示结果 */
						else
							LCD_Write_String(185,165,"ERROR        ",Black,White,1);
						iuputdata1 =  calres;
						datalen = 0;
				 }
				OSTimeDly(15);  /* 延时 */
			 }
		}
	
			
	}
					
}											  	