//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:54:27 07/06/2019 
// Design Name: 
// Module Name:    PRV32_SOPC_TB 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
`timescale 1ns / 1ns
module PRV32_SOPC_TB;

reg             clk;
reg             rst;
wire    [3:0]   led;
wire            uart_tx;
wire            uart_rx;

PRV32_SOPC U_DUT (
    .clk                (clk            ),
    .rst                (rst            ),
    .uart_txd           (uart_tx        ),
    .uart_rxd           (uart_rx        ),
    .led                (led            )
);

initial forever #10 clk = ~clk;

initial begin
    clk  = 1'b0;
    rst  = 1'b1;
    #100;
    rst = 1'b0;
    #10000000;
    $finish;
end

endmodule
