import sys
import os
import traceback
sys.path.append('./')
from common import *

scan_group   = 5
channel_num  = 2
clock_period = 10
setTimeResolution("ns")

try:

    wait(10)
    CPSetClock()
    wait(10*clock_period)
    
    # Copy from pattern: pat/01_RegisterRW/1_46_ADENDPx/tp01_46_001.cpp
    w_val   = [0xFFFFFFFF, 0x00000000, 0x55555555, 0xAAAAAAAA]
    r_val_01= [0x00000000, 0x00000000, 0x00000000, 0x00000055, 0x0000002A]
    r_val   = [0x00000000, 0x0000002A, 0x00000000, 0x00000055, 0x0000002A]
    
    msg_id = 0
    msg_set ( "=== Check ADENDP register read/write ======= ")
    for channel in range (0,channel_num):
        for index in range (0,scan_group): 
            reg_acc ( "RD", "ADC[" + str(channel) + "].ADENDP[" + str (index) + "]", 4, r_val[0])
    
            for i in range (0,4):
                reg_acc ( "WR", "ADC[" + str(channel) + "].ADENDP[" + str (index) + "]", 4, w_val[i])
                wait (SC_ZERO_TIME)
                reg_acc ( "RD", "ADC[" + str(channel) + "].ADENDP[" + str (index) + "]", 4, r_val_01[i+1])
            for i in range (0,4):
                addr = getAddress("ADC[" + str(channel) + "].ADENDP[" + str (index) + "]") + 2
                reg_acc ( "WR", addr, 2, (w_val[i] >> 16) &0xFFFF)
                wait (SC_ZERO_TIME)
                reg_acc ( "RD", addr, 2, (r_val[i+1] >> 16) &0xFFFF)
            for x in range (0,4):
                for y in range (0,4):
                    msg_set ("=== MSG ID " + "{0:05d}".format(msg_id) + " Invalid check")
                    addr = getAddress("ADC[" + str(channel) + "].ADENDP[" + str (index) + "]") + x
                    reg_acc ( "WR", addr, 1, (w_val[y] >> (x*8)) &0xFF)
                    wait (SC_ZERO_TIME)
                    reg_acc ( "RD", addr, 1, (r_val[y+1] >> (x*8)) &0xFF)
                    if (x > 1):
                        msg_chk("=== MSG ID " + "{0:05d}".format(msg_id) + " Invalid check", "Invalid access address", 2*clock_period, 1 ,False)
                    msg_id += 1
    wait((10 + clock_period) * 2)
    port_acc("WR", "preset_n", 0)
    msg_chk("port preset_n", "Initialize", -1, 784, True)
    msg_chk("port preset_n", "ABC XYZ", 0, 0, False)
    msg_chk("port preset_n", "ABC XYZ", 0, 0, True)
    wait((10 + clock_period) * 2)
    port_acc("WR", "preset_n", 1)
    wait((10 + clock_period) * 2)
    port_acc("WR", "preset_n", 0)
    wait((10 + clock_period) * 2)
   
    end_tm()
    
    exit
    
except Exception:
    traceback.print_exc()
    print ("SYNTAX ERROR in Python pattern. Please check and fix pattern first.\n")
    os.remove("transaction_log.txt")
