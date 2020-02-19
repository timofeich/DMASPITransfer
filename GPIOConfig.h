GPIO_InitTypeDef GPIO_InitStructure;

void SetLEDsPins(void)
{
	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_9 | GPIO_Pin_8);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC , &GPIO_InitStructure);
}
