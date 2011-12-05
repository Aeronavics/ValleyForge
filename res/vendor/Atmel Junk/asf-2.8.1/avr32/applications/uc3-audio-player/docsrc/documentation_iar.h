/*! \addtogroup group_compilation
 *
 * \section iar_jtag IAR + JTAG
 * - Make sure you have the latest `IAR for 32-bit AVR Microcontrollers' installed on your PC.
 *  - If not, an evaluation edition can be downloaded at the following address:
 *    http://www.iar.com/
 * - Plug the JTAGICE mkII between the PC and the EVK using the JTAG connector.
 * - Open `IAR for 32-bit AVR Microcontrollers' and load the associated IAR project of this
 *   application (located in the director /applications/uc3-audio-player/[...]/iar/).
 * - Press the `Debug' button at the top right of the IAR interface.
 *  - The project should compile. Then the generated binary file is downloaded
 *    to the target to finally switch to the debug mode.
 * - Click on the `Go' button in the `Debug' menu or press F5.
 */
