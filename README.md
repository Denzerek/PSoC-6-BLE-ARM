# PSoC-6-BLE-ARM
PSoC 6 based Servo Arm Controlled By Capsense and BMI160 Motion sensor over BLE using FreeRTOS

# Concepts
This project consist of 3 sections
1. Remote   -   A device that acts as wireless device based on bluetooth that is configured as a central device to send messages based on onboard sensor inputs to the peripheral device.

2. Controller - A device that acts as the brains of the system which is configured as a bluetooth peripheral device that received data from the central Remote device and processes on the same to send control commands to the servo slave via I2C.

3. Servo Slave -  A device that handles the hardware controls of the servo motor positions based on the I2C commands from the master Controller device.

# Hardware
The following hardware units were involved in the making of this project:
1. [PsoC 6 BLE Pioneer Kit] x 2   ()
2. [Arduino Uno]
3. [Kit4Curious]





[PsoC 6 BLE Pioneer Kit]: <https://www.cypress.com/documentation/development-kitsboards/psoc-6-ble-pioneer-kit-cy8ckit-062-ble>
[Arduino Uno]: <https://store.arduino.cc/products/arduino-uno-rev3>
[Kit4Curious]: <https://www.amazon.in/DOF-servo-Controlled-Robotic-Gripper/dp/B07R6SWCM7/ref=psdc_1378344031_t1_B07D5TVNQZ>