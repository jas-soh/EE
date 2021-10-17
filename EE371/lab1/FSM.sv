// This module tracks when cars leave or enter the lot and outputs whether the event occurred.
// input: the current logic of 1 bit signals A and B; clock (clk), reset 1 bit signal (reset)
// output: enter and exit; 1 if a car is entering, 0 if a car is not entering; 1 if a car is exiting, 0 if a car is not entering
module FSM (enter, exit, A, B, clk, reset);
	// SW and KEY cannot be declared if GPIO_0 is declared on LabsLand
	input logic clk, reset, A, B;
	output logic enter, exit;
	
	logic[1:0] ps, ns;
	assign ns = {A, B};
	
	assign enter = (ps == 2'b10 & ns == 2'b11); // situation: both sensors unblocked and then sensor a is blocked
	assign exit = (ps == 2'b11 & ns == 2'b10); // situation: only sensor a is blocked and then both sensors unblocked
	
	// transitioning to next state or re-setting
	always_ff @(posedge clk) begin
		if (reset)
			ps <= 2'b00; // resets to zero
		else
			ps <= ns;
	end
	
endmodule

// testbench for FSM module
module FSM_testbench();
	logic clk, reset, A, B;
	logic enter, exit;
	
	FSM dut (enter, exit, A, B, clk, reset);
	
	// Set up a simulated clock.
	parameter CLOCK_PERIOD=100;
	initial begin
		clk <= 0;
		forever #(CLOCK_PERIOD/2) clk <= ~clk; // Forever toggle the clock
		
	end

	initial begin
									@(posedge clk);
		reset <= 1;				@(posedge clk); // reset
		reset <= 0;				@(posedge clk);
		
		// enters
		reset <= 0;	A <= 0; B <= 0;			@(posedge clk);
		reset <= 0;	A <= 1; B <= 0;			@(posedge clk);
		reset <= 0;	A <= 1; B <= 1;			@(posedge clk);
		reset <= 0;	A <= 0; B <= 1;			@(posedge clk);
		
		reset <= 0;	A <= 0; B <= 0;			@(posedge clk);
		
		// exits
		reset <= 0;	A <= 0; B <= 0;			@(posedge clk);
		reset <= 0;	A <= 0; B <= 1;			@(posedge clk);
		reset <= 0;	A <= 1; B <= 1;			@(posedge clk);
		reset <= 0;	A <= 1; B <= 0;			@(posedge clk);
		reset <= 0;	A <= 0; B <= 0;			@(posedge clk);
		$stop; 
	end
endmodule
