#include "MVSmodel.h"
#include "View.h"
#include "LightEstimator.h"
#include "LightEstimatorNayar.h"
#include "utilities.h"
// lol use this to solve some algabra shit #include <Eigen/Dense>

int main()
{
	MVSmodel model("Model/option-highres.txt.patch");
	View image1("images/visualize/30.png","images/projection/30.txt");

	LightEstimator param;
	LightEstimatorNayar ParamNayar;

	std::cout<<"Lambertian Light estimation"<<std::endl;
	param.constructMatrixA(model);
	std::cout<<"matrix constraction done"<<std::endl;
	param.construcVector_b_red(image1,model);
	param.construcVector_b_green(image1,model);
	param.construcVector_b_blue(image1,model);


	std::cout<<"vector  constraction done"<<std::endl;

	param.Estimate();
	std::cout<<"Estimation  done"<<std::endl;
	glm::vec3* light = param.getParam();

	for(int i = 0; i < 16; i++)
		std::cout <<"R = "<<light[i].x<<" / G = "<<light[i].y<<" / B ="<<light[i].z<<std::endl;

	std::cout<<"save to file  done"<<std::endl;
	param.saveToFile();

	std::cout<<"**********************************************************************************"<<std::endl;
	std::cout<<"Nayar Light estimation"<<std::endl;
	ParamNayar.setRougthness(0.5);
	ParamNayar.constructMatrixA(model,image1);
	std::cout<<"matrix constraction done"<<std::endl;
	ParamNayar.construcVector_b_all(image1,model);
	std::cout<<"vector  constraction done"<<std::endl;
	ParamNayar.Estimate();
	std::cout<<"Estimation  done"<<std::endl;
	glm::vec3 light_nayar = ParamNayar.getParam();

	std::cout<< "light param nayar is  R:"<<light_nayar.x<<std::endl;
	std::cout<< "light param nayar is  G:"<<light_nayar.y<<std::endl;
	std::cout<< "light param nayar is  B:"<<light_nayar.z<<std::endl;
	//model.printData(10);	// debuging ...it's working fine am extracting correct data

	//std::vector<vertex> Data = model.getNeedPointModel(0); // this is working exctracting correct points

	/*for(int i = 0; i < Data.size(); i++)
	{
		std::cout<<" Point : " << Data[i].getPoint().x <<", " <<Data[i].getPoint().y<<", "<<Data[i].getPoint().z<<std::endl;
		std::cout<<" Normal : " << Data[i].getNormal().x <<", " <<Data[i].getNormal().y<<", "<<Data[i].getNormal().z<<std::endl;

		std::cout<<"Camera visibal : "<<std::endl;
		std::vector<unsigned int> vib = Data[i].getVisibility();
		for(int j = 0; j < vib.size();j++)
		{
			std::cout<<vib[j]<<std::endl;
		}


		std::cout<<"*******************************************************************************"<<std::endl;
	}
	*/
	return 0;
}
