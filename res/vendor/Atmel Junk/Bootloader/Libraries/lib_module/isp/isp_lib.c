//******************************************************************************
//! @file $RCSfile: isp_lib.c,v $
//!
//! Copyright (c) 2009 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains ISP routines available for AT90CAN128/64/32
//!        & ATmega16M1/32M1/32C1/64M1/64C1.
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
#include "isp_lib.h"
#include "flash_boot_lib.h"
#include "eeprom_lib.h"

//_____ D E F I N I T I O N S __________________________________________________

//_____ S P E C I A L   D E C L A R A T I O N S ________________________________

//----------------------------------------------------------------------------..
// CARE: The BOOT_CONF array must be in a different page that the function    ||
//       which is dedicated to program it (ex: flash_wr_block() function)     ||
//       The cause is to program some bytes the following steps are needed:   ||
//       - Fill_Temporary_Buffer (size=1 page length)                         ||
//       - Erase_Page                                                         ||
//       - Program_Page                                                       ||
//       If the bytes to program are in the page of the function, the step:   ||
//       Erase_Page --> Program_page is disturbed because blank words are     ||
//       fetched in place of  Program_Page !!!                                ||
//----------------------------------------------------------------------------''
#pragma location ="BOOT_CONF"
U8   _BOOT_CONF_TYPE_  boot_conf[]  = {
            BSB_DEFAULT , SSB_DEFAULT , EB_DEFAULT ,
            BTC1_DEFAULT, BTC2_DEFAULT, BTC3_DEFAULT,
            NNB_DEFAULT,  CRIS_DEFAULT,
            SA_H_DEFAULT, SA_L_DEFAULT               };

//_____ D E C L A R A T I O N S ________________________________________________

U8          isp_select_memory;
U8          isp_select_page;

U16         isp_start_address;
U16         isp_number_of_bytes;   // 0x0001=1 byte up to 0xFFFF=65535 bytes
U16         isp_start_address_copy;
U16         isp_number_of_bytes_copy;

Bool        isp_prog_on_going;

U8   boot_conf_default[]  = {
            BSB_DEFAULT , SSB_DEFAULT , EB_DEFAULT ,
            BTC1_DEFAULT, BTC2_DEFAULT, BTC3_DEFAULT,
            NNB_DEFAULT,  CRIS_DEFAULT,
            SA_H_DEFAULT, SA_L_DEFAULT               };


//_____ F U N C T I O N S ______________________________________________________

//------------------------------------------------------------------------------
//  @fn isp_jump_to
//!
//! This function analyzes the "jump to" comming from ISP PROTOCOL.
//!
//! @warning none
//!
//! @param:  jump_addr  Addresse to jump to
//!
//! @return none
//!
//------------------------------------------------------------------------------
void  isp_jump_to(U16 jump_addr)
{
    if (jump_addr <= ((FLASHEND - BOOT_LOADER_SIZE)>>1) )
    {
        Indirect_jump_to(jump_addr);   // Start application
    }
    else
    {
        Direct_jump_to_zero();        // Start application at address 0x00000
    }
}

//------------------------------------------------------------------------------
//  @fn isp_set_memory
//!
//! This function analyzes and set the memory code comming from ISP PROTOCOL.
//!
//! @warning none
//!
//! @param:  mem_code  Memory Code (from 0 to MEM_DEF_MAX)
//!
//! @return none
//!
//------------------------------------------------------------------------------
void  isp_set_memory(U8 mem_code)
{
    isp_select_memory = mem_code;
}

//------------------------------------------------------------------------------
//  @fn isp_set_page
//!
//! This function analyzes and set the page number comming from ISP PROTOCOL.
//!
//! @warning Only Flash Memory Space can have page number != 0
//!
//! @param:  page_nb  Page number
//!
//! @return none
//!
//------------------------------------------------------------------------------
void  isp_set_page(U8 page_nb)
{
    isp_select_page = page_nb;
}

