// This module is the controller FSM for the bit counter.
// Inputs: 1-bit signals clock, reset
// 	start - start signal to begin operation
//		done - done signal to indicate algo is finished
//		A - n bit register
module controller #(parameter reg_size = 8) (clk, reset, start, A, load_A, shift_en, done);
	input logic clk, reset, start;
	input logic [reg_size-1:0] A;
	output logic load_A, shift_en, done;

	enum {S_1, S_2, S_3} ps, ns;
	
	// combinational logic for next state
	always_comb begin
		case (ps)
			S_1: // idle state
				if (start) ns = S_2;
				else ns = S_1;
			S_2: // shift state
				if (A == 0) ns = S_3;
				else ns = S_2;
			S_3: // done state
				if (!(start)) ns = S_1;
				else ns = S_3;
			default: ns = S_1;
		endcase
	end
	
	// tranisition to next state unless reset
	always_ff @(posedge clk) begin
		if (reset) ps <= S_1;
		else ps <= ns;
	end
	
	// outputs
	assign load_A = (ps == S_1);
	assign shift_en = (ps == S_2);
	assign done = (ps == S_3);
	
endmodule 