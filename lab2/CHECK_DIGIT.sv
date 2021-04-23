// computes the logical ~(~(A+B)*(C+D))
module CHECK_DIGIT (out,A,B,C,D);
	output logic out;
	input logic A,B,C,D;
	logic nor1, nor2;
	
	nor NorGate1 (nor1,A,B);
	nor NorGate2 (nor2,C,D);
	and AndGate (out, nor1, nor2);
	
endmodule 
