module victory(clk, rst, L, R, L_edge, R_edge, hex);
  input logic clk, rst, L, R;
  input logic L_edge, R_edge;
  output logic [6:0] hex;
  
  enum logic[6:0] { L_win=7'b1111110, R_win=7'b0111111, no_win=7'b1011111 } ps, ns;
  
  always_comb begin
	ns = no_win;
    case (ps)
      no_win: if (L_edge & L & !R) ns = R_win;
              else if (R_edge & R & !L) ns = L_win;
      R_win: ns = R_win;
      L_win: ns = L_win;
	endcase 
  end
      
  assign hex = ps;
  
  always_ff @(posedge clk) begin
		if (rst)
			ps <= no_win;
		else
			ps <= ns;			
		end
endmodule 
