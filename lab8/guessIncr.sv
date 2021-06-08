module guessIncr(clk, rst, incr, out);
	input logic clk, rst, incr;
	output logic [1:0] out;
	
	always_ff @(posedge clk) begin
		if (rst) out <= 0;
		else if (incr) out <= out + 2'b01;
	end
endmodule 

module triesIncr(clk, rst, incr, out);
	input logic clk, rst, incr;
	output logic [2:0] out;
	
	always_ff @(posedge clk) begin
		if (rst) out <= 0;
		else if (incr) out <= out + 3'b001;
	end
endmodule 

module incr(clk, rst, sw, out);
	input logic clk, rst, sw;
	output logic out;
	enum logic [2:0] {on, off, held} ps, ns;
	
	always_comb begin
		case (ps)
			off: if (sw) ns = on;
					else ns = off;
			on: if (sw) ns = held;
					else ns = off;
			held: if (sw) ns = held;
					else ns = off;
		endcase
	end
	
	assign out = (ps == on);
	
	always_ff @(posedge clk) begin
		if (rst)
			ps <= off;
		else
			ps <= ns;
	end
endmodule 
