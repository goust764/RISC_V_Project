//==============================================================================
//  Filename    : Mem
//  Description : Data and instruction memory
//==============================================================================

module mem #(parameter  n=20) ( 
    input               clk,
    input               rst,
    // Data related IO
    input               memRW_i,         // Indicate if we read (0) or write (1)
    input               signed_i,        // Indicate if we read signed (1) or unsigned (0)
    input        [1 :0] dataSec_i,       // Indicate the size of the data to write (00: 1 byte, 01: 2 bytes, 10: 4 bytes)
    input        [31:0] dataW_i,         // Data to write
    input        [31:0] addr_i,          // Address to read/write
    output logic [31:0] data_sync_o,     // Synchrone  data read
    output logic [31:0] data_async_o,    // Asynchrone data read
    output logic [31:0] alu_o,           // Pass the value of addr_i to the next stage
    // Instruction related IO
    input        [31:0] pc_i,            // Program counter
    output logic [31:0] inst_o           // Instruction read
);
    //== Variable Declaration ======================================================
    // Data related variabless
    logic [7:0]  mem[n:0];               // Table containing the memory, n required to be a multiple of 4m-1
    integer i;                           // Loop variable
    // Instruction related variables
    logic  [31:0]  inst;                 // Asynchronous instruction read
    logic  [31:0]  count;                // Adress translated (count = pc/4)

    //== Main code =================================================================
    always_ff @(posedge clk) begin
        //----- Reset the memory
        if(rst) begin
            inst_o <= 0;               // NOP
            data_sync_o <= 32'hffffffff;
            alu_o       <= 0;
            /*
            We do not reset the memory since instructions are stored in it
            for (i = 0; i <= n; i=i+1)
                mem[i] <= 8'hff;
            */
        end

        else begin
            inst_o <= inst;
            data_sync_o <= data_async_o;
            alu_o       <= addr_i;
            if(memRW_i) begin
            //----- Write
                case (dataSec_i)
                    // Byte
                    2'b00: mem[addr_i] <= dataW_i[7:0];
                    // Half word
                    2'b01: begin
                        mem[addr_i+1] <= dataW_i[15:8];
                        if (addr_i+1 <= n) mem[addr_i] <= dataW_i[7:0];
                    end
                    // Word
                    2'b10: begin
                        mem[addr_i+3] <= dataW_i[31:24];
                        if (addr_i+1 <= n) mem[addr_i+2] <= dataW_i[23:16];
                        if (addr_i+2 <= n) mem[addr_i+1] <= dataW_i[15:8];
                        if (addr_i+3 <= n) mem[addr_i]   <= dataW_i[7:0];
                    end
                    default: begin
                        /* No write */
                    end
                endcase
            end
        end

    end
    
    always_comb begin                    // memRW_i, dataW_i, addr
        //========== Data read
        //----- Default values
        data_async_o = 32'hffffffff;

        //----- Read, manage the case where the size of the data is above the size of the memory
        if(!memRW_i && addr_i >= 0 && addr_i < n) begin
            if (addr_i+1 > n) begin
                data_async_o[31:8] = 24'h000000;
                data_async_o[7:0]  = mem[addr_i];
            end
            else if (addr_i+2 > n) begin
                data_async_o[31:16] = 16'h0000;
                data_async_o[7:0]  = mem[addr_i];
                data_async_o[15:8]  = mem[addr_i+1];

            end
            else if (addr_i+1 > n) begin
                data_async_o[31:24] = 8'h00;
                data_async_o[7:0]  = mem[addr_i];
                data_async_o[15:8]  = mem[addr_i+1];
                data_async_o[23:15]  = mem[addr_i+2];

            end
            else begin
                data_async_o[31:24] = mem[addr_i+3];
                data_async_o[23:16] = mem[addr_i+2];
                data_async_o[15:8]  = mem[addr_i+1];
                data_async_o[7:0]   = mem[addr_i];
            end

            // We mask the data according to the the value of dataSec_i
            case (dataSec_i)
                2'b00: begin             // Byte
                    if (signed_i && data_async_o[7])
                        data_async_o[31:8] = 24'hffffff;
                    else
                        data_async_o[31:8] = 24'h000000;
                    data_async_o[31:8]  = 24'h000000;
                end
                2'b01: begin             // Half word
                    if (signed_i && data_async_o[15])
                        data_async_o[31:16] = 16'hffff;
                    else
                        data_async_o[31:16] = 16'h0000;
                end
                default: begin
                    /* No mask */
                end
            endcase
        end

        //========== Instruction read
        //----- Default values
        inst = 32'h00000000;             // NOP

        //----- Read
        if (pc_i < n-4) begin
            count = pc_i >> 2;
            inst = {mem[pc_i+3], mem[pc_i+2], mem[pc_i+1], mem[pc_i]};
        end
    end
endmodule  
