# ura

There are two main directories in this repo:
arrivalcurve-opencl and arrivalcurve-standalone.
Then there are two examples of opencl implementation
and a directory named "simple-opencl" which
contains the abstraction code to automatically importing libraries 
for different GPUs.

The arrivalcurve-opencl is undeveloped (and a little out of sync)
but the opencl framework is in place for development (includes etc).

The arrivalcurve-standalone is written in C++ and is functional
in computing the maximum and minimum events given the window size.

The command to run:  ./main [min] [max] [input] [output]

And there's also a make file in both the standalone and
the opencl directories. You can simply type "make"
to compile the arrival_curve.cpp and the main.cpp and the
linking is also done by the Makefile.

My two cents:

I initially thought that it's an easy project especially because
I am fairly "okay" in programming C++. But then I realize that
translating C++ to OpenCL is a completely different story and it
requires extensive amount of time and expertise. 

I spent most of my time laying out the path so someone else
who has the expertise can walk straight to the point where I left off. 
And even for someone who doesn't have such expertise, 
given the two examples in this repo,
he/she should be able to proceed on the project.

Since I only have 6 hours per week to work on this project and
I spent quite a long time on first programming the C++ portion,
I don't have much else to share with you. One very good resource
I found in regards to OpenCL is the Nvidia OpenCL example website.

However, I spent two weeks trying but failing to get OpenCL working
on the lab machine because Nvidia intentionally drop support for
OpenCL so that they gain competitiveness on their own product called CUDA.
But I found this tool named "simple-opencl" in the end and it ended
up helping me to finally set up the code the run on the lab machine.
So try utilize this tool instead of writing your own C++ code
to interface with OpenCL or you will end up wasting time.

And as a computer engineer, it's about learning as many things as
you could and I think that this project really help me to understand
the infrastructure of OpenCL as a whole and learning how to optimize
code I have written in C++. I hope Sebastian and Greta are not too
upset that I didn't finish the original objective and they found the
next great candidate who has the great will power to complete such
interesting yet difficult task.
