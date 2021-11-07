// Top level module that handles inputs and outputs of the FPGA
// Description: This program draws lines between two points that are generated
// by up-counters within the project


module DE1_SoC (HEX0, HEX1, HEX2, HEX3, HEX4, HEX5, KEY, LEDR, SW, CLOCK_50, 
	VGA_R, VGA_G, VGA_B, VGA_BLANK_N, VGA_CLK, VGA_HS, VGA_SYNC_N, VGA_VS);
	
	output logic [6:0] HEX0, HEX1, HEX2, HEX3, HEX4, HEX5;
	output logic [9:0] LEDR;
	input logic [3:0] KEY;
	input logic [9:0] SW;

	input CLOCK_50;
	output [7:0] VGA_R;
	output [7:0] VGA_G;
	output [7:0] VGA_B;
	output VGA_BLANK_N;
	output VGA_CLK;
	output VGA_HS;
	output VGA_SYNC_N;
	output VGA_VS;
	
	assign HEX0 = '1;
	assign HEX1 = '1;
	assign HEX2 = '1;
	assign HEX3 = '1;
	assign HEX4 = '1;
	assign HEX5 = '1;
	assign LEDR = SW;
	
	logic [9:0] x0, x1, x;
	logic [8:0] y0, y1, y;
	logic frame_start;
	logic pixel_color;
	
	
	//////// DOUBLE_FRAME_BUFFER ////////
	logic dfb_en;
	assign dfb_en = 1'b0;
	/////////////////////////////////////
	
	logic [31:0] div_clk;
	clock_divider cdiv1 (.clock(CLOCK_50), .reset(1'b0), .divided_clocks(div_clk));
	logic clkSelect;
	assign clkSelect = div_clk[23];
	
	VGA_framebuffer fb(.clk(CLOCK_50), .rst(1'b0), .x, .y,
				.pixel_color, .pixel_write(1'b1), .dfb_en, .frame_start,
				.VGA_R, .VGA_G, .VGA_B, .VGA_CLK, .VGA_HS, .VGA_VS,
				.VGA_BLANK_N, .VGA_SYNC_N);
	
	logic finished, reset, r;
	
	// draw lines between (x0, y0) and (x1, y1)
	line_drawer lines (.clk(whichClock), .reset(r),
				.x0, .y0, .x1, .y1, .x, .y, .statex0, .statex1, .r);

	//set_end_points pts (.clk(clkSelect), .en(finished),.reset(~KEY[0]), .x0, .x1, .r);
	// draw an arbitrary line
	//assign y0 = 0;
	//assign y1 = 500;
	logic [8:0] statex0, statex1;
	logic whichClock;
	initial begin
	    statex0 = 0;
	    statex1 = 0;
	end
	assign y0 = 0;
    assign y1 = 500;
    
    logic color_clk;
    always_comb begin
        if (SW[0]) color_clk = CLOCK_50;
        else color_clk = div_clk[20];
    end
    
    always_ff @(posedge color_clk) begin
        if (SW[0]) pixel_color = 1'b0;
        else pixel_color <= ~pixel_color;
    end
	always_comb begin
	    //pixel_color = (SW[0] ? 0 : 1);
	    whichClock = (SW[0] ? div_clk[5] : div_clk[13]);
	    if (statex0 == 500) begin 
	        x0 = 0;
	        x1 = 0;
	   end
	   else begin 
	        x0 = statex0;
	        x1 = statex1;
	   end
            
	end
	
	//counter c0 (.address(x1), .clk(clkSelect), .reset);
	//assign x0 = 0;
	
	
	initial pixel_color = 1'b1;
	
endmodule


module DE1_SoC_testbench();
	logic [6:0] HEX0, HEX1, HEX2, HEX3, HEX4, HEX5;
	logic [9:0] LEDR;
	logic [3:0] KEY;
	logic [9:0] SW;

	logic CLOCK_50;
	logic [7:0] VGA_R;
	logic [7:0] VGA_G;
	logic [7:0] VGA_B;
	logic VGA_BLANK_N;
	logic VGA_CLK;
	logic VGA_HS;
	logic VGA_SYNC_N;
	logic VGA_VS;


	parameter CLOCK_PERIOD = 100;
	initial begin
		CLOCK_50 <= 0;
		forever #(CLOCK_PERIOD/2) CLOCK_50 <= ~CLOCK_50;
	end
	
	DE1_SoC dut (.*);
	
	initial begin
		// perfectly diagonal line from origin
		KEY[0] <= 1; repeat(2) @(posedge CLOCK_50);
		KEY[0] <= 0; repeat(100) @(posedge CLOCK_50);
		
		$stop;
	end
endmodule
