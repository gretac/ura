#include <iostream>
#include <ctime>
#include <string>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
using namespace std;

//O(mn) solution (m = time interval size, n = event size)
typedef struct step {
	long long events;
	long long left;
	long long right;
} step;

vector<string> e;
vector<step>max_vec, min_vec;
long long max_event, maxc, minc, prev_minc, next_max, next_min;

void get_min(long long invl, bool enable){
	long long upper = 0;
	minc = e.size();
	//find number of events between 0 and invl
	while(stoll(e[upper]) <= invl){
		upper++;			
	}
	long long events = upper;
	if(minc > events) minc = events;
	long long lower = 0, udiff, ldiff;
	bool upset = true, loset = true, delay = false;
	while(upper < e.size()){
		if(stoll(e[lower]) > max_event - invl) break;		
		// how far to get to next upper event
		if(upset){
			upset = false;
			if(lower == 0)
				udiff = stoll(e[upper]) - invl;
			else
				udiff = stoll(e[upper]) - stoll(e[upper - 1]);
		}
		if(loset){
			loset = false;
			if(lower == 0)
				ldiff = stoll(e[lower]) - 0; // how far to get to first lower event (+ 1 for post clean up)
			else
				ldiff = stoll(e[lower]) - stoll(e[lower - 1]);  // how far to get to next lower event
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

void get_counts(long long invl){
	minc = e.size();
	maxc = 0;
	long long upper = 0;
	//find number of events between 0 and invl
	while(stoll(e[upper]) <= invl){
		upper++;			
	}
	long long events = upper;
	if(maxc < events) maxc = events;
	if(minc > events) minc = events;
	long long lower = 0, udiff, ldiff;
	bool upset = true, loset = true, delay = false;
	while(upper < e.size()){
		if(stoll(e[lower]) > max_event - invl){
			//last round
			events += e.size() - upper - 1;
			if(maxc < events) maxc = events;
			break;
		}
		// how far to get to next upper event
		if(upset){
			upset = false;
			if(lower == 0)
				udiff = stoll(e[upper]) - invl;
			else
				udiff = stoll(e[upper]) - stoll(e[upper - 1]);
		}
		if(loset){
			loset = false;
			if(lower == 0)
				ldiff = stoll(e[lower]) - 0; // how far to get to first lower event (+ 1 for post clean up)
			else
				ldiff = stoll(e[lower]) - stoll(e[lower - 1]);  // how far to get to next lower event
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
		if(minc > events - 1) minc = events - 1; //IMPORTANT: the reason is the delay subtraction
	}	
}

long long bin_max_steps(long long lower, long long upper, long long curr){
	long long mid = (lower + upper) / 2;
	get_counts(mid);
	if(maxc == curr){
		get_counts(mid + 1);
		if(maxc > curr){
			next_max = maxc;
			return mid;
		} else {
			return bin_max_steps(mid + 1, upper, curr);
		}
	} else {
		return bin_max_steps(lower, mid - 1, curr);
	}
}

long long bin_min_steps(long long lower, long long upper, long long curr, bool enable){
	long long mid = (lower + upper) / 2;
	get_min(mid, enable);
	if(minc == curr){
		get_min(mid + 1, enable);
		if(minc > curr){
			next_min = minc;
			return mid;
		} else {
			return bin_min_steps(mid + 1, upper, curr, true);
		}
	} else {
		return bin_min_steps(lower, mid - 1, curr, false);
	}
}

int main( int argc, char *argv[] ){	
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
	while (std::getline(infile, line)) {
		istringstream iss(line);
		if (!(iss >> tmp)) break; // error
		e.push_back(tmp);
	}
	infile.close();
	ofstream cout;
	cout.open(argv[4]);
	max_event = stoll(e[e.size() - 1]);
	if(atoll(argv[2]) > max_event){
		cout << "[maximum interval] is larger than the max event time. Exiting...\n";
		return 0;
	}
	cout << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"100%\" height=\"100%\" version=\"1.\">\n<style type=\"text/css\"><![CDATA[line{stroke:#006600;fill:#00 cc00;} text{font-size:\"large\";font-family:\"sans-serif\"}]]></style>" << endl;
	cout << "<text x=\"10\" y=\"300\">Events</text>" << endl;
	cout << "<text x=\"450\" y=\"550\">Interval Length(ns)</text>" << endl;
	cout << "<line x1=\"100\" y1=\"100\" x2=\"100\" y2=\"500\" />" << endl;
	cout << "<line x1=\"100\" y1=\"500\" x2=\"900\" y2=\"500\" />" << endl;
	
	long long curr = atoll(argv[1]), last = atoll(argv[2]);
	get_counts(last);
	long long last_max = maxc, last_min = minc;
	get_counts(curr);
	long long curr_max = maxc, curr_min = minc, next;
	step s;
	cout << "<!--" << endl;
	while(curr_max != last_max){
		next = bin_max_steps(curr, last, curr_max);		
		cout << "maxc = " << curr_max << " for intervals between " << curr << " and " << next << endl;
		s.events = curr_max;
		s.left = curr;
		s.right = next;
		max_vec.push_back(s);
		curr = next + 1;
		curr_max = next_max;
	}
	cout << "maxc = " << curr_max << " for intervals between " << curr << " and " << last << endl << endl;
	s.events = curr_max;
	s.left = curr;
	s.right = last;
	max_vec.push_back(s);
		
	curr = atoll(argv[1]);
	while(curr_min != last_min){
		next = bin_min_steps(curr, last, curr_min, false);
		cout << "minc = " << curr_min << " for intervals between " << curr << " and " << next << endl;
		s.events = curr_min;
		s.left = curr;
		s.right = next;
		min_vec.push_back(s);
		curr = next + 1;
		curr_min = next_min;
	}
	cout << "minc = " << curr_min << " for intervals between " << curr << " and " << last << endl << endl;
	cout << "-->" << endl;
	s.events = curr_min;
	s.left = curr;
	s.right = last;
	min_vec.push_back(s);
	
	long long yrange = max_vec[max_vec.size() - 1].events - min_vec[0].events;
	long long yoffset = min_vec[0].events;
	long long xrange = atoll(argv[2]) - atoll(argv[1]);
	long long xprev = 100, yprev = 500, xnew, ynew;
	
	s = max_vec[0];
	for(long long i = 0; i < max_vec.size(); i++){
		s = max_vec[i];
		ynew = yprev - ((s.events - yoffset) * 400 / yrange) ;
		xnew = xprev + ((s.right - s.left + 1) * 800 / xrange) ;
		if(xnew > 900)
			xnew = 900;
		cout << "<text x=\"70\" y=\"" << (ynew + 5) << "\">" << s.events << "</text>" << endl;
		cout << "<line x1=\"" << xprev << "\" y1=\"" << yprev << "\" x2=\"" << xprev << "\" y2=\"" << ynew << "\" />" << endl;		

		cout << "<line x1=\"" << xprev << "\" y1=\"" << ynew << "\" x2=\"" << xnew << "\" y2=\"" << ynew << "\" />" << endl;		
		cout << "<text x=\"" << (xprev - 5) << "\" y=\"" << yprev << "\">" << s.left << "</text>" << endl;
		
		xprev = xnew;
		yprev = ynew;
		yoffset = s.events;
	}
	cout << "<text x=\"" << (xnew - 5) << "\" y=\"" << ynew << "\">" << s.right << "</text>" << endl;
	
	xprev = 100, yprev = 500;
	yoffset = min_vec[0].events;
	for(long long i = 0; i < min_vec.size(); i++){
		s = min_vec[i];
		ynew = yprev - ((s.events - yoffset) * 400 / yrange) ;
		xnew = xprev + ((s.right - s.left) * 800 / xrange) ;
		if(xnew > 900)
			xnew = 900;
		cout << "<line x1=\"" << xprev << "\" y1=\"" << yprev << "\" x2=\"" << xprev << "\" y2=\"" << ynew << "\" />" << endl;		

		cout << "<line x1=\"" << xprev << "\" y1=\"" << ynew << "\" x2=\"" << xnew << "\" y2=\"" << ynew << "\" />" << endl;		
		cout << "<text x=\"" << (xprev - 5) << "\" y=\"" << yprev << "\">" << s.left << "</text>" << endl;
		
		xprev = xnew;
		yprev = ynew;
		yoffset = s.events;
	}
	cout << "<text x=\"" << (xnew - 5) << "\" y=\"" << ynew << "\">" << s.right << "</text>" << endl;
	
	long double duration = (long double) (std::clock() - start) / CLOCKS_PER_SEC;
	cout << "<!--" << endl;
	cout << "Duration: " << duration << endl;
	cout << "-->" << endl;
	cout << "</svg>";
	cout.close();
}
