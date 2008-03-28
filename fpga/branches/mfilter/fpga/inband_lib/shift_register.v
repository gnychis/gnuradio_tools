module shift_register(input clk, input reset, input rxstrobe, 
                 input [15:0] in_sample, output wire [15:0] out_sample, 
                 input [2:0] sel, output reg [15:0] data);
  
    reg [15:0] shift [5:0];
    integer i;
    assign out_sample = shift[5];

    always @ (posedge clk)
        if(reset)
          begin
            for (i = 0; i< 6; i = i + 1)
                shift[i] <= 0;
          end
        else if (rxstrobe)
          begin
            for (i = 1; i< 6; i = i + 1)
                shift[i] <= shift[i-1];
            shift[0] <= in_sample;
          end
        else
          begin
            case(sel)
              3'd1:    data <= shift[0];
              3'd2:    data <= shift[1];
              3'd3:    data <= shift[2];
              3'd4:    data <= shift[3];
              3'd5:    data <= shift[4];
              3'd6:    data <= shift[5];
              default: data <= 0;
            endcase
          end

endmodule
