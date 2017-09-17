/*
 * component2.hpp
 *
 *  Created on: Feb 18, 2017
 *      Author: ishan
 */

#ifndef SRC_COMPONENT2_COMPONENT2_HPP_
#define SRC_COMPONENT2_COMPONENT2_HPP_

#include "../Idependencymanager/Idependencymanager.hpp"
#include "../interfaces/icomp2.hpp"
#include "../interfaces/ilcm.hpp"
#include "../interfaces/LanguageChangeInterface.hpp"
#include "../ComponentDependency/ComponentDependency.hpp"
class ILCM;
class LanguageChangeInterface;

class Component2:public Icomp2,public IsdkComponent,public LanguageChangeInterface{
	std::thread mainLoopthread;
	ComponentDependency<ILCM> m_lcm;
	void run(){
			while(1){
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		}
public:
	Component2(Idependencymanager &dp):m_lcm(dp){}
	~Component2(){
		if(mainLoopthread.joinable())
					mainLoopthread.join();
	}

	virtual void start() override{
		mainLoopthread = std::thread(&Component2::run,this);
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




#endif /* SRC_COMPONENT2_COMPONENT2_HPP_ */
