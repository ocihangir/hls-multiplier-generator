import subprocess
import os
from shutil import copyfile
import prepare_large_mult_directives
import prepare_large_mult_definition
import UnitMultiplier.prepare_unit_mult_definition
import UnitMultiplier.prepare_unit_mult_directives

# unit_multiplier_latency unit_multiplier_interval unit_multiplier_#mult, unit_multiplier_#add, unit_multiplier_bit_width, 
# large_multiplier_number_of_unit_mults, large_multiplier_latency, large_multiplier_interval, output_width
'''value_range = [[5,2,2,3,64,1,32,2,1024], [5,2,2,3,128,1,32,2,1024], [5,2,2,3,16,1,32,2,1024],[5,2,2,3,32,1,32,2,1024],
               [5,2,2,3,64,2,32,2,1024], [5,2,2,3,128,2,32,2,1024], [5,2,2,3,16,2,32,2,1024],[5,2,2,3,32,2,32,2,1024],
               [5,2,2,3,64,4,32,2,1024], [5,2,2,3,128,4,32,2,1024], [5,2,2,3,16,4,32,2,1024],[5,2,2,3,32,4,32,2,1024],
               [5,2,2,3,64,6,32,2,1024], [5,2,2,3,128,6,32,2,1024], [5,2,2,3,16,6,32,2,1024],[5,2,2,3,32,6,32,2,1024],
               [5,2,2,3,64,8,32,2,1024], [5,2,2,3,128,8,32,2,1024], [5,2,2,3,16,8,32,2,1024],[5,2,2,3,32,8,32,2,1024],
               [5,2,2,3,64,10,32,2,1024],[5,2,2,3,128,10,32,2,1024],[5,2,2,3,16,10,32,2,1024],[5,2,2,3,32,10,32,2,1024],
               [5,2,2,3,64,12,32,2,1024],[5,2,2,3,128,12,32,2,1024],[5,2,2,3,16,12,32,2,1024],[5,2,2,3,32,12,32,2,1024],
               [5,2,2,3,64,14,32,2,1024],[5,2,2,3,128,14,32,2,1024],[5,2,2,3,16,14,32,2,1024],[5,2,2,3,32,14,32,2,1024],
               [5,2,2,3,64,16,32,2,1024],[5,2,2,3,128,16,32,2,1024],[5,2,2,3,16,16,32,2,1024],[5,2,2,3,32,16,32,2,1024],
               [5,2,2,3,64,18,32,2,1024],[5,2,2,3,128,18,32,2,1024],[5,2,2,3,16,18,32,2,1024],[5,2,2,3,32,18,32,2,1024],
               [5,2,2,3,64,20,32,2,1024],[5,2,2,3,128,20,32,2,1024],[5,2,2,3,16,20,32,2,1024],[5,2,2,3,32,20,32,2,1024],
               [5,2,2,3,64,22,32,2,1024],[5,2,2,3,128,22,32,2,1024],[5,2,2,3,16,22,32,2,1024],[5,2,2,3,32,22,32,2,1024],
               [5,2,2,3,64,24,32,2,1024],[5,2,2,3,128,24,32,2,1024],[5,2,2,3,16,24,32,2,1024],[5,2,2,3,32,24,32,2,1024],
               [5,2,2,3,64,26,32,2,1024],[5,2,2,3,128,26,32,2,1024],[5,2,2,3,16,26,32,2,1024],[5,2,2,3,32,26,32,2,1024],
               [5,2,2,3,64,28,32,2,1024],[5,2,2,3,128,28,32,2,1024],[5,2,2,3,16,28,32,2,1024],[5,2,2,3,32,28,32,2,1024],
               [5,2,2,3,64,30,32,2,1024],[5,2,2,3,128,30,32,2,1024],[5,2,2,3,16,30,32,2,1024],[5,2,2,3,32,30,32,2,1024],
               [5,2,2,3,64,32,32,2,1024],[5,2,2,3,128,32,32,2,1024],[5,2,2,3,16,32,32,2,1024],[5,2,2,3,32,32,32,2,1024],
               [5,2,2,3,64,1,32,2,2048], [5,2,2,3,128,1,32,2,2048], [5,2,2,3,256,1,32,2,2048],[5,2,2,3,32,1,32,2,2048],
               [5,2,2,3,64,2,32,2,2048], [5,2,2,3,128,2,32,2,2048], [5,2,2,3,256,2,32,2,2048],[5,2,2,3,32,2,32,2,2048],
               [5,2,2,3,64,4,32,2,2048], [5,2,2,3,128,4,32,2,2048], [5,2,2,3,256,4,32,2,2048],[5,2,2,3,32,4,32,2,2048],
               [5,2,2,3,64,6,32,2,2048], [5,2,2,3,128,6,32,2,2048], [5,2,2,3,256,6,32,2,2048],[5,2,2,3,32,6,32,2,2048],
               [5,2,2,3,64,8,32,2,2048], [5,2,2,3,128,8,32,2,2048], [5,2,2,3,256,8,32,2,2048],[5,2,2,3,32,8,32,2,2048],
               [5,2,2,3,64,10,32,2,2048],[5,2,2,3,128,10,32,2,2048],[5,2,2,3,256,10,32,2,2048],[5,2,2,3,32,10,32,2,2048],
               [5,2,2,3,64,12,32,2,2048],[5,2,2,3,128,12,32,2,2048],[5,2,2,3,256,12,32,2,2048],[5,2,2,3,32,12,32,2,2048],
               [5,2,2,3,64,14,32,2,2048],[5,2,2,3,128,14,32,2,2048],[5,2,2,3,256,14,32,2,2048],[5,2,2,3,32,14,32,2,2048],
               [5,2,2,3,64,16,32,2,2048],[5,2,2,3,128,16,32,2,2048],[5,2,2,3,256,16,32,2,2048],[5,2,2,3,32,16,32,2,2048],
               [5,2,2,3,64,18,32,2,2048],[5,2,2,3,128,18,32,2,2048],[5,2,2,3,256,18,32,2,2048],[5,2,2,3,32,18,32,2,2048],
               [5,2,2,3,64,20,32,2,2048],[5,2,2,3,128,20,32,2,2048],[5,2,2,3,256,20,32,2,2048],[5,2,2,3,32,20,32,2,2048],
               [5,2,2,3,64,22,32,2,2048],[5,2,2,3,128,22,32,2,2048],[5,2,2,3,256,22,32,2,2048],[5,2,2,3,32,22,32,2,2048],
               [5,2,2,3,64,24,32,2,2048],[5,2,2,3,128,24,32,2,2048],[5,2,2,3,256,24,32,2,2048],[5,2,2,3,32,24,32,2,2048],
               [5,2,2,3,64,26,32,2,2048],[5,2,2,3,128,26,32,2,2048],[5,2,2,3,256,26,32,2,2048],[5,2,2,3,32,26,32,2,2048],
               [5,2,2,3,64,28,32,2,2048],[5,2,2,3,128,28,32,2,2048],[5,2,2,3,256,28,32,2,2048],[5,2,2,3,32,28,32,2,2048],
               [5,2,2,3,64,30,32,2,2048],[5,2,2,3,128,30,32,2,2048],[5,2,2,3,256,30,32,2,2048],[5,2,2,3,32,30,32,2,2048],
               [5,2,2,3,64,32,32,2,2048],[5,2,2,3,128,32,32,2,2048],[5,2,2,3,256,32,32,2,2048],[5,2,2,3,32,32,32,2,2048]] #,[5,2,2,3,128,16,1,1],[5,2,2,3,16,16,1,1],[5,2,2,3,32,16,1,1],[1,1,1,1,4,16,1,1],[1,1,1,1,8,16,1,1],[1,1,1,1,16,16,1,1],[1,1,1,1,32,16,1,1],[1,1,4,4,4,16,1,1],[1,1,4,4,8,16,1,1],[1,1,4,4,16,16,1,1],[1,1,4,4,32,16,1,1]]
'''

