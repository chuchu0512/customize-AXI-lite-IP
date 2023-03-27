#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "gray_axi.h"

#include "xil_io.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <fcntl.h>
#include <assert.h>

#define data 0x10000000
#define result 0x11000000


int main()
{
	//set input data
	Xil_Out8(data+0, 100) ; // red = 100
	Xil_Out8(data+1, 50) ; // green = 50
	Xil_Out8(data+2, 200) ; // blue = 200
	Xil_Out8(data+3, 255) ; // red = 255
	Xil_Out8(data+4, 0) ; // green = 0
	Xil_Out8(data+5, 255) ; // blue = 255

	//write data into AXI-Lite IP
	GRAY_AXI_mWriteReg(XPAR_GRAY_AXI_0_S00_AXI_BASEADDR, GRAY_AXI_S00_AXI_SLV_REG0_OFFSET, data+0) ; // reg0 is red (in vivado)
	GRAY_AXI_mWriteReg(XPAR_GRAY_AXI_0_S00_AXI_BASEADDR, GRAY_AXI_S00_AXI_SLV_REG1_OFFSET, data+1) ; // reg1 is green
	GRAY_AXI_mWriteReg(XPAR_GRAY_AXI_0_S00_AXI_BASEADDR, GRAY_AXI_S00_AXI_SLV_REG2_OFFSET, data+2) ; // reg2 is blue

	//read data from AXI-Lite IP
	Xil_Out8(result+0, GRAY_AXI_mReadReg(XPAR_GRAY_AXI_0_S00_AXI_BASEADDR, GRAY_AXI_S00_AXI_SLV_REG3_OFFSET)) ; // reg3 is gray

	//write data into AXI-Lite IP
	GRAY_AXI_mWriteReg(XPAR_GRAY_AXI_0_S00_AXI_BASEADDR, GRAY_AXI_S00_AXI_SLV_REG0_OFFSET, data+3) ; // reg0 is red (in vivado)
	GRAY_AXI_mWriteReg(XPAR_GRAY_AXI_0_S00_AXI_BASEADDR, GRAY_AXI_S00_AXI_SLV_REG1_OFFSET, data+4) ; // reg1 is green
	GRAY_AXI_mWriteReg(XPAR_GRAY_AXI_0_S00_AXI_BASEADDR, GRAY_AXI_S00_AXI_SLV_REG2_OFFSET, data+5) ; // reg2 is blue

	//read data from AXI-Lite IP
	Xil_Out8(result+1, GRAY_AXI_mReadReg(XPAR_GRAY_AXI_0_S00_AXI_BASEADDR, GRAY_AXI_S00_AXI_SLV_REG3_OFFSET)) ; // reg3 is gray

	//print resault
	xil_printf("gray0 = %d\r\n", Xil_In8(result+0)) ;
	xil_printf("gray1 = %d\r\n", Xil_In8(result+1)) ;

    return 0;
}
