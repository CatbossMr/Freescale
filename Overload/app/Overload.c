/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�Overload��-----------------
 * @file Overload.c
 * @version 0.0
 * @date 2013-9-29
 * @brief ���ڸù��̵�����
 *
 * ��Ȩ����:�����������µ��Ӽ������޹�˾
 * http://www.lpld.cn
 * mail:support@lpld.cn
 * Ӳ��ƽ̨:  LPLD K60 Card / LPLD K60 Nano
 *
 * �����̻���"��������K60�ײ��V3"������
 * ���п�Դ�������"lib"�ļ����£��û����ظ��ĸ�Ŀ¼�´��룬
 * �����û������豣����"project"�ļ����£��Թ����������ļ�������
 * �ײ��ʹ�÷���������ĵ��� 
 *
 */
#include "include.h"


   
   
void main (void)
{
  DisableInterrupts;
  Led_Init();
  LCD_Init();
  Camera_Init();
  Blue_Init();
  Key_Init();
  Server_Init();
  Motor_Init();  
  Led_Off();
  Encoder_Init();
  EnableInterrupts;
  while(1)
  {
    if(Has_Img)
    {
      Has_Img=0;
      Get_Bound_Qian();
    }
  } 
  
}

