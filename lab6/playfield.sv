module playfield(clk, rst, L, R, leds);
	input logic clk, rst, L, R;
	output logic [8:0] leds;

	genvar i;
	generate
		for(i = 0; i < 9; i++) begin : eachLight
				// right edge
				if (i == 0)
						light_state ls (.clk, .rst, .is_center(1'b0), .L, .R, .NL(leds[i+1]), .NR(1'b0), .led(leds[i]));
						
				// center
				else if (i == 4)
				      light_state ls (.clk, .rst, .is_center(1'b1), .L, .R, .NL(leds[i+1]), .NR(leds[i-1]), .led(leds[i]));
				
				// left edge
				else if (i == 8)
						light_state ls (.clk, .rst, .is_center(1'b0), .L, .R, .NL(1'b0), .NR(leds[i-1]), .led(leds[i]));
				
				else
						light_state ls (.clk(clk), .rst(rst), .is_center(1'b0), .L(L), .R(R), .NL(leds[i+1]), .NR(leds[i-1]), .led(leds[i]));
						
				
		end
	endgenerate
	
endmodule 

module playfield_testbench();
	logic clk, rst, L, R;
	
	logic [8:0] leds;
	
	
	playfield dut (clk, rst, L, R, leds);
	
		// Set up a simulated clock.
		parameter CLOCK_PERIOD=100;
		initial begin
			clk <= 0;
			forever #(CLOCK_PERIOD/2) clk <= ~clk; // Forever toggle the clock
			
		end
	
		// Set up the inputs to the design. Each line is a clock cycle.
		initial begin
																	 @(posedge clk);
	 rst <= 1;			   							       @(posedge clk);
	 rst <= 0; L <= 0; R <= 0; 						    @(posedge clk); // to left
					 L <= 1; 									 @(posedge clk);
																	 @(posedge clk);
																	 @(posedge clk);
																	 @(posedge clk);
																	 @(posedge clk);
					 L <= 0; 									 @(posedge clk);
																	 @(posedge clk);
																	 @(posedge clk);
																	 @(posedge clk);
	 rst <= 1;			   							       @(posedge clk);
	 rst <= 0; L <= 0; R <= 0; 						    @(posedge clk); // to right
								R <= 1; 							 @(posedge clk);
																	 @(posedge clk);
																	 @(posedge clk);
																	 @(posedge clk);
																	 @(posedge clk);	
								R <= 0;							 @(posedge clk);							
																	 @(posedge clk);							
																	 @(posedge clk);	
																	 @(posedge clk);								
	 rst <= 1;			   							       @(posedge clk);
	 rst <= 0; L <= 0; R <= 0; 						    @(posedge clk); // random
						    R <= 1; 							 @(posedge clk);
							 R <= 0;								 @(posedge clk);
				  L <= 1;										 @(posedge clk);
																	 @(posedge clk);
				  L <= 0; R <= 1;								 @(posedge clk);	
				  L <= 0;									    @(posedge clk);							
																	 @(posedge clk);							
																	 @(posedge clk);	
																	 @(posedge clk);																 
	$stop; // End the simulation.
	end
endmodule
