#ifndef __YFS201C_H__
#define __YFS201C_H__

#include "usart.h"
#include "stdio.h"

typedef struct
{
	uint8_t receive_flag;   //1s标志位
	uint16_t pluse_1s;      //1s内下降沿脉冲数
	
	float instant;          //瞬时流量
	float acculat;          //累计流量
}GOLBAL_FLOW;

extern GOLBAL_FLOW  golbal_flow;

void Flow_Read(void);


#endif