'''value_range = [[5,2,2,3,32,1,64,2,256],[5,2,2,3,64,1,64,2,512],
                [5,2,2,3,64,1,64,2,256],[5,2,2,3,16,1,64,2,256]]'''
value_range = [[5,2,2,3,256,1,4000,2,4096,1]]
'''for lat in range(1,6):
    for interval in range(1,lat+1):
        for num_of_umult in range(1,5):
            for out_width in [256,512]:
                value_range.append([lat,interval,1,1,32,num_of_umult,64,2,out_width])
                value_range.append([lat,interval,1,2,32,num_of_umult,64,2,out_width])
                value_range.append([lat,interval,1,3,32,num_of_umult,64,2,out_width])
                value_range.append([lat,interval,2,1,32,num_of_umult,64,2,out_width])
                value_range.append([lat,interval,2,2,32,num_of_umult,64,2,out_width])
                value_range.append([lat,interval,2,3,32,num_of_umult,64,2,out_width])
                value_range.append([lat,interval,3,1,32,num_of_umult,64,2,out_width])
                value_range.append([lat,interval,3,2,32,num_of_umult,64,2,out_width])
                value_range.append([lat,interval,3,3,32,num_of_umult,64,2,out_width])
                value_range.append([lat,interval,4,1,32,num_of_umult,64,2,out_width])
                value_range.append([lat,interval,4,2,32,num_of_umult,64,2,out_width])
                value_range.append([lat,interval,4,3,32,num_of_umult,64,2,out_width])
                value_range.append([lat,interval,4,4,32,num_of_umult,64,2,out_width])

                value_range.append([lat,interval,1,1,16,num_of_umult,64,2,out_width])
                value_range.append([lat,interval,1,2,16,num_of_umult,64,2,out_width])
                value_range.append([lat,interval,1,3,16,num_of_umult,64,2,out_width])
                value_range.append([lat,interval,2,1,16,num_of_umult,64,2,out_width])
                value_range.append([lat,interval,2,2,16,num_of_umult,64,2,out_width])
                value_range.append([lat,interval,2,3,16,num_of_umult,64,2,out_width])
                value_range.append([lat,interval,3,1,16,num_of_umult,64,2,out_width])
                value_range.append([lat,interval,3,2,16,num_of_umult,64,2,out_width])
                value_range.append([lat,interval,3,3,16,num_of_umult,64,2,out_width])
                value_range.append([lat,interval,4,1,16,num_of_umult,64,2,out_width])
                value_range.append([lat,interval,4,2,16,num_of_umult,64,2,out_width])
                value_range.append([lat,interval,4,3,16,num_of_umult,64,2,out_width])
                value_range.append([lat,interval,4,4,16,num_of_umult,64,2,out_width])'''


