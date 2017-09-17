/*
 * Idependencymanager.hpp
 *
 *  Created on: Feb 18, 2017
 *      Author: ishan
 */

#ifndef SRC_IDEPENDENCYMANAGER_IDEPENDENCYMANAGER_HPP_
#define SRC_IDEPENDENCYMANAGER_IDEPENDENCYMANAGER_HPP_

#include "../ComponentDependency/ComponentDependencyBase.hpp"

class ComponentDependencyBase;

class Idependencymanager{
public:
	virtual void dependencyMethod(ComponentDependencyBase*)=0;
};


#endif /* SRC_IDEPENDENCYMANAGER_IDEPENDENCYMANAGER_HPP_ */
