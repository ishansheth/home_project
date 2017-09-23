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
#include <boost/asio/io_service.hpp>

class Navsdk:public Idependencymanager{
	std::thread mainLoopthread;
	std::list<ComponentDependencyBase*> m_componentlist;
	std::list<std::shared_ptr<IsdkComponent>> m_factoryComponents;
	boost::asio::io_service* ioservice_instance;
	std::thread mainloopthread;

public:
	Navsdk()
	{
		ioservice_instance = new boost::asio::io_service();
	}
	~Navsdk(){
		if(mainloopthread.joinable())
		{
			mainloopthread.join();
		}
	}
	void start(){
		startApplication();
	}
private:
	void dependencyMethod(ComponentDependencyBase* componentObj){
		m_componentlist.push_back(componentObj);
	}

	template<typename Interface,typename Factory>
	void createComponents()
	{
		std::shared_ptr<Interface> ptr = Factory::createComponent(*this);
		m_factoryComponents.push_back(ptr);
	}

	void startApplication(){
		createComponents<IPathFinder,PathFinderFactory>();
		createComponents<IPositioning,PositioningFactory>();
		createComponents<ILCM,LCMFactory>();
		std::shared_ptr<IsdkComponent> net_comp = std::make_shared<NetComponent>(*this,*ioservice_instance,"highscore.de");

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

		//starting the tcp component
		net_comp->start();
		mainloopthread = std::thread([this](){ioservice_instance->run();});
		std::cout<<"in start app:"<<m_componentlist.size()<<std::endl;

	}
};

#endif /* SRC_NAVSDK_NAVSDK_HPP_ */
