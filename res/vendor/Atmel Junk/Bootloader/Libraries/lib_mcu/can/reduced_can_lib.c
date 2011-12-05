//**************************************************************************
//! @file $RCSfile: reduced_can_lib.c,v $
//!
//! Copyright (c) 2009 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains CAN lib routines available for all ATMEL CAN
//!        AT90CAN128/64/32 nd ATmega16M1/32M1/32C1/64M1/64C1.
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
#include "reduced_can_lib.h"
#include "can_drv.h"

//_____ D E F I N I T I O N S __________________________________________________

//_____ F U N C T I O N S ______________________________________________________

//------------------------------------------------------------------------------
//  @fn can_cmd
//!
//! This function takes a CAN descriptor, analyses the action to do:
//! transmit, receive or abort.
//! This function returns a status (CAN_CMD_ACCEPTED or CAN_CMD_REFUSED) if
//! a MOb for Rx or Tx has been found. If no MOB has been found, the
//! application must be retry at a later date.
//! This function also updates the CAN descriptor status (MOB_PENDING or
//! MOB_NOT_REACHED) if a MOb for Rx or Tx has been found. If aborting
//! is performed, the CAN descriptor status will be set to STATUS_CLEARED.
//!
//! @param  st_cmd_t* - Can_descriptor pointer on CAN descriptor structure
//!         to select the action to do.
//!
//! @return CAN_CMD_ACCEPTED - command is accepted
//!         CAN_CMD_REFUSED  - command is refused
//!
//------------------------------------------------------------------------------
U8 can_cmd(st_cmd_t* cmd)
{
U8  cpt;
U8  rtn_val;

    rtn_val = CAN_CMD_ACCEPTED;
    cmd->status = MOB_PENDING;

    //------------ special for "reduced_can_lib.c"
    if ((cmd->cmd) == CMD_TX_DATA)
    {
        cmd->handle = LAST_MOB_NB;
        Can_set_mob(LAST_MOB_NB);
        Can_clear_mob();
        Can_clear_ide();
        Can_set_std_id(cmd->id.std);
        for (cpt=0; cpt<cmd->dlc; cpt++) CANMSG = *(cmd->pt_data + cpt);
        Can_clear_rtr();
        Can_set_dlc(cmd->dlc);
        Can_config_tx();
    }
    //------------ special for "reduced_can_lib.c"
    else if ((cmd->cmd) == CMD_RX_DATA_MASKED)
    {
        cmd->handle = MOB_0;
        Can_set_mob(MOB_0);
        Can_clear_mob();
        Can_clear_ide();
        Can_set_std_id(cmd->id.std);
        Can_set_std_msk(cmd->msk.std);
        Can_set_rtrmsk(); Can_clear_rtr();
        Can_set_idemsk();
        Can_config_rx();
    }
    // case CMD_NONE or not implemented command
    else rtn_val= STATUS_CLEARED;

    return rtn_val;
}

//------------------------------------------------------------------------------
//  @fn can_get_status
//!
//! This function allows to return if the command has been performed or not.
//! In an reception case, all the CAN message is stored in the structure.
//! This function also updates the CAN descriptor status (MOB_TX_COMPLETED,
//!  MOB_RX_COMPLETED, MOB_RX_COMPLETED_DLCW or MOB_???_ERROR).
//!
//! @param  st_cmd_t* pointer on CAN descriptor structure.
//!
//! @return CAN_STATUS_COMPLETED     - Rx or Tx is completed
//!         CAN_STATUS_NOT_COMPLETED - Rx or Tx is not completed
//!         CAN_STATUS_ERROR         - Error in configuration or in the
//!                                    CAN communication
//!
//------------------------------------------------------------------------------
U8 can_get_status (st_cmd_t* cmd)
{
U8 a_status;
U8 rtn_val;

    a_status = cmd->status;
    if ( (a_status==STATUS_CLEARED)||(a_status==MOB_NOT_REACHED)||(a_status==MOB_DISABLE) )
    {
        return CAN_STATUS_ERROR;
    }

    Can_set_mob(cmd->handle);
    a_status = can_get_mob_status();

    switch (a_status)
    {
        case MOB_NOT_COMPLETED:
            // cmd->status not updated
            rtn_val = CAN_STATUS_NOT_COMPLETED;
            break;
        //--------------- special for "reduced_can_lib.c"
        case MOB_RX_COMPLETED:
        case MOB_RX_COMPLETED_DLCW:
            cmd->dlc = Can_get_dlc();
            can_get_data(cmd->pt_data);
            // Always standard frame
            Can_get_std_id(cmd->id.std);    //- Warning[Pa082]: undefined behavior: the order of volatile accesses is undefined in this statement
            // Status field of descriptor: 0x20 if Rx completed
            // Status field of descriptor: 0xA0 if Rx completed with DLCWarning
            cmd->status = a_status;
            Can_mob_abort();        // Freed the MOB
            Can_clear_status_mob(); //   and reset MOb status
            rtn_val = CAN_STATUS_COMPLETED;
            break;
        //--------------- special for "reduced_can_lib.c"
        case MOB_TX_COMPLETED:
            // Status field of descriptor: 0x40 if Tx completed
            cmd->status = a_status;
            Can_mob_abort();        // Freed the MOB
            Can_clear_status_mob(); //   and reset MOb status
            rtn_val = CAN_STATUS_COMPLETED;
            break;
        //---------------
        default:
            // Status field of descriptor: (bin)000b.scfa if MOb error
            cmd->status = a_status;
            Can_mob_abort();        // Freed the MOB
            Can_clear_status_mob(); //   and reset MOb status
            rtn_val = CAN_STATUS_ERROR;
            break;
    }
    return (rtn_val);
}















