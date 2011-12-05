/*!
 * \defgroup group_dsplib_adpcmstreaming IMA/DVI ADPCM WAVE Streaming tool
 * \ingroup group_dsplib_tools
 * \brief This tool permits to send IMA/DVI ADPCM data through the serial port of a computer.
 * It takes in parameter the IMA/DVI ADPCM encoded wav file you want to transfer and if the file is valid,
 * it will cut the file into blocks to send them trough the serial port.
 * The serial port used for transferring the data is the \b COM1 and is configured as follow: \b 57600 \b bauds, \b 8 \b bits, \b no \b parity and \b 1 \b stop \b bit.
 *
 * \section usage Usage
 * To use this tool you have two different ways:
 * -# You can just drag on the binary file the IMA/DVI ADPCM encoded wave file you want to transfer through the serial port.
 * -# Open a command window, go to the sources directory and launch the ADPCM_IMA_DVI.exe file with an argument
 * corresponding to the file path of the ADPCM encoded file you want to send (ADPCM_IMA_DVI.exe toto.wav)
 *
 * Once the transfer is running, the software will tell you about the processing advancement and some useful data about the original wav file.
 * \image html software.gif
 * You can abort the transfer when you want by pressing a key.
 *
 * \section information Information
 * All the files related to this module are located under /avr32/services/dsp/dsplib/utils/program/adpcm_streaming\n
 * In this directory you can find the source code and the binary of this module.\n
 * If you want to change the parameters of the serial port, you just have to modify the constants \b RS232_PORT,
 * \b RS232_BAUD_RATE, \b RS232_BYTE_SIZE, \b RS232_PARITY and \b RS232_STOP_BIT defined at the beginning of the "main.c" file.
 */
