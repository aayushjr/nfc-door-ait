#ifndef __SIC4310_H
#define __SIC4310_H

#ifdef __cplusplus
 extern ""C"" {
#endif

/* Includes -----------------------------------------------------------------------*/
#include "stm32f0xx.h"
     
/* Exported types -----------------------------------------------------------------*/
typedef struct _SIC4310_Struct {
	uint16_t size;
	uint8_t data[16];
	//uint16_t idx;
} SIC4310_Struct;    
     
/* Exported constants -------------------------------------------------------------*/
/* Exported macro -----------------------------------------------------------------*/
/* Exported functions -------------------------------------------------------------*/
void SIC4310_config(void);
void SIC4310_read(SIC4310_Struct *pmsg);
void SIC4310_write(SIC4310_Struct *pmsg);
int SIC4310_available(void);


#ifdef __cplusplus
 }
#endif

#endif // __SIC4310_H