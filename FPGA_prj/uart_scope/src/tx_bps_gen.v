module tx_bps_gen(
	clk,
	rst,
	baud_set,
	tx_done,
	byte_en,
	bps_clk
);

parameter sys_clk = 50_000_000;

input clk;
input rst;
input [2:0]baud_set;
input tx_done;
input byte_en;
output reg bps_clk;

localparam	bps9600   = sys_clk/9600-1;
localparam	bps19200  = sys_clk/19200-1;
localparam	bps38400  = sys_clk/38400-1;
localparam	bps57600  = sys_clk/57600-1;
localparam	bps115200 = sys_clk/115200-1;
localparam	bps230400 = sys_clk/230400-1;
localparam	bps460800 = sys_clk/460800-1;
localparam	bps921600 = sys_clk/921600-1;

//波特率设置
reg [31:0]bps_para;
always@(posedge clk or negedge rst)
	if(!rst)
		bps_para <= bps9600;
	else 
		begin
			case(baud_set)
				3'd0: bps_para <= bps9600  ;
				3'd1: bps_para <= bps19200 ;
				3'd2: bps_para <= bps38400 ;
				3'd3: bps_para <= bps57600 ;
				3'd4: bps_para <= bps115200;
				3'd5: bps_para <= bps230400;
				3'd6: bps_para <= bps460800;
				3'd7: bps_para <= bps921600;
			endcase 
		end

//计数
reg state;
localparam	IDEL = 1'd0,
				SEND = 1'd1;
reg bps_en;
always@(posedge clk or negedge rst)
	if(!rst)
		begin
			state <= IDEL;
			bps_en <= 1'd0;
		end
	else 
		begin
			case(state)
				IDEL:
					if(byte_en)
						begin
							state <= SEND;
							bps_en <= 1'd1;
						end
					else 
						begin
							state <= IDEL;
							bps_en <= 1'd0;
						end
				SEND:
					if(tx_done)
						begin
							state <= IDEL;
							bps_en <= 1'd0;
						end
					else 
						begin
							state <= SEND;
							bps_en <= 1'd1;
						end
			endcase 
		end

reg [12:0]cnt;
always@(posedge clk or negedge rst)
	if(!rst)
		cnt <= 13'd0;
	else if(bps_en)
		begin
			if(cnt == bps_para)
				cnt <= 13'd0;
			else 
				cnt <= cnt + 1'd1;
		end
	else 
		cnt <= 13'd0;
	
//波特率时钟
always@(posedge clk or negedge rst)
	if(!rst)
		bps_clk <= 1'd0;
	else if(cnt == 13'd1)
		bps_clk <= 1'd1;
	else 
		bps_clk <= 1'd0;

	
endmodule 
