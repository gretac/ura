# Arrival Curve Computation in FPGA

* <b>File Structure </b><br>
    - /common - contains OpenCL API code. <br>
    - /codegen - contains C code for generating the device-side code in OpenCL C and the header file used by the host. <br>
    - /acip - <br>
        - /bin - contains the *.aocx file generated after compiling the device-side code using Altera Offline Compiler (AOC). It will also contain the executable for running the host after compiling.<br>
        - /data - contains files which can be used as inputs to run the code.<br>
        - /device - contains the code for the device (FPGA).<br>
        - /host/src - contains the code for the host (CPU).<br>

* <b>Compile instructions for host </b><br>
    1. `cd ./acip/` <br>
    2. `make all` <br>

* <b>Compile instructions for device </b><br>
    1. `cd ./acip/` <br>
    2. `aoc -v --board <board_name> device/acip.cl -o bin/acip.aocx` <br>
	   `-v` option generates the compilation progress report<br>
	   The `<board_name>` is usually <b>p385_hpc_a7</b> if Nallatech 385 Accelerator card with Altera Stratix V A7 FPGA is used. Refer the Altera SDK for OpenCL programming guide to determine the board name.
	3. For emulator version: <br>
	   `aoc -march=emulator -g -v --board <board_name> device/acip.cl -o bin/acip.aocx` <br>

* <b>Run the program</b><br>
    1. `cd ./acip/` <br>
    2. `./bin/acip ./data/<file_name> [<min window size> <max window size> <resolution>]`
   
The Altera SDK for OpenCL programming guide can be found <a href="https://www.altera.com/content/dam/altera-www/global/en_US/pdfs/literature/hb/opencl-sdk/aocl_programming_guide.pdf" target="_blank">here</a>. <br>

The Altera SDK for OpenCL best practices guide for optimizations can be found <a href="https://www.altera.com/content/dam/altera-www/global/en_US/pdfs/literature/hb/opencl-sdk/aocl_optimization_guide.pdf" target="_blank">here</a>. <br>

	
