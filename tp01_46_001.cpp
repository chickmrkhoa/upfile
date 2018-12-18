// $Id$
#include "common.h"

#define CHANNEL_NUM 3 
//#define VC_NUM 48 //added by uyenle 060415
//#define VC_NUM_AVAI 36

#pragma section _MAIN
int main()
{
    //-----------------Setup CPU---------------//
    cpu_setup();
    //----------------Set clocks---------------//
    CPSetClock();

    delay(5);

    //-------------TESTING_CONTENT-------------//
    volatile unsigned int*   reg_ptr_base_long  = (volatile unsigned int*)   &ADC0.ADENDP[0].LONG; //please update this line for each register
    volatile unsigned short* reg_ptr_base_word0 = (volatile unsigned short*) &ADC0.ADENDP[0].LONG; //please update this line for each register
    volatile unsigned short* reg_ptr_base_word1 = (volatile unsigned short*) &ADC0.ADENDP[0].LONG+1; //please update this line for each register
    volatile unsigned char*  reg_ptr_base_byte0 = (volatile unsigned char*)  &ADC0.ADENDP[0].LONG; //please update this line for each register
    volatile unsigned char*  reg_ptr_base_byte1 = (volatile unsigned char*)  &ADC0.ADENDP[0].LONG+1; //please update this line for each register
    volatile unsigned char*  reg_ptr_base_byte2 = (volatile unsigned char*)  &ADC0.ADENDP[0].LONG+2; //please update this line for each register
    volatile unsigned char*  reg_ptr_base_byte3 = (volatile unsigned char*)  &ADC0.ADENDP[0].LONG+3;//please update this line for each register

    unsigned int w_val[4] = {0xFFFFFFFF, 0x00000000, 0x55555555, 0xAAAAAAAA};
    unsigned int r_val_01[5] = {0x00000000, 0x00000000, 0x00000000, 0x0000000, 0x0000002A};//please update this line for each register
    unsigned int r_val[5] = {0x00000000, 0x0000002A, 0x00000000, 0x00000000, 0x0000002A};//please update this line for each register

    unsigned int reg_index = 5 ;//please update this line for each register

    for (unsigned int channel=0; channel<CHANNEL_NUM; channel++) { 
        /// SARAD4 modify
        for (unsigned int index=0; index<reg_index; index++) {
            volatile unsigned int*   reg_ptr_long  = reg_ptr_base_long  + channel*0x2000/4 + index;
            volatile unsigned short* reg_ptr_word0 = reg_ptr_base_word0 + channel*0x2000/2 + 2*index;
            volatile unsigned short* reg_ptr_word1 = reg_ptr_base_word1 + channel*0x2000/2 + 2*index;
            volatile unsigned char*  reg_ptr_byte0 = reg_ptr_base_byte0 + channel*0x2000   + 4*index;
            volatile unsigned char*  reg_ptr_byte1 = reg_ptr_base_byte1 + channel*0x2000   + 4*index;
            volatile unsigned char*  reg_ptr_byte2 = reg_ptr_base_byte2 + channel*0x2000   + 4*index;
            volatile unsigned char*  reg_ptr_byte3 = reg_ptr_base_byte3 + channel*0x2000   + 4*index;
            //*******************************************
            //- Check the initial value
            //*******************************************
            if (*reg_ptr_long != r_val[0]) { fail_bp(); }
    
            delay(5);
    
            for (unsigned int i=0; i<4; i++) {
                 *reg_ptr_long = w_val[i];
                 //if (*reg_ptr_long != r_val[i+1]) { fail_bp(); }
                 if (*reg_ptr_long != r_val_01[i+1]) { fail_bp(); }
                 // warning message: Cannot write 1 to reserved bit.
             
                 delay(5);
            }
    
            //*******************************************
            //-Check access size less than access length-
            //*******************************************
            // Checking write 0xFFFF to WORD0 of register
            for (unsigned int i=0; i<4; i++) {
                unsigned int wr_val = w_val[i]&0xFFFF;
                unsigned int rd_val = r_val[i+1]&0xFFFF;
                *reg_ptr_word0 = wr_val;
                if (*reg_ptr_word0 != rd_val) { fail_bp(); }
    
                delay(5);
            }
            // Checking write 0xFFFF to WORD1 of register
            for (unsigned int i=0; i<4; i++) {
                unsigned int wr_val = (w_val[i]>>16)&0xFFFF;
                unsigned int rd_val = (r_val[i+1]>>16)&0xFFFF;
                *reg_ptr_word1 = wr_val;
                if (*reg_ptr_word1 != rd_val) { fail_bp(); }
    
                delay(5);
            }
            // Checking write 0xFF to BYTE0 of register
            for (unsigned int i=0; i<4; i++) {
                unsigned int wr_val = w_val[i]&0xFF;
                unsigned int rd_val = r_val[i+1]&0xFF;
                *reg_ptr_byte0 = wr_val;
                if (*reg_ptr_byte0 != rd_val) { fail_bp(); }
    
                delay(5);
            }
            // Checking write 0xFF to BYTE1 of register
            for (unsigned int i=0; i<4; i++) {
                unsigned int wr_val = (w_val[i]>>8)&0xFF;
                unsigned int rd_val = (r_val[i+1]>>8)&0xFF;
                *reg_ptr_byte1 = wr_val;
                if (*reg_ptr_byte1 != rd_val) { fail_bp(); }
    
                delay(5);
            }
            // Checking write 0xFF to BYTE0 of register
            for (unsigned int i=0; i<4; i++) {
                unsigned int wr_val = (w_val[i]>>16)&0xFF;
                unsigned int rd_val = (r_val[i+1]>>16)&0xFF;
                *reg_ptr_byte2 = wr_val;
                if (*reg_ptr_byte2 != rd_val) { fail_bp(); }
    
                delay(5);
            }
            // Checking write 0xFF to BYTE0 of register
            for (unsigned int i=0; i<4; i++) {
                unsigned int wr_val = (w_val[i]>>24)&0xFF;
                unsigned int rd_val = (r_val[i+1]>>24)&0xFF;
                *reg_ptr_byte3 = wr_val;
                if (*reg_ptr_byte3 != rd_val) { fail_bp(); }
    
                delay(5);
            }
        }
    }


    delay(5);


    pass_bp();
}
#pragma section