//------------------------------------------------------------------------------
//  @fn isp_address_range
//!
//! This function analyzes and set the "isp_start_address" inside 64K range
//! and the "isp_number_of_bytes" comming from ISP PROTOCOL.
//!
//! @warning: 1 - "isp_start_address" inside 64K range
//!           2 - "isp_number_of_bytes": 0x0001=1 byte up to 0xFFFF=65535
//!                bytes
//!
//! @param:  start_addr = start address byte inside 64K range
//!          end_addr   = end address byte inside 64K range
//!
//! @return none
//!
//------------------------------------------------------------------------------
void  isp_address_range(U16 start_addr, U16 end_addr)
{
    isp_start_address = start_addr;
    isp_number_of_bytes = (end_addr - start_addr) + 1;
}

//------------------------------------------------------------------------------
//  @fn isp_memory_erase
//!
//! This function performes a full erase (if it is possible) of the memory
//! selected, code number comming from ISP PROTOCOL.
//!
//! @warning: 1 - Some of memories are "READ Only"
//!           2 - Erasing the Flash Memory sets "SSB" (Software Security Byte)
//!               to "SSB_NO_SECURITY"
//!           3 - Boot Loader Configuration is erased with "Default Boot
//!               Loader Configuration" (controled by "SSB").
//!           2 - Each erasing is controled by "SSB".
//!           3 - Boot Loader Configuration erased with "Default Boot Loader
//!
//! @param  none
//!
//! @return: FALSE (0) = Command failed (Security set) or "READ Only" memory targeted
//!          TRUE  (1) = Command available
//!
//------------------------------------------------------------------------------
Bool  isp_memory_erase(void)
{
Bool    rtn = 1;

    switch (isp_select_memory)
    {

    //- FLASH MEMORY -----------------------------------------------------------
        case (MEM_FLASH):
            flash_full_erase();

#           if defined(_RAMPZ_IS_USED_)
                RAMPZ = 1;
#           endif   //- If _RAMPZ_IS_USED_ ...

            flash_wr_byte((U16)(&SSB), SSB_NO_SECURITY); //- Warning[Pe767]: conversion from pointer to smaller integer

#           if defined(_RAMPZ_IS_USED_)
                RAMPZ = isp_select_page;
#           endif   //- If _RAMPZ_IS_USED_ ...

            break;

    //- EEPROM MEMORY ----------------------------------------------------------
        case (MEM_EEPROM):
            if(SSB == SSB_NO_SECURITY)
            {
                eeprom_full_erase();
            }
            else rtn=0;

#           if defined(_RAMPZ_IS_USED_) //- CARE: Hereunder SSB test can destroy RAMPZ
                RAMPZ = isp_select_page;
#           endif   //- If _RAMPZ_IS_USED_ ...

            break;

    //- BOOT LOADER CONFIGURATION ----------------------------------------------
        case (MEM_BOOT_CONF):
            if(SSB == SSB_NO_SECURITY)
            {
#               if defined(_RAMPZ_IS_USED_)
                    RAMPZ = 0x01;
#               endif   //- If _RAMPZ_IS_USED_ ...

                flash_wr_block(boot_conf_default, (U16)(boot_conf), BOOT_CONF_SIZE);    //- Warning[Pe767]: conversion from pointer to smaller integer

#               if defined(_RAMPZ_IS_USED_)
                    RAMPZ = isp_select_page;
#               endif   //- If _RAMPZ_IS_USED_ ...
            }
            else rtn=0;
            break;

    //- OTHERS ARE "READ ONLY" -------------------------------------------------
        default:
            rtn = 0;
            break;

    }   // switch (isp_sel...
    return(rtn);
}

