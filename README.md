# PSoC-6-BLE-ARM
PSoC 6 based Servo Arm Controlled By Capsense and BMI160 Motion sensor over BLE using FreeRTOS

# Concepts
This project consist of 3 sections
1. Remote   -   A device that acts as wireless device based on bluetooth that is configured as a central device to send messages based on onboard sensor inputs to the peripheral device.

2. Controller - A device that acts as the brains of the system which is configured as a bluetooth peripheral device that received data from the central Remote device and processes on the same to send control commands to the servo slave via I2C.

3. Servo Slave -  A device that handles the hardware controls of the servo motor positions based on the I2C commands from the master Controller device.

# Hardware
The following hardware units were involved in the making of this project:
1. [PsoC 6 BLE Pioneer Kit] x 2 
2. [Arduino Uno]
3. [Kit4Curious] - Includes 4 SG90 Servo Motors
4. 5V Power Supply (SMPS Used Here)
5. Jumper Wires
6. Servo Interface Board

# Software
The following software units were involved in the making of this project:
1. [PSoC Creator]
2. [Arduino IDE]
3. [Tera Term]
4. [CySmart Android Application]

# Brief
This project mainly involves 3 sets of firmware for its operation.
The aim of this project is to understand the different concepts of <mark>bluetooth, freeeRTOS, capsense technology from Infineon and BMI160 motion sensor</mark> operation using the PSoC 6 BLE pioneer kit.
This project is in reference to the PSoC 6 101 lessons by Alan Hawse which was made for the control of 2 motors of a robotic arm.

# Innovations
1. Expanded the project for controlling 4 motors of the arm instead of 2, including horizontal movement and claw movement motors.
2. Used I2C based communication with external slave device (Arduino board here) for controlling servo motors of arm.
3. Capsense based touch feature to move each of the 4 motor is available on both the Central Remote and peripheral Controller boards.
4. Arduino firmware involves motor position limiting to prevent the servos from overstraining the arms.
5. Arduino firmware involves simultaneous motor positioning movement to move multiple motors at the same time instead of waiting for one motor to complete its positioning before moving the next.






[PsoC 6 BLE Pioneer Kit]: <https://www.cypress.com/documentation/development-kitsboards/psoc-6-ble-pioneer-kit-cy8ckit-062-ble>
[Arduino Uno]: <https://store.arduino.cc/products/arduino-uno-rev3>
[Kit4Curious]: <https://www.amazon.in/DOF-servo-Controlled-Robotic-Gripper/dp/B07R6SWCM7/ref=psdc_1378344031_t1_B07D5TVNQZ>
[PSoC Creator]: <https://www.cypress.com/products/psoc-creator-integrated-design-environment-ide>
[Arduino IDE]: <https://www.arduino.cc/en/software>
[Tera Term]: <https://ttssh2.osdn.jp/index.html.en>
[CySmart Android Application]: <https://www.cypress.com/documentation/software-and-drivers/cysmart-bluetooth-le-test-and-debug-tool#:~:text=CySmart%20is%20a%20Bluetooth%C2%AE%20LE%20host%20emulation%20tool%20for%20Windows%20PCs.>