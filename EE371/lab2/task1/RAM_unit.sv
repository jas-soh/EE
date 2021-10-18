module RAM_unit (data_out, clk, wr_en, address, data_in);
	input logic wr_en, clk;
	input logic [4:0] address;
	input logic [3:0] data_in;
	output logic [3:0] data_out;
	
	logic [3:0] memory_array [0:31];
	
	always_ff @(posedge clk) begin
		if (wr_en) begin
			memory_array[address] <= data_in;
		end

		data_out <= memory_array[address];
			
	end


endmodule 

module RAM_unit_testbench();
	reg wr_en,clk;
	reg [4:0] address;
	reg [3:0] data_in;
	//reg [3:0] memory_array [0:31];
	wire [3:0] data_out;
	
	RAM_unit dut (.data_out, .clk, .wr_en, .address, .data_in);
	
	parameter CLOCK_PERIOD = 100;
	initial begin
		clk <= 0;
		forever #(CLOCK_PERIOD/2) clk <= ~clk; // Forever toggle the clock
	end
	
	/*
	initial begin
		wr_en <= 1'b1; address <= 5'b0000; data_in <= 4'b0000; @(posedge clk);
		wr_en <= 1'b0; address <= 5'b0000; data_in <= 4'b0001; @(posedge clk);
		wr_en <= 1'b1; address <= 5'b0000; data_in <= 4'b0001; @(posedge clk);
		wr_en <= 1'b1; address <= 5'b0000; data_in <= 4'b0010; @(posedge clk);
		wr_en <= 1'b1; address <= 5'b0000; data_in <= 4'b0100; @(posedge clk);
		wr_en <= 1'b0; address <= 5'b0000; data_in <= 4'b0000; @(posedge clk);
		$stop;
	end
	*/
	
	initial begin
		// resetting the module
		
		// writing some random data into the RAM
		address <= 5'b00001; data_in <= 4'b0001; wr_en <= 1'b1; @(posedge clk);
		address <= 5'b00010; data_in <= 4'b0010; wr_en <= 1'b1; @(posedge clk);
		address <= 5'b00011; data_in <= 4'b0011; wr_en <= 1'b1; @(posedge clk);
		address <= 5'b11111; data_in <= 4'b1111; wr_en <= 1'b1; @(posedge clk);
						
		// reading the previously written data from the RAM
		address <= 5'b00001; data_in <= 4'b1010; wr_en <= 1'b0; @(posedge clk);
		address <= 5'b00010; data_in <= 4'b1010; wr_en <= 1'b0; @(posedge clk);
		address <= 5'b00011; data_in <= 4'b1010; wr_en <= 1'b0; @(posedge clk);
		address <= 5'b11111; data_in <= 4'b1010; wr_en <= 1'b0; @(posedge clk);
		$stop;
	end
	
endmodule 
