set_directive_latency -min 5 -max 5 "mul"
set_directive_pipeline -II 4 "mul"
set_directive_allocation -limit 4 -type function "mul" add
set_directive_allocation -limit 4 -type function "mul" mult
set_directive_resource -core Mul_LUT "mult" return
