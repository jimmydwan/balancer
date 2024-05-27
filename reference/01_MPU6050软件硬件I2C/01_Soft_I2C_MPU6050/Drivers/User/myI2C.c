#include "stm32f1xx_hal.h"
#include "Dealy.h"

//PB6��PB7���ó���ͨ��©���ģʽ
#define SCL_PORT GPIOB
#define SDA_PORT GPIOB
#define SCL_PIN  GPIO_PIN_6
#define SDA_PIN  GPIO_PIN_7

/**
  * ��    ����I2CдSCL���ŵ�ƽ
  * ��    ����BitValue Э��㴫��ĵ�ǰ��Ҫд��SCL�ĵ�ƽ����Χ0~1
  * �� �� ֵ����
  * ע������˺�����Ҫ�û�ʵ�����ݣ���BitValueΪ0ʱ����Ҫ��SCLΪ�͵�ƽ����BitValueΪ1ʱ����Ҫ��SCLΪ�ߵ�ƽ
  */
void MyI2C_W_SCL(uint8_t BitValue)
{
	HAL_GPIO_WritePin(SCL_PORT, SCL_PIN, (GPIO_PinState)BitValue);		//����BitValue������SCL���ŵĵ�ƽ
	Delay_us(10);												//��ʱ10us����ֹʱ��Ƶ�ʳ���Ҫ��
}

/**
  * ��    ����I2CдSDA���ŵ�ƽ
  * ��    ����BitValue Э��㴫��ĵ�ǰ��Ҫд��SDA�ĵ�ƽ����Χ0~0xFF
  * �� �� ֵ����
  * ע������˺�����Ҫ�û�ʵ�����ݣ���BitValueΪ0ʱ����Ҫ��SDAΪ�͵�ƽ����BitValue��0ʱ����Ҫ��SDAΪ�ߵ�ƽ
  */
void MyI2C_W_SDA(uint8_t BitValue)
{
	HAL_GPIO_WritePin(SDA_PORT, SDA_PIN, (GPIO_PinState)BitValue);		//����BitValue������SDA���ŵĵ�ƽ��BitValueҪʵ�ַ�0��1������
	Delay_us(10);												//��ʱ10us����ֹʱ��Ƶ�ʳ���Ҫ��
}

/**
  * ��    ����I2C��SDA���ŵ�ƽ
  * ��    ������
  * �� �� ֵ��Э�����Ҫ�õ��ĵ�ǰSDA�ĵ�ƽ����Χ0~1
  * ע������˺�����Ҫ�û�ʵ�����ݣ���ǰSDAΪ�͵�ƽʱ������0����ǰSDAΪ�ߵ�ƽʱ������1
  */
GPIO_PinState MyI2C_R_SDA(void)
{
	GPIO_PinState BitValue;
	BitValue = HAL_GPIO_ReadPin(SDA_PORT, SDA_PIN);		//��ȡSDA��ƽ
	Delay_us(10);												//��ʱ10us����ֹʱ��Ƶ�ʳ���Ҫ��
	return BitValue;											//����SDA��ƽ
}


/*Э���*/

/**
  * ��    ����I2C��ʼ
  * ��    ������
  * �� �� ֵ����
  */
void MyI2C_Start(void)
{
	MyI2C_W_SDA(1);							//�ͷ�SDA��ȷ��SDAΪ�ߵ�ƽ
	MyI2C_W_SCL(1);							//�ͷ�SCL��ȷ��SCLΪ�ߵ�ƽ
	MyI2C_W_SDA(0);							//��SCL�ߵ�ƽ�ڼ䣬����SDA��������ʼ�ź�
	MyI2C_W_SCL(0);							//��ʼ���SCLҲ���ͣ���Ϊ��ռ�����ߣ�ҲΪ�˷�������ʱ���ƴ��
}

/**
  * ��    ����I2C��ֹ
  * ��    ������
  * �� �� ֵ����
  */
