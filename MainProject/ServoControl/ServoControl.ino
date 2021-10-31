/*
 * Author : Alen Austin
 * Purpose : Arduino Firmware to controller servo motor operation for Main Controller
 *            This firmware communicates with the Main controller which is a Cypress BLE Pioneer Kit
 * Date: 15/10/2021
 */

#include <Wire.h>
#include <Servo.h>


//Uncomment to observe debug messages
//#define MOTOR_DEBUG_ENABLE

/*=========================
 * ADJUSTABLE parameters
 ==========================*/

#define SERVO_SPEED             20
#define MOTOR_INITIAL_POSITION  90
#define SLAVE_ADDRESS           0x08
#define DEBUG_COM_BAUDRATE      115200
#define I2C_CLOCK_SPEED         4000000


/*====================
 *MOTOR Motion Limits 
 ===================*/
#define MOTOR_FINGER                MOTOR_1       //pin 9
#define MOTOR_FINGER_PIN            9
#define MOTOR_FINGER_MAX_LIMIT      104
#define MOTOR_FINGER_MIN_LIMIT      0
#define MOTOR_FINGER_TARGET         servos[MOTOR_FINGER].target
#define MOTOR_FINGER_SPEED          5

#define MOTOR_FOREARM               MOTOR_2       //pin 10
#define MOTOR_FOREARM_PIN           10
#define MOTOR_FOREARM_MAX_LIMIT     180
#define MOTOR_FOREARM_MIN_LIMIT     0
#define MOTOR_FOREARM_TARGET        servos[MOTOR_FOREARM].target

#define MOTOR_HORIZ                 MOTOR_3       //pin 7
#define MOTOR_HORIZ_PIN             7
#define MOTOR_HORIZ_MAX_LIMIT       180
#define MOTOR_HORIZ_MIN_LIMIT       0
#define MOTOR_HORIZ_TARGET          servos[MOTOR_HORIZ].target

#define MOTOR_ARM                   MOTOR_4       //pin 8
#define MOTOR_ARM_PIN               8
#define MOTOR_ARM_MAX_LIMIT         180
#define MOTOR_ARM_MIN_LIMIT         30
#define MOTOR_ARM_TARGET            servos[MOTOR_ARM].target



/*=========================
 * FIXED parameters
 ==========================*/
#define serialPrint             Serial.print
#define servo_print(x)          serialPrint("[ SERVO SLAVE ] : ");serialPrint(x);serialPrint("\r\n");
#define COM_ADDRESSED_MOTOR     *(receptionBuffer + 1 )
#define COM_PACKET_TAIL         *(receptionBuffer + 3 )
#define PROTOCOL_TAIL           0x0D      //tail will remaiin fixed for every transmission
#define COM_PWM_DATA            *(receptionBuffer + 2 )
#define SERVO_PERCENT_TO_ANGLE  ( 180/100)
#define PWM_COMMAND             0x0C

#define MOTOR_MIN               MOTOR_1

typedef enum{
  MOTOR_1 = 0,
  MOTOR_2,
  MOTOR_3,
  MOTOR_4,
  MOTOR_MAX
}motors_t;



//move servo motors to new positions 
void setServoPos(Servo servoX,int targetPosition, int speedX);
void setMotorPWMPercent(uint8_t motorNum,uint8_t percent);
void motorsInit();
void positionMotors();
void motorPosTargetLimitsCheck();


// create servo object to control the horizontal servo
Servo servFinger;                
Servo servArm;                  
Servo servForeArm;                    
Servo servHoriz; 

typedef struct{
  motors_t num; 
  Servo servoObj;
  uint8_t motorPin;
  uint32_t target;
  uint8_t speedCtrl;
  uint8_t maxPos;
  uint8_t minPos;
}servo_s;

servo_s servos[MOTOR_MAX] = {
   {  MOTOR_1,  servFinger,   MOTOR_FINGER_PIN,   MOTOR_INITIAL_POSITION, MOTOR_FINGER_SPEED,  MOTOR_FINGER_MAX_LIMIT,   MOTOR_FINGER_MIN_LIMIT}
  ,{  MOTOR_2,  servForeArm,  MOTOR_FOREARM_PIN,  MOTOR_INITIAL_POSITION, SERVO_SPEED,  MOTOR_FOREARM_MAX_LIMIT,  MOTOR_FOREARM_MIN_LIMIT}
  ,{  MOTOR_3,  servHoriz,    MOTOR_HORIZ_PIN,    MOTOR_INITIAL_POSITION, SERVO_SPEED,  MOTOR_HORIZ_MAX_LIMIT,    MOTOR_HORIZ_MIN_LIMIT}
  ,{  MOTOR_4,  servArm,      MOTOR_ARM_PIN,      MOTOR_INITIAL_POSITION, SERVO_SPEED,  MOTOR_ARM_MAX_LIMIT,      MOTOR_ARM_MIN_LIMIT}
  
};

char temp[100];
char receptionBuffer[20];
volatile uint8_t index = 0;
volatile uint8_t motorFoundFlag = false,motorCtrlIndex = 0;               

