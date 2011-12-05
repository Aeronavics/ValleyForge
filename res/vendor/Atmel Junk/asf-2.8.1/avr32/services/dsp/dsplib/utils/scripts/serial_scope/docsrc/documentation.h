/*!
 * \defgroup group_dsplib_serialscope Serial Scope
 * \ingroup group_dsplib_tools
 * \brief This script is used to visualize a data stream from the serial port formatted as follow:
 * \code 0.265445
 * -0.025633
 * ... \endcode
 * \image html scope.gif
 * This script is a combination of two main programs (\ref group_dsplib_dataget and \ref group_dsplib_dataprint)
 *
 * \section usage Usage
 * \code scope [-port portname] [-speed baudrate] \endcode
 * - The \b -port portname argument is used to set the name of the port used to receive data.
 * - The \b -speed baudrate argument fixed the speed of the communication.
 *
 * You can also directly modify two parameters in the script:
 * - \b COM_PORT: the serial port identifier used (i.e.: COM1).
 * - \b COM_BAUDRATE: the baud rate of the transmission (i.e.: 9600).
 *
 * Once launched, the script will wait until a reset has been performed on the target
 * (which means it will wait until the beginning of the transmission to be sure data are well synchronized).
 *
 * \section information Information
 * All the files related to this module are located under /avr32/services/dsp/dsplib/utils/scripts/serial_scope\n
 */
