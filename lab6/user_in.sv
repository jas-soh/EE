module user_in(clk, rst, key, p);
	input logic clk, rst;
	input logic key;
	output logic p;
	
	enum {unpressed, pressed} ps, ns;
	
	always_comb begin
		case (ps)
			unpressed: if (key) ns = pressed;
				else ns = unpressed;
			pressed: if (key) ns = pressed;
				else ns = unpressed;
		endcase
	end
	
	assign p = (ps == pressed) & !key;
	
	always_ff @(posedge clk) begin
		if (rst)
			ps <= unpressed;
		else
			ps <= ns;
		end
endmodule

module user_in_testbench(); 
	logic clk;  
	logic KEY, rst;
	logic [1:0] p; 
 
	user_in dut (clk, rst, KEY, p);
 
	// Set up a simulated clock. 
	parameter CLOCK_PERIOD=100; 
	initial begin 
		clk <= 0; 
		forever #(CLOCK_PERIOD/2) clk <= ~clk; // Forever toggle the clock 
	end 
 
	// Test the design. 
	initial begin
			
					repeat(1) @(posedge clk);
		rst <= 1; 		repeat(4) @(posedge clk);
		rst <= 0; KEY <= 0; 	repeat(2) @(posedge clk);
			  KEY <= 1;	repeat(2) @(posedge clk);
		rst <= 1; 		repeat(2) @(posedge clk);
	end
endmodule
