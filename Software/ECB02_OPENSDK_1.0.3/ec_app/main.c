/******************************************************************************
 *  Copyright © 2019 Shenzhen ECIOT Technology Co., Ltd All Rights Reserved
 *-----------------------------------------------------------------------------
 * @file        main.c
 * @brief       app demo
 * @author      mo@eciot.cn (qq:2201920828,v:eciot_mo)
 * @date        2022-02-13
 * @version     1.0
 ******************************************************************************/

#include "main.h"

#ifdef EC_APP_MAIN

#include "ec_core.h"
#include "ec_app_flash.h"
#include "ec_app_ble_peripheral.h"
#include "ec_app_ble.h"
#include "ble_getup.h"

#define EC_APP_UART0_TX_BUF_SIZE 1024                 //串口0发送缓冲区大小，可以根据需要调整
#define EC_APP_UART0_RX_BUF_SIZE 1024                 //串口0接收缓冲区大小，可以根据需要调整
uint8_t uart0_tx_buf[EC_APP_UART0_TX_BUF_SIZE] = {0}; //串口0发送缓冲区
uint8_t uart0_rx_buf[EC_APP_UART0_RX_BUF_SIZE] = {0}; //串口0接收缓冲区

void uart0_rx(uint8_t *buf, uint16_t len)
{
	ec_core_uart_send(EC_CORE_UART0, buf, len); // ECHO 回显
//	ec_core_ble_send(buf, len); //串口数据转发到蓝牙 (当利用电脑串口发送数据，可以在手机上接收到数据)

//    if (strcmp((const char *)buf, "DISC") == 0)
//        ec_core_ble_disconnect(); //主动断开蓝牙连接
//		else if ((buf[0] == 'A') && (buf[1] == 'T'))
//    {
//        // The AT command is not supported.
//        ec_core_uart0_printf("The AT command is not supported.\r\n");
//    }
}
void uart0_init(void)	//串口0初始化 波特率精度受时钟频率影响
{
    ec_core_uart_init(EC_CORE_UART0, 115200, EC_CORE_UART_PARITY_NONE,
                      EC_CORE_GPIO_P4, EC_CORE_GPIO_P5,
                      uart0_tx_buf, EC_APP_UART0_TX_BUF_SIZE, uart0_rx_buf, EC_APP_UART0_RX_BUF_SIZE,
                      uart0_rx);
}

////红外遮挡中断
//void int_rising(void) //上升沿中断
//{
//}
//void int_falling(void) //下降沿中断
//{
//    motorB_change();
//}
//void int_falling2(void) //下降沿中断
//{
//    motorB_break();
//		motorB_stop();
//}


////下面为控制电机的程序
//uint16_t cmp[5] = {100,300,500,700,900};
//uint8_t flag = 0;
//void motorA_init(void)
//{
//	ec_core_gpio_out_init(EC_CORE_GPIO_P1, EC_CORE_GPIO_LEVEL_L);  // GPIO1 初始化 输出低电平
//	ec_core_gpio_out_init(EC_CORE_GPIO_P2, EC_CORE_GPIO_LEVEL_L);  // GPIO2 初始化 输出低电平
//	ec_core_gpio_out_init(EC_CORE_GPIO_P3, EC_CORE_GPIO_LEVEL_L);  // GPIO3 初始化 输出低电平
//}
//void motorA_stop(void)//电机A停转
//{
//	ec_core_gpio_write(EC_CORE_GPIO_P1, EC_CORE_GPIO_LEVEL_L);    //设置输出电平
//	ec_core_gpio_write(EC_CORE_GPIO_P2, EC_CORE_GPIO_LEVEL_L);
//	ec_core_gpio_write(EC_CORE_GPIO_P3, EC_CORE_GPIO_LEVEL_L);
//}
//void motorA_cw(uint16_t cmp)//电机A正转，输入为占空比大小
//{
//	ec_core_pwm_stop(EC_CORE_PWM_CH0);
//	ec_core_pwm_start(EC_CORE_PWM_CLK_NO_DIV, EC_CORE_PWM_CH0, EC_CORE_GPIO_P3, cmp, 1000); // 占空比cmp/1000 频率=16Mhz/1000=16KHz
//	ec_core_gpio_write(EC_CORE_GPIO_P1, EC_CORE_GPIO_LEVEL_H);  // GPIO1输出高电平
//	ec_core_gpio_write(EC_CORE_GPIO_P2, EC_CORE_GPIO_LEVEL_L);  // GPIO2输出低电平
//}
//void motorA_break(void)
//{
//	ec_core_pwm_stop(EC_CORE_PWM_CH0);
//	ec_core_gpio_write(EC_CORE_GPIO_P1, EC_CORE_GPIO_LEVEL_H);
//	ec_core_gpio_write(EC_CORE_GPIO_P2, EC_CORE_GPIO_LEVEL_H);
//}
//void motorA_ccw(uint16_t cmp)//电机A反转，输入为占空比大小
//{
//	ec_core_pwm_stop(EC_CORE_PWM_CH0);
//	ec_core_pwm_start(EC_CORE_PWM_CLK_NO_DIV, EC_CORE_PWM_CH0, EC_CORE_GPIO_P3, cmp, 1000); // 占空比cmp/1000 频率=16Mhz/1000=16KHz
//	ec_core_gpio_write(EC_CORE_GPIO_P1, EC_CORE_GPIO_LEVEL_L);  // GPIO1输出低电平
//	ec_core_gpio_write(EC_CORE_GPIO_P2, EC_CORE_GPIO_LEVEL_H);  // GPIO2输出高电平
//}


