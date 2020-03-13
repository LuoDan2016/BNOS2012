/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51播放器开发板 E1101
* 文件名称: guimain.c
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/01/20
* 功能描述: 主GUI程序.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"
/* 
**菜单全局变量 
*/
volatile INT8U menuflag  = 0;      /* 菜单标识为 */ 
volatile INT8U choseflag = 0;      /* 选择标识   */
volatile INT8U mainmenuflag   = 0; /*主菜单标识   */
/* 鼠标外部变量 */	
extern volatile INT16U xcoordinate,ycoordinate;
/* 变量声明 ---------------------------------------------------------------------*/
extern SYS_TIME datetime;	    /* 系统时间 */
/*  汉字字库检查标识 1为正确 其他不存在 */
extern INT8U CHNCHEK;
/* 文件系统相关全局变量声明 */
extern volatile FRESULT res;
extern volatile FATFS fs;	
extern volatile INT16U br,i,j;
extern volatile BYTE  buff[256];   /*文件缓存*/
extern volatile FILINFO finfo;
extern volatile DIR dir;
extern volatile char* filename;
/*********************************************************************************
** 函数名称: void GUI_BRCLOGO(void).
** 功能描述: 布尔创LOGO显示 如果SD存在且存在该图像文件则从SD开发 否则从 SPI FLASH开打.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void GUI_BRCLOGO(void)
{
	INT8U res;
	switch(GUIDATAPATH)
	{
		case 0:
			FlashGraphDis(4,140,100,66,FLASHADDR_SLOGO);
			break;
		case 1:
		{
			res = BmpDecode(4,140,BRCLOGO);
			if(res == 1)
			FlashGraphDis(4,140,100,66,FLASHADDR_SLOGO);
			break;
		 }				
	}
	/* 启动进度 */	
	GUIProgressBar(0,LCD_YSIZE_TFT - 6,400,6,80);		
}

/*********************************************************************************
** 函数名称: void GUI_BNOSSTART(void).
** 功能描述: BNOS启动提示.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void GUI_BNOSWALPAPER(void)
{
	INT16U i,j;
	/* 设定背景样色 */
	LCD_FilledRectangle(0,0,400,216,WALLCOLOR);
	/* 顶部样式 */
	LCD_FilledRectangle(0,0,400,20,RGB(36,39,39));
	/* 桌面通孔 */
	for(i=0;i<18;i++)
	{
		for(j=0;j<50;j++)
		{
			if(i%2 == 0)
				MinRound(j * 10,i*12,0x0000);
			else
				MinRound((j * 10)+5,i*12,0x0000);		
		}
	}
	LCD_Write_String(4,4,"BPOD",RGB(250,250,250),RGB(36,39,39));
//	LCD_Write_String(80,40,"Design by Boolesion.net - NETC",RGB(168,213,54),WALLCOLOR,0);		
}

/*********************************************************************************
** 函数名称: void GuiMainMenu(void).
** 功能描述: 启动界面GUI.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void GUI_MainMenu(void)
{
	INT8U *DISLANG;
	switch(USELANG)	     /* 语言选择 */
		{
			case 0:			 /* English  */
				DISLANG = "EN";
				break;
			case 1:			 /* 简体中文 */
				DISLANG = "CH";
				break;
			case 2:			 /* 默认语言 */
			 	if(CHNCHEK)
					DISLANG = "CH";
				else
					DISLANG = "EN";	
				break;
		}	
	/* 主界面窗口 */
	/* 任务栏 */	
	LCD_FilledRectangle(LCD_XSIZE_TFT - LCD_XSIZE_TFT,LCD_YSIZE_TFT - 24,LCD_XSIZE_TFT,1,RGB(127,127,127));
	LCD_FilledRectangle(LCD_XSIZE_TFT - LCD_XSIZE_TFT,LCD_YSIZE_TFT - 23,LCD_XSIZE_TFT,23,TASKBARCOLOR);/* 任务栏 */
	Lcd_WriteNumlen(2,datetime.hour,LCD_XSIZE_TFT - 44,LCD_YSIZE_TFT - 16,White,TASKBARCOLOR,1);	    /* 时间显示 */
	LCD_Write_String(LCD_XSIZE_TFT - 28,LCD_YSIZE_TFT - 16,":",White,TASKBARCOLOR,1);
	Lcd_WriteNumlen(2,datetime.min,LCD_XSIZE_TFT - 20,LCD_YSIZE_TFT - 16,White,TASKBARCOLOR,1);	
	GUIToolICOPower(340,220,8);	                                        /* 电量显示 */
	LCD_Write_String(310,LCD_YSIZE_TFT - 16,DISLANG,White,TASKBARCOLOR,1);	/* 系统语言 */
	LCD_FilledRectangle(4,LCD_YSIZE_TFT - 20,20,4,Magenta);	            /* 开始菜单 */
	LCD_FilledRectangle(4,LCD_YSIZE_TFT - 14,20,4,Green);
	LCD_FilledRectangle(4,LCD_YSIZE_TFT - 8,20,4,Blue2);

}

