/*
 * ComponentDependency.hpp
 *
 *  Created on: Feb 18, 2017
 *      Author: ishan
 */

#ifndef SRC_COMPONENTDEPENDENCY_COMPONENTDEPENDENCY_HPP_
#define SRC_COMPONENTDEPENDENCY_COMPONENTDEPENDENCY_HPP_
#include<memory>
#include<string>
#include "../Idependencymanager/Idependencymanager.hpp"

class Idependencymanager;

class ComponentDependencyBase{
	int m_major;
	int m_minor;
	std::string m_name;
public:
	ComponentDependencyBase(Idependencymanager &dp,std::string name,int major,int minor):
		m_major(major),m_minor(minor),m_name(name)
	{
		dp.dependencyMethod(this);
	}
};


template<typename Interface>
class ComponentDependency:public ComponentDependencyBase{
	std::shared_ptr<Interface> interface;
public:
	ComponentDependency(Idependencymanager &dp,std::string name,int major,int minor)
		:ComponentDependencyBase(dp,name,major,minor){
//		interface = std::dynamic_pointer_cast<Interface>(dp);

	}
	std::shared_ptr<Interface> get(){
		return interface;
	}


};



#endif /* SRC_COMPONENTDEPENDENCY_COMPONENTDEPENDENCY_HPP_ */
