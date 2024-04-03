#include "app.h"

//#define SlaveAddress 0x1e  //����������IIC�����еĴӵ�ַ
#define SlaveAddress 0x3c  //����������IIC�����еĴӵ�ַ
u8 hmc5883_data[6];
s16 hmc5883_xyz[3];

/*���ֽ�дHMC5833*/
void Single_Write_HMC5883(unsigned char Address,unsigned char Dat)
{
	IIC_Start();
	IIC_Send_Byte(SlaveAddress);
	IIC_Wait_Ack();	

	IIC_Send_Byte(Address);
	IIC_Wait_Ack();	

	IIC_Send_Byte(Dat);
	IIC_Wait_Ack();	

	IIC_Stop();
}

float CpsAngle;
float Kx = 0.0f,Ky = 0.0f;
float Gax,Gay,Gaz,GaxMax,GaxMin,GayMax,GayMin;
float OffestX,OffestY;
float HMC5883_X,HMC5883_Y;
u8 Cali_Flag = 0;
float FilterX,FilterY;
float hmc5883_xy[2];

/*���ֽڶ�HMC5833*/
void Multiple_Read_HMC5883(void)
{
	unsigned char i;  //��������HMC5883�ڲ��Ƕ����ݣ���ַ��Χ0x3~0x5
	IIC_Start();
	IIC_Send_Byte(SlaveAddress);
  IIC_Wait_Ack();	
	IIC_Send_Byte(0x03);//���ʹ洢��Ԫ��ַ����0x03��ʼ 
	IIC_Wait_Ack();	
	IIC_Start();
	IIC_Send_Byte(SlaveAddress+1);
	IIC_Wait_Ack();	
	for(i=0;i<6;i++) //������ȡ6����ַ���ݣ��洢��Rec_Data
	{
			
			if(i==5)
					hmc5883_data[i]=IIC_Read_Byte(0);
			else
					hmc5883_data[i]=IIC_Read_Byte(1);
	}
	IIC_Stop();
//	delay_us(1);
	
	hmc5883_xyz[0]=hmc5883_data[0]<<8 | hmc5883_data[1];//Combine MSB and LSB of X Data output register
	hmc5883_xyz[2]=hmc5883_data[2]<<8 | hmc5883_data[3];//Combine MSB and LSB of Z Data output register
	hmc5883_xyz[1]=hmc5883_data[4]<<8 | hmc5883_data[5];//Combine MSB and LSB of Y Data output register 
	
	hmc5883_xy[0] = (float)hmc5883_xyz[0];
	hmc5883_xy[1] = (float)hmc5883_xyz[1];
	
	FilterX += (hmc5883_xy[0] - FilterX) * 0.01f;
	FilterY += (hmc5883_xy[1] - FilterY) * 0.01f;
	
//	if(Cali_Flag == 1)
//	{
//		
//		
//		if(FilterX > GaxMax)
//		{
//			GaxMax = FilterX;
//		}
//		else if(FilterX < GaxMin)
//		{
//			GaxMin = FilterX;
//		}
//		
//		if(FilterY > GayMax)
//		{
//			GayMax = FilterY;
//		}
//		else if(FilterY < GayMin)
//		{
//			GayMin = FilterY;
//		}
//		
//		OffestX = (GaxMax+GaxMin)/2.0f;
//		OffestY = (GayMax+GayMin)/2.0f;
//		
//		Kx = (GaxMax-GaxMin)/2.0f;
//		Ky = (GayMax-GayMin)/2.0f;
//	}
//	else if(Cali_Flag == 2)
//	{		
//		HMC5883_X = (FilterX-OffestX)/Kx;
//		HMC5883_Y = (FilterY-OffestY)/Ky;
//		
//		CpsAngle = atan2(HMC5883_Y,HMC5883_X) * 57.2957795f + 180.0f;
		CpsAngle = atan2(FilterX,FilterY) * 57.2957795f + 180.0f;
//	}
}

//��ʼ��HMC5883��������Ҫ��ο�pdf�����޸�****
void HMC5883_Init(void)
{
     Single_Write_HMC5883(0x02,0x00); 
}

uint8_t temphigh, templow;

void read_temperature(void)
{
	IIC_Start();
	IIC_Send_Byte(0x9f);
	IIC_Wait_Ack();
	hmc5883_xyz[0] = IIC_Read_Byte(1);
	hmc5883_xyz[1] = IIC_Read_Byte(0);
	IIC_Stop();
}
























