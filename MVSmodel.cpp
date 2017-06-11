/*
 * MVSmodel.cpp
 *
 *  Created on: Mar 10, 2017
 *      Author: hakosoft
 */

#include "MVSmodel.h"

MVSmodel::MVSmodel(const std::string& filename)	// this will read the patch file and save the needed data into our model class
{
	std::ifstream file;
	file.open((filename).c_str());
	std::string line;

	if(!file.is_open())
	{
		std::cerr << " Enable to read the PMVS-2 patch file: "<<filename<<"...!!"<<std::endl;
		exit (EXIT_FAILURE);
	}

	unsigned int numberoflines = 0;
	while(file.good())
	{
		getline(file,line);
		numberoflines ++;
		unsigned int lineLength = line.length();

		if(lineLength < 1)
			continue;

		const char* lineCStr = line.c_str();

		switch(lineCStr[0])
		{
			case 'P':
					if(lineCStr[lineLength - 2] == 'E' && lineCStr[lineLength - 1] == 'S')	// the line contain the header PATCHES skype it
						break;
					if(lineCStr[lineLength - 2] == 'H' && lineCStr[lineLength - 1] == 'S')	// we are in PATCHS // we take the 2 lines points and normals
					{
						std::string point,normal,dumpData,number_of_camera,visibal;
						vertex patch;

						// read the points
						getline(file,point);
						patch.setPoint(ParseToVec3(point));
						numberoflines++; // we read new line

						// read the normal
						getline(file,normal);
						patch.setNormal(ParseToVec3(normal));
						numberoflines++; // we read new line

						//read the constensy scores and ingore it
						getline(file,dumpData);
						numberoflines++; // we read new line

						//read visibility
						getline(file,number_of_camera);	// just do nothing for the moment
						numberoflines++; // we read new line

						getline(file,visibal);
					    unsigned int visibalLength = visibal.length();
					    const char* visibalString = visibal.c_str();

					    unsigned int IndexStart = 0;
					    unsigned int IndexEnd = FindNextChar(IndexStart, visibalString, visibalLength, ' ');

					    std::vector<unsigned int> visb;
					    while(IndexEnd < visibalLength)
					    {
					    	unsigned int cameraindex = ParseToInt(visibal,IndexStart,IndexEnd);
					    	visb.push_back(cameraindex);
					    	IndexStart = IndexEnd + 1;
					    	IndexEnd = FindNextChar(IndexStart, visibalString, visibalLength, ' ');
					    }

					    patch.setVisibals(visb);

					    this->PMSV_model.push_back(patch);
					}
					break;
			default :
				if(numberoflines == 2) // this mean we are in 2end line which contain an integer that says how many vertex in the file
				{
					unsigned int model_size = ParseToInt(line,0,lineLength);
					this->PMSV_model.reserve(model_size);
				}
				break;
		}


	}

	file.close();
}

MVSmodel::~MVSmodel()
{
	// TODO Auto-generated destructor stub
}

std::vector<vertex> MVSmodel::getNeedPointModel(const unsigned int& view)const
{
	std::vector<vertex> patchs;

	for(int i = 0; i < this->PMSV_model.size(); i++)
	{
		std::vector<unsigned int> vis = this->PMSV_model[i].getVisibility();
		// let's look for view we want it to be our main

		for(int j = 0; j < vis.size(); j++)
		{
			if(vis[j] == view)
			{
				vertex buff = this->PMSV_model[i];
				patchs.push_back(buff);	// this the point i needed which is visbal by my main view
				break;
			}
		}
	}
	return patchs;
}

void MVSmodel::printData(unsigned int N)	// print N number of the data // debuging
{

	for(int i = 0; i < N; i++)
	{
		std::cout<<" Point : " << this->PMSV_model[i].getPoint().x <<", " <<this->PMSV_model[i].getPoint().y<<", "<<this->PMSV_model[i].getPoint().z<<std::endl;
		std::cout<<" Normal : " << this->PMSV_model[i].getNormal().x <<", " <<this->PMSV_model[i].getNormal().y<<", "<<this->PMSV_model[i].getNormal().z<<std::endl;

		std::cout<<"Camera visibal : "<<std::endl;
		std::vector<unsigned int> vib = this->PMSV_model[i].getVisibility();
		for(int j = 0; j < vib.size();j++)
		{
			std::cout<<vib[j]<<std::endl;
		}


		std::cout<<"*******************************************************************************"<<std::endl;
	}
}
