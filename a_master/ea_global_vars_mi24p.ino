// <MI24P_COLL_HEAD>
  #if (defined MI24P_COLL_SWITCH_PANEL)
    // last button state array count is based on three state mode switch multiplied by the amount of switch / button state + 1 8 way hat switch 
    bool g_mi24p_lastButtonState[25]; 
    uint16_t g_mi24p_lastHatVal = JOYSTICK_HATSWITCH_RELEASE;

    #define MI24P_HAT_LEFT 1
    #define MI24P_HAT_LEFT_UP 5
    #define MI24P_HAT_LEFT_DOWN 9
    #define MI24P_HAT_RIGHT 2
    #define MI24P_HAT_RIGHT_UP 6
    #define MI24P_HAT_RIGHT_DOWN 10
    #define MI24P_HAT_UP 4
    #define MI24P_HAT_DOWN 8
    #define MI24P_HAT_CLICK 16
    
  #endif
// </MI24P_COLL_HEAD>