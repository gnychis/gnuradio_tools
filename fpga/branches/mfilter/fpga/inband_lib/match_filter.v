module match_filter
   (input clk, input reset, input wire [15:0] r_input, input wire [15:0] i_input, 
    input rxstrobe, input wire [31:0] cdata,  input wire [3:0] cstate, input cwrite, 
    output wire [15:0] debugbus, output reg valid, output reg match);


    genvar  g;
    integer i;

    //setting up parameters  
    reg signed [23:0] threshhold;
    reg [2:0] co_len_state;
    reg [4:0] co_len_residual;
    always @(posedge clk)
        if(reset)
          begin
            threshhold      <= 0;
            co_len_state    <= 0;
            co_len_residual <= 0;
          end
        else if (in_state == 0)
          begin
            threshhold      <= cout_real[23:0];
            co_len_state    <= cout_img[7:5] + 3'd1;
            co_len_residual <= cout_img[4:0];
          end   

    //computation block
    reg signed [23:0] in_32_real   [31:0];
    reg signed [23:0] in_32_img    [31:0];

    wire [23:0] in_4_real          [3:0] ;
    wire [23:0] in_4_img           [3:0] ;
    wire [23:0] in_1_real                ;
    wire [23:0] in_1_img                 ;
    
    reg in_32_valid;
    reg in_4_valid;
    reg in_1_valid;


    generate for (g = 0; g < 4; g = g + 1)
      begin : generate_adder_8X24
      
        adder_8X24 a8_r(clk, reset, in_32_real[4*g], in_32_real[4*g+1], 
                        in_32_real[4*g+2], in_32_real[4*g+3], in_32_real[4*g+4],
                        in_32_real[4*g+5], in_32_real[4*g+6], in_32_real[4*g+7],
                        in_4_real[g]);
        adder_8X24 a8_i(clk, reset, in_32_img [4*g], in_32_img [4*g+1], 
                        in_32_img [4*g+2], in_32_img [4*g+3], in_32_img [4*g+4],
                        in_32_img [4*g+5], in_32_img [4*g+6], in_32_img [4*g+7],
                        in_4_img [g]);
      end
    endgenerate

    adder_4X24 a4_r(clk, reset, in_4_real[0], in_4_real[1], in_4_real[2],
                    in_4_real[3], in_1_real);
    adder_4X24 a4_i(clk, reset, in_4_img [0], in_4_img [1], in_4_img [2],
                    in_4_img [3], in_1_img );

    always @(posedge clk)
        if(reset)
          begin
            in_4_valid <= 0;
            in_1_valid <= 0;
          end
        else
          begin
            in_4_valid <= in_32_valid;
            in_1_valid <= in_4_valid;
          end

    //coefficient block
    wire [31:0] cout_real;
    wire [31:0] cout_img ;
    wire [3:0] ram_addr_a;
    wire [3:0] ram_addr_b;
    wire we_a;
    wire we_b;
    assign ram_addr_a = (cwrite) ? cstate : {in_state[2:0], 1'b0};
    assign ram_addr_b = (cwrite) ? cstate : {in_state[2:0], 1'b1};
    assign we_a       = cwrite & (~cstate[0]);
    assign we_b       = cwrite & cstate[0];
    true_dual_port_ram_single_clock ram
    (.data_a(cdata), .data_b(cdata), .addr_a(ram_addr_a), .addr_b(ram_addr_b),
     .we_a(we_a), .we_b(we_b), .clk(clk), .q_a(cout_real), .q_b(cout_img));   


    //data block
    
    wire [15:0] bridge_real[31:0];
    wire [15:0] bridge_img [31:0];
    wire [15:0] data_real[31:0];
    wire [15:0] data_img [31:0];
    wire [2:0]  sel;

    assign sel = in_state;

    generate for (g = 1; g< 32; g = g + 1)
      begin : generate_shift_regs_real
      
        shift_register sr_r (.clk(clk), .reset(reset), .rxstrobe(rxstrobe),
                      .in_sample(bridge_real[g-1]), .out_sample(bridge_real[g]),
                      .sel(sel), .data(data_real[g]));
      end
    endgenerate

    generate for (g = 1; g< 32; g = g + 1)
      begin : generate_shift_regs_img
      
        shift_register sr_i (.clk(clk), .reset(reset), .rxstrobe(rxstrobe),
                      .in_sample(bridge_img[g-1]), .out_sample(bridge_img[g]),
                      .sel(sel), .data(data_img[g]));
      end
    endgenerate

    shift_register sr_r0 (.clk(clk), .reset(reset), .rxstrobe(rxstrobe),
                     .in_sample(r_input), .out_sample(bridge_real[0]),
                     .sel(in_state), .data(data_real[0]));

    shift_register sr_i0 (.clk(clk), .reset(reset), .rxstrobe(rxstrobe),
                     .in_sample(i_input), .out_sample(bridge_img[0]),
                     .sel(in_state), .data(data_img[0]));
    

    wire state_check_under;
    wire state_check_equal;
    assign state_check_under = in_state < co_len_state;
    assign state_check_equal = in_state == co_len_state; 
    
    //data selection block   
    always @ (posedge clk)
        if (reset)
          begin
            for (i = 0; i< 32; i = i + 1)
              begin
                in_32_real[i] <= 0;
                in_32_img [i] <= 0;
              end
          end
        else
          begin
            for (i = 0; i < 32; i = i + 1)
              begin
                if ((state_check_equal && i < co_len_residual) || 
                    state_check_under)
                  begin
                    in_32_real[i] <= (cout_real[i]) ? (data_real[i]) :
                                                      (-data_real[i]);
                    in_32_img [i] <= (cout_img[i] ) ? (data_img[i])  :
                                                      (-data_img[i]) ;
                  end
                else
                  begin
                    in_32_real[i] <= 0;
                    in_32_img [i] <= 0;
                  end
              end
          end
  
    //logic block
    reg [2:0]  in_state;
    reg signed [23:0] real_result; 
    reg signed [23:0] img_result;
    reg sum_valid;
    reg calculate;

    always @ (posedge clk)
        if (reset)
          begin
            in_state <= 0;
          end 
        else if (rxstrobe && !cwrite)
          begin
            in_state <= 3'd1;
          end  
        else if (in_state != 0)
          begin
            in_state <= in_state + 3'd1;
          end
        else
          begin
            in_state <= 0;
          end 
   
    always @ (posedge clk)
        if (reset)
            in_32_valid <= 0;
        else if (in_state > 3'd1)
            in_32_valid <= 1;
        else
            in_32_valid <= 0;

    always @ (posedge clk)
        if (reset)
          begin
            real_result <= 0;
            img_result  <= 0;
            sum_valid   <= 0;
          end
        else if (in_1_valid)
          begin
            real_result <= real_result + in_1_real;
            img_result  <= img_result  + in_1_img ;
            sum_valid   <= 0;
          end
        else if (sum_valid)
          begin
            real_result <= 0;
            img_result  <= 0;
            sum_valid   <= 0;
          end
        else if (real_result != 0 || img_result != 0)
          begin
            sum_valid   <= 1;
          end                

    reg signed [23:0] final_result;
    wire [23:0] real_result_abs;
    wire [23:0] img_result_abs;
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
                final_result <= real_result_abs + {1'b0, img_result_abs[22:0]};
            else
                final_result <= {1'b0, real_result_abs[22:0]} + img_result_abs;
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
            match <= (final_result > threshhold);
            valid <= 1'b1;
          end
        else
            valid <= 0;
   
    assign debugbus = {clk, match, valid, sum_valid, final_result_valid, 
                      in_32_valid, in_4_valid, in_1_valid, 
                      in_state[2:0], cstate[3:0], cwrite};    
endmodule
