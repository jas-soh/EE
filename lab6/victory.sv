module victory(clk, rst, L, R, L_edge, R_edge, hex);
  input logic clk, rst;
  input logic L_edge, R_edge;
  output logic [6:0] hex;
  
  enum { L_win=7'b1111111, R_win=7'b1111111, no_win=7'b1111111 } ps, ns;
  
  always_comb begin
    case (ps)
      no_win: if (L_edge & L & !R) ns = win;
              else if (R_edge & R & !L) ns = win;
      R_win: ns = R_win;
      L_win: ns = L_win;
      default: ns = no_win;
  end
      
  hex = ps;
  
  always_ff @(posedge clk) begin
		if (rst)
			ps <= no_win;
		else
			ps <= ns;			
		end
endmodule 
