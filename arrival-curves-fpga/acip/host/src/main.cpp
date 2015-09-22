#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include "kernels.h"
#include "CL/opencl.h"
#include "AOCLUtils/aocl_utils.h"

using namespace aocl_utils;

// OpenCL runtime configuration
cl_platform_id platform = NULL;
unsigned nDevices = 0;
scoped_array<cl_device_id> device;
cl_context context = NULL;
scoped_array<cl_command_queue> queue;
cl_program program = NULL;
scoped_array<cl_kernel> kernel;

// Buffers
cl_mem bufTraceTime, bufBase, bufOutput;

// Problem data
unsigned N = 0; // problem size
unsigned nBases = 0;
char filename[35];
scoped_array<double> fileData;
scoped_array<double> inputTraceTime;
scoped_array<double> inputBase;
scoped_array<double> outputCounters;
scoped_array<unsigned> nBasesPerKernel;
scoped_array<scoped_aligned_ptr<double> > outputdata;
scoped_array<double> wSizes;  // Comment this line if hardcoded window sizes are used

// HARDCODED IF NEEDED

// Window Size Test1
// double wSizes[] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120};

// Window Size Test2
// double wSizes[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250};

// Window Size Test3
// double wSizes[] = {2, 4, 6, 8, 12, 14, 16, 24, 28, 30, 32, 48, 56, 60, 62, 64, 96, 112, 120, 124, 126, 128, 192, 224, 240, 248, 252, 254, 256};

// Window Size Test4
// double wSizes[] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125, 130, 135, 140, 145, 150, 155, 160, 165, 170, 175, 180, 185, 190, 195, 200, 205, 210, 215, 220, 225, 230, 235, 240, 245, 250, 255, 260, 265, 270, 275, 280, 285, 290, 295, 300, 305, 310, 315, 320, 325, 330, 335, 340, 345, 350, 355, 360, 365, 370, 375, 380, 385, 390, 395, 400};

// Window Size Test5
// double wSizes[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120};

// Window Size Test6
// double wSizes[] = {1041, 1042, 1083, 1084, 1125, 1208, 1291, 1333, 1375, 1416, 1417, 1458, 1541, 1542, 1583, 1584, 1625, 1708, 1750, 1791, 1792, 1833, 1834, 1875, 1917, 1958, 1959, 2000, 2041, 2042, 2083, 2084, 2125, 2208, 2209, 2250, 2291, 2334, 2375, 2416, 2417, 2458, 2500, 2542, 2583, 2584, 2625, 2666, 2667, 2708, 2709, 2750, 2791, 2833, 2834, 2875, 2916, 2917, 2958, 2959, 3000, 3041, 3042, 3083, 3084, 3125, 3167, 3208, 3209, 3250, 3291, 3292, 3333, 3375, 3417, 3458, 3459, 3500, 3541, 3542, 3583, 3584, 3625, 3666, 3667, 3708, 3709, 3750, 3791, 3792, 3833, 3834, 3916, 3917, 3958, 3959, 4000, 4041, 4042, 4083};

// Window Size PerfTests
// double wSizes[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110};
// double wSizes[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 500, 510, 520, 530, 540, 550, 560, 570, 580, 590, 600, 610, 620, 630, 640, 650, 660, 670, 680, 690, 700, 710, 720, 730, 740, 750, 760, 770, 780, 790, 800, 810, 820, 830, 840, 850, 860, 870, 880, 890, 900, 910, 920, 930, 940, 950, 960, 970, 980, 990, 1000};

unsigned nWSizes = (sizeof(wSizes)/sizeof(wSizes[0]));   // Number of Window Sizes

// Function prototypes
int get_problem_size();
void read_data();
void print_input_data();
bool init_opencl();
bool init_buffers(int);
void init_problem();
void run(int);
void cleanup();

