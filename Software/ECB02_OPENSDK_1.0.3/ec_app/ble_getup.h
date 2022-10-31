#ifndef __BLE_GETUP__
#define __BLE_GETUP__


#include "stdint.h"
#include "ec_core.h"
#include "ec_app_flash.h"
#include "main.h"

//归零
extern void to_begin(void);

extern void motorA_init(void);
extern void motorA_stop(void);//电机A停转
extern void motorA_cw(uint16_t cmp);//电机A正转，输入为占空比大小
extern void motorA_break(void);
extern void motorA_ccw(uint16_t cmp);//电机A反转，输入为占空比大小
extern void motorB_init(void);
extern void motorB_stop(void);//电机B停转
extern void motorB_cw(uint16_t cmp);//电机B正转，输入为占空比大小
extern void motorB_break(void);
extern void motorB_ccw(uint16_t cmp);//电机B反转，输入为占空比大小
extern void motorB_change(void);

//闹钟模式
extern void get_up_now(void);

//锤人模式
extern void hammer(void);




//字符串转整形，stm32不支持标准的atoi,这里自己实现
extern uint16_t myatoi(uint8_t chr);

//pow()平方运算
extern uint32_t pow(uint16_t base,uint16_t exponent);

//设置闹钟倒计时定时时间（蓝牙接收到字符串，转为数值）
extern uint32_t delayTimes(uint8_t *data);




#endif