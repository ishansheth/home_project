/*
 * LCMFactory.hpp
 *
 *  Created on: Sep 23, 2017
 *      Author: ishan
 */

#ifndef SRC_LCM_LCMFACTORY_HPP_
#define SRC_LCM_LCMFACTORY_HPP_

#include <memory>
#include "../interfaces/ilcm.hpp"
#include "../lcm/lcm.hpp"
#include "../Idependencymanager/Idependencymanager.hpp"

class Idependencymanager;
class ILCM;
class LCM;

class LCMFactory
{
public:
	static std::shared_ptr<ILCM> createComponent(Idependencymanager& dp)
	{
		return std::make_shared<LCM>(dp);
	}
};



#endif /* SRC_LCM_LCMFACTORY_HPP_ */
