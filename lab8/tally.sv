module wrongPlace(rst, enable, guess, sol, out);
  input logic st, enable;
  input logic [7:0] guess, sol;
  output logic [7:0] out;
  logic [7:0] tallyG, tallyS;
  
  always comb_begin
    if (rst)
      out = 7'b0000000;
    else if (!enable)
      out = out;
    else
      tally tallyGuess(guess, tallyG);
      tally tallySol(sol, tallyS);
      genvar i;
      generate
        for (i = 7; i > -1; i -= 2)
          if (tallyG[i:i-1] > tallyS[i:i-1])
            out[i:i-1] = tallyS[i:i-1);
          else
            out[i:i-1] = tallyG[i:i-1];
        end 
      endgenerate
  end
  
endmodule 

module tally(nums, out);
  input logic [7:0] nums;
  output logic [7:0] out;
  
  genvar i;
  generate
    for(i = 7; i > -1; i -= 2)
      case (num[i:i-1])
        2'b00: out[1:0] = out[1:0] + 2'b01;
        2'b01: out[3:2] = out[3:2] + 2'b01;
        2'b10: out[5:4] = out[5:4] + 2'b01;
        2'b11: out[7:6] = out[7:6] + 2'b01;
      endcase
    end
  endgenerate 
endmodule
