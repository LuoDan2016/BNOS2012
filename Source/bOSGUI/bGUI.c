/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: bGUI.c
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/01/20
* 功能描述: bGUI.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* 变量声明 ---------------------------------------------------------------------*/

/* BOOLESION.NET bGUI  */
/* 创建窗口 */
/*
**提供函数 LCD_FilledRectangle :在LCD屏幕上用颜色填充一个矩形.INT16U x,INT8U y,INT16U width,INT8U high,INT16U color
**         LCD_Write_String    :写字符串
** 		   LCD_DrawPoint	   ：LCD 画点
*/
/* INT16U x,INT8U y 起始位置 */
void CreateWindow(
	INT8U  *winname,		   /* 窗口名称/标题 */
	INT16U x,				   /* 窗口水平起始位置 */
	INT16U y,				   /* 窗口垂直起始位置 */
	INT16U width,			   /* 窗口宽度 */
	INT16U high,			   /* 窗口高度 */
	INT16U windowcolor		   /* 窗口颜色 */
)
{
	LCD_FilledRectangle(x + 1,y + 1,width - 1,high - 1,windowcolor);    /* 主窗口方块 width : 362  high : 176 */
	LCD_FilledRectangle(x + 1,y,width - 2,1,CTITLEBAR);		 	/* 标题栏 */
	LCD_FilledRectangle(x,y + 1,width,WORDHIGH+1,CTITLEBAR);	
	LCD_Write_String(x + 16,y,winname,CTITLE,CTITLEBAR,0);		/* 标题 */
	LCD_FilledRectangle(x + width - 28,y + 12,10,2,CTITLE);			/* 最小化图标 width : 2  high : 10 */
	LCD_FilledRectangle(x + width - 16,y + 6,10,4,Red);			    /* 关闭图标 width : 2  high : 10 */
	LCD_FilledRectangle(x + width - 16,y + 12,10,2,White);			/* 关闭图标 width : 4  high : 10 */

	LCD_FilledRectangle(x,y + 1,2,high - 1,CTITLEBAR);					/* 左边框*/
	LCD_FilledRectangle(width + x -2,y + 1,2,high-1,CTITLEBAR);		/* 右边框*/
	LCD_FilledRectangle(x,high + y - 2,width,2,CTITLEBAR);		/* 底部边框 */
	LCD_FilledRectangle(x + 4,y + 3,10,8,CTITLE);				/* 标题图标 width : 10  high : 10 */
}

/* 常用图标 */

/* 电量电量显示 */
void GUIToolICOPower(
	INT16U x,				   /* 窗口水平起始位置 */
	INT16U y,				   /* 窗口垂直起始位置 */
	INT8U power				   /* 电量0 - 12 */
)
{	
	if(power > 12)
		power = 12;
	if(power < 0)
		power = 0;
	LCD_FilledRectangle(x,y,6,2,White);
	LCD_FilledRectangle(x - 3,y + 2,12,16,White);
	LCD_FilledRectangle(x - 2,y + 3,10,14,RGB(127,127,127));
	LCD_FilledRectangle(x - 1,y + 4 + 12 - power,8,power,White);
	
}

/* 进度条 */
void GUIProgressBar(
	INT16U x,				   /* 进度条平起始位置 */
	INT16U y,				   /* 进度条垂直起始位置 */
	INT16U width,			   /* 进度条长度 */
	INT16U high,			   /* 进度条高度 */
	INT16U Progress			   /* 进度 0 - 100 */
)
{	
	FP32 Tran;
	if(Progress < 2)
		LCD_FilledRectangle(x,y,width,high,Gray);	           /* 进度条 width : 250  high : 6*/
	Tran =   (FP32)(width) / 100;
	if(Progress > 100)
		Progress = 100;	
	LCD_FilledRectangle(x,y,Progress * Tran,high,Green);	   /* 进度条 启动状态 */
}
/* 进度条2 */
void GUIProgressBar2(
	INT16U x,				   /* 进度条平起始位置 */
	INT16U y,				   /* 进度条垂直起始位置 */
	INT16U width,			   /* 进度条长度 */
	INT16U high,			   /* 进度条高度 */
	INT16U Progress			   /* 进度 0 - 100 */
)
{	
	FP32 Tran;
	LCD_FilledRectangle(x,y,width,high,Gray);	           /* 进度条 width : 250  high : 6*/
	Tran =   (FP32)(width) / 100;
	if(Progress > 100)
		Progress = 100;	
	LCD_FilledRectangle(x,y,Progress * Tran,high,Green);	   /* 进度条 启动状态 */
}
/* 音量图标 vol 0 - 48 */
void GUIVolumeico(
	INT16U x,				   /* 水平起始位置 */
	INT16U y,				   /* 垂直起始位置 */
	INT8U vol				   /* 音量值 0 - 48 */
)
{
	INT8U i,j;
	if(vol > 48)
		vol = 48;
	for(i=0;i<30;i+=3)						
	{
		for(j=0;j<(i/2);j++)
		{
			LCD_DrawPoint(x + (i - 1),y - j,Gray);
			LCD_DrawPoint(x + i,y - j,Gray);
		}
	}
	for(i=0;i<(vol * 30/48);i+=3)			
	{
		for(j=0;j<(i/2);j++)
		{
			LCD_DrawPoint(95 + (i - 1),80 - j,Green);
			LCD_DrawPoint(95 + i,80 - j,Green);
		}
	}
	
}

