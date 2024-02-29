#include "YFS401.h"
#include "tim.h"

GOLBAL_FLOW golbal_flow;

#define MODE_4_K            5.0f        //����ϵK
#define MODE_4_PLUSE_CNT_1L 300.0f      //ÿ��ˮ������
//#define MODE_6_K            5.5f
//#define MODE_6_PLUSE_CNT_1L 330.0f

#define MODE_6_K            750.0f
#define MODE_6_PLUSE_CNT_1L 45000.0f

#define	FLOW_FULL			1000000

uint8_t Flow_Model = 0;     //4�ֹܶ���Ϊ1��6�ֹܶ���Ϊ0

uint32_t pluse1L;
//==============================================================================
// @����: Flow_Read(void)
// @����: ��ȡ����
// @����: None
// @����: None
// @ʱ��: 2024.2.26
//==============================================================================
void Flow_Read(void)
{
	if(golbal_flow.receive_flag)
	{
		if(golbal_flow.pluse_1s > 0)
		{
        #ifdef Flow_Model
			/*���㹫ʽ��
				�ۼ����� = ��˲ʱ����������
								 = (����Ƶ�� / 300������)    //1L��Ҫ300�����壬����Ƶ��HZ
			*/
			golbal_flow.acculat += golbal_flow.pluse_1s / MODE_4_PLUSE_CNT_1L;   //��λL
				
			/*���㹫ʽ��
						˲ʱ���� = (����Ƶ�� / 300������) * 60s 
										 = ����Ƶ�� / 5.0(����ϵK)
			*/
			golbal_flow.instant = golbal_flow.pluse_1s / MODE_4_K;  //��λ��L/min��

        #else
      	/*���㹫ʽ��
				�ۼ����� = ��˲ʱ����������
								 = (����Ƶ�� / ÿ��ˮ������)
			*/
			golbal_flow.acculat += (golbal_flow.pluse_1s * 1000 / MODE_6_PLUSE_CNT_1L);   //��λmL
			pluse1L+=golbal_flow.pluse_1s;
			/*���㹫ʽ��
						˲ʱ���� = ((����Ƶ�� + 3) / 330������) * 60s 
										 = (����Ƶ�� + 3) / 5.5(����ϵK)
			*/
			golbal_flow.instant = golbal_flow.pluse_1s / MODE_6_K;  //��λ��L/min��

        #endif
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
		
		golbal_flow.receive_flag = 0;     			 //������ɱ�־λ����
	
        golbal_flow.pluse_1s = 0;
	}
}


