/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: BGUI.H
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.1
* 编制日期: 2012/01/20
* 功能描述: 文件包含.
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


/* INT16U x,INT8U y 起始位置 */
void CreateWindow(
	INT8U  *winname,		   /* 窗口名称/标题 */
	INT16U x,				   /* 窗口水平起始位置 */
	INT16U y,				   /* 窗口垂直起始位置 */
	INT16U width,			   /* 窗口宽度 */
	INT16U high,			   /* 窗口高度 */
	INT16U windowcolor		   /* 窗口颜色 */
);


/* 电量图标 */
void GUIToolICOPower(
	INT16U x,				   /* 窗口水平起始位置 */
	INT16U y,				   /* 窗口垂直起始位置 */
	INT8U power
);
/* 进度条 */
void GUIProgressBar(
	INT16U x,				   /* 进度条平起始位置 */
	INT16U y,				   /* 进度条垂直起始位置 */
	INT16U width,			   /* 进度条长度 */
	INT16U high,			   /* 进度条高度 */
	INT16U Progress			   /* 进度 0 - 100 */
);
/* 音量 */
void GUIVolumeico(
	INT16U x,				   /* 水平起始位置 */
	INT16U y,				   /* 垂直起始位置 */
	INT8U vol				   /* 音量值 0 - 48 */
);
	/* 上一曲 */ 
void GUIUpSong(
	INT16U x,				   /* 水平起始位置 */
	INT16U y,				   /* 垂直起始位置 */
	INT16U color
);
/* 下一曲 */ 
void GUIDownSong(
	INT16U x,				   /* 水平起始位置 */
	INT16U y,				   /* 垂直起始位置 */
	INT16U color
);
/* 播放按钮 */
void GUIPlay(
	INT16U x,				   /* 水平起始位置 */
	INT16U y,				   /* 垂直起始位置 */
	INT16U color
);
/* 暂停按钮 */
void GUIPause(
	INT16U x,				   /* 水平起始位置 */
	INT16U y,				   /* 垂直起始位置 */
	INT16U color
);
/* 频谱分析条形 */
void GUISpectrum(
	INT16U x,				   /* 水平起始位置 */
	INT16U y,				   /* 垂直起始位置 */
	INT8U  width,			   /* 条形宽度 */
	INT16U color,			   /* 条形颜色 */
	INT8U *specdata			   /* 频谱数据 */
);
/* 上一个 */ 
void GUIUp(
	INT16U x,				   /* 水平起始位置 */
	INT16U y,				   /* 垂直起始位置 */
	INT16U color			   /* 颜色 */
);
/* 下一个 */ 
void GUIDown(
	INT16U x,				   /* 水平起始位置 */
	INT16U y,				   /* 垂直起始位置 */
	INT16U color			   /* 颜色 */
);
/* 矩形按钮 */
void GUIButton(
	INT8U  *btntitle,		   /* 按钮标题 */
	INT16U x,				   /* 水平起始位置 */
	INT16U y,				   /* 垂直起始位置 */
	INT16U width,			   /* 长度 */
	INT16U high,			   /* 高度 */
	INT16U color			   /* 颜色 */		
);

/* 进度条2 */
void GUIProgressBar2(
	INT16U x,				   /* 进度条平起始位置 */
	INT16U y,				   /* 进度条垂直起始位置 */
	INT16U width,			   /* 进度条长度 */
	INT16U high,			   /* 进度条高度 */
	INT16U Progress			   /* 进度 0 - 100 */
);
/* 最小圆点 */
void MinRound(
	INT16U x,				   /* 水平起始位置 */
	INT16U y,				   /* 垂直起始位置 */
	INT16U color			   /* 颜色 */
);