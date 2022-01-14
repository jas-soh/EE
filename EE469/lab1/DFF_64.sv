// each register has array of 64 bits
module DFF_64 (dataOut, clk, reset, dataIn, write_en);
	input logic clk, reset, write_en;
	input logic [63:0] dataIn;
	output logic [63:0] dataOut;
	
	logic [63:0] dataLoaded;
	
	genvar i;
	generate
		for (i = 0; i < 64; i++) begin: eachDFF_1
			// mux to select new data or not
			mux2_1 mux0 (.out(dataLoaded[i]), .d0(dataOut[i]), .d1(dataIn[i]), .sel(write_en));
			D_FF dff1 (.q(dataLoaded[i]), .d(dataOut[i]), .reset(1'b0), .clk);  
		end
	
	endgenerate
endmodule 