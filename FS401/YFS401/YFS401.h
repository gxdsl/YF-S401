#ifndef __YFS201C_H__
#define __YFS201C_H__

#include "usart.h"
#include "stdio.h"

typedef struct
{
	uint8_t receive_flag;   //1s��־λ
	uint16_t pluse_1s;      //1s���½���������
	
	float instant;          //˲ʱ����
	float acculat;          //�ۼ�����
}GOLBAL_FLOW;

extern GOLBAL_FLOW  golbal_flow;

void Flow_Read(void);


#endif
