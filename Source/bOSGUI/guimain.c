/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: ������51������������ E1101
* �ļ�����: guimain.c
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/01/20
* ��������: ��GUI����.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"
/* 
**�˵�ȫ�ֱ��� 
*/
volatile INT8U menuflag  = 0;      /* �˵���ʶΪ */ 
volatile INT8U choseflag = 0;      /* ѡ���ʶ   */
volatile INT8U mainmenuflag   = 0; /*���˵���ʶ   */
/* ����ⲿ���� */	
extern volatile INT16U xcoordinate,ycoordinate;
/* �������� ---------------------------------------------------------------------*/
extern SYS_TIME datetime;	    /* ϵͳʱ�� */
/*  �����ֿ����ʶ 1Ϊ��ȷ ���������� */
extern INT8U CHNCHEK;
/* �ļ�ϵͳ���ȫ�ֱ������� */
extern volatile FRESULT res;
extern volatile FATFS fs;	
extern volatile INT16U br,i,j;
extern volatile BYTE  buff[256];   /*�ļ�����*/
extern volatile FILINFO finfo;
extern volatile DIR dir;
extern volatile char* filename;
/*********************************************************************************
** ��������: void GUI_BRCLOGO(void).
** ��������: ������LOGO��ʾ ���SD�����Ҵ��ڸ�ͼ���ļ����SD���� ����� SPI FLASH����.
** �������: None.         
** �������: None.
** ���ز���: None.
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
	/* �������� */	
	GUIProgressBar(0,LCD_YSIZE_TFT - 6,400,6,80);		
}

/*********************************************************************************
** ��������: void GUI_BNOSSTART(void).
** ��������: BNOS������ʾ.
** �������: None.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void GUI_BNOSWALPAPER(void)
{
	INT16U i,j;
	/* �趨������ɫ */
	LCD_FilledRectangle(0,0,400,216,WALLCOLOR);
	/* ������ʽ */
	LCD_FilledRectangle(0,0,400,20,RGB(36,39,39));
	/* ����ͨ�� */
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
** ��������: void GuiMainMenu(void).
** ��������: ��������GUI.
** �������: None.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void GUI_MainMenu(void)
{
	INT8U *DISLANG;
	switch(USELANG)	     /* ����ѡ�� */
		{
			case 0:			 /* English  */
				DISLANG = "EN";
				break;
			case 1:			 /* �������� */
				DISLANG = "CH";
				break;
			case 2:			 /* Ĭ������ */
			 	if(CHNCHEK)
					DISLANG = "CH";
				else
					DISLANG = "EN";	
				break;
		}	
	/* �����洰�� */
	/* ������ */	
	LCD_FilledRectangle(LCD_XSIZE_TFT - LCD_XSIZE_TFT,LCD_YSIZE_TFT - 24,LCD_XSIZE_TFT,1,RGB(127,127,127));
	LCD_FilledRectangle(LCD_XSIZE_TFT - LCD_XSIZE_TFT,LCD_YSIZE_TFT - 23,LCD_XSIZE_TFT,23,TASKBARCOLOR);/* ������ */
	Lcd_WriteNumlen(2,datetime.hour,LCD_XSIZE_TFT - 44,LCD_YSIZE_TFT - 16,White,TASKBARCOLOR,1);	    /* ʱ����ʾ */
	LCD_Write_String(LCD_XSIZE_TFT - 28,LCD_YSIZE_TFT - 16,":",White,TASKBARCOLOR,1);
	Lcd_WriteNumlen(2,datetime.min,LCD_XSIZE_TFT - 20,LCD_YSIZE_TFT - 16,White,TASKBARCOLOR,1);	
	GUIToolICOPower(340,220,8);	                                        /* ������ʾ */
	LCD_Write_String(310,LCD_YSIZE_TFT - 16,DISLANG,White,TASKBARCOLOR,1);	/* ϵͳ���� */
	LCD_FilledRectangle(4,LCD_YSIZE_TFT - 20,20,4,Magenta);	            /* ��ʼ�˵� */
	LCD_FilledRectangle(4,LCD_YSIZE_TFT - 14,20,4,Green);
	LCD_FilledRectangle(4,LCD_YSIZE_TFT - 8,20,4,Blue2);

}

