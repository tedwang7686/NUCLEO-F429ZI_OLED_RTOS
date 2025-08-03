

/**
 * @file rtos_tasks.h
 * @author Ted Wang
 * @date 2025-08-01
 * @brief RTOS task management header for OLED display on NUCLEO-F429ZI.
 *
 * This header provides the declaration for the OLED display RTOS task initialization function.
 * It is intended for use with CMSIS-RTOS2 and the u8g2 graphics library.
 */

#ifndef RTOS_TASKS_H
#define RTOS_TASKS_H

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Initializes and creates the OLED display RTOS task.
 *
 * This function configures and creates a new thread for the OLED display task using the CMSIS-RTOS2 API.
 * The created task is responsible for all OLED display updates and runs indefinitely under the RTOS scheduler.
 *
 * @note Call this function once during system initialization.
 */
void OLED_Task_Init(void);

#ifdef __cplusplus
}
#endif

#endif // RTOS_TASKS_H