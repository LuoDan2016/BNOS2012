/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: lcd5420.c
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/03/20
* 功能描述: LCD OTM4001驱动程序.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"
#include "diskio.h"
#include "pff.h"

/* 变量声明 ---------------------------------------------------------------------*/

extern const unsigned char code __ASCII816[]; /* 调用外部ASCII数据 */
/*********************************************************************************
** 函数名称: void LCD_Delay(INT8U count).
** 功能描述: LCD延时函数.
** 输入参数: INT8U count.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void LCD_Delay(INT8U count)   
{
	int  i,j;
    for(i=0;i<count;i++);
		for(j=0;j<100;j++);
}

/*********************************************************************************
** 函数名称: void LCD_Write_CMD(INT16U iadd).
** 功能描述: LCD写指令.
** 输入参数: INT16U iadd 寄存器地址.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void LCD_Write_CMD(INT16U iadd)
{
	LCD_CS_Low();	
	LCD_RS_Low();
	LCD_DATA_PORT=(iadd>>8);
	LCD_WR_Low();
	LCD_WR_High();
	LCD_DATA_PORT=(iadd&0xff);
	LCD_WR_Low();
	LCD_WR_High();	
	LCD_CS_High();
}

/*********************************************************************************
** 函数名称: void LCD_Write_Data(INT16U idat).
** 功能描述: LCD写数据.
** 输入参数: INT16U idat 16为数据.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void LCD_Write_Data(INT16U idat)
{
	LCD_CS_Low();	
	LCD_RS_High();
	LCD_DATA_PORT=(idat>>8);
	LCD_WR_Low();
	LCD_WR_High();
	LCD_DATA_PORT=(idat&0xff);
	LCD_WR_Low();
	LCD_WR_High();	
	LCD_CS_High();	
}

#if 0
/*********************************************************************************
** 函数名称: INT16U LCD_Read_CMD(void).
** 功能描述: LCD读命令.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
INT16U LCD_Read_CMD(void)
{
	INT16U d1,d2;

	LCD_CS_Low();
	LCD_WR_High();	
	LCD_RS_Low();	
	LCD_RD_Low();
	d1 = LCD_DATA_PORT;	
	LCD_RD_High();
	LCD_RD_Low();
	d2 = LCD_DATA_PORT;	
	LCD_RD_High();
	LCD_CS_High();
	
	return ((d1<<8) | (d2&0xff));

}
#endif /* LCD_Read_CMD */

#if 1
/*********************************************************************************
** 函数名称: INT16U LCD_Read_Data(void).
** 功能描述: LCD读数据.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: ((d1&0xff) | (d2<<8) ) 24位颜色.
**********************************************************************************/
INT16U LCD_Read_Data(void)
{
	INT16U d1,d2;
	LCD_DATA_PORT = 0XFF;  /* 上拉输入 */
	LCD_CS_Low();
	LCD_WR_High();
	LCD_RS_High();
	LCD_RD_Low();
	d1 = LCD_DATA_PORT;	
	LCD_RD_High();
	LCD_RD_Low();
	d2 = LCD_DATA_PORT;	
	LCD_RD_High();
	LCD_CS_High();
	return ((d1&0xff) | (d2<<8) );
} 
#endif /* LCD_Read_Data */

