/*
 * wifi.c
 *
 * Created: 2/7/2025 11:26:42 AM
 *  Author: andyh
 */ 
#include <asf.h>
#include "wifi.h"
#include "conf_board.h"

uint32_t g_ul_transfer_index = 0;
uint32_t g_ul_transfer_length = 0;
volatile bool g_provision_flag = false;

static uint32_t gs_ul_read_buffer = 0;

void wifi_usart_handler(void)
{
	uint32_t ul_status;

	/* Read USART Status. */
	ul_status = usart_get_status(BOARD_USART);

	/* Transfer without PDC. */
	if (ul_status & US_CSR_RXRDY)
		usart_getchar(BOARD_USART, (uint32_t *)&gs_ul_read_buffer);
		usart_write(BOARD_USART, gs_ul_read_buffer);
}

void process_incoming_byte_wifi(uint8_t in_byte)
{
	// put the byte in the next spot of the buffer
	g_puc_transfer_buffer[g_ul_transfer_index++] = in_byte;
}

void wifi_command_response_handler(uint32_t ul_id, uint32_t ul_mask)
{
	unused(ul_id);
	unused(ul_mask);

	process_data_wifi();
}

void process_data_wifi(void)
{
	usart_write_line()	
}

void wifi_provision_handler(uint32_t ul_id, uint32_t ul_mask)
{
	unused(ul_id);
	unused(ul_mask);

	g_provision_flag = true;
}

void wifi_spi_handler(void)
{
	
}

void configure_usart_wifi(void)
{
	const sam_usart_opt_t usart_console_settings = {
		BOARD_USART_BAUDRATE,
		US_MR_CHRL_8_BIT,
		US_MR_PAR_NO,
		US_MR_NBSTOP_1_BIT,
		US_MR_CHMODE_NORMAL,
		/* This field is only used in IrDA mode. */
		0
	};

	/* Enable the peripheral clock in the PMC. */
	sysclk_enable_peripheral_clock(BOARD_ID_USART);

	/* Configure USART in serial mode. */
	usart_init_rs232(BOARD_USART, &usart_console_settings,
	sysclk_get_peripheral_hz());

	/* Disable all the interrupts. */
	usart_disable_interrupt(BOARD_USART, ALL_INTERRUPT_MASK);

	/* Enable the receiver and transmitter. */
	usart_enable_tx(BOARD_USART);
	usart_enable_rx(BOARD_USART);

	/* Configure and enable interrupt of USART. */
	NVIC_EnableIRQ(USART_IRQn);
}

void configure_wifi_comm_pin(void)
{
	
}

void configure_wifi_provision_pin(void)
{
	
}

void configure_spi(void)
{
	
}

void spi_peripheral_initialize(void)
{
	uint32_t i;

	/* Reset status */
	gs_spi_status.ul_total_block_number = 0;
	gs_spi_status.ul_total_command_number = 0;
	for (i = 0; i < NB_STATUS_CMD; i++) {
		gs_spi_status.ul_cmd_list[i] = 0;
	}
	gs_ul_spi_state = SLAVE_STATE_IDLE;
	gs_ul_spi_cmd = RC_SYN;

	puts("-I- Initialize SPI as slave \r");

	/* Configure an SPI peripheral. */
	spi_enable_clock(SPI_SLAVE_BASE);
	
	spi_disable(SPI_SLAVE_BASE);
	spi_reset(SPI_SLAVE_BASE);
	spi_set_slave_mode(SPI_SLAVE_BASE);
	spi_disable_mode_fault_detect(SPI_SLAVE_BASE);
	spi_set_peripheral_chip_select_value(SPI_SLAVE_BASE, SPI_CHIP_PCS);
	spi_set_clock_polarity(SPI_SLAVE_BASE, SPI_CHIP_SEL, SPI_CLK_POLARITY);
	spi_set_clock_phase(SPI_SLAVE_BASE, SPI_CHIP_SEL, SPI_CLK_PHASE);
	spi_set_bits_per_transfer(SPI_SLAVE_BASE, SPI_CHIP_SEL, SPI_CSR_BITS_8_BIT);
	spi_enable_interrupt(SPI_SLAVE_BASE, SPI_IER_RDRF);
	spi_enable(SPI_SLAVE_BASE);

	/* Start waiting command. */
	prepare_spi_transfer(&gs_ul_spi_cmd, sizeof(gs_ul_spi_cmd));
}

void prepare_spi_transfer(void)
{
	g_puc_transfer_buffer = p_buf;
	g_ul_transfer_length = size;
	g_ul_transfer_index = 0;
	spi_write(SPI_SLAVE_BASE, g_puc_transfer_buffer[g_ul_transfer_index], 0, 0);
}

void write_wifi_command(char* comm, uint8_t cnt)
{
	
}

void write_image_to_web(void)
{
	
}
