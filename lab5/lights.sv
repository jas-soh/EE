module lights (clk, reset, w, out); 
	input logic clk, reset;
	input logic [0:1] w; 
	output logic [0:2] out; 
	
	// State variables 
	enum logic[2:0] { left=3'b100, right=3'b001, outside=3'b101, center=3'b010 } ps, ns; 
 
	// Next State logic 
	always_comb begin 
		ns=center;
		case (ps) 
			left:    if (w == 2'b01) ns = right; 
			right: 	if (w == 2'b10) ns = left; 
			center: if (w == 2'b00) ns = outside; 
						else if (w == 2'b01) ns = left;
						else if (w == 2'b10) ns = right;
		endcase 
	end 
 
	// Output logic
	assign out = ps; 
 
	// DFFs 
	always_ff @(posedge clk) begin 
		if (reset) 
			ps <= center; 
		else 
			ps <= ns; 
	end 
 
endmodule 

module lights_testbench(); 
	logic clk, reset;
	logic [0:1] w; 
	logic [0:2] out;
 
	lights dut (clk, reset, w, out); 
 
	// Set up a simulated clock. 
	parameter CLOCK_PERIOD=100; 
	initial begin 
		clk <= 0; 
		forever #(CLOCK_PERIOD/2) clk <= ~clk; // Forever toggle the clock 
	end 
 
	// Set up the inputs to the design. Each line is a clock cycle. 
	initial begin 
										@(posedge clk); 
		reset <= 1; 				@(posedge clk); // Always reset FSMs at start 
		reset <= 0; w <= 2'b00; @(posedge clk); 
						w <= 2'b01; @(posedge clk); 
						w <= 2'b10; @(posedge clk); 
 
		$stop; // End the simulation. 
	end 
endmodule
