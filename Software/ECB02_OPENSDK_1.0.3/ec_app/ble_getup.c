#include "ble_getup.h"



//�����ڵ��ж�
void int_rising(void) //�������ж�
{
}
void int_falling(void) //�½����ж�
{
    motorB_change();
}
void int_falling2(void) //�½����ж�
{
    motorB_break();
		motorB_stop();
}


//����Ϊ���Ƶ���ĳ���
uint16_t cmp[5] = {100,300,500,700,900};
uint8_t flag = 0;
void motorA_init(void)
{
	ec_core_gpio_out_init(EC_CORE_GPIO_P1, EC_CORE_GPIO_LEVEL_L);  // GPIO1 ��ʼ�� ����͵�ƽ
	ec_core_gpio_out_init(EC_CORE_GPIO_P2, EC_CORE_GPIO_LEVEL_L);  // GPIO2 ��ʼ�� ����͵�ƽ
	ec_core_gpio_out_init(EC_CORE_GPIO_P3, EC_CORE_GPIO_LEVEL_L);  // GPIO3 ��ʼ�� ����͵�ƽ
}
void motorA_stop(void)//���Aͣת
{
	ec_core_gpio_write(EC_CORE_GPIO_P1, EC_CORE_GPIO_LEVEL_L);    //���������ƽ
	ec_core_gpio_write(EC_CORE_GPIO_P2, EC_CORE_GPIO_LEVEL_L);
	ec_core_gpio_write(EC_CORE_GPIO_P3, EC_CORE_GPIO_LEVEL_L);
}
void motorA_cw(uint16_t cmp)//���A��ת������Ϊռ�ձȴ�С
{
	ec_core_pwm_stop(EC_CORE_PWM_CH0);
	ec_core_pwm_start(EC_CORE_PWM_CLK_NO_DIV, EC_CORE_PWM_CH0, EC_CORE_GPIO_P3, cmp, 1000); // ռ�ձ�cmp/1000 Ƶ��=16Mhz/1000=16KHz
	ec_core_gpio_write(EC_CORE_GPIO_P1, EC_CORE_GPIO_LEVEL_H);  // GPIO1����ߵ�ƽ
	ec_core_gpio_write(EC_CORE_GPIO_P2, EC_CORE_GPIO_LEVEL_L);  // GPIO2����͵�ƽ
}
void motorA_break(void)
{
	ec_core_pwm_stop(EC_CORE_PWM_CH0);
	ec_core_gpio_write(EC_CORE_GPIO_P1, EC_CORE_GPIO_LEVEL_H);
	ec_core_gpio_write(EC_CORE_GPIO_P2, EC_CORE_GPIO_LEVEL_H);
}
void motorA_ccw(uint16_t cmp)//���A��ת������Ϊռ�ձȴ�С
{
	ec_core_pwm_stop(EC_CORE_PWM_CH0);
	ec_core_pwm_start(EC_CORE_PWM_CLK_NO_DIV, EC_CORE_PWM_CH0, EC_CORE_GPIO_P3, cmp, 1000); // ռ�ձ�cmp/1000 Ƶ��=16Mhz/1000=16KHz
	ec_core_gpio_write(EC_CORE_GPIO_P1, EC_CORE_GPIO_LEVEL_L);  // GPIO1����͵�ƽ
	ec_core_gpio_write(EC_CORE_GPIO_P2, EC_CORE_GPIO_LEVEL_H);  // GPIO2����ߵ�ƽ
}