void setup() {
  
  //Initialize debug monitor
  Serial.begin(DEBUG_COM_BAUDRATE);           
  servo_print("\x1b[2J\x1b[;H");
  servo_print("Debug COM Initialized");
  
  //Set I2C Clock speed
  Wire.setClock(I2C_CLOCK_SPEED);

  //Initialize I2c bus with slave address
  Wire.begin(SLAVE_ADDRESS);           

  //Register command reception callback
  Wire.onReceive(commandReceptionCalback);

  
  servo_print("I2c Initialized");
  servo_print("==========================================");
  servo_print("========== SERVO SLAVE ONLINE ============");
  servo_print("==========================================");

  
  motorsInit();

}

void loop() {

  if(*receptionBuffer && (COM_PACKET_TAIL == PROTOCOL_TAIL))
  {
    switch(*receptionBuffer)
    {
      case PWM_COMMAND:
        for(int motorIndex = MOTOR_MIN  ; motorIndex < MOTOR_MAX ; motorIndex++)
        {
          if((COM_ADDRESSED_MOTOR - 1) == motorIndex)
          {
#ifdef MOTOR_DEBUG_ENABLE
            sprintf(temp,"Motor %d addressed",motorIndex);
            servo_print(temp);
#endif
            motorFoundFlag = true;
            setMotorPWMPercent(motorIndex,COM_PWM_DATA);
          }
        }
        if(!motorFoundFlag)
        {
            sprintf(temp,"Invalid motor %d addressed",COM_ADDRESSED_MOTOR);
            servo_print(temp);
        }
        *receptionBuffer = NULL;
        motorFoundFlag = false;
       break;
      
    }
  }

if (Serial.available() ) {
    //servos[MOTOR_ARM].target = Serial.parseInt();
    //servos[MOTOR_FOREARM].target = servos[MOTOR_ARM].target;
    //servos[MOTOR_FINGER].target = servos[MOTOR_ARM].target;
    servos[MOTOR_HORIZ].target = Serial.parseInt();
    Serial.read();
  }

  positionMotors();
  
}

void commandReceptionCalback(int howMany)
{
  char *temp;
  while (1 < Wire.available()) 
  { 
    //char c = Wire.read(); // receive byte as a character
#ifndef MOTOR_DEBUG_ENABLE
    receptionBuffer[index++] = Wire.read();
#else 
    receptionBuffer[index] = Wire.read();
  Serial.print(receptionBuffer[index++],HEX);
  Serial.print(" ");
#endif
  }
  
#ifdef MOTOR_DEBUG_ENABLE
  Serial.print("\r\n");
#endif
  index = 0;

  //Necessary for the next i2c read operation (dont remove)
  int x = Wire.read();
}





/*
 * ======================================================================
 * Motor Code Section
 * ======================================================================
 */
 

void motorsInit()
{
    for(int motorIndex = MOTOR_MIN ; motorIndex < MOTOR_MAX ; motorIndex++)
    {
      //Initialize the servo motor objects
      servos[motorIndex].servoObj.attach(servos[motorIndex].motorPin);
    }
}


/*
 * The servo motor object takes in the servo position i..e. from 0 to 180 degrees.
 */
void setMotorPWMPercent(uint8_t motorNum,uint8_t percent)
{ 
  //Set the target for the corresponding motor
  servos[motorNum].target = 180 * percent;
  servos[motorNum].target /= 100;
  
  sprintf(temp,"Motor : %d\tPWM :%%%3d\tTarget :%3d",motorNum,percent,servos[motorNum].target);
  servo_print(temp);
}

void motorPosTargetLimitsCheck()
{
  if(servos[motorCtrlIndex].target > servos[motorCtrlIndex].maxPos)
    {
      servos[motorCtrlIndex].target = servos[motorCtrlIndex].maxPos;
    }
    else
    if(servos[motorCtrlIndex].target < servos[motorCtrlIndex].minPos)
    {
      servos[motorCtrlIndex].target = servos[motorCtrlIndex].minPos;
    }
}


void positionMotors()
{
  
  if(MOTOR_ARM_TARGET < 90  && motorCtrlIndex == MOTOR_FOREARM) 
  {
      servos[motorCtrlIndex].minPos = 120 - MOTOR_ARM_TARGET;          
  }

  //Check if the motor is allowed to move to the specified target position
  motorPosTargetLimitsCheck();

  //Move the servo to the necessary position
  setServoPos(servos[motorCtrlIndex].servoObj,servos[motorCtrlIndex].target,servos[motorCtrlIndex].speedCtrl);
  motorCtrlIndex++;
  if(motorCtrlIndex >= MOTOR_MAX)
    motorCtrlIndex = MOTOR_MIN;
  
}


void setServoPos(Servo servoX,int targetPosition, int speedX){
    if (servoX.read()==targetPosition){
       return;
    }
    if (servoX.read() < targetPosition){
      servoX.write(servoX.read()+1);
      delay(speedX);
      return;
    }

    if (servoX.read() > targetPosition){
      servoX.write(servoX.read()-1);
      delay(speedX);
      return;
    }
}
