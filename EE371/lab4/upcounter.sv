// This module keeps track of the number of cars in the lot 
// by incrementing and decrementing the count
// if the relevant input signal is recieved. 
// input: clock (clk), reset (reset), 1 bit increment/decrement signals (inc, dec)
// output: 5 bit count of the current number of cars in the lot
module upcounter (clk, reset, upcount_en, result);
	
	input logic clk, reset, upcount_en;
	output logic [2:0] result;
	
	// increments or decrements score within 0 and capacity
	always_ff @(posedge clk) begin
		if (reset) result <= 0; // resets the car count to 0
		else if (upcount_en) result <= result + 3'b001; // count remains the same
		else result <= result;
	end

endmodule 
 
// testbench for upcounter module
module upcounter_testbench ();
	
	logic clk, reset, upcount_en;
	logic [2:0] result;
	
	upcounter dut (.clk, .reset, .upcount_en, .result);
	
	// Set up a simulated clock.
	parameter CLOCK_PERIOD=100;
	initial begin
		clk <= 0;
		forever #(CLOCK_PERIOD/2) clk <= ~clk; // Forever toggle the clock
		
	end
	
	// increments until 25 and continues having inc = 1 (but counter stops at 25)
	// then decrements until 0 and continues have dec = 1 (but counter stops at 0)
	initial begin
	 reset <= 1; upcount_en <= 0;				 	@(posedge clk);
	 reset <= 1; upcount_en <= 0;				 	@(posedge clk);
	 reset <= 0;									 	@(posedge clk);
	 reset <= 0;									 	@(posedge clk);
	 reset <= 0; upcount_en <= 1; 	       	@(posedge clk);
	 reset <= 0;  					 	repeat(7) 	@(posedge clk);
															 
	$stop; // End the simulation.
	end
endmodule 