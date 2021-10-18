module DE1_SoC (CLOCK_50, HEX0, HEX1, HEX2, HEX3, HEX4, HEX5, SW, KEY);
	input logic CLOCK_50;
	input logic [9:0] SW;
	input logic [3:0] KEY;
	output logic [6:0] HEX0, HEX1, HEX2, HEX3, HEX4, HEX5;
	
	// set HEX 1 and 3 to off
	assign HEX1 = 7'b1111111;
	assign HEX3 = 7'b1111111;
	
	// use switches SW 3−0 to provide input data for the RAM
	logic [3:0] data_in, data_out;
	assign data_in = SW[3:0];
	
	// use switches SW 8 − 4 to specify the address.
	logic [4:0] address;
	assign address = SW[8:4];
	
	// use SW 9 as the Write signal 
	logic wr_en;
	assign wr_en = SW[9];
	
	// use KEY 0 as theClock input.
	logic clk;
	assign clk = ~KEY[0];
	
	// defining memory unit as multidimensional array
	//logic [3:0] memory_array [31:0];
	RAM_unit ram (.data_out, .clk, .wr_en, .address, .data_in);
	
	// Using hexadecimal, show the address value on the 7-segment displays HEX5 − 4
	// and show the data being input to the memory on HEX2, and show the data read out of the memory on HEX0.
	hexDisplay address_display1 (.hex(HEX5), .num({3'b0,address[4]}));
	hexDisplay address_display0 (.hex(HEX4), .num(address[3:0]));
	hexDisplay data_in_display (.hex(HEX2), .num(data_in));
	hexDisplay data_out_display (.hex(HEX0), .num(data_out));
	
	
endmodule 
