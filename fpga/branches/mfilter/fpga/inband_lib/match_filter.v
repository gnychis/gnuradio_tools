module match_filter
   (input clk, input reset, input wire [15:0] real, input wire [15:0] img, 
    input rxstrobe, input wire [31:0] cdata, input wire [3:0] cstate, input cwrite, 
    output wire [15:0] debugbus, output reg valid, output reg match)


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
    reg [15:0] real_block [191:0];
    reg [15:0] img_block  [191:0];
    reg data_valid;

    always @ (posedge clk)
        if (reset)
          begin
            for( i = 0; i < 192; i = i + 1)
              begin
                real_block[i] <= 0;
                img_block[i]  <= 0;
              end
            data_valid <= 0;
          end 
        else if (rxstrobe)
          begin
            for( i = 1; i < 192; i = i + 1 ) 
              begin
                real_block[i] <= (i < co_length) ? real_block[i-1] : 0;
                img_block[i]  <= (i < co_length) ? img_block[i-1]  : 0;   
              end
            real_block[i] <= real;
            img_block[i]  <= img;
            data_valid    <= 1;
          end
        else
            data_valid    <= 0;

    
    //computation block
    reg [15:0] in_data [63:0];
    reg [31:0] in_8    [7:0] ;
    reg [31:0] in_1          ;
    
    reg in_64_valid;
    reg in_8_valid;
    reg in_1_valid;

    /*sign extension*/
    wire [31:0] in_64 [63:0] ;
    for (i = 0; i < 64; i = i + 1)
        assign in_64[i] = (in_data[i] > 0) ? {16'h0000, in_data[i]} : {16'hFFFF, in_data[i]};

    integer i;
    
    always @ (posedge clk)
        if (reset)
          begin
            in_8_valid  <= 0;
            in_1_valid  <= 0;
              end
        else
          begin
            for (i = 0; i < 8; i = i + 1)
              begin
                in_8[i] <= in_64[8*i] + in_64[8*i+1] + in_64[8*i+2] + in_64[8*i+3] + 
                           in_64[8*i + 4] + in_64[8*i+5] + in_64[8*i+6] + in_64[8*i+7];
              end
            in_1 <= in_8[0] + in_8[1] + in_8[2] + in_8[3] + in_8[4] + 
                    in_8[5] + in_8[6] + in_8[7];
            in_8_valid <= in_64_valid;
            in_1_valid <= in_8_valid;
          end

    
    //data selection block
    wire [15:0] com_block_real [63:0];
    wire [15:0] com_block_img  [63:0];
    wire com_block_co [127:0];

    assign com_block_real = (in_state <= 4'd2) ? real_block [63:0]; 
                            (in_state <= 4'd4) ? real_block[127:64] : real_block[191:128];
    assign com_block_img  = (in_state <= 4'd2) ? img_block [63:0]; 
                            (in_state <= 4'd4) ? img_block[127:64] : img_block[191:128]  ;
    assign com_block_co   = (in_state <= 4'd2) ? co[127:0]   :
                            (in_state <= 4'd4) ? co[255:128] : co[381:256];

    
    always @ (posedge clk)
        if (in_state > 0)
          begin
            for (i = 0; i < 64; i = i + 1)
              begin
                case (com_block_co[2*i+1 : 2*i])
                  2'b00:
              begin
                      in_64[i] <= (in_state[0]) ? (com_block_real[i]) :
                                                  (com_block_img[i])  ;
              end
                  2'b01:
                    begin
                      in_64[i] <= (in_state[0]) ? (com_block_real[i]) :
                                                  (-com_block_img[i]) ;
          end
                  2'b10:
          begin
                      in_64[i] <= (in_state[0]) ? (-com_block_real[i]) :
                                                  (-com_block_img[i])  ;
                    end
                  default:
              begin
                      in_64[i] <= (in_state[0]) ? (-com_block_real[i]) :
                                                  (com_block_img[i])   ;
                    end
              end
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
endmodle
