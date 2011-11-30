/*!
 * \defgroup group_dsplib_dataextract Data Extraction
 * \ingroup group_dsplib_tools
 * \brief This program is used to extract data from a buffer and print them with the following format on the standard output.
 * \code 0.1545211
 * -0.5892455
 * ... \endcode
 * It parses every line of the input buffer and check if it matches with the given pattern (gave in argument to this program).
 * If it does, it will extract the specified data from the buffer and print it, else it will ignore the line.
 *
 * \section usage Usage
 * \code DataExtract input_buffer_file_path pattern n_arg \endcode
 * - The \b input_buffer_file_path argument is the file path of the input buffer.
 * - The \b pattern argument is the pattern used to parse the line. This pattern is uses the same syntax as the printf function.
 * Example: if you want to parse a complex number, you will have to use the following pattern: "%f + %fi".
 * - The \b n_arg argument specifies the index of the number to extract form the previously defined pattern.
 *
 * Usage example:\n
 * To extract the 2nd number of a file which lines are defined as follow: integer float integer
 * \code DataExtract ./buffer.txt "%i %f %i" 2 \endcode
 *
 * \section information Information
 * All the files related to this module are located under /avr32/services/dsp/dsplib/utils/program/data_extract\n
 * In this directory you can find the source code and the binary of this module.
 */
