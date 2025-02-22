#pragma once

#include "../Configuration.hpp"
#include "inc/Globals.hpp"
PUSH_NO_WARNINGS
#include <AccelStepper.h>
POP_NO_WARNINGS

#include "Utility.hpp"
#include "DayTime.hpp"
#include "Mount.hpp"
#include "MeadeCommandProcessor.hpp"

// TODO: we have to change driver type to DRIVER_TYPE_TMC2209 and add a new definition for the actual mode (e.g. DRIVER_MODE_UART)
#if (RA_DRIVER_TYPE == DRIVER_TYPE_TMC2209_STANDALONE) || (RA_DRIVER_TYPE == DRIVER_TYPE_TMC2209_UART)                                     \
    || (DEC_DRIVER_TYPE == DRIVER_TYPE_TMC2209_STANDALONE) || (DEC_DRIVER_TYPE == DRIVER_TYPE_TMC2209_UART)                                \
    || (AZ_DRIVER_TYPE == DRIVER_TYPE_TMC2209_UART) || (ALT_DRIVER_TYPE == DRIVER_TYPE_TMC2209_UART)
PUSH_NO_WARNINGS
    #include <TMCStepper.h>
POP_NO_WARNINGS
#endif

#if USE_GPS == 1
PUSH_NO_WARNINGS
    //#include <SoftwareSerial.h>
    #include <TinyGPS++.h>
POP_NO_WARNINGS

//SoftwareSerial SoftSerial(GPS_SERIAL_RX_PIN, GPS_SERIAL_TX_PIN); // RX, TX
TinyGPSPlus gps;
#endif

////////////////////////////////////
// Stepper definitions /////////////
#if RA_STEPPER_TYPE == STEPPER_TYPE_28BYJ48
    // RA Motor pins
    #if RA_INVERT_DIR == 1
        #define RAmotorPin1 RA_IN1_PIN  // IN1 auf ULN2003 driver 1
        #define RAmotorPin3 RA_IN2_PIN  // IN2 auf ULN2003 driver 1
        #define RAmotorPin2 RA_IN3_PIN  // IN3 auf ULN2003 driver 1
        #define RAmotorPin4 RA_IN4_PIN  // IN4 auf ULN2003 driver 1
    #else
        #define RAmotorPin1 RA_IN4_PIN  // IN1 auf ULN2003 driver 1
        #define RAmotorPin3 RA_IN3_PIN  // IN2 auf ULN2003 driver 1
        #define RAmotorPin2 RA_IN2_PIN  // IN3 auf ULN2003 driver 1
        #define RAmotorPin4 RA_IN1_PIN  // IN4 auf ULN2003 driver 1
    #endif
#elif RA_STEPPER_TYPE == STEPPER_TYPE_NEMA17
    #define RAmotorPin1 RA_STEP_PIN
    #define RAmotorPin2 RA_DIR_PIN
#endif

// DEC Motor pins
#if DEC_STEPPER_TYPE == STEPPER_TYPE_28BYJ48
    #if DEC_INVERT_DIR == 1
        #define DECmotorPin1 DEC_IN4_PIN  // IN1 auf ULN2003 driver 2
        #define DECmotorPin3 DEC_IN3_PIN  // IN2 auf ULN2003 driver 2
        #define DECmotorPin2 DEC_IN2_PIN  // IN3 auf ULN2003 driver 2
        #define DECmotorPin4 DEC_IN1_PIN  // IN4 auf ULN2003 driver 2
    #else
        #define DECmotorPin1 DEC_IN1_PIN  // IN1 auf ULN2003 driver 2
        #define DECmotorPin3 DEC_IN2_PIN  // IN2 auf ULN2003 driver 2
        #define DECmotorPin2 DEC_IN3_PIN  // IN3 auf ULN2003 driver 2
        #define DECmotorPin4 DEC_IN4_PIN  // IN4 auf ULN2003 driver 2
    #endif
#elif DEC_STEPPER_TYPE == STEPPER_TYPE_NEMA17
    #define DECmotorPin1 DEC_STEP_PIN
    #define DECmotorPin2 DEC_DIR_PIN
#endif