/*********************************************************************************
** 函数名称: void MainIco(void).
** 功能描述: 主界面菜单ICO.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void MainIco(void)
{
	INT8U res;
	/* 主菜单标识为MAINMENU 0 */
	menuflag = MAINMENU;  
	switch(USELANG)	     /* 语言选择 */
	{
		case 0:			 /* English  */
			{
			EN_MAINMENUTITLE;
			}
			break;
		case 1:			 /* 简体中文 */
			CH_MAINMENUTITLE; 
			break;
		case 2:			 /* 默认语言 */
		 	if(CHNCHEK)
			{
				CH_MAINMENUTITLE;
			}
			else
			{
				EN_MAINMENUTITLE;
			}
			break;		
	}
	switch(GUIDATAPATH)
	{
		case 0:
			/* 第一行菜单ICO */
			FlashGraphDis(50,30,44,45,FLASHADDR_MUSIC);
			FlashGraphDis(140,30,44,45,FLASHADDR_PHOTOS);
			FlashGraphDis(220,30,44,45,FLASHADDR_RADIO);
			FlashGraphDis(300,30,44,45,	FLASHADDR_CALENDAR);
			/* 第二行菜单ICO */	
			FlashGraphDis(50,120,44,45,FLASHADDR_EBOOK	);
			FlashGraphDis(140,120,44,45,FLASHADDR_CALCU);
			FlashGraphDis(220,120,44,45,FLASHADDR_APP);
			FlashGraphDis(300,120,44,45,FLASHADDR_SETTINGS);
			break;
		case 1:
		{	
			/* 第一行菜单ICO */
			res = BmpDecode(50,30,"system/music.bmp");
			BmpDecode(140,30,"system/Photos.bmp");
			BmpDecode(220,30,"system/Radio.bmp");
			BmpDecode(300,30,"system/Calendar.bmp");
			/* 第二行菜单ICO */	
			BmpDecode(50,120,"system/Ebook.bmp");
			BmpDecode(140,120,"system/Calcu.bmp");
			BmpDecode(220,120,"system/app.bmp");
			BmpDecode(300,120,"system/Settings.bmp");
			if(res == 1)
			{
				/* 第一行菜单ICO */
				FlashGraphDis(50,30,44,45,FLASHADDR_MUSIC);
				FlashGraphDis(140,30,44,45,FLASHADDR_PHOTOS);
				FlashGraphDis(220,30,44,45,FLASHADDR_RADIO);
				FlashGraphDis(300,30,44,45,	FLASHADDR_CALENDAR);
				/* 第二行菜单ICO */	
				FlashGraphDis(50,120,44,45,FLASHADDR_EBOOK	);
				FlashGraphDis(140,120,44,45,FLASHADDR_CALCU);
				FlashGraphDis(220,120,44,45,FLASHADDR_APP);
				FlashGraphDis(300,120,44,45,FLASHADDR_SETTINGS);
			}


			break;
		 }				
	}



}

