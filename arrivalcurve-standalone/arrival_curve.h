#ifndef _ARRIVAL_CURVE_H_
#define _ARRIVAL_CURVE_H_
#include <vector>
using namespace std;
#define DEVICE_ID 0

//O(kmn) solution (k = number of steps, m = time interval size, n = event size)
//This method returns the total number of calls made to compute the entire arrival curve
//and it takes nine arguments
//e is the event vector
//min_windows_size is the lower interval size
//max_windows_size is the upper interval size
//max_events is the result in the form of a vector holding the maximum number of events
//max_left is the result in the form of a vector holding the left boundary of the maximum events
//max_right is the result in the form of a vector holding the right boundary of the maximum events
//min_events is the result in the form of a vector holding the minimum number of events
//min_left is the result in the form of a vector holding the left boundary of the minimum events
//min_right is the result in the form of a vector holding the right boundary of the minimum events

float compute_arrival_curve(vector<float> &e, float min_windows_size, float max_windows_size, 
vector<float> &max_events, vector<float> &max_left, vector<float> &max_right, 
vector<float> &min_events, vector<float> &min_left, vector<float> &min_right);

#endif
