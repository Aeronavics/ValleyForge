//******************************************************************************
//! @file $RCSfile: can_isp_protocol.c,v $
//!
//! Copyright (c) 2009 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains CAN ISP PROTOCOL routines available for
//!        AT90CAN128/64/32 and ATmega16M1/32M1/32C1/64M1/64C1.
//!
//! This file has been validated with:
//!     - AVRStudio 4.15.623,
//!     - IAR C/C++ Compiler for AVR 5.20.1 (5.20.1.50092)
//!
//! @version $Revision: 3.00 $ $Name: jtellier $
//!
//! @todo
//! @bug
//******************************************************************************

//_____ I N C L U D E S ________________________________________________________
#include "config.h"
#include "can_isp_protocol.h"
#include "isp_lib.h"
#include "reduced_can_lib.h"
#include "can_drv.h"

//_____ D E F I N I T I O N S __________________________________________________

//_____ D E C L A R A T I O N S ________________________________________________

U16          base_isp_id;
U8           can_isp_rx_buffer[8];
st_cmd_t     can_isp_rx_msg;
U8           can_isp_tx_buffer[8];
st_cmd_t     can_isp_tx_msg;

U8           local_buffer[BUFFER_SIZE];
U16          loc_buf_index;

Bool         can_communication_opened;

//_____ F U N C T I O N S ______________________________________________________

//------------------------------------------------------------------------------
//  @fn can_isp_protocol_task
//!
//! This function initializes the CAN ISP PROTOCOL.
//!
//! @warning none
//!
//! @param  none
//!
//! @return none
//!
//------------------------------------------------------------------------------
void can_isp_protocol_init(void)
{
    isp_select_memory = MEM_DEFAULT;
    isp_select_page   = PAGE_DEFAULT;
    isp_start_address = ADD_DEFAULT;
    isp_number_of_bytes = N_DEFAULT;
    isp_prog_on_going = FALSE;

    base_isp_id = (((U16)CRIS) << 4);
    if(base_isp_id > MAX_BASE_ISP_IAP_ID) base_isp_id = MIN_BASE_ISP_IAP_ID ;

    //- Init Rx data
    can_isp_rx_msg.pt_data = &can_isp_rx_buffer[0];
    loc_buf_index = 0;
    //- Prepare Rx Command
    can_isp_rx_msg.msk.std = MAX_BASE_ISP_IAP_ID;
    can_isp_rx_msg.cmd = CMD_RX_DATA_MASKED;

    //- Init Tx data
    can_isp_tx_msg.pt_data = &can_isp_tx_buffer[0];
    //- Prepare Tx Command
    can_isp_tx_msg.cmd = CMD_TX_DATA;
}

