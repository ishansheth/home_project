/*
 * component1.hpp
 *
 *  Created on: Feb 18, 2017
 *      Author: ishan
 */

#ifndef SRC_POSITIONING_POSITIONING_HPP_
#define SRC_POSITIONING_POSITIONING_HPP_

#include "../Idependencymanager/Idependencymanager.hpp"
#include "../interfaces/IPositioning.hpp"
#include "../interfaces/LanguageChangeInterface.hpp"
#include "../interfaces/ilcm.hpp"
#include "../interfaces/IsdkComponent.hpp"
#include "../ComponentDependency/ComponentDependency.hpp"

class LanguageChangeInterface;
class ILCM;

class Positioning:public IPositioning,public LanguageChangeInterface{
	ComponentDependency<ILCM> m_lcm;
	void run(){
		while(1){
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
	std::thread mainLoopthread;
	int i;
public:
	Positioning(Idependencymanager &dp):m_lcm(dp,"positioning",1,1){}
	~Positioning(){
		if(mainLoopthread.joinable())
			mainLoopthread.join();
		}

	virtual void start() override{
		mainLoopthread = std::thread(&Positioning::run,this);
	}
	virtual void component1_method(std::shared_ptr<ILCM> lcm_ptr) override{
		std::cout<<"inside component1 method"<<std::endl;
		lcm_ptr->registerForLanguageChange("Component1",*this);
	}

	virtual void setLanguage(std::string language,std::function<void(std::string)> callbackFunc) override{
		std::cout<<"language set:"<<language<<std::endl;
		callbackFunc("OK");
	}



};

#endif /* SRC_POSITIONING_POSITIONING_HPP_ */