// AZ Motor pins
#if (AZ_STEPPER_TYPE != STEPPER_TYPE_NONE)
    // AZ Pins are defined based on driver type rather than stepper type since the 28BYJ may be used with a TMC2209 or similar driver when modified to bipolar mode
    #if AZ_DRIVER_TYPE == DRIVER_TYPE_ULN2003
        #define AZmotorPin1 AZ_IN1_PIN
        #define AZmotorPin3 AZ_IN2_PIN
        #define AZmotorPin2 AZ_IN3_PIN
        #define AZmotorPin4 AZ_IN4_PIN
    #elif AZ_DRIVER_TYPE == DRIVER_TYPE_A4988_GENERIC || AZ_DRIVER_TYPE == DRIVER_TYPE_TMC2209_STANDALONE                                  \
        || AZ_DRIVER_TYPE == DRIVER_TYPE_TMC2209_UART
        #define AZmotorPin1 AZ_STEP_PIN
        #define AZmotorPin2 AZ_DIR_PIN
    #endif
#endif

// ALT Motor pins
#if (ALT_STEPPER_TYPE != STEPPER_TYPE_NONE)
    #if ALT_DRIVER_TYPE == DRIVER_TYPE_ULN2003
        #define ALTmotorPin1 ALT_IN1_PIN
        #define ALTmotorPin3 ALT_IN2_PIN
        #define ALTmotorPin2 ALT_IN3_PIN
        #define ALTmotorPin4 ALT_IN4_PIN
    #elif ALT_DRIVER_TYPE == DRIVER_TYPE_A4988_GENERIC || ALT_DRIVER_TYPE == DRIVER_TYPE_TMC2209_STANDALONE                                \
        || ALT_DRIVER_TYPE == DRIVER_TYPE_TMC2209_UART
        #define ALTmotorPin1 ALT_STEP_PIN
        #define ALTmotorPin2 ALT_DIR_PIN
    #endif
#endif

// Focus Motor pins
#if (FOCUS_STEPPER_TYPE != STEPPER_TYPE_NONE)
    #if FOCUS_DRIVER_TYPE == DRIVER_TYPE_ULN2003
        #define FOCUSmotorPin1 FOCUS_IN1_PIN
        #define FOCUSmotorPin3 FOCUS_IN2_PIN
        #define FOCUSmotorPin2 FOCUS_IN3_PIN
        #define FOCUSmotorPin4 FOCUS_IN4_PIN
    #elif FOCUS_DRIVER_TYPE == DRIVER_TYPE_A4988_GENERIC || FOCUS_DRIVER_TYPE == DRIVER_TYPE_TMC2209_STANDALONE                            \
        || FOCUS_DRIVER_TYPE == DRIVER_TYPE_TMC2209_UART
        #define FOCUSmotorPin1 FOCUS_STEP_PIN
        #define FOCUSmotorPin2 FOCUS_DIR_PIN
    #endif
#endif

// End Stepper Definitions //////////////
/////////////////////////////////////////

/////////////////////////////////////////
// Driver definitions ///////////////////
#if (RA_DRIVER_TYPE == DRIVER_TYPE_TMC2209_UART) || (DEC_DRIVER_TYPE == DRIVER_TYPE_TMC2209_UART)                                          \
    || (AZ_DRIVER_TYPE == DRIVER_TYPE_TMC2209_UART) || (ALT_DRIVER_TYPE == DRIVER_TYPE_TMC2209_UART)
    #define R_SENSE 0.11f  // 0.11 for StepStick
#endif
// End Driver Definitions ///////////////
/////////////////////////////////////////

// Menu IDs
#define RA_Menu          1
#define DEC_Menu         2
#define HA_Menu          3
#define Heat_Menu        4
#define Calibration_Menu 5
#define Focuser_Menu     6
#define Control_Menu     7
#define Home_Menu        8
#define POI_Menu         9
#define Status_Menu      10

// How many menu items at most?
#define MAXMENUITEMS 11

#if SUPPORT_GUIDED_STARTUP == 1
bool inStartup = true;  // Start with a guided startup
#else
bool inStartup = false;  // Start with a guided startup
#endif

// Serial control variables
bool okToUpdateMenu                = true;   // Can be used to supress rendering the first line of the menu.
bool quitSerialOnNextButtonRelease = false;  // Used to detect SELECT button to quit Serial mode.

// Global variables
bool isUnreachable = false;

// RA variables
int RAselect;

// DEC variables
int DECselect;

// HA variables
int HAselect;

//debugging
String inBT;
