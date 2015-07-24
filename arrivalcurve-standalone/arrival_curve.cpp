#include <iostream>
#include <ctime>
#include <string>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include "arrival_curve.h"

using namespace std;

ofstream stream;
float max_event, maxc, minc, prev_minc, next_max, next_min, getcount = 0, totalcount = 0;

//This method set the minc (global variable) and it takes three arguments
//e is the event vector
//invl is the interval size
//enable is a flag indicating whether to turn on skip mode or not
//skip mode is for skipping the remaining binary searches
//if the number of steps searched up to this point equals
//to the prior number of steps

void get_min(vector<float> &e, float invl, bool enable){
        getcount++;
        float upper = 0;
        minc = e.size();
        //find number of events between 0 and invl
        while(e[upper] <= invl){
                upper++;
        }
        float events = upper;
        if(minc > events) minc = events;
        float lower = 0, udiff, ldiff;
        bool upset = true, loset = true, delay = false;
        while(upper < e.size()){
                if(e[lower] > max_event - invl) break;
                // how far to get to next upper event
                if(upset){
                        upset = false;
                        if(lower == 0)
                                udiff = e[upper] - invl;
                        else
                                udiff = e[upper] - e[upper - 1];
                }
                if(loset){
                        loset = false;
                        if(lower == 0)
                                ldiff = e[lower] - 0; // how far to get to first lower event (+ 1 for post clean up)
                        else
                                ldiff = e[lower] - e[lower - 1];  // how far to get to next lower event
                }
                //cout << "ldiff " << ldiff << " udiff " << udiff << endl;
                if(udiff < ldiff){
                        upper++;
                        ldiff -= udiff;
                        upset = true;
                        events++;
                        if(delay){
                                events--;
                                delay = false;
                        }
                } else if(udiff > ldiff){
                        lower++;
                        udiff -= ldiff;
                        loset = true;
                        if(delay) events--;
                        else delay = true;
                } else{
                        upper++;
                        lower++;
                        upset = true;
                        loset = true;
                        events++;
                        if(delay) events--;
                        delay = true;
                }
                if(minc > events - 1) minc = events - 1; //IMPORTANT: the reason is the delay subtract
                if(minc == prev_minc && enable) break;
        }
        prev_minc = minc;
}

//This method set the minc (global variable) and the maxc (global variable) 
//and it takes two arguments
//e is the event vector
//invl is the interval size
//skip mode is not allowed because calculating maxc 
//does not allow skipping

void get_counts(vector<float> &e, float invl){
        getcount++;
        minc = e.size();
        maxc = 0;
        float upper = 0;

        //find number of events between 0 and invl
        while(e[upper] <= invl){
                upper++;
        }
        float events = upper;
        if(maxc < events) maxc = events;
        if(minc > events) minc = events;
        float lower = 0, udiff, ldiff;
        bool upset = true, loset = true, delay = false;
        while(upper < e.size()){
                if(e[lower] > max_event - invl){
                        //last round
                        events += e.size() - upper - 1;
                        if(maxc < events) maxc = events;
                        break;
                }
                // how far to get to next upper event
                if(upset){
                        upset = false;
                        if(lower == 0)
                                udiff = e[upper] - invl;
                        else
                                udiff = e[upper] - e[upper - 1];
                }
                if(loset){
                        loset = false;
                        if(lower == 0)
                                ldiff = e[lower] - 0; // how far to get to first lower event (+ 1 for post clean up)
                        else
                                ldiff = e[lower] - e[lower - 1];  // how far to get to next lower event
                }
                //cout << "ldiff " << ldiff << " udiff " << udiff << endl;
                if(udiff < ldiff){
                        upper++;
                        ldiff -= udiff;
                        upset = true;
                        events++;
                        if(delay){
                                events--;
                                delay = false;
                        }
                } else if(udiff > ldiff){
                        lower++;
                        udiff -= ldiff;
                        loset = true;
                        if(delay) events--;
                        else delay = true;
                } else{
                        upper++;
                        lower++;
                        upset = true;
                        loset = true;
                        events++;
                        if(delay) events--;
                        delay = true;
                }
                if(maxc < events) maxc = events;
                if(minc > events - 1 && events - 1 >= 0) minc = events - 1; //IMPORTANT: the reason is the delay subtraction
        }
}

