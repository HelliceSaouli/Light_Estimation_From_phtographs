/*********************************
 *  some basic function and needed
 *  c++ headers
 */

#ifndef UTILITIES_H
#define UTILITIES_H

/************* C ++ 11 headers ****************************/
#include <iostream>
#include <fstream>
#include <ostream>
#include <iterator>
#include <limits>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>

#include "opencv2/opencv.hpp"
#include "glm/glm.hpp"
/************************************* popular constant *************************/

#ifndef PI
# define PI 3.1415926535897932384626433832795                          //The number PI used in math
#endif

#ifndef LOG2
# define LOG2 0.69314718055994530941723212145818                       // The log
#endif

/*************************************************************************************
 *
 *  Include  some usful inline fucntion
 *
 ************************************************************************************/


inline
float DegreeToRad(float Angle)
{
	return (Angle  * ( PI / 180.00));
}

inline
float cotangent(float Angle)
{
	return (1/tan(Angle));
}


inline
unsigned int ParseToInt(const std::string& token, unsigned int start, unsigned int end)
{
    return atoi(token.substr(start, end - start).c_str());
}

inline
float ParseToFloat(const std::string& token, unsigned int start, unsigned int end)
{
    return atof(token.substr(start, end - start).c_str());
}

inline
unsigned int FindNextChar(unsigned int start, const char* str, unsigned int length, char token)
{
    unsigned int result = start;
    while(result < length)
    {
        result++;
        if(str[result] == token)
            break;
    }

    return result;
}

inline
glm::vec3 ParseToVec3(const std::string& line)
{
    unsigned int tokenLength = line.length();
    const char* tokenString = line.c_str();

    unsigned int vertIndexStart = 0;

/*  while(vertIndexStart < tokenLength)
    {
        if(tokenString[vertIndexStart] != ' ')
            break;
        vertIndexStart++;
    }
*/
    unsigned int vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

    float x = ParseToFloat(line, vertIndexStart, vertIndexEnd);

    vertIndexStart = vertIndexEnd + 1;
    vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

    float y = ParseToFloat(line, vertIndexStart, vertIndexEnd);

    vertIndexStart = vertIndexEnd + 1;
    vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

    float z = ParseToFloat(line, vertIndexStart, vertIndexEnd);

    return glm::vec3(x,y,z);

}

inline
cv::Mat  loadImage(std::string filename,int &w,int &h)	// read  image
{
	cv::Mat img;
	img = cv::imread(filename,CV_LOAD_IMAGE_COLOR);    // read the image
    if(! img.data )                              // Check for invalid input
    {
       std::cerr <<  "Could not open or find the image...!!" << std::endl ;
       exit(0);
    }
	h = img.rows;
	w = img.cols;

	std::cout<<w<<" "<<h<<std::endl;
	return img;
}

inline
glm::mat4 LoadMatrixFromFile(const char* path)
{
	glm::mat4 Projection_Matrix;
	glm::mat4 TProjection_Matrix;
	std::ifstream filep(path,std::ifstream::in);

	        //check if file opened
	        if(!filep)
	        {
	           std::cerr << " unable to open file!!!"<<std::endl;
	            exit(EXIT_FAILURE);
	        }
	        for(int i = 0; i < 3 ; i++)
	        {

	            for(int j = 0; j < 4; j++)
	            {
	                filep>>Projection_Matrix[i][j];
	            }
	        }
	        filep.close();

	        Projection_Matrix[3][0] =  0.0;
	        Projection_Matrix[3][1] =  0.0;
	        Projection_Matrix[3][2] =  0.0;
	        Projection_Matrix[3][3] =  1.0;

	        TProjection_Matrix = glm::transpose(Projection_Matrix);
	return TProjection_Matrix;
}

#endif /* UTILITIES_H */
