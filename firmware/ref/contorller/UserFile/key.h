#ifndef __KEY_H
#define __KEY_H	 
#include "app.h" 

#define Key1 		gpio_input_data_bit_read(GPIOD,GPIO_PINS_11)

extern u8 KeyFlag;

void Key_Init(void);	//IO��ʼ��
void Key_Scan(void);  		//����ɨ�躯��					    
#endif
