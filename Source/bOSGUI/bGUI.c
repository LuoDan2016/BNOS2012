/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: ������51������ E1101
* �ļ�����: bGUI.c
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/01/20
* ��������: bGUI.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* �������� ---------------------------------------------------------------------*/

/* BOOLESION.NET bGUI  */
/* �������� */
/*
**�ṩ���� LCD_FilledRectangle :��LCD��Ļ������ɫ���һ������.INT16U x,INT8U y,INT16U width,INT8U high,INT16U color
**         LCD_Write_String    :д�ַ���
** 		   LCD_DrawPoint	   ��LCD ����
*/
/* INT16U x,INT8U y ��ʼλ�� */
void CreateWindow(
	INT8U  *winname,		   /* ��������/���� */
	INT16U x,				   /* ����ˮƽ��ʼλ�� */
	INT16U y,				   /* ���ڴ�ֱ��ʼλ�� */
	INT16U width,			   /* ���ڿ�� */
	INT16U high,			   /* ���ڸ߶� */
	INT16U windowcolor		   /* ������ɫ */
)
{
	LCD_FilledRectangle(x + 1,y + 1,width - 1,high - 1,windowcolor);    /* �����ڷ��� width : 362  high : 176 */
	LCD_FilledRectangle(x + 1,y,width - 2,1,CTITLEBAR);		 	/* ������ */
	LCD_FilledRectangle(x,y + 1,width,WORDHIGH+1,CTITLEBAR);	
	LCD_Write_String(x + 16,y,winname,CTITLE,CTITLEBAR,0);		/* ���� */
	LCD_FilledRectangle(x + width - 28,y + 12,10,2,CTITLE);			/* ��С��ͼ�� width : 2  high : 10 */
	LCD_FilledRectangle(x + width - 16,y + 6,10,4,Red);			    /* �ر�ͼ�� width : 2  high : 10 */
	LCD_FilledRectangle(x + width - 16,y + 12,10,2,White);			/* �ر�ͼ�� width : 4  high : 10 */

	LCD_FilledRectangle(x,y + 1,2,high - 1,CTITLEBAR);					/* ��߿�*/
	LCD_FilledRectangle(width + x -2,y + 1,2,high-1,CTITLEBAR);		/* �ұ߿�*/
	LCD_FilledRectangle(x,high + y - 2,width,2,CTITLEBAR);		/* �ײ��߿� */
	LCD_FilledRectangle(x + 4,y + 3,10,8,CTITLE);				/* ����ͼ�� width : 10  high : 10 */
}

/* ����ͼ�� */

