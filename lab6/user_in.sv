module user_in(clk, rst, key, p);
	input logic clk, rst;
	input logic [1:0] key;
	output logic [1:0] p;
	
	enum {unpressed, pressed} ps, ns;
	
	always_comb begin
		case (ps)
			unpressed: if (key) ns = pressed;
				else ns = unpressed;
			pressed: if (key) ns = pressed;
				else ns = unpressed;
		endcase
	end
	
	assign p = (ps == pressed);
	
	always_ff @(posedge clk) begin
		if (rst)
			ps <= unpressed;
		else
			ps <= ns;
		end
endmodule
