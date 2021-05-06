module lights (clk, reset, w, out); 
	input logic clk, reset;
	input logic [0:1] w; 
	output logic [0:2] out; 
	// State variables 
	enum logic[2:0] { left=3'b100, right=3'b001, outside=3'b101, center=3'b010 } ps, ns; 
 
	// Next State logic 
	always_comb begin 
		ns=center;
		case (ps) 
			left:    if (w == 2'b01) ns = right; 
					   else if (w == (2'b00 || 2'b10)) ns = center;  
						//else if (w == 2'b10) ns = center;
			right: if (w == (2'b00 || 2'b01)) ns = center; 
					   //else if (w == 2'b01) ns = center; 
						else if (w == 2'b10) ns = left;
			center: if (w == 2'b00) ns = outside; 
					   else if (w == 2'b01) ns = left; 
						else if (w == 2'b10) ns = right;
			outside: ns = center; 
					   //else if (w == 2'b01) ns = center; 
						//else if (w == 2'b10) ns = center;
		endcase 
	end 
 
	// Output logic - could also be another always_comb block. 
	assign out = ps; 
 
	// DFFs 
	always_ff @(posedge clk) begin 
		if (reset) 
			ps <= center; 
		else 
			ps <= ns; 
	end 
 
endmodule 
