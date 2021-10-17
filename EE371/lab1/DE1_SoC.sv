// Top-level module that defines the I/Os for the DE-1 SoC board.
// This module and the submodules keep track of the number of cars in a parking lot
// based on the sequence of how the two 1 bit sensors (sensors A and B) are triggered.
// The output information is displayed on 6 7-seg HEX's.
// The CAPACITY parameter is the maximum number of cars that can be in the lot
module DE1_SoC #(parameter CAPACITY=5'b11001) (CLOCK_50, HEX0, HEX1, HEX2, HEX3, HEX4, HEX5, GPIO_0);

	// parameter can be changed in just this module and it will populate through all modules.
	
	input logic CLOCK_50;
	output logic [6:0]  HEX5, HEX4, HEX3, HEX2, HEX1, HEX0;
	inout logic [33:0] GPIO_0;
 	
	// Assign GPIO_0[27] (LED) to GPIO_0[5] (switch)
	assign GPIO_0[26] = GPIO_0[5];
	// Assign GPIO_0[26] (LED) to GPIO_0[6] (switch)
	assign GPIO_0[27] = GPIO_0[6];
	
	logic clk;
	assign clk = CLOCK_50;
	
	logic reset;
	assign reset = GPIO_0[7]; // right switch is reset
	
	logic enter, exit;
	
	// two switches are the A and B signals
	FSM sensors (.enter, .exit, .A(GPIO_0[5]), .B(GPIO_0[6]), .clk, .reset);
	
	logic [4:0] count; // the number of cars in the lot
	counter #(CAPACITY) c (.out(count), .clk, .reset, .inc(enter), .dec(exit));
	hexDisplay #(CAPACITY) display (.HEX5, .HEX4, .HEX3, .HEX2, .HEX1, .HEX0, .count);

endmodule

// testbench for DE1_SoC top-level module
module DE1_SoC_testbench();
	wire[33:0] GPIO_0;
	logic CLOCK_50;
	logic [6:0]  HEX5, HEX4, HEX3, HEX2, HEX1, HEX0;
	
	DE1_SoC #(5'b00101) dut (.CLOCK_50, .HEX0, .HEX1, .HEX2, .HEX3, .HEX4, .HEX5, .GPIO_0);

	
	parameter CLOCK_PERIOD=100;
	initial begin
		CLOCK_50 <= 0;
		forever #(CLOCK_PERIOD/2) CLOCK_50 <= ~CLOCK_50; // Forever toggle the clock
		
	end
	
	logic reset, A, B;
	assign GPIO_0[7] = reset;
	assign GPIO_0[5] = A;
	assign GPIO_0[6] = B;
	
	// Testing the module
	integer i;
	initial begin
		// reset
		reset <= 1;                      repeat(3) @(posedge CLOCK_50);
		reset <= 0;

		// cars enter until full
		for (i = 1; i < 7; i = i + 1) begin
			A <= 0; B <= 0; @(posedge CLOCK_50);
			A <= 1; B <= 0; @(posedge CLOCK_50);
			A <= 1; B <= 1; @(posedge CLOCK_50);
			A <= 0; B <= 1; @(posedge CLOCK_50);
			A <= 0; B <= 0; @(posedge CLOCK_50);
		end
		
		// cars exit until clear
		for (i = 1; i < 7; i = i + 1) begin
			A <= 0; B <= 0; @(posedge CLOCK_50);
			A <= 0; B <= 1; @(posedge CLOCK_50);
			A <= 1; B <= 1; @(posedge CLOCK_50);
			A <= 1; B <= 0; @(posedge CLOCK_50);
			A <= 0; B <= 0; @(posedge CLOCK_50);
		end

		$stop;
	end
endmodule
