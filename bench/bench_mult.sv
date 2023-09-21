//==============================================================================
//  Filename    : bench_mult
//  Description : Test bench for multiplication program
//==============================================================================

module bench_mult();

timeunit      1ns;
timeprecision 1ns;

// Simulation parameters
localparam  MEM_SIZE   = 511, 
            PROG_SIZE  = 46,
            CLK_PERIOD = 20, 
            NB_TESTS   = 70;

logic [31:0]  insn_buff[PROG_SIZE:0];                       // Buffer to read

int clock_number;                                           // Number of clock cycles since the reset
int passed_test = 0;                                        // Number of passed tests
int done_test = 0;                                          // Number of done tests
int value_ok = 0;                                           // Inidicate if the value read is the expected one

typedef struct {
    string name;
    int clk;
    logic [32:0] address;
    int size;
    logic [31:0] value;
} tests;

tests test[NB_TESTS] = '{
'{"PC = 8 : SW", 2, 184, 32, 32'h000002fc},             // 00008 sw     a5,-32(fp)
'{"PC = 16 : SW", 4, 196, 32, 32'h00000009},            // 00016 sw     a5,-20(fp)
'{"PC = 20 : SW", 5, 192, 32, 32'h00000000},            // 00020 sw     zero,-24(fp)
'{"PC = 24 : SW", 6, 188, 32, 32'h00000000},            // 00024 sw     zero,-28(fp)
'{"PC = 96 : SW", 32, 192, 32, 32'h000002fc},           // 00096 sw     a5,-24(fp)
'{"PC = 108 : SW", 35, 196, 32, 32'h00000004},          // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 38, 188, 32, 32'h00000001},          // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 56, 196, 32, 32'h00000002},          // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 59, 188, 32, 32'h00000002},          // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 77, 196, 32, 32'h00000001},          // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 80, 188, 32, 32'h00000003},          // 00120 sw     a5,-28(fp)
'{"PC = 96 : SW", 101, 192, 32, 32'h00001adc},          // 00096 sw     a5,-24(fp)
'{"PC = 108 : SW", 104, 196, 32, 32'h00000000},         // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 107, 188, 32, 32'h00000004},         // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 125, 196, 32, 32'h00000000},         // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 128, 188, 32, 32'h00000005},         // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 146, 196, 32, 32'h00000000},         // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 149, 188, 32, 32'h00000006},         // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 167, 196, 32, 32'h00000000},         // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 170, 188, 32, 32'h00000007},         // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 188, 196, 32, 32'h00000000},         // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 191, 188, 32, 32'h00000008},         // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 209, 196, 32, 32'h00000000},         // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 212, 188, 32, 32'h00000009},         // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 230, 196, 32, 32'h00000000},         // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 233, 188, 32, 32'h0000000a},         // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 251, 196, 32, 32'h00000000},         // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 254, 188, 32, 32'h0000000b},         // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 272, 196, 32, 32'h00000000},         // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 275, 188, 32, 32'h0000000c},         // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 293, 196, 32, 32'h00000000},         // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 296, 188, 32, 32'h0000000d},         // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 314, 196, 32, 32'h00000000},         // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 317, 188, 32, 32'h0000000e},         // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 335, 196, 32, 32'h00000000},         // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 338, 188, 32, 32'h0000000f},         // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 356, 196, 32, 32'h00000000},         // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 359, 188, 32, 32'h00000010},         // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 377, 196, 32, 32'h00000000},         // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 380, 188, 32, 32'h00000011},         // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 398, 196, 32, 32'h00000000},         // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 401, 188, 32, 32'h00000012},         // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 419, 196, 32, 32'h00000000},         // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 422, 188, 32, 32'h00000013},         // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 440, 196, 32, 32'h00000000},         // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 443, 188, 32, 32'h00000014},         // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 461, 196, 32, 32'h00000000},         // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 464, 188, 32, 32'h00000015},         // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 482, 196, 32, 32'h00000000},         // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 485, 188, 32, 32'h00000016},         // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 503, 196, 32, 32'h00000000},         // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 506, 188, 32, 32'h00000017},         // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 524, 196, 32, 32'h00000000},         // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 527, 188, 32, 32'h00000018},         // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 545, 196, 32, 32'h00000000},         // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 548, 188, 32, 32'h00000019},         // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 566, 196, 32, 32'h00000000},         // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 569, 188, 32, 32'h0000001a},         // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 587, 196, 32, 32'h00000000},         // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 590, 188, 32, 32'h0000001b},         // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 608, 196, 32, 32'h00000000},         // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 611, 188, 32, 32'h0000001c},         // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 629, 196, 32, 32'h00000000},         // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 632, 188, 32, 32'h0000001d},         // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 650, 196, 32, 32'h00000000},         // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 653, 188, 32, 32'h0000001e},         // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 671, 196, 32, 32'h00000000},         // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 674, 188, 32, 32'h0000001f},         // 00120 sw     a5,-28(fp)
'{"PC = 108 : SW", 692, 196, 32, 32'h00000000},         // 00108 sw     a5,-20(fp)
'{"PC = 120 : SW", 695, 188, 32, 32'h00000020}          // 00120 sw     a5,-28(fp)
};

