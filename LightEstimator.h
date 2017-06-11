/*
 * LightEstimator.h
 *
 *  Copyright (c) 2017, Saouli Abdelhak
 * Mohammed Khder biskra university - Laboratoire de Recherche des Systèmes Experts, Imagerie et leurs Applications dans l’ingénierie
 * All rights reserved.
 *
 *
 */

#ifndef LIGHTESTIMATOR_H_
#define LIGHTESTIMATOR_H_

#include "utilities.h"
#include "SphericalHarmonic.h"
#include "MVSmodel.h"
#include "View.h"

#include <Eigen/Dense> // use some algebra libs
class LightEstimator
{
	private:
		glm::vec3 m_light_Param[16];		// the 16 light paramaters for each color

		Eigen::MatrixXf m_A;	// matrix  A for solving the linear least square size of A is M x N  where M = number of vertcies N = rank of SH

		Eigen::VectorXf m_b_r;	// vector  b for solving the linear least square M x 1
		Eigen::VectorXf m_b_g;	// vector  b for solving the linear least square M x 1
		Eigen::VectorXf m_b_b;	// vector  b for solving the linear least square M x 1



	public:
		LightEstimator();
		virtual ~LightEstimator();

		void constructMatrixA(const MVSmodel&);
		void construcVector_b_red(const View&,const MVSmodel&);
		void construcVector_b_green(const View&,const MVSmodel&);
		void construcVector_b_blue(const View&,const MVSmodel&);

		void Estimate();
		glm::vec3* getParam();
		void saveToFile();

};

#endif /* LIGHTESTIMATOR_H_ */
