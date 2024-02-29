#include "YFS401.h"
#include "tim.h"

GOLBAL_FLOW golbal_flow;

#define MODE_4_K            5.0f        //流量系K
#define MODE_4_PLUSE_CNT_1L 300.0f      //每升水脉冲数
//#define MODE_6_K            5.5f
//#define MODE_6_PLUSE_CNT_1L 330.0f

#define MODE_6_K            750.0f
#define MODE_6_PLUSE_CNT_1L 45000.0f

#define	FLOW_FULL			1000000

uint8_t Flow_Model = 0;     //4分管定义为1；6分管定义为0

uint32_t pluse1L;
//==============================================================================
// @函数: Flow_Read(void)
// @描述: 读取流量
// @参数: None
// @返回: None
// @时间: 2024.2.26
//==============================================================================
void Flow_Read(void)
{
	if(golbal_flow.receive_flag)
	{
		if(golbal_flow.pluse_1s > 0)
		{
        #ifdef Flow_Model
			/*计算公式：
				累计流量 = 对瞬时流量做积分
								 = (脉冲频率 / 300个脉冲)    //1L需要300个脉冲，脉冲频率HZ
			*/
			golbal_flow.acculat += golbal_flow.pluse_1s / MODE_4_PLUSE_CNT_1L;   //单位L
				
			/*计算公式：
						瞬时流量 = (脉冲频率 / 300个脉冲) * 60s 
										 = 脉冲频率 / 5.0(流量系K)
			*/
			golbal_flow.instant = golbal_flow.pluse_1s / MODE_4_K;  //单位（L/min）

        #else
      	/*计算公式：
				累计流量 = 对瞬时流量做积分
								 = (脉冲频率 / 每升水脉冲数)
			*/
			golbal_flow.acculat += (golbal_flow.pluse_1s * 1000 / MODE_6_PLUSE_CNT_1L);   //单位mL
			pluse1L+=golbal_flow.pluse_1s;
			/*计算公式：
						瞬时流量 = ((脉冲频率 + 3) / 330个脉冲) * 60s 
										 = (脉冲频率 + 3) / 5.5(流量系K)
			*/
			golbal_flow.instant = golbal_flow.pluse_1s / MODE_6_K;  //单位（L/min）

        #endif
      if(golbal_flow.acculat >= 1000000)        //最大累计流量1000L
			{
				golbal_flow.acculat = 0;
			}
		}
		else
		{
			golbal_flow.instant  = 0;
		}
		
		printf("瞬间流量：%.2f（L/min） 累计流量：%.2f mL   脉冲数：%d \n",golbal_flow.instant,golbal_flow.acculat,golbal_flow.pluse_1s);
		
		golbal_flow.receive_flag = 0;     			 //接收完成标志位清零
	
        golbal_flow.pluse_1s = 0;
	}
}