/*********************************************************************************
** 函数名称: void MovMenu(void).
** 功能描述: 主动态选中菜单.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void MovMenu(void)
{
		switch(menuflag)
		{
			case MAINMENU:
			{	 
				/* 主菜单 图标 */
				if(mainmenuflag == 0)
					{
						/* 桌面 */
						GUI_BNOSWALPAPER();
						/* 桌面菜单图标 */
						MainIco();
						MouseInit(10,40);	 /* 设定光标位置 */
						mainmenuflag = 1;
					} 
				if(	/* Music */
				xcoordinate >= 33 && xcoordinate <= 85 && ycoordinate >= 30 && ycoordinate <= 100 
				)	/* 进入 */	   /* 音乐菜单标题 */
				{
					if(	choseflag != MAINMENU_MUSIC)
					{	
						switch(USELANG)	     /* 语言选择 */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_MUSIC,1);
								}
								break;
							case 1:			 /* 简体中文 */
								CH_MAINMENUSEL(MAINMENU_MUSIC,1); 
								break;
							case 2:			 /* 默认语言 */
							 	if(CHNCHEK)
								{
									CH_MAINMENUSEL(MAINMENU_MUSIC,1);
								}
								else
								{
									EN_MAINMENUSEL(MAINMENU_MUSIC,1);
								}
								break;		
						}		    
				    	choseflag = MAINMENU_MUSIC;	
					}
				}
				else if(choseflag == MAINMENU_MUSIC)	 /* 离开 */
				{
						switch(USELANG)	     /* 语言选择 */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_MUSIC,0);
								}
								break;
							case 1:			 /* 简体中文 */
								CH_MAINMENUSEL(MAINMENU_MUSIC,0); 
								break;
							case 2:			 /* 默认语言 */
							 	if(CHNCHEK)
								{
									CH_MAINMENUSEL(MAINMENU_MUSIC,0);
								}
								else
								{
									EN_MAINMENUSEL(MAINMENU_MUSIC,0);
								}
								break;		
						}		   
				    choseflag = 0;			
				}	
				if(	  /* Photos */
				xcoordinate >= 125 && xcoordinate <= 174 && ycoordinate >= 30 && ycoordinate <= 100 
				)	 	/* 进入 */			/* 相册菜单标题 */
				{
						switch(USELANG)	     /* 语言选择 */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_PHOTOS,1);
								}
								break;
							case 1:			 /* 简体中文 */
								CH_MAINMENUSEL(MAINMENU_PHOTOS,1); 
								break;
							case 2:			 /* 默认语言 */
							 	if(CHNCHEK)
								{
									CH_MAINMENUSEL(MAINMENU_PHOTOS,1);
								}
								else
								{
									EN_MAINMENUSEL(MAINMENU_PHOTOS,1);
								}
								break;		
						}			
				    choseflag = MAINMENU_PHOTOS;
				}
				else if(choseflag == MAINMENU_PHOTOS)	 /* 离开 */		  /* 相册菜单标题 */
				{
					switch(USELANG)	     /* 语言选择 */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_PHOTOS,0);
								}
								break;
							case 1:			 /* 简体中文 */
								CH_MAINMENUSEL(MAINMENU_PHOTOS,0); 
								break;
							case 2:			 /* 默认语言 */
							 	if(CHNCHEK)
								{
									CH_MAINMENUSEL(MAINMENU_PHOTOS,0);
								}
								else
								{
									EN_MAINMENUSEL(MAINMENU_PHOTOS,0);
								}
								break;		
						}		    	   
				    choseflag = 0;			
				}
				if(	  /* Radio */
				xcoordinate >= 206 && xcoordinate <= 257 &&	ycoordinate >= 30 && ycoordinate <= 100 
				)	  	/* 进入 */	  	/* 收音机菜单标标题 */
				{
					switch(USELANG)	     /* 语言选择 */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_RADIO,1);
								}
								break;
							case 1:			 /* 简体中文 */
								CH_MAINMENUSEL(MAINMENU_RADIO,1); 
								break;
							case 2:			 /* 默认语言 */
							 	if(CHNCHEK)
								{
									CH_MAINMENUSEL(MAINMENU_RADIO,1);
								}
								else
								{
									EN_MAINMENUSEL(MAINMENU_RADIO,1);
								}
								break;		
						}			
				    choseflag = MAINMENU_RADIO;
				}
				else if(choseflag == MAINMENU_RADIO)	 /* 离开 */	   	/* 收音菜单标标题 */
				{
						switch(USELANG)	     /* 语言选择 */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_RADIO,0);
								}
								break;
							case 1:			 /* 简体中文 */
								CH_MAINMENUSEL(MAINMENU_RADIO,0); 
								break;
							case 2:			 /* 默认语言 */
							 	if(CHNCHEK)
								{
									CH_MAINMENUSEL(MAINMENU_RADIO,0);
								}
								else
								{
									EN_MAINMENUSEL(MAINMENU_RADIO,0);
								}
								break;		
						}				   
				    choseflag = 0;			
				}
				if(	  /* Calendar */
				xcoordinate >= 287 && xcoordinate <= 336 &&	ycoordinate >= 30 && ycoordinate <= 100 
				)	 	/* 进入 */	     /* 日历菜单标题 */
				{
						switch(USELANG)	     /* 语言选择 */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_CALENDAR,1);
								}
								break;
							case 1:			 /* 简体中文 */
								CH_MAINMENUSEL(MAINMENU_CALENDAR,1); 
								break;
							case 2:			 /* 默认语言 */
							 	if(CHNCHEK)
								{
									CH_MAINMENUSEL(MAINMENU_CALENDAR,1);
								}
								else
								{
									EN_MAINMENUSEL(MAINMENU_CALENDAR,1);
								}
								break;		
						}		  
				    choseflag = MAINMENU_CALENDAR;
				}
				else if(choseflag == MAINMENU_CALENDAR)	 /* 离开 */	  /* 日历菜单标题 */
				{
					switch(USELANG)	     /* 语言选择 */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_CALENDAR,0);
								}
								break;
							case 1:			 /* 简体中文 */
								CH_MAINMENUSEL(MAINMENU_CALENDAR,0); 
								break;
							case 2:			 /* 默认语言 */
							 	if(CHNCHEK)
								{
									CH_MAINMENUSEL(MAINMENU_CALENDAR,0);
								}
								else
								{
									EN_MAINMENUSEL(MAINMENU_CALENDAR,0);
								}
								break;		
						}		    	   
				    choseflag = 0;			
				}
				if(	  /* Ebook */
				xcoordinate >= 33 && xcoordinate <= 85 &&	ycoordinate >= 120 && ycoordinate <= 190 
				)	 	/* 进入 */	     /* 电子书菜单标题 */
				{
					switch(USELANG)	     /* 语言选择 */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_EBOOK,1);
								}
								break;
							case 1:			 /* 简体中文 */
								CH_MAINMENUSEL(MAINMENU_EBOOK,1); 
								break;
							case 2:			 /* 默认语言 */
							 	if(CHNCHEK)
								{
									CH_MAINMENUSEL(MAINMENU_EBOOK,1);
								}
								else
								{
									EN_MAINMENUSEL(MAINMENU_EBOOK,1);
								}
								break;		
						}			  
				    choseflag = MAINMENU_EBOOK;
				}
				else if(choseflag == MAINMENU_EBOOK)	 /* 离开 */	    /* 电子书菜单标题 */
				{
					switch(USELANG)	     /* 语言选择 */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_EBOOK,0);
								}
								break;
							case 1:			 /* 简体中文 */
								CH_MAINMENUSEL(MAINMENU_EBOOK,0); 
								break;
							case 2:			 /* 默认语言 */
							 	if(CHNCHEK)
								{
									CH_MAINMENUSEL(MAINMENU_EBOOK,0);
								}
								else
								{
									EN_MAINMENUSEL(MAINMENU_EBOOK,0);
								}
								break;		
						}			   	   
				    choseflag = 0;			
				}
				if(	  /* Calculator */
				xcoordinate >= 125 && xcoordinate <= 174 &&	ycoordinate >= 120 && ycoordinate <= 190 
				)	  	/* 进入 */	 /* 计算器菜单标题 */
				{
					switch(USELANG)	     /* 语言选择 */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_CALCULATOR,1);
								}
								break;
							case 1:			 /* 简体中文 */
								CH_MAINMENUSEL(MAINMENU_CALCULATOR,1); 
								break;
							case 2:			 /* 默认语言 */
							 	if(CHNCHEK)
								{
									CH_MAINMENUSEL(MAINMENU_CALCULATOR,1);
								}
								else
								{
									EN_MAINMENUSEL(MAINMENU_CALCULATOR,1);
								}
								break;		
						}	    
				    choseflag = MAINMENU_CALCULATOR;
				}
				else if(choseflag == MAINMENU_CALCULATOR)	 /* 离开 */	  /* 计算器菜单标题 */
				{
						switch(USELANG)	     /* 语言选择 */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_CALCULATOR,0);
								}
								break;
							case 1:			 /* 简体中文 */
								CH_MAINMENUSEL(MAINMENU_CALCULATOR,0); 
								break;
							case 2:			 /* 默认语言 */
							 	if(CHNCHEK)
								{
									CH_MAINMENUSEL(MAINMENU_CALCULATOR,0);
								}
								else
								{
									EN_MAINMENUSEL(MAINMENU_CALCULATOR,0);
								}
								break;		
						}		   	   
				    choseflag = 0;			
				}
				if(	  /* App */
				xcoordinate >= 206 && xcoordinate <= 257 &&	ycoordinate >= 120 && ycoordinate <= 190 
				)	  	/* 进入 */		 	/* 应用程序菜单标题 */
				{
						switch(USELANG)	     /* 语言选择 */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_APP,1);
								}
								break;
							case 1:			 /* 简体中文 */
								CH_MAINMENUSEL(MAINMENU_APP,1); 
								break;
							case 2:			 /* 默认语言 */
							 	if(CHNCHEK)
								{
									CH_MAINMENUSEL(MAINMENU_APP,1);
								}
								else
								{
									EN_MAINMENUSEL(MAINMENU_APP,1);
								}
								break;		
						}			
				    choseflag = MAINMENU_APP;
				}
				else if(choseflag == MAINMENU_APP)	 /* 离开 */	  	/* 应用程序菜单标题 */
				{
						switch(USELANG)	     /* 语言选择 */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_APP,0);
								}
								break;
							case 1:			 /* 简体中文 */
								CH_MAINMENUSEL(MAINMENU_APP,0); 
								break;
							case 2:			 /* 默认语言 */
							 	if(CHNCHEK)
								{
									CH_MAINMENUSEL(MAINMENU_APP,0);
								}
								else
								{
									EN_MAINMENUSEL(MAINMENU_APP,0);
								}
								break;		
						}				   
				    choseflag = 0;			
				}
				if(	  /* Settings */
				xcoordinate >= 287 && xcoordinate <= 336 &&	ycoordinate >= 120 && ycoordinate <= 190 
				)	  	/* 进入 */	  /* 系统设置菜单标题 */
				{
					switch(USELANG)	     /* 语言选择 */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_SETTINGS,1);
								}
								break;
							case 1:			 /* 简体中文 */
								CH_MAINMENUSEL(MAINMENU_SETTINGS,1); 
								break;
							case 2:			 /* 默认语言 */
							 	if(CHNCHEK)
								{
									CH_MAINMENUSEL(MAINMENU_SETTINGS,1);
								}
								else
								{
									EN_MAINMENUSEL(MAINMENU_SETTINGS,1);
								}
								break;		
						}		    
				    choseflag = MAINMENU_SETTINGS;
				}
				else if(choseflag == MAINMENU_SETTINGS)	 /* 离开 */	    /* 系统设置菜单标题 */
				{
					switch(USELANG)	     /* 语言选择 */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_SETTINGS,0);
								}
								break;
							case 1:			 /* 简体中文 */
								CH_MAINMENUSEL(MAINMENU_SETTINGS,0); 
								break;
							case 2:			 /* 默认语言 */
							 	if(CHNCHEK)
								{
									CH_MAINMENUSEL(MAINMENU_SETTINGS,0);
								}
								else
								{
									EN_MAINMENUSEL(MAINMENU_SETTINGS,0);
								}
								break;		
						}		  	   
				    choseflag = 0;			
				}
				/* 按下MODE键进入 */
			if(!KEY_ENTER)
				{
						switch(choseflag)
						{
							case MAINMENU_MUSIC:   /* 进入音乐播放器 */
							{
								GuiMusicPlayer();  /* 播放器GUI */
								MusicDecode(); 	   /* 音频解码程序 */
								break;
							} 
							case MAINMENU_PHOTOS:  /* 进入电子相册 */
							{
								GUIPhotos();  /* 播放器GUI */
						 	    PhotosPlay(); /* 相片播放 */
								break;
							}
							case MAINMENU_RADIO:  /* 进入收音机 */
							{
								GUIRadio();		 /* 收音机GUI */
								FMRadio();		 /* 收音机程序 */
								break;
							}
							case MAINMENU_CALENDAR:  /* 进入万年历 */
							{
								GUICalendar();  /* 万年历GUI */
								CalendarApp();	/* 万年历程序 */
								break;
							} 
							case MAINMENU_EBOOK:  /* 进入电子书 */
							{
								GUIEbook();  /* 电子书GUI */
								EbookView(); /* 电子书程序 */
								break;
							}
							case MAINMENU_CALCULATOR:  /* 进入计算器 */
							{
								GUICalculator();  /* 计算器GUI */
								Calculator(); 	  /* 计算器程序 */
								break;
							}
							case MAINMENU_APP:  /* 进入你的应用程序 */
							{
								GUIHelloWorld();  /* 应用程序GUI */
								HelloWorld(); 	  /* 应用程序 */
								break;
							}
							case MAINMENU_SETTINGS:  /* 进入你的应用程序 */
							{
								GUISettings();    /* 系统设置GUI */
								Settings(); 	  /* 应用程序 */
								break;
							}
						}		
				}

			
			}
		 
		}
}		