//******************************************************************************
//! @file $RCSfile: flash_boot_lib.c,v $
//!
//! Copyright (c) 2009 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains a set of routines to perform Flash access
//!        for AT90CAN128/64/32 parts
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
#include "flash_boot_lib.h"
#include "flash_boot_drv.h"

//_____ D E F I N I T I O N S __________________________________________________

//_____ F U N C T I O N S ______________________________________________________

//------------------------------------------------------------------------------
//  @fn flash_rd_byte
//!
//! This function allows to read a byte in 64K bytes of Flash memory.
//!
//! @warning: The 64K page setting must be done before (ex: setting
//!           or clearing the RAMPZ register).
//!
//! @param: addr_byte   Address to read the byte in Flash memory.
//!
//! @return:    Value read in the Flash memory.
//------------------------------------------------------------------------------
U8 flash_rd_byte(U16 addr_byte)
{
#if defined(_RAMPZ_IS_USED_)
    U32  far_addr_byte;

    far_addr_byte = (((U32)(RAMPZ))<<16) | ((U32)(addr_byte));
    return (Farflash_rd_byte(far_addr_byte));

#else
    return (Stdflash_rd_byte(addr_byte));

#endif   //- If _RAMPZ_IS_USED_ ...

//    return (Flash_rd_byte(addr_word));
}

//------------------------------------------------------------------------------
//  @fn flash_rd_word
//!
//! This function allows to read a word in 64K bytes of Flash memory.
//!
//! @warning: 1 - The address of the word is an even byte address.
//!           2 - The 64K page setting must be done before (ex: setting
//!               or clearing the RAMPZ register).
//!
//! @param: addr_word   Address to read the word in Flash memory.
//!
//! @return:    Value read in the Flash memory.
//------------------------------------------------------------------------------
U16 flash_rd_word(U16 addr_word)
{
#if defined(_RAMPZ_IS_USED_)
    U32  far_addr_word;

    far_addr_word = (((U32)(RAMPZ))<<16) | ((U32)(addr_word));
    return (Farflash_rd_word(far_addr_word));

#else
    return (Stdflash_rd_word(addr_word));

#endif   //- If _RAMPZ_IS_USED_ ...

//    return (Flash_rd_word(addr_word));
}

//------------------------------------------------------------------------------
//  @fn flash_wr_byte
//!
//! This function allows to write a byte in 64K bytes of Flash memory.
//!
//! @warning: The 64K page setting must be done before (ex: setting
//!           or clearing the RAMPZ register).
//!
//! @param: addr_byte   Address to write the byte in Flash memory.
//!         value       Value to write in the Flash memory.
//!
//! @return none
//------------------------------------------------------------------------------
void flash_wr_byte(U16 addr_byte, U8 value)
{
    flash_wr_block(&value, addr_byte, 1);
}

