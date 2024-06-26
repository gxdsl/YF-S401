#include "YFS401.h"

GOLBAL_FLOW golbal_flow;

// 定义流量模型的枚举类型
typedef enum {
    MODE_4_PIPE = 0,   // 四分管
    MODE_6_PIPE = 1,   // 六分管
    MODE_6MM_PIPE = 2  // 6mm管
} FlowModel;

// 定义流量参数
float flowK[3] = {5.0f, 5.5f, 80.0f};                  // 流量系数 K
float pulseCntPerLiter[3] = {300.0f, 330.0f, 4800.0f}; // 每升水脉冲数

// 定义 Flow_Model
FlowModel flowModel = MODE_6MM_PIPE; // 默认使用6mm管


uint32_t pluse1L;           //测试1L水的脉冲数

//==============================================================================
// @函数: Flow_Read(void)
// @描述: 读取流量
// @参数: None
// @返回: None
// @时间: 2024.2.26
//==============================================================================
void Flow_Read(void)
{
    // 根据 Flow_Model 选择不同的流量参数
    float flowKValue = flowK[flowModel];
    float pulseCntValue = pulseCntPerLiter[flowModel];
    
	if(golbal_flow.pluse_1s > 0)
	{
		golbal_flow.acculat += (golbal_flow.pluse_1s * 1000 / pulseCntValue);   //单位mL
		pluse1L+=golbal_flow.pluse_1s;
		golbal_flow.instant = golbal_flow.pluse_1s / flowKValue;  //单位（L/min）

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
   
	golbal_flow.receive_flag = 0;   //接收完成标志位清零
    golbal_flow.pluse_1s = 0;       //脉冲数清零
}