//------------------------------------------------------------------------------
//  @fn isp_read_block
//!
//! This function performes a read of "isp_number_of_bytes" of bytes, block
//! by block (size of buffer passed as parameter) on the selected memory
//! ("isp_select_memory") and in the selected page ("isp_select_page") from
//! "isp_start_address".
//!
//! @warning:  This function works on copies of "isp_start_address" and
//!            "isp_number_of_bytes" according with the size of the buffer
//!            passed as parameter. In fact, the calling function is in
//!            charge of manage copies for restoring initial values.
//!
//! @param: - isp_buffer = block for output data
//!         - size = size of isp_buffer
//!
//! @return: 0x00 = "isp_read_block()" block available and transfer
//!                  not finished.
//!          0x01 = "isp_read_block()" last block, then "isp_number_of_bytes"
//!                  is equal to size of this last block.
//!          0xFF = Software Security Byte Set, read not available.
//!
//------------------------------------------------------------------------------
U8  isp_read_block(U8* isp_buffer, U16 size)
{
U16  i;
U8  rtn = 0x00;

    switch (isp_select_memory)
    {

    //- FLASH MEMORY -----------------------------------------------------------
        case (MEM_FLASH):
            if( (SSB == SSB_NO_SECURITY) || (SSB == SSB_WR_PROTECTION) )
            {
#               if defined(_RAMPZ_IS_USED_) //- CARE: Hereunder SSB test can destroy RAMPZ
                    RAMPZ = isp_select_page;
#               endif   //- If _RAMPZ_IS_USED_ ...

                if (size !=0)   //- Not 64K
                {
                    size = Min (size, isp_number_of_bytes); //- Macro in "compiler.h"
                }
                for (i=0; i< size; i++)
                {
                    isp_buffer[i] = flash_rd_byte(isp_start_address);
                    isp_start_address++;
                    isp_number_of_bytes--;
                }
                if (isp_number_of_bytes == 0)
                {
                    isp_number_of_bytes = size;
                    rtn = 0x01;
                }
            }
            else rtn = 0xFF;
            break;

    //- EEPROM MEMORY ----------------------------------------------------------
        case (MEM_EEPROM):
            if( (SSB == SSB_NO_SECURITY) || (SSB == SSB_WR_PROTECTION) )
            {
#               if defined(_RAMPZ_IS_USED_) //- CARE: Hereunder SSB test can destroy RAMPZ
                    RAMPZ = isp_select_page;
#               endif   //- If _RAMPZ_IS_USED_ ...

                size = Min (size, isp_number_of_bytes); //- Macro in "compiler.h"
                for (i=0; i< size; i++)
                {
                    isp_buffer[i] = eeprom_rd_byte(isp_start_address);
                    isp_start_address++;
                    isp_number_of_bytes--;
                }
                if (isp_number_of_bytes == 0)
                {
                    isp_number_of_bytes = size;
                    rtn = 0x01;
                }
            }
            else rtn = 0xFF;
            break;

    //- DEVICE SIGNATURE -------------------------------------------------------
        case (MEM_SIGNATURE):   //-  (MAX 4 Bytes)
            size = Min (size, isp_number_of_bytes); //- Macro in "compiler.h"
            for (i=0; i< size; i++)
            {
                if      ( isp_start_address == 0 ) isp_buffer[i] = MANUF_ID;
                else if ( isp_start_address == 1 ) isp_buffer[i] = FAMILY_CODE;
                else if ( isp_start_address == 2 ) isp_buffer[i] = PRODUCT_NAME;
                else                               isp_buffer[i] = PRODUCT_REV;

                isp_start_address++;
                isp_number_of_bytes--;
            }
            if (isp_number_of_bytes == 0)
            {
                isp_number_of_bytes = size;
                rtn = 0x01;
            }
            break;

    //- BOOT LOADER INFORMATION ------------------------------------------------
        case (MEM_BOOT_INF):    //-  (MAX 3 Bytes)
            size = Min (size, isp_number_of_bytes); //- Macro in "compiler.h"
            for (i=0; i< size; i++)
            {
                if      ( isp_start_address == 0 ) isp_buffer[i] = BOOT_VERSION;
                else if ( isp_start_address == 1 ) isp_buffer[i] = BOOT_ID1;
                else                               isp_buffer[i] = BOOT_ID2;

                isp_start_address++;
                isp_number_of_bytes--;
            }
            if (isp_number_of_bytes == 0)
            {
                isp_number_of_bytes = size;
                rtn = 0x01;
            }
            break;

    //- BOOT LOADER CONFIGURATION ----------------------------------------------
        case (MEM_BOOT_CONF):
            size = Min (size, isp_number_of_bytes); //- Macro in "compiler.h"
            for (i=0; i< size; i++)
            {
                isp_buffer[i] = boot_conf[isp_start_address];
                isp_start_address++;
                isp_number_of_bytes--;
            }
            if (isp_number_of_bytes == 0)
            {
                isp_number_of_bytes = size;
                rtn = 0x01;
            }
#           if defined(_RAMPZ_IS_USED_) //- CARE: Hereunder boot_conf[] accesses can destroy RAMPZ
                RAMPZ = isp_select_page;
#           endif   //- If _RAMPZ_IS_USED_ ...

            break;

    //- DEVICE REGISTERS -------------------------------------------------------
        case (MEM_HW_REG):
            size = Min (size, isp_number_of_bytes); //- Macro in "compiler.h"
            for (i=0; i< size; i++)
            {
                isp_buffer[i] = REGISTER_BYTE_AT(isp_start_address);
                isp_start_address++;
                isp_number_of_bytes--;
            }
            if (isp_number_of_bytes == 0)
            {
                isp_number_of_bytes = size;
                rtn = 0x01;
            }
             break;

    //- NO MORE TYPE OF MEMORY -------------------------------------------------
        default:
            rtn = 0xFF;
            break;

    }   // switch (isp_sel...
    return(rtn);
}

