/* 按键扫描 */
#include "includes.h"
extern volatile INT8U menuflag; /* 菜单标识 */
volatile INT8U keybacknextcode = 0,keyentercode = 0;		/* 按键代码 */
extern volatile INT8U guiprintflag;	  /* 界面显示标识 */
void Keyboard(void)
{
	/* 按下KEY_MODE键则加载主界面 */
	if( (!KEY_MODE) && (menuflag != MAINMENU) )	 
		GUI_MAIN;
	/* NEXT BACK KEY */
	switch(menuflag)                             
	{		
		case MAINMENU:
		{
			if(!KEY_BACK)			   /* BACK 上一步 */
			{
				if(keybacknextcode < 8)
				{
					keybacknextcode++;
				}	
				else
					keybacknextcode = 0;
			   guiprintflag = 0; /* 重新打印GUI标识 */
			 }
			if(!KEY_NEXT)				  /* NEXT 下一步 */
			{
				if(keybacknextcode > 0)
				{
					keybacknextcode--;
				}
				else
					keybacknextcode = 8;
			   guiprintflag = 0; /* 重新打印GUI标识 */
			 }
			if(!KEY_ENTER)		/* ENTER */
				keyentercode = 1;
			else
				keyentercode = 0;
										
		}	
	}	
}