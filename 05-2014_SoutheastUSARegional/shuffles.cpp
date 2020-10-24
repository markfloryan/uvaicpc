#include<iostream>
#include<math.h>

using namespace std;

int main(){

	int n;
	cin >> n;

	//problem indexes from 1, so we will too
	//index i will store the location in the shuffled list of card numbered i
	int* a = new int[n+1];

	for(int i=1; i<=n; i++){
		int num;
		cin >> num;
		a[num] = i; //card numbered 'num' is at position i in shuffle
	}

	int c = 1; //count number of times we have 'splits'
	for(int i=2; i<=n; i++){
		//if the number i is further 'left' than i-1
		//e.g., 2 is left of 1, then inversion
		if(a[i] < a[i-1]) c++; //c++, hahahaha
	}

	//answer is ceiling(log_2(c))
	cout << ceil(log2(c)) << endl;

		

	return 0;
}