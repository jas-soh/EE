// This module tunes the frequency of a clock
// divided_clocks[0] = 25MHz, [1] = 12.5Mhz, ... [23] = 3Hz, [24] = 1.5Hz, 
// [25] = 0.75Hz, ... 
// input: 1-bit clock
// output: 32-bit clocks of different frequency
module clock_divider (clock, reset, divided_clocks); 
	input logic reset, clock; 
	output logic [31:0] divided_clocks = 0; 
 
	always_ff @(posedge clock) begin 
		divided_clocks <= divided_clocks + 1; 
	end  
endmodule 

module clock_divider_testbench();
	reg reset, clock; 
	wire [31:0] divided_clocks = 0; 
	
	clock_divider dut (.clock, .reset, .divided_clocks);
	
	// Setting up a simulated clock.
	parameter CLOCK_PERIOD = 100;
	initial begin
		clock <= 0;
		forever #(CLOCK_PERIOD/2) clock <= ~clock; // Forever toggle the clock
	end
	
	initial begin
		reset <= 1; @(posedge clock);
		reset <= 0; repeat (40) @(posedge clock);
		$stop;
	end
endmodule 
