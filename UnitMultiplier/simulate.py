import subprocess
import os
from shutil import copyfile

# latency interval #mult, #add, bit_width
value_range = [ [4,2,4,4,4],[4,2,4,4,8],[4,2,4,4,16],[4,2,4,4,32],
                [4,2,3,3,4],[4,2,3,3,8],[4,2,3,3,16],[4,2,3,3,32],
                [4,2,2,2,4],[4,2,2,2,8],[4,2,2,2,16],[4,2,2,2,32],
                [4,2,1,1,4],[4,2,1,1,8],[4,2,1,1,16],[4,2,1,1,32]]


print(value_range)
print("size : ", len(value_range))
#exit()

#bit_width_range = [3, 8, 16, 32, 64]
#latency_range = [8, 7, 6, 5, 4, 3, 2, 1]
#interval_range = [8, 7, 6, 5, 4, 3, 2, 1]
#number_of_mults_range = [1, 2, 3, 4, 5]
#number_of_adders_range = [1, 2, 3, 4, 5]

for value in value_range:

    latency = value[0]
    interval = value[1]
    number_of_mults = value[2]
    number_of_adders = value[3]
    mult_type = "Mul_LUT"

    bit_width = value[4]

    # python prepare_directives.py 5 2 2 3 Mul_LUT
    subprocess.check_call(["python","prepare_directives.py", str(latency), str(interval), str(number_of_mults), str(number_of_adders), mult_type])

    # python prepare_definition.py 16
    subprocess.check_call(["python","prepare_definition.py", str(bit_width)])

    # vivado_hls -f script.tcl
    subprocess.check_call(["D:/Xilinx/Vivado/2018.2/bin/vivado_hls.bat","-f","script.tcl"])

    # mkdir synthesis_outputs
    try:
        os.mkdir("simulation_outputs")
    except:
        print("Folder is already exist. Skipping.")

    # copy files
    folder = "./simulation_outputs/csynth_"  + str(latency) + "_" + str(interval) + "_" + str(number_of_mults) + "_" + str(number_of_adders) + "_" + str(bit_width)
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
    