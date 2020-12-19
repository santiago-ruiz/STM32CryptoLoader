# The Problem
If you ever develop a firmware application that was deployed on a commercial product you know how difficult it's sometimes to have the possibility to **upgrade it**. Sometimes going near the device and flash it, it's impossible due to distances or time. Sometimes Over-The-Air updates are way too complicated for the specific application and don't make sense at all. Sometimes you only need to upgrade a firmware version to a specific client with few devices.

In those cases, giving the device the possibility to read a binary file and upgrade from it, it's the right choice. You can send the **binary file** via the internet to the client (*email, cloud*, etc.) and then they can copy it to a media device (*USB Flash, SD Card*, etc.), plug it into the product, and perform the upgrade by themself.  All without extra specific hardware.

![](./img/firmware_update.png)

Although a very simple procedure, it can bring some problems to the manufacturer:
- If the device hardware is simple enough, the client could flash it with the binary image you send, having unwanted replication of your product.
- The client could try to disassemble the code, losing your IP.
- The binary image could get damaged during some part of the upgrade process.
- Clients could try to upgrade a product with an incorrect binary image (different configuration, different product, etc.).

# A Solution
Adding a bootloader that runs before the execution of the main application, detects a specific condition to check for upgrades, read a binary file and flash the new application can do the trick.

![https://www.edgefx.in/know-about-boot-loader-technique-for-programming-microcontroller](https://www.edgefx.in/wp-content/uploads/2014/06/A-Boot-loader-for-Microcontroller-Programming.jpg)

Add some crypto magic and you have a secure way to upgrade your firmware on the field. 
In this project, we will analyze different cryptographic algorithms and libraries to measure:
- Use of RAM.
- Use of Flash.
- Time of overall upgrade procedure.
- Ease of use.

# Development
As this project is aiming for small microcontrollers, we choose a cheap and common development board, the famous STM32 BluePill. It rocks an STM32 Cortex M3 microcontroller, the STM32F103C8T6, with 64Kb of Flash and 20Kb of SRAM.


[![](https://www.electronicshub.org/wp-content/uploads/2020/02/STM32F103C8T6-Board-Features.jpg)](http://https://www.electronicshub.org/getting-started-with-stm32f103c8t6-blue-pill/)
