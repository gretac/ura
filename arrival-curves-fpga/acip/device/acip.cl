// Generated Code
#pragma OPENCL EXTENSION cl_altera_channels : enable

// Channel declarations
channel double ACIP_BASE[22];
channel double ACIP_CTR[22];

kernel void data_in(global double *data_in) {
	int index = get_global_id(0);
	double base = data_in[index];
	int acipIndex = index % 22;
	switch (acipIndex) {
		case 0: write_channel_altera(ACIP_BASE[0], base); break;
		case 1: write_channel_altera(ACIP_BASE[1], base); break;
		case 2: write_channel_altera(ACIP_BASE[2], base); break;
		case 3: write_channel_altera(ACIP_BASE[3], base); break;
		case 4: write_channel_altera(ACIP_BASE[4], base); break;
		case 5: write_channel_altera(ACIP_BASE[5], base); break;
		case 6: write_channel_altera(ACIP_BASE[6], base); break;
		case 7: write_channel_altera(ACIP_BASE[7], base); break;
		case 8: write_channel_altera(ACIP_BASE[8], base); break;
		case 9: write_channel_altera(ACIP_BASE[9], base); break;
		case 10: write_channel_altera(ACIP_BASE[10], base); break;
		case 11: write_channel_altera(ACIP_BASE[11], base); break;
		case 12: write_channel_altera(ACIP_BASE[12], base); break;
		case 13: write_channel_altera(ACIP_BASE[13], base); break;
		case 14: write_channel_altera(ACIP_BASE[14], base); break;
		case 15: write_channel_altera(ACIP_BASE[15], base); break;
		case 16: write_channel_altera(ACIP_BASE[16], base); break;
		case 17: write_channel_altera(ACIP_BASE[17], base); break;
		case 18: write_channel_altera(ACIP_BASE[18], base); break;
		case 19: write_channel_altera(ACIP_BASE[19], base); break;
		case 20: write_channel_altera(ACIP_BASE[20], base); break;
		case 21: write_channel_altera(ACIP_BASE[21], base); break;
	}
}

kernel void data_out(global double *restrict data_out) {
	int index = get_global_id(0);
	int acipIndex = index % 22;
	switch (acipIndex) {
		case 0: data_out[index] = read_channel_altera(ACIP_CTR[0]); break;
		case 1: data_out[index] = read_channel_altera(ACIP_CTR[1]); break;
		case 2: data_out[index] = read_channel_altera(ACIP_CTR[2]); break;
		case 3: data_out[index] = read_channel_altera(ACIP_CTR[3]); break;
		case 4: data_out[index] = read_channel_altera(ACIP_CTR[4]); break;
		case 5: data_out[index] = read_channel_altera(ACIP_CTR[5]); break;
		case 6: data_out[index] = read_channel_altera(ACIP_CTR[6]); break;
		case 7: data_out[index] = read_channel_altera(ACIP_CTR[7]); break;
		case 8: data_out[index] = read_channel_altera(ACIP_CTR[8]); break;
		case 9: data_out[index] = read_channel_altera(ACIP_CTR[9]); break;
		case 10: data_out[index] = read_channel_altera(ACIP_CTR[10]); break;
		case 11: data_out[index] = read_channel_altera(ACIP_CTR[11]); break;
		case 12: data_out[index] = read_channel_altera(ACIP_CTR[12]); break;
		case 13: data_out[index] = read_channel_altera(ACIP_CTR[13]); break;
		case 14: data_out[index] = read_channel_altera(ACIP_CTR[14]); break;
		case 15: data_out[index] = read_channel_altera(ACIP_CTR[15]); break;
		case 16: data_out[index] = read_channel_altera(ACIP_CTR[16]); break;
		case 17: data_out[index] = read_channel_altera(ACIP_CTR[17]); break;
		case 18: data_out[index] = read_channel_altera(ACIP_CTR[18]); break;
		case 19: data_out[index] = read_channel_altera(ACIP_CTR[19]); break;
		case 20: data_out[index] = read_channel_altera(ACIP_CTR[20]); break;
		case 21: data_out[index] = read_channel_altera(ACIP_CTR[21]); break;
	}
}

// ACL kernel for ACIPs
kernel void acip1(global const double *ttime, double wsize, int N)
{
	int index = get_global_id(0);
	double base;
	base = read_channel_altera(ACIP_BASE[0]);
	base = nextafter(base, -0.00001);

	double count = 0;
	double limit = (base + wsize);
	for (int i = 0; i < N; ++i) {
		double t = nextafter(ttime[i], -0.00001);
		if (t >= base && t <= limit)
			count++;
	}
	write_channel_altera(ACIP_CTR[0], count);
}

kernel void acip2(global const double *ttime, double wsize, int N)
{
	int index = get_global_id(0);
	double base;
	base = read_channel_altera(ACIP_BASE[1]);
	base = nextafter(base, -0.00001);

	double count = 0;
	double limit = (base + wsize);
	for (int i = 0; i < N; ++i) {
		double t = nextafter(ttime[i], -0.00001);
		if (t >= base && t <= limit)
			count++;
	}
	write_channel_altera(ACIP_CTR[1], count);
}

