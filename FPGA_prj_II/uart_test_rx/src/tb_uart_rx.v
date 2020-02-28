`timescale 1ns/1ns
`define clk_period 20

module tb_uart_rx();

reg clk;
reg rst;
wire rs232_Tx;
reg [7:0]data_byte_tx;
reg send_en;
wire tx_done;
wire uart_state;
wire bps_clk;

wire [7:0]data_byte_rx;
wire rx_done;

uart_test_x uart_test_x(
	.clk(clk),
	.rst(rst),
	.baud_set(3'd0),
	.data_byte(data_byte_tx),
	.send_en(send_en),
	.rs232_Tx(rs232_Tx),
	.tx_done(tx_done),
	.uart_state(uart_state),
	.bps_clk(bps_clk)
);

uart_rx uart_rx(
	.clk(clk),
	.rst(rst),
	.baud_set(3'd0),
	.rs232_rx(rs232_Tx),
	.data_byte(data_byte_rx),
	.rx_done(rx_done)
);

initial clk = 1'b1;
always#(`clk_period/2) clk = ~clk;

initial begin
	rst = 1'd0;
	#(`clk_period*20);
	rst = 1'd1;
	#(`clk_period*20 +1);
	rst = 1'd0;
	send_en = 1'd0;
	data_byte_tx = 8'd0;
	#(`clk_period*20)
	rst = 1'd1;
	#(`clk_period*20+1);
	data_byte_tx = 8'haa;
	send_en = 1'd1;
	#(`clk_period);
	send_en = 1'd0;
	
	@(posedge tx_done)
	
	#(`clk_period*5000)
	data_byte_tx = 8'he0;
	send_en = 1'd1;
	#(`clk_period);
	send_en = 1'd0;
	
	@(posedge tx_done)
	
	#(`clk_period*5000);
	data_byte_tx = 8'h55;
	send_en = 1'd1;
	#(`clk_period);
	send_en = 1'd0;
	
	@(posedge tx_done)	
	
	#(`clk_period*5000);
	$stop;




end
endmodule
