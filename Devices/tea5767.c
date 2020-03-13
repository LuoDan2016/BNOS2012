/******************** (C) COPYRIGHT 2012 BOOLESION.NET ***************************
* 产品名称: 布尔创51开发板 E1101
* 文件名称: tea5767.c
* 程序作者: BOOLESION.NET 布尔创(BOOLESION)电子科技 - NETC (陈建长)
* 程序版本: V1.2
* 编制日期: 2012/03/20
* 功能描述: TEA5767 收音机 驱动程序.
**********************************************************************************/

/* Includes ---------------------------------------------------------------------*/
#include "includes.h"

/* 宏定义 -----------------------------------------------------------------------*/
#define max_freq 108000
#define min_freq 87500



/* 变量声明 ---------------------------------------------------------------------*/
INT8U radio_write_data[5]={0x29,0x76,0x20,0x11,0x00};   /* 要写入TEA5767的数据 */
INT8U radio_read_data[5];                               /* TEA5767读出的状态 */
INT16U default_pll=108000;                              /* 默认存台的pll,101.8MHz */  
INT32U frequency = 108000;
INT16U  pll;
INT8U  radiocolsedata[5] =  {0x80,0x00,0x00,0x50,0x00}; /* 关闭TEA5767数据 */


#define ADC_MIN	6		    /* 频率入选的最小ADC */
INT8U Signal_Status=0;		/* 信号状态  最高位：立体声标志，高三位：停止搜索的信号强度。低四位：信号强度 */
/*********************************************************************************
** 函数名称: void Delay_4us(void).
** 功能描述: 4us延时.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void Delayus(unsigned int number)
{
	while(number--);
}
/*********************************************************************************
** 函数名称: void I2c_Start(void).
** 功能描述: 启动IIC总线函数.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void I2c_Start(void)
{
	SDA=1;
	Delayus(4);
	SCL=1;
	Delayus(4);
	SDA=0;
	Delayus(4);
	SCL=0;
	Delayus(4);
}

/*********************************************************************************
** 函数名称: void I2c_Stop(void).
** 功能描述: 停止IIC总线函数.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void I2c_Stop(void)
{
	SCL=0;
	Delayus(4);
	SDA=0;
	Delayus(4);
	SCL=1;
	Delayus(4);
	SDA=1;
	Delayus(4);
}

/*********************************************************************************
** 函数名称: INT8U Rcv_Byte(void).
** 功能描述: IIC总线接收数据,此数据可以是地址,可以是数据.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: rbyte 数据或地址.
**********************************************************************************/ 
INT8U Rcv_Byte(void)
{
	INT8U i,rbyte=0;
	for(i=8;i;i--)
	{
	SCL=1;
	Delayus(4);
	rbyte=rbyte<<1;
	rbyte=rbyte|(SDA);
	SCL=0;
	}
	return rbyte; 
}

/*********************************************************************************
** 函数名称: void I2c_Ack(bit a).
** 功能描述: IIC总线发送数据,此数据可以是地址,可以是数据 .
** 输入参数: 数据或地址.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/     
void Send_Byte(INT8U dat)
{
	INT8U i;
	for(i=8;i;i--)
	{
	SDA=(bit)(dat&0x80);
	Delayus(4);
	SCL=1;
	Delayus(4);
	SCL=0;
	Delayus(4);
	dat=dat<<1;
	}
}

/*********************************************************************************
** 函数名称: void I2c_Ack(bit a).
** 功能描述: 主控器进行应答信号.
** 输入参数: 发送1代表非应答  0代表应答.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/ 
void I2c_Ack(bit a)
{
	SDA=a;
	Delayus(4);
	SCL=1;
	Delayus(4);
	SCL=0;
	Delayus(4);
	SDA=1;
	Delayus(4);
}

/*********************************************************************************
** 函数名称: bit Test_Ack(void).
** 功能描述: 检查设备是否应答.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: 返回0代表应答,返回1代表不应答.
**********************************************************************************/
bit Test_Ack(void)
{
	bit ack;
	SDA=1;
	Delayus(4);
	SCL=1;
	Delayus(4);
	ack=SDA;
	Delayus(4);
	SCL=0;
	return ack;
}

/*********************************************************************************
** 函数名称: void radio_write(void).
** 功能描述: 将radio_write_data参数数据写入tea5767.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void radio_write(void)
{
    unsigned char i;
    I2c_Start();
    Send_Byte(0xc0);        /* TEA5767写地址 */
    if(!Test_Ack())  
        for(i=0;i<5;i++)
        {
            Send_Byte(radio_write_data[i]);
			I2c_Ack(0);
        }    
    I2c_Stop();    
}

/*********************************************************************************
** 函数名称: void get_pll(void).
** 功能描述: 由频率计算出PLL值,频率是一Khz为单位,比如88兆,frequency就是88000.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void get_pll(void)
{
    unsigned char hlsi;
    hlsi=radio_write_data[2]&0x10;  /* 判断高低边带接收 */
    if (hlsi)
		pll=(frequency+225)*1000/8192;
    else
		pll=(frequency-225)*1000/8192;
}

