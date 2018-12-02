#include "help.h"

UsrParameters::UsrParameters() {
	methylationfile = "";
	normalMapfile = "";
	outputFilepath = "";
	configFilepath = "";
	ClassNumber = 10;
	RemoveCutoff = 0.01;
	MapSitesNumber = 80000;
	MaxiterTime = 10000;
}

UsrParameters::~UsrParameters(){}	

UsrParameters UsrParameter;


std::ifstream fin_d;
std::ofstream fout;

void print_help(){
	std::cout << "Usage: MEpurity <-f tumorMethylationfile> <-m normalMapfile> <-o outputFilepath> [...]" << endl << endl;
	std::cout << "MEpurity version : 0.1" << endl;
	std::cout << "Program : MEpurity (Cauculate tumor purity using DNA Methylation differences.)" << endl;
	std::cout << "Required parameters:" << endl << '\t' << '\t';
	std::cout << "-f:" << "	The 450k methylation input data. Either this, a config file of input data.\n" << endl;
	std::cout << "		-F:" << "	The config file path of input data. Either this, a 450k methylation input data.\n" << endl;
	std::cout << "		-m:" << "	The normal mapfile under path of this software.\n" << endl;
	std::cout << "		-o:" << "	The output file path that you would like to contain the results.\n" << endl;
	std::cout << "Optional parameters:" << endl << '\t' << '\t';
	std::cout << "-h" << "	Show this help message and exit.\n";
	std::cout << "		-s" << "	The number of CpG sites that you want to use in the map file.(Default:80000)\n" << endl;
	std::cout << "		-t" << "	The maximum iteration time of bmm algorithm.(Default:10000)\n" << endl;
	std::cout << "		-c" << "	The least percemtage of sites belonging to a cluster that would not be filted.(Default:0.01)\n" << endl;
	std::cout << "		-n" << "	The original number of clusters.(Default:10)\n" << endl;
	exit(1);
}


int mGetOptions(int rgc, char *rgv[]) {
	
	int i;
	for (i = 1; i < rgc; i++) {
		if (rgv[i][0] != '-') return i;
		switch (rgv[i][1]) {
			case 'h':print_help();
			case 'f':UsrParameter.methylationfile = rgv[++i]; break;
			case 'F':UsrParameter.configFilepath = rgv[++i]; break;
			case 'm':UsrParameter.normalMapfile = rgv[++i]; break;
			case 'o':UsrParameter.outputFilepath = rgv[++i]; break;
			case 's':UsrParameter.MapSitesNumber = atoi(rgv[++i]); break;
			case 't':UsrParameter.MaxiterTime= atoi(rgv[++i]); break;
			case 'c':UsrParameter.RemoveCutoff = atof(rgv[++i]); break;
			case 'n':UsrParameter.ClassNumber = atoi(rgv[++i]); break;
			default: std::cout << "Parameter " << rgv[i][1] << " is not an effective value . Please check it out." << endl; exit(1);
		}
	}
	return i;
}

void Paramscan(int argc, char *argv[]){
	if(argc==1) print_help();
	int noptions = mGetOptions(argc, argv);
	if(UsrParameter.methylationfile == "" && UsrParameter.configFilepath == ""){
		std::cerr << "fatal error: User do not give the input methylation file or config file.\n";
		exit(1);
	}
	if(UsrParameter.methylationfile != "" && UsrParameter.configFilepath != ""){
		std::cerr << "Warning: User give both the input methylation file and the config file.\n";
		exit(0);
	}
	if(UsrParameter.normalMapfile == ""){
		std::cerr << "fatal error: User do not give the input map file.\n";
		exit(1);
	}
	if(UsrParameter.outputFilepath == ""){
		std::cerr << "fatal error: User do not gice the output file path.\n";
		exit(1);
	}
	if(UsrParameter.methylationfile != ""){
		fin_d.open(UsrParameter.methylationfile.c_str());
		if (!fin_d) {
			std::cerr << "fatal error: failed to open methylation file.\n";
			exit(1);
		}
	}
	std::ifstream fin_d2;
	fin_d2.open(UsrParameter.normalMapfile.c_str());
	if (!fin_d2) {
		std::cerr << "fatal error: failed to open map file.\n";
		exit(1);
	}
	fout.open(UsrParameter.outputFilepath.c_str(),ios::app);
	if (!fout) {
		std::cerr << "failed to open file: " << UsrParameter.outputFilepath << std::endl;
		exit(1);
	}
	/*if(UsrParameter.configFilepath != ""){
		fin_d2.open(UsrParameter.configFilepath.c_str());
		if (!fin_d2) {
			std::cerr << "fatal error: failed to open config file.\n";
			exit(1);
		}
	}*/
	fout.close();
	fin_d.close();
	fin_d2.close();
}

