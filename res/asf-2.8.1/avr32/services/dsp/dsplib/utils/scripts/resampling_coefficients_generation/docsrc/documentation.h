/*!
 * \defgroup group_dsplib_resamplingcoefficients Re-sampling coefficients generator
 * \ingroup group_dsplib_tools
 * \brief This script is used to generate filter coefficients to feed the re-sampling algorithm.
 *
 * \section usage Usage
 * This script runs with Scilab (http://www.scilab.org/), Scilab is the free software for numerical computation.\n
 * The following variables can be modified in the script:
 * - \b fs_in_hz: Input sampling frequency (i.e.: 44100).
 * - \b fs_out_hz: Output sampling frequency (i.e.: 48000).
 * - \b order: Order of the re-sampling (this is NOT the order of the filter, see the doucmentation about the re-sampling for more information).
 * - \b normalized: If set to 1, the coefficients will be normalized.
 * - \b output_path: Where to store the resulting header file.
 *
 * \section information Information
 * All the files related to this module are located under /avr32/services/dsp/dsplib/utils/scripts/resampling_coefficients_generation\n
 */