// Entry point.
int main(int argc, char *argv[]) {
  if ((argc != 2) && (argc != 5)) {
    printf("Usage: ./bin/acip <data filename> \n");
    printf("Usage: ./bin/acip <data filename> <min window size> <max window size> <resolution>\n");
    return -1;   
  }

  strcpy(filename, argv[1]);

  double minWSize = 10.0;
  double maxWSize = 110.0;
  double res = 10.0;

  if (argc == 5) {
    minWSize = atof(argv[2]);
    maxWSize = atof(argv[3]);
    res = atof(argv[4]);
  }

  nWSizes = ((maxWSize - minWSize)/res)+1;
  wSizes.reset(nWSizes);

  int j = 0;
  for (int i = minWSize; i <= maxWSize; i+=res)
    wSizes[j++] = i;

  // Get problem data
  N = get_problem_size();

  // Get the trace time values
  read_data();
  
  if(!init_opencl()) {
    return -1;
  }

  cl_int status;
  bufTraceTime = clCreateBuffer(context, CL_MEM_READ_ONLY, N * sizeof(double), NULL, &status);
  checkError(status, "Failed to create buffer for input trace times");

  outputdata.reset(nWSizes);

  const double start_time = getCurrentTimestamp();
  for (int i = 0; i < nWSizes; ++i) {
    printf("Window Size: %f\n", wSizes[i]);

    // Initialize Buffers.
    if(!init_buffers(i)) {
      return -1;
    }

    if (nBases == 0) 
      continue;

    // Initialize the problem data.
    init_problem();

    // print_input_data();

    // Run
    run(i);

    // Free the resources allocated
    cleanup();
  }

  // Clean up the rest
  if(program) {
    clReleaseProgram(program);
  }
  if(context) {
    clReleaseContext(context);
  }

  if(bufTraceTime) {
    clReleaseMemObject(bufTraceTime);
  }

  printf("window size\tmax number of events\tmin number of events\n");
  for (int i = 0; i < nWSizes; ++i) {
    printf("%f\t%f\t\t\t\t%f\n", wSizes[i], outputdata[i][1], outputdata[i][0]);
  }

  const double end_time = getCurrentTimestamp();
  printf("\nTotal Time: %0.3f ms\n", (end_time - start_time) * 1e3);

  return 0;
}

// Get problem size i.e. number of lines in the data file
int get_problem_size() {
  long lines = 0;
  FILE *file;
  char buffer [100];

  file = fopen(filename, "r");
  if (file == NULL) {
    printf("ERROR: Unable to open %s.\n", filename);
    exit(EXIT_FAILURE);
  }

  while(!feof(file))
  {
    if ( fgets (buffer , sizeof(buffer) , file) == NULL ) 
      break;
    if (!strstr(buffer, "time,id") && buffer != "\n") {
      lines++;
      // lines+=5;
    }
  }

  fclose(file);

  if (lines == 0) {
    printf("ERROR: No data in %s.\n", filename);
    exit(EXIT_FAILURE);
  }
  return lines;
  // return lines-4;
}


// Read trace time values from file
void read_data() {
  FILE *file;
  char buffer [100];
  unsigned i = 0;

  // Initialize file pointer
  file = fopen(filename, "r");
  if (file == NULL) {
    printf("ERROR: Unable to open %s.\n", filename);
    exit(EXIT_FAILURE);
  }

  fileData.reset(N);
  // double ttime[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
  double ttime = 0.0;

  while(!feof(file))
  {
    if ( fgets (buffer , sizeof(buffer) , file) == NULL ) 
      break;
    if (!strstr(buffer, "time,id") && buffer != "\n") {
      
      sscanf (buffer,"%lf", &ttime);
      fileData[i] = ttime;
      i++;
      
      // sscanf (buffer,"%lf %lf %lf %lf %lf", &ttime[0], &ttime[1], &ttime[2], &ttime[3], &ttime[4]);
      // fileData[i++] = ttime[0];
      // fileData[i++] = ttime[1];
      // fileData[i++] = ttime[2];
      // fileData[i++] = ttime[3];
      // fileData[i++] = ttime[4];
    }
  }

  fclose(file);

  if (i == 0) {
    printf("ERROR: No data in %s.\n", filename);
    exit(EXIT_FAILURE);
  }
}

