import sys

def generate(unit_multiplier_latency, unit_multiplier_interval, unit_multiplier_number_of_mults, unit_multiplier_number_of_adders, unit_multiplier_mult_type,
            large_multiplier_number_of_unit_multipliers, large_multiplier_latency, large_multiplier_interval, large_multiplier_mult_type, large_multiplier_number_of_adders):
    print("Creating directives file...")

    fo = open("directives.tcl","w+")

    print("Unit Multiplier Targets:\nLatency : " + str(unit_multiplier_latency) + "\nInitiation Interval : " + str(unit_multiplier_interval) + "\nNumber Of Multipliers : " + str(unit_multiplier_number_of_mults) + "\nNumber Of Adders : " + str(unit_multiplier_number_of_adders) + "\nMultiplier Type : " + str(unit_multiplier_mult_type))

    #Unit multiplier directives
    fo.write('set_directive_latency -min ' + str(unit_multiplier_latency) + ' -max ' + str(unit_multiplier_latency) + ' "mul"\n')
    fo.write('set_directive_pipeline -II ' + str(unit_multiplier_interval) + ' "mul"\n')
    fo.write('set_directive_allocation -limit ' + str(unit_multiplier_number_of_adders) + ' -type function "mul" add\n')
    fo.write('set_directive_allocation -limit ' + str(unit_multiplier_number_of_mults) + ' -type function "mul" mult\n')
    #fo.write('set_directive_resource -core ' + str(unit_multiplier_mult_type) + ' "mult" return\n')

    print("Large Multiplier Targets:\nLatency : " + str(large_multiplier_latency) + "\nInitiation Interval : " + str(large_multiplier_interval) + "\nNumber Of Multipliers : " + str(large_multiplier_number_of_unit_multipliers) + "\nMultiplier Type : " + str(large_multiplier_mult_type))

    #Large multiplier directives
    fo.write('set_directive_latency -min ' + str(1) + ' -max ' + str(large_multiplier_latency) + ' "large_mul"\n')
    fo.write('set_directive_pipeline -II ' + str(large_multiplier_interval) + ' "large_mul"\n')
    fo.write('set_directive_allocation -limit ' + str(large_multiplier_number_of_unit_multipliers) + ' -type function "large_mul" unit_mult\n')
    fo.write('set_directive_allocation -limit ' + str(large_multiplier_number_of_adders) + ' -type function "large_mul" adder\n')
    fo.write('set_directive_resource -core ' + large_multiplier_mult_type + ' "large_mul" y\n')

    fo.close()

    print("directives.tcl file created!")

def main():
    if len(sys.argv) < 11:
        print("usage : python prepare_directives.py unit_multiplier_latency unit_multiplier_interval unit_multiplier_number_of_mults unit_multiplier_number_of_adders unit_multiplier_mult_type large_multiplier_number_of_unit_mults large_multiplier_latency large_multiplier_interval large_multiplier_mult_type large_multiplier_number_of_adders")
        exit
    unit_multiplier_latency = sys.argv[1]
    unit_multiplier_interval = sys.argv[2]
    unit_multiplier_number_of_mults = sys.argv[3]
    unit_multiplier_number_of_adders = sys.argv[4]
    unit_multiplier_mult_type = sys.argv[5]
    large_multiplier_number_of_unit_multipliers = sys.argv[6]
    large_multiplier_latency = sys.argv[7]
    large_multiplier_interval = sys.argv[8]
    large_multiplier_mult_type = sys.argv[9]
    large_multiplier_number_of_adders = sys.argv[10]

    generate(unit_multiplier_latency, unit_multiplier_interval, unit_multiplier_number_of_mults, unit_multiplier_number_of_adders, unit_multiplier_mult_type,
            large_multiplier_number_of_unit_multipliers, large_multiplier_latency, large_multiplier_interval, large_multiplier_mult_type, large_multiplier_number_of_adders)

if __name__ == "__main__":
    main()