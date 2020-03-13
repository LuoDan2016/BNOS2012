/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* ��Ʒ����: ������51������ E1101
* �ļ�����: lcd5420.c
* ��������: BOOLESION.NET ������(BOOLESION)���ӿƼ� - NETC (�½���)
* ����汾: V1.2
* ��������: 2012/03/20
* ��������: LCD OTM4001��������.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"
#include "diskio.h"
#include "pff.h"

/* �������� ---------------------------------------------------------------------*/

extern const unsigned char code __ASCII816[]; /* �����ⲿASCII���� */
/*********************************************************************************
** ��������: void LCD_Delay(INT8U count).
** ��������: LCD��ʱ����.
** �������: INT8U count.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void LCD_Delay(INT8U count)   
{
	int  i,j;
    for(i=0;i<count;i++);
		for(j=0;j<100;j++);
}

/*********************************************************************************
** ��������: void LCD_Write_CMD(INT16U iadd).
** ��������: LCDдָ��.
** �������: INT16U iadd �Ĵ�����ַ.         
** �������: None.
** ���ز���: None.
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
** ��������: void LCD_Write_Data(INT16U idat).
** ��������: LCDд����.
** �������: INT16U idat 16Ϊ����.         
** �������: None.
** ���ز���: None.
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
** ��������: INT16U LCD_Read_CMD(void).
** ��������: LCD������.
** �������: None.         
** �������: None.
** ���ز���: None.
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
** ��������: INT16U LCD_Read_Data(void).
** ��������: LCD������.
** �������: None.         
** �������: None.
** ���ز���: ((d1&0xff) | (d2<<8) ) 24λ��ɫ.
**********************************************************************************/
INT16U LCD_Read_Data(void)
{
	INT16U d1,d2;
	LCD_DATA_PORT = 0XFF;  /* �������� */
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
** ��������: void LCD_Write_Reg(INT16U iadd, INT16U iidata).
** ��������: ��lcd�Ĵ�����д���������.
** �������: INT16U iadd, INT16U iidata.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void LCD_Write_Reg(INT16U iadd, INT16U iidata)
{
	LCD_Write_CMD(iadd);
	LCD_Write_Data(iidata);
}

/*********************************************************************************
** ��������: void LCD_SET_XY(INT16U x,INT8U y).
** ��������: ���ù�꺯��.
** �������: INT16U x,INT8U y.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void LCD_SET_XY(INT16U x,INT8U y)
{
    LCD_Write_Reg(0x200,y);
    LCD_Write_Reg(0x201,x);
    LCD_Write_CMD(0x0202);    
}

/*********************************************************************************
** ��������: void LCD_Init(void).
** ��������: LCD��ʼ������.
** �������: None.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void LCD_Init(void)
{
	LCD_Backlight = 0;	/* ������� 0:�� 1���� */
   	LCD_Backlight = 1;	/* ������� 0:�� 1���� */
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
** ��������: void LCD_Clear (INT16U color).
** ��������: LCDָ����ɫ����.
** �������: INT16U color ������ɫ.         
** �������: None.
** ���ز���: None.
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
** ��������: void LCD_DrawPoint(INT16U x,INT8U y,INT16U color).
** ��������: LCDָ��λ�û���.
** �������: INT16U x,INT8U y,INT16U color λ�á���ɫ.         
** �������: None.
** ���ز���: None.
**********************************************************************************/
void LCD_DrawPoint(INT16U x,INT8U y,INT16U color)
{
    LCD_SET_XY(x,y);
 	LCD_Write_Data(color);
}
#endif /* LCD_DrawPoint */

#if 1
/*********************************************************************************
** ��������: INT16U LCD_GetPoint(INT16U x,INT16U y).
** ��������: LCD��ȡָ���������ɫֵ.
** �������: INT16U x,INT16U y λ��.         
** �������: None.
** ���ز���: data1 ��ɫ.
**********************************************************************************/
INT16U LCD_GetPoint(INT16U x,INT16U y)
{
	INT16U data1; 
	
	LCD_Write_Reg(0x200,y); /* Lcd���GRAMˮƽ��ʼλ�� */ 
	LCD_Write_Reg(0x201,x); /* Lcd��괹ֱGRAM��ʼλ�� */     
	LCD_Write_Reg(0x210,y); /* ˮƽ GRAM��ʼλ�� */ 
	LCD_Write_Reg(0x211,y); /* ˮƽGRAM��ֹλ�� */ 
	LCD_Write_Reg(0x212,x); /* ��ֱGRAM��ʼλ�� */ 
	LCD_Write_Reg(0x213,x); /* ��ֱGRAM��ֹλ�� */  
	LCD_Write_CMD(0x0202); 
	
	data1=LCD_Read_Data();  /* ��� */
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
** ��������: LCD_Line.
** ��������: LCD��Ļ����.
** �������: int x1,int y1,int x2,int y2,int color.         
** �������: None
** ���ز���: None
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
* ��������: Glib_FilledRectangle.
* ��������: ��LCD��Ļ������ɫ���һ������.
* �������: INT16U x,INT8U y,INT16U width,INT8U high,INT16U color         
* �������: None
* ���ز���: None
*******************************************************************************/
void LCD_FilledRectangle(INT16U x,INT8U y,INT16U width,INT8U high,INT16U color)
{
	INT16U i=0,j=0;
	LCD_SET_XY(x,y);	/* ����LCD��ʾ��� */
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
** ��������: LCD_Write_ASCII().
** ��������: д�����ַ�ASCII�� ASCII�ֿ��ֿ�.
** �������: INT8U String,INT16U x,INT88U y,INT16U color,INT16U backcolor,INT8U bcst.         
** �������: None
** ���ز���: None
*******************************************************************************/
void LCD_Write_ASCII(INT8U String,INT16U x,INT8U y,INT16U color,INT16U backcolor,INT8U bcst)
{
	 
	   unsigned short int i,j;
       unsigned char mask,buf;             /* ���建����� ָ�� */
	   for( i = 0 ; i < 16 ; i++ )		        /* ѭ��ʮ���� */
	   {
	   		mask = 0x80;			            /* ��λ�����������ڵ�λ 1 ����֪���Ƿ�Ϊ1 ������ǰ�λ������� */
	  		buf = __ASCII816[String*16 + i];    /* 0-255��ASCII�� ��N N��ASCII֮Ϊ78=��78*16=1536��N�ĳ�ʼ��ַ ����ָ�� */
			for( j = 0 ; j < 8 ; j++ )	        /* ѭ������ */
			{
				if( buf & mask )		         /* ����������Ϊ�����ӡ */
				{
					LCD_DrawPoint(x+j,y+i,color);
				}
				else
                {
					if(bcst)
	               	LCD_DrawPoint(x+j,y+i,backcolor);
                }						 
				mask >>= 1;			              /* ����λ�������һ�� */
			}
	   }		

}

/*******************************************************************************
** ��������: LCD_Write_HZ().
** ��������: д�����ַ����� SPI FLASH�ֿ�.
** �������: INT8U String,INT16U x,INT88U y,INT16U color,INT16U backcolor,INT8U bcst.         
** �������: None
** ���ز���: None
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
	/* ������� */
	for( i = 0 ; i < 16 ; i++ )		        /* ѭ��ʮ���� */
	{
		LCD_CS_Low();
		LCD_RS_High();
		mask = 0x80;			            /* ��λ�����������ڵ�λ 1 ����֪���Ƿ�Ϊ1 ������ǰ�λ������� */
		buf = charbuff[i * 2];					/* ȡ������� */					
		for( j = 0 ; j < 8 ; j++ )	        /* ѭ������ */
		{
			if( buf & mask )		         /* ����������Ϊ�����ӡ */
			{
				LCD_Write_Data(color);
			}
			else
	        {
				if(bcst)
	           		LCD_Write_Data(backcolor);
	        }						 
			mask >>= 1;			              /* ����λ�������һ�� */
		}
		LCD_SET_XY(x,++y);
	}
	/* �Ҳ����� */
	LCD_SET_XY(x+=8,y-=16);
	for( i = 0 ; i < 16 ; i++ )		        /* ѭ��ʮ���� */
	{
		LCD_CS_Low();
		LCD_RS_High();
		mask = 0x80;			            /* ��λ�����������ڵ�λ 1 ����֪���Ƿ�Ϊ1 ������ǰ�λ������� */
		buf = charbuff[i * 2 + 1]; 						/* ȡ�Ҳ����� */
		for( j = 0 ; j < 8 ; j++ )	        /* ѭ������ */
		{
			if( buf & mask )		         /* ����������Ϊ�����ӡ */
			{
				LCD_Write_Data(color);
			}
			else
	        {
				if(bcst)
	           		LCD_Write_Data(backcolor);
	        }						 
			mask >>= 1;			              /* ����λ�������һ�� */
		}
		LCD_SET_XY(x,++y);
	}			
}

/*******************************************************************************
** ��������: LCD_Write_String().
** ��������: дASCII���ַ���.
** �������: INT16U x,INT8U y,INT8U *String,INT16U color,INT16U backcolor,INT8U bcst.         
** �������: None
** ���ز���: None
*******************************************************************************/
void LCD_Write_String(INT16U x,INT8U y,INT8U *String,INT16U color,INT16U backcolor,INT8U bcst)
{
	INT8U i = 0;
    while ((* String  != 0) && (i < 50))
    {
		if( *String > 0xA0 & *(String+1) > 0xA0 )  /* ͬʱ���� 0xA0����GB2312����*/
		{	  /*  *pStr-0xA0=���� ,*(pStr+1)-0xA0=λ��,����X100+λ��=��λ��  ������� */
			LCD_Write_HZ(x,y,(*String - 0xA0)*0x0064 + *(String+1) - 0xA0,color,backcolor,bcst);
			String += 2;	     /* ȡ��һ��ָ���ַ */
			/* Decrement the column position by 16 */
			x += 16;	 /* 16���� */
			i += 2;		 /* ��ʾ���� */
		}						  
		else
		{
	        LCD_Write_ASCII(( *String++),x,y,color,backcolor,bcst);
	         /* Decrement the column position by 8 */
			x += 8;
			i += 1;		/* ��ʾ���� */
		}
    }
}


#if 0
/*******************************************************************************
* ��������: Lcd_PutNum.
* ��������: LCD��ֵ��ʾ32λ 0-4294967295 ����ָ������NETC-�½���.	
* �������: unsigned int x,unsigned int y,unsigned int c,unsigned int bk_c,
             unsigned long num(��������),unsigned int st  ������ɫѡ��
			  st = 1 �� st = 0 ��,�ڶ�̬�仯�������,���û��������ɫ��ǰ����Ϣ����.     
* �������: None
* ���ز���: None
*******************************************************************************/
void Lcd_WriteNum(unsigned int x,unsigned int y,unsigned int c,unsigned int bk_c,unsigned long  num,unsigned char st)
{
    unsigned int length = 0 , i = 0 ;		 /* ���ݳ��� */
	unsigned long temp,databuf;
	unsigned char asciibit = 8;				 /* ASCIIλ�� */
	databuf	= num;							 /* �������� ����㳤�Ȼ�ʹ����Ϊ0 */
	if(num == 0)							 /* �������Ϊ0 ����ʾ0 */
		LCD_Write_ASCII(x,y,48,White,Black,1);	 /* 48Ϊ0��ASCIIֵ */
	while(num!=0)							 /* �������ݳ��� */
	{
		num = num / 10;
		length++;
	}										 
	for(i=0;i<length;i++)					 /* ��ӡ���� */
	{											
		temp = databuf % 10;			     /* �����λ��ʼ��ȡ���� */
		databuf = databuf / 10;				 /* ��ʣ��λ������ */
		/* �����λ��ʼ��ӡ ��4+48=52���� 4��ASCII��ֵ ��ASCII����� */				
		LCD_Write_ASCII(x+(length*asciibit-asciibit),y,temp+48,c,bk_c,st);
		x -= asciibit;
	}
}
#endif	/* Lcd_WriteNum */

#if 1
 /*******************************************************************************
* ��������: Lcd_PutNum.		 ָ������
* ��������: LCD��ֵ��ʾ32λ 0-4294967295 ����ָ������NETC-�½���.	
* �������: unsigned int x,unsigned int y,unsigned int c,unsigned int bk_c,
             unsigned long num(��������),unsigned int st  ������ɫѡ��
			  st = 1 �� st = 0 ��,�ڶ�̬�仯�������,���û��������ɫ��ǰ����Ϣ����.     
* �������: None
* ���ز���: None
*******************************************************************************/
void Lcd_WriteNumlen(INT8U length,INT32U  num,INT16U x,INT16U y,INT16U c,INT16U bk_c,INT8U st)
{
    unsigned int i = 0 ; /* ���ݳ��� */
	unsigned long temp;
	unsigned char asciibit = 8;				 /* ASCIIλ�� */									 
	for(i=0;i<length;i++)					 /* ��ӡ���� */
	{											
		temp = num % 10;			     /* �����λ��ʼ��ȡ���� */
		num = num / 10;				 /* ��ʣ��λ������ */
		/* �����λ��ʼ��ӡ ��4+48=52���� 4��ASCII��ֵ ��ASCII����� */				
		LCD_Write_ASCII(temp+48,x+(length*asciibit-asciibit),y,c,bk_c,st);
		x -= asciibit;
	}
}
#endif /* Lcd_WriteNumlen */
