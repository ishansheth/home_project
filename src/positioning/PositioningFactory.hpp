/*
 * PositioningFactory.hpp
 *
 *  Created on: Sep 23, 2017
 *      Author: ishan
 */

#ifndef SRC_POSITIONING_POSITIONINGFACTORY_HPP_
#define SRC_POSITIONING_POSITIONINGFACTORY_HPP_

#include <memory>
#include "../interfaces/IPositioning.hpp"
#include "../positioning/positioning.hpp"
#include "../Idependencymanager/Idependencymanager.hpp"

class Idependencymanager;
class Positioning;
class IPositioning;

class PositioningFactory
{
public:
	static std::shared_ptr<IPositioning> createComponent(Idependencymanager& dp)
	{
		return std::make_shared<Positioning>(dp);
	}
};




#endif /* SRC_POSITIONING_POSITIONINGFACTORY_HPP_ */