// Initializes the OpenCL objects
bool init_opencl() {
  cl_int status;

  printf("Initializing OpenCL\n");

  if(!setCwdToExeDir()) {
    return false;
  }

  // Get the OpenCL platform.
  platform = findPlatform("Altera");
  if(platform == NULL) {
    printf("ERROR: Unable to find Altera OpenCL platform.\n");
    return false;
  }

  // Query the available OpenCL device.
  device.reset(getDevices(platform, CL_DEVICE_TYPE_ALL, &nDevices));
  printf("Platform: %s\n", getPlatformName(platform).c_str());
  printf("Using %d device(s)\n", nDevices);
  for(unsigned i = 0; i < nDevices; ++i) {
    printf("  %s\n", getDeviceName(device[i]).c_str());
  }

  if(nDevices == 0) {
    checkError(-1, "No devices");
  }

  if (nDevices > 1) {
    checkError(-1, "More than one device available. This code uses only one device."); 
  }

  // Create the context.
  context = clCreateContext(NULL, nDevices, device, &oclContextCallback, NULL, &status);
  checkError(status, "Failed to create context");

  // Create the program for the given device.
  std::string binary_file = getBoardBinaryFile("acip", device[0]);
  printf("Using AOCX: %s\n", binary_file.c_str());
  program = createProgramFromBinary(context, binary_file.c_str(), device, nDevices);

  // Build the program that was just created.
  status = clBuildProgram(program, 0, NULL, "", NULL, NULL);
  checkError(status, "Failed to build program");

  return true;
}


bool init_buffers(int nWindowIndex) {
  cl_int status;

  // Number of bases = Number of trace time values such that if the window size is added to a value, 
  // it does not exceed the last (max) trace time.
  nBases = 0;
  for(unsigned i = 0; i < N && ((fileData[i] + wSizes[nWindowIndex]) <= fileData[N-1]); ++i) {
    nBases++;
  }

  if (nBases == 0) {
    printf("The number of bases is zero. This indicates that all of the given trace time values fit into the given window size (%f)\n", wSizes[nWindowIndex]);
    printf("\nMin: %d\nMax: %d\n", N, N);
    outputdata[nWindowIndex].reset(2);
    outputdata[nWindowIndex][0] = N;
    outputdata[nWindowIndex][1] = N;
    return true;
  }

  // Create a command queue for each kernel
  queue.reset(NUM_KERNELS);
  kernel.reset(NUM_KERNELS);

  // Distribute the bases among the kernels
  nBasesPerKernel.reset(NUM_KERNELS-2);

  // Determine the number of bases processed per kernel for distribution
  int nBasesSoFar = 0;
  for(unsigned i = 0; i < NUM_KERNELS-2; ++i) {
    if (nBasesSoFar >= nBases)
      nBasesPerKernel[i] = 0;

    nBasesPerKernel[i] = nBases / (NUM_KERNELS-2);
    if(i < (nBases % (NUM_KERNELS-2))) {
      nBasesPerKernel[i]++;
    }
    nBasesSoFar += nBasesPerKernel[i];
  }
  
  bufBase = clCreateBuffer(context, CL_MEM_READ_WRITE, nBases * sizeof(double), NULL, &status);
  checkError(status, "Failed to create buffer for input base");

  bufOutput = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_BANK_2_ALTERA, nBases * sizeof(double), NULL, &status);
  checkError(status, "Failed to create buffer for output");

  // Command queue for DATA_IN and DATA_OUT
  queue[K_DATA_IN] = clCreateCommandQueue(context, device[0], CL_QUEUE_PROFILING_ENABLE, &status);
  checkError(status, "Failed to create command queue");

  queue[K_DATA_OUT] = clCreateCommandQueue(context, device[0], CL_QUEUE_PROFILING_ENABLE, &status);
  checkError(status, "Failed to create command queue");

  // Kernel for DATA_IN and DATA_OUT
  kernel[K_DATA_IN] = clCreateKernel(program, kernel_names[K_DATA_IN], &status);
  checkError(status, "Failed to create kernel");

  kernel[K_DATA_OUT] = clCreateKernel(program, kernel_names[K_DATA_OUT], &status);
  checkError(status, "Failed to create kernel");

  // Command queue and kernel for the ACIP kernels defined in kernels.h
  for(unsigned i = 1; i < NUM_KERNELS-1; ++i) {
    if (nBasesPerKernel[i-1] != 0) {
      // Command queue
      queue[i] = clCreateCommandQueue(context, device[0], CL_QUEUE_PROFILING_ENABLE, &status);
      checkError(status, "Failed to create command queue");

      // Kernel
      kernel[i] = clCreateKernel(program, kernel_names[i], &status);
      checkError(status, "Failed to create kernel");

      printf("Kernel %s with Base size %d. \n", kernel_names[i], nBasesPerKernel[i-1]);
    }
  }
  return true;
}

