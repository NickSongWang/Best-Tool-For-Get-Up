#include "ble_getup.h"



//红外遮挡中断
void int_rising(void) //上升沿中断
{
}
void int_falling(void) //下降沿中断
{
    motorB_change();
}
void int_falling2(void) //下降沿中断
{
    motorB_break();
		motorB_stop();
}


//下面为控制电机的程序
uint16_t cmp[5] = {100,300,500,700,900};
uint8_t flag = 0;
void motorA_init(void)
{
	ec_core_gpio_out_init(EC_CORE_GPIO_P1, EC_CORE_GPIO_LEVEL_L);  // GPIO1 初始化 输出低电平
	ec_core_gpio_out_init(EC_CORE_GPIO_P2, EC_CORE_GPIO_LEVEL_L);  // GPIO2 初始化 输出低电平
	ec_core_gpio_out_init(EC_CORE_GPIO_P3, EC_CORE_GPIO_LEVEL_L);  // GPIO3 初始化 输出低电平
}
void motorA_stop(void)//电机A停转
{
	ec_core_gpio_write(EC_CORE_GPIO_P1, EC_CORE_GPIO_LEVEL_L);    //设置输出电平
	ec_core_gpio_write(EC_CORE_GPIO_P2, EC_CORE_GPIO_LEVEL_L);
	ec_core_gpio_write(EC_CORE_GPIO_P3, EC_CORE_GPIO_LEVEL_L);
}
void motorA_cw(uint16_t cmp)//电机A正转，输入为占空比大小
{
	ec_core_pwm_stop(EC_CORE_PWM_CH0);
	ec_core_pwm_start(EC_CORE_PWM_CLK_NO_DIV, EC_CORE_PWM_CH0, EC_CORE_GPIO_P3, cmp, 1000); // 占空比cmp/1000 频率=16Mhz/1000=16KHz
	ec_core_gpio_write(EC_CORE_GPIO_P1, EC_CORE_GPIO_LEVEL_H);  // GPIO1输出高电平
	ec_core_gpio_write(EC_CORE_GPIO_P2, EC_CORE_GPIO_LEVEL_L);  // GPIO2输出低电平
}
void motorA_break(void)
{
	ec_core_pwm_stop(EC_CORE_PWM_CH0);
	ec_core_gpio_write(EC_CORE_GPIO_P1, EC_CORE_GPIO_LEVEL_H);
	ec_core_gpio_write(EC_CORE_GPIO_P2, EC_CORE_GPIO_LEVEL_H);
}
void motorA_ccw(uint16_t cmp)//电机A反转，输入为占空比大小
{
	ec_core_pwm_stop(EC_CORE_PWM_CH0);
	ec_core_pwm_start(EC_CORE_PWM_CLK_NO_DIV, EC_CORE_PWM_CH0, EC_CORE_GPIO_P3, cmp, 1000); // 占空比cmp/1000 频率=16Mhz/1000=16KHz
	ec_core_gpio_write(EC_CORE_GPIO_P1, EC_CORE_GPIO_LEVEL_L);  // GPIO1输出低电平
	ec_core_gpio_write(EC_CORE_GPIO_P2, EC_CORE_GPIO_LEVEL_H);  // GPIO2输出高电平
}


