

/**
 * @file oled_driver.c
 * @author Ted Wang
 * @date 2025-08-01
 * @brief OLED driver implementation for STM32 using u8g2 library (I2C, delay, and display access).
 *
 * This file provides the implementation of the OLED driver for the NUCLEO-F429ZI board, including:
 *   - STM32-specific I2C byte transfer and delay callback functions for the u8g2/u8x8 library
 *   - Initialization of the SH1106-based 128x64 OLED display
 *   - Accessor for the internal u8g2 display object
 *
 * The driver is designed for use with the CMSIS HAL and u8g2 graphics library.
 */

#include "oled_driver.h"
#include "i2c.h"



/**
 * @brief u8g2 display object (file scope only).
 *
 * This static object holds the state and configuration for the SH1106 OLED display.
 */
static u8g2_t u8g2;

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
uint8_t u8x8_stm32_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    switch (msg)
    {
        case U8X8_MSG_DELAY_MILLI:
            HAL_Delay(arg_int);
            break;
        case U8X8_MSG_DELAY_10MICRO:
            HAL_Delay(1);
            break;
        case U8X8_MSG_DELAY_100NANO:
            __NOP();
            break;
        default:
            return 0;
    }
    return 1;
}

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
uint8_t u8x8_byte_stm32_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    static uint8_t buffer[32];
    static uint8_t buf_idx;
    uint8_t *data;

    switch (msg)
    {
        case U8X8_MSG_BYTE_SEND:
            data = (uint8_t *)arg_ptr;
            while (arg_int > 0)
            {
                buffer[buf_idx++] = *data++;
                arg_int--;
            }
            break;
        case U8X8_MSG_BYTE_INIT:
            break;
        case U8X8_MSG_BYTE_SET_DC:
            break;
        case U8X8_MSG_BYTE_START_TRANSFER:
            buf_idx = 0;
            break;
        case U8X8_MSG_BYTE_END_TRANSFER:
            HAL_I2C_Master_Transmit(&hi2c1, (u8x8_GetI2CAddress(u8x8) << 1), buffer, buf_idx, HAL_MAX_DELAY);
            break;
        default:
            return 0;
    }
    return 1;
}

/**
 * @brief Initializes the OLED display (SH1106 I2C 128x64).
 *
 * Sets up the internal u8g2 object, configures the I2C address, initializes the display, and powers it on.
 *
 * @note This function must be called before any drawing operations.
 */
void OLED_Init(void)
{
    u8g2_Setup_sh1106_i2c_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_stm32_i2c, u8x8_stm32_gpio_and_delay);
    u8g2_SetI2CAddress(&u8g2, 0x3C);
    u8g2_InitDisplay(&u8g2);
    u8g2_SetPowerSave(&u8g2, 0);
}

/**
 * @brief Returns a pointer to the internal u8g2 display object.
 *
 * Provides access to the static u8g2 object for direct drawing operations.
 *
 * @return Pointer to the internal u8g2 object.
 */
u8g2_t* OLED_GetDisplay(void)
{
    return &u8g2;
}