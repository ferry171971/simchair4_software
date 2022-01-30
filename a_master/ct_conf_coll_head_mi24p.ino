// <MI24P_COLL_HEAD>
  // Address for the MPC27013 I/O Expander (0x20 - 0x27)  
  #define MI24P_HEAD_I2C_ADDRESS 0x20
  //
  #define MI24P_COLL_HEAD_HAT_DIRECTIONS 4
  #define MI24P_COLL_HEAD_HAT_RESPECTS_MODE_SWITCH 1
  
  #define MI24P_HEAD_IDLE_REL_BTN 12
  #define USE_MI24P_HEAD_MODESWITCH 1
  #define MI24P_HEAD_MODESWITCH_BTN 4 // use lower joy button number of the switch here  

  // The pinout for MCP23017 is add behind the definition for final connection

  #define MI24P_PIN_HAT_LEFT 0                    // GPA0 Pin 21       
  #define MI24P_PIN_HAT_RIGHT 1                   // GPA1 Pin 22
  #define MI24P_PIN_HAT_UP 2                      // GPA2 Pin 23
  #define MI24P_PIN_HAT_DOWN 3                    // GPA3 Pin 24
  #define MI24P_PIN_HAT_CLICK 4                   // GPA4 Pin 25

  #define MI24P_PIN_COLLECTIVE_FRICTION_CLUTCH 8  // GPB0 Pin 1
  #define MI24P_PIN_TACTICAL_CARGO_RELEASE 9      // GPB1 Pin 2
  #define MI24P_PIN_TURBINE_RPM_UP 10             // GPB2 Pin 3
  #define MI24P_PIN_TURBINE_RPM_DOWN 11           // GPB3 Pin 4
  #define MI24P_PIN_EMERGENCY_CARGO_RELEASE 12    // GPB4 Pin 5
  
// </MI24P_COLL_HEAD>