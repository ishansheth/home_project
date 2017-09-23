/*
 * PathfinderFactory.hpp
 *
 *  Created on: Sep 23, 2017
 *      Author: ishan
 */

#ifndef SRC_PATHFINDER_PATHFINDERFACTORY_HPP_
#define SRC_PATHFINDER_PATHFINDERFACTORY_HPP_

#include <memory>
#include "../interfaces/IPathFinder.hpp"
#include "../pathfinder/pathfinder.hpp"
#include "../Idependencymanager/Idependencymanager.hpp"

class Idependencymanager;
class PathFinder;
class IPathFinder;

class PathFinderFactory
{
public:
	static std::shared_ptr<IPathFinder> createComponent(Idependencymanager& dp)
	{
		return std::make_shared<PathFinder>(dp);
	}
};


#endif /* SRC_PATHFINDER_PATHFINDERFACTORY_HPP_ */
