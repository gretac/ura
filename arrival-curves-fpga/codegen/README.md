# Code Generator for device

* <b>Compile instructions</b><br>
    * `g++ codegen.cpp -o codegen` <br>

* <b>Run the program</b><br>
    * `./codegen <No. of ACIPs to generate>`

This will generate two files -
* acip.cl - This is the code for the device. After generation, move this file to <b>../acip/device/</b> directory.<br>
* kernels.h - This header file contains the names of the kernels and is used by host. After generation, move this file to <b>../acip/host/src/</b> directory.<br>