//------------------------------------------------------------------------------
//  @fn can_isp_protocol_task
//!
//! This function manages the CAN ISP PROTOCOL.
//!
//! @warning none
//!
//! @param  none
//!
//! @return 0: Re-evaluation of bit-timming asked
//!         1: OK (for a new command)
//!
//------------------------------------------------------------------------------
Bool can_isp_protocol_task(void)
{
U8      i;
U8      u8_temp;

    //- Prepare Rx Command
    can_isp_rx_msg.dlc = 8;        // Max
    can_isp_rx_msg.id.std = base_isp_id;

    //- Rx Command (always accepted !!!)
    can_cmd(&can_isp_rx_msg);
    //- Wait for Rx completed
    while (1)
    {
        u8_temp = can_get_status(&can_isp_rx_msg);
        if (u8_temp != CAN_STATUS_NOT_COMPLETED) break; // Out of: while(1...
    }
    if (u8_temp == CAN_STATUS_ERROR)
    {
        return(0);  // Re-evaluation of bit-timming asked, out of the function
    }

//--- Switch following CAN ISP resquest received
    switch ((can_isp_rx_msg.id.std - base_isp_id))
    {

    //- OPEN or CLOSE COMMUNICATION (0x00) -------------------------------------
        case CAN_ID_SELECT_NODE:

            isp_prog_on_going = FALSE;  //- To prevent error if time-out during prog

            //- The length of the received frame needs to be tested because a
            //-     confusion can appears in case of IAP network when a node
            //-     acknowledges its "Open Communication". Else, this 2-byte
            //-     response could be interpreted by a non-involved slave node
            //-     as an "Open Communication"!!!
            if ( ((can_isp_rx_buffer[0]==NNB)||(can_isp_rx_buffer[0]==0xFF))
                              && (can_isp_rx_msg.dlc==1) )
            {
                if (can_communication_opened == FALSE)
                {
                    can_communication_opened = TRUE;
                    isp_select_memory = MEM_DEFAULT;
                    isp_select_page = PAGE_DEFAULT;
                }
                else
                {
                    can_communication_opened = FALSE;
                }

                //- Acknowledge frame
                can_isp_tx_msg.id.std = (base_isp_id + CAN_ID_SELECT_NODE);
                can_isp_tx_msg.dlc = 2;
                can_isp_tx_buffer[0] = BOOT_VERSION;
                can_isp_tx_buffer[1] = can_communication_opened;
                can_isp_send_frame();
            }
            //- Else nothing
            break;


    //- START PROGRAMMING (0x01) -----------------------------------------------
        case CAN_ID_PROG_START:

//$-1
//            isp_prog_on_going = FALSE;  //- To prevent error if time-out during prog

            if (can_communication_opened)
            {

            //- FULL ERASE -----------------------------------------------------
                if ( (can_isp_rx_buffer[0] == CAN_FULL_ERASE_1) && \
                     (can_isp_rx_buffer[1] == CAN_FULL_ERASE_2) && \
                     (can_isp_rx_buffer[2] == CAN_FULL_ERASE_3)    )
                {
                    if (isp_memory_erase() == FALSE)
                    {
                        can_isp_send_error_frame(); break;  //- Exit from: case ...
                    }
                }

            //- START PROGRAMMING ----------------------------------------------
                else if (can_isp_rx_buffer[0] == CAN_INIT_PROG)
                {
                isp_address_range   ( ( (((U16)can_isp_rx_buffer[1])<<8) | ((U16)can_isp_rx_buffer[2]) ) ,  \
                                      ( (((U16)can_isp_rx_buffer[3])<<8) | ((U16)can_isp_rx_buffer[4]) ) ) ;

                loc_buf_index = 0;
                isp_prog_on_going = TRUE;

                //- Save pointer and size for block programming using
                isp_start_address_copy = isp_start_address;
                isp_number_of_bytes_copy = isp_number_of_bytes;

                }

            //- ERROR WHEN START PROGRAMMING -----------------------------------
                else
                {
                    can_isp_send_error_frame(); break;  //- Exit from: case ...
                }

                //- Acknowledge frame
                can_isp_tx_msg.id.std = (base_isp_id + CAN_ID_PROG_START);
                can_isp_tx_buffer[0] = COMMAND_OK;
                can_isp_tx_msg.dlc = 1;
                if(isp_prog_on_going == TRUE)
                {
                    can_isp_tx_msg.dlc = 0;
                }
                can_isp_send_frame();
            }
            //- Else nothing
            break;

    //- DATA PROGRAMMING (0x02) ------------------------------------------------
        case CAN_ID_PROG_DATA:
            if (can_communication_opened)
            {
                if ( isp_prog_on_going == TRUE )
                {
                //- BLOCK PROGRAMMING ------------------------------------------
                    for (i=0; i<can_isp_rx_msg.dlc; i++)
                    {
                        local_buffer[loc_buf_index] = can_isp_rx_buffer[i];
                        loc_buf_index++;
                        u8_temp = 0x00;
                    }
                    if ( (loc_buf_index > (BUFFER_SIZE-0x08)) || (loc_buf_index == isp_number_of_bytes) )
                    {
                        u8_temp = isp_prog_block(local_buffer, loc_buf_index);
                        loc_buf_index = 0;
                    }
                   //- Acknowledge frame
                    can_isp_tx_msg.id.std = (base_isp_id + CAN_ID_PROG_DATA);
                    can_isp_tx_msg.dlc = 1;
                    if (u8_temp == 0x00)
                    {
                        can_isp_tx_buffer[0] = OK_NEW_DATA;
                    }
                    else if (u8_temp == 0x01)
                    {
                        can_isp_tx_buffer[0] = OK_END_OF_DATA;
                        isp_prog_on_going = FALSE;

                        //- Restore pointer and size
                        isp_start_address = isp_start_address_copy;
                        isp_number_of_bytes = isp_number_of_bytes_copy;

                    }
                    else    //- u8_temp == 0xFF, error (ex: SSB cause)
                    {
                        isp_prog_on_going = FALSE;
                        can_isp_send_error_frame(); break;  //- Exit from: case ...
                        //- CARE: Pointer and size not restored
                    }
                    can_isp_send_frame();
                }

            //- ERROR WHEN BLOCK PROGRAMMING -----------------------------------
                else
                {
                    can_isp_send_error_frame();
                }
            }
            //- Else nothing
            break;

    //- DATA DISPLAY (0x03) ----------------------------------------------------
        case CAN_ID_DISPLAY_DATA:

            isp_prog_on_going = FALSE;  //- To prevent error if time-out during prog

            if (can_communication_opened)
            {
                //- Prepare acknowledge frame
                can_isp_tx_msg.id.std = (base_isp_id + CAN_ID_DISPLAY_DATA);
                can_isp_tx_msg.dlc = 0;

                isp_address_range   ( ( (((U16)can_isp_rx_buffer[1])<<8) | ((U16)can_isp_rx_buffer[2]) ) ,  \
                                      ( (((U16)can_isp_rx_buffer[3])<<8) | ((U16)can_isp_rx_buffer[4]) ) ) ;

                //- Save pointer and size
                isp_start_address_copy = isp_start_address;
                isp_number_of_bytes_copy = isp_number_of_bytes;

            //- READ DATA ------------------------------------------------------
                if (can_isp_rx_buffer[0] == CAN_READ_DATA)
                {
                    can_isp_tx_msg.dlc = 8; //- default
                    while (1)
                    {
                        //- Using of "can_isp_tx_buffer" to store the blocks
                        u8_temp = isp_read_block(can_isp_tx_buffer,8);
                        if (u8_temp == 0x00)
                        {
                            can_isp_send_frame();   //- Intermediate  block
                        }
                        else if  (u8_temp == 0x01)
                        {
                            can_isp_tx_msg.dlc = isp_number_of_bytes;
                            can_isp_send_frame();   //- Last block
                            break;  //- Exit from: while ...
                        }
                        else    //- u8_temp == 0xFF, error (ex: SSB cause)
                        {
                            can_isp_send_error_frame(); break;  //- Exit from: while ...
                        }
                    }
                }

            //- BLANK CHECK ----------------------------------------------------
                else if (can_isp_rx_buffer[0] == CAN_BLANK_CHECK)
                {
                    if ( isp_blank_check() == FALSE )
                    {
                        //- Prepare to send 1st failed address
                        can_isp_tx_msg.dlc = 2;
                        can_isp_tx_buffer[0] = (U8)(isp_start_address >>8);
                        can_isp_tx_buffer[1] = (U8)(isp_start_address);
                    }
                    //- Acknowledge frame or send 1st failed address
                    can_isp_send_frame();
                 }

            //- ERROR WHEN DATA DISPLAY ----------------------------------------
                else
                {
                    can_isp_send_error_frame(); break;  //- Exit from: case ...
                }

                //- Restore pointer and size
                isp_start_address = isp_start_address_copy;
                isp_number_of_bytes = isp_number_of_bytes_copy;
            }
            //- Else nothing
            break;

    //- START APPLICATION (0x04) -----------------------------------------------
         case CAN_ID_START_APPLI:

//$-2
//            isp_prog_on_going = FALSE;  //- To prevent error if time-out during prog

            if (can_communication_opened)
            {
                if (can_isp_rx_buffer[0] == CAN_START_APPLI)
                {

            //- HARD RESET -----------------------------------------------------
                    if (can_isp_rx_buffer[1] == CAN_RESET_APPLI)
                    {
                        // Exit from Boot Loader and Hard
                        Hard_reset();       // c.f. at90canxx_drv.h or atmegaxxm1c1_drv.h included in config.h
                    }

            //- JUMP TO APPLICATION @ ------------------------------------------
                    else if (can_isp_rx_buffer[1] == CAN_JUMP_APPLI)
                    {
                        isp_jump_to( (((U16)can_isp_rx_buffer[2])<<8) | ((U16)can_isp_rx_buffer[3]) );
                    }

            //- ERROR WHEN START APPLICATION BUT NO RESET OR JUMP --------------
                    else { can_isp_send_error_frame(); break; }  //- Exit from: case ...
                }

            //- ERROR WHEN START APPLICATION -----------------------------------
                else { can_isp_send_error_frame(); break; }  //- Exit from: case ...
            }
            //- Else nothing
            break;

    //- SELECT MEMORY PAGE (0x06)    -------------------------------------------
        case CAN_ID_SELECT_MEM_PAGE:

            isp_prog_on_going = FALSE;  //- To prevent error if time-out during prog

            if (can_communication_opened)
            {

            //- NO ACTION ------------------------------------------------------
                if      (can_isp_rx_buffer[0] == CAN_NO_ACTION); //- No action

            //- ONLY SELECT MEMORY ---------------------------------------------
                else if (can_isp_rx_buffer[0] == CAN_SEL_MEM)
                {
                    isp_set_memory(can_isp_rx_buffer[1]);
                }

            //- ONLY SELECT PAGE -----------------------------------------------
                else if (can_isp_rx_buffer[0] == CAN_SEL_PAGE)
                {
                    isp_set_page(can_isp_rx_buffer[2]);
                }

            //- SELECT MEMORY AND PAGE -----------------------------------------
                else if (can_isp_rx_buffer[0] == CAN_SEL_MEM_N_PAGE)
                {
                    isp_set_memory(can_isp_rx_buffer[1]);
                    isp_set_page(can_isp_rx_buffer[2]);
                }

            //- ERROR WHEN SELECT MEMORY PAGE ----------------------------------
                else
                {
                can_isp_send_error_frame(); break;  //- Exit from: case ...
                }

                //- Acknowledge frame
                can_isp_tx_msg.id.std = (base_isp_id + CAN_ID_SELECT_MEM_PAGE);
                can_isp_tx_msg.dlc = 1;
                can_isp_tx_buffer[0] = COMMAND_OK;
                can_isp_send_frame();

            }   // if (can_comm...
            //- Else nothing
            break;

    //- Default ----------------------------------------------------------------
        default:
            break;

    }   // switch ((can_isp_rx...

    //- Else nothing

    return(1);
}

//------------------------------------------------------------------------------
//  @fn can_isp_send_error_frame
//!
//! This function send error protocol frame in CAN ISP PROTOCOL.
//!
//! @warning none
//!
//! @param  none
//!
//! @return
//!
//------------------------------------------------------------------------------
void can_isp_send_error_frame(void)
{
    can_isp_tx_msg.id.std = (base_isp_id + CAN_ID_ERROR);
    can_isp_tx_buffer[0] = 0x00;
    can_isp_tx_msg.dlc = 1;
    can_isp_send_frame();
}

//------------------------------------------------------------------------------
//  @fn can_isp_send_frame
//!
//! This function send frames in CAN ISP PROTOCOL.
//!
//! @warning none
//!
//! @param  none
//!
//! @return
//!
//------------------------------------------------------------------------------
void can_isp_send_frame(void)
{
    //- Tx Command (always accepted !!!)
    can_cmd(&can_isp_tx_msg);
    //- wait for Tx completed
    while(can_get_status(&can_isp_tx_msg) == CAN_STATUS_NOT_COMPLETED);
}

