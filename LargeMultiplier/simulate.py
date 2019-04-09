import subprocess
import os
from shutil import copyfile

# unit_multiplier_latency unit_multiplier_interval unit_multiplier_#mult, unit_multiplier_#add, unit_multiplier_bit_width, large_multiplier_number_of_unit_mults, large_multiplier_latency, large_multiplier_interval, output_width
value_range = [[5,2,2,3,1,1,1,1,64]] #,[5,2,2,3,8,16,1,1],[5,2,2,3,16,16,1,1],[5,2,2,3,32,16,1,1],[1,1,1,1,4,16,1,1],[1,1,1,1,8,16,1,1],[1,1,1,1,16,16,1,1],[1,1,1,1,32,16,1,1],[1,1,4,4,4,16,1,1],[1,1,4,4,8,16,1,1],[1,1,4,4,16,16,1,1],[1,1,4,4,32,16,1,1]]

#bit_width_range = [4, 8, 16, 32, 64]
#latency_range = [8, 7, 6, 5, 4, 3, 2, 1]
#interval_range = [8, 7, 6, 5, 4, 3, 2, 1]
#number_of_mults_range = [1, 2, 3, 4, 5]
#number_of_adders_range = [1, 2, 3, 4, 5]

for value in value_range:

    latency = value[0]
    interval = value[1]
    number_of_mults = value[2]
    number_of_adders = value[3]
    bit_width = value[4]
    large_multiplier_number_of_unit_mults = value[5]
    large_multiplier_latency = value[6]
    large_multiplier_interval = value[7]
    large_multiplier_output_width = value[8]
    mult_type = "Mul_LUT"

    

    # python prepare_directives.py 5 2 2 3 Mul_LUT
    subprocess.check_call(["python","prepare_directives.py", str(latency), str(interval), str(number_of_mults), str(number_of_adders), mult_type, str(large_multiplier_number_of_unit_mults), str(large_multiplier_latency), str(large_multiplier_interval), mult_type])

    # python prepare_definition.py 16
    subprocess.check_call(["python","prepare_definition.py", str(large_multiplier_output_width), str(bit_width)])

    #
    subprocess.check_call(["python","../UnitMultiplier/prepare_definition.py", str(bit_width * 4)])

    # vivado_hls -f script.tcl
    subprocess.check_call(["D:/Xilinx/Vivado/2018.2/bin/vivado_hls.bat","-f","script.tcl"])

    # mkdir synthesis_outputs
    try:
        os.mkdir("simulation_outputs")
    except:
        print("Folder is already exist. Skipping.")

    # copy files
    folder = "./simulation_outputs/csynth_"  + str(latency) + "_" + str(interval) + "_" + str(number_of_mults) + "_" + str(number_of_adders) + "_" + str(bit_width) + "_" + str(large_multiplier_number_of_unit_mults) + "_" + str(large_multiplier_latency) + "_" + str(large_multiplier_interval)
    try:
        os.mkdir(folder)
    except:
        print("Folder is already exist. Skipping.")
    src_file = "./mul_prj/solution1/syn/report/mul_csynth.xml"
    dest_file = folder + "/mul_csynth.xml"
    copyfile(src_file, dest_file)
    src_file = "./mul_prj/solution1/syn/report/add_csynth.xml"
    dest_file = folder + "/add_csynth.xml"
    copyfile(src_file, dest_file)
    src_file = "./mul_prj/solution1/syn/report/mult_csynth.xml"
    dest_file = folder + "/mult_csynth.xml"
    copyfile(src_file, dest_file)
    src_file = "./mul_prj/solution1/syn/report/mult_csynth.xml"
    dest_file = folder + "/mult_csynth.xml"
    copyfile(src_file, dest_file)

    src_file = "./mul_prj/solution1/syn/report/mul_csynth.rpt"
    dest_file = folder + "/mul_csynth.rpt"
    copyfile(src_file, dest_file)
    src_file = "./mul_prj/solution1/syn/report/add_csynth.rpt"
    dest_file = folder + "/add_csynth.rpt"
    copyfile(src_file, dest_file)
    src_file = "./mul_prj/solution1/syn/report/mult_csynth.rpt"
    dest_file = folder + "/mult_csynth.rpt"
    copyfile(src_file, dest_file)
    