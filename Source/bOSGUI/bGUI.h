/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: ������51������ E1101
* �ļ�����: BGUI.H
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.1
* ��������: 2012/01/20
* ��������: �ļ�����.
**********************************************************************************/

/* bGUI CFG */
#define LCD_XSIZE_TFT 	(400)  /* LCD TFT Level Size */	
#define LCD_YSIZE_TFT 	(240)  /* LCD TFT Vertical Size */

/* Setting LCD Color Mode */
#define LCD_COLOR_MODE_16BIT   /* 24bit or 16bit,LCD Clor Mode */
#define DATA_MODE	0		   /* DATA_MODE = 1 :MSB(Most Significant Byte),DATA_MODE = 0 LSB(Least Significant Byte)*/
#define WORDHIGH		 16	   /* "LCD_Write_String" Function Character Height */

/* Color Mode Transform */
#ifdef  LCD_COLOR_MODE_16BIT
	/* Color Define 16-bit */
	#define White          0xFFFF
	#define Black          0x0000
	#define Grey           0xF7DE
	#define Blue           0x001F
	#define Blue2          0x051F
	#define Red            0xF800
	#define Magenta        0xF81F
	#define Green          0x07E0
	#define Cyan           0x7FFF   
	#define Yellow         0xFFE0
	#define Gray           0x738E
	#define Back_Color 	   0x0000
	#define String_Color   0x07ff
//	#define NotselColor	   0xFFFF
//	#define SelectedColor  0xFFE0
	#if DATA_MODE					/* Data Memory Mode*/
		#define RGB(b,g,r) ((unsigned short)(r & (~(0x07))) << 8) | ((unsigned short)(g & (~(0x03))) << 3) | ((unsigned short)(b & (~(0x7))) >> 3) 
	#else 
		#define RGB(r,g,b) ((unsigned short)(r & (~(0x07))) << 8) | ((unsigned short)(g & (~(0x03))) << 3) | ((unsigned short)(b & (~(0x7))) >> 3) 
	#endif /* DATA_MODE */
#else
	#define RGB(r,g,b) (unsigned int)( (r << 16) + (g << 8) + b )
#endif /* LCD_COLOR_MODE */
		
/* bGUI Color Define */
#define CTITLE       White   /* Title Color */
#define CTITLEBAR    RGB(152,180,208) /* Title Bar Color 24-bit */


/* INT16U x,INT8U y ��ʼλ�� */
void CreateWindow(
	INT8U  *winname,		   /* ��������/���� */
	INT16U x,				   /* ����ˮƽ��ʼλ�� */
	INT16U y,				   /* ���ڴ�ֱ��ʼλ�� */
	INT16U width,			   /* ���ڿ�� */
	INT16U high,			   /* ���ڸ߶� */
	INT16U windowcolor		   /* ������ɫ */
);


/* ����ͼ�� */
void GUIToolICOPower(
	INT16U x,				   /* ����ˮƽ��ʼλ�� */
	INT16U y,				   /* ���ڴ�ֱ��ʼλ�� */
	INT8U power
);
/* ������ */
void GUIProgressBar(
	INT16U x,				   /* ������ƽ��ʼλ�� */
	INT16U y,				   /* ��������ֱ��ʼλ�� */
	INT16U width,			   /* ���������� */
	INT16U high,			   /* �������߶� */
	INT16U Progress			   /* ���� 0 - 100 */
);
/* ���� */
void GUIVolumeico(
	INT16U x,				   /* ˮƽ��ʼλ�� */
	INT16U y,				   /* ��ֱ��ʼλ�� */
	INT8U vol				   /* ����ֵ 0 - 48 */
);
	/* ��һ�� */ 
void GUIUpSong(
	INT16U x,				   /* ˮƽ��ʼλ�� */
	INT16U y,				   /* ��ֱ��ʼλ�� */
	INT16U color
);
/* ��һ�� */ 
void GUIDownSong(
	INT16U x,				   /* ˮƽ��ʼλ�� */
	INT16U y,				   /* ��ֱ��ʼλ�� */
	INT16U color
);
/* ���Ű�ť */
void GUIPlay(
	INT16U x,				   /* ˮƽ��ʼλ�� */
	INT16U y,				   /* ��ֱ��ʼλ�� */
	INT16U color
);
/* ��ͣ��ť */
void GUIPause(
	INT16U x,				   /* ˮƽ��ʼλ�� */
	INT16U y,				   /* ��ֱ��ʼλ�� */
	INT16U color
);
/* Ƶ�׷������� */
void GUISpectrum(
	INT16U x,				   /* ˮƽ��ʼλ�� */
	INT16U y,				   /* ��ֱ��ʼλ�� */
	INT8U  width,			   /* ���ο�� */
	INT16U color,			   /* ������ɫ */
	INT8U *specdata			   /* Ƶ������ */
);
/* ��һ�� */ 
void GUIUp(
	INT16U x,				   /* ˮƽ��ʼλ�� */
	INT16U y,				   /* ��ֱ��ʼλ�� */
	INT16U color			   /* ��ɫ */
);
/* ��һ�� */ 
void GUIDown(
	INT16U x,				   /* ˮƽ��ʼλ�� */
	INT16U y,				   /* ��ֱ��ʼλ�� */
	INT16U color			   /* ��ɫ */
);
/* ���ΰ�ť */
void GUIButton(
	INT8U  *btntitle,		   /* ��ť���� */
	INT16U x,				   /* ˮƽ��ʼλ�� */
	INT16U y,				   /* ��ֱ��ʼλ�� */
	INT16U width,			   /* ���� */
	INT16U high,			   /* �߶� */
	INT16U color			   /* ��ɫ */		
);

/* ������2 */
void GUIProgressBar2(
	INT16U x,				   /* ������ƽ��ʼλ�� */
	INT16U y,				   /* ��������ֱ��ʼλ�� */
	INT16U width,			   /* ���������� */
	INT16U high,			   /* �������߶� */
	INT16U Progress			   /* ���� 0 - 100 */
);
/* ��СԲ�� */
void MinRound(
	INT16U x,				   /* ˮƽ��ʼλ�� */
	INT16U y,				   /* ��ֱ��ʼλ�� */
	INT16U color			   /* ��ɫ */
);