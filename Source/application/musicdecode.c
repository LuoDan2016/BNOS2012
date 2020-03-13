/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: ������51������ E1101
* �ļ�����: musicdecode.c
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/01/20
* ��������: ��Ƶ���봦��.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* �������� ---------------------------------------------------------------------*/
/* �ļ�ϵͳ���ȫ�ֱ������� */
extern volatile FRESULT res;
extern volatile FATFS fs;	
extern volatile INT16U br,i,j;
extern volatile BYTE  buff[256];    /*�ļ�����    */
volatile FILINFO finfo;
volatile DIR dir;
volatile char* filename;
char playcmd = 0;	                /* ���ſ���   */
unsigned char filecount = 0;        /* �ļ�����   */
extern volatile INT8U menuflag;     /* �˵���ʶΪ */
extern volatile INT8U mainmenuflag; /*���˵���ʶ  */

/*********************************************************************************
** ��������: INT16U VsGetDecodeTime(void).
** ��������: �õ�mp3�Ĳ���ʱ��n sec.
** �������: None.         
** �������: None.
** ���ز���: VS_Read_Reg(VS_DECODE_TIME).
**********************************************************************************/
INT16U VsGetDecodeTime(void)
{ 
    return VS_Read_Reg(VS_DECODE_TIME);   
}


/*
** ������Ԥ��ֵ
** FOR WAV HEAD0 :0X7761 HEAD1:0X7665    
** FOR MIDI HEAD0 :other info HEAD1:0X4D54
** FOR WMA HEAD0 :data speed HEAD1:0X574D
** FOR MP3 HEAD0 :data speed HEAD1:ID
*/
const unsigned int code MediaBitRate[2][16]=
{{0,8,16,24,32,40,48,56,64,80,96,112,128,144,160,0}, 
{0,32,40,48,56,64,80,96,112,128,160,192,224,256,320,0}};

