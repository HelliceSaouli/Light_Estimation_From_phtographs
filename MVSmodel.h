/*
 * MVSmodel.h
 *
 * Copyright (c) 2017, Saouli Abdelhak
 * Mohammed Khder biskra university - Laboratoire de Recherche des Systèmes Experts, Imagerie et leurs Applications dans l’ingénierie
 * All rights reserved.
 */

#ifndef MVSMODEL_H_
#define MVSMODEL_H_

#include "utilities.h"

#include "glm/glm.hpp"

class vertex
{
	private:
		glm::vec3 m_point;	// point from model created by PMVS-2
		glm::vec3 m_normal; // estimated normal created from PMVS-2
		std::vector<unsigned int> m_visibal;	// list of camera which this vertex is consistent and visbal


	public:
	vertex(){
			}

		/*************** setters *****************/
		void setPoint(const glm::vec3 &point)	// set the point which will read from patch file  that we calculated using PMVS-2
		{
			this->m_point = point;
		}

		void setNormal(const glm::vec3 &normal)
		{
			this->m_normal = normal;
		}

		void setVisibals(const std::vector<unsigned int>& visb)
		{
			this->m_visibal = visb;
		}

		/********************** getter ************************/

		glm::vec3 getPoint()const
		{
			return this->m_point;
		}

		glm::vec3 getNormal()const
		{
			return this->m_normal;
		}

		std::vector<unsigned int> getVisibility()const
		{
			return this->m_visibal;
		}
};
class MVSmodel
{
	private:
		std::vector<vertex> PMSV_model;

	public:
		MVSmodel(const std::string&);
		virtual ~MVSmodel();

		//debug
		void printData(unsigned int);

		std::vector<vertex> getNeedPointModel(const unsigned int&)const; // this will return all the point and their normals which
																	// they are all agree and visibal into a given view
																	// if i say getNeedPointModel(10) this will return all the
																	// the point that they are visbal in view 10

};

#endif /* MVSMODEL_H_ */
