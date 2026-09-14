#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructA;
	GPIO_InitStructA.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructA.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructA.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructA);

	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);

	OLED_Init();
	OLED_ShowString(1, 1, "Light:OFF  ");
	OLED_ShowString(2, 1, "Status:READY");

	uint8_t last_state = 0;
	while (1)
	{
		uint8_t level = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
		if (level != last_state)
		{
			if (level == 1)
			{
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				Delay_ms(80);
				GPIO_ResetBits(GPIOB, GPIO_Pin_0);
				Delay_ms(20);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				OLED_ShowString(1, 1, "Light:ON   ");
			}
			else
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_0);
				OLED_ShowString(1, 1, "Light:OFF  ");
			}
			GPIO_ResetBits(GPIOB, GPIO_Pin_12);
			Delay_ms(150);
			GPIO_SetBits(GPIOB, GPIO_Pin_12);
			last_state = level;
		}
		Delay_ms(100);
	}
}
