module hexDisplay (hex, num);
	input logic [3:0] num;
	output logic [6:0] hex;
	
	// address is input in binary form
	always_comb begin
		case (num)
			4'b0000: hex = 7'b1000000; // 0
			4'b0001: hex = 7'b1111001; // 1
			4'b0010: hex = 7'b0100100; // 2
			4'b0011: hex = 7'b0110000; // 3
			4'b0100: hex = 7'b0011001; // 4
			4'b0101: hex = 7'b0010010; // 5
			4'b0110: hex = 7'b0000010; // 6
			4'b0111: hex = 7'b1111000; // 7
			4'b1000: hex = 7'b0000000; // 8
			4'b1001: hex = 7'b0011000; // 9		
			4'b1010: hex = 7'b0001000; // A
			4'b1011: hex = 7'b0000011; // B
			4'b1100: hex = 7'b0100111; // C
			4'b1101: hex = 7'b0100001; // D
			4'b1110: hex = 7'b0000110; // E
			4'b1111: hex = 7'b0001110; // F
			
		endcase
	end

endmodule 

module hexDisplay_testbench ();
	reg [3:0] num;
	wire [6:0] hex; 
	
	hexDisplay dut (.hex, .num);
	
	initial begin
		#(10) num = 4'b0000; 
		#(10) num = 4'b0001; 
		#(10) num = 4'b0010; 
		#(10) num = 4'b0011; 
		#(10) num = 4'b0100; 
		#(10) num = 4'b0101; 
		#(10) num = 4'b0110; 
		#(10) num = 4'b0111; 
		#(10) num = 4'b1000; 
		#(10) num = 4'b1001;
		#(10) num = 4'b1010;
		#(10) num = 4'b1011;
		#(10) num = 4'b1100;
		#(10) num = 4'b1101;
		#(10) num = 4'b1110;
		#(10) num = 4'b1111;
	end
endmodule 