/*********************************************************************************
** 函数名称: void LCD_Write_Reg(INT16U iadd, INT16U iidata).
** 功能描述: 对lcd寄存器，写命令和数据.
** 输入参数: INT16U iadd, INT16U iidata.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void LCD_Write_Reg(INT16U iadd, INT16U iidata)
{
	LCD_Write_CMD(iadd);
	LCD_Write_Data(iidata);
}

/*********************************************************************************
** 函数名称: void LCD_SET_XY(INT16U x,INT8U y).
** 功能描述: 设置光标函数.
** 输入参数: INT16U x,INT8U y.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void LCD_SET_XY(INT16U x,INT8U y)
{
    LCD_Write_Reg(0x200,y);
    LCD_Write_Reg(0x201,x);
    LCD_Write_CMD(0x0202);    
}

/*********************************************************************************
** 函数名称: void LCD_Init(void).
** 功能描述: LCD初始化程序.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void LCD_Init(void)
{
	LCD_Backlight = 0;	/* 背光控制 0:关 1：开 */
   	LCD_Backlight = 1;	/* 背光控制 0:关 1：开 */
	LCD_Delay(20);
	LCD_RST_Low();
    LCD_Delay(5); 
    LCD_RST_High();         
    LCD_Delay(5);
    
    LCD_CS_Low();
    LCD_Write_Reg(0x0606,0x0000);
	LCD_Delay(100);
	LCD_Write_Reg(0x0007,0x0001);
	LCD_Delay(100);
	LCD_Write_Reg(0x0110,0x0001);
	LCD_Delay(100);
	LCD_Write_Reg(0x0100,0x17B0);
	LCD_Write_Reg(0x0101,0x0147);
	LCD_Write_Reg(0x0102,0x019D);
	LCD_Write_Reg(0x0103,0x3600);
	LCD_Write_Reg(0x0281,0X0010);
	LCD_Delay(100);
	LCD_Write_Reg(0x0102,0x01BD);
	LCD_Delay(100);
    
	LCD_Write_Reg(0x0000,0x0000);
	LCD_Write_Reg(0x0001,0x0000);
	LCD_Write_Reg(0x0002,0x0100);
	LCD_Write_Reg(0x0003,0x1038);  //0x1030 0x1038
	LCD_Write_Reg(0x0006,0x0000);
	LCD_Write_Reg(0x0008,0x0503);
	LCD_Write_Reg(0x0009,0x0001);
	LCD_Write_Reg(0x000B,0x0010);
	LCD_Write_Reg(0x000C,0x0000);
	LCD_Write_Reg(0x000F,0x0000);
	LCD_Write_Reg(0x0007,0x0001);
	LCD_Write_Reg(0x0010,0x0013);
	LCD_Write_Reg(0x0011,0x0202);
	LCD_Write_Reg(0x0012,0x0300);
	LCD_Write_Reg(0x0020,0x021E);
	LCD_Write_Reg(0x0021,0x0202);
	LCD_Write_Reg(0x0022,0x0100);
	LCD_Write_Reg(0x0090,0x8000);
	LCD_Write_Reg(0x0092,0x0000);
	LCD_Write_Reg(0x0100,0x16B0);
	LCD_Write_Reg(0x0101,0x0147);
	LCD_Write_Reg(0x0102,0x01BD);
	LCD_Write_Reg(0x0103,0x2A00);
	LCD_Write_Reg(0x0107,0x0000);
	LCD_Write_Reg(0x0110,0x0001);
	LCD_Write_Reg(0x0210,0);
	LCD_Write_Reg(0x0211,239);
	LCD_Write_Reg(0x0212,0);
	LCD_Write_Reg(0x0213,399);
	LCD_Write_Reg(0x0280,0x0000);
	LCD_Write_Reg(0x0281,0x000E);
	LCD_Write_Reg(0x0282,0x0000);
	LCD_Write_Reg(0x0300,0x0101);
	LCD_Write_Reg(0x0301,0x0B2C);
	LCD_Write_Reg(0x0302,0x1030);
	LCD_Write_Reg(0x0303,0x3010);
	LCD_Write_Reg(0x0304,0x2C0B);
	LCD_Write_Reg(0x0305,0x0101);
	LCD_Write_Reg(0x0306,0x0807);
	LCD_Write_Reg(0x0307,0x0708);
	LCD_Write_Reg(0x0308,0x0107);
	LCD_Write_Reg(0x0309,0x0105);
	LCD_Write_Reg(0x030A,0x0F04);
	LCD_Write_Reg(0x030B,0x0F00);
	LCD_Write_Reg(0x030C,0x000F);
	LCD_Write_Reg(0x030D,0x040F);
	LCD_Write_Reg(0x030E,0x0501);
	LCD_Write_Reg(0x030F,0x0701);
	LCD_Write_Reg(0x0400,0x3500);
	LCD_Write_Reg(0x0401,0x0001);
	LCD_Write_Reg(0x0404,0x0000);
	LCD_Write_Reg(0x0500,0x0000);
	LCD_Write_Reg(0x0501,0x0000);
	LCD_Write_Reg(0x0502,0x0000);
	LCD_Write_Reg(0x0503,0x0000);
	LCD_Write_Reg(0x0504,0x0000);
	LCD_Write_Reg(0x0505,0x0000);
	LCD_Write_Reg(0x0600,0x0000);
	LCD_Write_Reg(0x0606,0x0000);
	LCD_Write_Reg(0x06F0,0x0000);
	LCD_Write_Reg(0x07F0,0x5420);
	LCD_Write_Reg(0x07F3,0x288A);
	LCD_Write_Reg(0x07F4,0x0022);
	LCD_Write_Reg(0x07F5,0x0041);
	LCD_Write_Reg(0x07F0,0x0000);
	LCD_Write_Reg(0x0007,0x0173);
    LCD_Clear(Black);
}

