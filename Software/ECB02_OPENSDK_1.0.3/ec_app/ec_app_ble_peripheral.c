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
#include "ble_getup.h"



//字符串转整形，stm32不支持标准的atoi,这里自己实现
//uint16_t myatoi(uint8_t chr)
//{
//	uint16_t s=0;
//	s=chr-'0';
//	return s;
//}


////pow()平方运算
//uint32_t pow(uint16_t base,uint16_t exponent)
//{
//   uint32_t result = 1;
//   while (exponent != 0)
//   {
//       result *= base;
//       --exponent;
//   }
//    return result;
//}










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
static void ec_app_ble_peripheral_receive_event(uint8_t *data, uint8_t len) //蓝牙数据接收回调（这里面就是关于蓝牙单片机受到手机发来的数据）
{
  ec_core_uart_send(EC_CORE_UART0, data, len); //蓝牙数据转发到串口
	
	if(data[0]=='T')
	{
			ec_core_uart0_printf(data);
			uint32_t dTime=delayTimes(data);
			ec_core_sw_timer_start(EC_CORE_SW_TIMER2, dTime, get_up_now); //软件定时器,根据蓝牙发送的毫秒数设置软件定时器，到时间后执行函数get_up_now()
			uint8_t *data = "TimeSeted\n";
			uint16_t len = strlen(data);
			ec_core_ble_send(data, len); //使用蓝牙发送数据给手机

	}
	if(data=="CANCEL")
	{
			ec_core_uart0_printf(data);
			to_begin();
			uint8_t *data = "Canceled\n";
			uint16_t len = strlen(data);
			ec_core_ble_send(data, len); //使用蓝牙发送数据给手机

	}

	
	


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
