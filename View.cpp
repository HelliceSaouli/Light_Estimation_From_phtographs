/*
 * View.cpp
 *
 *  Created on: Mar 13, 2017
 *      Author: hakosoft
 */

#include "View.h"

View::View(const std::string& imageFileName,const std::string& ProjectionMatrixFileName)
{

	this->m_image = loadImage(imageFileName.c_str(),this->w,this->h);	// load image shoud add some checks if somethig goes wrong
	this->m_projection = LoadMatrixFromFile(ProjectionMatrixFileName.c_str());

}

View::~View()
{

}

unsigned char View::redIntensity(const glm::vec3& position)const
{
	glm::vec4 positionHomogenous = glm::vec4(position,1.0);
	glm::vec4 projected = this->m_projection * positionHomogenous;

	projected /= projected.z;

	int u = (int)projected.x;
	int v = (int)projected.y;
	cv::Vec3b intensity = this->m_image.at<cv::Vec3b>(v,u);
	//std::cout<<"u = "<<u<<" v = "<<v<<" R1 = "<<(unsigned int)intensity.val[2] <<std::endl;
	return intensity.val[2];
}

unsigned char View::greenIntensity(const glm::vec3& position)const
{
	glm::vec4 positionHomogenous = glm::vec4(position,1.0);
	glm::vec4 projected = this->m_projection * positionHomogenous;

	projected /= projected.z;

	int u = (int)projected.x;
	int v = (int)projected.y;
	cv::Vec3b intensity = this->m_image.at<cv::Vec3b>(v,u);
	return intensity.val[1];
}

unsigned char View::blueIntensity(const glm::vec3& position)const
{
	glm::vec4 positionHomogenous = glm::vec4(position,1.0);
	glm::vec4 projected = this->m_projection * positionHomogenous;

	projected /= projected.z;

	int u = (int)projected.x;
	int v = (int)projected.y;
	cv::Vec3b intensity = this->m_image.at<cv::Vec3b>(v,u);
	return intensity.val[0];
}

glm::vec3 View::getCameraPosition(unsigned int ID)const
{
	glm::vec3 pos;

	std::ifstream filep("images/CameraPosition.txt",std::ifstream::in);

		        //check if file opened
		        if(!filep)
		        {
		           std::cerr << " unable to open file!!!"<<std::endl;
		            exit(EXIT_FAILURE);
		        }

		        int idx = -1;
		        while(filep.is_open())
		        {

					filep>>pos.x;
					filep>>pos.y;
					filep>>pos.z;
					idx++;

					if(idx == ID)
						break;
		        }
		        filep.close();

		        return pos;
}
