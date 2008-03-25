module match_filter
   (input clk, input reset, input wire [15:0] r_input, input wire [15:0] i_input, 
    input rxstrobe, input wire [31:0] cdata, input wire [3:0] cstate, input cwrite, 
    output wire [15:0] debugbus, output reg valid, output reg match);


    //parameter block
    reg [383:0] co;
    reg [7:0]   co_length;
    reg         co_valid;
    reg [31:0]  threshhold;

    always @ (posedge clk)
        if (reset)
          begin
            co_length <= 8'd192;
            co_valid  <= 0;
          end
        else if (cwrite)
          begin
            case (cstate)
              4'd1:    co_length   <= cdata;
              4'd2:    threshhold  <= cdata;
              4'd3:    co[383:352] <= cdata;
              4'd4:    co[351:320] <= cdata;
              4'd5:    co[319:288] <= cdata;
              4'd6:    co[287:256] <= cdata;
              4'd7:    co[255:224] <= cdata;
              4'd8:    co[223:192] <= cdata;
              4'd9:    co[191:160] <= cdata;
              4'd10:   co[159:128] <= cdata;
              4'd11:   co[127:96]  <= cdata;
              4'd12:   co[95:64]   <= cdata;
              4'd13:   co[63:32]   <= cdata;
              default: co[31:0]    <= cdata;
            endcase
            co_valid <= 0;
          end
        else
            co_valid <= 1;   


    //data block
    genvar g;
    wire [15:0] bridge_real[31:0];
    wire [15:0] bridge_img [31:0];
    reg [2:0] state;
    wire [15:0] data_real[31:0];
    wire [15:0] data_img [31:0];
    
    generate for (g = 1; g< 32; g = g + 1)
      begin : generate_shift_regs_real
      
        shift_register sr_r (.clk(clk), .reset(reset), .rxstrobe(rxstrobe),
                      .in_sample(bridge_real[g-1]), .out_sample(bridge_real[g]),
                      .sel(state), .data(data_real[g]));
      end
    endgenerate

    generate for (g = 1; g< 32; g = g + 1)
      begin : generate_shift_regs_img
      
        shift_register sr_i (.clk(clk), .reset(reset), .rxstrobe(rxstrobe),
                      .in_sample(bridge_img[g-1]), .out_sample(bridge_img[g]),
                      .sel(state), .data(data_img[g]));
      end
    endgenerate

    shift_register sr_r0 (.clk(clk), .reset(reset), .rxstrobe(rxstrobe),
                     .in_sample(in_real), .out_sample(bridge_real[0]),
                     .sel(state), .data(data_real[0]));

    shift_register sr_i0 (.clk(clk), .reset(reset), .rxstrobe(rxstrobe),
                     .in_sample(in_img), .out_sample(bridge_img[0]),
                     .sel(state), .data(data_img[0]));
    
    //computation block
    reg signed [31:0] in_32_real   [31:0];
    reg signed [31:0] in_32_img    [31:0];
    reg signed [31:0] in_4_real    [3:0] ;
    reg signed [31:0] in_4_img     [3:0] ;
    reg signed [31:0] in_1_real          ;
    reg signed [31:0] in_1_img           ;
    
    reg in_64_valid;
    reg in_8_valid;
    reg in_1_valid;


    integer i;
    
    always @ (posedge clk)
        if (reset)
          begin
            in_8_valid  <= 0;
            in_1_valid  <= 0;
          end
        else
          begin
            for (i = 0; i < 4; i = i + 1)
              begin
                in_4_real[i] <= in_32_real[8*i] + in_32_real[8*i+1] + in_32_real[8*i+2] + in_32_real[8*i+3] + 
                            in_32_real[8*i + 4] + in_32_real[8*i+5] + in_32_real[8*i+6] + in_32_real[8*i+7];
                in_4_img [i] <= in_32_img[8*i]  + in_32_img[8*i+1]  + in_32_img[8*i+2]  + in_32_img[8*i+3]  + 
                            in_32_img[8*i + 4]  + in_32_img[8*i+5]  + in_32_img[8*i+6]  + in_32_img[8*i+7] ;
              end
            in_1_real <= in_4_real[0] + in_4_real[1] + in_4_real[2] + in_4_real[3];
            in_1_img  <= in_4_img[0]  + in_4_img[1]  + in_4_img[2]  + in_4_img[3] ;
            in_8_valid <= in_64_valid;
            in_1_valid <= in_8_valid;
          end

    
    //data selection block   
    always @ (posedge clk)
        for (i = 0; i < 64; i = i + 1)
          begin
            case (in_state)
              4'd1:
                begin
                  in_64[i] <= (co[2*i+1]) ? (real_block[i]) :
                                            (-real_block[i]); 
                end
              4'd2:
                begin
                  in_64[i] <= (co[2*i+1] == co[2*i]) ? (img_block[i]) :
                                                       (-img_block[i]);
                end
              4'd3:
                begin
                  in_64[i] <= (co[2*i+129]) ? (real_block[i+64]) :
                                              (-real_block[i+64]);  
                end
              4'd4:
                begin
                  in_64[i] <= (co[2*i+129] == co[2*i+128]) ? (img_block[i+64]) :
                                                             (-img_block[i+64]); 
                end
              4'd5:
                begin
                  in_64[i] <= (co[2*i+257]) ? (real_block[i+128]) :
                                              (-real_block[i+128]); 
                end
              4'd6:
                begin
                  in_64[i] <= (co[2*i+257] == co[2*i+256]) ? (img_block[i+128]) :
                                                             (-img_block[i+128]);
                end
              default:
                begin
                  in_64[i] <= 0;
                end
            endcase
          end
  
    //logic block
    reg [3:0]  in_state;
    reg [3:0]  out_state;
    reg [31:0] real_result; 
    reg [31:0] img_result;
    reg sum_valid;

    always @ (posedge clk)
        if (reset)
            in_state <= 0; 
        else if (rxstrobe && co_valid)
            in_state <= 4'd1;
        else if (in_state > 0 && in_state < 4'd6)
            in_state <= in_state + 4'd1;
        else
            in_state <= 0; 
   
    always @ (posedge clk)
        if (reset)
            out_state <= 4'd1;
        else if (in_1_valid)
            out_state <= out_state + 4'd1;
        else
            out_state <= 4'd1; 
    
    always @ (posedge clk)
        if (reset)
            in_64_valid <= 0;
        else if (in_state > 0)
            in_64_valid <= 1;
        else
            in_64_valid <= 0;

    always @ (posedge clk)
        if (reset)
          begin
            real_result <= 0;
            img_result  <= 0;
          end
        else if (in_1_valid)
          begin
            real_result <= (out_state[0]) ? (real_result + in_1) : (real_result);
            img_result  <= (out_state[0]) ? (img_result) : (img_result + in_1)  ;
          end
        else
          begin
            real_result <= 0;
            img_result  <= 0;
          end
   
    always @ (posedge clk)
         if (reset)
             sum_valid <= 0;
         else if (out_state == 4'd6)
             sum_valid <= 1;
         else
             sum_valid <= 0;                   

    reg [31:0] final_result;
    wire [31:0] real_result_abs;
    wire [31:0] img_result_abs;
    reg final_result_valid;
    
    assign real_result_abs = (real_result > 0) ? real_result : (-real_result);
    assign img_result_abs  = (img_result > 0)  ? img_result  : (-img_result) ;
 
    //final calculation
    always @ (posedge clk)
        if (reset)
          begin
            final_result <= 0;
            final_result_valid <= 0;
          end
        else if (sum_valid)
          begin
            if (real_result_abs > img_result_abs)
                final_result <= real_result_abs + {1'b0, img_result_abs[30:0]};
            else
                final_result <= {1'b0, real_result_abs} + img_result_abs;
            final_result_valid <= 1;    
          end
        else
            final_result_valid <= 0; 

    //output evaluation
    always @ (posedge clk)
        if (reset)
          begin
            match <= 0;
            valid <= 0;
          end
        else if (final_result_valid)
          begin
            match <= (final_result > threshhold)? 1: 0;
            valid <= 1;
          end
        else
            valid <= 0;
   
    assign debugbus = {clk, match, valid, sum_valid, final_result_valid, 
                      in_64_valid, in_8_valid, in_1_valid, data_valid, co_valid,
                      in_state[2:0], out_state[2:0]};    
endmodule
