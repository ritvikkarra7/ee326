/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include "wifi.h"

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	board_init();
	sysclk_init();
	ioport_init();
	wdt_disable(WDT);
	
	configure_usart_wifi();
	configure_wifi_comm_pin();
	
	usart_write_line(WIFI_USART, "set comm_gpio 21\r\n");
	
	ioport_set_pin_level(LED_PIN, 0);

	while(1) {
		usart_write_line(WIFI_USART, "test\r\n");
		//ioport_toggle_pin_level(LED_PIN);
		delay_ms(500);
	}
}