// Initialize the input data for the problem
void init_problem() {

  inputTraceTime.reset(N);
  inputBase.reset(nBases);
  outputCounters.reset(nBases);

  int l = 0;

  for(unsigned j = 0; j < N; ++j) {
    inputTraceTime[j] = fileData[j];
  }

  for(unsigned j = 0; j < nBases; ++j) {
    inputBase[j] = fileData[l++];
  }
}

// Print the input data
void print_input_data() {
  printf("File data: ");
  for(unsigned i = 0; i < N; ++i) {
    printf("%1f ", fileData[i]);
  }
  printf("\n\n");

  printf("Trace Times: \n");
  for(unsigned j = 0; j < N; ++j) {
    printf("%f ", inputTraceTime[j]);
  }
  printf("\n\n");

  printf("Bases: \n");
  for(unsigned j = 0; j < nBases; ++j) {
    printf("%f ", inputBase[j]);
  }
  printf("\n\n");

  printf("Window Sizes: \n");
  for(unsigned j = 0; j < nWSizes; ++j) {
    printf("%f ", wSizes[j]);
  }
  printf("\n\n");
}

// Launch
void run(int nWindowIndex) {
  cl_int status;

  const double start_time = getCurrentTimestamp();

  // This event is used to keep track of the start and end time for each kernel
  scoped_array<cl_event> kernel_event(NUM_KERNELS);

  // This event is used to ensure that all kernels are started at the same time
  cl_event user_event = clCreateUserEvent(context, &status);
  checkError(status, "Failed to create user event");

  // Write the input data to the corressponding buffer
  status = clEnqueueWriteBuffer(queue[K_DATA_IN], bufTraceTime, CL_TRUE, 
    0, N * sizeof(double), inputTraceTime, 0, NULL, NULL);
  checkError(status, "Failed to transfer bufTraceTime");

  status = clEnqueueWriteBuffer(queue[K_DATA_IN], bufBase, CL_TRUE,
      0, nBases * sizeof(double), inputBase, 0, NULL, NULL);
  checkError(status, "Failed to transfer bufBase");

  // Set the arguments for the kernels
  status = clSetKernelArg(kernel[K_DATA_IN], 0, sizeof(cl_mem), &bufBase);
  checkError(status, "Failed to set DATA_OUT argument 0");

  cl_double dWSize = wSizes[nWindowIndex];
  cl_uint inputN = N;
  const size_t global_work_size = nBases;

  for (int i = 1; i < NUM_KERNELS - 1; ++i) {
    if (nBasesPerKernel[i-1] != 0) {
      status = clSetKernelArg(kernel[i], 0, sizeof(cl_mem), &bufTraceTime);
      checkError(status, "Failed to set %s argument 0", kernel_names[i]);

      status = clSetKernelArg(kernel[i], 1, sizeof(cl_double), &dWSize);
      checkError(status, "Failed to set %s argument 1", kernel_names[i]);

      status = clSetKernelArg(kernel[i], 2, sizeof(cl_uint), &inputN);
      checkError(status, "Failed to set %s argument 2", kernel_names[i]);
    }
  }
  
  status = clSetKernelArg(kernel[K_DATA_OUT], 0, sizeof(cl_mem), &bufOutput);
  checkError(status, "Failed to set DATA_OUT argument 0");

  printf("Launching for %d elements ... \n", global_work_size);

  // Launch kernels with user_event as the wait event
  status = clEnqueueNDRangeKernel(queue[K_DATA_IN], kernel[K_DATA_IN], 1, NULL,
      &global_work_size, NULL, 1, &user_event, &kernel_event[K_DATA_IN]);
  checkError(status, "Failed to launch kernel K_DATA_IN");

  for (int i = 1; i < NUM_KERNELS - 1; ++i) {
    if (nBasesPerKernel[i-1] != 0) {
      const size_t acip_work_size = nBasesPerKernel[i-1];
      status = clEnqueueNDRangeKernel(queue[i], kernel[i], 1, NULL,
        &acip_work_size, NULL, 1, &user_event, &kernel_event[i]);
      checkError(status, "Failed to launch kernel %s", kernel_names[i]);
    }
  }

  status = clEnqueueNDRangeKernel(queue[K_DATA_OUT], kernel[K_DATA_OUT], 1, NULL,
      &global_work_size, NULL, 1, &user_event, &kernel_event[K_DATA_OUT]);
  checkError(status, "Failed to launch kernel K_DATA_OUT");

  // Start all kernels by completing the user event
  clSetUserEventStatus(user_event, CL_COMPLETE);

  // Wait for command queue to complete pending events
  for(int i = 0; i < NUM_KERNELS; ++i) {
    if (i == 0 || i == NUM_KERNELS-1 || (i != 0 && i != NUM_KERNELS-1 && nBasesPerKernel[i-1] != 0)) {
      printf("Waiting for %s\n", kernel_names[i]);
      status = clFinish(queue[i]);
      printf("%s done.\n", kernel_names[i]);
      checkError(status, "Failed to finish (%d: %s)", i, kernel_names[i]);
    }
  }
  
  // Read the output from the output buffer
  status = clEnqueueReadBuffer(queue[K_DATA_OUT], bufOutput, CL_TRUE, 0, nBases * sizeof(double), outputCounters, 
    1, &kernel_event[K_DATA_OUT], NULL);
  
  const double end_time = getCurrentTimestamp();

  // Wall-clock time taken
  printf("\nTime: %0.3f ms\n", (end_time - start_time) * 1e3);

  // Get kernel times using the OpenCL event profiling API.
  for(unsigned i = 0; i < NUM_KERNELS; ++i) {
    if (i == 0 || i == NUM_KERNELS-1 || (i != 0 && i != NUM_KERNELS-1 && nBasesPerKernel[i-1] != 0)) {
      cl_ulong time_ns = getStartEndTime(kernel_event[i]);
      printf("Kernel time (Kernel %d): %0.3f ms\n", i, double(time_ns) * 1e-6);

      cl_ulong start;
      clGetEventProfilingInfo(kernel_event[i], CL_PROFILING_COMMAND_START,
                              sizeof(start), &start, NULL);
      cl_ulong end;
      clGetEventProfilingInfo(kernel_event[i], CL_PROFILING_COMMAND_END,
                              sizeof(end), &end, NULL);
      printf("Event %d: start=%llu, end=%llu \n", i, start, end);
    }
  }

  // Release all events.
  for(unsigned i = 0; i < NUM_KERNELS; ++i) {
    if (i == 0 || i == NUM_KERNELS-1 || (i != 0 && i != NUM_KERNELS-1 && nBasesPerKernel[i-1] != 0)) {
      clReleaseEvent(kernel_event[i]);
    }
  }

  int min = INT_MAX;
  int max = INT_MIN;
  for(unsigned j = 0; j < nBases; ++j) {
    if (outputCounters[j] > (double)max)
      max = outputCounters[j];

    if (outputCounters[j] < (double)min)
      min = outputCounters[j];
  }
  printf("\n");
  printf("\nMin: %d\nMax: %d\n", min, max);
  outputdata[nWindowIndex].reset(2);
  outputdata[nWindowIndex][0] = min;
  outputdata[nWindowIndex][1] = max;
}

// Free the resources allocated during initialization
void cleanup() {
  for(unsigned i = 0; i < NUM_KERNELS; ++i) {
    if (i == 0 || i == NUM_KERNELS-1 || (i != 0 && i != NUM_KERNELS-1 && nBasesPerKernel[i-1] != 0)) {
      if(kernel && kernel[i]) {
        clReleaseKernel(kernel[i]);
      }
      if(queue && queue[i]) {
        clReleaseCommandQueue(queue[i]);
      }
    }
  }
  
  if(bufBase) {
    clReleaseMemObject(bufBase);
  }

  if(bufOutput) {
    clReleaseMemObject(bufOutput);
  }
}

