/*!
 * \defgroup group_dsplib_printrealvect Real Vector Visualizator
 * \ingroup group_dsplib_tools
 * \brief This script is used to visualize a fixed-length data buffer from the serial port formatted as follow:
 * \code 1.      0.265445
 * 2.      -0.025633
 * ... \endcode
 * All others pattern lines will be avoided and not included in the visualization.
 * This script is useful to visualize example's results. In a nutshell, it permits to visualize data printed with
 * the dsp16_debug_print_vect and dsp32_debug_print_vect functions.\n
 * This script is a combination of three main programs (\ref group_dsplib_dataget, \ref group_dsplib_dataextract and \ref group_dsplib_dataprint)
 *
 * \section usage Usage
 * The following variables can be modified in the script:
 * - \b COM_PORT: the serial port identifier used (i.e.: COM1).
 * - \b COM_BAUDRATE: the baud rate of the transmission (i.e.: 9600).
 *
 * Then, once launched, the script will wait until a reset has been performed on the target
 * (which means it will wait until the beginning of the transmission to be sure data are well synchronized).
 *
 * \section information Information
 * All the files related to this module are located under /avr32/services/dsp/dsplib/utils/scripts/print_real_vect\n
 */
