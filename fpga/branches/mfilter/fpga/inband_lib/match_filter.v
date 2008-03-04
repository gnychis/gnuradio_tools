module match_filter
   (input clk, input reset, input wire [15:0] real, input wire [15:0] img, input rxstrobe,
    input wire [31:0] co_0, input wire [31:0] co_1, input wire [31:0] co_2, 
    input wire [31:0] co_3, input wire [31:0] co_4, input wire [31:0] co_5,
    input wire [31:0] co_6, input wire [31:0] co_7, input wire [31:0] co_8, 
    input wire [31:0] co_9, input wire [31:0] co_10, input wire [31:0] co_11, 
    input wire [7:0] co_length, input co_valid, input wire [31:0] threshhold, input ack,
    output wire [15:0] debugbus, output reg valid, output reg match)
  
    wire co[383:0];
    assign co = {co_11, co_10, co_9, co_8, co_7, co_6, co_5, co_4, co_3, co_2, co_1, co_0};
  
    integer i;

    reg [15:0] r [191:0]; //storing space -- real part
    reg [15:0] s [191:0]; //storing space -- imaginary part

    //storing the sample: consider using a lock
    always @ (posedge clk)
        if (reset)
          begin
            for( i = 0; i < 192; i = i + 1)
              begin
                r[i] <= 0;
                s[i] <= 0;
              end
          end 
        else if (rxstrobe)
          begin
            for( i = 0; i < 191; i = i + 1 ) 
              begin
                r[i+1] <= (i < (co_length - 8'd1)) ? r[i] : 0;
                s[i+1] <= (i < (co_length - 8'd1)) ? s[i] : 0;   
              end
            r[0] <= real;
            s[0] <= img;
          end

    reg [4:0] state;
    
    //generate the state information
    always @ (posedge clk)
        if (reset)
            state <= 0;
        else if (count < co_length || !co_valid)
            state <= 0;
        else if (rxstrobe)
            state <= 5'd1;
        else if (state < 5'd8)
            state <= state + 5'd1;
        else
            state <= 5'd0;

    reg [15:0] level1 [63:0];
    wire [15:0] rdata [63:0];
    wire [15:0] sdata [63:0];
    wire [1:0]  cdata [63:0];
    
    //performing the level1 calculation
    always @ (posedge clk)
        if (reset)
          begin
            for( i = 0; i < 64; i = i + 1)
              begin
                level1[i] <= 16'd0;
              end
          end
        else if (state == 5'd1 || state == 5'd3 || state == 5'd5)
          begin
            for( i = 0; i < 64; i = i + 1)
              begin
                assign rdata[i] = (state == 5'd1) ? (r[i]) : ((state == 5'd3) ? r[i+64] : r[i+128]); 
                assign sdata[i] = (state == 5'd1) ? (s[i]) : ((state == 5'd3) ? s[i+64] : s[i+128]);                    
                assign cdata[i] = (state == 5'd1) ? ({co[2*i], co[2*i+1]}) : 
                               ((state == 5'd3) ? ({co[2*i+128], co[2*i+129]}) : ({co[2*i+256], co[2*i+257]}));
                if (cdata == 2'b00)
                    level1[i] <= rdata[i] + sdata[i];
                else if (cdata == 2'b01)
                    level1[i] <= rdata[i] - sdata[i];
                else if (cdata == 2'b10)
                    level1[i] <= -rdata[i] - sdata[i];
                else
                    level1[i] <= sdata[i] - rdata[i];
              end
          end

    reg [31:0] level2 [7:0];
    
    //perform the level2 calculation
    always @ (posedge clk)
        if (reset)
          begin
            for( i = 0; i < 8; i = i + 1)
              begin
                level2[i] <= 31'd0;
              end
          end
        else if (state == 5'd2 || state == 5'd4 || state == 5'd6)
          begin
            for( i = 0; i < 8; i = i + 1)
              begin
                level2[i] <= level1[7*i] + level1[7*i+1] + level1[7*i+2] + level1[7*i+3] +        
                             level1[7*i + 4] + level1[7*i+5] + level1[7*i+6] + level1[7*i+7];
              end
          end

    reg [31:0] level3[2:0];
    
    //perfrom the level3 calculation
    always @ (posedge clk)
        if (reset)
          begin
            level3[0] < = 0;
            level3[1] < = 0;
            level3[2] < = 0;
          end
        else if (state == 5'd3)
          level3[0] < = level2[0] + level2[1] + level2[2] + level2[3] + 
                        level2[4] + level2[5] + level2[6] + level2[7];
        else if (state == 5'd5)
          level3[1] < = level2[0] + level2[1] + level2[2] + level2[3] + 
                        level2[4] + level2[5] + level2[6] + level2[7];
        else if (state == 5'd7)
          level3[2] < = level2[0] + level2[1] + level2[2] + level2[3] + 
                        level2[4] + level2[5] + level2[6] + level2[7];
   

    reg [31:0] final_result;
    reg final_valid;
 
    //final calculation
    always @ (posedge clk)
        if (reset)
          begin
            final_result <= 0;
            final_valid <= 0;
          end
        else if (state == 5'd8)
          begin
            final_result <= level3[0] + level3[1] + level3[2];
            final_valid <= 1;
          end
        else if (final_valid <= 1)
            final_valid <= 0;
    

    //output data
    //when another part of the fpga board receives a match,
    //it should acknowledge with an ack to turn match off similar to ISR
    always @ (posedge clk)
        if (reset)
            match <= 0;
        else if(final_valid && (final_valid > threshhold)
            match <= 1;
        else if (ack)
            match <= 0; 
      
    assign debugbus <= {clk, state[3:0], match, final_valid, co_valid, count};  
   
endmodle
