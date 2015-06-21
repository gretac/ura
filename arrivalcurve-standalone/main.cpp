#include <iostream>
#include <ctime>
#include <string>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
using namespace std;

#define DEVICE_ID 0

//O(mn) solution (m = time interval size, n = event size)
typedef struct step {
	float events;
	float left;
	float right;
} step;

ofstream stream;
vector<step>max_vec, min_vec;
float max_event, maxc, minc, prev_minc, next_max, next_min, getcount = 0, totalcount = 0;

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
		//stream << "ldiff " << ldiff << " udiff " << udiff << endl;
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
		//stream << "ldiff " << ldiff << " udiff " << udiff << endl;
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
		if(minc > events - 1) minc = events - 1; //IMPORTANT: the reason is the delay subtraction
	}	
}

float bin_max_steps(vector<float> &e, float lower, float upper, float curr){
	long long mid = (lower + upper) / 2;
	get_counts(e, (float)mid);
	if(maxc == curr){
		get_counts(e, mid + 1);
		if(maxc > curr){
			next_max = maxc;
			return mid;
		} else {
			return bin_max_steps(e, mid + 1, upper, curr);
		}
	} else {
		return bin_max_steps(e, lower, mid - 1, curr);
	}
}

float bin_min_steps(vector<float> &e, float lower, float upper, float curr, bool enable){
	long long mid = (lower + upper) / 2;
	get_min(e, (float)mid, enable);
	if(minc == curr){
		get_min(e, mid + 1, enable);
		if(minc > curr){
			next_min = minc;
			return mid;
		} else {
			return bin_min_steps(e, mid + 1, upper, curr, true);
		}
	} else {
		return bin_min_steps(e, lower, mid - 1, curr, false);
	}
}

void computer_arrival_curve(vector<float> &e, float min_windows_size, float max_windows_size){
	float curr = min_windows_size, last = max_windows_size;
	get_counts(e, last);
	float last_max = maxc, last_min = minc;
	get_counts(e, curr);
	float curr_max = maxc, curr_min = minc, next;
	step s;
	while(curr_max != last_max){
		next = bin_max_steps(e, curr, last, curr_max);		
		stream << "maxc = " << curr_max << " for intervals between " << curr << " and " << next << endl;
		stream << "called getcount() " << getcount << " times" << endl;
		totalcount += getcount;
		getcount = 0;
		s.events = curr_max;
		s.left = curr;
		s.right = next;
		max_vec.push_back(s);
		curr = next + 1;
		curr_max = next_max;
	}
	stream << "maxc = " << curr_max << " for intervals between " << curr << " and " << last << endl;
	stream << "called getcount() " << getcount << " times" << endl << endl;
	totalcount += getcount;
	getcount = 0;
	s.events = curr_max;
	s.left = curr;
	s.right = last;
	max_vec.push_back(s);
		
	curr = min_windows_size;
	while(curr_min != last_min){
		next = bin_min_steps(e, curr, last, curr_min, false);
		stream << "minc = " << curr_min << " for intervals between " << curr << " and " << next << endl;
		stream << "called getcount() " << getcount << " times" << endl;
		totalcount += getcount;
		getcount = 0;
		s.events = curr_min;
		s.left = curr;
		s.right = next;
		min_vec.push_back(s);
		curr = next + 1;
		curr_min = next_min;
	}
	stream << "minc = " << curr_min << " for intervals between " << curr << " and " << last << endl;
	stream << "called getcount() " << getcount << " times" << endl << endl;
	totalcount += getcount;
	getcount = 0;
	s.events = curr_min;
	s.left = curr;
	s.right = last;
	min_vec.push_back(s);
}

int main(int argc, char *argv[]){
	if ( argc != 5 || atoll(argv[1]) <= 0 || atoll(argv[2]) <= atoll(argv[1]) ){
		cout << "usage: [minimum interval ( >= 1 ns )] [maximum interval] [input] [output]\n";
		return 0;
	}
    clock_t start = clock();
	ifstream infile(argv[3]);
	string tmp, line;
	if(!infile.good()){
		infile.close();
		cout << "input file does not exist!\n";
		return 0;
	}
	//this is the code of setting up vector events.
	vector<float> e;
	while (std::getline(infile, line)) {
		istringstream iss(line);
		if (!(iss >> tmp)) break; // error
		e.push_back(stof(tmp));
	}
	infile.close();
	stream.open(argv[4]);
	max_event = e[e.size() - 1];
	if(atoll(argv[2]) > max_event){
		cout << "[maximum interval] is larger than the max event time. Exiting...\n";
		return 0;
	}
	computer_arrival_curve(e, stof(argv[1]), stof(argv[2]));
	
	long double duration = (long double) (std::clock() - start) / CLOCKS_PER_SEC;
	stream << "Duration: " << duration << endl;
	stream << "total number of getcount(): " << totalcount << endl;
	stream << "time spent per getcount(): " << duration / totalcount << endl;
	stream.close();
        return 0;
    
}
