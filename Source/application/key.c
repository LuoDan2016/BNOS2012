/* ����ɨ�� */
#include "includes.h"
extern volatile INT8U menuflag; /* �˵���ʶ */
volatile INT8U keybacknextcode = 0,keyentercode = 0;		/* �������� */
extern volatile INT8U guiprintflag;	  /* ������ʾ��ʶ */
void Keyboard(void)
{
	/* ����KEY_MODE������������� */
	if( (!KEY_MODE) && (menuflag != MAINMENU) )	 
		GUI_MAIN;
	/* NEXT BACK KEY */
	switch(menuflag)                             
	{		
		case MAINMENU:
		{
			if(!KEY_BACK)			   /* BACK ��һ�� */
			{
				if(keybacknextcode < 8)
				{
					keybacknextcode++;
				}	
				else
					keybacknextcode = 0;
			   guiprintflag = 0; /* ���´�ӡGUI��ʶ */
			 }
			if(!KEY_NEXT)				  /* NEXT ��һ�� */
			{
				if(keybacknextcode > 0)
				{
					keybacknextcode--;
				}
				else
					keybacknextcode = 8;
			   guiprintflag = 0; /* ���´�ӡGUI��ʶ */
			 }
			if(!KEY_ENTER)		/* ENTER */
				keyentercode = 1;
			else
				keyentercode = 0;
										
		}	
	}	
}