bit clk;
bit reset;

// Design Under Test
riscv #(MEM_SIZE) riscv1 (
    .clk(clk),
    .rst(reset)
);

initial $timeformat ( -9, 1, " ns", 12 );

// Clock and Reset Definitin
initial begin
    clk = 1'b1;
    reset = 1'b1;
    #(CLK_PERIOD) reset = 1'b0;
end

always
    #(CLK_PERIOD/2) clk = ~clk;

// Load the program in the instruction memory from a binary file
initial begin
    // Init the memory with 0
    for (int i = 0; i < MEM_SIZE+1; i=i+1) begin
        riscv1.mem1.mem[i] = 8'hff;
    end
    $readmemb("D:/Dossier principal/Electronique/Tout MES programmes/RISC_V_Project/prog/asm_mult.bin", insn_buff);   
    for (int i = 0; i < PROG_SIZE; i=i+1) begin
        riscv1.mem1.mem[4*i  ] = insn_buff[i][7:0];
        riscv1.mem1.mem[4*i+1] = insn_buff[i][15:8];
        riscv1.mem1.mem[4*i+2] = insn_buff[i][23:16];
        riscv1.mem1.mem[4*i+3] = insn_buff[i][31:24];
    end

    clk <= 1'b0  ;
    reset <= 1'b1;
    #21 reset <= 1'b0;
    clock_number = 0;
end

always @(posedge clk) begin
    clock_number = clock_number + 1;
    //----- Tests généraux
    for (int i = 0; i < NB_TESTS; i++) begin
        if (clock_number == test[i].clk+5) begin      // +5 because of the stages of the pipeline
        // if (clock_number == test[i].clk+4) begin      // +4 because of the stages of the pipeline
            $display("========== Test %s (CLK = %d)", test[i].name, clock_number);
            $display("Expected value : 0x%h @ 0x%h",  test[i].value, test[i].address);
            value_ok = 0;
            case (test[i].size)
                8: begin
                    $display(
                        "Read value     : 0x%h @ 0x%h", 
                        riscv1.mem1.mem[test[i].address], 
                        test[i].address
                    );
                    if (riscv1.mem1.mem[test[i].address  ][7:0]  == test[i].value[7:0]) begin
                        value_ok = 1;
                    end
                end
                16: begin
                    $display(
                        "Read value     : 0x%h %h @ 0x%h", 
                        riscv1.mem1.mem[test[i].address+1], 
                        riscv1.mem1.mem[test[i].address], 
                        test[i].address
                    );
                    if (riscv1.mem1.mem[test[i].address  ][7:0]  == test[i].value[7:0] &&
                        riscv1.mem1.mem[test[i].address+1][7:0]  == test[i].value[15:8]) begin
                        value_ok = 1;
                    end
                end
                32: begin
                    $display(
                        "Read value     : 0x%h %h %h %h @ 0x%h", 
                        riscv1.mem1.mem[test[i].address+3], 
                        riscv1.mem1.mem[test[i].address+2], 
                        riscv1.mem1.mem[test[i].address+1], 
                        riscv1.mem1.mem[test[i].address], 
                        test[i].address
                    );
                    if (riscv1.mem1.mem[test[i].address  ][7:0]  == test[i].value[7:0] &&
                        riscv1.mem1.mem[test[i].address+1][7:0]  == test[i].value[15:8] &&
                        riscv1.mem1.mem[test[i].address+2][7:0]  == test[i].value[23:16] &&
                        riscv1.mem1.mem[test[i].address+3][7:0]  == test[i].value[31:24]) begin
                        value_ok = 1;
                    end
                end
                default: begin
                    $display("ERROR : Wrong size");
                    $finish;
                end
            endcase
            if (value_ok == 0) begin
                $display("ERROR : Expected value is not the same as the read value");
                // $finish;
            end
            else begin
                $display("TEST PASSED");
                passed_test = passed_test + 1;
            end
            done_test = done_test + 1;
        end
    end
    if (done_test == NB_TESTS) begin
        $display("");
        $display("========== %d tests passed on %d", passed_test, done_test);
        // $finish;
    end
end

endmodule