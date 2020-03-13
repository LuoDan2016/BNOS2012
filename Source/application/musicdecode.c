/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: musicdecode.c
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/01/20
* 功能描述: 音频解码处理.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* 变量声明 ---------------------------------------------------------------------*/
/* 文件系统相关全局变量声明 */
extern volatile FRESULT res;
extern volatile FATFS fs;	
extern volatile INT16U br,i,j;
extern volatile BYTE  buff[256];    /*文件缓存    */
volatile FILINFO finfo;
volatile DIR dir;
volatile char* filename;
char playcmd = 0;	                /* 播放控制   */
unsigned char filecount = 0;        /* 文件计数   */
extern volatile INT8U menuflag;     /* 菜单标识为 */
extern volatile INT8U mainmenuflag; /*主菜单标识  */

/*********************************************************************************
** 函数名称: INT16U VsGetDecodeTime(void).
** 功能描述: 得到mp3的播放时间n sec.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: VS_Read_Reg(VS_DECODE_TIME).
**********************************************************************************/
INT16U VsGetDecodeTime(void)
{ 
    return VS_Read_Reg(VS_DECODE_TIME);   
}


/*
** 比特率预定值
** FOR WAV HEAD0 :0X7761 HEAD1:0X7665    
** FOR MIDI HEAD0 :other info HEAD1:0X4D54
** FOR WMA HEAD0 :data speed HEAD1:0X574D
** FOR MP3 HEAD0 :data speed HEAD1:ID
*/
const unsigned int code MediaBitRate[2][16]=
{{0,8,16,24,32,40,48,56,64,80,96,112,128,144,160,0}, 
{0,32,40,48,56,64,80,96,112,128,160,192,224,256,320,0}};

/*********************************************************************************
** 函数名称: INT16U VsGetBitRate(void).
** 功能描述: 得到mp3&wma的波特率,返回Kbps的大小.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: MediaBitRate[HEAD1][HEAD0 >> 12].
**********************************************************************************/
INT16U VsGetBitRate(void)
{
	INT16U HEAD0;
	INT16U HEAD1;     
	
    HEAD0=VS_Read_Reg(VS_HDAT0); 
    HEAD1=VS_Read_Reg(VS_HDAT1);
    
    switch(HEAD1)
    {        
        case 0x7665:return 0;//WAV格式
        case 0X4D54:return 1;//MIDI格式 
        case 0X574D://WMA格式
        {
            HEAD1=HEAD0*2/25;
            if((HEAD1%10)>5)return HEAD1/10+1;
            else return HEAD1/10;
        }
        default://MP3格式
        {
            HEAD1>>=3;
            HEAD1=HEAD1&0x03; 
            if(HEAD1==3)HEAD1=1;
            else HEAD1=0;
            return MediaBitRate[HEAD1][HEAD0 >> 12];
        }
    } 
}  

/*********************************************************************************
** 函数名称: INT8U MusicPlayCmd(INT8U playcmd).
** 功能描述: 音乐播放控制.
** 输入参数: INT8U playcmd 控制代码.         
** 输出参数: None.
** 返回参数: 0 - 3.
**********************************************************************************/
INT8U MusicPlayCmd(INT8U playcmd)
{
	INT8U i;
	switch(playcmd)
	{
		case MUSICPLAY:
		{
		 /* 
		  **最低一次向VS1003写入512个字节 320Kbps的音频才能正常解码
		  **256个字节播放320Kbps播放出声音现断续现象
		  */
			res=pf_read(buff,256,&br);	 
		 	for(i=0;i<8;i++)
		 	VS_Send_Dat32(buff+(i<<5));
			if(res != 0 || br == 0)
			{
				if(br == 0)	 
					return 1;	   /* 播放结束 */
				if(res != 0)
					return 3;	   /* 打开文件失败 */
			}					  
			else
			 	return 0;	       /* 正常播放 */
			break;
		}
		case MUSICPAUSE:	       /* 暂停播放 */
		{
			return 2;
			break;	
		}		
	}
		return 3;	               /* 打开文件失败 */		
}

