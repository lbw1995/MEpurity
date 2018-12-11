#include "help.h"

UsrParameters::UsrParameters() {
	methylationfile = "";
	normalMapfile = "";
	outputFilepath = "";
	configFilepath = "";
	ClassNumber = 10;
	RemoveCutoff = 0.01;
	MapSitesNumber = 70000;
	MaxiterTime = 10000;
	verbose = 0;
}

UsrParameters::~UsrParameters(){}	

UsrParameters UsrParameter;


std::ifstream fin_d1,fin_d2,fin_d3;
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
	std::cout << "-h" << "	Show this help message and exit.\n\n";
	std::cout << "		-s" << "	The number of CpG sites that you want to use in the map file.(Default:70000)\n" << endl;
	std::cout << "		-t" << "	The maximum iteration time of bmm algorithm.(Default:10000)\n" << endl;
	std::cout << "		-c" << "	The least percemtage of sites belonging to a cluster that would not be filted.(Default:0.01)\n" << endl;
	std::cout << "		-n" << "	The original number of clusters.(Default:10)\n" << endl;
	std::cout << "		-v" << "	Output progress in terms of mixing coefficient (expected) values if 1.(Default:False)\n" << endl;
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
			case 'v':UsrParameter.verbose = atoi(rgv[++i]); break;
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
		fin_d1.open(UsrParameter.methylationfile.c_str());
		if (!fin_d1) {
			std::cerr << "fatal error: failed to open methylation file.\n";
			exit(1);
		}
	}
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
	if(UsrParameter.configFilepath != ""){
		fin_d3.open(UsrParameter.configFilepath.c_str());
		if (!fin_d3) {
			std::cerr << "fatal error: failed to open config file.\n";
			exit(1);
		}
	}
	fout.close();
	fin_d1.close();
	fin_d2.close();
	fin_d3.close();
	if (UsrParameter.MapSitesNumber < 40000){
		std::cerr << "error: map sites number must not less than 40000.\n";
		exit(1);
	}
	if (UsrParameter.MaxiterTime < 0){
		std::cerr << "error: the number of iterations must be a positive integer.\n";
		exit(1);
	}
	if (UsrParameter.ClassNumber < 0){
		std::cerr << "error: the number of class number must be a positive integer.\n";
		exit(1);
	}
	if (UsrParameter.RemoveCutoff < 0 || UsrParameter.RemoveCutoff > 1){
		std::cerr << "error: the cut off must be larger than 0 and smaller than 1.\n";
		exit(1);
	}
	if (UsrParameter.verbose != 0 && UsrParameter.verbose != 1){
		std::cerr << "error: the verbose must be 0 or 1.\n";
		exit(1);
	}
}

