module match_filter_test();

  reg rxclk;
  reg reset;
  reg [15:0] ch_0;
  reg [15:0] ch_1;
  reg [31:0] ch;
  wire rxstrobe;
  reg [31:0] cdata;
  reg [2:0] cstate;
  reg cwrite;
  wire valid;
  wire match;
  integer file_co, file_dat; 

  match_filter mf
   (.clk(rxclk), .reset(reset), .r_input(ch_0), .i_input(ch_1), 
    .rxstrobe(rxstrobe), .cdata(cdata),  .cstate(cstate), .cwrite(cwrite), 
    .valid(valid), .match(match));
  
  strobe_gen sgen
   (.reset(reset), .enable(1'b1), .clock(rxclk), .strobe_in(1'b1),
    .strobe(rxstrobe), .rate(8'd16));

  always
      #5 rxclk = ~rxclk ;

  initial
    begin
      reset   = 1;
      rxclk   = 0;
      ch_0    = 0;
      ch_1    = 0;
      cdata   = 0;
      cstate = 0;
      cwrite  = 0;
      
      #40 reset = 1'b0;

      file_co  = $fopen("simulation\tx_cs.dat", "rb");

      if(!file_co) begin
        $display("Error opening coefficients\n");
      end

      repeat (7)
      begin
      @(posedge rxclk)
        cwrite = 1;
        cstate = cstate + 1;
        $fread(cdata, file_co);;
      end

      $fclose(file_co);
     
      @(posedge rxclk)
        cwrite = 0;

      file_dat = $fopen("simulation\rx_data_clear.dat", "rb");
      if(!file_dat) begin
        $display("Error opening data\n");
      end
      
      while ($feof(file_dat) == 0)
        begin
          @(posedge rxstrobe)
            $fread(ch, file_dat);;
            ch_0 = {ch[31:16], 16'd0};
            ch_1 = {ch[15:0], 16'd0};
        end 
      $fclose(file_dat);  
    end
endmodule