/*********************************************************************************
** 函数名称: void VsResetDecodeTime(void).
** 功能描述: 重设解码时间 .
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/                       
void VsResetDecodeTime(void)
{
	/* 操作两次 */
	VS_Write_Reg(VS_DECODE_TIME,0x0000);
	VS_Write_Reg(VS_DECODE_TIME,0x0000);
}

/*********************************************************************************
** 函数名称: char* OpenMusicdir(unsigned char* path,unsigned int mediath).
** 功能描述: 返回指定目录指定序数的绝对路径 .
** 输入参数:  path目录 mediath返回第几个文件 mediath=0时显示所有文件但不返回文件.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/ 
char* OpenMusicdir(unsigned char* path,unsigned int mediath)
{
	/* 读目录 */
	unsigned char idata returnpath[20];
	filecount = 0;                              /* 文件计数为0 */
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
		    	/*寻找后缀为 WMA,WAV,MIDI,P-MIIDI的文件*/ 
				if(
					(finfo.fname[i]   == '.' || finfo.fname[i]   == '.' || finfo.fname[i]   == '.' || finfo.fname[i]   == '.') && 
					(finfo.fname[i+1] == 'M' || finfo.fname[i+1] == 'W' || finfo.fname[i+1] == 'W' || finfo.fname[i+1] == 'M') && 
					(finfo.fname[i+2] == 'P' || finfo.fname[i+2] == 'M' || finfo.fname[i+2] == 'A' || finfo.fname[i+2] == 'I') && 
					(finfo.fname[i+3] == '3' || finfo.fname[i+3] == 'A' || finfo.fname[i+3] == 'V' || finfo.fname[i+3] == 'D') &&
					(!(finfo.fattrib & AM_DIR))	                      /* 只查找文件 不包含目录 */
				  )	 
				{ 
					filecount++; 
					if(mediath == 0)	                              /* 显示目录下的文件 */
					{
						//	TransmitString("\r\nMEDIA FILE:");
						//	TransmitString(finfo.fname);
					}
					else if(filecount == mediath)	                  /* 返回目录下指定的文件 */
					{
					    UnionString(returnpath,path,"/",finfo.fname); /* 将目录+ "/" +文件名合并 */
					 	return returnpath;  						  /* 返回文件的绝对路径 */
					}
				
				} 
			}
		
	}
		return 0;
}

