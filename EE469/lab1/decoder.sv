module decoder_5to32 (in, out);
	input logic [4:0] in;
	output logic [31:0] out;
	
	logic [3:0] enable;
	
	// four 3 to 8 and one 2 to 4
	
	decoder_2to4 dec_2to4 (.in(in[4:3]), .out(enable));
	decoder_3to8 dec0_3to8 (.in({in[2:0], enable[3]}), .out(out[31:25]));
	decoder_3to8 dec1_3to8 (.in({in[2:0], enable[2]}), .out(out[24:17]));
	decoder_3to8 dec2_3to8 (.in({in[2:0], enable[1]}), .out(out[16:8]));
	decoder_3to8 dec3_3to8 (.in({in[2:0], enable[0]}), .out(out[7:0]));
	
endmodule


module decoder_3to8 (in, out);
	input logic [2:0] in;
	output logic [7:0] out;
	
	logic [2:0] not_in;
	
	not not_in2_gate (not_in[2], in[2]);
	not not_in1_gate (not_in[1], in[1]);
	not not_in0_gate (not_in[0], in[0]);
	
	// seven
	and and_gate7 (out[7], in[2], in[1], in[0]);
	
	// six
	and and_gate6 (out[6], in[2], in[1], not_in[0]);
	
	// five
	and and_gate5 (out[5], in[2], not_in[1], in[0]);
	
	// four
	and and_gate4 (out[4], in[2], not_in[1], not_in[0]);
	
	// three
	and and_gate3 (out[3], not_in[2], in[1], in[0]);
	
	// two
	and and_gate2 (out[2], not_in[2], in[1], not_in[0]);
	
	// one
	and and_gate1 (out[1], not_in[2], not_in[1], in[0]);
	
	// zero
	and and_gate0 (out[0], not_in[2], not_in[1], not_in[0]);
	
	
endmodule


module decoder_2to4 (in, out);
	input logic [1:0] in;
	output logic [3:0] out;
	
	logic [1:0] not_in;

	not not_in1_gate (not_in[1], in[1]);
	not not_in0_gate (not_in[0], in[0]);
	
	// three
	and and_gate3 (out[3], in[1], in[0]);
	
	// two
	and and_gate2 (out[2], in[1], not_in[0]);
	
	// one
	and and_gate1 (out[1], not_in[1], in[0]);
	
	// zero
	and and_gate0 (out[0], not_in[1], not_in[0]);	
	
endmodule 