//void motorB_init(void)
//{
//	ec_core_gpio_out_init(EC_CORE_GPIO_P6, EC_CORE_GPIO_LEVEL_L);  // GPIO6 初始化 输出低电平
//	ec_core_gpio_out_init(EC_CORE_GPIO_P7, EC_CORE_GPIO_LEVEL_L);  // GPIO7 初始化 输出低电平
//	ec_core_gpio_out_init(EC_CORE_GPIO_P8, EC_CORE_GPIO_LEVEL_L);  // GPIO8 初始化 输出低电平
//}
//void motorB_stop(void)//电机B停转
//{
//	ec_core_gpio_write(EC_CORE_GPIO_P6, EC_CORE_GPIO_LEVEL_L);    //设置输出电平
//	ec_core_gpio_write(EC_CORE_GPIO_P7, EC_CORE_GPIO_LEVEL_L);
//	ec_core_gpio_write(EC_CORE_GPIO_P8, EC_CORE_GPIO_LEVEL_L);
//	flag=0;
//}
//void motorB_cw(uint16_t cmp)//电机B正转，输入为占空比大小
//{
//	ec_core_pwm_stop(EC_CORE_PWM_CH1);
//	ec_core_pwm_start(EC_CORE_PWM_CLK_NO_DIV, EC_CORE_PWM_CH1, EC_CORE_GPIO_P8, cmp, 1000); // 占空比cmp/1000 频率=16Mhz/1000=16KHz
//	ec_core_gpio_write(EC_CORE_GPIO_P6, EC_CORE_GPIO_LEVEL_H);  // GPIO1输出高电平
//	ec_core_gpio_write(EC_CORE_GPIO_P7, EC_CORE_GPIO_LEVEL_L);  // GPIO2输出低电平
//	flag=1;
//}
//void motorB_break(void)
//{
//	ec_core_pwm_stop(EC_CORE_PWM_CH1);
//	ec_core_gpio_write(EC_CORE_GPIO_P6, EC_CORE_GPIO_LEVEL_H);
//	ec_core_gpio_write(EC_CORE_GPIO_P7, EC_CORE_GPIO_LEVEL_H);
//	flag=0;
//}
//void motorB_ccw(uint16_t cmp)//电机B反转，输入为占空比大小
//{
//	ec_core_pwm_stop(EC_CORE_PWM_CH1);
//	ec_core_pwm_start(EC_CORE_PWM_CLK_NO_DIV, EC_CORE_PWM_CH1, EC_CORE_GPIO_P8, cmp, 1000); // 占空比cmp/1000 频率=16Mhz/1000=16KHz
//	ec_core_gpio_write(EC_CORE_GPIO_P6, EC_CORE_GPIO_LEVEL_L);  // GPIO1输出低电平
//	ec_core_gpio_write(EC_CORE_GPIO_P7, EC_CORE_GPIO_LEVEL_H);  // GPIO2输出高电平
//	flag=2;
//}
//void motorB_change(void)
//{
//	if(flag==1)
//		motorB_ccw(cmp[2]);
//	else if(flag==2)
//		motorB_cw(cmp[2]);
//}



