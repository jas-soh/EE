module DE1_SoC (CLOCK_50, HEX0, HEX1, HEX2, HEX3, HEX4, HEX5, KEY, LEDR, SW); 
	input logic CLOCK_50; // 50MHz clock. 
	output logic [6:0] HEX0, HEX1, HEX2, HEX3, HEX4, HEX5; 
	output logic [9:0] LEDR; 
	input logic [3:0] KEY; // True when not pressed, False when pressed 
	input logic [9:0] SW; 
 
	// Generate clk off of CLOCK_50, whichClock picks rate. 
 
	logic reset; 
	logic [31:0] div_clk; 
 
	assign reset = SW[9]; 
	logic [1:0] stable1; // after 1st DFF
	logic [1:0] stable2; // after 2nd DFF
	logic [1:0] p; // player input
	
	always_ff @(posedge CLOCK_50) begin
		stable1[1] <= KEY[3];
		stable1[0] <= KEY[0];
	end
	
	always_ff @(posedge CLOCK_50) begin
		stable2 <= stable1;
	end
	
	user_in playerL (.clk(CLOCK_50), .rst(reset), .key(stable2[1]), .p(p[1]));
	user_in playerR (.clk(CLOCK_50), .rst(reset), .key(stable2[0]), .p(p[0]));
	
	playfield pf (.clk(CLOCK_50), .rst(reset), .L(p[1]), .R(p[0]), .leds(LEDR[8:0]));
	
	victory v (.clk(CLOCK_50), .rst(reset), .L(p[1]), .R(p[0]), .L_edge(LEDR[8]), .R_edge(LEDR[0]), .hex(HEX0));
 
endmodule

module DE1_SoC_testbench(); 
	logic CLOCK_50; 
	logic [6:0] HEX0, HEX1, HEX2, HEX3, HEX4, HEX5; 
	logic [9:0] LEDR; 
	logic [3:0] KEY; 
	logic [9:0] SW; 
 
	DE1_SoC dut (CLOCK_50, HEX0, HEX1, HEX2, HEX3, HEX4, HEX5, KEY, LEDR, SW); 
 
	// Set up a simulated clock. 
	parameter CLOCK_PERIOD=100; 
	initial begin 
		CLOCK_50 <= 0; 
		forever #(CLOCK_PERIOD/2) CLOCK_50 <= ~CLOCK_50; // Forever toggle the clock 
	end 
 
	// Test the design. 
	initial begin
			
									 repeat(1) @(posedge CLOCK_50);
					SW[9] <= 1; repeat(1) @(posedge CLOCK_50); // Always reset FSMs at start
					SW[9] <= 0; repeat(1) @(posedge CLOCK_50);
	  KEY[0] <=0 ; KEY[3] <= 1; repeat(3)  	@(posedge CLOCK_50); // Test case 1 calm: input is 00
											@(posedge CLOCK_50);
	  KEY[0] <=0 ; KEY[3] <= 0;  	@(posedge CLOCK_50); // Test case 2 Right To Left: input 01 for 6 cycleS
											@(posedge CLOCK_50);
	  KEY[0] <=0 ; KEY[3] <= 1;  	@(posedge CLOCK_50);
		                           @(posedge CLOCK_50);
		KEY[0] <=0 ; KEY[3] <= 0;  @(posedge CLOCK_50); 
											@(posedge CLOCK_50);
	  KEY[0] <=0 ; KEY[3] <= 1;   	@(posedge CLOCK_50);
	                              @(posedge CLOCK_50);
		KEY[0] <=0 ; KEY[3] <= 0;  	@(posedge CLOCK_50); 
	                             	@(posedge CLOCK_50);
		 KEY[0] <=0 ; KEY[3] <= 1;   	@(posedge CLOCK_50);
	                              @(posedge CLOCK_50);
		KEY[0] <=0 ; KEY[3] <= 0;  	@(posedge CLOCK_50); 
	                             	@(posedge CLOCK_50);
	  KEY[0] <=0 ; KEY[3] <= 1;   	@(posedge CLOCK_50);
	                              @(posedge CLOCK_50);
		KEY[0] <=0 ; KEY[3] <= 0;  	@(posedge CLOCK_50); 
	                             	@(posedge CLOCK_50);
	 KEY[0] <=0 ; KEY[3] <= 1;   	@(posedge CLOCK_50);
	                              @(posedge CLOCK_50);
		KEY[0] <=0 ; KEY[3] <= 0;  	@(posedge CLOCK_50); 
	                             	@(posedge CLOCK_50);
		 KEY[0] <=0 ; KEY[3] <= 1;   	@(posedge CLOCK_50);
	                              @(posedge CLOCK_50);
		KEY[0] <=0 ; KEY[3] <= 0;  	@(posedge CLOCK_50); 
	                             	@(posedge CLOCK_50);
		 KEY[0] <=0 ; KEY[3] <= 1;   	@(posedge CLOCK_50);
	                              @(posedge CLOCK_50);
		KEY[0] <=0 ; KEY[3] <= 0;  	@(posedge CLOCK_50); 
	                             	@(posedge CLOCK_50);

											@(posedge CLOCK_50);
	  				SW[9] <= 1; repeat(1) @(posedge CLOCK_50); // Always reset FSMs at start
					SW[9] <= 0; repeat(1) @(posedge CLOCK_50);
	  KEY[0] <=1 ; KEY[3] <= 0;  	@(posedge CLOCK_50); 
											@(posedge CLOCK_50);
	  KEY[0] <=0 ; KEY[3] <= 0;  	@(posedge CLOCK_50); // Test case 2 Right To Left: input 01 for 6 cycleS
											@(posedge CLOCK_50);
	  KEY[0] <=1 ; KEY[3] <= 0;  	@(posedge CLOCK_50);
		                            	@(posedge CLOCK_50); 
	  KEY[0] <=0 ; KEY[3] <= 0;  	@(posedge CLOCK_50);
	                           	@(posedge CLOCK_50);  
	  KEY[0] <=1 ; KEY[3] <= 0;  	@(posedge CLOCK_50);
											@(posedge CLOCK_50); 
	  KEY[0] <=0 ; KEY[3] <= 0;  	@(posedge CLOCK_50);
	                              @(posedge CLOCK_50);
		 KEY[0] <=1 ; KEY[3] <= 0;  	@(posedge CLOCK_50);
											@(posedge CLOCK_50); 
	  KEY[0] <=0 ; KEY[3] <= 0;  	@(posedge CLOCK_50);
	                              @(posedge CLOCK_50);
		 KEY[0] <=1 ; KEY[3] <= 0;  	@(posedge CLOCK_50);
											@(posedge CLOCK_50); 
	  KEY[0] <=0 ; KEY[3] <= 0;  	@(posedge CLOCK_50);
	                              @(posedge CLOCK_50);
		 KEY[0] <=1 ; KEY[3] <= 0;  	@(posedge CLOCK_50);
											@(posedge CLOCK_50); 
	  KEY[0] <=0 ; KEY[3] <= 0;  	@(posedge CLOCK_50);
	                              @(posedge CLOCK_50);
		 KEY[0] <=1 ; KEY[3] <= 0;  	@(posedge CLOCK_50);
											@(posedge CLOCK_50); 
	  KEY[0] <=0 ; KEY[3] <= 0;  	@(posedge CLOCK_50);
	                              @(posedge CLOCK_50);
											
					$stop; // End the simulation.
					
			end
endmodule