'''lat = 7
interval = 1
numofmult = 1
numofadd = 1
for lat in range(3,8):
    for interval in range(2,lat+1):
        for num_of_umult in range(1,8):
            for out_width in [512]:
                for unit_width in [32,64,128]:
                    value_range.append([lat,interval,numofmult,numofadd,unit_width,num_of_umult,64,2,out_width,num_of_umult])'''
        
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
    large_multiplier_number_of_adders = value[9]
    

    #  prepare_directives.py 5 2 2 3 Mul_LUT
    prepare_large_mult_directives.generate(latency, interval, number_of_mults, number_of_adders, mult_type, large_multiplier_number_of_unit_mults, large_multiplier_latency, large_multiplier_interval, mult_type, large_multiplier_number_of_adders)

    #  prepare_definition.py 16
    prepare_large_mult_definition.generate(large_multiplier_output_width, bit_width / 2)
    #
    UnitMultiplier.prepare_unit_mult_definition.generate(bit_width * 2)

    # vivado_hls -f script.tcl
    subprocess.check_call(["C:/Xilinx/Vivado/2019.2/bin/vivado_hls.bat","-f","script.tcl"])

    # mkdir synthesis_outputs
    try:
        os.mkdir("simulation_outputs")
    except:
        print("Folder is already exist. Skipping.")

    # copy files
    folder = "./simulation_outputs/csynth_"  + str(latency) + "_" + str(interval) + "_" + str(number_of_mults) + "_" + str(number_of_adders) + "_" + str(bit_width) + "_" + str(large_multiplier_number_of_unit_mults) + "_" + str(large_multiplier_latency) + "_" + str(large_multiplier_interval) + "_" + str(large_multiplier_output_width)
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
    src_file = "./mul_prj/solution1/syn/report/csynth.xml"
    dest_file = folder + "/csynth.xml"
    copyfile(src_file, dest_file)
    src_file = "./mul_prj/solution1/syn/report/unit_mult_csynth.xml"
    dest_file = folder + "/unit_mult_csynth.xml"
    copyfile(src_file, dest_file)
    src_file = "./mul_prj/solution1/syn/report/large_mul_csynth.xml"
    dest_file = folder + "/large_mul_csynth.xml"
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
    src_file = "./mul_prj/solution1/syn/report/unit_mult_csynth.rpt"
    dest_file = folder + "/unit_mult_csynth.rpt"
    copyfile(src_file, dest_file)
    src_file = "./mul_prj/solution1/syn/report/large_mul_csynth.rpt"
    dest_file = folder + "/large_mul_csynth.rpt"
    copyfile(src_file, dest_file)
    