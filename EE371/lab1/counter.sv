// This module keeps track of the number of cars in the lot 
// by incrementing and decrementing the count
// if the relevant input signal is recieved. 
// input: clock (clk), reset (reset), 1 bit increment/decrement signals (inc, dec)
// output: 5 bit count of the current number of cars in the lot
module counter	#(parameter CAPACITY=5'b11001) (out, clk, reset, inc, dec);
	
	input logic clk, reset, inc, dec;
	output logic [4:0] out;
	
	// increments or decrements score within 0 and capacity
	always_ff @(posedge clk) begin
		if (reset) out <= 0; // resets the car count to 0
		else if (inc & out < CAPACITY) out <= out + 5'b00001; // increments until max capacity
		else if (dec & out > 0) out <= out - 5'b00001; // decrements until empty
		else
			out <= out; // count remains the same
	end

endmodule 
 
// testbench for counter module
module counter_testbench ();
	
	logic clk, reset, inc, dec;
	logic [4:0] out;
	
	counter dut (out, clk, reset, inc, dec);
	
	// Set up a simulated clock.
	parameter CLOCK_PERIOD=100;
	initial begin
		clk <= 0;
		forever #(CLOCK_PERIOD/2) clk <= ~clk; // Forever toggle the clock
		
	end
	
	// increments until 25 and continues having inc = 1 (but counter stops at 25)
	// then decrements until 0 and continues have dec = 1 (but counter stops at 0)
	initial begin
																@(posedge clk);
	 reset <= 1;	   					repeat(5)	@(posedge clk);
	 reset <= 0;											@(posedge clk);
	 reset <= 0; inc <= 1; dec <= 0;	repeat(30) 	@(posedge clk);
	 reset <= 0; inc <= 0; dec <= 1;	repeat(30) 	@(posedge clk);
															 
	$stop; // End the simulation.
	end
endmodule 
