#ajout de rst et clk 
add wave sim:/bench_mult/*
#ajout de la mémoire donnée
add wave  \
sim:/bench_mult/riscv1/mem1/mem
#ajout de pc et next_instruction 
add wave  \
sim:/bench_mult/riscv1/mem1/inst_o
#ajout du tableau de registre
add wave -position insertpoint  \
sim:/bench_mult/riscv1/regfile1/Registers
#rajouter tous les signaux des modules
add wave -group riscv sim:/bench_mult/riscv1/*
add wave -group wb sim:/bench_mult/riscv1/wb1/*
add wave -group regfile sim:/bench_mult/riscv1/regfile1/*
add wave -group opti sim:/bench_mult/riscv1/opti1/*
add wave -group branch_comp sim:/bench_mult/riscv1/opti1/branch_comp1/*
add wave -group imm_gen sim:/bench_mult/riscv1/imm_gen1/*
add wave -group alu sim:/bench_mult/riscv1/alu1/*
add wave -group mem sim:/bench_mult/riscv1/mem1/*
add wave -group control_logic sim:/bench_mult/riscv1/control_logic1/*
add wave -group wb sim:/bench_mult/riscv1/wb1/*
run 3000