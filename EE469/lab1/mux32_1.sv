module mux32_1 (out, d, sel);
	input logic out;
	input logic [31:0] d;
	output logic [4:0] sel;
	
	logic mux0_out, mux1_out;
	
	mux16_1 mux0 (.out(mux0_out), .d(d[15:0]), .sel(sel[3:0]));
	mux16_1 mux1 (.out(mux1_out), .d(d[31:16]), .sel(sel[3:0]));
	mux2_1 mux2 (.out, .d0(mux0_out), .d1(mux1_out), .sel(sel[4]));

endmodule 