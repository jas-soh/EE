// Top-level module that defines the I/Os for the DE-1 SoC board

module DE1_SoC (HEX0, HEX1, HEX2, HEX3, HEX4, HEX5, KEY, LEDR, SW);
	output logic [6:0]  HEX0, HEX1, HEX2, HEX3, HEX4, HEX5;
	output logic [9:0] LEDR;
	input logic [3:0] KEY;
	input logic [9:0] SW;
	logic notM, OUT1, OUT2;
	
	// Default values, turns off the HEX displays
	assign HEX0 = 7'b1111111;
	assign HEX1 = 7'b1111111;
	assign HEX2 = 7'b1111111;
	assign HEX3 = 7'b1111111;
	assign HEX4 = 7'b1111111;
	assign HEX5 = 7'b1111111;
	
	// Logic to check discount
	// based on SW[9],SW[8],SW[7] corresponding UPC code
	// Result should drive LEDR[1]
	assign LEDR[1] = (SW[8] | SW[9] & SW[7]);
	
	// Logic to check if item was stolen
	// based on SW[9],SW[8],SW[7] corresponding UPC code
	// And if there is prescence of a mark from SW[0]
	// Result should drive LEDR[0]
	not n1 (notM, SW[0]);
	nor norGate (OUT1, SW[8], SW[7], SW[0]);
	and andGate (OUT2, SW[9], SW[7], notM);
	or orGate (LEDR[0], OUT1, OUT2);
	
endmodule

module DE1_SoC_testbench();
	logic [6:0] HEX0, HEX1, HEX2, HEX3, HEX4, HEX5;
	logic [9:0] LEDR;
	logic [3:0] KEY;
	logic [9:0] SW;
	
	DE1_SoC dut (.HEX0, .HEX1, .HEX2, .HEX3, .HEX4, .HEX5, .KEY, .LEDR, .SW);
	
	// Try all combinations of inputs.
	integer i;
	initial begin
		SW[6] = 1'b0;
		SW[5] = 1'b0;
		SW[4] = 1'b0;
		SW[3] = 1'b0;
		SW[2] = 1'b0;
		SW[1] = 1'b0;
		for(i = 0; i <16; i++) begin
			{SW[9:7], SW[0]} = i; #10;
		end
	end
endmodule 