module counter #(parameter WIDTH=3)
	(clk, rst, hex, incr);
	
	output logic [6:0] hex;
	input logic 				 clk, rst, incr;
	logic [WIDTH-1:0] num;
	
	always_ff @(posedge clk) begin
		if (rst) num <= 0;
		else if (incr) num <= num + 1;
	end
	
	seg7 s (.bcd(num), .leds(hex));

endmodule 

module seg7 (bcd, leds);    
	input  logic  [2:0] bcd;
	output logic  [6:0] leds; 
	
	always_comb begin
		case (bcd)            
			//          Light: 6543210          
			3'b000: leds = ~7'b0111111; // 0          
			3'b001: leds = ~7'b0000110; // 1          
			3'b010: leds = ~7'b1011011; // 2          
			3'b011: leds = ~7'b1001111; // 3          
			3'b100: leds = ~7'b1100110; // 4          
			3'b101: leds = ~7'b1101101; // 5          
			3'b110: leds = ~7'b1111101; // 6          
			3'b111: leds = ~7'b0000111; // 7          
			default:   leds   =  ~7'bx;         
		endcase      
	end
endmodule 

module counter_testbench ();
	logic clk, rst, incr;
	logic [6:0] hex;
	
	counter dut (clk, rst, hex, incr);
	
	// Set up a simulated clock.
	parameter CLOCK_PERIOD=100;
	initial begin
		clk <= 0;
		forever #(CLOCK_PERIOD/2) clk <= ~clk; // Forever toggle the clock
		
	end
	
	// Set up the inputs to the design. Each line is a clock cycle.
	initial begin
													@(posedge clk);
	 rst <= 1;	   							@(posedge clk);
	 rst <= 0;					repeat(2) 	@(posedge clk);
	 rst <= 0; incr <= 1;	repeat(10) 	@(posedge clk);
															 
	$stop; // End the simulation.
	end
endmodule 