kernel void acip3(global const double *ttime, double wsize, int N)
{
	int index = get_global_id(0);
	double base;
	base = read_channel_altera(ACIP_BASE[2]);
	base = nextafter(base, -0.00001);

	double count = 0;
	double limit = (base + wsize);
	for (int i = 0; i < N; ++i) {
		double t = nextafter(ttime[i], -0.00001);
		if (t >= base && t <= limit)
			count++;
	}
	write_channel_altera(ACIP_CTR[2], count);
}

kernel void acip4(global const double *ttime, double wsize, int N)
{
	int index = get_global_id(0);
	double base;
	base = read_channel_altera(ACIP_BASE[3]);
	base = nextafter(base, -0.00001);

	double count = 0;
	double limit = (base + wsize);
	for (int i = 0; i < N; ++i) {
		double t = nextafter(ttime[i], -0.00001);
		if (t >= base && t <= limit)
			count++;
	}
	write_channel_altera(ACIP_CTR[3], count);
}

kernel void acip5(global const double *ttime, double wsize, int N)
{
	int index = get_global_id(0);
	double base;
	base = read_channel_altera(ACIP_BASE[4]);
	base = nextafter(base, -0.00001);

	double count = 0;
	double limit = (base + wsize);
	for (int i = 0; i < N; ++i) {
		double t = nextafter(ttime[i], -0.00001);
		if (t >= base && t <= limit)
			count++;
	}
	write_channel_altera(ACIP_CTR[4], count);
}

kernel void acip6(global const double *ttime, double wsize, int N)
{
	int index = get_global_id(0);
	double base;
	base = read_channel_altera(ACIP_BASE[5]);
	base = nextafter(base, -0.00001);

	double count = 0;
	double limit = (base + wsize);
	for (int i = 0; i < N; ++i) {
		double t = nextafter(ttime[i], -0.00001);
		if (t >= base && t <= limit)
			count++;
	}
	write_channel_altera(ACIP_CTR[5], count);
}

kernel void acip7(global const double *ttime, double wsize, int N)
{
	int index = get_global_id(0);
	double base;
	base = read_channel_altera(ACIP_BASE[6]);
	base = nextafter(base, -0.00001);

	double count = 0;
	double limit = (base + wsize);
	for (int i = 0; i < N; ++i) {
		double t = nextafter(ttime[i], -0.00001);
		if (t >= base && t <= limit)
			count++;
	}
	write_channel_altera(ACIP_CTR[6], count);
}

kernel void acip8(global const double *ttime, double wsize, int N)
{
	int index = get_global_id(0);
	double base;
	base = read_channel_altera(ACIP_BASE[7]);
	base = nextafter(base, -0.00001);

	double count = 0;
	double limit = (base + wsize);
	for (int i = 0; i < N; ++i) {
		double t = nextafter(ttime[i], -0.00001);
		if (t >= base && t <= limit)
			count++;
	}
	write_channel_altera(ACIP_CTR[7], count);
}

kernel void acip9(global const double *ttime, double wsize, int N)
{
	int index = get_global_id(0);
	double base;
	base = read_channel_altera(ACIP_BASE[8]);
	base = nextafter(base, -0.00001);

	double count = 0;
	double limit = (base + wsize);
	for (int i = 0; i < N; ++i) {
		double t = nextafter(ttime[i], -0.00001);
		if (t >= base && t <= limit)
			count++;
	}
	write_channel_altera(ACIP_CTR[8], count);
}

kernel void acip10(global const double *ttime, double wsize, int N)
{
	int index = get_global_id(0);
	double base;
	base = read_channel_altera(ACIP_BASE[9]);
	base = nextafter(base, -0.00001);

	double count = 0;
	double limit = (base + wsize);
	for (int i = 0; i < N; ++i) {
		double t = nextafter(ttime[i], -0.00001);
		if (t >= base && t <= limit)
			count++;
	}
	write_channel_altera(ACIP_CTR[9], count);
}

kernel void acip11(global const double *ttime, double wsize, int N)
{
	int index = get_global_id(0);
	double base;
	base = read_channel_altera(ACIP_BASE[10]);
	base = nextafter(base, -0.00001);

	double count = 0;
	double limit = (base + wsize);
	for (int i = 0; i < N; ++i) {
		double t = nextafter(ttime[i], -0.00001);
		if (t >= base && t <= limit)
			count++;
	}
	write_channel_altera(ACIP_CTR[10], count);
}

kernel void acip12(global const double *ttime, double wsize, int N)
{
	int index = get_global_id(0);
	double base;
	base = read_channel_altera(ACIP_BASE[11]);
	base = nextafter(base, -0.00001);

	double count = 0;
	double limit = (base + wsize);
	for (int i = 0; i < N; ++i) {
		double t = nextafter(ttime[i], -0.00001);
		if (t >= base && t <= limit)
			count++;
	}
	write_channel_altera(ACIP_CTR[11], count);
}

