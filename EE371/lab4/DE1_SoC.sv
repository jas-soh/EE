module DE1_SoC (HEX0, HEX1, HEX2, HEX3, HEX4, HEX5, KEY, SW, LEDR, CLOCK_50);
   output logic [6:0]  HEX0, HEX1, HEX2, HEX3, HEX4, HEX5;
	output logic [9:0]  LEDR;
   input  logic [3:0]  KEY;
   input  logic [9:0]  SW;
   input logic CLOCK_50;
	
	// assign unused hex displays
	assign HEX1 = 7'b1111111;
	assign HEX2 = 7'b1111111;
	assign HEX3 = 7'b1111111;
	assign HEX4 = 7'b1111111;
	assign HEX5 = 7'b1111111;
	
	// use logic to make interconnections
	//logic clk, reset, start, done;
	logic [7:0] A;
	logic [2:0] result;
	
	// synchronizing reset
	//always_ff @(posedge clk) begin
		//reset <= ~KEY[0];
	//end
	
	//assign clk = CLOCK_50;
	//assign start = SW[9];
	//assign A = SW[7:0];
	//assign LEDR[9] = done;
	
	// instantiting bit counter. SW[7:0] as input, SW[9] as start, LEDR[9] as done,
	// result to a bus connecting to the hex display module
	logic load_A, shift_en, done;
	logic [7:0] data;
	
	controller c (.clk(CLOCK_50), .reset(~KEY[0]), .start(SW[9]), .A, .load_A, .shift_en, .done);
	datapath dp (.clk(CLOCK_50), .reset(~KEY[0]), .data_in(A), .load_A, .shift_en, .result, .data);
	
	// instantiating hex driver. result bus as input, HEx0 as output
	//hex_driver hd1 (.in(result), .out(HEX0));
	
endmodule