/* 上一曲 */ 
void GUIUpSong(
	INT16U x,				   /* 水平起始位置 */
	INT16U y,				   /* 垂直起始位置 */
	INT16U color
)
{
	INT8U i,j;
	LCD_FilledRectangle(x,y,5,20,color);	    /* 上一曲 方块 width : 5  high : 20 */
	for(i=0;i<20;i++)							/* 画实心三角 */
	{
	for(j=i;j<20 - i;j++)
		{
			LCD_DrawPoint((x+15) - i,y + j,color);
		}
	}
}
/* 下一曲 */ 
void GUIDownSong(
	INT16U x,				   /* 水平起始位置 */
	INT16U y,				   /* 垂直起始位置 */
	INT16U color
)
{
	INT8U i,j;
	LCD_FilledRectangle(x,y,5,20,color);	 /* 下一曲 方块 width : 5  high : 20 */
	for(i=0;i<20;i++)							 /* 画实心三角 */
	{
		for(j=i;j<20 - i;j++)
		{
			LCD_DrawPoint((x-10) + i,y + j,color);
		}
	}
}
/* 播放按钮 */
void GUIPlay(
	INT16U x,				   /* 水平起始位置 */
	INT16U y,				   /* 垂直起始位置 */
	INT16U color
)
{
	INT8U i,j;
	for(i=0;i<20;i++)
	{
		for(j=i;j<20 - i;j++)
		{
			LCD_DrawPoint(x + i,y + j,color);  

		}
	}	
}

/* 暂停图标 */
void GUIPause(
	INT16U x,				   /* 水平起始位置 */
	INT16U y,				   /* 垂直起始位置 */
	INT16U color
)
{

	LCD_FilledRectangle(x,y,5,20,color);	                /* 暂停 width : 5  high : 20 */
	LCD_FilledRectangle(x + 10,y,5,20,color);
}
#if 0 
/* 频谱分析条形 */
void GUISpectrum(
	INT16U x,				   /* 水平起始位置 */
	INT16U y,				   /* 垂直起始位置 */
	INT8U  width,			   /* 条形宽度 */
	INT16U color,			   /* 条形颜色 */
	INT8U *specdata			   /* 频谱数据 */
)
{
	INT8U i;
	for(i=0;i<14;i++)
    {
		if(*specdata > 60)
			*specdata = 60;	
        LCD_FilledRectangle(x,y-(*specdata),width,(*specdata),color);	    /* 方块 width : *  high :  */
		*specdata++;
        x += (width + 1);
    }
}
#endif /* GUISpectrum */

/* 上一个 */ 
void GUIUp(
	INT16U x,				   /* 水平起始位置 */
	INT16U y,				   /* 垂直起始位置 */
	INT16U color			   /* 颜色 */
)
{
	INT8U i,j;
	for(i=0;i<20;i++)							/* 画实心三角 */
	{
	for(j=i;j<20 - i;j++)
		{
			LCD_DrawPoint(x - i,y + j,color);
		}
	}
}

/* 下一个 */ 
void GUIDown(
	INT16U x,				   /* 水平起始位置 */
	INT16U y,				   /* 垂直起始位置 */
	INT16U color			   /* 颜色 */
)
{
	INT8U i,j;
	for(i=0;i<20;i++)							 /* 画实心三角 */
	{
		for(j=i;j<20 - i;j++)
		{
			LCD_DrawPoint(x + i,y + j,color);
		}
	}
}

/* 矩形按钮 */
void GUIButton(
	INT8U  *btntitle,		   /* 按钮标题 */
	INT16U x,				   /* 水平起始位置 */
	INT16U y,				   /* 垂直起始位置 */
	INT16U width,			   /* 长度 */
	INT16U high,			   /* 高度 */
	INT16U color			   /* 颜色 */		
)
{
	LCD_FilledRectangle(x,y,width,high,color); 
	LCD_FilledRectangle(x,y,width,1,RGB(240,240,240));
	LCD_FilledRectangle(x,y,1,high,RGB(240,240,240)); 
	LCD_FilledRectangle(x,y + high,width,1,RGB(127,127,127));
	LCD_FilledRectangle(x + width,y,1,high + 1,RGB(127,127,127));
	LCD_Write_String(x+10,y + ((high - 16) / 2),btntitle,Black,color,0);		/* 标题 */
}
/* 最小圆点 */
void MinRound(
	INT16U x,				   /* 水平起始位置 */
	INT16U y,				   /* 垂直起始位置 */
	INT16U color			   /* 颜色 */
)
{
	/*  左上 */
	LCD_DrawPoint(x-1,y-1,RGB(color + 27,color +29,color +30));
	/*  右上 */
	LCD_DrawPoint(x+1,y-1,RGB(color +27,color +29,color +30));
	/* 上 */
	LCD_DrawPoint(x,y-1,RGB(color +7,color +7,color +7));
	/* 中 */
 	LCD_DrawPoint(x,y,color);
	/* 下 */
	LCD_DrawPoint(x,y+1,RGB(color +7,color +7,color +7));
    /* 左 */
	LCD_DrawPoint(x-1,y,RGB(color +7,color +7,color +7));
	/* 右 */
	LCD_DrawPoint(x+1,y,RGB(color +7,color +7,color +7));
	/* 左下 */
	LCD_DrawPoint(x-1,y+1,RGB(color +27,color +29,color +30));
	/* 右下 */
	LCD_DrawPoint(x+1,y+1,RGB(color +27,color +29,color +30));

}