void motorB_init(void)
{
	ec_core_gpio_out_init(EC_CORE_GPIO_P6, EC_CORE_GPIO_LEVEL_L);  // GPIO6 ��ʼ�� ����͵�ƽ
	ec_core_gpio_out_init(EC_CORE_GPIO_P7, EC_CORE_GPIO_LEVEL_L);  // GPIO7 ��ʼ�� ����͵�ƽ
	ec_core_gpio_out_init(EC_CORE_GPIO_P8, EC_CORE_GPIO_LEVEL_L);  // GPIO8 ��ʼ�� ����͵�ƽ
}
void motorB_stop(void)//���Bͣת
{
	ec_core_gpio_write(EC_CORE_GPIO_P6, EC_CORE_GPIO_LEVEL_L);    //���������ƽ
	ec_core_gpio_write(EC_CORE_GPIO_P7, EC_CORE_GPIO_LEVEL_L);
	ec_core_gpio_write(EC_CORE_GPIO_P8, EC_CORE_GPIO_LEVEL_L);
	flag=0;
}
void motorB_cw(uint16_t cmp)//���B��ת������Ϊռ�ձȴ�С
{
	ec_core_pwm_stop(EC_CORE_PWM_CH1);
	ec_core_pwm_start(EC_CORE_PWM_CLK_NO_DIV, EC_CORE_PWM_CH1, EC_CORE_GPIO_P8, cmp, 1000); // ռ�ձ�cmp/1000 Ƶ��=16Mhz/1000=16KHz
	ec_core_gpio_write(EC_CORE_GPIO_P6, EC_CORE_GPIO_LEVEL_H);  // GPIO1����ߵ�ƽ
	ec_core_gpio_write(EC_CORE_GPIO_P7, EC_CORE_GPIO_LEVEL_L);  // GPIO2����͵�ƽ
	flag=1;
}
void motorB_break(void)
{
	ec_core_pwm_stop(EC_CORE_PWM_CH1);
	ec_core_gpio_write(EC_CORE_GPIO_P6, EC_CORE_GPIO_LEVEL_H);
	ec_core_gpio_write(EC_CORE_GPIO_P7, EC_CORE_GPIO_LEVEL_H);
	flag=0;
}
void motorB_ccw(uint16_t cmp)//���B��ת������Ϊռ�ձȴ�С
{
	ec_core_pwm_stop(EC_CORE_PWM_CH1);
	ec_core_pwm_start(EC_CORE_PWM_CLK_NO_DIV, EC_CORE_PWM_CH1, EC_CORE_GPIO_P8, cmp, 1000); // ռ�ձ�cmp/1000 Ƶ��=16Mhz/1000=16KHz
	ec_core_gpio_write(EC_CORE_GPIO_P6, EC_CORE_GPIO_LEVEL_L);  // GPIO1����͵�ƽ
	ec_core_gpio_write(EC_CORE_GPIO_P7, EC_CORE_GPIO_LEVEL_H);  // GPIO2����ߵ�ƽ
	flag=2;
}
void motorB_change(void)
{
	if(flag==1)
		motorB_ccw(cmp[2]);
	else if(flag==2)
		motorB_cw(cmp[2]);
}




//����ģʽ
void find_target(void)//Ѱ���ҵ�ͷ,���GPIO10������Ϊ�ߵ�ƽ����˵��û��ͷ
{
	//ec_core_gpio_in_init(EC_CORE_GPIO_P10, EC_CORE_GPIO_PULL_UP_S);
	if(ec_core_gpio_read(EC_CORE_GPIO_P10)==EC_CORE_GPIO_LEVEL_L)
		motorB_stop();
	else if(ec_core_gpio_read(EC_CORE_GPIO_P10)==EC_CORE_GPIO_LEVEL_H)
	{
		ec_core_gpio_int_register(EC_CORE_GPIO_P10, int_rising, int_falling2); // GPIO3 �ж�ʹ��
		motorB_ccw(cmp[0]);
	}
}

//�������������������ʱ��ʵ���𴲴��˳��������ٴ��򵽿��ٴ������ӵ�λ
void sw_timer1_int2(void) //�����ʱ��1�ж�
{
	ec_core_sw_timer_stop(EC_CORE_SW_TIMER1);
	motorA_ccw(cmp[4]);
}
void sw_timer1_int(void) //�����ʱ��1�ж�
{
	motorA_ccw(cmp[2]);
	ec_core_sw_timer_start(EC_CORE_SW_TIMER1, 10000, sw_timer1_int2);
    // ec_core_uart0_printf("sw_timer1_int\r\n");
}
void get_up_now(void)
{
	motorA_ccw(cmp[0]);
	ec_core_sw_timer_start(EC_CORE_SW_TIMER1, 10000, sw_timer1_int); //�����ʱ��
	find_target();
}



//ң��ģʽ





//����ģʽ
void hammer(void)
{
	
	motorA_ccw(cmp[2]);
	ec_core_gpio_int_register(EC_CORE_GPIO_P9, int_rising, int_falling);
}



//���ֻ��ٿ��л�ģʽʱ����һ�й��㣬��ֹ���ֱ��綨ʱ�����ڼ�ʱ������
void to_begin(void)
{
	ec_core_sw_timer_stop(EC_CORE_SW_TIMER1);
	motorA_stop();
	motorB_stop();
	ec_core_pwm_stop(EC_CORE_PWM_CH0);
	ec_core_pwm_stop(EC_CORE_PWM_CH1);
}






//�ַ���ת���Σ�stm32��֧�ֱ�׼��atoi,�����Լ�ʵ��
uint16_t myatoi(uint8_t chr)
{
	uint16_t s=0;
	s=chr-'0';
	return s;
}


//pow()ƽ������
uint32_t pow(uint16_t base,uint16_t exponent)
{
   uint32_t result = 1;
   while (exponent != 0)
   {
       result *= base;
       --exponent;
   }
    return result;
}


//�������ӵ���ʱ��ʱʱ�䣨�������յ��ַ�����תΪ��ֵ��
uint32_t delayTimes(uint8_t *data)
{
		uint32_t delayTimes = 0;
		int i = 1;
		int count = 0;
		while(data[i]!='\n')
		{
			count++;
		}
		for(i;i<=count;i++)
		{
			delayTimes+=myatoi(data[i])*pow(10,(count-i+1));
		}
		char* B=(char*)delayTimes;//��ֵת�ַ�����
		ec_core_uart0_printf(B);
}
