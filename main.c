#include "stm32f10x.h" 
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_adc.h"
#include "SPIConfig.h"
#include "GPIOConfig.h"
#include "DMAConfig.h"
#include <string.h>
		
//uint16_t data[4];
uint16_t receiveData[4];
//uint16_t result;

void delay(void) 
{
 volatile uint32_t i;
 for (i=1; i != 0x1FFFF; i++);
}

void ConfigurePeriphClock(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
}

//void SetValuesForData(void)
//{
//	for(int i=0; i < sizeof(data); i++)
//  {
//    data[i] = i + 1;
//  }
//}

int GetAverageValue(uint16_t *data)
{
	int sumOfArrayElements = 0;
	
	for(int i = 0; i < 4; i++)
	{
		sumOfArrayElements += data[i];
	}
	 return sumOfArrayElements/4;
}

int main(void) 
{  
	uint16_t x = 0x0500;
	uint16_t y = 0x0600;
	
 	ConfigurePeriphClock(); 
	SetLEDsPins();
	
	DMAInit_ADCRecieve();
	ConfigureSPI2AsMaster();		
	ConfigureSPI1AsSlave();

	while(1)
	{  	
		DMAInit_SPI2Sending(ADCBuffer, sizeof(ADCBuffer));

		DMAInit_SPI1Recieve(receiveData, sizeof(receiveData));
		
		if(SPI1->SR &= SPI_SR_CRCERR)
		{
				uint16_t result = GetAverageValue(receiveData);
				if(result > x && result < y)
				{
					GPIOC->ODR ^= (GPIO_Pin_9);
				}
				else 
				{
					GPIO_ResetBits(GPIOC, GPIO_Pin_9);
				}	
		}
		
		SPI_I2S_SendData(SPI2, 0x90);

		
			if(SPI_I2S_ReceiveData(SPI1) == 0x90)
			{
				GPIOC->ODR ^= (GPIO_Pin_8 | GPIO_Pin_9);	
			}

	}
}
	
void DMA1_Channel5_IRQHandler(void)
{
	DMA_ClearITPendingBit(DMA1_IT_TC5);

	DMA_Cmd(DMA1_Channel5, DISABLE);
}

void DMA1_Channel2_IRQHandler(void)
{
	DMA_ClearITPendingBit(DMA1_IT_TC2);

	DMA_Cmd(DMA1_Channel2, DISABLE);
}


