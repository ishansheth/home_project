/*
 * Navsdk.hpp
 *
 *  Created on: Feb 18, 2017
 *      Author: ishan
 */

#ifndef SRC_NAVSDK_NAVSDK_HPP_
#define SRC_NAVSDK_NAVSDK_HPP_

#include<memory>
#include "componentnames.hpp"

class Navsdk:public Idependencymanager{
	std::thread mainLoopthread;
	std::list<ComponentDependencyBase*> m_componentlist;

public:
	Navsdk(){}
	~Navsdk(){
	}
	void start(){
	}

	void dependencyMethod(ComponentDependencyBase* componentObj){
		std::cout<<"inside Navsdk::dependency method"<<std::endl;
		m_componentlist.push_back(componentObj);
	}

	void startApplication(){
		std::shared_ptr<IsdkComponent> ptr1 = std::make_shared<Component1>(*this);
		std::shared_ptr<IsdkComponent> ptr2 = std::make_shared<Component2>(*this);
		std::shared_ptr<IsdkComponent> lcm_ptr = std::make_shared<LCM>(*this);
		std::shared_ptr<IsdkComponent> net_comp = std::make_shared<NetComponent>(*this);

		// generating the EventLoop and getting the signals from it
		std::shared_ptr<IEventloop> eloop = std::make_shared<EventLoop>(*this);
		std::shared_ptr<IEventloop::TimerEventSignal> signal1 = eloop->getPeriodicSignal(IEventloop::TimerGroup::FIVE_SECONDS);
		signal1->connect([](const IEventloop::TimerGroup& gr){
			std::cout<<"signal received::"<<static_cast<int>(gr)<<std::endl;
		});
		std::shared_ptr<IEventloop::TimerEventSignal> signal2 = eloop->getPeriodicSignal(IEventloop::TimerGroup::ONE_SECOND);
		signal2->connect([](const IEventloop::TimerGroup& gr){
			std::cout<<"signal received::"<<static_cast<int>(gr)<<std::endl;
		});
		eloop->start();

		//starting the Component1 and 2
		ptr1->start();
		ptr2->start();

		//starting the LCM component
		lcm_ptr->start();

		//starting the tcp component
		net_comp->start();

		std::cout<<"in start app:"<<m_componentlist.size()<<std::endl;

	}
};

#endif /* SRC_NAVSDK_NAVSDK_HPP_ */
