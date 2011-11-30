/*! \addtogroup group_compilation
 *
 * \section gcc_jtag Stand-alone GCC + JTAG
 * - The GNU Toolchain for 32-bit AVR Microcontrollers must be preliminary installed.
 *  - If not, please download it and install it from the following link:
 *    http://www.atmel.com/dyn/products/tools_card.asp?tool_id=4118
 * - Plug the JTAGICE mkII between the PC and the EVK using the JTAG connector.
 * - Open a shell.
 * - Go to the /applications/uc3-audio-player/[...]/gcc/ directory and type:
 *  \code `make rebuild program run' \endcode
 *
 * \section gcc_bootloader Stand-alone GCC + USB DFU BOOTLOADER
 * - The GNU Toolchain for 32-bit AVR Microcontrollers must be preliminary installed.
 *  - If not, please download it and install it from the following link:
 *    http://www.atmel.com/dyn/products/tools_card.asp?tool_id=4118
 * - Make sure the USB power cable is plugged on the left USB port of the board (USB USER).
 * - Open a shell.
 * - Go to the /applications/uc3-audio-player/[...]/gcc/ directory and type:
 *  \code `make rebuild isp program run' \endcode
 *
 * \section avr32studio AVR32Studio
 * - See "AVR32769: How to Compile the standalone AVR32 Software Framework in AVR32 Studio V2".
 */
