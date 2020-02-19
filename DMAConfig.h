DMA_InitTypeDef DMA_InitStructure;
ADC_InitTypeDef ADC_InitStructure;

uint16_t ADCBuffer[] = {0x0000, 0x0000, 0x0000, 0x0000 }; 

void DMAInit_SPI2Sending(uint16_t *data, uint16_t len)
{
		DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI2->DR;                 
		DMA_InitStructure.DMA_MemoryBaseAddr =(uint32_t)data;                      
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;                            
		DMA_InitStructure.DMA_BufferSize = len;                                          
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                         
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;                 
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;              
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord ;   
		DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                                   
		DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;                            
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                                    
		DMA_Init (DMA1_Channel5, &DMA_InitStructure);
		SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);
		DMA_Cmd(DMA1_Channel5, ENABLE);
	
		DMA_ITConfig(DMA1_Channel5, DMA_IT_TC, ENABLE);
		NVIC_EnableIRQ(DMA1_Channel5_IRQn);
}
	
void DMAInit_SPI1Recieve(uint16_t *data, uint16_t len)
{	
		DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI1->DR;                
		DMA_InitStructure.DMA_MemoryBaseAddr =(uint32_t)data;                     
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                              
		DMA_InitStructure.DMA_BufferSize = len;                                            
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                         
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;                 
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;              
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord ;   
		DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                                  
		DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;                           
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                                    
		DMA_Init (DMA1_Channel2, &DMA_InitStructure);	
		SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Rx, ENABLE);	
		DMA_Cmd(DMA1_Channel2, ENABLE);
	
		DMA_ITConfig(DMA1_Channel2, DMA_IT_TC, ENABLE);
		NVIC_EnableIRQ(DMA1_Channel2_IRQn);
}


void ADC1_Configure(void)
{
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;  // we work in continuous sampling mode
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
 
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_28Cycles5); // define regular conversion config
    ADC_Init ( ADC1, &ADC_InitStructure);   //set config of ADC1
 
    ADC_Cmd (ADC1,ENABLE);  //enable ADC1
 
    ADC_ResetCalibration(ADC1); // Reset previous calibration
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1); // Start new calibration (ADC must be off at that time)
    while(ADC_GetCalibrationStatus(ADC1));

		ADC_Cmd(ADC1 , ENABLE ) ;
    ADC_DMACmd(ADC1 , ENABLE );

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}


void DMAInit_ADCRecieve(void)
{
    DMA_InitStructure.DMA_BufferSize = 4;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADCBuffer;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);
    DMA_Cmd(DMA1_Channel1 , ENABLE ) ;
	
		ADC1_Configure();
}