//This method returns the interval size when the number of max events increase by one
//and it takes four arguments
//e is the event vector
//lower is the lower interval size
//upper is the upper interval size
//curr is the current size for reference

float bin_max_steps(vector<float> &e, float lower, float upper, float curr, float res){
        long long mid = (lower + upper) / 2;
        get_counts(e, (float)mid);
        if(maxc == curr){
		if(mid + res >= max_event)
                	return upper - 1;
		else
			get_counts(e, mid + res);
                if(maxc > curr){
                        next_max = maxc;
                        return mid;
                } else {
                        return bin_max_steps(e, mid + 1, upper, curr, res);
                }
        } else {
                return bin_max_steps(e, lower, mid - 1, curr, res);
        }
}

//This method returns the interval size when the number of min events increase by one
//and it takes five arguments
//e is the event vector
//lower is the lower interval size
//upper is the upper interval size
//curr is the current size for reference
//enable is a flag indicating whether to turn on skip mode or not
//skip mode is for skipping the remaining binary searches
//if the number of steps searched up to this point equals
//to the prior number of steps

float bin_min_steps(vector<float> &e, float lower, float upper, float curr, bool enable, float res){
        long long mid = (lower + upper) / 2;
        get_min(e, (float)mid, enable);
        if(minc == curr){
		if(mid + res >= max_event)
                	return upper - 1;
		else
                get_min(e, mid + res, enable);
                if(minc > curr){
                        next_min = minc;
                        return mid;
                } else {
                        return bin_min_steps(e, mid + 1, upper, curr, true, res);
                }
        } else {
                return bin_min_steps(e, lower, mid - 1, curr, false, res);
        }
}

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
float compute_arrival_curve(vector<float> &e, float min_windows_size, float max_windows_size, float res, vector<float> &max_events, vector<float> &max_left, vector<float> &max_right, 
vector<float> &min_events, vector<float> &min_left, vector<float> &min_right){
	max_event = e[e.size()-1];
        float curr = min_windows_size, last = max_windows_size;	
	if(max_windows_size >= max_event) last = max_event - 1;
        get_counts(e, last);
        float last_max = maxc, last_min = minc;	
	//cout << last_min << endl;
        get_counts(e, curr);
        float curr_max = maxc, curr_min = minc, next;
	//cout << curr_min << endl;
        while(curr_max != last_max){
                next = bin_max_steps(e, curr, last, curr_max, res);
                totalcount += getcount;
                getcount = 0;
                max_events.push_back(curr_max);
                max_left.push_back(curr);
                max_right.push_back(next);
                curr = next + 1;
                curr_max = next_max;
        }
        totalcount += getcount;
        getcount = 0;
        max_events.push_back(curr_max);
        max_left.push_back(curr);
        max_right.push_back(last);
        curr = min_windows_size;
	if(max_windows_size >= max_event) {
		max_events.push_back(e.size());
        	max_left.push_back(max_event);
        	max_right.push_back(max_windows_size);
	}
        while(curr_min != last_min){
                next = bin_min_steps(e, curr, last, curr_min, false, res);
                totalcount += getcount;
                getcount = 0;
                min_events.push_back(curr_min);
                min_left.push_back(curr);
                min_right.push_back(next);
                curr = next + 1;
                curr_min = next_min;
        }
        totalcount += getcount;
        getcount = 0;
        min_events.push_back(curr_min);
        min_left.push_back(curr);
        min_right.push_back(last);
	if(max_windows_size >= max_event) {
		min_events.push_back(e.size());
        	min_left.push_back(max_event);
        	min_right.push_back(max_windows_size);
	}
        return totalcount;
}


