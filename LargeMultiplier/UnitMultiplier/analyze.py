import xml.etree.ElementTree as ET
import os
mypath = "./simulation_outputs/"
f = []
for (dirpath, dirnames, filenames) in os.walk(mypath):
    f.extend(dirnames)
    break

print(f)

fo = open("results_analyze.csv","w+")

first = True
for dir in f:
    tree = ET.parse('./simulation_outputs/' + dir + "/mul_csynth.xml")
    root = tree.getroot()
    if first:
        fo.write(dir.replace("_", ",") + "," + root.findall("PerformanceEstimates/SummaryOfTimingAnalysis/EstimatedClockPeriod")[0].tag + "," + root.findall("PerformanceEstimates/SummaryOfOverallLatency/Worst-caseLatency")[0].tag  + "," + root.findall("PerformanceEstimates/SummaryOfOverallLatency/Interval-max")[0].tag  + "," + root.findall("AreaEstimates/Resources/LUT")[0].tag  + "," + root.findall("AreaEstimates/Resources/FF")[0].tag  + "," + root.findall("AreaEstimates/Resources/DSP48E")[0].tag + "\n")
        first = False
    fo.write(dir.replace("_", ",") + "," + root.findall("PerformanceEstimates/SummaryOfTimingAnalysis/EstimatedClockPeriod")[0].text + "," + root.findall("PerformanceEstimates/SummaryOfOverallLatency/Worst-caseLatency")[0].text  + "," + root.findall("PerformanceEstimates/SummaryOfOverallLatency/Interval-max")[0].text  + "," + root.findall("AreaEstimates/Resources/LUT")[0].text  + "," + root.findall("AreaEstimates/Resources/FF")[0].text  + "," + root.findall("AreaEstimates/Resources/DSP48E")[0].text + "\n")
    
    #all_name_elements = root.findall("PerformanceEstimates/SummaryOfTimingAnalysis/EstimatedClockPeriod")[0].text
    #print(all_name_elements)
fo.close()