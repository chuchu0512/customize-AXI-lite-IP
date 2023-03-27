# customize-AXI-lite-IP
* Using Xilinx Vivado **`AXI`** protocal to control your IP in Vitis

#contents
> 1. Vivado part  
    1.1. create own AXI-Lite slave IP  
    1.2. connect to AXI-Lite master  
    1.3. connect SoC and AXI-Lite IP  
    1.4. synthsis and implement the IP
> 2. Vitis part
    2.1. create Vitis file  
    2.2. using AXI-Lite API  

# 1 Vivado part
## 1.1 create own AXI-Lite slave IP
* Create new Project
* Choose RTL Project
	- [x] Do not specify sources at this time  
	- [ ] Project is an extensible Vitis platform  
* find ZCU104 board and choose  
* Copy `gray.v` into project  
* Set tb file to top run debug and set function file to top run synthesis check errors  
* Enter `Tools/Create and Package New IP`, choose `Create AXI4 Peripheral` and export to the path you want to store  
* In Interface page, set `Interface Type to Lite, `Interface Mode to Slave`
* According to IP input and output number, choose `Number of Register`(We choose 4 because gray.v has 3 input and 1 output, clk did't count)
* Next go to `Edit IP`
## 1.2 commect to AXI-Lite master
* Add IP.v(gray.v) to Design Sources
* In Design Sources we have `IP name_v1_0.v(Master.v)` and `IP name_v1_0_Slave name.v(Slave.v)`
* Go to `Slave.v` and annotation input register  
![](https://i.imgur.com/rdrMa1d.png)  
* Add `Users ports` to input ports and output ports `Notice that IP I/O ports will be Slave O/I ports`  
![](https://i.imgur.com/bRhtzUb.png)  
* Change `Address Register` name according to previous 2 steps  
![](https://i.imgur.com/8bOL0Yy.png)  
* Go to `Master.v` add master ports name  
![](https://i.imgur.com/0NKeW3V.png)  
* connect `Master.v` and `Slave.v` using each ports name  
![](https://i.imgur.com/Y0lOUlM.png)  
* Add IP module and connect to `Master.v`, `Notice that clock need to connect to AXI clock`  
![](https://i.imgur.com/h9d499V.png)  
* Enter `IP-XACT/component.xml`, find `File Groups` and `Customization Parameters`, Merge changes from xxx Wizard
* Enter `Review and Package` and click `Re-Package IP`
## 1.3 connect SoC and AXI-Lite IP
* Create new Project  
* Enter `Tools/Settings/IP/Repository`, add the IP you create in 1.2  
* click `Create Block Design` on the left  
* Add `Zynq UltraScale+ MPSoC` and `click Run Block Automation`  
* Dobble click enter the IP. set `PS-PL Configuration/PS-PL Interface/Master Interface`use only `AXI HPM0 LPD`  
* Add AXI-Lite IP, run connection Automation and let clock be auto. `If want set clock be your own, notice that Bridge IP and Master Interface clock must same clock`
![](https://i.imgur.com/MYHY3dI.png)  
## 1.4 synthesis and implement IP
* Press `F6` to valid design, next `Create HDL Wrapper`
* Using `Run Synthesis` to check IP's netlist and `Run Implement` to check setup time and hold time correction  
	* if setup time is negative, it need to change AXI-Lite IP Slave clock  
        ![](https://i.imgur.com/IyTMR5X.png)  
* If there is no other problem, generate `bitstream`
* Enter `File/Export/Export Hardware`, choose `include bitstream`, and you will get the `xsa` file  
# 2 Vitis part
## 2.1 Create Vitis file
* Open Vitis and `Create Application Project` in the workplace path. choose your xsa file as `Hardware Specification` and default other selection  
* Using `Hello world` templates  
## 2.2 Using AXI-Lite API
* Follow the `Vitis_AXI.c` code to use functions  
* Build `filename_system` to get `boot.bin` in `Debug/sd_card` and run on FPGA
