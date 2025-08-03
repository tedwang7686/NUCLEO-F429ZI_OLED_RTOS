

/**
 * @file rtos_tasks.c
 * @author Ted Wang
 * @date 2025-08-01
 * @brief Implementation of RTOS task creation and OLED display task for the NUCLEO-F429ZI board.
 *
 * This file contains the implementation of FreeRTOS task(s) related to the OLED display, including
 * initialization and periodic screen updates using the u8g2 graphics library. The OLED task demonstrates
 * basic text rendering and periodic refresh functionality.
 */

#include "rtos_tasks.h"
#include "oled_driver.h"
#include "cmsis_os.h"


/**
 * @brief RTOS task function for OLED display.
 *
 * This static function serves as the main loop for the OLED display task. It initializes the OLED hardware
 * and periodically updates the display with predefined text messages. The task runs indefinitely and is
 * intended to be managed by the CMSIS-RTOS2 scheduler.
 *
 * @param argument Pointer to user-defined data (unused).
 */
static void OLED_Task(void *argument);


/**
 * @brief Initializes and creates the OLED display RTOS task.
 *
 * This function configures the thread attributes and creates a new thread for the OLED display task
 * using the CMSIS-RTOS2 API. The task is responsible for handling all OLED display updates.
 *
 * @note This function should be called once during system initialization.
 */
void OLED_Task_Init(void)
{
    const osThreadAttr_t oled_task_attributes = {
        .name = "OLED_Task",              /**< Name of the OLED task. */
        .priority = (osPriority_t)osPriorityNormal, /**< Task priority. */
        .stack_size = 256 * 4              /**< Stack size in bytes. */
    };
    osThreadNew(OLED_Task, NULL, &oled_task_attributes);
}


static void OLED_Task(void *argument)
{
    /* Initialize the OLED hardware and graphics context */
    OLED_Init();
    u8g2_t *u8g2 = OLED_GetDisplay();

    while (1)
    {
        /* Clear the display buffer */
        u8g2_ClearBuffer(u8g2);
        /* Set font and draw text strings */
        u8g2_SetFont(u8g2, u8g2_font_ncenB08_tr);
        u8g2_DrawStr(u8g2, 0, 15, "Hello, NUCLEO-F429ZI!");
        u8g2_DrawStr(u8g2, 0, 35, "My name is Ted.");
        u8g2_DrawStr(u8g2, 0, 55, "How are you doing?");
        /* Send buffer to OLED display */
        u8g2_SendBuffer(u8g2);
        /* Delay for 1000 ms */
        osDelay(1000);
    }
}