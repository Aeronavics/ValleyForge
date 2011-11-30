/*!
 * \defgroup group_dsplib_adpcmencode IMA/DVI ADPCM WAVE File Builder
 * \ingroup group_dsplib_tools
 * \brief This tool is used to build a WAVE file from raw IMA/DVI ADPCM data.
 * It takes in parameter the path of the file containing the raw IMA/DVI ADPCM encoded data and the output file to be generated.
 * This first file must be formatted as follow: the file is a combination of multiple 256-byte blocks that contain in the first
 * 4 bytes the "predicted value" and the "step index" used to encode the following 252-byte of data.
 *
 * \section usage Usage
 * \code ADPCM_IMA_DVI input_file output_file \endcode
 * - The \b input_file argument is the path of the file containing the raw IMA/DVI ADPCM encoded data.
 * - The \b output_file argument is the path of the output WAVE file to be generated.
 *
 * \section information Information
 * All the files related to this module are located under /avr32/services/dsp/dsplib/utils/program/adpcm_encode\n
 * In this directory you can find the source code and the binary of this module.
 */
