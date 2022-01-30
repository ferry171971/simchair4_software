#if (defined MI24P_COLL_SWITCH_PANEL)
  #include <Adafruit_MCP23X17.h>
  
  // Enable this to output data read from the MCP23017 I/O Extender
  #define MI24P_HEAD_DEBUG
  Joystick_ j_mi24p(0x19, JOYSTICK_TYPE_GAMEPAD, 24, 1, false, false, false, false, false, false, false, false, false, false, false);
  Adafruit_MCP23X17 mcp;

  #if defined(MI24P_HEAD_DEBUG)
   uint16_t wa_debug;
  #endif
  
  void setup_mi24p_coll_head() {
    
    memset(g_mi24p_lastButtonState,0,sizeof(g_mi24p_lastButtonState));
 
    j_mi24p.begin(false);  
    // configure the i2c expansion controller
    mcp.begin_I2C(MI24P_HEAD_I2C_ADDRESS);
    // configure the pins te be input with internal pullup and inverted
    // buttons assigned to port A
    mcp.pinMode(MI24P_PIN_HAT_LEFT, INPUT_PULLUP);
    mcp.pinMode(MI24P_PIN_HAT_RIGHT, INPUT_PULLUP);
    mcp.pinMode(MI24P_PIN_HAT_UP, INPUT_PULLUP);
    mcp.pinMode(MI24P_PIN_HAT_DOWN, INPUT_PULLUP);
    mcp.pinMode(MI24P_PIN_HAT_CLICK, INPUT_PULLUP);
    // buttons assigned to port B
    mcp.pinMode(MI24P_PIN_COLLECTIVE_FRICTION_CLUTCH, INPUT_PULLUP);
    mcp.pinMode(MI24P_PIN_TACTICAL_CARGO_RELEASE, INPUT_PULLUP);
    mcp.pinMode(MI24P_PIN_TURBINE_RPM_UP, INPUT_PULLUP);
    mcp.pinMode(MI24P_PIN_TURBINE_RPM_DOWN, INPUT_PULLUP);
    mcp.pinMode(MI24P_PIN_EMERGENCY_CARGO_RELEASE, INPUT_PULLUP);
    // Send dummy update
    poll_mi24pcoll_head();
  }
  
  void poll_mi24pcoll_head() {
       
    bool mi24p_btn_state[sizeof(g_mi24p_lastButtonState)];
    bool bUpdate = false;
    uint8_t ba, bb;
    uint8_t mod = 0;
    uint8_t hb = 0;

    // set array to zero value
    memset(mi24p_btn_state,0,sizeof(mi24p_btn_state));
        
    // receive data from port A and B, invert and show the low nibble of each byte
    uint16_t wa = (~(mcp.readGPIOAB()) & 0x1F1F);
    // wa = ((~wa) & 0x1F1F);
    ba = lowByte(wa);
    bb = highByte(wa);
    
    if (COLLECTIVE_MODE_SWITCH_ENABLED == 1) {
      if (g_coll_modesw_pos_decimal == MODESW_POS_MIDDLE_DECIMAL_VAL) {
        mod = 0;
      } else if (g_coll_modesw_pos_decimal == MODESW_POS_LEFT_DECIMAL_VAL) {
        mod = 5;     
      } else if (g_coll_modesw_pos_decimal == MODESW_POS_RIGHT_DECIMAL_VAL) {
        mod = 10;        
      }
    }

    #if defined(MI24P_HEAD_DEBUG)
      if( wa != wa_debug) {
        wa_debug = wa;
        printBits16(wa);
        Serial.println();
      }      
    #endif

    uint16_t hat_val = parse_MI24P_hat_val(ba,0);
 
    bUpdate = ( g_mi24p_lastHatVal != hat_val);
    g_mi24p_lastHatVal = hat_val;
    
    if (mod == 0) {
      j_mi24p.setHatSwitch(0, hat_val);
    } else if (MI24P_COLL_HEAD_HAT_RESPECTS_MODE_SWITCH) {
      hb = hat_to_btns(hat_val);
      parse_btn_bytes (mi24p_btn_state,hb,16,0,0);      
    }

    parse_btn_bytes (mi24p_btn_state,bb,mod,5,0);
    
    // decode button states
    for (byte i = 1; i < sizeof(mi24p_btn_state); i++) {
      bool v = mi24p_btn_state[i];      
      if (v != g_mi24p_lastButtonState[i]) {
        bUpdate = true;
        j_mi24p.setButton(i - 1, v);
        g_mi24p_lastButtonState[i] = v;
      }
    }    
    
    if( bUpdate ){
      j_mi24p.sendState();
    }
  }

  uint16_t parse_MI24P_hat_val (uint8_t h, uint8_t hs) {
    if (h == MI24P_HAT_LEFT){
      return 270;
    } else if (h == MI24P_HAT_LEFT_UP){
      return 315;
    } else if (h == MI24P_HAT_LEFT_DOWN){
      return 225;
    } else if (h == MI24P_HAT_RIGHT) {
      return 90;
    } else if (h == MI24P_HAT_RIGHT_UP) {
      return 45;
    } else if (h == MI24P_HAT_RIGHT_DOWN) {
      return 135;
    } else if (h == MI24P_HAT_UP) {
      return 0;
    } else if (h == MI24P_HAT_DOWN) {
      return 180;
    } else if (h == MI24P_HAT_CLICK) {
      j_mi24p.setButton(6,1);
    } else {
      j_mi24p.setButton(6,0);
      return JOYSTICK_HATSWITCH_RELEASE;   
    }
  }
   
#endif
