// This module is the last step before outputing the read data.
// A 32:1 mux is used to output the data and that process must be done 64 times because each row has 64 columns
module mux_64x32_1 (data, readReg, readData);
	input logic [31:0][63:0] data;
	input logic [4:0] readReg;
	output logic [63:0] readData;

	
	logic [63:0][31:0] data_transpose;
	genvar j,k;
	generate
		for (j = 0; j < 63; j++) begin: eachCol
			 for (k = 0; k < 31; k++) begin: eachRow
				assign data_transpose[j][k] = data[k][j];
			 end
		end
	endgenerate

	genvar i;
	generate
		for (j = 0; j < 63; j++) begin: eachTransposedRow
			mux32_1 mux1 (.out(readData[j]), .d(data_transpose[i]), .sel(readReg));
		end
	endgenerate
endmodule 