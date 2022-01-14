module mux4_1 (out, d, sel);
	input logic [1:0] sel;
	input logic [3:0] d;
	output logic out;
	
	logic mux_out0, mux_out1;
	
	mux2_1 mux0 (.out(mux_out0), .d0(d[0]), .d1(d[1]), .sel(sel[0]));
	mux2_1 mux1 (.out(mux_out1), .d0(d[2]), .d1(d[3]), .sel(sel[0]));
	
	mux2_1 mux3 (.out, .d0(mux_out0), .d1(mux_out1), .sel(sel[1]));
	
endmodule 