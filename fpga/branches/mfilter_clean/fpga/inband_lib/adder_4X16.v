module adder_4X16(input clk, input reset, input [15:0] in_0, input [15:0] in_1, 
                  input [15:0] in_2, input [15:0] in_3, output reg [15:0] out);

    always@(posedge clk)
        if(reset)
            out <= 0;
        else
            out <= in_0 + in_1 + in_2 + in_3;

endmodule
 


