set_directive_latency -min 5 -max 5 "mul"
set_directive_pipeline -II 2 "mul"
set_directive_allocation -limit 1 -type function "mul" add
set_directive_allocation -limit 1 -type function "mul" mult
set_directive_latency -min 1 -max 4000 "large_mul"
set_directive_pipeline -II 2 "large_mul"
set_directive_allocation -limit 1 -type function "large_mul" unit_mult
set_directive_allocation -limit 1 -type function "large_mul" adder
set_directive_resource -core Mul_LUT "large_mul" y
