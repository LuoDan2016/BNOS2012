/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: BNOS 2012
* �ļ�����: bmpdecode.c
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/03/20
* ��������: BNOS ͼ����봦��.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"
#include "diskio.h"
#include "pff.h"

#define BUFFSIZE 252 /* ÿ�ζ���BMP���ݴ�С һ��Ϊ3�ı��� */
#define DISWIDTH 245 /* ������ʾ��� */
#define DISHIGH  125 /* ������ʾ�߶� */
/* RGB24 TO RGB16 */
#define TRANSFORM(color,r,g,b) color = ((r>>3)<<11)|((g>>2)<<5)|(b>>3)

/* �ļ�ϵͳ�������� */
extern volatile FRESULT res;	
extern volatile INT16U br;
extern volatile BYTE buff[256]; /*SD Buffer Size 256 Byte*/


#if 1
/*********************************************************************************
** ��������: void Bmpdisplay(INT16U x,INT8U y,INT8U *bmppath).
** ��������: BMPͼ�����.
** �������: INT16U x ˮƽλ������(��ʾ),INT8U y ��ֱλ������(��ʾ),
**			 INT8U *bmppath BMP�ļ�·��.         
** �������: None
** ���ز���: None
**********************************************************************************/	

INT8U BmpDecode(INT16U x,INT8U y,INT8U *BMPPath)
{
	INT16U width,high,i=0,j=0;
	INT16U biBitCount,getcodecount,color;            /* ���ļ����� ���ر�����  ��ɫ */  
	INT32U offset=0;	                             /* ͼ�����ݵ�ƫ���� */
	INT8U *prgbdata;
	res = pf_open(BMPPath); 						 /* ���ļ� */
	if(res != 0)
	{return 1;}										 /* ��ʧ�ܷ��� 1 �ɹ����� 0 */
	else
	{
		pf_read(buff,56,&br);                            /* ��ȡ54�ֽ��ļ�ͷ+2�ֽڵ�ɫ���� */       
		biBitCount = (INT32U)(buff[0x1C]);               /* ������ر����� */    
		offset = (INT32U)(buff[0x0A]);                   /* �õ�ͼ�����ݵ�ƫ���� 10 - 13*/
		width = (INT32U)(buff[0x12]);                    /* �õ�ͼ���� 18 - 21�ֽ�*/  
		high = (INT32U)(buff[0x16]);                     /* �õ�ͼ��߶� 22 - 25*/ 
		pf_lseek(offset+1);			                     /* ͷ�ļ�ƫ���� */
		getcodecount=BUFFSIZE;
		LCD_SET_XY(x,high+y);	                         /* ����LCD��ʾ��� */
														 /* 24 BIT BMP ���������ʾ���� */
		if(width <= DISWIDTH && high <= DISHIGH && buff[0] == 'B' && buff[1] == 'M')
		for(i=0;i<high;i++)			 
		{	
			for(j=0;j<width;j++)	  
			{
		 	    /* ��ʾͼ��,��Ҫ��RGB24ת��ΪRGB565	*/
			    /* ��BMP�ļ��ж�����ͼ�����������������ֽ�B G R */
				/* ��ɫrռ5Ϊ���ε���λ  ��ɫgռ6Ϊ���ε���λ   ��ɫbռ5Ϊ���ε���λ */ 
				/* �ȶ����������ֽڶ�Ӧ����ͼ���е����½ǵ��Ǹ�����,��������ֽڶ�Ӧͼ�� ���Ͻ� */
				if(getcodecount==BUFFSIZE)
			   	{
					res = pf_read(buff,BUFFSIZE,&br);
					if(res || br == 0)break;/* �����ʹ��� */
					prgbdata = buff;
					getcodecount=0;
				}
				getcodecount+=3;
				/* ��ɫת�� */
				color = ((*prgbdata++) &(~(0x03)))<<3;
				color +=(((*prgbdata++)&(~(0x7)))<<8);
				color +=(((*prgbdata++)&(~(0x7)))>>3);
				/* LCD��ʾ */
				LCD_Write_Data(color);   
			}
			LCD_SET_XY(x,high+y-i);
		}
		return 0;
	}
}
#endif

/*********************************************************************************
** ��������: FlashGraphDis().
** ��������: ��ȡFLASH BMP ������ʾ,�洢ʱ��Ҫȷ����ַ����BMP-24BIT����ͷ�ļ�ֱ�Ӵ��.
** �������: INT16U x ˮƽλ������(��ʾ),INT8U y ��ֱλ������(��ʾ) 
**			 INT16U width,INT16U high ͼ�� ��,�� , INT32U GraphAddr ���ݻ�ַ.         
** �������: None
** ���ز���: None
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
	 	    /* ��ʾͼ��,��Ҫ��RGB24ת��ΪRGB565	*/
		    /* ��BMP�ļ��ж�����ͼ�����������������ֽ�B G R */
			/* ��ɫrռ5Ϊ���ε���λ  ��ɫgռ6Ϊ���ε���λ   ��ɫbռ5Ϊ���ε���λ */ 
			/* �ȶ����������ֽڶ�Ӧ����ͼ���е����½ǵ��Ǹ�����,��������ֽڶ�Ӧͼ�� ���Ͻ� */
			if(getcodecount==BUFFSIZE)
		   	{
				/* 
				**����Flash ��BMPͼ������ �洢��ַ+BMPƫ���� + ��ȡ����
				*/
				M25P16_Fast_Read_Data(GraphAddr + ( readcount * 252),252,buff);
				prgbdata = buff;
				getcodecount=0;
				readcount++;
			}
			getcodecount+=3;
			/* ��ɫת�� */
			color = ((*prgbdata++) &(~(0x03)))<<3;
			color +=(((*prgbdata++)&(~(0x7)))<<8);
			color +=(((*prgbdata++)&(~(0x7)))>>3);
			/* LCD��ʾ */
			LCD_Write_Data(color);    
		}
		LCD_SET_XY(x,++y);
	}
}