/*********************************************************************************
** 函数名称: void get_frequency(void).
** 功能描述: 由PLL值计算出频率.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/ 
void get_frequency(void)
{
    unsigned char hlsi;
    unsigned long npll=0;
    npll=pll;
    hlsi=radio_write_data[2]&0x10;	 /* 判断高低边带接收 */
    if (hlsi)
		frequency=npll*8192/1000-225;
    else
	    frequency=npll*8192/1000+225;
}

/*********************************************************************************
** 函数名称: void radio_read(void).
** 功能描述: 读TEA5767状态,并转换成频率.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/ 
void radio_read(void)
{
    INT8U i;
    pll=0;
    I2c_Start();
    Send_Byte(0xc1);                 /* TEA5767读地址 */
    if(!Test_Ack())
    {
        for(i=0;i<5;i++)
        {
            radio_read_data[i]=Rcv_Byte();
            I2c_Ack(0);
        }
    }
    I2c_Stop();
    pll=radio_read_data[0]&0x3f;	 /* 读取高6位数据 */
	pll<<=8;
	pll+=radio_read_data[1];		 /* 读取低六位数据 */
    get_frequency();
}


/*********************************************************************************
** 函数名称: void search(bit mode).
** 功能描述: 手动设置频率,mode=1,+0.1MHz; mode=0:-0.1MHz.
** 输入参数: bit mode.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/ 
void search(bit mode)
{
    radio_read();        
    if(mode)
    {
        frequency+=100;
        if(frequency>max_freq)
            frequency=min_freq;
    }
    else
    {
        frequency-=100;
        if(frequency<min_freq)
            frequency=max_freq;
    }        
    get_pll();
    radio_write_data[0]=pll>>8;		 /* 写入pll高6位字节 */
    radio_write_data[1]=pll&0x00ff;	 /* 写入pll低6位字节 */
    radio_write_data[2]=0x20;
    radio_write_data[3]=0x11;
    radio_write_data[4]=0x00;
    radio_write();
}

/*********************************************************************************
** 函数名称: void auto_search(bit mode).
** 功能描述: 自动搜台,mode=1,频率增加搜台; mode=0:频率减小搜台.
** 输入参数: bit mode.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/ 
void auto_search(bit mode)  
{  
    radio_read();  
    get_pll();  
    if(mode)  
        radio_write_data[2]=0xa0;  
    else  
        radio_write_data[2]=0x20;      
    radio_write_data[0]=pll/256+0x40;  
    radio_write_data[1]=pll%256;      
    radio_write_data[3]=0x11;  
    radio_write_data[4]=0x00;  
    radio_write();  
    radio_read();  
    while(!(radio_read_data[0]&0x80))     /* 搜台成功标志 */  
    {  
        radio_read();  
    }      
} 

/*********************************************************************************
** 函数名称: void radio_close(void).
** 功能描述: 关闭.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/
void radio_close(void)
{
    unsigned char i;
    I2c_Start();
    Send_Byte(0xc0);        /* TEA5767写地址 */
    if(!Test_Ack())  
        for(i=0;i<5;i++)
        {
            Send_Byte(radiocolsedata[i]);
			I2c_Ack(0);
        }    
    I2c_Stop();    
}


/*********************************************************************************
** 函数名称: void FreqShow(INT32U freq).
** 功能描述: 频率显示.
** 输入参数: INT32U freq.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/ 
void FreqShow(INT32U freq)
{
	
	freq/=100;											      /* 缩小100倍 760~1080的范围 */    
	if(freq>999)
		Lcd_WriteNumlen(1,freq/1000,134+50,90,White,Back_Color,1);	
	else 
		LCD_Write_String(134+50,90," ",White,Back_Color,1);			/* 清空显示 */	
	Lcd_WriteNumlen(1,(freq/100)%10,134+50+8,90,White,Back_Color,1);        /* 十位数 */
	Lcd_WriteNumlen(1,(freq/10)%10,134+50+16,90,White,Back_Color,1);		/* 个位数 */
	LCD_Write_String(134+50+24,90,".",White,Back_Color,0);                  /* "." */
	Lcd_WriteNumlen(1,freq%10,134+50+32,90,White,Back_Color,1);       /* 显示小数 */

	/* 频率进度条 */
	GUIProgressBar2(70,120,250,6,100 * ((FP32)((frequency/100) - 870) / (FP32)(1080 - 870)) );	
	
//	Signal_CH_Show();									     /* 显示信号强度，频道值 */
}

/*********************************************************************************
** 函数名称: void Signal_CH_Show(void).
** 功能描述: 显示信号强度.
** 输入参数: None.         
** 输出参数: None.
** 返回参数: None.
**********************************************************************************/ 
void Signal_CH_Show(void)
{

  /* 显示信号强度 */	
	Lcd_WriteNumlen(1,Signal_Status&0x0F,120,76,White,Back_Color,1);	

}
