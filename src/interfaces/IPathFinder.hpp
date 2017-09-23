/*
 * icomp2.hpp
 *
 *  Created on: Feb 18, 2017
 *      Author: ishan
 */

#ifndef SRC_INTERFACES_IPATHFINDER_HPP_
#define SRC_INTERFACES_IPATHFINDER_HPP_

#include<memory>
#include "ilcm.hpp"
#include "IsdkComponent.hpp"
class IPathFinder:public IsdkComponent{
public:
	virtual void component2_method(std::shared_ptr<ILCM> lcm_ptr)=0;

};




#endif /* SRC_INTERFACES_IPATHFINDER_HPP_ */
