#include "YFS401.h"

GOLBAL_FLOW golbal_flow;

// ��������ģ�͵�ö������
typedef enum {
    MODE_4_PIPE = 0,   // �ķֹ�
    MODE_6_PIPE = 1,   // ���ֹ�
    MODE_6MM_PIPE = 2  // 6mm��
} FlowModel;

// ������������
float flowK[3] = {5.0f, 5.5f, 80.0f};                  // ����ϵ�� K
float pulseCntPerLiter[3] = {300.0f, 330.0f, 4800.0f}; // ÿ��ˮ������

// ���� Flow_Model
FlowModel flowModel = MODE_6MM_PIPE; // Ĭ��ʹ��6mm��


uint32_t pluse1L;           //����1Lˮ��������

//==============================================================================
// @����: Flow_Read(void)
// @����: ��ȡ����
// @����: None
// @����: None
// @ʱ��: 2024.2.26
//==============================================================================
void Flow_Read(void)
{
    // ���� Flow_Model ѡ��ͬ����������
    float flowKValue = flowK[flowModel];
    float pulseCntValue = pulseCntPerLiter[flowModel];
    
	if(golbal_flow.pluse_1s > 0)
	{
		golbal_flow.acculat += (golbal_flow.pluse_1s * 1000 / pulseCntValue);   //��λmL
		pluse1L+=golbal_flow.pluse_1s;
		golbal_flow.instant = golbal_flow.pluse_1s / flowKValue;  //��λ��L/min��

        if(golbal_flow.acculat >= 1000000)        //����ۼ�����1000L
		{
			golbal_flow.acculat = 0;
		}
	}
	else
	{
		golbal_flow.instant  = 0;
	}
	
    printf("˲��������%.2f��L/min�� �ۼ�������%.2f mL   ��������%d \n",golbal_flow.instant,golbal_flow.acculat,golbal_flow.pluse_1s);
   
	golbal_flow.receive_flag = 0;   //������ɱ�־λ����
    golbal_flow.pluse_1s = 0;       //����������
}




