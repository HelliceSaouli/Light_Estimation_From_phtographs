/*
 * SphericalHarmonic.cpp
 *
 *  Created on: Mar 10, 2017
 *      Author: hakosoft
 */

#include "SphericalHarmonic.h"

SphericalHarmonic::SphericalHarmonic()
{
	this->m_SH_basis = new float[16];
}

SphericalHarmonic::~SphericalHarmonic()
{
	// TODO Auto-generated destructor stub
}


void SphericalHarmonic::evaluate_4_band(const glm::vec3 &normal)
{

	/*Y0_0*/   this->m_SH_basis[0] = (1.0 / 2.0)  * sqrt(1.0/ PI);
	/*Y1_-1*/  this->m_SH_basis[1] = sqrt(3.0 / (4.0 * PI)) * normal.y;
	/*Y1_0*/   this->m_SH_basis[2] = sqrt(3.0 / (4.0 * PI)) * normal.z;
	/*Y1_1*/   this->m_SH_basis[3] = sqrt(3.0 / (4.0 * PI)) * normal.x;

	/*Y2_-2*/ this->m_SH_basis[4] = (1.0 / 2.0)  * sqrt(15.0/ PI) * normal.x * normal.y;
	/*Y2_-1*/ this->m_SH_basis[5] = (1.0 / 2.0)  * sqrt(15.0/ PI) * normal.y * normal.z;
	/*Y2_0*/  this->m_SH_basis[6] = (1.0 / 4.0)  * sqrt(5.0/ PI) * (-pow(normal.x,2.0) - pow(normal.y,2.0) + ( 2 * pow(normal.z,2.0) ));
	/*Y2_1*/  this->m_SH_basis[7] = (1.0 / 2.0)  * sqrt(15.0/ PI) * normal.z * normal.x;
	/*Y2_2*/  this->m_SH_basis[8] = (1.0 / 4.0)  * sqrt(15.0/ PI) * (pow(normal.x,2.0) - pow(normal.y,2.0));

	/*Y3_-3*/ this->m_SH_basis[9]  = (1.0 / 4.0)  * sqrt(35.0/ ( 2.0 * PI)) * ((3.0 * pow(normal.x,2.0)) - pow(normal.y,2.0)) * normal.y;
	/*Y3_-2*/ this->m_SH_basis[10] = (1.0 / 2.0)  * sqrt(105.0/ PI) * normal.x * normal.y * normal.z;
	/*Y3_-1*/ this->m_SH_basis[11] = (1.0 / 4.0)  * sqrt(21.0/ ( 2.0 * PI)) * (-pow(normal.x,2.0) - pow(normal.y,2.0) + ( 4 * pow(normal.z,2.0) )) * normal.y;
	/*Y3_0*/  this->m_SH_basis[12] = (1.0 / 4.0)  * sqrt(7.0/ PI) * ((- 3.0 * pow(normal.x,2.0)) - (3.0 * pow(normal.y,2.0)) + ( 2 * pow(normal.z,2.0) )) * normal.z;
	/*Y3_1*/  this->m_SH_basis[13] = (1.0 / 4.0)  * sqrt(21.0/ ( 2.0 * PI)) * (-pow(normal.x,2.0) - pow(normal.y,2.0) + ( 4 * pow(normal.z,2.0) )) * normal.x;
	/*Y3_2*/  this->m_SH_basis[14] = (1.0 / 4.0)  * sqrt(105.0/ PI) *  (pow(normal.x,2.0) - pow(normal.y,2.0)) * normal.z;
	/*Y3_3*/  this->m_SH_basis[15] = (1.0 / 4.0)  * sqrt(35.0/ ( 2.0 * PI)) * ( pow(normal.x,2.0) -(3.0 * pow(normal.y,2.0))) * normal.x;

}

float* SphericalHarmonic::getBasis()const
{
	return this->m_SH_basis;
}
