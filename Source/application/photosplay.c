/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: photosplay.c
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/01/20
* 功能描述: 电子相册播放.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* 变量声明 ---------------------------------------------------------------------*/
extern volatile INT8U menuflag;     /* 菜单标识为 */
extern volatile INT8U mainmenuflag; /*主菜单标识   */
extern volatile INT8U filecount;    /* 文件计数 */

/* 文件系统相关全局变量声明 */
extern volatile FRESULT res;
extern volatile FATFS fs;	
extern volatile INT16U br,i,j;
extern volatile BYTE  buff[256];   /*文件缓存*/
extern volatile FILINFO finfo;
extern volatile DIR dir;
extern volatile char* filename;

/*********************************************************************************
** 函数名称: char* OpenPhotosdir(unsigned char* path,unsigned int photosth).
** 功能描述: 返回指定目录指定序数的绝对路径.
** 输入参数: path目录 mediath返回第几个文件 mediath=0时显示所有文件但不返回文件.         
** 输出参数: None.
** 返回参数: returnpath 文件路径.
**********************************************************************************/
char* OpenPhotosdir(unsigned char* path,unsigned int photosth)
{
	/* 读目录 */
	unsigned char idata returnpath[20];
	filecount = 0; /* 文件计数为 0 */
	res =  pf_opendir(&dir,path);  
	for(;dir.sect>0;)
	{
		res = pf_readdir(&dir,&finfo);
		if(finfo.fname[0] == 0 || res != 0)	    /*  文件出错跳出*/	
		{
			return 1;
			break;	
		}
			for(i = 0;i < 13;i ++) 
			{ 	
		    	/*寻找后缀为 .BMP的文件*/ 
				if(
					(finfo.fname[i]   == '.') &&
					(finfo.fname[i+1] == 'B') &&
					(finfo.fname[i+2] == 'M') &&
					(finfo.fname[i+3] == 'P') &&
					(!(finfo.fattrib & AM_DIR))	 /* 只查找文件 不包含目录 */
				  )	 
				{ 
					filecount++; 
					if(filecount == photosth)	   /* 返回目录下指定的文件 */
					{
					    UnionString(returnpath,path,"/",finfo.fname); /* 将目录+ "/" +文件名合并 */
					 	return returnpath;  						  /* 返回文件的绝对路径 */
					}
				
				} 
			}
		
	}
		return 1;
}

/* 相片播放 */
/* 24 BIT BMP 解码最大限制 240 x 120 */
/*********************************************************************************
** 函数名称: void PhotosPlay(void).
** 功能描述: 相片播放.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void PhotosPlay(void)
{
	INT8U playres = 0, playcount = 1;
    while(1)
	{
		if(playres == 0)
		{
			filename = OpenPhotosdir("Photos",playcount);
			/* 上一张 */
			GUIUpSong(35,110,White);
			/* 下一张 */
			GUIDownSong(350,110,White);
			if(filename != 1)
			{
				LCD_FilledRectangle(75,60,245,125,Black);	        /* 方块 width : 240  high :  120 */
				BmpDecode(75,60,filename);
			}
			playres = 1;	
		}
		/* 按键 KEY_DOWN_EXIT 退出并返回主菜单 */
		if(!KEY_DOWN_EXIT)					
		{
		 	menuflag     = 0;
		    mainmenuflag = 0;
			break;			
		}
		/* 上一张 */
		if(!KEY_PRE)
		{
			GUIUpSong(35,110,Green);
			if(playcount <= filecount)
			{
				playcount++;
				playres = 0;
			}		
		}
		/* 下一张 */
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