module mux8_1 (out, d, sel);
	input logic [7:0] d;
	input logic [2:0] sel;
	output logic out;
	
	logic mux0_out, mux1_out;
	
	mux4_1 mux0 (.out(mux0_out), .d(d[3:0]), .sel(sel[1:0]));
	mux4_1 mux1 (.out(mux1_out), .d(d[7:4]), .sel(sel[1:0]));
	mux2_1 mux2 (.out, .d0(mux0_out), .d1(mux1_out), .sel(sel[2]));
	
endmodule 