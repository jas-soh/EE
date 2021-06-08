module DE1_SoC (CLOCK_50, HEX0, HEX1, HEX2, HEX3, HEX4, HEX5, KEY, LEDR, SW);
	input logic CLOCK_50; // 50MHz clock.
	output logic [6:0] HEX0, HEX1, HEX2, HEX3, HEX4, HEX5;
	output logic [9:0] LEDR;
	input logic [3:0] KEY; // True when not pressed, False when pressed
	input logic [9:0] SW;
   
	logic [31:0] div_clk;
	clock_divider cdiv(.clock(CLOCK_50), .reset(SW[9]), .divided_clocks(div_clk));
	
	logic clkSelect;
	
	//uncomment one each time
	//assign clkSelect = CLOCK_50; //simulation
	assign clkSelect = div_clk[15];
	
	logic reset;
	assign reset = SW[9];
	
	// set random solution
	logic [7:0] sol;
	LFSR getSolution (.clk(clkSelect), .rst(reset), .out(sol));
	
	// count number of tries
	logic [5:0] tries;
	logic [1:0] incrTries;
	incr incr_ones (.clk(clkSelect), .rst(reset), .sw(SW[0]), .out(incrTries[0]));
	incr incr_tens (.clk(clkSelect), .rst(reset), .sw(SW[0]), .out(incrTries[1]));
	triesIncr countOnes (.clk(clkSelect), .rst(reset), .incr(incrTries[0]), .out(tries[2:0]));
	triesIncr countTens (.clk(clkSelect), .rst(reset), .incr(incrTries[1]), .out(tries[5:3]));
	guessDisplay displayOnes (.num(tries[2:0]), .out(HEX5));
	guessDisplay displayTens (.num(tries[5:3]), .out(HEX4));
	
	// stabilize
	logic KEY3, KEY2, KEY1, KEY0;
	series_dffs dff3 (.clk(clkSelect), .rst(reset), .d1(~KEY[3]), .q1(KEY3));
	series_dffs dff2 (.clk(clkSelect), .rst(reset), .d1(~KEY[2]), .q1(KEY2));
	series_dffs dff1 (.clk(clkSelect), .rst(reset), .d1(~KEY[1]), .q1(KEY1));
	series_dffs dff0 (.clk(clkSelect), .rst(reset), .d1(~KEY[0]), .q1(KEY0));	
	
	// user input
	logic b3, b2, b1, b0;
	user_in button3 (.clk(clkSelect), .rst(reset), .enable(~SW[0]), .key(KEY3), .p(b3));
	user_in button2 (.clk(clkSelect), .rst(reset), .enable(~SW[0]), .key(KEY2), .p(b2));
	user_in button1 (.clk(clkSelect), .rst(reset), .enable(~SW[0]), .key(KEY1), .p(b1));
	user_in button0 (.clk(clkSelect), .rst(reset), .enable(~SW[0]), .key(KEY0), .p(b0));
	
	// incrementing guess
	logic [1:0] num0, num1, num2, num3;
	guessIncr incr3 (.clk(clkSelect), .rst(reset), .incr(b3), .out(num3));
	guessIncr incr2 (.clk(clkSelect), .rst(reset), .incr(b2), .out(num2));
	guessIncr incr1 (.clk(clkSelect), .rst(reset), .incr(b1), .out(num1));
	guessIncr incr0 (.clk(clkSelect), .rst(reset), .incr(b0), .out(num0));
	
	// HEX display of incrementing guess
	guessDisplay display3 (.num({1'b0, num3}), .out(HEX3));
	guessDisplay display2 (.num({1'b0, num2}), .out(HEX2));
	guessDisplay display1 (.num({1'b0, num1}), .out(HEX1));
	guessDisplay display0 (.num({1'b0, num0}), .out(HEX0));
	//assign HEX4 = 7'b1111111;
	//assign HEX3 = 7'b0010010;
	//assign HEX2 = 7'b0000111;
	//assign HEX1 = 7'b0101111;
	//assign HEX0 = 7'b0000111;
	
	// checking correct color correct place
	logic [7:0] correctPlace;
	checkCorrect checkC (.clk(clkSelect), .rst(reset), .enable(SW[0]), .num({num3, num2, num1, num0}), .sol(sol), .out(correctPlace));
	
	// checking correct color wrong place
	logic [7:0] wrongPlace;
	checkWrong checkW (.clk(clkSelect), .rst(reset), .enable(SW[0]), .guess({num3, num2, num1, num0}), .sol(sol), .out(wrongPlace));
	
	logic [3:0] countCorrect;
	logic [3:0] countWrong;
	logic victory;
	assign countCorrect = correctPlace[7:6] + correctPlace[5:4] + correctPlace[3:2] + correctPlace[1:0];
	assign countWrong = (wrongPlace[7:6] + wrongPlace[5:4] + wrongPlace[3:2] + wrongPlace[1:0]) - countCorrect;
	assign victory = (countCorrect == 4'b0100);
	displayLedr ledsCorrect (.clk(clkSelect), .rst(reset), .enable(SW[0]), .count(countCorrect), .victory, .out(LEDR[9:6]));
	displayLedr ledsWrong (.clk(clkSelect), .rst(reset), .enable(SW[0]), .count(countWrong), .victory, .out({LEDR[0], LEDR[1], LEDR[2], LEDR[3]}));
	
	always_comb begin
		if (victory) begin
			LEDR[5] = 1'b1;
			LEDR[4] = 1'b1;
		end
		else begin
			LEDR[5] = 1'b0;
			LEDR[4] = 1'b0;
		end
	end
	
	assign HEX4 = 7'b1111111;
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
		SW[9] <= 1;	 				repeat(1) @(posedge CLOCK_50); // Always reset FSMs at start
		SW[9] <= 0; 				repeat(1) @(posedge CLOCK_50);
		KEY[0] <=1 ; 					  		@(posedge CLOCK_50); 
		KEY[0] <=0 ; 				  			@(posedge CLOCK_50);
		KEY[0] <=1 ; 				 			@(posedge CLOCK_50); 
		KEY[0] <=0 ; 							@(posedge CLOCK_50);
		KEY[0] <=1 ; 				  			@(posedge CLOCK_50); 
		KEY[0] <=0 ; 				  			@(posedge CLOCK_50);
		KEY[0] <=1 ; 					  		@(posedge CLOCK_50); 
		KEY[0] <=0 ; 				  			@(posedge CLOCK_50);
		KEY[0] <=1 ; 					  		@(posedge CLOCK_50); 
		KEY[0] <=0 ; 				  			@(posedge CLOCK_50);
		KEY[0] <=1 ; 					  		@(posedge CLOCK_50); 
		KEY[0] <=0 ; 				  			@(posedge CLOCK_50);
		KEY[0] <=1 ; 					  		@(posedge CLOCK_50); 
		KEY[0] <=0 ; 				  			@(posedge CLOCK_50);
		KEY[0] <=1 ; 				 			@(posedge CLOCK_50); 
		KEY[0] <=0 ; 							@(posedge CLOCK_50);
		KEY[0] <=1 ; 				  			@(posedge CLOCK_50); 
	   KEY[0] <=0 ; 						  	@(posedge CLOCK_50); 							
		KEY[0] <=1 ;  				  			@(posedge CLOCK_50); 
		KEY[0] <=1 ;  				  			@(posedge CLOCK_50); 
		KEY[0] <=0 ; 				  			@(posedge CLOCK_50);
		KEY[0] <=1 ; 					  		@(posedge CLOCK_50); 
		KEY[0] <=0 ; 				  			@(posedge CLOCK_50);
		KEY[0] <=1 ; 					  		@(posedge CLOCK_50); 
		KEY[0] <=0 ; 				  			@(posedge CLOCK_50);
		
		$stop;
	  end
endmodule 
