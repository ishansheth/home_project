/*
 * icomp2.hpp
 *
 *  Created on: Feb 18, 2017
 *      Author: ishan
 */

#ifndef SRC_INTERFACES_ICOMP2_HPP_
#define SRC_INTERFACES_ICOMP2_HPP_

#include<memory>
#include "ilcm.hpp"
class Icomp2{
public:
	virtual void component2_method(std::shared_ptr<ILCM> lcm_ptr)=0;

};




#endif /* SRC_INTERFACES_ICOMP2_HPP_ */
