//==============================================================================
//  Filename    : bench_imem        
//  Description : Testbench of the instruction memory module
//==============================================================================
module bench_imem ();

timeunit      1ns;
timeprecision 1ns;

bit clk=1'b0;
bit reset;     
// logic   [31:0]tab_inst[3:0];
logic  [31:0]  addr;
logic  [31:0]  inst_out;


imem #(3) imem1(
    .clk(clk),
    .rst(reset),
    .pc(addr),
    .inst_out(inst_out)
);

initial $timeformat ( -9, 1, " ns", 12 );

// Clock and Reset Definition
`define PERIOD 10

  initial
    begin
      clk = 1'b1  ;
      reset = 1'b1;
      #1 reset = 1'b0;
    end

always
    #(`PERIOD/2) clk = ~clk;


initial forever begin
    imem1.tab_inst[0] = 32'haaaaaaaa;
    imem1.tab_inst[1] = 32'hbbbbbbbb;
    imem1.tab_inst[2] = 32'hcccccccc;
    imem1.tab_inst[3] = 32'hdddddddd;
    addr = 32'h00000000;
    #100
    addr = 32'h00000004;
    #100
    addr = 32'h00000008;
    #100
    addr = 32'h0000000c;
    #100;
end

// Automatic checker to compare Filter value with expected Output

endmodule










