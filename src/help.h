#ifndef HELP_H
#define HELP_H

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

struct UsrParameters
{
	UsrParameters();
	~UsrParameters();
	std::string methylationfile;
	std::string normalMapfile;
	std::string outputFilepath;
	std::string configFilepath;
	int ClassNumber;
	float RemoveCutoff;
	int MapSitesNumber;
	int MaxiterTime;
	bool verbose;
};

void print_help();
int mGetOptions(int rgc, char *rgv[]);
void Paramscan(int argc, char *argv[]);



#endif