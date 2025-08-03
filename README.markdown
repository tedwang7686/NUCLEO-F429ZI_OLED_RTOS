# NUCLEO-F429ZI OLED RTOS Project

This project demonstrates the use of a **NUCLEO-F429ZI** development board to drive an **SH1106 OLED display** (128x64) via **I2C** (PB8-SCL, PB9-SDA) using the **u8g2** library and **CMSIS-RTOS V2** (FreeRTOS). The program displays the text "Hello, NUCLEO-F429ZI!" on the OLED screen, refreshing every second. The codebase is modularized for maintainability, with separate modules for hardware drivers, RTOS tasks, and system configuration.

## Features
- **Hardware**: NUCLEO-F429ZI with SH1106 OLED (I2C interface).
- **Software**: STM32 HAL, FreeRTOS (CMSIS-RTOS V2), and u8g2 library.
- **Functionality**: Displays text on the OLED using a dedicated RTOS task.
- **Modular Design**: Organizes code into core system, hardware drivers, and RTOS tasks.

## Hardware Requirements
- **NUCLEO-F429ZI** development board.
- **SH1106 OLED display** (128x64, I2C interface).
- **Connections**:
  - SCL: PB8
  - SDA: PB9
  - VCC: 5V
  - GND: GND
- **Pull-up Resistors**: 4.7kΩ resistors on SCL and SDA lines for stable I2C communication.

## Software Requirements
- **STM32CubeIDE** or **Keil uVision** (with Keil project included in `MDK-ARM/`).
- **STM32CubeMX** for hardware configuration.
- **u8g2 Library**: Included in `Hardware/u8g2/` (sourced from [https://github.com/olikraus/u8g2](https://github.com/olikraus/u8g2)).
- **STM32F4 HAL Drivers** and **FreeRTOS** (included via STM32CubeMX).

## Project Structure
```
NUCLEO-F429ZI_OLED_RTOS/
├── NUCLEO-F429ZI_OLED_RTOS/
│   ├── Core/
│   │   ├── Inc/
│   │   │   ├── main.h               // System configuration and error handling
│   │   │   ├── gpio.h              // GPIO configuration
│   │   │   ├── i2c.h               // I2C configuration
│   │   │   ├── usart.h             // USART configuration
│   │   │   ├── stm32f4xx_hal_conf.h // HAL configuration
│   │   │   ├── stm32f4xx_it.h      // Interrupt handlers
│   │   │   ├── FreeRTOSConfig.h    // FreeRTOS configuration
│   │   │   └── rtos_tasks.h        // RTOS task declarations
│   │   ├── Src/
│   │   │   ├── main.c              // System initialization and RTOS startup
│   │   │   ├── gpio.c              // GPIO initialization
│   │   │   ├── i2c.c               // I2C initialization
│   │   │   ├── usart.c             // USART initialization
│   │   │   ├── stm32f4xx_it.c      // Interrupt handler implementations
│   │   │   ├── freertos.c          // FreeRTOS initialization
│   │   │   └── rtos_tasks.c        // RTOS task implementations
│   ├── Hardware/
│   │   ├── oled/
│   │   │   ├── oled_driver.h       // OLED driver interface
│   │   │   └── oled_driver.c       // OLED driver with u8g2 callbacks
│   │   ├── u8g2/                   // u8g2 library source code
│   │   └── ...                     // Other hardware-related files
│   ├── Drivers/
│   │   ├── CMSIS/                  // CMSIS core and RTOS API
│   │   └── STM32F4xx_HAL_Driver/   // STM32 HAL drivers
│   ├── MDK-ARM/
│   │   ├── NUCLEO-F429ZI_OLED_RTOS.uvprojx  // Keil project file
│   │   └── ...                     // Keil build artifacts
│   └── Middlewares/
│       └── Third_Party/
│           └── FreeRTOS/           // FreeRTOS core
├── README.md                       // Project documentation
└── LICENSE                         // MIT License
```

## Setup Instructions
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/<your-username>/NUCLEO-F429ZI-OLED-RTOS.git
   ```
2. **Configure Hardware**:
   - Connect the SH1106 OLED to the NUCLEO-F429ZI:
     - SCL to PB8, SDA to PB9, VCC to 5V, GND to GND.
     - Ensure 4.7kΩ pull-up resistors are connected to SCL and SDA.
3. **Set Up Development Environment**:
   - Install STM32CubeIDE or Keil uVision.
   - For STM32CubeIDE, import the project from the root directory.
   - For Keil, open `MDK-ARM/NUCLEO-F429ZI_OLED_RTOS.uvprojx`.
   - Use STM32CubeMX to verify configurations (I2C1: PB8-SCL, PB9-SDA, 400 kHz; FreeRTOS with CMSIS-RTOS V2).
4. **Verify u8g2 Library**:
   - The `Hardware/u8g2/` directory contains the u8g2 library.
   - Ensure `u8g2.h`, `u8x8.h`, and `u8g2_fonts.c` are present.
   - Add `Hardware/u8g2/` to the compiler's include path.
5. **Build and Flash**:
   - Build the project in STM32CubeIDE or Keil uVision.
   - Flash the binary to the NUCLEO-F429ZI using an ST-Link debugger.
6. **Verify**:
   - The OLED should display "Hello, NUCLEO-F429ZI!" with a 1-second refresh rate.
   - If no display appears, check:
     - I2C connections and pull-up resistors.
     - SH1106 I2C address (default: 0x3C) in `Hardware/oled/oled_driver.c`.

## Troubleshooting
- **No Display on OLED**:
  - Verify I2C connections and pull-up resistors.
  - Confirm the SH1106 I2C address in `Hardware/oled/oled_driver.c`.
  - Ensure `Hardware/u8g2/` is correctly included in the build.
- **Build Errors**:
  - Check include paths for `Hardware/u8g2/` and `Core/Inc/`.
  - Verify STM32CubeMX-generated files in `Drivers/` and `Middlewares/`.
- **RTOS Issues**:
  - Confirm FreeRTOS is enabled with CMSIS-RTOS V2 in STM32CubeMX.
  - Check task stack size in `Core/Src/rtos_tasks.c` (default: 256 * 4 bytes).

## Future Extensions
- **Additional Peripherals**: Add support for sensors (e.g., DHT11) or UART communication via `usart.c`.
- **Enhanced Display**: Implement animations or charts using u8g2 functions like `u8g2_DrawBox` or `u8g2_DrawBitmap`.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

The u8g2 library, included in `Hardware/u8g2/`, is licensed under the Apache 2.0 License. If you distribute this project (source code or binaries), you must include the u8g2 license file located at `Hardware/u8g2/LICENSE` as per its terms. See [https://github.com/olikraus/u8g2/blob/master/LICENSE](https://github.com/olikraus/u8g2/blob/master/LICENSE) for details.

## Acknowledgments
- [u8g2 Library](https://github.com/olikraus/u8g2) for OLED display support.
- [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html) for hardware configuration.
- [FreeRTOS](https://www.freertos.org) for real-time task management.