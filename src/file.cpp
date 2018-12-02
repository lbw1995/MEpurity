#include "bmm.h"
#include "help.h"
#include "kmeans.h"
#include "file.h"
using namespace std;

extern UsrParameters UsrParameter;




int main(int argc, char* argv[]) {
	Paramscan(argc, argv);
	map<std::string, std::vector<float> > sites_mean;
	load_mean_vir_and_site(UsrParameter.normalMapfile.c_str(), sites_mean, UsrParameter.MapSitesNumber);
	std::ofstream outputt(UsrParameter.outputFilepath.c_str(), ios::app);
	if(UsrParameter.methylationfile != ""){
		std::map<string, float> dif_map;
		cmp_methylation(UsrParameter.methylationfile.c_str(), sites_mean, dif_map);
		std::vector<float> my_data = generate_input_data(dif_map);
		int data_size = my_data.size();
		float purity = calculate_purity(my_data, UsrParameter);
		outputt << UsrParameter.methylationfile << '\t' << purity << endl;
	}
	else if(UsrParameter.configFilepath != ""){
		std::vector<string> file_names = read_file_names(UsrParameter.configFilepath.c_str());
		for(int i = 0; i < file_names.size(); i++){
			std::map<string, float> dif_map;
			cmp_methylation(file_names[i].c_str(), sites_mean, dif_map);
			std::vector<float> my_data = generate_input_data(dif_map);
			int data_size = my_data.size();
			float purity = calculate_purity(my_data, UsrParameter);
			outputt <<file_names[i] << '\t' << purity << endl;
		}
	}
	outputt.close();
	return 0;
}