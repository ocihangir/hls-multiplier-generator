import sys
import subprocess
import multiplier_generator_hls

def generate(bit_width, unit_mult_width):
  print("Creating include file...")

  print("Targets:\nBit Width of Multiplier Output : " + str(bit_width))

  processing_foo1s = False
  fo = open("../src/stmul_large.h","w+")
  fi=open("../src/stmul_large.h_template", "r")
  lines = fi.readlines()
  for line in lines:
    if line.startswith('//DEFINE_LRG_WIDTH'):
      processing_foo1s = True
    else:
      if processing_foo1s:
        fo.write("#define LRG_WIDTH" + str(bit_width))
      processing_foo1s = False
    fo.write(line)
  fo.close()
  fi.close

  print("Creating large multiplier cpp file...")

  multiplier_generator_hls.LargeMultiplierGenerator(int(bit_width)/2, int(bit_width)/2, unit_mult_width)

  fi=open("multiplier.gen", "r")
  mult_content = fi.read()
  fi.close()

  processing_foo1s = False
  fo = open("../src/stmul_large.cpp","w+")
  fi=open("../src/stmul_large.cpp_template", "r")
  lines = fi.readlines()
  for line in lines:
    if line.startswith('//GENERATED_MULTIPLIER'):
      processing_foo1s = True
    else:
      if processing_foo1s:
        fo.write(mult_content)
      processing_foo1s = False
    fo.write(line)
  fo.close()
  fi.close

def main():
  if len(sys.argv) < 3:
    print("usage : python prepare_directives.py bit_width unit_mult_width")
    exit

  bit_width = sys.argv[1]
  unit_mult_width = sys.argv[2]

  generate(bit_width, unit_mult_width)
  

if __name__ == "__main__":
    main()