/*********************************************************************************
** 函数名称: void LCD_Clear (INT16U color).
** 功能描述: LCD指定颜色清屏.
** 输入参数: INT16U color 清屏颜色.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void LCD_Clear (INT16U color)
{
    INT8U x;
    INT16U y;
    LCD_SET_XY(0,0);
    for(x=0;x<240;x++)
    {
        for(y=0;y<400;y++)
        {
            LCD_Write_Data(color);
        }
    }
}

#if 1
/*********************************************************************************
** 函数名称: void LCD_DrawPoint(INT16U x,INT8U y,INT16U color).
** 功能描述: LCD指定位置画点.
** 输入参数: INT16U x,INT8U y,INT16U color 位置、颜色.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void LCD_DrawPoint(INT16U x,INT8U y,INT16U color)
{
    LCD_SET_XY(x,y);
 	LCD_Write_Data(color);
}
#endif /* LCD_DrawPoint */

#if 1
/*********************************************************************************
** 函数名称: INT16U LCD_GetPoint(INT16U x,INT16U y).
** 功能描述: LCD获取指定座标的颜色值.
** 输入参数: INT16U x,INT16U y 位置.         
** 输出参数: None.
** 返回参数: data1 颜色.
**********************************************************************************/
INT16U LCD_GetPoint(INT16U x,INT16U y)
{
	INT16U data1; 
	
	LCD_Write_Reg(0x200,y); /* Lcd光标GRAM水平起始位置 */ 
	LCD_Write_Reg(0x201,x); /* Lcd光标垂直GRAM起始位置 */     
	LCD_Write_Reg(0x210,y); /* 水平 GRAM起始位置 */ 
	LCD_Write_Reg(0x211,y); /* 水平GRAM终止位置 */ 
	LCD_Write_Reg(0x212,x); /* 垂直GRAM起始位置 */ 
	LCD_Write_Reg(0x213,x); /* 垂直GRAM终止位置 */  
	LCD_Write_CMD(0x0202); 
	
	data1=LCD_Read_Data();  /* 虚读 */
	data1=LCD_Read_Data(); 
	
	LCD_Write_Reg(0x0210,0);
	LCD_Write_Reg(0x0211,239);
	LCD_Write_Reg(0x0212,0);
	LCD_Write_Reg(0x0213,399);
	
	return data1;
}
#endif /* LCD_GetPoint */


