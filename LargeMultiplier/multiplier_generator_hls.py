
import math
import sys

def sort_by_weight(reg):
        return reg.position

def number_of_registers_in_position(reg_list, position):
    cnt = 0
    for reg in reg_list:
        if reg.is_at_position(position):
            cnt = cnt + 1
    return cnt

class LargeMultiplierGenerator(object):
    def __init__(self, op1_size, op2_size, unit_mult_size):
        print("Generating multiplier to multiplier.gen file...")
        self.output_file = open("multiplier.gen","w+")
        self.generate_input_registers(op1_size, op2_size, unit_mult_size)
        self.generate_mults(self.input_registers_1, self.input_registers_2, unit_mult_size)
        self.output_file.close()

    def generate_input_registers(self, op1_size, op2_size, unit_mult_size):
        self.input_registers_1 = []
        self.input_registers_2 = []

        number_of_operands1 = int( math.ceil(op1_size / unit_mult_size) )
        number_of_operands2 = int( math.ceil(op2_size / unit_mult_size) )

        for i in range(0, number_of_operands1):
            self.input_registers_1.append(Register(unit_mult_size, i * unit_mult_size))

        for i in range(0, number_of_operands2):
            self.input_registers_2.append(Register(unit_mult_size, i * unit_mult_size))
    
    def generate_mults(self, input_registers_1, input_registers_2, unit_mult_size):
        self.unit_mults = []

        for reg1 in input_registers_1:
            for reg2 in input_registers_2:
                self.unit_mults.append(NodeMultiplier(reg1, reg2, reg1.position + reg2.position, unit_mult_size))

        ind = 0
        used_mults = []
        self.mult_pos = []

        self.output_file.write("\n")

        for i in range(0,len(self.input_registers_1)):
            self.output_file.write("uintlhalf in_op0_" + str(i * unit_mult_size) + " = a.range(" + str((i + 1) * unit_mult_size - 1) + "," + str(i * unit_mult_size) + ");\n")

        self.output_file.write("\n")

        for i in range(0,len(self.input_registers_2)):
            self.output_file.write("uintlhalf in_op1_" + str(i * unit_mult_size) + " = b.range(" + str((i + 1) * unit_mult_size - 1) + "," + str(i * unit_mult_size) + ");\n")

        self.output_file.write("\n")
        self.output_file.write("// Unit multiplier outputs\n")
        self.output_file.write("//uint_large_h output[" + str(len(self.unit_mults) / 4) + "];\n")
        self.output_file.write("uint_large_h tmp_output = 0;\n")
        self.output_file.write("\n")

        adder = ""

        for mult in self.unit_mults:
            used = False
            for mult_ in used_mults:
                if (mult_ is mult):
                    used = True
                    break
            if used == True:
                continue
            used_mults.append(mult)
            cnt = 0
            mult_group = []
            mult_group.append(mult)
            for mult_ in self.unit_mults:
                used = False
                for mult__ in used_mults:
                    if (mult__ is mult_):
                        used = True
                        break
                if used == True:
                    continue
                if (cnt == 0 or cnt == 1):
                    if (mult_.weight == mult.weight + unit_mult_size):
                        used_mults.append(mult_)
                        mult_group.append(mult_)
                        cnt = cnt + 1
                elif (cnt == 2):
                    if (mult_.weight == mult.weight + 2 * unit_mult_size):
                        used_mults.append(mult_)
                        mult_group.append(mult_)
                        self.output_file.write("// Unit multiplier " + str(ind) + "\n")
                        
                        min_weight = len(self.unit_mults) * unit_mult_size

                        for i in range(0, 4):
                            tmp = mult_group[i].op1.position + mult_group[i].op2.position
                            if tmp < min_weight:
                                min_weight = tmp
                        self.mult_pos.append(min_weight)
                        self.output_file.write("//output[" + str(ind) + "] = (uint_large_h)((uint_large_h)unit_mult(in_op0_" + str(mult_group[0].op1.position) + ", in_op0_" + str(mult_group[1].op1.position) + ", in_op0_" + str(mult_group[2].op1.position) + ", in_op0_" + str(mult_group[3].op1.position) + ", in_op1_" + str(mult_group[0].op2.position) + ", in_op1_" + str(mult_group[1].op2.position) + ", in_op1_" + str(mult_group[2].op2.position) + ", in_op1_" + str(mult_group[3].op2.position) + ") << " + str(min_weight) + " );\n")
                        self.output_file.write("tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_" + str(mult_group[0].op1.position) + ", in_op0_" + str(mult_group[1].op1.position) + ", in_op0_" + str(mult_group[2].op1.position) + ", in_op0_" + str(mult_group[3].op1.position) + ", in_op1_" + str(mult_group[0].op2.position) + ", in_op1_" + str(mult_group[1].op2.position) + ", in_op1_" + str(mult_group[2].op2.position) + ", in_op1_" + str(mult_group[3].op2.position) + ") << " + str(min_weight) + " ));\n")
                        adder = adder + " + output[" + str(ind) + "]"
                        break
                
            ind = ind + 1
        
        self.output_file.write("\n")

        self.output_file.write("//*y = " + adder + ";\n")
        self.output_file.write("*y = tmp_output;\n")

        self.output_file.write("\n")
        
        for mult in self.unit_mults:
            used = False
            for mult_ in used_mults:
                if (mult_ is mult):
                    used = True
                    break
            if used == False:
                self.output_file.write(str(mult.weight) + " " + str(mult.op1.position) + " " + str(mult.op2.position) + "\n")
            

    def generate_adders(self, unit_multipliers):
        self.adders = []
        self.registers = []
        self.carry_registers = []

        for mult in unit_multipliers:
            for res in mult.results:
                self.registers.append(res)

        self.registers.sort(key=sort_by_weight)

class Register(object):
    def __init__(self, size, position):
        self.size = size
        self.position = position

    def is_at_position(self, position):
        return position == self.position

class NodeMultiplier(object):
    def __init__(self, op1, op2, weight, unit_output_size):
        self.op1 = op1
        self.op2 = op2
        self.weight = weight

        number_of_outputs = int(math.ceil((op1.size + op2.size) / unit_output_size))
        output_regs = []

        for i in range(0, number_of_outputs):
            output_regs.append(Register(unit_output_size, weight + i * unit_output_size))

        self.results = output_regs

class NodeAdder(object):
    def __init__(self, op1, op2, c_in, weight):
        self.op1 = op1
        self.op2 = op2
        self.c_in = c_in
        self.weight = weight
        self.result = None
        self.c_out = None

def main():
    if len(sys.argv) < 4:
        print("usage : python multiplier_generator_hls.py op1_width op2_width unit_mult_size")
        exit
    multGen = LargeMultiplierGenerator(int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3]))
    
if __name__== "__main__":
    main()