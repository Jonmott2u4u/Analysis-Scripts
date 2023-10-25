import os
import numpy as np


ch_start = 0    #QDC channel number
ch_stop = 4
ch_step = 1

run_start = 21869
run_stop = 21882
run_step = 1


for channel in np.arange(ch_start,ch_stop+ch_step,ch_step):
    runtext = ""
    for run in np.arange(run_start,run_stop+run_step,run_step):
        runtext += "data/ch0" + str(channel) + "/run_" + str(run) + "_ch0" + str(channel) + ".dat"    
        if run != run_stop:
            runtext += "\n"
    runfile = "ch0" + str(channel) + "_" + str(run_start) + "_" + str(run_stop) + ".dat"
    fout = open("runs/" + runfile, "w")
    fout.write(runtext)
    fout.close()