/*********************************************************************************
** 函数名称: void MusicDecode(void).
** 功能描述: 音乐解码处理 播放.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/ 
void MusicDecode(void)
{
   
	INT8U playcount = 1,playres  = 1,playmode = 2;
	INT16U mediatime  = 0,playtime = 0,bitrate  = 0;
	INT8U vol=10;	  /* 默认声量 */
	/* 清除SPI数据 */
	SPI_Init();	
	VS_Init();	/* 复位音频解码 */
	VsSetVolume(vol);
	FCLK_FAST(); /* SPI设置为高速模式 */
	FM_SW=0;/* FM输出关闭 */
	/* 读文件 */
		 	 	
	while(1)
	{
	/* 按键 KEY_DOWN_EXIT 退出播放器并返回主菜单 */
	if(!KEY_DOWN_EXIT)
	{
		/* 清除SPI数据 */
		SPI_Init();
		VS_Init();	/* 复位音频解码 */
		FCLK_FAST(); /* SPI设置为高速模式 */
	 	menuflag     = 0;
	    mainmenuflag = 0;
		break;			
	}
	if(playres == 1)
	{
	OSMSG("Into MP3!");	
	/* 打开目录 下的第1个文件 PFATFS不支持长文件名和中文名 文件名长度 为8+3 */
	filename = OpenMusicdir("Music",playcount);
	OSMSG("Open File OK!");	 
		if(filename != "")
		{
			playtime = 0; /* 设播放时间为0 */
			VsResetDecodeTime();
			Lcd_WriteNumlen(2,playtime,230,68,White,Back_Color,1);	    /*   显示播放时间   分 */
			Lcd_WriteNumlen(2,playtime,256,68,White,Back_Color,1);              /* 显示播播放时间  秒 */
		    res = pf_open(filename);
			LCD_Write_String(128,68,"            ",String_Color,Back_Color,1);/* 歌曲标题 */
			LCD_Write_String(128,68,finfo.fname,String_Color,Back_Color,1);   /* 歌曲标题 */
			GUIVolumeico(95,80,48 - vol);   /* 音量显示 */
			GUIProgressBar(70,180,250,6,0); /* 进度条重设 */
			GUIUpSong(90,150,White);        /* 上一首图标恢复 */	
			GUIDownSong(295,150,White);	    /* 下一首图标恢复 */
			GUIPlay(170,150,Green);         /* 播放图标 */
			GUIPause(200,150,White);        /* 暂停按钮 */ 
		}
	 }

	 if(VsGetDecodeTime() > playtime)	/* 显示一次/s */
	 {
		playtime = VsGetDecodeTime();		                   /* 获得播放时间 */
		Lcd_WriteNumlen(2,playtime/60,230,68,White,Back_Color,1);	    /* 显示播放时间  分 */
		Lcd_WriteNumlen(2,playtime%60,256,68,White,Back_Color,1);              /* 显示播播放时间  秒 */
		GUIProgressBar(70,180,250,6,100 * ((FP32)(playtime) / (FP32)(mediatime)) );						   /* 进度显示 */
	 }
   	if(bitrate == 0 || playres == 1)
	{
		bitrate = VsGetBitRate();/* 获得波特率 */
		if(bitrate != 0)
		{
			 /* (文件长度(字节)/(1000/8)/比特率=持续秒数 */
		     mediatime =  fs.fsize /(1000/8)/bitrate;
			 Lcd_WriteNumlen(2,mediatime/60,281,68,White,Back_Color,1);           /* 总时长  分 */
			 Lcd_WriteNumlen(2,mediatime%60,305,68,White,Back_Color,1);	          /* 总时长  秒 */
			 Lcd_WriteNumlen(3,bitrate,264,50,White,Back_Color,1);	              /* 波特率显示 */
			 LCD_Write_String(289,50,"Kbps",White,Back_Color,1);	              /* 波特率显示 */
		}
	}				
		playres = MusicPlayCmd(playcmd);   /* 播放控制 */
		if(playres == 1)                   /* 播放模式设置 */
		{
			switch(playmode)
			{
				case GENERALMODE:  /* 普通模式 */
					playcount++;
					break;	
				case SINGLECYCLE:  /* 单曲循环 */
				   playcount = playcount;
				   break;
			    case    ALLCYCLE:  /* 全部循环 */
				{
					if(playcount < 6)
						playcount++;
					 else
					 	playcount = 1;
					break;		
				}
			}	
		}
		if(!KEY_UP_VOL )  /* 音量调节 */
		{
			if(vol <49)
				vol+=1;
			else
				vol=1;			
			VsSetVolume(vol);
			GUIVolumeico(95,80,48 - vol);		/* 音量显示 */
		}

		if(!KEY_ENTER && playcmd == 2)	        /* 播放 */ 
		{
			playcmd=0;
 			GUIPlay(170,150,Green);             /* 播放图标 */
			GUIPause(200,150,White);            /* 暂停按钮 */
			OSTimeDly(10);
		}			
		if(!KEY_ENTER && playcmd == 0)	        /* 暂停 */
		{
			playcmd=2;
			GUIPlay(170,150,White);             /* 播放图标 */
			GUIPause(200,150,Green);            /* 暂停按钮 */
			OSTimeDly(10);
		}		
		if(!KEY_PRE)		                    /* 上一首 */
		{
			playcount--;
			playres = 1;
			GUIUpSong(90,150,Green);            /*下一首图标*/
		}
		if(!KEY_NEXT)	                        /* 下一首 */
		{
			playcount++;
			playres = 1;	 	
			GUIDownSong(295,150,Green);	        /* 上一曲图标 */
		}
		

			
	}

				

}