module light_state (clk, rst, is_center, L, R, NL, NR, led);
	input logic clk, rst, is_center, L, R, NL, NR;
	output logic led;
	
	enum {on, off} ps, ns;
	
	
	always_comb begin
		case (ps)
			on: if ( !L & R & !NL & !NR ) ns = off;
					else if ( L & !R & !NL & !NR ) ns = off;
					else ns = on;
			off: if ( !L & R & NL & !NR ) ns = on;
					else if ( L & !R & !NL & NR ) ns = on;
					else ns = off;
		endcase
	end
	
	assign led = (ps == on);
	
	always_ff @(posedge clk) begin
		if (rst)  
			if (is_center)
				ps <= on;
			else
				ps <= off;
		else 
			ps <= ns;
	end 
endmodule 

module light_state_testbench ();
	logic clk;
	logic rst;
	logic	NL;
	logic NR;
	logic	L;
	logic R;
	logic led;
	logic is_center;
 
	light_state dut (clk, rst, is_center, L, R, NL, NR, led);
 
	// Set up a simulated clock. 
	parameter CLOCK_PERIOD=100; 
	initial begin 
		clk <= 0; 
		forever #(CLOCK_PERIOD/2) clk <= ~clk; // Forever toggle the clock 
	end 
 
	// Test the design. 
	initial begin
																					@(posedge clk);
			rst <= 1; is_center <= 1;										@(posedge clk); // Always reset FSMs at start
			rst <= 1; is_center <= 0;										@(posedge clk);
			rst <= 0; NL <= 0; NR <= 0; L <= 0; R <= 0;  	 		@(posedge clk);
																					@(posedge clk);
																					@(posedge clk);
																					@(posedge clk);
			NL <= 0; NR <= 0; L <= 1; R <= 0;						   @(posedge clk);
																		         @(posedge clk);
			NL <= 0; NR <= 0; L <= 0; R <= 1;			  				@(posedge clk);
																					@(posedge clk);
			NL <= 1; NR <= 0; L <= 0; R <= 0;							@(posedge clk);
																					@(posedge clk);
			NL <= 1; NR <= 0; L <= 0; R <= 1;							@(posedge clk);
																					@(posedge clk);
					                                                @(posedge clk);
																					@(posedge clk);
			NL <= 0; NR <= 1; L <= 0; R <= 0;							@(posedge clk);
																	         	@(posedge clk);
			NL <= 0; NR <= 1; L <= 1; R <= 0;							@(posedge clk);
			                                                      @(posedge clk);
																					@(posedge clk);
		
			$stop; // End the simulation.
		end
endmodule 
