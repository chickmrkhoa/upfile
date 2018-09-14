// $Id$
#include "common.h"
#pragma section _MAIN
int main()
{
    //-----------------Setup CPU---------------//
    cpu_setup();

    delay(5);
    //-----------------Testing-----------------//
    // LIN Master mode - Response Transmission/Reception //
    // Data byte count in the response //
    unsigned int status_flag = 0x0;
    unsigned int int_r0 = 0x0;
    unsigned int int_r1 = 0x0;
    unsigned int bit_time = 0x208;
    SetClockPCLK(0x1, 0);	
    SetClockCLKC(0x02DC6C00, 0x0);	
    
    lin_master_conf(); 
    lin_master_common_setting();
    lin_master_enable_intr();
    lin_master_SetPID(0xCA);       
    
    CheckSlaveConf();
    lin_fix_slave_conf_1(); 
    lin_slave_SetBaudRatePrescaler0(0x2F);
    lin_slave_SetResponseDataLength(1);
    lin_slave_enable_intr();

    RLIN3_0.LCUC.BYTE = 0x3;
    RLIN3_1.LCUC.BYTE = 0x3;
    
    lin_master_SetResponseCommunication(MODE_TRANSMIT);
    lin_slave_SetStartTransferFrame(TRUE);
    lin_master_SetStartTransferFrameHeader(TRUE);

    // check LIN header transfer complete flag assert after 34*bit time
    //unsigned int delay_time = ((CONTROL_PORT.REG_TXCONTROL0.LONG >> 16)&0xFFFF)*100*32;
    
   // idle(0,delay_time);

    lin_slave_SetResponseCommunication(MODE_RECEIVE);
    lin_slave_SetStartResponseTransfer(TRUE);

    delay_time = ((CONTROL_PORT.REG_TXCONTROL0.LONG >> 16)&0xFFFF)*100*32;
    
    idle(0,delay_time);

    status_flag = lin_slave_ResponseSpaceStatusFlag();
    if (status_flag  != 0x00) {
        fail_bp();
    }
 
    unsigned int delay_time = ((CONTROL_PORT.REG_TXCONTROL0.LONG >> 16)&0xFFFF)*100*40;
    
    idle(0,delay_time);


    status_flag = lin_slave_ResponseSpaceStatusFlag();
    if (status_flag  != 0x01) {
        fail_bp();
    }


    if (RLIN3_1.LST.BYTE != 0) {
        fail_bp();
    }

    CONTROL_PORT.REG_LIN3INTR1.BYTE = 0;
    lin_slave_SetStartTransferFrame(FALSE);
    lin_master_SetStartTransferFrameHeader(FALSE);

 //   RLIN3_0.LCUC.BYTE = 0x0;
 //   RLIN3_1.LCUC.BYTE = 0x0;
    
 //   RLIN3_0.LCUC.BYTE = 0x3;
 //   RLIN3_1.LCUC.BYTE = 0x3;
   //check LBSS reset by writing 0
    status_flag = lin_slave_ResponseSpaceStatusFlag();
    if (status_flag  != 0x01) {
        fail_bp();
    }
 
   
    lin_slave_SetStartTransferFrame(TRUE);
    lin_master_SetStartTransferFrameHeader(TRUE);

    // check LIN header transfer complete flag assert after 34*bit time
    //delay_time = ((CONTROL_PORT.REG_TXCONTROL0.LONG >> 16)&0xFFFF)*100*12;
    
    //idle(0,delay_time);

    lin_slave_SetResponseCommunication(MODE_RECEIVE);
    lin_slave_SetStartResponseTransfer(TRUE);

    delay_time = ((CONTROL_PORT.REG_TXCONTROL0.LONG >> 16)&0xFFFF)*100*33;
    
    idle(0,delay_time);

    status_flag = lin_slave_ResponseSpaceStatusFlag();
    if (status_flag  != 0x01) {
        fail_bp();
    }

    delay_time = ((CONTROL_PORT.REG_TXCONTROL0.LONG >> 16)&0xFFFF)*100*38;
    
    idle(0,delay_time);

    status_flag = lin_slave_ResponseSpaceStatusFlag();
    if (status_flag  != 0x00) {
        fail_bp();
    }

    if (RLIN3_1.LST.BYTE != 0) {
        fail_bp();
    }

    CONTROL_PORT.REG_LIN3INTR1.BYTE = 0;
    lin_slave_SetStartTransferFrame(FALSE);
    lin_master_SetStartTransferFrameHeader(FALSE);

    lin_slave_SetStartTransferFrame(TRUE);
    lin_master_SetStartTransferFrameHeader(TRUE);

    // check LIN header transfer complete flag assert after 34*bit time
    //delay_time = ((CONTROL_PORT.REG_TXCONTROL0.LONG >> 16)&0xFFFF)*100*12;
    
    //idle(0,delay_time);

    lin_slave_SetResponseCommunication(MODE_RECEIVE);
    lin_slave_SetStartResponseTransfer(TRUE);

    delay_time = ((CONTROL_PORT.REG_TXCONTROL0.LONG >> 16)&0xFFFF)*100*40;
    
    idle(0,delay_time);

    status_flag = lin_slave_ResponseSpaceStatusFlag();
    if (status_flag  != 0x01) {
        fail_bp();
    }




    RLIN3_0.LCUC.BYTE = 0x0;
    RLIN3_1.LCUC.BYTE = 0x0;
    
    RLIN3_0.LCUC.BYTE = 0x3;
    RLIN3_1.LCUC.BYTE = 0x3;

    status_flag = lin_slave_ResponseSpaceStatusFlag();
    if (status_flag  != 0x00) {
        fail_bp();
    }

    CONTROL_PORT.REG_LIN3INTR1.BYTE = 0;

    delay(10);

    pass_bp();
}
#pragma section

void LIN3_INT_T0_func(void)
{
    *LIN3_INT_T0 = 1;
}

void LIN3_INT_R0_func(void)
{
    *LIN3_INT_R0 = 1;
}

void LIN3_INT_S0_func(void)
{
    *LIN3_INT_S0 = 1;
}

void LIN3_INT_T1_func(void)
{
    *LIN3_INT_T1 = 1;
}

void LIN3_INT_R1_func(void)
{
    *LIN3_INT_R1 = 1;
}

void LIN3_INT_S1_func(void)
{
    *LIN3_INT_S1 = 1;
}

void LIN3_INT_T2_func(void)
{
    *LIN3_INT_T2 += 1;
}

void LIN3_INT_R2_func(void)
{
    *LIN3_INT_R2 += 1;
}

void LIN3_INT_S2_func(void)
{
    *LIN3_INT_S2 += 1;
}

void LIN3_INT_T3_func(void)
{
    *LIN3_INT_T3 += 1;
}

void LIN3_INT_R3_func(void)
{
    *LIN3_INT_R3 += 1;
}

void LIN3_INT_S3_func(void)
{
    *LIN3_INT_S3 += 1;
}