#if 0
/*******************************************************************************
** 函数名称: LCD_Line.
** 功能描述: LCD屏幕画线.
** 输入参数: int x1,int y1,int x2,int y2,int color.         
** 输出参数: None
** 返回参数: None
*******************************************************************************/
void LCD_DrawLine(int x1,int y1,int x2,int y2,int color)
{
	int dx,dy,e;
	dx=x2-x1; 
	dy=y2-y1;
    
	if(dx>=0)
	{
		if(dy >= 0) 
		{
			if(dx>=dy)                                          /* 1/8 octant */
			{
				e=dy-dx/2;
				while(x1<=x2)
				{
					LCD_DrawPoint(x1,y1,color);
					if(e>0){y1+=1;e-=dx;}	
					x1+=1;
					e+=dy;
				}
			}
			else		                                         /* 2/8 octant */
			{
				e=dx-dy/2;
				while(y1<=y2)
				{
					LCD_DrawPoint(x1,y1,color);
					if(e>0){x1+=1;e-=dy;}	
					y1+=1;
					e+=dx;
				}
			}
		}
		else		   
		{
			dy=-dy;                                                /* dy=abs(dy) */

			if(dx>=dy)                                             /* 8/8 octant */
			{
				e=dy-dx/2;
				while(x1<=x2)
				{
					LCD_DrawPoint(x1,y1,color);
					if(e>0){y1-=1;e-=dx;}	
					x1+=1;
					e+=dy;
				}
			}
			else		                                            /* 7/8 octant */
			{
				e=dx-dy/2;
				while(y1>=y2)
				{
					LCD_DrawPoint(x1,y1,color);
					if(e>0){x1+=1;e-=dy;}	
					y1-=1;
					e+=dx;
				}
			}
		}	
	}
	else /* dx<0 */
	{
		dx=-dx;		/* dx=abs(dx) */
		if(dy >= 0) 
		{
			if(dx>=dy) /* 4/8 octant */
			{
				e=dy-dx/2;
				while(x1>=x2)
				{
					LCD_DrawPoint(x1,y1,color);
					if(e>0){y1+=1;e-=dx;}	
					x1-=1;
					e+=dy;
				}
			}
			else		/* 3/8 octant */
			{
				e=dx-dy/2;
				while(y1<=y2)
				{
					LCD_DrawPoint(x1,y1,color);
					if(e>0){x1-=1;e-=dy;}	
					y1+=1;
					e+=dx;
				}
			}
		}
		else		       /* dy<0 */
		{
			dy=-dy;        /* dy=abs(dy) */

			if(dx>=dy)     /* 5/8 octant */
			{
				e=dy-dx/2;
				while(x1>=x2)
				{
					LCD_DrawPoint(x1,y1,color);
					if(e>0){y1-=1;e-=dx;}	
					x1-=1;
					e+=dy;
				}
			}
			else		 /* 6/8 octant */
			{
				e=dx-dy/2;
				while(y1>=y2)
				{
					LCD_DrawPoint(x1,y1,color);
					if(e>0){x1-=1;e-=dy;}	
					y1-=1;
					e+=dx;
				}
			}
		}	
	}
}
#endif /* LCD_DrawLine */

#if 1
/*******************************************************************************
* 函数名称: Glib_FilledRectangle.
* 功能描述: 在LCD屏幕上用颜色填充一个矩形.
* 输入参数: INT16U x,INT8U y,INT16U width,INT8U high,INT16U color         
* 输出参数: None
* 返回参数: None
*******************************************************************************/
void LCD_FilledRectangle(INT16U x,INT8U y,INT16U width,INT8U high,INT16U color)
{
	INT16U i=0,j=0;
	LCD_SET_XY(x,y);	/* 设置LCD显示起点 */
	for(i=0;i<high;i++)			 
	{	
		for(j=0;j<width;j++)	  
		{
			LCD_Write_Data(color);   
		}
		LCD_SET_XY(x,++y);
	}
}
#endif /* LCD_FilledRectangle */


