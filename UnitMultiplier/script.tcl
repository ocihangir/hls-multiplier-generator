############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
############################################################
open_project mul_prj -reset
set_top mul
add_files ../src/stmul.cpp
add_files -tb out.calc.dat
add_files -tb ../src/stmul_test.cpp
open_solution "solution1" -reset
set_part {xc7k160tfbg484-2} -tool vivado
create_clock -period 2.5 -name default
source "directives.tcl"
csim_design
csynth_design
#cosim_design
#export_design -rtl verilog -format ip_catalog
exit