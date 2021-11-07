
module line_drawer(
	input logic clk, reset,
	input logic [9:0] x0, x1,
	input logic [8:0] y0, y1,
	output logic [9:0] x,
	output logic [8:0] y,
	output logic [8:0] statex0, statex1, 
	output logic r
	);
	

	 //* You'll need to create some registers to keep track of things
	 //* such as error and direction
	 //* Example: 
	logic signed [10:0] abs_dx, x0_adj,x1_adj; 
	logic signed [9:0] abs_dy, y0_adj, y1_adj; 
	
	logic is_steep;
	
	// calculates the absolute value of x and y differences
	// and determines if the line is steep or not
	assign abs_dy = (y1 > y0) ? (y1 - y0) : (y0 - y1);
	assign abs_dx = (x1 > x0) ? (x1 - x0) : (x0 - x1);
	assign is_steep = (abs_dy >= abs_dx);
	
	// if the line is steep, switch axis
	
	always_comb begin
		if (is_steep) begin
			if (y0 < y1) begin 
				x0_adj = x0;
				x1_adj = x1;
				y0_adj = y0;
				y1_adj = y1;
			end
			else begin 
				x0_adj = x1;
				x1_adj = x0;
				y0_adj = y1;
				y1_adj = y0;
			end
		end
		else begin 
			if (x0 < x1) begin 
				x0_adj = x0;
				x1_adj = x1;
				y0_adj = y0;
				y1_adj = y1;
			end
			else begin
				x0_adj = x1;
				x1_adj = x0;
				y0_adj = y1;
				y1_adj = y0;
			end
		end
	end
	
	// calculates the difference of the current x and y
	// determines if y is increasing or not
	logic x_step, y_step;
	
	assign x_step = (x0_adj < x1_adj) ? 1 : -1;
	assign y_step = (y0_adj < y1_adj) ? 1 : -1;
	
	// keeping track of error and next state variables
	logic signed [11:0] error, next_error;
	logic [9:0] next_x, next_y;
	
	// next state logic to determine if points are incremented
	always_comb begin	
		// steep so y is incremented every time
		if ((is_steep == 1) && (y < y1_adj)) begin
			next_y = y + 1;
			if ((error + abs_dx) > 0) begin // increment x
				next_x = x + x_step;
				next_error = error + abs_dx - abs_dy;
			end
		
			else begin
				next_x = x;
				next_error = error + abs_dx;
			end
		end
		
		// gradual so x is incremented every time
		else if (x < x1_adj) begin
			next_x = x + 1;
			if ((error + abs_dy) >= 0) begin // increment y
				next_y = y + y_step;
				next_error = error + abs_dy - abs_dx;
			end
			else begin
				next_y = y;
				next_error = error + abs_dy;
			end
		end
		
		else begin
			next_x = x;
			next_y = y;
			next_error = error;
		end
		
	end
	
	// ps -> ns at rising clock edge
	always_ff @(posedge clk) begin
		// resets to initial start point
		if (reset) begin
			x <= x0_adj;
			y <= y0_adj;
			if (is_steep) error <= -abs_dy/2;
			else error <= -abs_dx/2;
		end
	   else begin
			x <= next_x;
			y <= next_y;
			error <= next_error;
		end
		
		if ((x == x1_adj) && (y == y1_adj)) begin
		    statex0 <= statex0 + 1;
		    statex1 <= statex1 + 1;
		    r <= 1;
		end
		else begin
		    statex0 <= statex0;
		    statex1 <= statex1;
		    r <= 0;
		end
	end
	
endmodule




// This module tests the previous module
module line_drawer_testbench();
	reg clk, reset, clear;
	reg [9:0] x0, x1;
	reg [8:0] y0, y1;
	wire [9:0] x;
	wire [8:0] y;
	wire [8:0] statex0, statex1;
	wire r;
	
	parameter CLOCK_PERIOD = 100;
	initial begin
		clk <= 0;
		forever #(CLOCK_PERIOD/2) clk <= ~clk;
	end
	
	line_drawer dut (.*);
	
	initial begin
		// perfectly diagonal line from origin
		reset <= 1; x0 <= 10; y0 <= 10; x1 <= 40; y1 <= 10; repeat(3) @(posedge clk);
		reset <= 0; x0 <= 10; y0 <= 10; x1 <= 40; y1 <= 10; repeat(45) @(posedge clk);
		reset <= 1; x0 <= 50; y0 <= 50; x1 <= 90; y1 <= 90; repeat(3) @(posedge clk);
		reset <= 0; x0 <= 50; y0 <= 50; x1 <= 90; y1 <= 90; repeat(50) @(posedge clk);
		$stop;
	end
endmodule