//------------------------------------------------------------------------------
//  @fn isp_blank_check
//!
//! This function performes a blank check of "isp_number_of_bytes" of bytes
//! on the selected memory ("isp_select_memory") and in the selected page
//! ("isp_select_page") from "isp_start_address".
//!
//! @warning  none
//!
//! @param  none
//!
//! @return: TRUE  (1) = no error, memory range blank.
//!          FALSE (0) = "isp_blank_check()" error, then "isp_start_address"
//!                       is equal to the address of the first byte not blank.
//!
//------------------------------------------------------------------------------
Bool  isp_blank_check(void)
{
Bool    rtn = TRUE;

    switch (isp_select_memory)
    {

    //- FLASH MEMORY -----------------------------------------------------------
        case (MEM_FLASH):
#           if defined(_RAMPZ_IS_USED_)
                RAMPZ = isp_select_page;
#           endif   //- If _RAMPZ_IS_USED_ ...
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//- Modification -
//================
//- JT 13-Apr-2006
//- Transform "for(...;...;...)" in "while(1)" to manage up to 64K
//-
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
            while(1) //- Special for computing up to 64K
            {
                if ( (flash_rd_byte(isp_start_address)) != ((U8)(FLASH_BLANK_WORD)) )
                {
                    rtn = FALSE;
                    break;  //- Exit from: for (....
                }
                isp_start_address++;
                isp_number_of_bytes--;
                if (isp_number_of_bytes == 0) break;  //- Std Exit from: while(....
            }
            break;

    //- EEPROM MEMORY ----------------------------------------------------------
        case (MEM_EEPROM):
            while(1)
            {
                if ( (eeprom_rd_byte(isp_start_address)) != EEPROM_BLANK_BYTE )
                {
                    rtn = FALSE;
                    break;  //- Exit from: for (....
                }
                isp_start_address++;
                isp_number_of_bytes--;
                if (isp_number_of_bytes == 0) break;  //- Std exit from: while(....
            }
            break;

    //- BOOT LOADER CONFIGURATION ----------------------------------------------
        case (MEM_BOOT_CONF):
            while(1)
            {

#               if defined(_RAMPZ_IS_USED_)
                    RAMPZ = 0x01;
#               endif   //- If _RAMPZ_IS_USED_ ...
                if ( boot_conf[isp_start_address] != boot_conf_default[isp_start_address] )
                {
                    rtn = FALSE;
                    break;  //- Exit from: for (....
                }
                isp_start_address++;
                isp_number_of_bytes--;
                if (isp_number_of_bytes == 0) break;  //- Std exit from: while(....
            }
#           if defined(_RAMPZ_IS_USED_) //- CARE: Hereunder boot_conf[] accesses can destroy RAMPZ
                RAMPZ = isp_select_page;
#           endif   //- If _RAMPZ_IS_USED_ ...

            break;

    //- OTHERS ARE EQUAL TO THEIR DEFINITION -----------------------------------
        default:
            break;

    }   // switch (isp_sel...
    return(rtn);
}

