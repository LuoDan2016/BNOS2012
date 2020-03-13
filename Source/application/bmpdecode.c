/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: BNOS 2012
* 文件名称: bmpdecode.c
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/03/20
* 功能描述: BNOS 图像解码处理.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"
#include "diskio.h"
#include "pff.h"

#define BUFFSIZE 252 /* 每次读出BMP数据大小 一定为3的倍数 */
#define DISWIDTH 245 /* 设置显示宽度 */
#define DISHIGH  125 /* 设置显示高度 */
/* RGB24 TO RGB16 */
#define TRANSFORM(color,r,g,b) color = ((r>>3)<<11)|((g>>2)<<5)|(b>>3)

/* 文件系统变量声明 */
extern volatile FRESULT res;	
extern volatile INT16U br;
extern volatile BYTE buff[256]; /*SD Buffer Size 256 Byte*/


#if 1
/*********************************************************************************
** 函数名称: void Bmpdisplay(INT16U x,INT8U y,INT8U *bmppath).
** 功能描述: BMP图像解码.
** 输入参数: INT16U x 水平位置坐标(显示),INT8U y 垂直位置坐标(显示),
**			 INT8U *bmppath BMP文件路径.         
** 输出参数: None
** 返回参数: None
**********************************************************************************/	

INT8U BmpDecode(INT16U x,INT8U y,INT8U *BMPPath)
{
	INT16U width,high,i=0,j=0;
	INT16U biBitCount,getcodecount,color;            /* 读文件计数 像素比特数  颜色 */  
	INT32U offset=0;	                             /* 图像数据的偏移量 */
	INT8U *prgbdata;
	res = pf_open(BMPPath); 						 /* 打开文件 */
	if(res != 0)
	{return 1;}										 /* 打开失败返回 1 成功返回 0 */
	else
	{
		pf_read(buff,56,&br);                            /* 读取54字节文件头+2字节调色板数 */       
		biBitCount = (INT32U)(buff[0x1C]);               /* 获得像素比特数 */    
		offset = (INT32U)(buff[0x0A]);                   /* 得到图像数据的偏移量 10 - 13*/
		width = (INT32U)(buff[0x12]);                    /* 得到图像宽度 18 - 21字节*/  
		high = (INT32U)(buff[0x16]);                     /* 得到图像高度 22 - 25*/ 
		pf_lseek(offset+1);			                     /* 头文件偏移量 */
		getcodecount=BUFFSIZE;
		LCD_SET_XY(x,high+y);	                         /* 设置LCD显示起点 */
														 /* 24 BIT BMP 解码最大显示限制 */
		if(width <= DISWIDTH && high <= DISHIGH && buff[0] == 'B' && buff[1] == 'M')
		for(i=0;i<high;i++)			 
		{	
			for(j=0;j<width;j++)	  
			{
		 	    /* 显示图像,需要将RGB24转换为RGB565	*/
			    /* 从BMP文件中读出的图像数据连续的三个字节B G R */
				/* 红色r占5为屏蔽低三位  绿色g占6为屏蔽低两位   蓝色b占5为屏蔽低三位 */ 
				/* 先读出的三个字节对应的是图像中的左下角的那个像素,最后三个字节对应图像 右上角 */
				if(getcodecount==BUFFSIZE)
			   	{
					res = pf_read(buff,BUFFSIZE,&br);
					if(res || br == 0)break;/* 结束和错误 */
					prgbdata = buff;
					getcodecount=0;
				}
				getcodecount+=3;
				/* 颜色转换 */
				color = ((*prgbdata++) &(~(0x03)))<<3;
				color +=(((*prgbdata++)&(~(0x7)))<<8);
				color +=(((*prgbdata++)&(~(0x7)))>>3);
				/* LCD显示 */
				LCD_Write_Data(color);   
			}
			LCD_SET_XY(x,high+y-i);
		}
		return 0;
	}
}
#endif

/*********************************************************************************
** 函数名称: FlashGraphDis().
** 功能描述: 读取FLASH BMP 数据显示,存储时需要确定地址并将BMP-24BIT不含头文件直接存放.
** 输入参数: INT16U x 水平位置坐标(显示),INT8U y 垂直位置坐标(显示) 
**			 INT16U width,INT16U high 图像 高,宽 , INT32U GraphAddr 数据基址.         
** 输出参数: None
** 返回参数: None
**********************************************************************************/
void FlashGraphDis(INT16U x,INT16U y,INT16U width,INT16U high,INT32U GraphAddr)
{
	INT32U readcount=0,getcodecount=0;
	INT16U i,j,color;
	INT8U *prgbdata;
	getcodecount = BUFFSIZE; 
	LCD_SET_XY(x,y);
	for(i=0;i<high;i++)			 
	{	
		for(j=0;j<width;j++)	  
		{
	 	    /* 显示图像,需要将RGB24转换为RGB565	*/
		    /* 从BMP文件中读出的图像数据连续的三个字节B G R */
			/* 红色r占5为屏蔽低三位  绿色g占6为屏蔽低两位   蓝色b占5为屏蔽低三位 */ 
			/* 先读出的三个字节对应的是图像中的左下角的那个像素,最后三个字节对应图像 右上角 */
			if(getcodecount==BUFFSIZE)
		   	{
				/* 
				**读出Flash 中BMP图像数据 存储基址+BMP偏移量 + 读取计数
				*/
				M25P16_Fast_Read_Data(GraphAddr + ( readcount * 252),252,buff);
				prgbdata = buff;
				getcodecount=0;
				readcount++;
			}
			getcodecount+=3;
			/* 颜色转换 */
			color = ((*prgbdata++) &(~(0x03)))<<3;
			color +=(((*prgbdata++)&(~(0x7)))<<8);
			color +=(((*prgbdata++)&(~(0x7)))>>3);
			/* LCD显示 */
			LCD_Write_Data(color);    
		}
		LCD_SET_XY(x,++y);
	}
}
