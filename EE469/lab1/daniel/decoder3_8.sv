
//3:8 decoder
`timescale 1ps/1ps
module decoder3_8(i, d, enable);
	input logic [2:0] i;
	output logic [7:0] d;
	input logic enable;
	
	and #50 d0 (d[0], ~i[2], ~i[1], ~i[0], enable);
	and #50 d1 (d[1], ~i[2], ~i[1], i[0], enable);
	and #50 d2 (d[2], ~i[2], i[1], ~i[0], enable);
	and #50 d3 (d[3], ~i[2], i[1], i[0], enable);
	and #50 d4 (d[4], i[2], ~i[1], ~i[0], enable);
	and #50 d5 (d[5], i[2], ~i[1], i[0], enable);
	and #50 d6 (d[6], i[2], i[1], ~i[0], enable);
	and #50 d7 (d[7], i[2], i[1], i[0], enable);
	
endmodule

module decoder3_8_testbench();   
  logic [2:0] i;    
  logic [7:0] d;   
  logic enable;
  
  decoder3_8 dut (i, d, enable)  ; 
  
  integer j;
  initial begin   
		i <= 2'b00; enable <=0; #10;
	   for (j = 0; j < 8; j++) begin
			i <= j; #10;
		end
		i <= 2'b00; enable <=1; #10;
		for (j = 0; j < 8; j++) begin
			i <= j; #10;
		end
		$stop;
  end   
endmodule 