//------------------------------------------------------------------------------
//  @fn isp_prog_block
//!
//! This function performes a programmation of "isp_number_of_bytes" of bytes,
//! block by block (size of buffer passed as parameter) on the selected
//! memory ("isp_select_memory") and in the selected page ("isp_select_page")
//! from "isp_start_address".
//!
//! @warning:  This function works with "isp_start_address" and
//!            "isp_number_of_bytes" according with the size of the buffer
//!            passed as parameter. In fact, the calling function is in
//!            charge of manage copies for restoring initial values.
//!
//! @param: - isp_buffer = block for input data
//!         - size = size of isp_buffer
//!
//! @return: 0x00 = "isp_prog_block()" block programming completed and transfer
//!                  not finished.
//!          0x01 = "isp_prog_block()" last block, then "isp_number_of_bytes"
//!                  is equal to size of this last block.
//!          0xFF = Software Security Byte Set, write not available.
//!
//------------------------------------------------------------------------------
U8  isp_prog_block(U8* isp_buffer, U16 size)
{
U8  rtn = 0x00;

    switch (isp_select_memory)
    {

    //- FLASH MEMORY -----------------------------------------------------------
        case (MEM_FLASH):
            if( SSB == SSB_NO_SECURITY )
            {
#               if defined(_RAMPZ_IS_USED_) //- CARE: Hereunder SSB test can destroy RAMPZ
                    RAMPZ = isp_select_page;
#               endif   //- If _RAMPZ_IS_USED_ ...

                //- It is not neccessary to check size (as for read) because
                //- the host send exactly what it is needed
                flash_wr_block(isp_buffer, isp_start_address, size);

                isp_start_address += size;
                isp_number_of_bytes -= size;

                if (isp_number_of_bytes == 0) rtn = 0x01;
            }
            else rtn = 0xFF;
            break;

    //- EEPROM MEMORY ----------------------------------------------------------
        case (MEM_EEPROM):
            if( SSB == SSB_NO_SECURITY )
            {
#               if defined(_RAMPZ_IS_USED_) //- CARE: Hereunder SSB test can destroy RAMPZ
                    RAMPZ = isp_select_page;
#               endif   //- If _RAMPZ_IS_USED_ ...

                //- It is not neccessary to check size (as for read) because
                //- the host send exactly what it is needed

                eeprom_wr_block(isp_buffer, isp_start_address, size);

                isp_start_address += size;
                isp_number_of_bytes -= size;

                if (isp_number_of_bytes == 0) rtn = 0x01;
            }
            else rtn = 0xFF;
            break;

    //- BOOT LOADER CONFIGURATION ----------------------------------------------
        case (MEM_BOOT_CONF):
#           if defined(_RAMPZ_IS_USED_)
                RAMPZ = 0x01;
#           endif   //- If _RAMPZ_IS_USED_ ...

            //- It is not neccessary to check size (as for read) because
            //- the host send exactly what it is needed

            if( SSB == SSB_NO_SECURITY )
            {
                flash_wr_block(isp_buffer, ( isp_start_address + ((U16)(boot_conf)) ), size);    //- Warning[Pe767]: conversion from pointer to smaller integer

                isp_start_address += size;
                isp_number_of_bytes -= size;

                if (isp_number_of_bytes == 0) rtn = 0x01;
            }
            else if ( (SSB == SSB_WR_PROTECTION) && \
                      (isp_start_address == SSB_INDEX) && \
                      (size == 1) && (isp_buffer[0] == SSB_RD_WR_PROTECTION ) )
            {
                flash_wr_byte(((U16)(&SSB)), SSB_RD_WR_PROTECTION); //- Warning[Pe767]: conversion from pointer to smaller integer
                rtn = 0x01;
            }
            else rtn = 0xFF;

#           if defined(_RAMPZ_IS_USED_)
                RAMPZ = isp_select_page;
#           endif   //- If _RAMPZ_IS_USED_ ...

            break;

    //- NO MORE TYPE OF MEMORY IN WRITE ACCESS ---------------------------------
        default:
            rtn = 0xFF;
            break;

    }   // switch (isp_sel...
    return(rtn);
}

