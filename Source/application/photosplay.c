/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: ������51������ E1101
* �ļ�����: photosplay.c
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/01/20
* ��������: ������Ქ��.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* �������� ---------------------------------------------------------------------*/
extern volatile INT8U menuflag;     /* �˵���ʶΪ */
extern volatile INT8U mainmenuflag; /*���˵���ʶ   */
extern volatile INT8U filecount;    /* �ļ����� */

/* �ļ�ϵͳ���ȫ�ֱ������� */
extern volatile FRESULT res;
extern volatile FATFS fs;	
extern volatile INT16U br,i,j;
extern volatile BYTE  buff[256];   /*�ļ�����*/
extern volatile FILINFO finfo;
extern volatile DIR dir;
extern volatile char* filename;

/*********************************************************************************
** ��������: char* OpenPhotosdir(unsigned char* path,unsigned int photosth).
** ��������: ����ָ��Ŀ¼ָ�������ľ���·��.
** �������: pathĿ¼ mediath���صڼ����ļ� mediath=0ʱ��ʾ�����ļ����������ļ�.         
** �������: None.
** ���ز���: returnpath �ļ�·��.
**********************************************************************************/
char* OpenPhotosdir(unsigned char* path,unsigned int photosth)
{
	/* ��Ŀ¼ */
	unsigned char idata returnpath[20];
	filecount = 0; /* �ļ�����Ϊ 0 */
	res =  pf_opendir(&dir,path);  
	for(;dir.sect>0;)
	{
		res = pf_readdir(&dir,&finfo);
		if(finfo.fname[0] == 0 || res != 0)	    /*  �ļ���������*/	
		{
			return 1;
			break;	
		}
			for(i = 0;i < 13;i ++) 
			{ 	
		    	/*Ѱ�Һ�׺Ϊ .BMP���ļ�*/ 
				if(
					(finfo.fname[i]   == '.') &&
					(finfo.fname[i+1] == 'B') &&
					(finfo.fname[i+2] == 'M') &&
					(finfo.fname[i+3] == 'P') &&
					(!(finfo.fattrib & AM_DIR))	 /* ֻ�����ļ� ������Ŀ¼ */
				  )	 
				{ 
					filecount++; 
					if(filecount == photosth)	   /* ����Ŀ¼��ָ�����ļ� */
					{
					    UnionString(returnpath,path,"/",finfo.fname); /* ��Ŀ¼+ "/" +�ļ����ϲ� */
					 	return returnpath;  						  /* �����ļ��ľ���·�� */
					}
				
				} 
			}
		
	}
		return 1;
}

/* ��Ƭ���� */
/* 24 BIT BMP ����������� 240 x 120 */
/*********************************************************************************
** ��������: void PhotosPlay(void).
** ��������: ��Ƭ����.
** �������: None.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void PhotosPlay(void)
{
	INT8U playres = 0, playcount = 1;
    while(1)
	{
		if(playres == 0)
		{
			filename = OpenPhotosdir("Photos",playcount);
			/* ��һ�� */
			GUIUpSong(35,110,White);
			/* ��һ�� */
			GUIDownSong(350,110,White);
			if(filename != 1)
			{
				LCD_FilledRectangle(75,60,245,125,Black);	        /* ���� width : 240  high :  120 */
				BmpDecode(75,60,filename);
			}
			playres = 1;	
		}
		/* ���� KEY_DOWN_EXIT �˳����������˵� */
		if(!KEY_DOWN_EXIT)					
		{
		 	menuflag     = 0;
		    mainmenuflag = 0;
			break;			
		}
		/* ��һ�� */
		if(!KEY_PRE)
		{
			GUIUpSong(35,110,Green);
			if(playcount <= filecount)
			{
				playcount++;
				playres = 0;
			}		
		}
		/* ��һ�� */
		if(!KEY_NEXT)
		{
		   	GUIDownSong(350,110,Green);
		
			if(playcount > 1)
			{
				playcount--;
				playres = 0;
			}		
		}
	}
}