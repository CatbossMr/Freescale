#include "include.h"


/*  ������   */
FTM_InitTypeDef motor_PWM_init_struct;
void Motor_Init(void)
{
  motor_PWM_init_struct.FTM_Ftmx=FTM0;
  motor_PWM_init_struct.FTM_Mode= FTM_MODE_PWM;
  motor_PWM_init_struct.FTM_PwmFreq=10000;
  LPLD_FTM_Init(motor_PWM_init_struct);
  
  LPLD_FTM_PWM_Enable(FTM0, FTM_Ch0, 0,PTC1,ALIGN_LEFT);
  LPLD_FTM_PWM_Enable(FTM0, FTM_Ch1, 480,PTC2,ALIGN_LEFT);
  Motor_Drive(1300);
}


void Motor_Drive(int16 duty)
{
  /*��Χand�������ƣ�������*/
  if(duty>=0)
  {
    duty=duty>1700?1700:duty;
    LPLD_FTM_PWM_ChangeDuty(FTM0,FTM_Ch0,0);
    LPLD_FTM_PWM_ChangeDuty(FTM0,FTM_Ch1,duty);  
  }else{
    duty=abs(duty);
    duty=duty>2000?2000:duty;
    LPLD_FTM_PWM_ChangeDuty(FTM0,FTM_Ch0,duty);
    LPLD_FTM_PWM_ChangeDuty(FTM0,FTM_Ch1,0);  
  }
}


/*  ������   */
FTM_InitTypeDef server_PWM_init_struct;
void Server_Init(void)
{
  server_PWM_init_struct.FTM_Ftmx=FTM2;
  server_PWM_init_struct.FTM_Mode=FTM_MODE_PWM;
  server_PWM_init_struct.FTM_PwmFreq=Server_PWM_FREQ;
  
  LPLD_FTM_Init(server_PWM_init_struct);
  // FTM2 ch1ͨ�����м�ֵ,B19���ţ������
  LPLD_FTM_PWM_Enable(FTM2,FTM_Ch1,Server_PWM_MIDDLE,PTB19,ALIGN_LEFT); 
  Server_Drive(Server_PWM_MIDDLE);
}

void Server_Drive(uint32 duty)
{
  if(duty < Server_PWM_LEFT_MAX) duty = Server_PWM_LEFT_MAX;
  if(duty > Server_PWM_RIGHT_MAX) duty = Server_PWM_RIGHT_MAX;
  LPLD_FTM_PWM_ChangeDuty(FTM2,FTM_Ch1,duty);
}

/*  ���������   */

int32 QD_Interval=0;
int32 QD_Result=0;
int32 Last_QD_Result=0;

// FTM��ʼ��
FTM_InitTypeDef encoder_pwm_init_struct;
void Encoder_PWM_Init(void)
{
  encoder_pwm_init_struct.FTM_Ftmx = FTM1;
  encoder_pwm_init_struct.FTM_Mode = FTM_MODE_QD;
  encoder_pwm_init_struct.FTM_QdMode = QD_MODE_CNTDIR;
  LPLD_FTM_Init(encoder_pwm_init_struct);
  LPLD_FTM_QD_Enable(FTM1,PTA12,PTA13);
}

//�жϺ���
void pit_isr0(void)
{
  QD_Result  =  LPLD_FTM_GetCounter(FTM1);
  
  if(QD_Result<=Last_QD_Result)
  {
    QD_Interval = Last_QD_Result - QD_Result;
  }
  else
  {
    QD_Interval = 65535 + Last_QD_Result-QD_Result;
  }
  Last_QD_Result = QD_Result;
  Speed_Control();
}


// PIT��ʼ��
PIT_InitTypeDef encoder_pit_init_struct;
void Encoder_PIT_Init(void)
{
  encoder_pit_init_struct.PIT_Pitx = PIT0;
  encoder_pit_init_struct.PIT_PeriodMs = 10;
  encoder_pit_init_struct.PIT_Isr = pit_isr0;
  LPLD_PIT_Init(encoder_pit_init_struct);
  LPLD_PIT_EnableIrq(encoder_pit_init_struct);
}

void Encoder_Init(void)
{
  Encoder_PWM_Init();
  Encoder_PIT_Init();
  
}