#include "led.h"

u16 R_cnt = 0;
u16 G_cnt = 0;
u16 B_cnt = 0;

void LED_Init(void)
{ 
	gpio_init_type gpio_init_struct;
  crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
	gpio_default_para_init(&gpio_init_struct);

  /* configure the led gpio */
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
  gpio_init_struct.gpio_pins = GPIO_PINS_13|GPIO_PINS_14|GPIO_PINS_15;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init(GPIOC, &gpio_init_struct);
	gpio_bits_set(GPIOC,GPIO_PINS_13|GPIO_PINS_14|GPIO_PINS_15);
}
 
void R_LED(u8 data)
{
	if(data == 0)//�����
	{
		RED_1;
		R_cnt = 0;
	}
	else if(data == 1)//��Ƴ���
	{
		RED_0;
		R_cnt = 0;
	}
	else if(data == 2)//��ƿ���
	{
		if(R_cnt < 100)
		{
			RED_0;
		}
		else if(R_cnt == 100)
		{
			RED_1;
		}
		else if(R_cnt >= 200)
		{
			R_cnt = 0;
		}
	}
	else if(data == 3)//��Ƶ���
	{
		if(R_cnt < 100)
		{
			RED_0;
		}
		else if(R_cnt == 100)
		{
			RED_1;
		}
		else if(R_cnt >= 1300)
		{
			R_cnt = 0;
		}
	}
	else if(data == 4)//���˫��
	{
		if(R_cnt < 100)
		{
			RED_0;
		}
		else if(R_cnt == 100)
		{
			RED_1;
		}
		else if(R_cnt == 200)
		{
			RED_0;
		}
		else if(R_cnt == 300)
		{
			RED_1;
		}
		else if(R_cnt >= 1500)
		{
			R_cnt = 0;
		}
	}
	else if(data == 5)//�������
	{
		if(R_cnt < 100)
		{
			RED_0;
		}
		else if(R_cnt == 100)
		{
			RED_1;
		}
		else if(R_cnt == 200)
		{
			RED_0;
		}
		else if(R_cnt == 300)
		{
			RED_1;
		}	
		else if(R_cnt == 400)
		{
			RED_0;
		}
		else if(R_cnt == 500)
		{
			RED_1;
		}
		
		else if(R_cnt >= 1500)
		{
			R_cnt = 0;
		}
	}
	
	R_cnt++;
}

void G_LED(u8 data)
{
	if(data == 0)//�����
	{
		GREEN_1;
		G_cnt = 0;
	}
	else if(data == 1)//��Ƴ���
	{
		GREEN_0;
		G_cnt = 0;
	}
	else if(data == 2)//��ƿ���
	{
		if(G_cnt < 100)
		{
			GREEN_0;
		}
		else if(G_cnt == 100)
		{
			GREEN_1;
		}
		else if(G_cnt >= 200)
		{
			G_cnt = 0;
		}
	}
	else if(data == 3)//��Ƶ���
	{
		if(G_cnt < 100)
		{
			GREEN_0;
		}
		else if(G_cnt == 100)
		{
			GREEN_1;
		}
		else if(G_cnt >= 1500)
		{
			G_cnt = 0;
		}
	}
	else if(data == 4)//���˫��
	{
		if(G_cnt < 100)
		{
			GREEN_0;
		}
		else if(G_cnt == 100)
		{
			GREEN_1;
		}
		else if(G_cnt == 200)
		{
			GREEN_0;
		}
		else if(G_cnt == 300)
		{
			GREEN_1;
		}
		else if(G_cnt >= 1500)
		{
			G_cnt = 0;
		}
	}
	else if(data == 5)//�������
	{
		if(G_cnt < 100)
		{
			GREEN_0;
		}
		else if(G_cnt == 100)
		{
			GREEN_1;
		}
		else if(G_cnt == 200)
		{
			GREEN_0;
		}
		else if(G_cnt == 300)
		{
			GREEN_1;
		}
		
		else if(G_cnt == 400)
		{
			GREEN_0;
		}
		else if(G_cnt == 500)
		{
			GREEN_1;
		}
		
		else if(G_cnt >= 1500)
		{
			G_cnt = 0;
		}
	}
	
	G_cnt++;
}

void B_LED(u8 data)
{
	if(data == 0)//�����
	{
		BLUE_1;
		B_cnt = 0;
	}
	else if(data == 1)//��Ƴ���
	{
		BLUE_0;
		B_cnt = 0;
	}
	else if(data == 2)//��ƿ���
	{
		if(B_cnt < 100)
		{
			BLUE_0;
		}
		else if(B_cnt == 100)
		{
			BLUE_1;
		}
		else if(B_cnt >= 200)
		{
			B_cnt = 0;
		}
	}
	else if(data == 3)//��Ƶ���
	{
		if(B_cnt < 100)
		{
			BLUE_0;
		}
		else if(B_cnt == 100)
		{
			BLUE_1;
		}
		else if(B_cnt >= 1500)
		{
			B_cnt = 0;
		}
	}
	else if(data == 4)//���˫��
	{
		if(B_cnt < 100)
		{
			BLUE_0;
		}
		else if(B_cnt == 100)
		{
			BLUE_1;
		}
		else if(B_cnt == 200)
		{
			BLUE_0;
		}
		else if(B_cnt == 300)
		{
			BLUE_1;
		}
		else if(B_cnt >= 1500)
		{
			B_cnt = 0;
		}
	}
	else if(data == 5)//�������
	{
		if(B_cnt < 100)
		{
			BLUE_0;
		}
		else if(B_cnt == 100)
		{
			BLUE_1;
		}
		else if(B_cnt == 200)
		{
			BLUE_0;
		}
		else if(B_cnt == 300)
		{
			BLUE_1;
		}
		
		else if(B_cnt == 400)
		{
			BLUE_0;
		}
		else if(B_cnt == 500)
		{
			BLUE_1;
		}
		
		else if(B_cnt >= 1500)
		{
			B_cnt = 0;
		}
	}
	
	B_cnt++;
}
