/******************************************************************************
 *  Copyright © 2019 Shenzhen ECIOT Technology Co., Ltd All Rights Reserved
 *-----------------------------------------------------------------------------
 * @file        ec_app_spi_ssd1306_oled_test.c
 * @brief       spi ssd1306 oled test
 * @author      mo@eciot.cn (qq:2201920828,v:eciot_mo)
 * @date        2022-04-09
 * @version     1.0
 ******************************************************************************/

#include "main.h"

#ifdef EC_APP_SPI_SSD1306_OLED_TEST

#include "ec_core.h"

#define EC_APP_UART0_TX_BUF_SIZE 1024                 //串口0发送缓冲区大小，可以根据需要调整
#define EC_APP_UART0_RX_BUF_SIZE 1024                 //串口0接收缓冲区大小，可以根据需要调整
uint8_t uart0_tx_buf[EC_APP_UART0_TX_BUF_SIZE] = {0}; //串口0发送缓冲区
uint8_t uart0_rx_buf[EC_APP_UART0_RX_BUF_SIZE] = {0}; //串口0接收缓冲区

void uart0_rx(uint8_t *buf, uint16_t len) //串口0接收数据中断
{
}

void uart0_init(void) //串口0初始化 波特率精度受时钟频率影响
{
    ec_core_uart_init(EC_CORE_UART0, 115200, EC_CORE_UART_PARITY_NONE,
                      EC_CORE_GPIO_P4, EC_CORE_GPIO_P5,
                      uart0_tx_buf, EC_APP_UART0_TX_BUF_SIZE, uart0_rx_buf, EC_APP_UART0_RX_BUF_SIZE,
                      uart0_rx);
}

int main(void)
{
    ec_core_sys_clk_set(EC_CORE_SYS_CLK_48M); //系统时钟初始化

    ec_core_init(); //蓝牙内核初始化

    uart0_init(); //串口0初始化 波特率精度受时钟频率影响

    ec_core_uart0_printf("ec_app_spi_ssd1306_oled_test\r\n"); //串口0 printf打印

    // sckl mosi rst dc
    ec_core_spi_ssd1306_oled_init(EC_CORE_GPIO_P1, EC_CORE_GPIO_P2, EC_CORE_GPIO_P3, EC_CORE_GPIO_P4);
    ec_core_spi_ssd1306_oled_show_string(0, 0, "eciot.cn");
    ec_core_spi_ssd1306_oled_show_string(16 * 1, 2, "eciot.cn");
    ec_core_spi_ssd1306_oled_show_string(16 * 2, 4, "eciot.cn");
    ec_core_spi_ssd1306_oled_show_string(16 * 3, 6, "eciot.cn");

    ec_core_sleep_disable(); //禁止睡眠，串口可以接收数据
    ec_core_main_loop_run(); //系统主循环
}

#endif
