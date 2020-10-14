// Week 1 - Problem I
// Tired Terry

#include <iostream>

using namespace std;

int main() {

	int length;		// n
	int interval;	// p
	int threshold;	// d
	
	cin >> length;
	cin >> interval;
	cin >> threshold;
	
	char pattern[length];
	cin >> pattern;
	
	int sleep = 0;
	
	// get the number of sleep seconds for the first second in the cycle
	for (int i = 0; i < interval; i++) {
		int index = i - interval + 1;
		if (index < 0) {
			index = length + index;
		}
		
		char c = pattern[index];
		if (c == 'Z') {
			sleep++;
		}
	}
	
	// seconds where he is tired
	int total_tired = 0;
	
	if (sleep < threshold) {
		total_tired++;
	}
	
	// go through each second in the cycle after the first
	// subtract 1 if the second no longer in the interval was a sleep second
	// add 1 if the new second in the interval is a sleep second
	// check if the new interval qualifies as a tired second (sleep seconds greater than the threshold)
	for (int i = 1; i < length; i++) {
		// the character to remove from the counting
		int last_index = i - interval;
		if (last_index < 0) {
			last_index = length + last_index;
		}
		
		if (pattern[last_index] == 'Z') {
			sleep--;
		}
		
		// the new character being added to the count
		int new_index = i;
		
		if (pattern[new_index] == 'Z') {
			sleep++;
		}
		
		if (sleep < threshold) {
			total_tired++;
		}
	}
	
	cout << total_tired << endl;
}