kernel void acip13(global const double *ttime, double wsize, int N)
{
	int index = get_global_id(0);
	double base;
	base = read_channel_altera(ACIP_BASE[12]);
	base = nextafter(base, -0.00001);

	double count = 0;
	double limit = (base + wsize);
	for (int i = 0; i < N; ++i) {
		double t = nextafter(ttime[i], -0.00001);
		if (t >= base && t <= limit)
			count++;
	}
	write_channel_altera(ACIP_CTR[12], count);
}

kernel void acip14(global const double *ttime, double wsize, int N)
{
	int index = get_global_id(0);
	double base;
	base = read_channel_altera(ACIP_BASE[13]);
	base = nextafter(base, -0.00001);

	double count = 0;
	double limit = (base + wsize);
	for (int i = 0; i < N; ++i) {
		double t = nextafter(ttime[i], -0.00001);
		if (t >= base && t <= limit)
			count++;
	}
	write_channel_altera(ACIP_CTR[13], count);
}

kernel void acip15(global const double *ttime, double wsize, int N)
{
	int index = get_global_id(0);
	double base;
	base = read_channel_altera(ACIP_BASE[14]);
	base = nextafter(base, -0.00001);

	double count = 0;
	double limit = (base + wsize);
	for (int i = 0; i < N; ++i) {
		double t = nextafter(ttime[i], -0.00001);
		if (t >= base && t <= limit)
			count++;
	}
	write_channel_altera(ACIP_CTR[14], count);
}

kernel void acip16(global const double *ttime, double wsize, int N)
{
	int index = get_global_id(0);
	double base;
	base = read_channel_altera(ACIP_BASE[15]);
	base = nextafter(base, -0.00001);

	double count = 0;
	double limit = (base + wsize);
	for (int i = 0; i < N; ++i) {
		double t = nextafter(ttime[i], -0.00001);
		if (t >= base && t <= limit)
			count++;
	}
	write_channel_altera(ACIP_CTR[15], count);
}

kernel void acip17(global const double *ttime, double wsize, int N)
{
	int index = get_global_id(0);
	double base;
	base = read_channel_altera(ACIP_BASE[16]);
	base = nextafter(base, -0.00001);

	double count = 0;
	double limit = (base + wsize);
	for (int i = 0; i < N; ++i) {
		double t = nextafter(ttime[i], -0.00001);
		if (t >= base && t <= limit)
			count++;
	}
	write_channel_altera(ACIP_CTR[16], count);
}

kernel void acip18(global const double *ttime, double wsize, int N)
{
	int index = get_global_id(0);
	double base;
	base = read_channel_altera(ACIP_BASE[17]);
	base = nextafter(base, -0.00001);

	double count = 0;
	double limit = (base + wsize);
	for (int i = 0; i < N; ++i) {
		double t = nextafter(ttime[i], -0.00001);
		if (t >= base && t <= limit)
			count++;
	}
	write_channel_altera(ACIP_CTR[17], count);
}

kernel void acip19(global const double *ttime, double wsize, int N)
{
	int index = get_global_id(0);
	double base;
	base = read_channel_altera(ACIP_BASE[18]);
	base = nextafter(base, -0.00001);

	double count = 0;
	double limit = (base + wsize);
	for (int i = 0; i < N; ++i) {
		double t = nextafter(ttime[i], -0.00001);
		if (t >= base && t <= limit)
			count++;
	}
	write_channel_altera(ACIP_CTR[18], count);
}

kernel void acip20(global const double *ttime, double wsize, int N)
{
	int index = get_global_id(0);
	double base;
	base = read_channel_altera(ACIP_BASE[19]);
	base = nextafter(base, -0.00001);

	double count = 0;
	double limit = (base + wsize);
	for (int i = 0; i < N; ++i) {
		double t = nextafter(ttime[i], -0.00001);
		if (t >= base && t <= limit)
			count++;
	}
	write_channel_altera(ACIP_CTR[19], count);
}

kernel void acip21(global const double *ttime, double wsize, int N)
{
	int index = get_global_id(0);
	double base;
	base = read_channel_altera(ACIP_BASE[20]);
	base = nextafter(base, -0.00001);

	double count = 0;
	double limit = (base + wsize);
	for (int i = 0; i < N; ++i) {
		double t = nextafter(ttime[i], -0.00001);
		if (t >= base && t <= limit)
			count++;
	}
	write_channel_altera(ACIP_CTR[20], count);
}

kernel void acip22(global const double *ttime, double wsize, int N)
{
	int index = get_global_id(0);
	double base;
	base = read_channel_altera(ACIP_BASE[21]);
	base = nextafter(base, -0.00001);

	double count = 0;
	double limit = (base + wsize);
	for (int i = 0; i < N; ++i) {
		double t = nextafter(ttime[i], -0.00001);
		if (t >= base && t <= limit)
			count++;
	}
	write_channel_altera(ACIP_CTR[21], count);
}

