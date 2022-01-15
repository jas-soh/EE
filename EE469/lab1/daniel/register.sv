// 64 bit wide reister, built by using DFFs
module register (Din, Dout, enable, clk);

	input logic [63:0] Din;
	input logic enable, clk;
	output logic [63:0] Dout;
	
	logic [63:0] muxOut;
	genvar i;
	generate

		for(i = 0; i < 64; i = i + 1) begin : building_one_register
			mux2_1 selector (.out(muxOut[i]), .i0(Dout[i]), .i1(Din[i]), .sel(enable));
			D_FF bits (.q(Dout[i]), .d(muxOut[i]), .reset(1'b0), .clk);
		end
		
	endgenerate

endmodule

// DFF given in lab specs
module D_FF (q, d, reset, clk);
  output reg q; 
  input d, reset, clk; 
 
  always_ff @(posedge clk) 
  if (reset) 
    q <= 0;  // On reset, set to 0 
  else 
    q <= d; // Otherwise out = d 
endmodule