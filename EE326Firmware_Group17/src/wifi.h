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

/* Status block. */
struct status_block_t {
	/** Number of data blocks. */
	uint32_t ul_total_block_number;
	/** Number of SPI commands (including data blocks). */
	uint32_t ul_total_command_number;
	/** Command list. */
	uint32_t ul_cmd_list[NB_STATUS_CMD];
};

// SPI Status.
struct status_block_t gs_spi_status;

// Flag for ESP32 provisioning mode.
volatile bool g_provision_flag;

// Pointer to transfer buffer.
uint8_t *g_puc_transfer_buffer;

// Transfer buffer index.
uint32_t g_ul_transfer_index;

// Transfer buffer length.
uint32_t g_ul_transfer_length;


// Handler for incoming data from the WiFi. Should call process incoming byte wifi when a new byte arrives.
void wifi_usart_handler(void);

// Stores every incoming byte (in byte) from the ESP32 in a buffer.
void process_incoming_byte_wifi(uint8_t in_byte);

// Handler for “command complete” rising-edge interrupt from ESP32. When this is triggered, it is time to process
// the response of the ESP32.
void wifi_command_response_handler(uint32_t ul_id, uint32_t ul_mask);

// Processes the response of the ESP32, which should be stored in
// the buffer filled by process incoming byte wifi. This processing should be looking for certain
// responses that the ESP32 should give, such as “SUCCESS” when “test” is sent to it.
void process_data_wifi(void);

// Handler for button to initiate
// provisioning mode of the ESP32. Should set a flag indicating a request to initiate provisioning.
// mode
void wifi_provision_handler(uint32_t ul_id, uint32_t ul_mask);

// Handler for peripheral mode interrupts on SPI bus. When the
// ESP32 SPI controller requests data, this interrupt should send one byte of the image at a time.
void wifi_spi_handler(void);

// Configuration of USART port used to communicate with the ESP32.
void configure_usart_wifi(void);

// Configuration of “command complete” rising-edge interrupt.
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

/* Chip select. */
#define SPI_CHIP_SEL 0
#define SPI_CHIP_PCS spi_get_pcs(SPI_CHIP_SEL)

/* Clock polarity. */
#define SPI_CLK_POLARITY 0

/* Clock phase. */
#define SPI_CLK_PHASE 0

/** SPI base address for SPI slave mode, (on different board) */
#define SPI_SLAVE_BASE       SPI

/* SPI slave states for this example. */
#define SLAVE_STATE_IDLE           0
#define SLAVE_STATE_TEST           1
#define SLAVE_STATE_DATA           2
#define SLAVE_STATE_STATUS_ENTRY   3
#define SLAVE_STATE_STATUS         4
#define SLAVE_STATE_END            5

/* Number of commands logged in status. */
#define NB_STATUS_CMD   20

/* General return value. */
#define RC_SYN       0x55AA55AA

/* Current SPI return code. */
static uint32_t gs_ul_spi_cmd = RC_SYN;

/* Current SPI state. */
static uint32_t gs_ul_spi_state = 0;

#endif /* WIFI_H_ */