

/**
 * @file oled_driver.h
 * @author Ted Wang
 * @date 2025-08-01
 * @brief OLED display driver interface for STM32 using the u8g2 graphics library.
 *
 * This header provides the interface for controlling a SH1106-based 128x64 OLED display
 * on the NUCLEO-F429ZI board. It includes initialization, display object access, and
 * STM32-specific callback functions for I2C and timing integration with the u8g2 library.
 */

#ifndef OLED_DRIVER_H
#define OLED_DRIVER_H

#include "u8g2.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Initializes the OLED display (SH1106 I2C 128x64).
 *
 * Sets up the internal u8g2 object, configures the I2C address, initializes the display,
 * and powers it on. This function must be called before any drawing operations.
 *
 * @note Call once during system startup before using any display functions.
 */
void OLED_Init(void);


/**
 * @brief Returns a pointer to the internal u8g2 display object.
 *
 * Provides access to the static u8g2 object for direct drawing operations.
 *
 * @return Pointer to the internal u8g2 object.
 */
u8g2_t* OLED_GetDisplay(void);


/**
 * @brief STM32 I2C transfer callback for u8g2/u8x8.
 *
 * Implements the I2C byte transfer protocol for the u8g2 library on STM32 platforms. Handles data buffering,
 * transfer start/end, and actual I2C transmission using the STM32 HAL.
 *
 * @param[in] u8x8    Pointer to u8x8 structure.
 * @param[in] msg     Message type (U8X8_MSG_*).
 * @param[in] arg_int Integer argument (depends on message).
 * @param[in] arg_ptr Pointer argument (depends on message).
 * @retval 1 Operation successful or handled.
 * @retval 0 Operation not handled or failed.
 */
uint8_t u8x8_byte_stm32_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);


/**
 * @brief STM32-specific delay and GPIO callback for u8g2/u8x8.
 *
 * Provides timing and GPIO control for the u8g2 library on STM32 platforms. Handles delay messages
 * and basic GPIO operations as required by the u8g2/u8x8 interface.
 *
 * @param[in] u8x8    Pointer to u8x8 structure.
 * @param[in] msg     Message type (U8X8_MSG_*).
 * @param[in] arg_int Integer argument (depends on message).
 * @param[in] arg_ptr Pointer argument (depends on message).
 * @retval 1 Operation successful or handled.
 * @retval 0 Operation not handled or failed.
 */
uint8_t u8x8_stm32_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

#ifdef __cplusplus
}
#endif

#endif // OLED_DRIVER_H