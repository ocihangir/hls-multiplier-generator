import sys

def generate(bit_width):
  print("Creating include file...")

  print("Targets:\nBit Width of Multiplier Output : " + str(bit_width))

  processing_foo1s = False
  fo = open("../src/stmul.h","w+")
  fi=open("../src/stmul.h_template", "r")
  lines = fi.readlines()
  for line in lines:
    if line.startswith('//DEFINE_WIDTH'):
      processing_foo1s = True
    else:
      if processing_foo1s:
        fo.write("#define WIDTH" + str(bit_width))
      processing_foo1s = False
    fo.write(line)
  fo.close()
  fi.close

def main():
  if len(sys.argv) < 1:
    print("usage : python prepare_directives.py bit_width")
    exit

  bit_width = sys.argv[1]

  generate(bit_width)

if __name__ == "__main__":
    main()