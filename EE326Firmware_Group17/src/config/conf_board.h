/**
 * \file
 *
 * \brief User board configuration template
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef CONF_BOARD_H
#define CONF_BOARD_H

#define BOARD_ID_USART             ID_USART0

#define BOARD_USART                USART0

#define BOARD_USART_BAUDRATE       115200

#define wifi_usart_handler         USART0_Handler

#define USART_IRQn                 USART0_IRQn

#endif // CONF_BOARD_H
