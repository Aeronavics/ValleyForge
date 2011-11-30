/*!
 * \defgroup group_dsplib_adpcmencoder IMA/DVI ADPCM Encoder Script
 * \ingroup group_dsplib_tools
 * \brief This script is used to create an IMA/DVI ADPCM WAVE file with data received from a serial COM port.\n
 * It is a combination of two main programs (\ref group_dsplib_dataget and \ref group_dsplib_adpcmencode)
 *
 * \section usage Usage
 * The following variables can be modified in the script:
 * - \b COM_PORT: the serial port identifier used (i.e.: COM1).
 * - \b COM_BAUDRATE: the baud rate of the transmission (i.e.: 115200).
 * Then, once launched, the script will wait until a reset has been performed on the target
 * (which means it will wait until the beginning of the transmission to be sure data are well synchronized).
 *
 * \section information Information
 * All the files related to this module are located under /avr32/services/dsp/dsplib/utils/scripts/adpcm_encoder\n
 */
