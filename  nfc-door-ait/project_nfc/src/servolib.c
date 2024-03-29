
#include "servolib.h"

//Create new structs
TIM_TimeBaseInitTypeDef T;
TIM_OCInitTypeDef TO;
GPIO_InitTypeDef G;
NVIC_InitTypeDef N;

#define ServoPWMOut GPIO_Pin_0
#define ServoPWMPS GPIO_PinSource0

//If triangle mode is defined, output will vary between
//1ms and 2ms over a ~2s period. To change to static
//mode, merely comment this out.
//#define TRIANGLE_MODE

//Variable to hold PulseWidth. In triangle mode,
//PulseWidth will temporarily be <0, to ensure this
//doesnt overflow and destroy the triangle wave,
//it will need to be a 32bit integer.

 volatile uint32_t PulseWidth = 0;


void TIM2_IRQHandler(void){
 //Rate of output variation defined by PulseAdd
 //If PulseAdd is larger, output will vary faster.

 //WARNING: This value was only used to produce the waveform
 //in my logic analyzer image.
 //static int16_t PulseAdd = 10000;

 if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET){
 TIM_ClearITPendingBit(TIM2, TIM_IT_Update);


 //Set capture compare register to 1ms+PulseWidth time
 //Each PulseWidth time is equal to 20.833ns
 //meaning 20.8333ns*48000 = 1ms
 TIM_SetCompare1(TIM2, 48000+PulseWidth);
 }
}

void Servo_fcn(void)
{
 //Enable the clock to GPIOA and TIM2. The updated
 //standard peripheral library doesn't require
 //SystemInit() anymore.
 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
 SysTick_Config(SystemCoreClock/1000);
 //Setup timer 2 to overflow at 959999
 //with no clock division (running at 48MHz)
 //Period is calculated by:
 //(48e6/((Prescalar+1)*Freq) - 1
 //Where Freq = 50 t=0.02 s
 T.TIM_ClockDivision = TIM_CKD_DIV1;
 T.TIM_Prescaler = 0;
 T.TIM_Period = 960000 - 1;
 T.TIM_CounterMode = TIM_CounterMode_Up;
 TIM_TimeBaseInit(TIM2, &T);

 //Setup timer 2 output compare with the output being
 //reset in idle state and the output polarity being
 //high. Output is high if Cnt < CCR1.
 //Set initial pulse to 1ms (0% rotation)
 TO.TIM_OCIdleState = TIM_OCIdleState_Reset;
 TO.TIM_OCMode = TIM_OCMode_PWM1;
 TO.TIM_OCPolarity = TIM_OCPolarity_High;
 TO.TIM_OutputState = TIM_OutputState_Enable;
 TO.TIM_Pulse = 48000; //Initial pulse at 1ms
 
 //Initialize output compare for timer 2
 TIM_OC1Init(TIM2, &TO);

 //Disable OC preload
 TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);

 //Set update interrupt
 TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
 TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

 //Configure update interrupt IRQ
 N.NVIC_IRQChannel = TIM2_IRQn;
 N.NVIC_IRQChannelCmd = ENABLE;
 N.NVIC_IRQChannelPriority = 0;
 NVIC_Init(&N);

 //Configure Servo PWM output
 G.GPIO_Pin = ServoPWMOut;
 G.GPIO_Mode = GPIO_Mode_AF;
 G.GPIO_OType = GPIO_OType_PP;
 G.GPIO_Speed = GPIO_Speed_Level_1;
 GPIO_Init(GPIOA, &G);

 //Connect Servo PWM Output to timer 2 (GPIO_AF_2)
 GPIO_PinAFConfig(GPIOA, ServoPWMPS, GPIO_AF_2);

 //Start the timer!
 TIM_Cmd(TIM2, ENABLE);


 
	
	/*delay(5000);
	PulseWidth = 0;
	delay(5000);*/
	
}
 void changePulse_fcn(uint32_t val)
 {
	 PulseWidth = val;   //  96000; for 180 degrees
 }
 
 //Return 1 if open, 0 if close
 int Get_State(void)
 {
	 if (PulseWidth == OPEN)
	 {
		 return 1;
	 }
	 return 0;
 }