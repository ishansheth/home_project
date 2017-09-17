/*
 * component1.hpp
 *
 *  Created on: Feb 18, 2017
 *      Author: ishan
 */

#ifndef SRC_COMPONENT1_COMPONENT1_HPP_
#define SRC_COMPONENT1_COMPONENT1_HPP_

#include "../Idependencymanager/Idependencymanager.hpp"
#include "../interfaces/icomp1.hpp"
#include "../interfaces/LanguageChangeInterface.hpp"
#include "../interfaces/ilcm.hpp"
#include "../interfaces/IsdkComponent.hpp"
#include "../ComponentDependency/ComponentDependency.hpp"

class LanguageChangeInterface;
class ILCM;

class Component1:public Icomp1,public IsdkComponent,public LanguageChangeInterface{
	ComponentDependency<ILCM> m_lcm;
	void run(){
		while(1){
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
	std::thread mainLoopthread;
	int i;
public:
	Component1(Idependencymanager &dp):m_lcm(dp){}
	~Component1(){
		if(mainLoopthread.joinable())
			mainLoopthread.join();
		}

	virtual void start() override{
		mainLoopthread = std::thread(&Component1::run,this);
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

#endif /* SRC_COMPONENT1_COMPONENT1_HPP_ */
