module mux2_1 (out, d0, d1, sel);
	input logic d0, d1, sel;
	output logic out;
	
	logic inv_sel, and0_result, and1_result;
	
	not not_gate (inv_sel, sel);
	and and_gate0 (and0_result, d0, inv_sel);
	and and_gate1 (and1_result, d1, sel);
	or or_gate (out, and0_result, and1_result);

	
endmodule



//module m21(Y, D0, D1, S);
//output Y;
//input D0, D1, S;
//wire T1, T2, T3;
//and_gate u1(T1, D1, S);
//not_gate u2(T2, S);
//and_gate u3(T3, D0, T2);
//or_gate u4(Y, T1, T3);
//endmodule