/*********************************************************************************
** ��������: INT16U VsGetBitRate(void).
** ��������: �õ�mp3&wma�Ĳ�����,����Kbps�Ĵ�С.
** �������: None.         
** �������: None.
** ���ز���: MediaBitRate[HEAD1][HEAD0 >> 12].
**********************************************************************************/
INT16U VsGetBitRate(void)
{
	INT16U HEAD0;
	INT16U HEAD1;     
	
    HEAD0=VS_Read_Reg(VS_HDAT0); 
    HEAD1=VS_Read_Reg(VS_HDAT1);
    
    switch(HEAD1)
    {        
        case 0x7665:return 0;//WAV��ʽ
        case 0X4D54:return 1;//MIDI��ʽ 
        case 0X574D://WMA��ʽ
        {
            HEAD1=HEAD0*2/25;
            if((HEAD1%10)>5)return HEAD1/10+1;
            else return HEAD1/10;
        }
        default://MP3��ʽ
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
** ��������: INT8U MusicPlayCmd(INT8U playcmd).
** ��������: ���ֲ��ſ���.
** �������: INT8U playcmd ���ƴ���.         
** �������: None.
** ���ز���: 0 - 3.
**********************************************************************************/
INT8U MusicPlayCmd(INT8U playcmd)
{
	INT8U i;
	switch(playcmd)
	{
		case MUSICPLAY:
		{
		 /* 
		  **���һ����VS1003д��512���ֽ� 320Kbps����Ƶ������������
		  **256���ֽڲ���320Kbps���ų������ֶ�������
		  */
			res=pf_read(buff,256,&br);	 
		 	for(i=0;i<8;i++)
		 	VS_Send_Dat32(buff+(i<<5));
			if(res != 0 || br == 0)
			{
				if(br == 0)	 
					return 1;	   /* ���Ž��� */
				if(res != 0)
					return 3;	   /* ���ļ�ʧ�� */
			}					  
			else
			 	return 0;	       /* �������� */
			break;
		}
		case MUSICPAUSE:	       /* ��ͣ���� */
		{
			return 2;
			break;	
		}		
	}
		return 3;	               /* ���ļ�ʧ�� */		
}

/*********************************************************************************
** ��������: void VsResetDecodeTime(void).
** ��������: �������ʱ�� .
** �������: None.         
** �������: None.
** ���ز���: None.
**********************************************************************************/                       
void VsResetDecodeTime(void)
{
	/* �������� */
	VS_Write_Reg(VS_DECODE_TIME,0x0000);
	VS_Write_Reg(VS_DECODE_TIME,0x0000);
}

/*********************************************************************************
** ��������: char* OpenMusicdir(unsigned char* path,unsigned int mediath).
** ��������: ����ָ��Ŀ¼ָ�������ľ���·�� .
** �������:  pathĿ¼ mediath���صڼ����ļ� mediath=0ʱ��ʾ�����ļ����������ļ�.         
** �������: None.
** ���ز���: None.
**********************************************************************************/ 
char* OpenMusicdir(unsigned char* path,unsigned int mediath)
{
	/* ��Ŀ¼ */
	unsigned char idata returnpath[20];
	filecount = 0;                              /* �ļ�����Ϊ0 */
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
		    	/*Ѱ�Һ�׺Ϊ WMA,WAV,MIDI,P-MIIDI���ļ�*/ 
				if(
					(finfo.fname[i]   == '.' || finfo.fname[i]   == '.' || finfo.fname[i]   == '.' || finfo.fname[i]   == '.') && 
					(finfo.fname[i+1] == 'M' || finfo.fname[i+1] == 'W' || finfo.fname[i+1] == 'W' || finfo.fname[i+1] == 'M') && 
					(finfo.fname[i+2] == 'P' || finfo.fname[i+2] == 'M' || finfo.fname[i+2] == 'A' || finfo.fname[i+2] == 'I') && 
					(finfo.fname[i+3] == '3' || finfo.fname[i+3] == 'A' || finfo.fname[i+3] == 'V' || finfo.fname[i+3] == 'D') &&
					(!(finfo.fattrib & AM_DIR))	                      /* ֻ�����ļ� ������Ŀ¼ */
				  )	 
				{ 
					filecount++; 
					if(mediath == 0)	                              /* ��ʾĿ¼�µ��ļ� */
					{
						//	TransmitString("\r\nMEDIA FILE:");
						//	TransmitString(finfo.fname);
					}
					else if(filecount == mediath)	                  /* ����Ŀ¼��ָ�����ļ� */
					{
					    UnionString(returnpath,path,"/",finfo.fname); /* ��Ŀ¼+ "/" +�ļ����ϲ� */
					 	return returnpath;  						  /* �����ļ��ľ���·�� */
					}
				
				} 
			}
		
	}
		return 0;
}

