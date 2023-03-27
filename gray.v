`timescale 1ns/1ps

module gray(
input clk,
input [7:0] red, green, blue,
output reg [7:0] gray
);

	always@(posedge clk)begin
		gray <= ((red*19595 + green*38469 + blue*7472) >> 16) ;
	end
endmodule