////闹钟模式
//void find_target(void)//寻找我的头,如果GPIO10的输入为高电平，则说明没有头
//{
//	//ec_core_gpio_in_init(EC_CORE_GPIO_P10, EC_CORE_GPIO_PULL_UP_S);
//	if(ec_core_gpio_read(EC_CORE_GPIO_P10)==EC_CORE_GPIO_LEVEL_L)
//		motorB_stop();
//	else if(ec_core_gpio_read(EC_CORE_GPIO_P10)==EC_CORE_GPIO_LEVEL_H)
//	{
//		ec_core_gpio_int_register(EC_CORE_GPIO_P10, int_rising, int_falling2); // GPIO3 中断使能
//		motorB_ccw(cmp[0]);
//	}
//}


////下面三个是利用软件定时器实现起床锤人程序由慢速捶打到快速捶打增加挡位
//void sw_timer1_int2(void) //软件定时器1中断
//{
//	ec_core_sw_timer_stop(EC_CORE_SW_TIMER1);
//	motorA_ccw(cmp[4]);
//}
//void sw_timer1_int(void) //软件定时器1中断
//{
//	motorA_ccw(cmp[2]);
//	ec_core_sw_timer_start(EC_CORE_SW_TIMER1, 10000, sw_timer1_int2);
//    // ec_core_uart0_printf("sw_timer1_int\r\n");
//}
//void get_up_now(void)
//{
//	motorA_ccw(cmp[0]);
//	ec_core_sw_timer_start(EC_CORE_SW_TIMER1, 10000, sw_timer1_int); //软件定时器
//	find_target();
//}



////遥控模式





////锤人模式
//void hammer(void)
//{
//	
//	motorA_ccw(cmp[2]);
//	ec_core_gpio_int_register(EC_CORE_GPIO_P9, int_rising, int_falling);
//}




//void to_begin(void)//当手机操控切换模式时，把一切归零，防止出现比如定时器还在计时的问题
//{
//	ec_core_sw_timer_stop(EC_CORE_SW_TIMER1);
//	motorA_stop();
//	motorB_stop();
//	ec_core_pwm_stop(EC_CORE_PWM_CH0);
//	ec_core_pwm_stop(EC_CORE_PWM_CH1);
//}


/*
关于各个GPIO引脚功能：
GPIO00：BOOT
GPIO01：电机控制AO1
GPIO02：电机控制AO2
GPIO03：电机控制APWM
GPIO04：UART_TX
GPIO05：UART_RX
GPIO06：电机控制BO1
GPIO07：电机控制BO2
GPIO08：电机控制BPWM
GPIO09：红外对管接收1
GPIO10：红外对管接收2  用于找头
*/
int main(void)
{
    ec_core_sys_clk_set(EC_CORE_SYS_CLK_48M); //配置系统时钟
	
    ec_app_flash_sys_param_read(); // 从flash读取系统参数
		ec_app_ble_param_init();       // 初始化蓝牙相关的参数（其中有关于通过蓝牙接收数据来控制电机的代码）
    ec_core_init(); //蓝牙内核初始化
    uart0_init();
		ec_core_gpio_in_init(EC_CORE_GPIO_P9, EC_CORE_GPIO_PULL_UP_S);//初始化GPIO9为上拉输入
		ec_core_gpio_in_init(EC_CORE_GPIO_P10, EC_CORE_GPIO_PULL_UP_S);
		motorA_init();
		motorB_init();
	
	

//    uint8_t ver[3] = {0};
//    ec_core_ver(ver);                                                       //读取软件版本
//    ec_core_uart0_printf("ECB02 SDK %d.%d.%d\r\n", ver[0], ver[1], ver[2]); //串口0 printf打印
	

		

		
		
		
    ec_core_sleep_disable(); //禁止睡眠，串口可以接收数据
    ec_core_main_loop_run(); //系统主循环
}

#endif