/*******************************************************************************
** 函数名称: LCD_Write_ASCII().
** 功能描述: 写单个字符ASCII码 ASCII字库字库.
** 输入参数: INT8U String,INT16U x,INT88U y,INT16U color,INT16U backcolor,INT8U bcst.         
** 输出参数: None
** 返回参数: None
*******************************************************************************/
void LCD_Write_ASCII(INT8U String,INT16U x,INT8U y,INT16U color,INT16U backcolor,INT8U bcst)
{
	 
	   unsigned short int i,j;
       unsigned char mask,buf;             /* 定义缓存变量 指针 */
	   for( i = 0 ; i < 16 ; i++ )		        /* 循环十六行 */
	   {
	   		mask = 0x80;			            /* 八位数据与上所在的位 1 即可知道是否为1 如果不是八位则需更改 */
	  		buf = __ASCII816[String*16 + i];    /* 0-255的ASCII表 如N N的ASCII之为78=》78*16=1536即N的初始地址 赋给指针 */
			for( j = 0 ; j < 8 ; j++ )	        /* 循环八列 */
			{
				if( buf & mask )		         /* 以上与运算为真则打印 */
				{
					LCD_DrawPoint(x+j,y+i,color);
				}
				else
                {
					if(bcst)
	               	LCD_DrawPoint(x+j,y+i,backcolor);
                }						 
				mask >>= 1;			              /* 右移位后进行下一列 */
			}
	   }		

}

/*******************************************************************************
** 函数名称: LCD_Write_HZ().
** 功能描述: 写单个字符汉字 SPI FLASH字库.
** 输入参数: INT8U String,INT16U x,INT88U y,INT16U color,INT16U backcolor,INT8U bcst.         
** 输出参数: None
** 返回参数: None
*******************************************************************************/
INT8U data charbuff[32];
void LCD_Write_HZ(INT16U x,INT8U y,INT16U quwei,INT16U color,INT16U backcolor,INT8U bcst)
{
	unsigned int i,j;
	unsigned char mask,buf;
	unsigned long quma,weima;
	quma  =  quwei / 100;
	weima =  quwei % 100;
	M25P16_Fast_Read_Data((INT32U)((quma - 1) * 94 + (weima - 1)) * 32,32,charbuff);
	LCD_SET_XY(x,y);
	/* 左侧文字 */
	for( i = 0 ; i < 16 ; i++ )		        /* 循环十六行 */
	{
		LCD_CS_Low();
		LCD_RS_High();
		mask = 0x80;			            /* 八位数据与上所在的位 1 即可知道是否为1 如果不是八位则需更改 */
		buf = charbuff[i * 2];					/* 取左侧字码 */					
		for( j = 0 ; j < 8 ; j++ )	        /* 循环八列 */
		{
			if( buf & mask )		         /* 以上与运算为真则打印 */
			{
				LCD_Write_Data(color);
			}
			else
	        {
				if(bcst)
	           		LCD_Write_Data(backcolor);
	        }						 
			mask >>= 1;			              /* 右移位后进行下一列 */
		}
		LCD_SET_XY(x,++y);
	}
	/* 右侧文字 */
	LCD_SET_XY(x+=8,y-=16);
	for( i = 0 ; i < 16 ; i++ )		        /* 循环十六行 */
	{
		LCD_CS_Low();
		LCD_RS_High();
		mask = 0x80;			            /* 八位数据与上所在的位 1 即可知道是否为1 如果不是八位则需更改 */
		buf = charbuff[i * 2 + 1]; 						/* 取右侧字码 */
		for( j = 0 ; j < 8 ; j++ )	        /* 循环八列 */
		{
			if( buf & mask )		         /* 以上与运算为真则打印 */
			{
				LCD_Write_Data(color);
			}
			else
	        {
				if(bcst)
	           		LCD_Write_Data(backcolor);
	        }						 
			mask >>= 1;			              /* 右移位后进行下一列 */
		}
		LCD_SET_XY(x,++y);
	}			
}