//------------------------------------------------------------------------------
//  @fn flash_wr_block
//!
//! This function allows to write up to 65535 bytes (64K Bytes-1 byte) in
//! the Flash memory.
//! This function manages alignment issue (byte and page alignments).
//!
//!-----------------------------------------------------------------------------
//! CARE: Bytes to program must be in a different page that flash_wr_block()  ||
//!       function which is dedicated to program them.                        ||
//!       The cause is to program some bytes the following steps are needed:  ||
//!       - Fill_Temporary_Buffer (size=1 page length)                        ||
//!       - Erase_Page                                                        ||
//!       - Program_Page                                                      ||
//!       If the bytes to program are in the page of the function, the step:  ||
//!       Erase_Page --> Program_page is disturbed because blank words are    ||
//!       fetched in place of Program_Page !!!                                ||
//!-----------------------------------------------------------------------------
//!
//! @warning: 1 - This function isn't able to address the fully 64K bytes
//!               but we cannot find in the device a source buffer up to
//!               64K bytes.
//!           2 - The 64K page setting must be done before (ex: setting
//!               or clearing the RAMPZ register).
//!
//! @param: src      Pointer on source buffer (in SRAM).
//!         dest     Destination, start address value in Flash memory where data
//!                  must be written.
//!         byte_nb  Number of bytes to write.
//!
//! @return none
//------------------------------------------------------------------------------
#pragma location ="API_FLASH"
void flash_wr_block(U8* src, U16 dest, U16 byte_nb)
{
U8      save_i_flag;
U16     u16_temp, nb_word;
U16     address;
U16     save_page_addr;

    //--- Special for API's ------------------------
    //- First of all, disabling the Global Interrupt
    save_i_flag = SREG;
    Disable_interrupt();

    //- Compute the start address of the destination page
    address = dest & ~( (U16)(FLASH_PAGE_SIZE-1) );

    //- While there is data to load from source buffer
    while(byte_nb)
    {
        //- Save the page address
        save_page_addr = address;
        //- For each word in this page
        for(nb_word = 0; nb_word < (FLASH_PAGE_SIZE/2); nb_word++)
        {
             //- Reset data word to write
             u16_temp = 0x00;

             //- Still some data to load from source
             if(byte_nb)
             {
                //- Current address is inside the target range address
                if(address >= dest)
                {
                    //- Load MSB of word from buffer source
                    u16_temp |= (U16)(Sram_rd_byte(src));      // Sram_rd_byte(addr) defined in "flash_boot_drv.h"
                    src++; byte_nb--;
                    //- Still (encore) some data to load ?
                    if(byte_nb)
                    {
                        //- Load LSB of word from buffer source
                        u16_temp |= ((U16)(Sram_rd_byte(src))) << 8;  // Sram_rd_byte(addr) defined in "flash_boot_drv.h"
                        src++; byte_nb--;
                    }
                    //- Only the MSB of the working belong to source buffer
                    else
                    {
                        //- Load LSB form existing Flash
                        u16_temp |= ((U16)(flash_rd_byte(address+1))) << 8;
                    }
                }
                //- Current word address out of destination target
                else
                {
                    //- Load MSB from existing Flash
                    u16_temp |= (U16)(flash_rd_byte(address));
                    //- Is LSB word addr in destination range ?
                    if((address+1) == dest)
                    {
                        u16_temp |= ((U16)(Sram_rd_byte(src))) << 8;      // Sram_rd_byte(addr) defined in "flash_boot_drv.h"
                        src++; byte_nb--;
                    }
                    //- LSB read from existing Flash
                    else
                    {
                        u16_temp |= ((U16)(flash_rd_byte(address+1))) << 8;
                    }
                }
            }
            //- Complete the page with words from the Flash content
            else
            {
                u16_temp = flash_rd_word(address);
            }
            flash_fill_temp_buffer(address, u16_temp);
            address += 2;
        }

        //- If the page isn't blank then erase it
        //- It is faster than to systematically erase the page
        address = save_page_addr;
        if ( flash_page_blank_check(save_page_addr) != 0 ) flash_page_erase(save_page_addr);

        //- Write (or program) the page
        flash_page_write(save_page_addr);

        //- First Flash address update for the next page
        address = save_page_addr + FLASH_PAGE_SIZE;

    }
    //- Wait for RWWSB flag cleared
    Flash_rww_section_enable;
    Flash_prog_completed;

    //--- Special for API's ---------------------------
    //- If it was set, re-enabling the Global Interrupt
    if(save_i_flag & 0x80) Enable_interrupt();;

}

//------------------------------------------------------------------------------
//  @fn flash_full_erase
//!
//! This function erases the whole Flash memory. It manages itself the RAMPZ.
//!
//! @warning none
//!
//! @param none
//!
//! @return none
//------------------------------------------------------------------------------
void flash_full_erase(void)

#if defined(_RAMPZ_IS_USED_)
{
U8  save_rampz;
U32 page_nb = 0;

    //- Push RAMPZ
    save_rampz = RAMPZ;

    while ( page_nb < ((U32)(MAX_FLASH_SIZE_TO_ERASE)) )
    {
        RAMPZ = ((U8)(page_nb>>16));
        flash_page_erase((U16)(page_nb));
        page_nb += ((U32)(FLASH_PAGE_SIZE));
    }
    //- Wait for RWWSB flag cleared
    Flash_prog_completed;

    //- Pop RAMPZ
    RAMPZ = save_rampz;
}

#else
{
U16 page_nb = 0;

    while ( page_nb < ((U16)(MAX_FLASH_SIZE_TO_ERASE)) )
    {
        flash_page_erase(page_nb);
        page_nb += ((U16)(FLASH_PAGE_SIZE));
    }
    //- Wait for RWWSB flag cleared
    Flash_prog_completed;
}

#endif

//------------------------------------------------------------------------------
//  @fn flash_page_blank_check
//!
//! This function blank checks a page of Flash memory.
//!
//! @warning: The 64K page setting must be done before (ex: setting or
//!           clearing the RAMPZ register).
//!
//! @param: page_addr   Address in the range page to blank check.
//!
//! @return: 1 - 0000 0000 0000 0000 binary = blank page
//!          2 - 1xxx xxxx xxxx xxxx binaty = first byte address not blank
//!                                           in the page (offset in the page)
//------------------------------------------------------------------------------
U16 flash_page_blank_check(U16 page_addr)
{
U16     u16_temp = 0;
U16     nb_word;

    //- Align the page address
    page_addr = page_addr & ~((U16)(FLASH_PAGE_SIZE - 1));

    //- Blank checking
    for(nb_word = 0; nb_word < (FLASH_PAGE_SIZE/2); nb_word++)
    {
        if( ( flash_rd_word(page_addr) ) != ((U16)(FLASH_BLANK_WORD)) )
        {
            u16_temp = 0x1000;
            //- Exit from blank checking (for(nb_word...)
            break;
        }
    page_addr += 2;
    }

    //- Reporting
    u16_temp = u16_temp |  ( page_addr & ((U16)(FLASH_PAGE_SIZE - 1)) );
    return (u16_temp);
}


