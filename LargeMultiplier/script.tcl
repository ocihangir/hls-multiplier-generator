open_project mul_prj -reset
set_top large_mul
add_files ../src/stmul.cpp
add_files ../src/stmul_large.cpp
add_files -tb out_large.calc.dat -cflags "-Wno-unknown-pragmas -Wno-unknown-pragmas"
add_files -tb ../src/stmul_large_test.cpp -cflags "-Wno-unknown-pragmas -Wno-unknown-pragmas"
open_solution "solution1" -reset
set_part {xc7k160tfbg484-2} -tool vivado
create_clock -period 2.5 -name default
source "directives.tcl"
csim_design
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog
exit