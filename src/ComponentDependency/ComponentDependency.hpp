/*
 * ComponentDependency.hpp
 *
 *  Created on: Feb 18, 2017
 *      Author: ishan
 */

#ifndef SRC_COMPONENTDEPENDENCY_COMPONENTDEPENDENCY_HPP_
#define SRC_COMPONENTDEPENDENCY_COMPONENTDEPENDENCY_HPP_


#include<memory>
#include "../Idependencymanager/Idependencymanager.hpp"

class Idependencymanager;

class ComponentDependencyBase{
public:
	ComponentDependencyBase(Idependencymanager &dp){
		dp.dependencyMethod(this);
	}
};


template<typename Interface>
class ComponentDependency:public ComponentDependencyBase{
	std::shared_ptr<Interface> interface;
public:
	ComponentDependency(Idependencymanager &dp):ComponentDependencyBase(dp){
//		interface = std::dynamic_pointer_cast<Interface>(dp);


	}
	std::shared_ptr<Interface> get(){
		return interface;
	}


};



#endif /* SRC_COMPONENTDEPENDENCY_COMPONENTDEPENDENCY_HPP_ */
