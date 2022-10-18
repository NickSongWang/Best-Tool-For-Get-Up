/******************************************************************************
 *  Copyright © 2019 Shenzhen ECIOT Technology Co., Ltd All Rights Reserved
 *-----------------------------------------------------------------------------
 * @file        ec_app_ble_peripheral.c
 * @brief       peripheral control
 * @author      mo@eciot.cn (qq:2201920828,v:eciot_mo)
 * @date        2022-02-13
 * @version     1.0
 ******************************************************************************/

#include "ec_core.h"
#include "ec_app_flash.h"
#include "main.h"



//字符串转整形，stm32不支持标准的atoi,这里自己实现
uint16_t myatoi(uint8_t chr)
{
	uint16_t s=0;
	s=chr-'0';
	return s;
}

char *reverse(char *s)
{
    char temp;
    char *p = s;    //p指向s的头部
    char *q = s;    //q指向s的尾部
    while(*q)
        ++q;
    q--;

    //交换移动指针，直到p和q交叉
    while(q > p)
    {
        temp = *p;
        *p++ = *q;
        *q-- = temp;
    }
    return s;
}

/*
 * 功能：整数转换为字符串
 * char s[] 的作用是存储整数的每一位
 */
char *myitoa(uint16_t n)
{
    uint16_t i = 0,isNegative = 0;
    static char s[100];      //必须为static变量，或者是全局变量
//    if((isNegative = n) < 0) //如果是负数，先转为正数
//    {
//        n = -n;
//    }
    do      //从各位开始变为字符，直到最高位，最后应该反转
    {
        s[i++] = n%10 + '0';
        n = n/10;
    } while(n > 0);

    if(isNegative < 0)   //如果是负数，补上负号
    {
        s[i++] = '-';
    }
    s[i] = '\0';    //最后加上字符串结束符
    return reverse(s);
}



// 1:允许通过蓝牙无线升级程序，0：禁止无线升级程序，需要重新上电，拉高BOOT引脚才能进入下载模式。
uint8_t ec_app_ble_peripheral_ota_en = 1;


void ec_app_ble_peripheral_set_ota_en(uint8_t p) //开启或关闭OTA 默认开启
{
    ec_app_ble_peripheral_ota_en = p; //修改内存
    ec_app_flash_sys_param_write();   //保存到flash
    ec_core_delay_ms(20);             //延迟20ms
    ec_core_sys_soft_reset();         //系统复位
}

static void ec_app_ble_peripheral_connect_event(void) //蓝牙连接回调
{
    ec_core_uart0_printf("ble peripheral connect\r\n");
}
static void ec_app_ble_peripheral_disconnect_event(void) //蓝牙断开回调
{
    ec_core_uart0_printf("ble peripheral disconnect\r\n");
}
static void ec_app_ble_peripheral_notify_enable_event(void) //蓝牙订阅打开回调
{
    ec_core_uart0_printf("ble peripheral notify enable\r\n");
}
static void ec_app_ble_peripheral_notify_disable_event(void) //蓝牙订阅关闭回调
{
    ec_core_uart0_printf("ble peripheral notify disable\r\n");
}
static void ec_app_ble_peripheral_receive_event(uint8_t *data, uint8_t len) //蓝牙数据接收回调
{
//	motorA_init();
//	motorB_init();
  ec_core_uart_send(EC_CORE_UART0, data, len); //蓝牙数据转发到串口
	
	if(data[0]=='T')
	{
		uint32_t time=0;;
		uint16_t h=0;
		uint16_t m=0;
		h=myatoi(data[1]);
		m=myatoi(data[2]);
		time=(h*3600+m*60)*1000;
		ec_core_uart0_printf("hello");
		ec_core_uart0_printf(myitoa(time));
	}
	if (data[0]=='1')
	{
		to_begin();
		get_up_now();
	}
		
	if (data[0]=='2')
	{
		to_begin();
		hammer();
	}
	if (data[0]=='3')
		to_begin();

  ec_core_sw_watchdog_feed(); //软件看门狗喂狗
}
void ec_app_ble_peripheral_register_event(void) //注册蓝牙事件回调
{
    ec_core_ble_peripheral_set_event_cb(EC_CORE_BLE_PERIPHERAL_EVENT_CONNECT, ec_app_ble_peripheral_connect_event);               //注册蓝牙连接的回调
    ec_core_ble_peripheral_set_event_cb(EC_CORE_BLE_PERIPHERAL_EVENT_DISCONNECT, ec_app_ble_peripheral_disconnect_event);         //注册蓝牙断开的回调
    ec_core_ble_peripheral_set_event_cb(EC_CORE_BLE_PERIPHERAL_EVENT_NOTIFY_ENABLE, ec_app_ble_peripheral_notify_enable_event);   //注册蓝牙订阅打开的回调
    ec_core_ble_peripheral_set_event_cb(EC_CORE_BLE_PERIPHERAL_EVENT_NOTIFY_DISABLE, ec_app_ble_peripheral_notify_disable_event); //注册蓝牙订阅关闭的回调
    ec_core_ble_peripheral_set_receive_cb(ec_app_ble_peripheral_receive_event);                                                   //注册蓝牙数据接收的回调
}
