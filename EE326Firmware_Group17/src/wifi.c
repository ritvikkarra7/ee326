/*
 * wifi.c
 *
 * Created: 2/7/2025 11:26:42 AM
 *  Author: andyh
 */ 
#include <asf.h>
#include "wifi.h"
#include "conf_board.h"
#include <string.h>

volatile uint32_t received_byte_wifi = 0;
volatile bool new_rx_wifi = false;
volatile unsigned int input_pos_wifi = 0;
volatile bool wifi_comm_success = false;

// Handler for incoming data from the WiFi. Should call process incoming byte wifi when a new byte arrives.
void wifi_usart_handler(void)
{
	uint32_t ul_status;

	/* Read USART status. */
	ul_status = usart_get_status(WIFI_USART);

	/* Receive buffer is full. */
	if (ul_status & US_CSR_RXBUFF) {
		usart_read(WIFI_USART, &received_byte_wifi);
		new_rx_wifi = true;
		process_incoming_byte_wifi((uint8_t)received_byte_wifi);
	}
}

// Stores every incoming byte (in byte) from the ESP32 in a buffer.
void process_incoming_byte_wifi(uint8_t in_byte)
{
	// put the byte in the next spot of the buffer
	input_line_wifi[input_pos_wifi++] = in_byte;
}

// Handler for “command complete” rising-edge interrupt from ESP32. When this is triggered, it is time to process
// the response of the ESP32.
void wifi_command_response_handler(uint32_t ul_id, uint32_t ul_mask)
{
	unused(ul_id);
	unused(ul_mask);
	
	wifi_comm_success = true;
	process_data_wifi();
	for (int jj=0;jj<MAX_INPUT_WIFI;jj++) input_line_wifi[jj] = 0;
	input_pos_wifi = 0;
}

// Processes the response of the ESP32, which should be stored in
// the buffer filled by process incoming byte wifi. This processing should be looking for certain
// responses that the ESP32 should give, such as “SUCCESS” when “test” is sent to it.
void process_data_wifi(void)
{
	if (strstr(input_line_wifi, "SUCCESS")) {
		//ioport_toggle_pin_level(LED_PIN);
	}
}

void wifi_provision_handler(uint32_t ul_id, uint32_t ul_mask)
{
	unused(ul_id);
	unused(ul_mask);

	
}

void wifi_spi_handler(void)
{
	
}

// Configuration of USART port used to communicate with the ESP32.
void configure_usart_wifi(void)
{
	gpio_configure_pin(PIN_USART0_RXD_IDX, PIN_USART0_RXD_FLAGS);
	gpio_configure_pin(PIN_USART0_RXD_IDX, PIN_USART0_RXD_FLAGS);
	
	const sam_usart_opt_t usart_console_settings = {
		WIFI_USART_BAUDRATE,
		US_MR_CHRL_8_BIT,
		US_MR_PAR_NO,
		US_MR_NBSTOP_1_BIT,
		US_MR_CHMODE_NORMAL,
		
		/* This field is only used in IrDA mode. */
		0
	};

	/* Enable the peripheral clock in the PMC. */
	sysclk_enable_peripheral_clock(WIFI_ID_USART);

	/* Configure USART in serial mode. */
	usart_init_rs232(WIFI_USART, &usart_console_settings, sysclk_get_peripheral_hz());

	/* Disable all the interrupts. */
	usart_disable_interrupt(WIFI_USART, ALL_INTERRUPT_MASK);

	/* Enable the receiver and transmitter. */
	usart_enable_tx(WIFI_USART);
	usart_enable_rx(WIFI_USART);

	/* Configure and enable interrupt of USART. */
	NVIC_EnableIRQ(WIFI_USART_IRQn);
	
	usart_enable_interrupt(WIFI_USART, US_IER_RXRDY);
}

// Configuration of “command complete” rising-edge interrupt.
void configure_wifi_comm_pin(void)
{
	/* Configure PIO clock. */
	pmc_enable_periph_clk(WIFI_COMM_ID);

	/* Initialize PIO interrupt handler, see PIO definition in conf_board.h
	**/
	pio_handler_set(WIFI_COMM_PIO, WIFI_COMM_ID, WIFI_COMM_PIN_NUM, WIFI_COMM_ATTR, wifi_command_response_handler);

	/* Enable PIO controller IRQs. */
	NVIC_EnableIRQ((IRQn_Type)WIFI_COMM_ID);

	/* Enable PIO interrupt lines. */
	pio_enable_interrupt(WIFI_COMM_PIO, WIFI_COMM_PIN_NUM);
}

void configure_wifi_provision_pin(void)
{
	
}

void configure_spi(void)
{
	
}

void spi_peripheral_initialize(void)
{
	
}

void prepare_spi_transfer(void)
{
	
}

void write_wifi_command(char* comm, uint8_t cnt)
{
	
}

void write_image_to_web(void)
{
	
}
