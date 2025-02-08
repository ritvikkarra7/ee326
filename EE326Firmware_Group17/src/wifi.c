/*
 * wifi.c
 *
 * Created: 2/7/2025 11:26:42 AM
 *  Author: andyh
 */ 
#include <asf.h>
#include "wifi.h"

void wifi_usart_handler(void)
{
	// change made here (:
}

void process_incoming_byte_wifi(uint8_t in_byte)
{
	
}

void wifi_command_response_handler(uint32_t ul_id, uint32_t ul_mask)
{
	
}

void process_data_wifi(void)
{
	
}

void wifi_provision_handler(uint32_t ul_id, uint32_t ul_mask)
{
	
}

void wifi_spi_handler(void)
{
	
}

void configure_usart_wifi(void)
{
	
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
	gs_puc_transfer_buffer = p_buf;
	gs_ul_transfer_length = size;
	gs_ul_transfer_index = 0;
	spi_write(SPI_SLAVE_BASE, gs_puc_transfer_buffer[gs_ul_transfer_index], 0, 0);
}

void write_wifi_command(char* comm, uint8_t cnt)
{
	
}

void write_image_to_web(void)
{
	
}
