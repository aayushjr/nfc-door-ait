/**
* @file      sic4310.c
* @author    Supachai Vorapojpisut
* @version   1.0
* @date      November 4, 2014
* @brief     SIC4310 module using USART1 in IRQ mode.
*/

/* Includes -----------------------------------------------------------------------*/
#include "sic4310.h"

/* Private types ------------------------------------------------------------------*/
/* Private constants --------------------------------------------------------------*/
#define SIC4310_BAUDRATE    115200

/* Private macro ------------------------------------------------------------------*/
/* Private variables --------------------------------------------------------------*/
static SIC4310_Struct buffer_msg;
    
/* Private function prototypes ----------------------------------------------------*/
/* Private functions --------------------------------------------------------------*/

/**
* @brief    Configure USART1, pins PB6/PB7, and enable TXE/RXNE IRQ handler
* @param    None
* @retval   None
*/
void SIC4310_config()
{
    USART_InitTypeDef usart_init_struct;
    GPIO_InitTypeDef gpio_init_struct;
    NVIC_InitTypeDef nvic_init_struct;
    
    // Enable GPIOB and USART1
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    
    // Configure pin PB6 for Tx, pin PB7 for Rx 
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_1);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_1);
    
    gpio_init_struct.GPIO_Mode = GPIO_Mode_AF;
	  gpio_init_struct.GPIO_OType = GPIO_OType_PP;
//	  gpio_init_struct.GPIO_Speed = GPIO_Speed_Level_1;
	  gpio_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
    gpio_init_struct.GPIO_PuPd = GPIO_PuPd_UP;
    gpio_init_struct.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOB, &gpio_init_struct);
    
		//gpio_init_struct.GPIO_PuPd = GPIO_PuPd_UP;
    gpio_init_struct.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOB, &gpio_init_struct);
    
    // Configure USART1 for 115200,8,n,1
    usart_init_struct.USART_BaudRate = SIC4310_BAUDRATE;
    usart_init_struct.USART_WordLength = USART_WordLength_8b;
    usart_init_struct.USART_Parity = USART_Parity_No;
    usart_init_struct.USART_StopBits = USART_StopBits_1;
    usart_init_struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    usart_init_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART1, &usart_init_struct);
    USART_Cmd(USART1, ENABLE);
    
    // Configure NVIC for USART1 IRQ
    nvic_init_struct.NVIC_IRQChannel = USART1_IRQn;
    nvic_init_struct.NVIC_IRQChannelPriority = 0;
    nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic_init_struct);
    
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
}


/**
* @brief    Read stored message
* @param    pmsg    Pointer to buffer
* @retval   None
*/
void SIC4310_read(SIC4310_Struct *pmsg)
{
}


/**
* @brief    Write into message
* @param    pmsg    Pointer to buffer
* @retval   None
*/
void SIC4310_write(SIC4310_Struct *pmsg)
{
}


/**
* @brief    Return status of buffer storing UART data
* @param    None
* @retval   True if available, 0 otherwise
*/
int SIC4310_available(void)
{
    return 0;
}


// IRQ handler for USART1 TXE and RXNE events
void USART1_IRQHandler()
{
		uint8_t data;
    // See 8.2.1 TxRU command, 64-byte downlink FIFO
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
        data = USART_ReceiveData(USART1);
    }
    
    // See 8.2.2 RxUR command, 64-byte uplink FIFO
    if (USART_GetITStatus(USART1, USART_IT_TXE) != RESET) {
        USART_SendData(USART1,data);
    }
}
