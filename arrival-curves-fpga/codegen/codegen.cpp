#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>

#define OPENCL_FILENAME "acip.cl"
#define KERNEL_HEADER "kernels.h"

// Function prototypes
bool GenerateOpenCLCode(int);
bool GenerateKernelsHeader(int);

// Entry point.
int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: ./codegen <No. of ACIPs to generate>\n");
    return -1;
  }

  int n = atoi(argv[1]);

  if (n < 0) {
    printf("Usage: ./codegen <No. of ACIPs to generate>\n");
    return -1;
  }

  if (!GenerateOpenCLCode(n)) {
    printf("OpenCL Code generation failed\n");
    return -1;
  }

  if (!GenerateKernelsHeader(n)) {
    printf("Kernel Header file generation failed\n");
    return -1;
  }

  return 0;
}

bool GenerateOpenCLCode(int n) {
  FILE *file;

  // Initialize file pointer
  file = fopen(OPENCL_FILENAME, "w");
  if (file == NULL) {
    printf("ERROR: Unable to create/write to %s.\n", OPENCL_FILENAME);
    return false;
  }

  fprintf(file, "// Generated Code\n");
  fprintf(file, "#pragma OPENCL EXTENSION cl_altera_channels : enable\n");
  fprintf(file, "\n");
  fprintf(file, "// Channel declarations\n");
  fprintf(file, "channel double ACIP_BASE[%d];\n", n);
  fprintf(file, "channel double ACIP_CTR[%d];\n", n);
  fprintf(file, "\n");

  // Generate data_in kernel
  fprintf(file, "kernel void data_in(global double *data_in) {\n");
  fprintf(file, "\tint index = get_global_id(0);\n");
  fprintf(file, "\tdouble base = data_in[index];\n");
  fprintf(file, "\tint acipIndex = index %% %d;\n", n);
  fprintf(file, "\tswitch (acipIndex) {\n");
  for (int i = 0; i < n; ++i) {
    fprintf(file, "\t\tcase %d: write_channel_altera(ACIP_BASE[%d], base); break;\n", i, i);
  }
  fprintf(file, "\t}\n");
  fprintf(file, "}\n");
  fprintf(file, "\n");

  // Generate data_out kernel
  fprintf(file, "kernel void data_out(global double *restrict data_out) {\n");
  fprintf(file, "\tint index = get_global_id(0);\n");
  fprintf(file, "\tint acipIndex = index %% %d;\n", n);
  fprintf(file, "\tswitch (acipIndex) {\n");
  for (int i = 0; i < n; ++i) {
    fprintf(file, "\t\tcase %d: data_out[index] = read_channel_altera(ACIP_CTR[%d]); break;\n", i, i);
  }
  fprintf(file, "\t}\n");
  fprintf(file, "}\n");
  fprintf(file, "\n");

  // Kernels for ACIPs
  fprintf(file, "// ACL kernel for ACIPs\n");
  for (int i = 0; i < n; ++i) {
    fprintf(file, "kernel void acip%d(global const double *ttime, double wsize, int N)\n", i+1);
    fprintf(file, "{\n");
    fprintf(file, "\tint index = get_global_id(0);\n");
    fprintf(file, "\tdouble base;\n");
    fprintf(file, "\tbase = read_channel_altera(ACIP_BASE[%d]);\n", i);
    fprintf(file, "\tbase = nextafter(base, -0.00001);\n");
    fprintf(file, "\n");
    fprintf(file, "\tdouble count = 0;\n");
    fprintf(file, "\tdouble limit = (base + wsize);\n");
    fprintf(file, "\tfor (int i = 0; i < N; ++i) {\n");
    fprintf(file, "\t\tdouble t = nextafter(ttime[i], -0.00001);\n");
    fprintf(file, "\t\tif (t >= base && t <= limit)\n");
    fprintf(file, "\t\t\tcount++;\n");
    fprintf(file, "\t}\n");
    fprintf(file, "\twrite_channel_altera(ACIP_CTR[%d], count);\n", i);
    fprintf(file, "}\n");
    fprintf(file, "\n");
  }

  return true;
}

bool GenerateKernelsHeader(int n) {
  FILE *file;

  // Initialize file pointer
  file = fopen(KERNEL_HEADER, "w");
  if (file == NULL) {
    printf("ERROR: Unable to create/write to %s.\n", KERNEL_HEADER);
    return false;
  }
  
  fprintf(file, "enum KERNELS {\n");
  fprintf(file, "\tK_DATA_IN,\n");
  for (int i = 1; i <= n; ++i) {
    fprintf(file, "\tK_ACIP%d,\n", i);
  }
  fprintf(file, "\tK_DATA_OUT,\n");
  fprintf(file, "\tNUM_KERNELS\n");
  fprintf(file, "};\n");

  fprintf(file, "static const char* kernel_names[NUM_KERNELS] = \n");
  fprintf(file, "{\n");
  fprintf(file, "\t\"data_in\",\n");
  for (int i = 1; i <= n; ++i) {
    fprintf(file, "\t\"acip%d\",\n", i);
  }
  fprintf(file, "\t\"data_out\",\n");
  fprintf(file, "};\n");

  return true;
}
