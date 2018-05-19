#include "u8g_arm.h"
#include "../config.h"

void u8g_Delay(uint16_t val) {
	HAL_Delay(val);
}
void u8g_MicroDelay(void) {

	HAL_Delay(1);
}
void u8g_10MicroDelay(void) {

	HAL_Delay(1);
}
uint8_t u8g_com_hw_spi_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val,
		void *arg_ptr) {
	switch (msg) {
	case U8G_COM_MSG_STOP:
		break;
	case U8G_COM_MSG_INIT:
		u8g_10MicroDelay();
		break;
	case U8G_COM_MSG_ADDRESS: /* define cmd (arg_val = 0) or data mode (arg_val = 1) */
		u8g_10MicroDelay();
		if (arg_val == 0) {
			changeStateOfGPIO(&LCD_CD, 0);
		} else
			changeStateOfGPIO(&LCD_CD, 1);
		u8g_MicroDelay();
		break;
	case U8G_COM_MSG_CHIP_SELECT:
		u8g_MicroDelay();
		if (arg_val == 0) {
			changeStateOfGPIO(&LCD_CS, 1);
		} else
			changeStateOfGPIO(&LCD_CS, 0);
		u8g_MicroDelay();
		break;
	case U8G_COM_MSG_RESET:
		break;
	case U8G_COM_MSG_WRITE_BYTE:
		HAL_SPI_Transmit(&SPI_HANDLER, &arg_val, 1, 3);
		while (HAL_SPI_GetState(&SPI_HANDLER) != HAL_SPI_STATE_READY)
			;
		u8g_MicroDelay();
		break;
	case U8G_COM_MSG_WRITE_SEQ:
	case U8G_COM_MSG_WRITE_SEQ_P: {
		HAL_SPI_Transmit(&SPI_HANDLER, (uint8_t *) arg_ptr, arg_val, 3);
		while (HAL_SPI_GetState(&SPI_HANDLER) != HAL_SPI_STATE_READY)
			;
		u8g_MicroDelay();
		arg_val = 0;
	}
		break;
	}
	return 1;
}
