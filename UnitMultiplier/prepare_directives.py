import sys

print("Creating directives file...")

if len(sys.argv) < 6:
    print("usage : python prepare_directives.py latency interval number_of_mults number_of_adders mult_type")
    exit

fo = open("directives.tcl","w+")

latency = sys.argv[1]
interval = sys.argv[2]
number_of_mults = sys.argv[3]
number_of_adders = sys.argv[4]
mult_type = sys.argv[5]

print("Targets:\nLatency : " + latency + "\nInitiation Interval : " + interval + "\nNumber Of Multipliers : " + number_of_mults + "\nNumber Of Adders : " + number_of_adders + "\nMultiplier Type : " + mult_type)

fo.write('set_directive_latency -min ' + str(latency) + ' -max ' + str(latency) + ' "mul"\n')
fo.write('set_directive_pipeline -II ' + str(interval) + ' "mul"\n')
fo.write('set_directive_allocation -limit ' + str(number_of_adders) + ' -type function "mul" add\n')
fo.write('set_directive_allocation -limit ' + str(number_of_mults) + ' -type function "mul" mult\n')
#fo.write('set_directive_resource -core ' + str(mult_type) + ' "mult" return\n')

fo.close()

print("directives.tcl file created!")