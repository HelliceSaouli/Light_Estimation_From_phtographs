/*
 * View.h
 *
 * Copyright (c) 2017, Saouli Abdelhak
 * Mohammed Khder biskra university - Laboratoire de Recherche des Systèmes Experts, Imagerie et leurs Applications dans l’ingénierie
 * All rights reserved.
 */

#ifndef VIEW_H_
#define VIEW_H_

#include "utilities.h"
#include "glm/glm.hpp"

class View
{
	private:
		cv::Mat m_image;		// the main view data it is RGB image
		int w,h;
	//	unsigned char* m_gradien;
		glm::mat4  m_projection;

	public:
		View(const std::string&,const std::string&);	// collect data from source files
		virtual ~View();

		//given a 3D position project it to the image and return the needed value since the point is consistent to view   the projection shoud never be out of boundry
		unsigned char redIntensity(const glm::vec3&)const;
		unsigned char greenIntensity(const glm::vec3&)const;
		unsigned char blueIntensity(const glm::vec3&)const;

		glm::vec3 getCameraPosition(unsigned int)const;
};

#endif /* VIEW_H_ */
