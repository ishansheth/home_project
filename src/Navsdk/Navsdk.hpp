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

/*
#include "../Idependencymanager/Idependencymanager.hpp"
#include "../component1/component1.hpp"
#include "../interfaces/icomp1.hpp"
#include "../component2/component2.hpp"
#include "../interfaces/icomp2.hpp"
#include "../Networking/NetComponent.hpp"
#include "../interfaces/ilcm.hpp"
#include "../lcm/lcm.hpp"
#include "../TimerComponent/EventLoopTimer.hpp"


class IEventloop;
class EventLoop;
class Icomp1;
class Component1;
class Icomp2;
class Component2;
class Idependencymanager;
class ILCM;
class LCM;
class NetComponent;
*/


class Navsdk:public Idependencymanager{
	std::thread mainLoopthread;
	std::list<ComponentDependencyBase*> m_componentlist;
	void run(){
		while(1){
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
public:
	Navsdk(){}
	~Navsdk(){
		if(mainLoopthread.joinable())
			mainLoopthread.join();
	}
	void start(){
		mainLoopthread = std::thread(&Navsdk::run,this);
	}

	void dependencyMethod(ComponentDependencyBase* componentObj){
		std::cout<<"inside Navsdk::dependency method"<<std::endl;
		m_componentlist.push_back(componentObj);
	}

	void startApplication(){

		std::shared_ptr<IsdkComponent> ptr1 = std::make_shared<Component1>(*this);
		std::shared_ptr<IsdkComponent> ptr2 = std::make_shared<Component2>(*this);

		std::shared_ptr<IsdkComponent> lcm_ptr = std::make_shared<LCM>(*this);


//		std::shared_ptr<IsdkComponent> net_comp = std::make_shared<NetComponent>();

		// generating the EventLoop and getting the signals from it
		std::shared_ptr<IEventloop> eloop = std::make_shared<EventLoop>();
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
//		ptr1->start();
//		ptr2->start();

//starting the LCM component
//		lcm_ptr->start();

//starting the tcp component
//		net_comp->start();

		std::cout<<"in start app:"<<m_componentlist.size()<<std::endl;
		while(1){
		}

	}
};





#endif /* SRC_NAVSDK_NAVSDK_HPP_ */
