module regfile (readReg1, readReg2, writeReg, writeData, readData1, readData2, clk);
	input logic [4:0] readReg1, readReg2, writeReg;
	input logic [63:0] writeData;
	input logic clk; 
	output logic [63:0] readData1, readData2;
	
	logic [31:0] reg64; // there are 32 64-bit registers
	logic [31:0][63:0] data_arr; // the entire array of data
	
	// making 32 registers, each register has 64-bit
	genvar i;
	generate
		for(i = 0; i < 31; i++) begin: eachDFF_64 // make 31 64-bit registers
			DFF_64 eachReg (.dataOut(data_arr[i]), .clk, .reset(1'b0), .dataIn(writeData), .regWrite(reg64[i]));
		end
	endgenerate
	
	// register 31 is 0's
	DFF_64 reg31 (.dataOut(data_arr[i]), .clk, .reset(1'b1), .dataIn(64'b0), .regWrite(reg64[31]));
	
	mux_64x32_1 mux1 (.data(data_arr), .readReg(readReg1), .readData(readData1));
	mux_64x32_1 mux2 (.data(data_arr), .readReg(readReg2), .readData(readData2));
endmodule 