/*********************************************************************************
** ��������: void MusicDecode(void).
** ��������: ���ֽ��봦�� ����.
** �������: None.         
** �������: None.
** ���ز���: None.
**********************************************************************************/ 
void MusicDecode(void)
{
   
	INT8U playcount = 1,playres  = 1,playmode = 2;
	INT16U mediatime  = 0,playtime = 0,bitrate  = 0;
	INT8U vol=10;	  /* Ĭ������ */
	/* ���SPI���� */
	SPI_Init();	
	VS_Init();	/* ��λ��Ƶ���� */
	VsSetVolume(vol);
	FCLK_FAST(); /* SPI����Ϊ����ģʽ */
	FM_SW=0;/* FM����ر� */
	/* ���ļ� */
		 	 	
	while(1)
	{
	/* ���� KEY_DOWN_EXIT �˳����������������˵� */
	if(!KEY_DOWN_EXIT)
	{
		/* ���SPI���� */
		SPI_Init();
		VS_Init();	/* ��λ��Ƶ���� */
		FCLK_FAST(); /* SPI����Ϊ����ģʽ */
	 	menuflag     = 0;
	    mainmenuflag = 0;
		break;			
	}
	if(playres == 1)
	{
	OSMSG("Into MP3!");	
	/* ��Ŀ¼ �µĵ�1���ļ� PFATFS��֧�ֳ��ļ����������� �ļ������� Ϊ8+3 */
	filename = OpenMusicdir("Music",playcount);
	OSMSG("Open File OK!");	 
		if(filename != "")
		{
			playtime = 0; /* �貥��ʱ��Ϊ0 */
			VsResetDecodeTime();
			Lcd_WriteNumlen(2,playtime,230,68,White,Back_Color,1);	    /*   ��ʾ����ʱ��   �� */
			Lcd_WriteNumlen(2,playtime,256,68,White,Back_Color,1);              /* ��ʾ������ʱ��  �� */
		    res = pf_open(filename);
			LCD_Write_String(128,68,"            ",String_Color,Back_Color,1);/* �������� */
			LCD_Write_String(128,68,finfo.fname,String_Color,Back_Color,1);   /* �������� */
			GUIVolumeico(95,80,48 - vol);   /* ������ʾ */
			GUIProgressBar(70,180,250,6,0); /* ���������� */
			GUIUpSong(90,150,White);        /* ��һ��ͼ��ָ� */	
			GUIDownSong(295,150,White);	    /* ��һ��ͼ��ָ� */
			GUIPlay(170,150,Green);         /* ����ͼ�� */
			GUIPause(200,150,White);        /* ��ͣ��ť */ 
		}
	 }

	 if(VsGetDecodeTime() > playtime)	/* ��ʾһ��/s */
	 {
		playtime = VsGetDecodeTime();		                   /* ��ò���ʱ�� */
		Lcd_WriteNumlen(2,playtime/60,230,68,White,Back_Color,1);	    /* ��ʾ����ʱ��  �� */
		Lcd_WriteNumlen(2,playtime%60,256,68,White,Back_Color,1);              /* ��ʾ������ʱ��  �� */
		GUIProgressBar(70,180,250,6,100 * ((FP32)(playtime) / (FP32)(mediatime)) );						   /* ������ʾ */
	 }
   	if(bitrate == 0 || playres == 1)
	{
		bitrate = VsGetBitRate();/* ��ò����� */
		if(bitrate != 0)
		{
			 /* (�ļ�����(�ֽ�)/(1000/8)/������=�������� */
		     mediatime =  fs.fsize /(1000/8)/bitrate;
			 Lcd_WriteNumlen(2,mediatime/60,281,68,White,Back_Color,1);           /* ��ʱ��  �� */
			 Lcd_WriteNumlen(2,mediatime%60,305,68,White,Back_Color,1);	          /* ��ʱ��  �� */
			 Lcd_WriteNumlen(3,bitrate,264,50,White,Back_Color,1);	              /* ��������ʾ */
			 LCD_Write_String(289,50,"Kbps",White,Back_Color,1);	              /* ��������ʾ */
		}
	}				
		playres = MusicPlayCmd(playcmd);   /* ���ſ��� */
		if(playres == 1)                   /* ����ģʽ���� */
		{
			switch(playmode)
			{
				case GENERALMODE:  /* ��ͨģʽ */
					playcount++;
					break;	
				case SINGLECYCLE:  /* ����ѭ�� */
				   playcount = playcount;
				   break;
			    case    ALLCYCLE:  /* ȫ��ѭ�� */
				{
					if(playcount < 6)
						playcount++;
					 else
					 	playcount = 1;
					break;		
				}
			}	
		}
		if(!KEY_UP_VOL )  /* �������� */
		{
			if(vol <49)
				vol+=1;
			else
				vol=1;			
			VsSetVolume(vol);
			GUIVolumeico(95,80,48 - vol);		/* ������ʾ */
		}

		if(!KEY_ENTER && playcmd == 2)	        /* ���� */ 
		{
			playcmd=0;
 			GUIPlay(170,150,Green);             /* ����ͼ�� */
			GUIPause(200,150,White);            /* ��ͣ��ť */
			OSTimeDly(10);
		}			
		if(!KEY_ENTER && playcmd == 0)	        /* ��ͣ */
		{
			playcmd=2;
			GUIPlay(170,150,White);             /* ����ͼ�� */
			GUIPause(200,150,Green);            /* ��ͣ��ť */
			OSTimeDly(10);
		}		
		if(!KEY_PRE)		                    /* ��һ�� */
		{
			playcount--;
			playres = 1;
			GUIUpSong(90,150,Green);            /*��һ��ͼ��*/
		}
		if(!KEY_NEXT)	                        /* ��һ�� */
		{
			playcount++;
			playres = 1;	 	
			GUIDownSong(295,150,Green);	        /* ��һ��ͼ�� */
		}
		

			
	}

				

}