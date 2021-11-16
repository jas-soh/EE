// This module right shifts input data 1 bit, if enable is true

module shifter #(parameter reg_size = 8) (data, shifted_data);
	input logic [reg_size-1:0] data;
	output logic [reg_size-1:0] shifted_data;
	
	assign shifted_data[reg_size-1] = 0;
	assign shifted_data[reg_size-2 : 0] = data[reg_size-1 : 1];

endmodule 

// This module is the testbench for the shifter module
module shifter_testbench ();
	logic [7:0] data;
	logic [7:0] shifted_data;
	
	shifter dut (.data, .shifted_data);
	
	initial begin
		data <= 8'b10101010;
		data <= 8'b10101010;
		data <= 8'b10101010;
		data <= 8'b10101010;
		data <= 8'b01010101;
		data <= 8'b01010101;
		data <= 8'b00101010;
		data <= 8'b00101010;
		data <= 8'b00010101;
		data <= 8'b00010101;	
		data <= 8'b00001010;
		data <= 8'b00001010;
		data <= 8'b00000101;
		data <= 8'b00000101;
		data <= 8'b00000010;
		data <= 8'b00000010;
		data <= 8'b00000001;
		data <= 8'b00000001;
		data <= 8'b00000000;
		data <= 8'b00000000;
	end
endmodule 