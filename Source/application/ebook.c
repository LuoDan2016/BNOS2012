/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: ebook.c
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/01/20
* 功能描述: 电子书应用程序.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* 变量声明 ---------------------------------------------------------------------*/ 
extern volatile INT8U menuflag;     /* 菜单标识为 */
extern volatile INT8U mainmenuflag; /* 主菜单标识   */
extern unsigned char filecount;     /* 文件计数 */

/* 文件系统相关全局变量声明 */
extern volatile FRESULT res;
extern volatile FATFS fs;	
extern volatile INT16U br,i,j;
volatile BYTE   ebuff[38];    /* 文件缓存 */

/*********************************************************************************
** 函数名称: void EbookView(void).
** 功能描述: 电子书处理.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void EbookView(void)
{
	INT16U row = 0 ,page = 0;	       /* row行 page页 */
	res = pf_open("ebook/vs1003.txt"); /* 打开文件 */
	while(1)
	{
		/* 按键 KEY_DOWN_EXIT 退出并返回主菜单 */
		if(!KEY_DOWN_EXIT)
		{
		 	menuflag     = 0;
		    mainmenuflag = 0;
			break;			
		}

		if(row == 0)                             /* 显示第一页 */
		{
			for(i=0;i<7;i++)
			{
				pf_lseek(row * 38);
				res = pf_read(ebuff,38,&br);	  /*读文件TXT文件*/ 		 
				LCD_Write_String(40,50 + (i * 16),ebuff,Black,White,1);
				if(i > 0)
					if(ebuff[0] != 32)
						LCD_Write_String(40 + 38 * 8,50 + ((i-1) * 16),"-",Black,White,1);
				row++;				
			}
		}
		if(KEY_NEXT == 0 && (!(res || br == 0)))          /* 下一页 */
		{
			GUIDown(320,170,Green);	                      /* 下一页按钮 */
			LCD_FilledRectangle(40,50,316,118,White);     /* 擦除显示区域 */
			for(i=0;i<7;i++)
			{
				
				row++;
				pf_lseek(row * 38);
				res = pf_read(ebuff,38,&br);	              /* 读文件TXT文件 */ 
				if(res || br == 0) break;	              /* 读文件结束 */		 
				LCD_Write_String(40,50 + (i * 16),ebuff,Black,White,1);
				if(i > 0)
					if(ebuff[0] != 32)
						LCD_Write_String(40 + 38 * 8,50 + ((i-1) * 16),"-",Black,White,1);		
			}
			GUIDown(320,170,Black);	                      /* 下一页按钮 */	
		}
		if(KEY_PRE == 0 && (row > 7))                    /* 上一页 */
		{
			GUIUp(70,170,Green);	                      /* 下一页按钮 */
			LCD_FilledRectangle(40,50,316,118,White);     /* 擦除显示区域 */
			row -= 14;
			for(i=0;i<7;i++)
			{
				pf_lseek(row * 38);
				res = pf_read(ebuff,38,&br);	              /*读文件TXT文件*/ 
				if(res || br == 0) break;	              /*读文件结束*/		 
				LCD_Write_String(40,50 + (i * 16),ebuff,Black,White,1);
				if(i > 0)
					if(ebuff[0] != 32)
						LCD_Write_String(40 + 38 * 8,50 + ((i-1) * 16),"-",Black,White,1);		
				row++;
			}
			GUIUp(70,170,Black);	                      /* 下一页按钮 */	
		}



	}	

}