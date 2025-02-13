/*
 * camera.h
 *
 * Created: 2/7/2025 11:27:21 AM
 *  Author: ritvik karra
 */ 
#include <asf.h>


#ifndef CAMERA_H_
#define CAMERA_H_

/* Pointer to the image data destination buffer */
uint8_t *g_p_uc_cap_dest_buf;

/* Rows size of capturing picture */
uint16_t g_us_cap_rows = IMAGE_HEIGHT; // define IMAGE_HEIGHT

// Handler for rising-edge of VSYNC signal. Should set a flag indicating a rising edge of VSYNC.
void vsync_handler(uint32_t ul_id, uint32_t ul_mask);

// Configuration of VSYNC interrupt.
void init_vsync_interrupts(void);

// Configuration of TWI (two wire interface).
void configure_twi(void);

// Configuration and initialization of parallel capture.
void pio_capture_init(Pio *p_pio, uint32_t ul_id);

// Uses parallel capture and PDC to store image in buffer.
uint8_t pio_capture_to_buffer(Pio *p_pio, uint8_t *uc_buf, uint32_t ul_size);

// Configuration of camera pins, camera clock (XCLK), and calling the configure twi function.
void init_camera(void);

// Configuration of OV2640 registers for desired operation.
// To properly initialize the camera for JPEG (at 320 � 240 resolution), use the following commands, instead of the corresponding one in the sample project)
// ov_configure(BOARD_TWI, JPEG_INIT);
// ov_configure(BOARD_TWI, YUV422);
// ov_configure(BOARD_TWI, JPEG);
// ov_configure(BOARD_TWI, JPEG_320x240);
void configure_camera(void);

// Captures an image after a rising edge of VSYNC, and gets image
// length. Returns 1 on success (i.e. a nonzero image length), 0 on error.
uint8_t start_capture(void);

// Finds image length based on JPEG protocol. Returns 1 on success
//(i.e. able to find end of image (EOI) and start of image (SOI) markers, with SOI preceding
// EOI), 0 on error.
uint8_t find_image_len(void);

#endif /* CAMERA_H_ */