void MyI2C_Stop(void)
{
	MyI2C_W_SDA(0);							//����SDA��ȷ��SDAΪ�͵�ƽ
	MyI2C_W_SCL(1);							//�ͷ�SCL��ʹSCL���ָߵ�ƽ
	MyI2C_W_SDA(1);							//��SCL�ߵ�ƽ�ڼ䣬�ͷ�SDA��������ֹ�ź�
}

/**
  * ��    ����I2C����һ���ֽ�
  * ��    ����Byte Ҫ���͵�һ���ֽ����ݣ���Χ��0x00~0xFF
  * �� �� ֵ����
  */
void MyI2C_SendByte(uint8_t Byte)
{
	//��ʼ������SCLһ���ǵ͵�ƽ
	uint8_t i;
	for (i = 0; i < 8; i ++)				//ѭ��8�Σ��������η������ݵ�ÿһλ
	{
		MyI2C_W_SDA(Byte & (0x80 >> i));	//ʹ������ķ�ʽȡ��Byte��ָ��һλ���ݲ�д�뵽SDA��
		MyI2C_W_SCL(1);						//�ͷ�SCL���ӻ���SCL�ߵ�ƽ�ڼ��ȡSDA
		MyI2C_W_SCL(0);						//����SCL��������ʼ������һλ����
	}
}

/**
  * ��    ����I2C����һ���ֽ�
  * ��    ������
  * �� �� ֵ�����յ���һ���ֽ����ݣ���Χ��0x00~0xFF
  */
GPIO_PinState MyI2C_ReceiveByte(void)
{
	uint8_t i;
	GPIO_PinState Byte = (GPIO_PinState)0x00;					//������յ����ݣ�������ֵ0x00���˴����븳��ֵ0x00��������õ�
	MyI2C_W_SDA(1);							//����ǰ��������ȷ���ͷ�SDA��������Ŵӻ������ݷ���
	for (i = 0; i < 8; i ++)				//ѭ��8�Σ��������ν������ݵ�ÿһλ
	{
		MyI2C_W_SCL(1);						//�ͷ�SCL����������SCL�ߵ�ƽ�ڼ��ȡSDA
		if (MyI2C_R_SDA() == 1){Byte |= (0x80 >> i);}	//��ȡSDA���ݣ����洢��Byte����
														//��SDAΪ1ʱ���ñ���ָ��λΪ1����SDAΪ0ʱ����������ָ��λΪĬ�ϵĳ�ֵ0
		MyI2C_W_SCL(0);						//����SCL���ӻ���SCL�͵�ƽ�ڼ�д��SDA
	}
	return Byte;							//���ؽ��յ���һ���ֽ�����
}

/**
  * ��    ����I2C����Ӧ��λ
  * ��    ����Byte Ҫ���͵�Ӧ��λ����Χ��0~1��0��ʾӦ��1��ʾ��Ӧ��
  * �� �� ֵ����
  */
void MyI2C_SendAck(uint8_t AckBit)
{
	MyI2C_W_SDA(AckBit);					//������Ӧ��λ���ݷŵ�SDA��
	MyI2C_W_SCL(1);							//�ͷ�SCL���ӻ���SCL�ߵ�ƽ�ڼ䣬��ȡӦ��λ
	MyI2C_W_SCL(0);							//����SCL����ʼ��һ��ʱ��ģ��
}

/**
  * ��    ����I2C����Ӧ��λ
  * ��    ������
  * �� �� ֵ�����յ���Ӧ��λ����Χ��0~1��0��ʾӦ��1��ʾ��Ӧ��
  */
GPIO_PinState MyI2C_ReceiveAck(void)
{
	GPIO_PinState AckBit;							//����Ӧ��λ����
	MyI2C_W_SDA(1);							//����ǰ��������ȷ���ͷ�SDA��������Ŵӻ������ݷ���
	MyI2C_W_SCL(1);							//�ͷ�SCL����������SCL�ߵ�ƽ�ڼ��ȡSDA
	AckBit = MyI2C_R_SDA();					//��Ӧ��λ�洢��������
	MyI2C_W_SCL(0);							//����SCL����ʼ��һ��ʱ��ģ��
	return AckBit;							//���ض���Ӧ��λ����
}