/* ����������ʾ */
void GUIToolICOPower(
	INT16U x,				   /* ����ˮƽ��ʼλ�� */
	INT16U y,				   /* ���ڴ�ֱ��ʼλ�� */
	INT8U power				   /* ����0 - 12 */
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

/* ������ */
void GUIProgressBar(
	INT16U x,				   /* ������ƽ��ʼλ�� */
	INT16U y,				   /* ��������ֱ��ʼλ�� */
	INT16U width,			   /* ���������� */
	INT16U high,			   /* �������߶� */
	INT16U Progress			   /* ���� 0 - 100 */
)
{	
	FP32 Tran;
	if(Progress < 2)
		LCD_FilledRectangle(x,y,width,high,Gray);	           /* ������ width : 250  high : 6*/
	Tran =   (FP32)(width) / 100;
	if(Progress > 100)
		Progress = 100;	
	LCD_FilledRectangle(x,y,Progress * Tran,high,Green);	   /* ������ ����״̬ */
}
/* ������2 */
void GUIProgressBar2(
	INT16U x,				   /* ������ƽ��ʼλ�� */
	INT16U y,				   /* ��������ֱ��ʼλ�� */
	INT16U width,			   /* ���������� */
	INT16U high,			   /* �������߶� */
	INT16U Progress			   /* ���� 0 - 100 */
)
{	
	FP32 Tran;
	LCD_FilledRectangle(x,y,width,high,Gray);	           /* ������ width : 250  high : 6*/
	Tran =   (FP32)(width) / 100;
	if(Progress > 100)
		Progress = 100;	
	LCD_FilledRectangle(x,y,Progress * Tran,high,Green);	   /* ������ ����״̬ */
}
/* ����ͼ�� vol 0 - 48 */
void GUIVolumeico(
	INT16U x,				   /* ˮƽ��ʼλ�� */
	INT16U y,				   /* ��ֱ��ʼλ�� */
	INT8U vol				   /* ����ֵ 0 - 48 */
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

/* ��һ�� */ 
void GUIUpSong(
	INT16U x,				   /* ˮƽ��ʼλ�� */
	INT16U y,				   /* ��ֱ��ʼλ�� */
	INT16U color
)
{
	INT8U i,j;
	LCD_FilledRectangle(x,y,5,20,color);	    /* ��һ�� ���� width : 5  high : 20 */
	for(i=0;i<20;i++)							/* ��ʵ������ */
	{
	for(j=i;j<20 - i;j++)
		{
			LCD_DrawPoint((x+15) - i,y + j,color);
		}
	}
}
/* ��һ�� */ 
void GUIDownSong(
	INT16U x,				   /* ˮƽ��ʼλ�� */
	INT16U y,				   /* ��ֱ��ʼλ�� */
	INT16U color
)
{
	INT8U i,j;
	LCD_FilledRectangle(x,y,5,20,color);	 /* ��һ�� ���� width : 5  high : 20 */
	for(i=0;i<20;i++)							 /* ��ʵ������ */
	{
		for(j=i;j<20 - i;j++)
		{
			LCD_DrawPoint((x-10) + i,y + j,color);
		}
	}
}
/* ���Ű�ť */
void GUIPlay(
	INT16U x,				   /* ˮƽ��ʼλ�� */
	INT16U y,				   /* ��ֱ��ʼλ�� */
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

/* ��ͣͼ�� */
void GUIPause(
	INT16U x,				   /* ˮƽ��ʼλ�� */
	INT16U y,				   /* ��ֱ��ʼλ�� */
	INT16U color
)
{

	LCD_FilledRectangle(x,y,5,20,color);	                /* ��ͣ width : 5  high : 20 */
	LCD_FilledRectangle(x + 10,y,5,20,color);
}
#if 0 
/* Ƶ�׷������� */
void GUISpectrum(
	INT16U x,				   /* ˮƽ��ʼλ�� */
	INT16U y,				   /* ��ֱ��ʼλ�� */
	INT8U  width,			   /* ���ο�� */
	INT16U color,			   /* ������ɫ */
	INT8U *specdata			   /* Ƶ������ */
)
{
	INT8U i;
	for(i=0;i<14;i++)
    {
		if(*specdata > 60)
			*specdata = 60;	
        LCD_FilledRectangle(x,y-(*specdata),width,(*specdata),color);	    /* ���� width : *  high :  */
		*specdata++;
        x += (width + 1);
    }
}
#endif /* GUISpectrum */

/* ��һ�� */ 
void GUIUp(
	INT16U x,				   /* ˮƽ��ʼλ�� */
	INT16U y,				   /* ��ֱ��ʼλ�� */
	INT16U color			   /* ��ɫ */
)
{
	INT8U i,j;
	for(i=0;i<20;i++)							/* ��ʵ������ */
	{
	for(j=i;j<20 - i;j++)
		{
			LCD_DrawPoint(x - i,y + j,color);
		}
	}
}

/* ��һ�� */ 
void GUIDown(
	INT16U x,				   /* ˮƽ��ʼλ�� */
	INT16U y,				   /* ��ֱ��ʼλ�� */
	INT16U color			   /* ��ɫ */
)
{
	INT8U i,j;
	for(i=0;i<20;i++)							 /* ��ʵ������ */
	{
		for(j=i;j<20 - i;j++)
		{
			LCD_DrawPoint(x + i,y + j,color);
		}
	}
}

/* ���ΰ�ť */
void GUIButton(
	INT8U  *btntitle,		   /* ��ť���� */
	INT16U x,				   /* ˮƽ��ʼλ�� */
	INT16U y,				   /* ��ֱ��ʼλ�� */
	INT16U width,			   /* ���� */
	INT16U high,			   /* �߶� */
	INT16U color			   /* ��ɫ */		
)
{
	LCD_FilledRectangle(x,y,width,high,color); 
	LCD_FilledRectangle(x,y,width,1,RGB(240,240,240));
	LCD_FilledRectangle(x,y,1,high,RGB(240,240,240)); 
	LCD_FilledRectangle(x,y + high,width,1,RGB(127,127,127));
	LCD_FilledRectangle(x + width,y,1,high + 1,RGB(127,127,127));
	LCD_Write_String(x+10,y + ((high - 16) / 2),btntitle,Black,color,0);		/* ���� */
}
/* ��СԲ�� */
void MinRound(
	INT16U x,				   /* ˮƽ��ʼλ�� */
	INT16U y,				   /* ��ֱ��ʼλ�� */
	INT16U color			   /* ��ɫ */
)
{
	/*  ���� */
	LCD_DrawPoint(x-1,y-1,RGB(color + 27,color +29,color +30));
	/*  ���� */
	LCD_DrawPoint(x+1,y-1,RGB(color +27,color +29,color +30));
	/* �� */
	LCD_DrawPoint(x,y-1,RGB(color +7,color +7,color +7));
	/* �� */
 	LCD_DrawPoint(x,y,color);
	/* �� */
	LCD_DrawPoint(x,y+1,RGB(color +7,color +7,color +7));
    /* �� */
	LCD_DrawPoint(x-1,y,RGB(color +7,color +7,color +7));
	/* �� */
	LCD_DrawPoint(x+1,y,RGB(color +7,color +7,color +7));
	/* ���� */
	LCD_DrawPoint(x-1,y+1,RGB(color +27,color +29,color +30));
	/* ���� */
	LCD_DrawPoint(x+1,y+1,RGB(color +27,color +29,color +30));

}