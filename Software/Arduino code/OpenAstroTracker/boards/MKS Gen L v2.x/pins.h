#pragma once

#include "Configuration.hpp"

////////////////////////////////////////////////////////////////////
// Arduino MEGA 
////////////////////////////////////////////////////////////////////
#ifdef __AVR_ATmega2560__  // Arduino Mega
    //---------------------------------------
    // If using 28BYJ-48 and ULN2003 drivers:
    #define RA_IN1_PIN  63
    #define RA_IN2_PIN  38
    #define RA_IN3_PIN  54
    #define RA_IN4_PIN  55
    #define DEC_IN1_PIN 64
    #define DEC_IN2_PIN 56
    #define DEC_IN3_PIN 60
    #define DEC_IN4_PIN 61
    //-----------------------
    // If using NEMA steppers
    #define RA_STEP_PIN 54  // STEP
    #define RA_DIR_PIN  55  // DIR
    #define RA_EN_PIN   38  // Enable
    #define RA_DIAG_PIN 3  // only needed for autohome function
    #define RA_MS0_PIN  51
    #define RA_MS1_PIN  52
    #define RA_MS2_PIN  63
    //RA TMC2209 UART specific pins
    #if UART_SOFTWARESERIAL == 0 //Required for some boards - not needed when using Serial1, Serial2, or Serial3
        #define RA_SERIAL_PORT Serial3  // HardwareSerial port, wire to TX3 for write-only
    #else
        #define RA_SERIAL_PORT_TX 40 // SoftwareSerial TX port
        #define RA_SERIAL_PORT_RX 63 // SoftwareSerial RX port
    #endif
    #define RA_DRIVER_ADDRESS 0b00  // Set by MS1/MS2. LOW/LOW in this case

    #define DEC_STEP_PIN 60  // STEP
    #define DEC_DIR_PIN  61  // DIR
    #define DEC_EN_PIN   56  // Enable
    #define DEC_DIAG_PIN 14  // only needed for autohome function
    #define DEC_MS0_PIN  51
    #define DEC_MS1_PIN  52
    #define DEC_MS2_PIN  64
    //DEC TMC2209 UART specific pins
    #if UART_SOFTWARESERIAL == 0 //Required for some boards - not needed when using Serial1, Serial2, or Serial3
        #define DEC_SERIAL_PORT Serial3  // HardwareSerial port, wire to TX3 for write-only
    #else
        #define DEC_SERIAL_PORT_TX 59 // SoftwareSerial TX port
        #define DEC_SERIAL_PORT_RX 64 // SoftwareSerial RX port
    #endif
    #define DEC_DRIVER_ADDRESS 0b01  // Set by MS1/MS2 (MS1 HIGH, MS2 LOW)
    
    #if AZIMUTH_ALTITUDE_MOTORS == 1
        // Azimuth and Altitude pins
        #define ALT_IN1_PIN 65
        #define ALT_IN2_PIN 62
        #define ALT_IN3_PIN 46
        #define ALT_IN4_PIN 48
        #define AZ_IN1_PIN 66
        #define AZ_IN2_PIN 24
        #define AZ_IN3_PIN 26
        #define AZ_IN4_PIN 28
    #endif
    //---------------
    // MISC PINS amd SETTINGS
    #if USE_GPS == 1
        #define GPS_SERIAL_PORT Serial1
        #define GPS_BAUD_RATE 9600
    #endif
    
    //LCD pin definitions (to allow configuration on different boards)
    #if DISPLAY_TYPE == DISPLAY_TYPE_LCD_KEYPAD
      #define LCD_PINA0 58
      #define LCD_PIN4 57
      #define LCD_PIN5 6
      #define LCD_PIN6 45
      #define LCD_PIN7 5
      #define LCD_PIN8 43
      #define LCD_PIN9 47
    #endif
    
#endif //mega