/*******************************************************************************
** 函数名称: LCD_Write_String().
** 功能描述: 写ASCII码字符串.
** 输入参数: INT16U x,INT8U y,INT8U *String,INT16U color,INT16U backcolor,INT8U bcst.         
** 输出参数: None
** 返回参数: None
*******************************************************************************/
void LCD_Write_String(INT16U x,INT8U y,INT8U *String,INT16U color,INT16U backcolor,INT8U bcst)
{
	INT8U i = 0;
    while ((* String  != 0) && (i < 50))
    {
		if( *String > 0xA0 & *(String+1) > 0xA0 )  /* 同时大于 0xA0的是GB2312编码*/
		{	  /*  *pStr-0xA0=区码 ,*(pStr+1)-0xA0=位码,区码X100+位码=区位码  中文输出 */
			LCD_Write_HZ(x,y,(*String - 0xA0)*0x0064 + *(String+1) - 0xA0,color,backcolor,bcst);
			String += 2;	     /* 取下一个指针地址 */
			/* Decrement the column position by 16 */
			x += 16;	 /* 16点宽度 */
			i += 2;		 /* 显示计数 */
		}						  
		else
		{
	        LCD_Write_ASCII(( *String++),x,y,color,backcolor,bcst);
	         /* Decrement the column position by 8 */
			x += 8;
			i += 1;		/* 显示计数 */
		}
    }
}


#if 0
/*******************************************************************************
* 函数名称: Lcd_PutNum.
* 功能描述: LCD数值显示32位 0-4294967295 无需指定长度NETC-陈建长.	
* 输入参数: unsigned int x,unsigned int y,unsigned int c,unsigned int bk_c,
             unsigned long num(整型数据),unsigned int st  区域颜色选择
			  st = 1 有 st = 0 无,在动态变化的情况下,如果没有区域颜色则前后信息叠加.     
* 输出参数: None
* 返回参数: None
*******************************************************************************/
void Lcd_WriteNum(unsigned int x,unsigned int y,unsigned int c,unsigned int bk_c,unsigned long  num,unsigned char st)
{
    unsigned int length = 0 , i = 0 ;		 /* 数据长度 */
	unsigned long temp,databuf;
	unsigned char asciibit = 8;				 /* ASCII位数 */
	databuf	= num;							 /* 缓存数据 因计算长度会使数据为0 */
	if(num == 0)							 /* 如果数据为0 则显示0 */
		LCD_Write_ASCII(x,y,48,White,Black,1);	 /* 48为0的ASCII值 */
	while(num!=0)							 /* 计算数据长度 */
	{
		num = num / 10;
		length++;
	}										 
	for(i=0;i<length;i++)					 /* 打印数据 */
	{											
		temp = databuf % 10;			     /* 从最高位开始提取数据 */
		databuf = databuf / 10;				 /* 将剩余位数缓存 */
		/* 从最高位开始打印 如4+48=52正是 4的ASCII码值 从ASCII表查找 */				
		LCD_Write_ASCII(x+(length*asciibit-asciibit),y,temp+48,c,bk_c,st);
		x -= asciibit;
	}
}
#endif	/* Lcd_WriteNum */

#if 1
 /*******************************************************************************
* 函数名称: Lcd_PutNum.		 指定长度
* 功能描述: LCD数值显示32位 0-4294967295 无需指定长度NETC-陈建长.	
* 输入参数: unsigned int x,unsigned int y,unsigned int c,unsigned int bk_c,
             unsigned long num(整型数据),unsigned int st  区域颜色选择
			  st = 1 有 st = 0 无,在动态变化的情况下,如果没有区域颜色则前后信息叠加.     
* 输出参数: None
* 返回参数: None
*******************************************************************************/
void Lcd_WriteNumlen(INT8U length,INT32U  num,INT16U x,INT16U y,INT16U c,INT16U bk_c,INT8U st)
{
    unsigned int i = 0 ; /* 数据长度 */
	unsigned long temp;
	unsigned char asciibit = 8;				 /* ASCII位数 */									 
	for(i=0;i<length;i++)					 /* 打印数据 */
	{											
		temp = num % 10;			     /* 从最高位开始提取数据 */
		num = num / 10;				 /* 将剩余位数缓存 */
		/* 从最高位开始打印 如4+48=52正是 4的ASCII码值 从ASCII表查找 */				
		LCD_Write_ASCII(temp+48,x+(length*asciibit-asciibit),y,c,bk_c,st);
		x -= asciibit;
	}
}
#endif /* Lcd_WriteNumlen */
