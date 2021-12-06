# PSoC-6-BLE-ARM
PSoC 6 based Servo Arm Controlled By Capsense and BMI160 Motion sensor over BLE using FreeRTOS
Please See the Demo Video 'BLEControlledARM-DemoVideo.mp4' for functional demo.

![Demo 1](/BLEControlledARM-DemoVideo.mp4)

# Brief
This project mainly involves 3 sets of firmware for its operation.
The aim of this project is to understand the different concepts of bluetooth, freeeRTOS, capsense technology from Infineon and BMI160 motion sensor operation using the PSoC 6 BLE pioneer kit.
This project is in reference to the [PSoC 6 101 lessons by Alan Hawse] which was made for the control of 2 motors of a robotic arm.

# Innovations
1. Expanded the project for controlling 4 motors of the arm instead of 2, including horizontal movement and claw movement motors.
2. Used I2C based communication with external slave device (Arduino board here) for controlling servo motors of arm.
3. Capsense based touch feature to move each of the 4 motor is available on both the Central Remote and peripheral Controller boards.
4. Arduino firmware involves motor position limiting to prevent the servos from overstraining the arms.
5. Arduino firmware application implements simultaneous motor positioning movement to move multiple motors at the same time instead of waiting for one motor to complete its positioning before moving the next.

# Concepts
This project consist of 3 sections
1. Remote   -   A device that acts as wireless device based on bluetooth that is configured as a central device to send messages based on onboard sensor inputs to the peripheral device.

2. Controller - A device that acts as the brains of the system which is configured as a bluetooth peripheral device that received data from the central Remote device and processes on the same to send control commands to the servo slave via I2C.

3. Servo Slave -  A device that handles the hardware controls of the servo motor positions based on the I2C commands from the master Controller device.

4. Servo Motor Position - Each servo motor has a rotation from 0 to 180 degrees. Here the percentage equivalent of the same is used i.e. 0% => 0 degree and 100% => 180 degrees. 

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

# Firmware
The following details the firmware used in this project (Can be found under the folder MainProject):
1. BT_Central_Remote.cydsn 
    - Developed in PSoC Creator.
    - To be loaded in the PSoC 6 BLE Pioneer Kit board that is to be used as the wireless remote
    - Implements Bluetooth configured as central device for establishing connection to peripheral device based on compare match of Motor service UUID.
    - Cannot be used as standalone.
    - Implements firmware for data acquisition from BMI160 motion sensor from Bosch (Onboard the E-Ink display that comes packaged along with the BLE Pioneer kit) and Capsense based touch sensors from Infineon (Onboard the BLE Pioneer kit)
    - FreeRTOS for syncing BLE write operation handles from the capsense and motion sensor applications.
    - Capsense task is capable of changing the selected servo motor by clicking on the capsense buttons while the finger position on the slider will change the position of the selected servo motor.
    - If there is not movement of this board for more thatn 3 seconds, then motion sensor is deactivated and capsense touch sensor will be active.
    - User can also send UART commands from a terminal application as well to change the position of each motor as a relative to its current position.The following commands can be sent via UART    
        - 'o' - Move motor 1 by -10%
        - 'p' - Move motor 1 by  10%
        - 'k' - Move motor 2 by -10%
        - 'l' - Move motor 2 by  10%
        - 'n' - Move motor 3 by -10%
        - 'm' - Move motor 3 by  10%
        - ',' - Move motor 4 by -10%
        - '.' - Move motor 4 by  10%

2. BT_Peripheral_Controller.cydsn
    - Developed in PSoC Creator.
    - To be loaded in the PSoC 6 BLE Pioneer Kit board that is to be used as the central controller for communicating with the Servo slave over I2C
    - Implements Bluetooth configured as a peripheral device for starting advertisement for the central device to detect and connect to.
    - This firmware can be used as a standalone one where the user can connect to the 'BLEArm' bluetooth advertisement from an android phone using the CySmart application and write the positions of each motor from the motor characteristics for each of the 4 motors.
    - Capsense task is capable of changing the selected servo motor by clicking on the capsense buttons while the finger position on the slider will change the position of the selected servo motor.
    - User can also send UART commands from a terminal application as well to change the position of each motor as a relative to its current position.The following commands can be sent via UART    
        - 'o' - Move motor 1 by -10%
        - 'p' - Move motor 1 by  10%
        - 'k' - Move motor 2 by -10%
        - 'l' - Move motor 2 by  10%
        - 'n' - Move motor 3 by -10%
        - 'm' - Move motor 3 by  10%
        - ',' - Move motor 4 by -10%
        - '.' - Move motor 4 by  10%
    - I2C Configured for 400Khz in master mode to send I2C commands to Arduino Slave.
    - I2C Command packet is designed as follows :  &lt;command&gt;&lt;motor_num&gt;&lt;position_percent&gt;0D

3. ServoControl
    - Developed in Arduino IDE
    - Uses the wire.h library for I2C communication in slave mode and the servo.h library for servo motor pwm control.
    - Slave address is 0x08
    - I2C Command packet is designed as follows :  &lt;command&gt;&lt;motor_num&gt;&lt;position_percent&gt;0D
    - Only the I2C command 0x0C is supported for now.
    - Uart display of motor positions enabled.


# NOTES:
1. The interface baord is a custom soldered PCB to power the 4 servo motors operating at 5 V.
2. An SMPS (took one from an old PC I had) to get 5 V power for each of the 4 servo motors.
3. Make sure the grounds of the SMPS and arduino and all servo motors are same  (else causes excessive jerking of servo motorsm causing the arm to go out of control and not respond to PWM signals from arduino)
4. Do not power 4 servo motors from arduino (It cannot supply the necessary current and can result in motor heating).
5. Do not use the same single 5V line for all 4 servo motors, This can cause excessive current to flow and heat and melt the wires. (Recommended : Use different 5 V lines for each servo (SMPS used in PCs has multiple 5V lines making this possible))





[PsoC 6 BLE Pioneer Kit]: <https://www.cypress.com/documentation/development-kitsboards/psoc-6-ble-pioneer-kit-cy8ckit-062-ble>
[Arduino Uno]: <https://store.arduino.cc/products/arduino-uno-rev3>
[Kit4Curious]: <https://www.amazon.in/DOF-servo-Controlled-Robotic-Gripper/dp/B07R6SWCM7/ref=psdc_1378344031_t1_B07D5TVNQZ>
[PSoC Creator]: <https://www.cypress.com/products/psoc-creator-integrated-design-environment-ide>
[Arduino IDE]: <https://www.arduino.cc/en/software>
[Tera Term]: <https://ttssh2.osdn.jp/index.html.en>
[CySmart Android Application]: <https://www.cypress.com/documentation/software-and-drivers/cysmart-bluetooth-le-test-and-debug-tool#:~:text=CySmart%20is%20a%20Bluetooth%C2%AE%20LE%20host%20emulation%20tool%20for%20Windows%20PCs.>
[PSoC 6 101 lessons by Alan Hawse]: <https://www.cypress.com/training/psoc-101-video-tutorial-series-how-use-arm-cortex-m4-based-psoc-6>