#ifndef __BLE_GETUP__
#define __BLE_GETUP__


#include "stdint.h"
#include "ec_core.h"
#include "ec_app_flash.h"
#include "main.h"

//����
extern void to_begin(void);

extern void motorA_init(void);
extern void motorA_stop(void);//���Aͣת
extern void motorA_cw(uint16_t cmp);//���A��ת������Ϊռ�ձȴ�С
extern void motorA_break(void);
extern void motorA_ccw(uint16_t cmp);//���A��ת������Ϊռ�ձȴ�С
extern void motorB_init(void);
extern void motorB_stop(void);//���Bͣת
extern void motorB_cw(uint16_t cmp);//���B��ת������Ϊռ�ձȴ�С
extern void motorB_break(void);
extern void motorB_ccw(uint16_t cmp);//���B��ת������Ϊռ�ձȴ�С
extern void motorB_change(void);

//����ģʽ
extern void get_up_now(void);

//����ģʽ
extern void hammer(void);




//�ַ���ת���Σ�stm32��֧�ֱ�׼��atoi,�����Լ�ʵ��
extern uint16_t myatoi(uint8_t chr);

//pow()ƽ������
extern uint32_t pow(uint16_t base,uint16_t exponent);

//�������ӵ���ʱ��ʱʱ�䣨�������յ��ַ�����תΪ��ֵ��
extern uint32_t delayTimes(uint8_t *data);




#endif