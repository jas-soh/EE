// This module displays the count on six seg-7 HEX's.
// The words 'FULL' or 'CLEAr' are also displayed when the count is 0 or at capacity, respectively.
// input: the current count of cars in the lot
// output: words (when appropriate) and the count across six 7-seg HEX's
module hexDisplay #(parameter CAPACITY=5'b11001) (HEX5, HEX4, HEX3, HEX2, HEX1, HEX0, count);
	input logic [4:0] count;
	output logic [6:0] HEX5, HEX4, HEX3, HEX2, HEX1, HEX0;
	
	logic [6:0] one, two, three, four, five, six, seven, eight, nine, zero, x;
	
	// 7-seg representation of numbers
	assign zero = 7'b1000000; // 0
	assign one = 7'b1111001; // 1
	assign two = 7'b0100100; // 2
	assign three = 7'b0110000; // 3
	assign four = 7'b0011001; // 4
	assign five = 7'b0010010; // 5
	assign six = 7'b0000010; // 6
	assign seven = 7'b1111000; // 7
	assign eight = 7'b0000000; // 8
	assign nine = 7'b0011000; // 9
	assign x = 7'bx;
	
	// displays count and words (if count is at limits 0 or capacity)
	always_comb begin
		case (count)
			5'b0: begin
				// words needed
				HEX5 = 7'b1000110; // C
				HEX4 = 7'b1000111; // L
				HEX3 = 7'b0000110; // E
				HEX2 = 7'b0001000; // A
				HEX1 = 7'b0101111; // r
				HEX0 = 7'b1000000;
			end
			
			default: begin
				if (count == CAPACITY) begin
					// words needed
					HEX5 = 7'b0001110; // F
					HEX4 = 7'b1000001; // U
					HEX3 = 7'b1000111; // L
					HEX2 = 7'b1000111; // L
				end
				
				else begin
					// no words needed
					HEX5 = 7'b1111111;
					HEX4 = 7'b1111111;
					HEX3 = 7'b1111111;
					HEX2 = 7'b1111111; 
			
				end
				
				// cases for count associated with each number in the ones place
				if ((count == 5'b01010 ) || (count == 5'b10100)) HEX0 = zero;
				else if ((count == 5'b00001) || (count == 5'b01011 ) || (count == 5'b10101)) HEX0 = one;
				else if ((count == 5'b00010) || (count == 5'b01100 ) || (count == 5'b10110)) HEX0 = two;
				else if ((count == 5'b00011) || (count == 5'b01101 ) || (count == 5'b10111)) HEX0 = three;
				else if ((count == 5'b00100) || (count == 5'b01110 ) || (count == 5'b11000)) HEX0 = four;
				else if ((count == 5'b00101) || (count == 5'b01111 ) || (count == 5'b11001)) HEX0 = five;
				else if ((count == 5'b00110) || (count == 5'b10000 )) HEX0 = six;
				else if ((count == 5'b00111) || (count == 5'b10001 )) HEX0 = seven;
				else if ((count == 5'b01000) || (count == 5'b10010 )) HEX0 = eight;
				else if ((count == 5'b01001) || (count == 5'b10011 )) HEX0 = nine;
				else HEX0 = x;
				
				// cases for count associated with each number in the tens place
				if (count < 5'b01010) HEX1 = zero;
				else if (count < 5'b10100) HEX1 = one;
				else if (count < 5'b11110) HEX1 = two;
				else HEX1 = x;
			end
		endcase
	end
endmodule 

// testbench for hexDisplay module
module hexDisplay_testbench();
	logic [4:0] count;
	logic [6:0] hex5, hex4, hex3, hex2, hex1, hex0;
	
	hexDisplay dut (hex5, hex4, hex3, hex2, hex1, hex0, count);
	
	initial begin
	
		// tests every value of count within capacity of lot
		#(1) count = 5'b000000; // 0
		#(1) count = 5'b000001; // 1
		#(1) count = 5'b000010; // 2
		#(1) count = 5'b000011; // 3
		#(1) count = 5'b000100; // 4
		#(1) count = 5'b000101; // 5
		#(1) count = 5'b000110; // 6
		#(1) count = 5'b000111; // 7
		#(1) count = 5'b001000; // 8
		#(1) count = 5'b001001; // 9
		#(1) count = 5'b001010; // 10
		#(1) count = 5'b001011; // 11
		#(1) count = 5'b001100; // 12
		#(1) count = 5'b001101; // 13
		#(1) count = 5'b001110; // 14
		#(1) count = 5'b001111; // 15
		#(1) count = 5'b010000; // 16
		#(1) count = 5'b010001; // 17
		#(1) count = 5'b010010; // 18
		#(1) count = 5'b010011; // 19
		#(1) count = 5'b010100; // 20
		#(1) count = 5'b010101; // 21
		#(1) count = 5'b010110; // 22
		#(1) count = 5'b010111; // 23
		#(1) count = 5'b011000; // 24
		#(5) count = 5'b011001; // 25
		
		#(1) count = 5'b011000; // 24
		#(1) count = 5'b010111; // 23
		#(1) count = 5'b010110; // 22
		#(1) count = 5'b010101; // 21
		#(1) count = 5'b010100; // 20
		#(1) count = 5'b010011; // 19
		#(1) count = 5'b010010; // 18
		#(1) count = 5'b010001; // 17
		#(1) count = 5'b010000; // 16
		#(1) count = 5'b001111; // 15
		#(1) count = 5'b001110; // 14
		#(1) count = 5'b001101; // 13
		#(1) count = 5'b001100; // 12
		#(1) count = 5'b001011; // 11
		#(1) count = 5'b001010; // 10
		#(1) count = 5'b001001; // 9
		#(1) count = 5'b001000; // 8
		#(1) count = 5'b000111; // 7
		#(1) count = 5'b000110; // 6
		#(1) count = 5'b000101; // 5
		#(1) count = 5'b000100; // 4
		#(1) count = 5'b000011; // 3
		#(1) count = 5'b000010; // 2
		#(1) count = 5'b000001; // 1
		#(1) count = 5'b000000; // 0
		

	end
endmodule 
