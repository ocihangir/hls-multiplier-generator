import sys
import subprocess

print("Creating include file...")

if len(sys.argv) < 3:
    print("usage : python prepare_directives.py bit_width unit_mult_width")
    exit

bit_width = sys.argv[1]
unit_mult_width = sys.argv[2]

print("Targets:\nBit Width of Multiplier Output : " + bit_width)

processing_foo1s = False
fo = open("../src/stmul_large.h","w+")
fi=open("../src/stmul_large.h_template", "r")
lines = fi.readlines()
for line in lines:
  if line.startswith('//DEFINE_LRG_WIDTH'):
    processing_foo1s = True
  else:
    if processing_foo1s:
      fo.write("#define LRG_WIDTH" + bit_width)
    processing_foo1s = False
  fo.write(line)
fo.close()
fi.close

print("Creating large multiplier cpp file...")

subprocess.check_call(["python","multiplier_generator_hls.py", str(int(bit_width)/2), str(int(bit_width)/2), unit_mult_width])

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

