/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: LCD5420.H
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/03/20
* 功能描述: 文件包含.
**********************************************************************************/


#ifndef __LCD5420_H__
#define __LCD5420_H__

/* 变量定义 ----------------------------------------------------------------------- */


/* LCD硬件管脚配置 */
sbit LCD_CS	 = P1^3;
sbit LCD_RS  = P1^2;
sbit LCD_WR  = P1^1;
sbit LCD_RD  = P1^0;
sbit LCD_RST = P4^6;
sbit LCD_Backlight = P4^1;
#define LCD_CS_Low()   LCD_CS=0
#define LCD_CS_High()  LCD_CS=1
#define LCD_RS_Low()   LCD_RS=0
#define LCD_RS_High()  LCD_RS=1
#define LCD_WR_Low()   LCD_WR=0
#define LCD_WR_High()  LCD_WR=1
#define LCD_RD_Low()   LCD_RD=0
#define LCD_RD_High()  LCD_RD=1
#define LCD_RST_Low()  LCD_RST=0
#define LCD_RST_High() LCD_RST=1
#define LCD_DATA_PORT P0

/* LCD color */
#define White          0xFFFF
#define Black          0x0000
#define Grey           0xF7DE
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF    /* 淡蓝 */
#define Yellow         0xFFE0
#define Gray           0x738E	 /* 灰色 */
#define Back_Color 	   0x0000
#define String_Color   0x07ff
#define NotselColor	   0xFFFF
#define SelectedColor  0x07E0
/*TFT_SIZE */
#define LCD_XSIZE_TFT 	(400)	
#define LCD_YSIZE_TFT 	(240)

#define USE_LCD_DRAWPOINT 1	 /* 暂不使用函数 */
#define USE_TransmitHex   0
#define USE_LCD_Write_HZ  0

/* 函数声明 */
void LCD_Delay(unsigned char count);
void LCD_Write_CMD(INT16U iadd);
void LCD_Write_Data(INT16U idat);
INT16U LCD_Read_CMD(void);
INT16U LCD_Read_Data(void);
void LCD_Write_Reg(INT16U iadd, INT16U iidata);
void LCD_SET_XY (unsigned int x,unsigned char y);
void LCD_Init(void);
void LCD_Clear (unsigned int color);
INT16U LCD_GetPoint(INT16U x,INT16U y);
void LCD_DrawPoint(INT16U x,INT8U y,INT16U color);
void LCD_DrawLine(int x1,int y1,int x2,int y2,int color);
void LCD_FilledRectangle(INT16U x,INT8U y,INT16U width,INT8U high,INT16U color);
void LCD_HollowRectangle(INT16U x,INT8U y,INT16U width,INT8U high,INT16U color);
void LCD_Write_ASCII(INT8U String,INT16U x,INT8U y,INT16U color,INT16U backcolor,INT8U bcst);
void LCD_Write_String(INT16U x,INT8U y,INT8U *String,INT16U color,INT16U backcolor,INT8U bcst);
void Lcd_WriteNum(unsigned int x,unsigned int y,unsigned int c,unsigned int bk_c,unsigned long  num,unsigned char st);
void Lcd_WriteNumlen(INT8U length,INT32U  num,INT16U x,INT16U y,INT16U c,INT16U bk_c,INT8U st);
void LCD_Write_HZ(INT16U x,INT8U y,INT16U quwei,INT16U color,INT16U backcolor,INT8U bcst);

#endif /*NED  __LCD5420_H__ */