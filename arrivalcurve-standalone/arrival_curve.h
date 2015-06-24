#ifndef _ARRIVAL_CURVE_H_
#define _ARRIVAL_CURVE_H_
#include <vector>
using namespace std;
#define DEVICE_ID 0

//O(kmn) solution (k = number of steps, m = time interval size, n = event size)
float compute_arrival_curve(vector<float> &e, float min_windows_size, float max_windows_size, float max_event_param, vector<float> &max_events, vector<float> &max_left, vector<float> &max_right, vector<float> &min_events, vector<float> &min_left, vector<float> &min_right);

#endif
