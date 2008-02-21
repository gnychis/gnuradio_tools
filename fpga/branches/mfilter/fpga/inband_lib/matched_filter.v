

wire [31:0] round1 [31:0];
wire [31:0] round2 [15:0];
wire [31:0] round3 [7:0];
wire [31:0] round4 [3:0];
wire [31:0] round5 [1:0];
wire [31:0] result;

assign result = round5[1] + round5[0];

assign round5[0] = round4[1] + round4[0];
assign round5[1] = round4[3] + round4[2];

assign round4[0] = round3[1] + round3[0];
assign round4[1] = round3[3] + round3[2];
assign round4[2] = round3[5] + round3[4];
assign round4[3] = round3[7] + round3[6];

assign round3[0] = round2[1] + round2[0];
assign round3[1] = round2[3] + round2[2];
assign round3[2] = round2[5] + round2[4];
assign round3[3] = round2[7] + round2[6];
assign round3[4] = round2[9] + round2[8];
assign round3[5] = round2[11] + round2[10];
assign round3[6] = round2[13] + round2[12];
assign round3[7] = round2[15] + round2[14];

assign round2[0] = round1[1] + round1[0];
assign round2[1] = round1[3] + round1[2];
assign round2[2] = round1[5] + round1[4];
assign round2[3] = round1[7] + round1[6];
assign round2[4] = round1[9] + round1[8];
assign round2[5] = round1[11] + round1[10];
assign round2[6] = round1[13] + round1[12];
assign round2[7] = round1[15] + round1[14];
assign round2[0] = round1[17] + round1[16];
assign round2[1] = round1[19] + round1[18];
assign round2[2] = round1[21] + round1[20];
assign round2[3] = round1[23] + round1[22];
assign round2[4] = round1[25] + round1[24];
assign round2[5] = round1[27] + round1[26];
assign round2[6] = round1[29] + round1[28];
assign round2[7] = round1[31] + round1[30];

generate for (i = 0; i < 63; i = i + 1)
  begin
    wire [31:0] a;
    wire [31:0] b;
    wire [31:0] s;
    
    assign s = sample[i + offset];
    assign a = {16'd0, s[31:16]};
    assign b = {16'd0, s[15:0]};
    assign round1[i] = (coefficient[0]) ? ((coefficient[1]) ? (b-a) : (-a-b)) :
                                          ((coefficient[1]) ? (a-b) : (a+b)); 
  end

