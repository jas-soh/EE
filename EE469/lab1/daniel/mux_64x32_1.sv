`timescale 1ps/1ps
module mux_64x32_1 (data, readReg, readData);

	input logic [31:0][63:0] data;
	input logic [4:0] readReg;
	output logic [63:0] readData;
	
	logic [63:0][31:0] transpose;
	
	genvar i, j;
	generate
		for (i = 0; i < 64; i++) begin: eachCol
			for (j = 0; j < 32; j++) begin: eachRow
				assign transpose[i][j] = data[j][i];
			end
		end
	endgenerate
	
	generate
		for (i = 0; i < 64; i++) begin: muxSelect
			mux_32_1 readPort1 (.inputs(transpose[i]), .out(readData[i]), .readReg(readReg));
		end
	endgenerate
endmodule



// testbench
module mux_64x32_1_testbench();
	logic [31:0][63:0] data;
	logic [4:0] readReg;
	logic [63:0] readData;
	
	mux_64x32_1 dut(data, readReg, readData);
	
	integer i;
	integer j;
	initial begin
	// initialize data
		data[0] = 64'b1;
		for (i = 1; i < 32; i++) begin
			data[i] = i*2;
		end
		
		readReg = 5'b11111; #1000; // readData should be 64
		readReg = 5'b00001; #1000;
		readReg = 5'b00000; #1000;
		#100;
		$stop;
	end
	
endmodule
