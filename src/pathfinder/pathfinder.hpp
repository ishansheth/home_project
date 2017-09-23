/*
 * component2.hpp
 *
 *  Created on: Feb 18, 2017
 *      Author: ishan
 */

#ifndef SRC_PATHFINDER_PATHFINDER_HPP_
#define SRC_PATHFINDER_PATHFINDER_HPP_

#include "../Idependencymanager/Idependencymanager.hpp"
#include "../interfaces/IPathFinder.hpp"
#include "../interfaces/ilcm.hpp"
#include "../interfaces/LanguageChangeInterface.hpp"
#include "../ComponentDependency/ComponentDependency.hpp"
class ILCM;
class LanguageChangeInterface;

class PathFinder:public IPathFinder,public LanguageChangeInterface{
	std::thread mainLoopthread;
	ComponentDependency<ILCM> m_lcm;
	void run(){
			while(1){
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		}
public:
	PathFinder(Idependencymanager &dp):m_lcm(dp,"pathfinder",1,1){}
	~PathFinder(){
		if(mainLoopthread.joinable())
					mainLoopthread.join();
	}

	virtual void start() override{
		mainLoopthread = std::thread(&PathFinder::run,this);
	}

	virtual void component2_method(std::shared_ptr<ILCM> lcm_ptr) override{
		std::cout<<"inside component2 method"<<std::endl;
				lcm_ptr->registerForLanguageChange("Component2",*this);

	}
	virtual void setLanguage(std::string language,std::function<void(std::string)> callbackFunc) override{
		std::cout<<"language set:"<<language<<std::endl;
		callbackFunc("OK");

	}

};




#endif /* SRC_PATHFINDER_PATHFINDER_HPP_ */
