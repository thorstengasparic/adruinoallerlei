/*
 * MathVector.h
 *
 * Created: 11.03.2018 15:40:51
 *  Author: gat
 */ 


#ifndef MATHVECTOR_H_
#define MATHVECTOR_H_
#include "Arduino.h"

class MpuVector
{
	public:
		double x;
		double y;
		double z;
		
		double absolut()
		{
			return sqrt(x*x + y*y + z*z);  
		}
		double pitch()
		{
			return asin((double)y/absolut())* 57.296;       
		}
		double roll()
		{
			return asin((double)x/absolut())* 57.296;       
		}
		
		double skalarprodukt(MpuVector b)
		{
			return x*b.x + y*b.y + z*b.z;
		}
		
		double angle( MpuVector b)
		{
			return acos(skalarprodukt(b) / (absolut() * b.absolut())) * 57.296;
			
		}
};



#endif /* MATHVECTOR_H_ */