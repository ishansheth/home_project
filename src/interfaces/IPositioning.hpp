/*
 * icomp1.hpp
 *
 *  Created on: Feb 18, 2017
 *      Author: ishan
 */

#ifndef SRC_INTERFACES_IPOSITIONING_HPP_
#define SRC_INTERFACES_IPOSITIONING_HPP_

#include<memory>
#include "ilcm.hpp"
#include "IsdkComponent.hpp"
class IPositioning:public IsdkComponent{
public:
	virtual void component1_method(std::shared_ptr<ILCM> lcm_ptr)=0;
};






#endif /* SRC_INTERFACES_IPOSITIONING_HPP_ */
