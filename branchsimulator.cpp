#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <cmath>
#include <bitset>

using namespace std;

struct config {
	int m;
};

int main(int argc, char* argv[]) {
	config cacheconfig;
	ifstream cache_params;
	cache_params.open(argv[1]);
	while (!cache_params.eof()) {  // read config file value m
		cache_params >> cacheconfig.m;
	}
	int numCounter = pow(2.0, cacheconfig.m); //each counters start at 11
	vector<bitset<2> > sCounter;
	sCounter.resize(numCounter);
	for (int i = 0;i < numCounter;i++) {
		sCounter[i] = bitset<2>(11);
	}

	int result;
	ifstream traces;
	ofstream tracesout;
	string outname;
	outname = string(argv[2]) + ".out";

	traces.open(argv[2]);
	tracesout.open(outname.c_str());

	string line;
	string xaddr; 
	int tnt;  // taken or not taken      
	unsigned int addr;
	bitset<32> branchins;
	if (traces.is_open() && tracesout.is_open()) {
		while (getline(traces, line)) {   // read trace file
			istringstream iss(line);
			if (!(iss >> xaddr >> tnt)) { break; }
			stringstream saddr(xaddr);
			saddr >> std::hex >> addr;
			branchins = bitset<32>(addr);
			long int a = 0;
			if (tnt == 1)
			{
				for (int i = 0;i < cacheconfig.m;i++) {
					a += (branchins[i] * pow(2.0, i));
				}
				if (sCounter[a] == 11) {
					result = 1;
					sCounter[a] = 11;
				}
				else if (sCounter[a] == 10) {
					result = 1;
					sCounter[a] = 11;
				}
				else if (sCounter[a] == 01) {
					result = 0;
					sCounter[a] = 11;
				}
				else if (sCounter[a] == 00) {
					result = 0;
					sCounter[a] = 01;
				}
			}

			else if (tnt == 0)
			{
				for (int i = 0;i < cacheconfig.m;i++) {
					a += (branchins[i] * pow(2.0, i));
				}
				if (sCounter[a] == 11) {
					result = 1;
					sCounter[a] = 10;
				}
				else if (sCounter[a] == 10) {
					result = 1;
					sCounter[a] = 00;
				}
				else if (sCounter[a] == 01) {
					result = 0;
					sCounter[a] = 00;
				}
				else if (sCounter[a] == 00) {
					result = 0;
					sCounter[a] = 00;
				}
			}
			tracesout << result << endl;  // Output taken/not taken
		}
		traces.close();
		tracesout.close();
	}
	else cout << "Unable to open trace or traceout file ";
	return 0;
}