/*
 * lcm.hpp
 *
 *  Created on: Feb 18, 2017
 *      Author: ishan
 */

#ifndef SRC_LCM_LCM_HPP_
#define SRC_LCM_LCM_HPP_

#include<map>
#include "../interfaces/ilcm.hpp"
#include "../interfaces/LanguageChangeInterface.hpp"
#include "../interfaces/IsdkComponent.hpp"
#include "../Idependencymanager/Idependencymanager.hpp"
#include "../ComponentDependency/ComponentDependency.hpp"

class LanguageChangeInterface;

class LCM:public ILCM{
	std::map<std::string,LanguageChangeInterface* > m_componentMap;
	std::function<void(std::string)> callback_func_ptr;
	std::list<std::string> resultList;
	std::thread mainLoopthread;

	void run(){
			while(1){
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		}
public:
	LCM(Idependencymanager &dp){
		callback_func_ptr = std::bind(&LCM::store_result,this,std::placeholders::_1);
	}
	virtual void start() override{
			mainLoopthread = std::thread(&LCM::run,this);
	}
	virtual void registerForLanguageChange(std::string componentName, LanguageChangeInterface& componentPtr) override{
		std::cout<<" Registering:"<<componentName<<std::endl;
		m_componentMap[componentName] = & componentPtr;

	}
	virtual void trigger_changeTransaction() override{
		for(auto& element: m_componentMap ){
			element.second->setLanguage("english",callback_func_ptr);
		}

	}
	virtual void print_component_map() override{
		for(auto& element: m_componentMap ){
			std::cout<<element.first<<std::endl;
		}
		for (auto& element: resultList){
			std::cout<<element<<std::endl;
		}

	}

	void store_result(std::string result){
		std::cout<<"storing result:"<<result<<std::endl;
		resultList.push_back(result);

	}


};




#endif /* SRC_LCM_LCM_HPP_ */
