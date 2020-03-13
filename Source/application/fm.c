#include "includes.h"

extern volatile INT8U menuflag;     /* 菜单标识为 */
extern volatile INT8U mainmenuflag; /*主菜单标识  */
extern INT32U frequency; /* FM频率声明 */

 /* 图标动作 频率减小 */
void GUIFreqDown(void)
{
	GUIUpSong(90,150,Green);	        
	OSTimeDly(10);
	GUIUpSong(90,150,White);
}

/* 图标动作 频率增大 */
void GUIFreqUp(void)
{
	GUIDownSong(295,150,Green);	       
	OSTimeDly(10);
	GUIDownSong(295,150,White);
}

void FMRadio(void)
{
	INT8U fmmode = 0;
	FM_SW=1;             /* FM使能输出 */
	VS_RST = 0;          /* VS1003 输出关 */
	
   radio_write();        /* 写入TEA5767数据,初始化*/

   while(1)
   {
		/* 一行程序实现STC不断电自动下载(如果头文件未定义IAP_CONTR寄存器,在while函数中加入if(P3==(P3&0xFE))IAP_CONTR=0x60;
		** 需定义在#include<reg52.h>中加入sfr IAP_CONTR = 0xC7; )原创BOOLESION.NET  -NETC */
		if(P3==(P3&0xFE))IAP_CONTR=0x60;

		/* 按键 KEY_DOWN_EXIT 退出并返回主菜单 */
		if(!KEY_DOWN_EXIT)					
		{
			radio_close();	 /* 关闭FM */
		 	menuflag     = 0;
		    mainmenuflag = 0;
			break;			
		}
		/* 手动搜台 */
		if(KEY_PRE == 0)     /* 按键KEY_NEXT频率减小 */
		{ 
			/* 频率显示 */
			FreqShow(frequency);
			GUIFreqDown();   /* 图标变色及延时消抖 */
			search(0);
			radio_read();
			OSTimeDly(10); /* 延时 */
		}
		
		if(KEY_NEXT == 0)     /* 按键KEY_BACK频率增加 */
		{
			/* 频率显示 */
			FreqShow(frequency);
			GUIFreqUp();   /* 图标变色及延时消抖 */
			search(1);
			radio_read();
			OSTimeDly(10); /* 延时 */
		}
		if(KEY_ENTER==0)     /* 按键KEY_ENTER暂停 */
		{
			if(fmmode == 0)	  /* 暂停 */
			{
				radio_close();
				fmmode = 1;	
				GUIPlay(170,150,White);    /* 播放图标 */
				GUIPause(200,150,Green);   /* 暂停按钮 */ 
			}
			else			 /* 播放 */
			{
				radio_write(); 
				fmmode = 0;
				GUIPlay(170,150,Green);    /* 播放图标 */
				GUIPause(200,150,White);   /* 暂停按钮 */ 		
			}
			OSTimeDly(20); /* 延时 */
		}
	}
}