/*********************************************************************************
** ��������: void MainIco(void).
** ��������: ������˵�ICO.
** �������: None.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void MainIco(void)
{
	INT8U res;
	/* ���˵���ʶΪMAINMENU 0 */
	menuflag = MAINMENU;  
	switch(USELANG)	     /* ����ѡ�� */
	{
		case 0:			 /* English  */
			{
			EN_MAINMENUTITLE;
			}
			break;
		case 1:			 /* �������� */
			CH_MAINMENUTITLE; 
			break;
		case 2:			 /* Ĭ������ */
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
			/* ��һ�в˵�ICO */
			FlashGraphDis(50,30,44,45,FLASHADDR_MUSIC);
			FlashGraphDis(140,30,44,45,FLASHADDR_PHOTOS);
			FlashGraphDis(220,30,44,45,FLASHADDR_RADIO);
			FlashGraphDis(300,30,44,45,	FLASHADDR_CALENDAR);
			/* �ڶ��в˵�ICO */	
			FlashGraphDis(50,120,44,45,FLASHADDR_EBOOK	);
			FlashGraphDis(140,120,44,45,FLASHADDR_CALCU);
			FlashGraphDis(220,120,44,45,FLASHADDR_APP);
			FlashGraphDis(300,120,44,45,FLASHADDR_SETTINGS);
			break;
		case 1:
		{	
			/* ��һ�в˵�ICO */
			res = BmpDecode(50,30,"system/music.bmp");
			BmpDecode(140,30,"system/Photos.bmp");
			BmpDecode(220,30,"system/Radio.bmp");
			BmpDecode(300,30,"system/Calendar.bmp");
			/* �ڶ��в˵�ICO */	
			BmpDecode(50,120,"system/Ebook.bmp");
			BmpDecode(140,120,"system/Calcu.bmp");
			BmpDecode(220,120,"system/app.bmp");
			BmpDecode(300,120,"system/Settings.bmp");
			if(res == 1)
			{
				/* ��һ�в˵�ICO */
				FlashGraphDis(50,30,44,45,FLASHADDR_MUSIC);
				FlashGraphDis(140,30,44,45,FLASHADDR_PHOTOS);
				FlashGraphDis(220,30,44,45,FLASHADDR_RADIO);
				FlashGraphDis(300,30,44,45,	FLASHADDR_CALENDAR);
				/* �ڶ��в˵�ICO */	
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
** ��������: void MovMenu(void).
** ��������: ����̬ѡ�в˵�.
** �������: None.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void MovMenu(void)
{
		switch(menuflag)
		{
			case MAINMENU:
			{	 
				/* ���˵� ͼ�� */
				if(mainmenuflag == 0)
					{
						/* ���� */
						GUI_BNOSWALPAPER();
						/* ����˵�ͼ�� */
						MainIco();
						MouseInit(10,40);	 /* �趨���λ�� */
						mainmenuflag = 1;
					} 
				if(	/* Music */
				xcoordinate >= 33 && xcoordinate <= 85 && ycoordinate >= 30 && ycoordinate <= 100 
				)	/* ���� */	   /* ���ֲ˵����� */
				{
					if(	choseflag != MAINMENU_MUSIC)
					{	
						switch(USELANG)	     /* ����ѡ�� */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_MUSIC,1);
								}
								break;
							case 1:			 /* �������� */
								CH_MAINMENUSEL(MAINMENU_MUSIC,1); 
								break;
							case 2:			 /* Ĭ������ */
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
				else if(choseflag == MAINMENU_MUSIC)	 /* �뿪 */
				{
						switch(USELANG)	     /* ����ѡ�� */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_MUSIC,0);
								}
								break;
							case 1:			 /* �������� */
								CH_MAINMENUSEL(MAINMENU_MUSIC,0); 
								break;
							case 2:			 /* Ĭ������ */
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
				)	 	/* ���� */			/* ���˵����� */
				{
						switch(USELANG)	     /* ����ѡ�� */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_PHOTOS,1);
								}
								break;
							case 1:			 /* �������� */
								CH_MAINMENUSEL(MAINMENU_PHOTOS,1); 
								break;
							case 2:			 /* Ĭ������ */
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
				else if(choseflag == MAINMENU_PHOTOS)	 /* �뿪 */		  /* ���˵����� */
				{
					switch(USELANG)	     /* ����ѡ�� */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_PHOTOS,0);
								}
								break;
							case 1:			 /* �������� */
								CH_MAINMENUSEL(MAINMENU_PHOTOS,0); 
								break;
							case 2:			 /* Ĭ������ */
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
				)	  	/* ���� */	  	/* �������˵������ */
				{
					switch(USELANG)	     /* ����ѡ�� */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_RADIO,1);
								}
								break;
							case 1:			 /* �������� */
								CH_MAINMENUSEL(MAINMENU_RADIO,1); 
								break;
							case 2:			 /* Ĭ������ */
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
				else if(choseflag == MAINMENU_RADIO)	 /* �뿪 */	   	/* �����˵������ */
				{
						switch(USELANG)	     /* ����ѡ�� */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_RADIO,0);
								}
								break;
							case 1:			 /* �������� */
								CH_MAINMENUSEL(MAINMENU_RADIO,0); 
								break;
							case 2:			 /* Ĭ������ */
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
				)	 	/* ���� */	     /* �����˵����� */
				{
						switch(USELANG)	     /* ����ѡ�� */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_CALENDAR,1);
								}
								break;
							case 1:			 /* �������� */
								CH_MAINMENUSEL(MAINMENU_CALENDAR,1); 
								break;
							case 2:			 /* Ĭ������ */
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
				else if(choseflag == MAINMENU_CALENDAR)	 /* �뿪 */	  /* �����˵����� */
				{
					switch(USELANG)	     /* ����ѡ�� */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_CALENDAR,0);
								}
								break;
							case 1:			 /* �������� */
								CH_MAINMENUSEL(MAINMENU_CALENDAR,0); 
								break;
							case 2:			 /* Ĭ������ */
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
				)	 	/* ���� */	     /* ������˵����� */
				{
					switch(USELANG)	     /* ����ѡ�� */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_EBOOK,1);
								}
								break;
							case 1:			 /* �������� */
								CH_MAINMENUSEL(MAINMENU_EBOOK,1); 
								break;
							case 2:			 /* Ĭ������ */
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
				else if(choseflag == MAINMENU_EBOOK)	 /* �뿪 */	    /* ������˵����� */
				{
					switch(USELANG)	     /* ����ѡ�� */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_EBOOK,0);
								}
								break;
							case 1:			 /* �������� */
								CH_MAINMENUSEL(MAINMENU_EBOOK,0); 
								break;
							case 2:			 /* Ĭ������ */
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
				)	  	/* ���� */	 /* �������˵����� */
				{
					switch(USELANG)	     /* ����ѡ�� */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_CALCULATOR,1);
								}
								break;
							case 1:			 /* �������� */
								CH_MAINMENUSEL(MAINMENU_CALCULATOR,1); 
								break;
							case 2:			 /* Ĭ������ */
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
				else if(choseflag == MAINMENU_CALCULATOR)	 /* �뿪 */	  /* �������˵����� */
				{
						switch(USELANG)	     /* ����ѡ�� */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_CALCULATOR,0);
								}
								break;
							case 1:			 /* �������� */
								CH_MAINMENUSEL(MAINMENU_CALCULATOR,0); 
								break;
							case 2:			 /* Ĭ������ */
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
				)	  	/* ���� */		 	/* Ӧ�ó���˵����� */
				{
						switch(USELANG)	     /* ����ѡ�� */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_APP,1);
								}
								break;
							case 1:			 /* �������� */
								CH_MAINMENUSEL(MAINMENU_APP,1); 
								break;
							case 2:			 /* Ĭ������ */
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
				else if(choseflag == MAINMENU_APP)	 /* �뿪 */	  	/* Ӧ�ó���˵����� */
				{
						switch(USELANG)	     /* ����ѡ�� */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_APP,0);
								}
								break;
							case 1:			 /* �������� */
								CH_MAINMENUSEL(MAINMENU_APP,0); 
								break;
							case 2:			 /* Ĭ������ */
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
				)	  	/* ���� */	  /* ϵͳ���ò˵����� */
				{
					switch(USELANG)	     /* ����ѡ�� */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_SETTINGS,1);
								}
								break;
							case 1:			 /* �������� */
								CH_MAINMENUSEL(MAINMENU_SETTINGS,1); 
								break;
							case 2:			 /* Ĭ������ */
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
				else if(choseflag == MAINMENU_SETTINGS)	 /* �뿪 */	    /* ϵͳ���ò˵����� */
				{
					switch(USELANG)	     /* ����ѡ�� */
						{
							case 0:			 /* English  */
								{
								EN_MAINMENUSEL(MAINMENU_SETTINGS,0);
								}
								break;
							case 1:			 /* �������� */
								CH_MAINMENUSEL(MAINMENU_SETTINGS,0); 
								break;
							case 2:			 /* Ĭ������ */
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
				/* ����MODE������ */
			if(!KEY_ENTER)
				{
						switch(choseflag)
						{
							case MAINMENU_MUSIC:   /* �������ֲ����� */
							{
								GuiMusicPlayer();  /* ������GUI */
								MusicDecode(); 	   /* ��Ƶ������� */
								break;
							} 
							case MAINMENU_PHOTOS:  /* ���������� */
							{
								GUIPhotos();  /* ������GUI */
						 	    PhotosPlay(); /* ��Ƭ���� */
								break;
							}
							case MAINMENU_RADIO:  /* ���������� */
							{
								GUIRadio();		 /* ������GUI */
								FMRadio();		 /* ���������� */
								break;
							}
							case MAINMENU_CALENDAR:  /* ���������� */
							{
								GUICalendar();  /* ������GUI */
								CalendarApp();	/* ���������� */
								break;
							} 
							case MAINMENU_EBOOK:  /* ��������� */
							{
								GUIEbook();  /* ������GUI */
								EbookView(); /* ��������� */
								break;
							}
							case MAINMENU_CALCULATOR:  /* ��������� */
							{
								GUICalculator();  /* ������GUI */
								Calculator(); 	  /* ���������� */
								break;
							}
							case MAINMENU_APP:  /* �������Ӧ�ó��� */
							{
								GUIHelloWorld();  /* Ӧ�ó���GUI */
								HelloWorld(); 	  /* Ӧ�ó��� */
								break;
							}
							case MAINMENU_SETTINGS:  /* �������Ӧ�ó��� */
							{
								GUISettings();    /* ϵͳ����GUI */
								Settings(); 	  /* Ӧ�ó��� */
								break;
							}
						}		
				}

			
			}
		 
		}
}		