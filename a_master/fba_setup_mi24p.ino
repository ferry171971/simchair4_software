#if (defined MI24P_COLL_SWITCH_PANEL)      
  if (g_operating_mode != 1) {
    delay(DEVICE_INIT_DELAY);
    setup_mi24p_coll_head();            
  }  
#endif