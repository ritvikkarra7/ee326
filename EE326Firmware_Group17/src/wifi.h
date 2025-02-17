/*
 * wifi.h
 *
 * Created: 2/7/2025 11:26:54 AM
 *  Author: andyh
 */ 
#include <asf.h>
#include "conf_board.h"

#ifndef WIFI_H_
#define WIFI_H_

// Handler for button to initiate
// provisioning mode of the ESP32. Should set a flag indicating a request to initiate provisioning.
// mode
void wifi_provision_handler(uint32_t ul_id, uint32_t ul_mask);

// Handler for peripheral mode interrupts on SPI bus. When the
// ESP32 SPI controller requests data, this interrupt should send one byte of the image at a time.
void wifi_spi_handler(void);

void configure_usart_wifi(void);
void configure_wifi_comm_pin(void);

// Configuration of button interrupt to initiate provisioning mode.
void configure_wifi_provision_pin(void);

// Configuration of SPI port and interrupts used to send images to the ESP32.
void configure_spi(void);

// Initialize the SPI port as a peripheral (slave) device.
void spi_peripheral_initialize(void);

// Set necessary parameters to prepare for SPI transfer.
void prepare_spi_transfer(void);

// Writes a command (comm) to the ESP32,
// and waits either for an acknowledgment (via the “command complete” pin) or a timeout. The
// timeout can be created by setting the global variable counts to zero, which will automatically
// increment every second, and waiting while counts < cnt.
void write_wifi_command(char* comm, uint8_t cnt);

/*
Writes an image from the SAM4S8B to the ESP32. If the
length of the image is zero (i.e. the image is not valid), return. Otherwise, follow this protocol
(illustrated in Appendix C):
1. Configure the SPI interface to be ready for a transfer by setting its parameters appropriately.
2. Issue the command “image transfer xxxx”, where xxxx is replaced by the length of the
image you want to transfer.
3. The ESP32 will then set the “command complete” pin low and begin transferring the image
over SPI.
2
4. After the image is done sending, the ESP32 will set the “command complete” pin high. The
MCU should sense this and then move on.
*/
void write_image_to_web(void);

/** USART0 pin RX */
#define PIN_USART0_RXD	  {PIO_PA5A_RXD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_PULLUP}
#define PIN_USART0_RXD_IDX        (PIO_PA5_IDX)
#define PIN_USART0_RXD_FLAGS      (PIO_PERIPH_A | PIO_PULLUP)
/** USART0 pin TX */
#define PIN_USART0_TXD    {PIO_PA6A_TXD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_PULLUP}
#define PIN_USART0_TXD_IDX        (PIO_PA6_IDX)
#define PIN_USART0_TXD_FLAGS      (PIO_PERIPH_A | PIO_PULLUP)

/** Configure USART0 */
#define WIFI_ID_USART             ID_USART0
#define WIFI_USART                USART0
#define WIFI_USART_BAUDRATE       115200
#define wifi_usart_handler        USART0_Handler
#define WIFI_USART_IRQn			  USART0_IRQn

/** All interrupt mask. */
#define ALL_INTERRUPT_MASK  0xffffffff

#define WIFI_COMM_PIN_NUM			PIO_PA22
#define WIFI_COMM_PIO				PIOA
#define WIFI_COMM_ID				ID_PIOA
#define WIFI_COMM_ATTR				PIO_IT_RISE_EDGE

#define MAX_INPUT_WIFI 1000
volatile char input_line_wifi[MAX_INPUT_WIFI];
volatile uint32_t received_byte_wifi;
volatile bool new_rx_wifi;
volatile unsigned int input_pos_wifi;
volatile bool wifi_comm_success;

#endif /* WIFI_H_ */