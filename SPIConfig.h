GPIO_InitTypeDef GPIO_InitStructure;
SPI_InitTypeDef SPI_InitStructure;

void SetPinsForSPI1(void)
{
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}


void SetPinsForSPI2(void)
{
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void ConfigureSPI1AsSlave(void)
{
	SetPinsForSPI1();
	
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; 
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; 
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 
  SPI_InitStructure.SPI_Mode = SPI_Mode_Slave; 
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	
	SPI_Init(SPI1, &SPI_InitStructure); 
  SPI_Cmd(SPI1, ENABLE); 
	SPI_CalculateCRC(SPI1, ENABLE);
}
	

void ConfigureSPI2AsMaster(void)
{
	SetPinsForSPI2();
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32; 
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master; 
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	
  SPI_Init(SPI2, &SPI_InitStructure); 
  SPI_Cmd(SPI2, ENABLE);
	SPI_CalculateCRC(SPI2, ENABLE);	
}
