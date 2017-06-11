/*
 * SphericalHarmonic.h
 *
 * Copyright (c) 2017, Saouli Abdelhak
 * Mohammed Khder biskra university - Laboratoire de Recherche des Systèmes Experts, Imagerie et leurs Applications dans l’ingénierie
 * All rights reserved.
 *
 * https://en.wikipedia.org/wiki/Table_of_spherical_harmonics#Real_spherical_harmonics
 */

#ifndef SPHERICALHARMONIC_H_
#define SPHERICALHARMONIC_H_

#include "utilities.h"

class SphericalHarmonic
{
	private:
		float *m_SH_basis;	// this is the Y0_0......Y3_3

	public:
		SphericalHarmonic();
		virtual ~SphericalHarmonic();

		float* getBasis()const; //return the evaluated basis

		void  evaluate_4_band(const glm::vec3&);	// evaluate for each vertex normal 4 band the l start from 0 and at 3
};

#endif /* SPHERICALHARMONIC_H_ */
