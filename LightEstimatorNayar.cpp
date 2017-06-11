/*
 * LightEstimatorNayar.cpp
 *
 *  Created on: Mar 19, 2017
 *      Author: hakosoft
 */

#include "LightEstimatorNayar.h"

LightEstimatorNayar::LightEstimatorNayar()
{
	// TODO Auto-generated constructor stub

}

LightEstimatorNayar::~LightEstimatorNayar()
{
	// TODO Auto-generated destructor stub
}


void LightEstimatorNayar::setRougthness(float rough)
{
	this->roughness = rough;
}

float LightEstimatorNayar::ComputeCosTheta(const glm::vec3& pos,const glm::vec3& normal,const View &img)
{

	//compute view direction which is equal to light direction
	glm::vec3 CamraPos = img.getCameraPosition(30);
	glm::vec3 light_dir = glm::normalize(pos - CamraPos);

	return glm::dot(light_dir,normal);// mybe i should take max(0,costheta) ?
}

float LightEstimatorNayar::Fcostheta(float costheta, float A, float B)
{
	float cosSquare = costheta * costheta;
	return (1.0 / PI) * ( (A * costheta) + (B *(1- cosSquare) ));
}

void LightEstimatorNayar::constructMatrixA(const MVSmodel& model,const View &img)
{
	float roughsquare = this->roughness * this->roughness;

	float A = 1.0 - 0.5 * (roughsquare / (roughsquare + 0.57));
	float B = 0.45 * (roughsquare / (roughsquare + 0.09));

	std::vector<vertex> Patchs = model.getNeedPointModel(30);
	unsigned int A_rows = Patchs.size();
	std::cout<<"nmbr of point "<<A_rows<<std::endl;
	unsigned int A_cols = 1;

	this->m_A.resize(A_rows,A_cols);

	for(unsigned int row = 0; row < A_rows; row++)
	{
		glm::vec3 normal = glm::normalize(Patchs[row].getNormal());
		glm::vec3 pos	=  Patchs[row].getPoint();

		Eigen::VectorXf H(A_cols);

		for(unsigned int col = 0; col < A_cols; col++)
		{
			float CosTheta = ComputeCosTheta(pos,normal,img);
			H(col) = Fcostheta(CosTheta,A,B);

		}
		this->m_A.row(row) = H;
	}
}

void LightEstimatorNayar::construcVector_b_all(const View& image,const MVSmodel& model)
{
	// i will set the view manually here which is thirst view 30 remmber
	std::vector<vertex> Patchs = model.getNeedPointModel(30);
	unsigned int A_rows = Patchs.size();

	this->m_b_r.resize(A_rows);
	this->m_b_g.resize(A_rows);
	this->m_b_b.resize(A_rows);

	for(int row = 0; row < A_rows; row++)
	{
		glm::vec3 point = Patchs[row].getPoint();

		float red = (float)image.redIntensity(point) / 255.0;
		float green = (float)image.greenIntensity(point) / 255.0;
		float blue = (float)image.blueIntensity(point) / 255.0;

		this->m_b_r[row] = red ;
		this->m_b_g[row] = green ;
		this->m_b_b[row] = blue ;
	}
}

void LightEstimatorNayar::Estimate()
{
	Eigen::MatrixXf A_transpose = this->m_A.transpose();

	Eigen::MatrixXf Alpha = A_transpose * this->m_A;	// this is the matrice [A(transpose).A]

	Eigen::VectorXf Betar  = A_transpose * this->m_b_r;	// this is [A(transpose).b] not that we are solving for every chanal RGB
	Eigen::VectorXf Betag  = A_transpose * this->m_b_g;
	Eigen::VectorXf Betab  = A_transpose * this->m_b_b;

	this->m_light_param.x = Betar(0) / Alpha(0,0);
	this->m_light_param.y = Betag(0) / Alpha(0,0);
	this->m_light_param.z = Betab(0) / Alpha(0,0);
}

glm::vec3 LightEstimatorNayar::getParam()const
{
	return this->m_light_param;
}
