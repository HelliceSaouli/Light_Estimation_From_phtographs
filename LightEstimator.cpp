/*
 * LightEstimator.cpp
 *
 *  Created on: Mar 11, 2017
 *      Author: hakosoft
 */

#include "LightEstimator.h"

LightEstimator::LightEstimator()
{
	// TODO Auto-generated constructor stub

}

LightEstimator::~LightEstimator()
{
	// TODO Auto-generated destructor stub
}

void LightEstimator::constructMatrixA(const MVSmodel& model)
{
	// i will set the view manually here which is thirst view 0 remmber
	std::vector<vertex> Patchs = model.getNeedPointModel(30);
	unsigned int A_rows = Patchs.size();
	std::cout<<"nmbr of point "<<A_rows<<std::endl;
	unsigned int A_cols = 16;	// rank 4 of SH

	// spherical harmonic will give for each patch withh give us a row of matrice
	this->m_A.resize(A_rows,A_cols);
	for(unsigned int row = 0; row < A_rows; row++)
	{
		glm::vec3 normal = glm::normalize(Patchs[row].getNormal());
		SphericalHarmonic Sh;
		Sh.evaluate_4_band(normal);
		float *basis = Sh.getBasis();

		Eigen::VectorXf H(A_cols);	// named H according to : Shading-based Refinement on Volumetric Signed Distance Functions

		for(unsigned int col = 0; col < A_cols; col++)
		{
			H(col) = basis[col];

		}
		this->m_A.row(row) = H;
	}
}

void LightEstimator::construcVector_b_red(const View& image,const MVSmodel& model)
{
	// i will set the view manually here which is thirst view 30 remmber
	std::vector<vertex> Patchs = model.getNeedPointModel(30);
	unsigned int A_rows = Patchs.size();

	this->m_b_r.resize(A_rows);
	for(int row = 0; row < A_rows; row++)
	{
		glm::vec3 point = Patchs[row].getPoint();
		float red = (float)image.redIntensity(point) / 255.0;
		this->m_b_r(row) = red;
	}
}

void LightEstimator::construcVector_b_green(const View& image,const MVSmodel& model)
{
	// i will set the view manually here which is thirst view 30 remmber
	std::vector<vertex> Patchs = model.getNeedPointModel(30);
	unsigned int A_rows = Patchs.size();
	this->m_b_g.resize(A_rows);
	for(unsigned int row = 0; row < A_rows; row++)
	{
		glm::vec3 point = Patchs[row].getPoint();
		float green = (float)image.greenIntensity(point) / 255.0;
		this->m_b_g(row) = green;
	}
}

void LightEstimator::construcVector_b_blue(const View& image,const MVSmodel& model)
{
	// i will set the view manually here which is thirst view 30 remmber
	std::vector<vertex> Patchs = model.getNeedPointModel(30);
	unsigned int A_rows = Patchs.size();
	this->m_b_b.resize(A_rows);
	for(unsigned int row = 0; row < A_rows; row++)
	{
		glm::vec3 point = Patchs[row].getPoint();
		float blue = (float)image.blueIntensity(point) / 255.0;
		this->m_b_b(row) = blue;
	}
}

void LightEstimator::Estimate()	// we are estimating the light by finding the least square solution [A(transpose).A].l = [A(transpose).b]
{

	Eigen::MatrixXf A_transpose = this->m_A.transpose();

	Eigen::MatrixXf Alpha = A_transpose * this->m_A;	// this is the matrice [A(transpose).A]

	Eigen::VectorXf Beta_red  = A_transpose * this->m_b_r;	// this is [A(transpose).b] not that we are solving for every chanal RGB
	Eigen::VectorXf Beta_green  = A_transpose * this->m_b_g;
	Eigen::VectorXf Beta_blue  = A_transpose * this->m_b_b;

	//compute the psodo inverse of Alpha using SVD
	Eigen::JacobiSVD<Eigen::MatrixXf> svd(Alpha, Eigen::ComputeFullU | Eigen::ComputeFullV);

	/*
	 *  Eigen::MatrixXf U = svd.matrixU();
	 *	Eigen::MatrixXf V = svd.matrixV();
	 *  Eigen::MatrixXf Sigma = svd.singularValues();
	 */

	// let's solve using svd

	Eigen::VectorXf ligh_param_red = svd.solve(Beta_red);
	Eigen::VectorXf ligh_param_green = svd.solve(Beta_green);
	Eigen::VectorXf ligh_param_blue = svd.solve(Beta_blue);

	/************************************************************************/

	for(int i = 0; i < 16; i++)
	{
		glm::vec3 damp;
		damp.x = ligh_param_red(i);
		damp.y = ligh_param_green(i);
		damp.z = ligh_param_blue(i);

		this->m_light_Param[i] = damp;
	}
}


glm::vec3* LightEstimator::getParam()
{
	return this->m_light_Param;
}

void LightEstimator::saveToFile()
{
	std::ofstream file("/home/hakosoft/cuda-workspaceTow/Lighting_from_photographs/resources/LightParam.txt",std::ofstream::out);

	if(file.is_open())
	{
		for(int i = 0; i < 16;i++)
		{
			file<<this->m_light_Param[i].x<<" "<<this->m_light_Param[i].y<<" "<<this->m_light_Param[i].z<<std::endl;
		}
	}

	file.close();
}
