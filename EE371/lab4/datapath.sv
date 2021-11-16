module datapath #(parameter reg_size = 8) (clk, reset, data_in, load_A, shift_en, result, data);
	input logic clk, reset, load_A, shift_en;
	input logic [reg_size-1:0] data_in;
	output logic [2:0] result;
	output logic [reg_size-1:0] data;
	
	logic [reg_size-1:0] shifted_data;
	//logic [reg_size-1:0] data_initial;
	//logic [reg_size-1:0] data;
	//logic [reg_size-1:0] data_out;

	// ----------- loading data, must be in state 1 -----------
	// load registerloads data until system starts
	always_ff @(posedge clk) begin
		if (reset) data <= '0;
		else if (load_A) data <= data_in;
		else data <= shifted_data;
	end
	
	// ---------- shifting data, must be in state 2 ------------
	shifter sh (.data, .shifted_data);
	
	// ---------- adding to result -------------
	// adding +1 to the result count if the bit is 1
	logic upcount_en;
	always_ff @(posedge clk) begin
		if (data[0] == 1) upcount_en = 1;
		else upcount_en = 0;
	end
	upcounter uc (.clk, .reset, .upcount_en, .result);
	
endmodule 

module datapath_testbench ();
	reg clk, reset, load_A, shift_en;
	reg [7:0] data_in;
	wire [2:0] result;
	wire [7:0] data;
	
	datapath dut (.clk, .reset, .data_in, .load_A, .shift_en, .result, .data);
	
	parameter CLOCK_PERIOD = 100;
	initial begin
		clk <= 0;
		forever #(CLOCK_PERIOD/2) clk <= ~clk; // Forever toggle the clock
	end
	
	initial begin
		// resetting
		reset <= 1; data_in <= 8'b10101010; load_A <= 0; shift_en <= 0; @(posedge clk);
		reset <= 1; data_in <= 8'b10101010; load_A <= 0; shift_en <= 0; @(posedge clk);
		
		// loading data until start; data_in is changing
		reset <= 0; data_in <= 8'b10101010; load_A <= 1; shift_en <= 0; @(posedge clk);
		reset <= 0; data_in <= 8'b10000010; load_A <= 1; shift_en <= 0; @(posedge clk);
		reset <= 0; data_in <= 8'b11111111; load_A <= 1; shift_en <= 0; @(posedge clk);
		
		// start now, so no longer loading, now shifting
		// make sure data_in changing does not affect anything
		reset <= 0; data_in <= 8'b11111111; load_A <= 0; shift_en <= 1; @(posedge clk);
		reset <= 0; data_in <= 8'b11111111; load_A <= 0; shift_en <= 1; @(posedge clk);
		reset <= 0; data_in <= 8'b11111111; load_A <= 0; shift_en <= 1; @(posedge clk);
		reset <= 0; data_in <= 8'b11111111; load_A <= 0; shift_en <= 1; @(posedge clk);
		reset <= 0; data_in <= 8'b00000000; load_A <= 0; shift_en <= 1; @(posedge clk);
		reset <= 0; data_in <= 8'b00000000; load_A <= 0; shift_en <= 1; @(posedge clk);
		reset <= 0; data_in <= 8'b00000000; load_A <= 0; shift_en <= 1; @(posedge clk);
		reset <= 0; data_in <= 8'b00000000; load_A <= 0; shift_en <= 1; @(posedge clk);
		reset <= 0; data_in <= 8'b00000000; load_A <= 0; shift_en <= 1; @(posedge clk);
		reset <= 0; data_in <= 8'b00000000; load_A <= 0; shift_en <= 1; @(posedge clk);
		reset <= 0; data_in <= 8'b00000000; load_A <= 0; shift_en <= 1; @(posedge clk);
		reset <= 0; data_in <= 8'b00000000; load_A <= 0; shift_en <= 1; @(posedge clk);
		reset <= 0; data_in <= 8'b00000000; load_A <= 0; shift_en <= 1; @(posedge clk);
	
		$stop;
	end
endmodule 