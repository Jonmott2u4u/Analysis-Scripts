# Analysis-Scripts
Collection of analysis scripts I use

# LangauFitExtract.C & ExtractScanResults.C
Creates Langau fits of the simulated spectra from MOLLEROptical.
Each file has the following differences:
  * ExtractScanResults.C is from an older version that lacked as many scan parameters. Histograms are outputted to the display
  * LangauFitExtract.C is an updated version designed for newer MOLLEROptical versions. Histos are no longer output to display

# segment_scan.C & segment_scan_with_Mainz.C & data_mover.C
Plots parameters such as pe yield, rms, etc. from txt files output by LangauFitExtract/ExtractScanResults 
Fits are performed for certain parameters
Each file has the following differences:
  * segment_scan.C is for use with the newer MOLLEROptical versions. Contains fits for determining average pe yield over a detector's active area
  * with_Mainz is an older version and lacks certain options, but references Mainz 2023 data files for comparison to simulations
  * data_mover.C was made for creating .csv files from the txt files.

# Mainz-data-analysis.C
Creates Gaussian and Langau fits of the photoelectron (PE) yield of MOLLER's integrating Cherenkov detectors.
Data is handled through the following process:
  * The paths of files to be analyzed are written in a .dat file. The script then opens it and individually analyzes each file
  * Information like mean PE's, sigma, MP of a gaussian fit, and gsigma of said fit are stored in a .txt file for future reference
  * The zero-point of the data is moved to the pedestal peak, and the remaining pedestal is cut from the data (this part has to be done by hand depending on the voltage and gain of the PMT used)
  * A langau fit is performed, followed by a gaussian fit based on langau fit parameters (has to be adjusted by hand)
  * Pngs of the langau and gaussian fitted plots are printed and sent to a user-specified location.

# subtraction.C
Functions similarly to Mainz-data-analysis.C, but with a few differences:
  * Designed to subtract one dataset from another after normalizing the distributions
  * Example of use: Data is loaded from two files originating from the same detector with the same electronics setup (voltage, gain, etc), but hitting different regions. Region 1 is some part of the detector (generating a small pulse), whereas region 2 is not hitting the detector (providing a background signal). After normalizing both such that the pedestal peaks on each equal 1, they are subtracted to find the yield of the detector for particles hitting region 1.
  * This was used for signals that could not be easily separated from the background.

# HOW TO RUN - Mainz-data-analysis.C
In filemaker.py, enter the range of QDC channels and range of runs to analyze.
  * This script requires you to have created a folder called "runs" to store the files it makes
  * The file it makes should then be pointed to in Mainz-data-analysis.C

The controls for Mainz-data-analysis.C are listed below:
  * In object FitLanGaus()
    * Line 15: Within rfiles(), enter runs/"file made by filemaker.py". This gets the file that was just made
    * Line 17: In Mainz_dat.open(), enter analyzed_data/"same file as above". This file should be .txt instead of .dat however. You should make an "analyzed_data" folder before running this
    * Line 36: Controls the amplification of the PMT gain
    * pedestal: Pedestal of the data is set here. Adjusting this will change the zero-point of the x-axis. New values should be found for each PMT+base and voltage combination. Set this to be at the pedestal peak
    * gainFactor: The gainFactor can be adjusted depending on the analysis method. If gainPMT is not defined, use gainFactor = 1, else use the line above it
    * cut: Removes remaining pedestal data from the plot. Should only be non-zero after finding the pedestal peak
    * run_number: Ajust the channel nummber within its definition to match whatever file you're analyzing
    * fr[0], fr[1]: Controls the fitting ranges for the langau and gaussian fits
    * multi_plot: The plot where data is displayed. In multi_plot->SaveAs(), insert plots/"file made"/, but without any file extensions (.txt, .dat, etc). A "plots" directory should be made before running this
  * In object langaufun()
    * np: Controls how many steps the fit takes when looking over the data. 100 runs quickly and is useful for determining pedestal and cut, but should be between 1000->10000 for more precise fits (once all the parameters are known).