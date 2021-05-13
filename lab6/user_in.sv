module user_in(clk, rst, key, p);
	input logic clk, rst;
	input logic [1:0] key;
	output logic [1:0] p;
	logic [1:0] stable_p;
	
	enum {unpressed, pressed} ps, ns;
	
	genvar i;
	generate
		for(i = 0; i < 2; i++) begin : eachplayer
				two_dffs df (.clk, .rst, .d(key[i]), .q(stable_p[i]));
				is_pressed ip (.clk, .rst, .stable_p(stable_p[i]), .input_p(p[i]));
		end
	endgenerate
endmodule 

module two_dffs (clk, rst, d, q);
	input logic clk, rst, d;
	output logic q;
	logic n;
	
	always_ff @(posedge clk)
		begin
		if (rst)
			begin
				n <= 0; 
				q <= 0;
			end
		else
			n <= d;
			q <= n; 
		
		end
endmodule 

module is_pressed (clk, rst, stable_p, input_p);
	input logic clk, rst;
	input logic stable_p;
	output logic input_p;
	
	enum {unpressed, pressed} ps, ns;
	
	always_comb begin
		case (ps)
			unpressed: if (stable_p) ns = pressed;
				else ns = unpressed;
			pressed: if (stable_p) ns = pressed;
				else ns = unpressed;
		endcase
	end
	
	assign input_p = (ps == pressed);
	
	always_ff @(posedge clk) begin
		if (rst)
			ps <= unpressed;
		else
			ps <= ns;
		end
endmodule