void motorB_init(void)
{
	ec_core_gpio_out_init(EC_CORE_GPIO_P6, EC_CORE_GPIO_LEVEL_L);  // GPIO6 初始化 输出低电平
	ec_core_gpio_out_init(EC_CORE_GPIO_P7, EC_CORE_GPIO_LEVEL_L);  // GPIO7 初始化 输出低电平
	ec_core_gpio_out_init(EC_CORE_GPIO_P8, EC_CORE_GPIO_LEVEL_L);  // GPIO8 初始化 输出低电平
}
void motorB_stop(void)//电机B停转
{
	ec_core_gpio_write(EC_CORE_GPIO_P6, EC_CORE_GPIO_LEVEL_L);    //设置输出电平
	ec_core_gpio_write(EC_CORE_GPIO_P7, EC_CORE_GPIO_LEVEL_L);
	ec_core_gpio_write(EC_CORE_GPIO_P8, EC_CORE_GPIO_LEVEL_L);
	flag=0;
}
void motorB_cw(uint16_t cmp)//电机B正转，输入为占空比大小
{
	ec_core_pwm_stop(EC_CORE_PWM_CH1);
	ec_core_pwm_start(EC_CORE_PWM_CLK_NO_DIV, EC_CORE_PWM_CH1, EC_CORE_GPIO_P8, cmp, 1000); // 占空比cmp/1000 频率=16Mhz/1000=16KHz
	ec_core_gpio_write(EC_CORE_GPIO_P6, EC_CORE_GPIO_LEVEL_H);  // GPIO1输出高电平
	ec_core_gpio_write(EC_CORE_GPIO_P7, EC_CORE_GPIO_LEVEL_L);  // GPIO2输出低电平
	flag=1;
}
void motorB_break(void)
{
	ec_core_pwm_stop(EC_CORE_PWM_CH1);
	ec_core_gpio_write(EC_CORE_GPIO_P6, EC_CORE_GPIO_LEVEL_H);
	ec_core_gpio_write(EC_CORE_GPIO_P7, EC_CORE_GPIO_LEVEL_H);
	flag=0;
}
void motorB_ccw(uint16_t cmp)//电机B反转，输入为占空比大小
{
	ec_core_pwm_stop(EC_CORE_PWM_CH1);
	ec_core_pwm_start(EC_CORE_PWM_CLK_NO_DIV, EC_CORE_PWM_CH1, EC_CORE_GPIO_P8, cmp, 1000); // 占空比cmp/1000 频率=16Mhz/1000=16KHz
	ec_core_gpio_write(EC_CORE_GPIO_P6, EC_CORE_GPIO_LEVEL_L);  // GPIO1输出低电平
	ec_core_gpio_write(EC_CORE_GPIO_P7, EC_CORE_GPIO_LEVEL_H);  // GPIO2输出高电平
	flag=2;
}
void motorB_change(void)
{
	if(flag==1)
		motorB_ccw(cmp[2]);
	else if(flag==2)
		motorB_cw(cmp[2]);
}




//闹钟模式
void find_target(void)//寻找我的头,如果GPIO10的输入为高电平，则说明没有头
{
	//ec_core_gpio_in_init(EC_CORE_GPIO_P10, EC_CORE_GPIO_PULL_UP_S);
	if(ec_core_gpio_read(EC_CORE_GPIO_P10)==EC_CORE_GPIO_LEVEL_L)
		motorB_stop();
	else if(ec_core_gpio_read(EC_CORE_GPIO_P10)==EC_CORE_GPIO_LEVEL_H)
	{
		ec_core_gpio_int_register(EC_CORE_GPIO_P10, int_rising, int_falling2); // GPIO3 中断使能
		motorB_ccw(cmp[0]);
	}
}

//下面三个是利用软件定时器实现起床锤人程序由慢速捶打到快速捶打增加挡位
void sw_timer1_int2(void) //软件定时器1中断
{
	ec_core_sw_timer_stop(EC_CORE_SW_TIMER1);
	motorA_ccw(cmp[4]);
}
void sw_timer1_int(void) //软件定时器1中断
{
	motorA_ccw(cmp[2]);
	ec_core_sw_timer_start(EC_CORE_SW_TIMER1, 10000, sw_timer1_int2);
    // ec_core_uart0_printf("sw_timer1_int\r\n");
}
void get_up_now(void)
{
	motorA_ccw(cmp[0]);
	ec_core_sw_timer_start(EC_CORE_SW_TIMER1, 10000, sw_timer1_int); //软件定时器
	find_target();
}



//遥控模式





//锤人模式
void hammer(void)
{
	
	motorA_ccw(cmp[2]);
	ec_core_gpio_int_register(EC_CORE_GPIO_P9, int_rising, int_falling);
}



//当手机操控切换模式时，把一切归零，防止出现比如定时器还在计时的问题
void to_begin(void)
{
	ec_core_sw_timer_stop(EC_CORE_SW_TIMER1);
	motorA_stop();
	motorB_stop();
	ec_core_pwm_stop(EC_CORE_PWM_CH0);
	ec_core_pwm_stop(EC_CORE_PWM_CH1);
}






//字符串转整形，stm32不支持标准的atoi,这里自己实现
uint16_t myatoi(uint8_t chr)
{
	uint16_t s=0;
	s=chr-'0';
	return s;
}


//pow()平方运算
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


//设置闹钟倒计时定时时间（蓝牙接收到字符串，转为数值）
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
		char* B=(char*)delayTimes;//数值转字符串；
		ec_core_uart0_printf(B);
}
