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

// Configuration of camera pins, camera clock (XCLK), and calling the configure twi function.
void init_camera(void);

// Captures an image after a rising edge of VSYNC, and gets image
// length. Returns 1 on success (i.e. a nonzero image length), 0 on error.
uint8_t start_capture(void);


#endif /* CAMERA_H_ */