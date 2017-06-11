/*
 * LightEstimatorNayar.h
 *
 *  Copyright (c) 2017, Saouli Abdelhak
 * 	Mohammed Khder biskra university - Laboratoire de Recherche des Systèmes Experts, Imagerie et leurs Applications dans l’ingénierie
 * 	All rights reserved.
 */

#ifndef LIGHTESTIMATORNAYAR_H_
#define LIGHTESTIMATORNAYAR_H_

#include "utilities.h"
#include "SphericalHarmonic.h"
#include "MVSmodel.h"
#include "View.h"

#include <Eigen/Dense> // use some algebra libs
class LightEstimatorNayar
{

	private:

		glm::vec3 m_light_param;	// this is what need to estimate
		float roughness;	// constant given

		Eigen::MatrixXf m_A;	// matrix to solve the estimation problm
		Eigen::VectorXf m_b_r;
		Eigen::VectorXf m_b_g;
		Eigen::VectorXf m_b_b;
		float ComputeCosTheta(const glm::vec3&,const glm::vec3&, const View&);	//it's the dot product betewen normal and view direction
		float Fcostheta(float,float,float); //compute the function F for each vertex to fill matrice A

	public:
		LightEstimatorNayar();
		virtual ~LightEstimatorNayar();

		void setRougthness(float);
		void constructMatrixA(const MVSmodel&,const View &);
		void construcVector_b_all(const View&,const MVSmodel&); // i was solving for  gray but know i solve for all rgb


		void Estimate();
		glm::vec3 getParam()const;
};

#endif /* LIGHTESTIMATORNAYAR_H_ */
