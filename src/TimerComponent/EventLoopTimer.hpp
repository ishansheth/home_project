/*
 * EventLoopTimer.hpp
 *
 *  Created on: Aug 3, 2017
 *      Author: ishan
 */

#ifndef SRC_TIMERCOMPONENT_EVENTLOOPTIMER_HPP_
#define SRC_TIMERCOMPONENT_EVENTLOOPTIMER_HPP_

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/signals2/signal.hpp>
#include "../interfaces/IsdkComponent.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>


class IEventloop:public IsdkComponent{
public:
	enum class TimerGroup:int{
		TWO_HUNDRED_MILLIS,
		FIVE_HUNDRED_MILLIS,
		ONE_SECOND,
		FIVE_SECONDS,
		ONE_MINUTE,
		FIVE_MINUTE,
		ONE_HOUR
	};

	using AsioEventLoop = boost::asio::io_service;
//	using TimerEvent = void(const TimerGroup&);
	using TimerEventSignal = boost::signals2::signal<void(const TimerGroup&)>;
	using TimerEventConnection = boost::signals2::connection;
	virtual std::shared_ptr<AsioEventLoop> getEventloop()=0;
	virtual std::shared_ptr<TimerEventSignal> getPeriodicSignal(const TimerGroup& grp)=0;
	virtual void start()=0;
};

class EventLoop : public IEventloop{
private:
	const size_t two_hundred_millis = 200;
	const size_t five_hundred_millis = 500;
	const size_t one_second = five_hundred_millis * 2;
	const size_t five_seconds = one_second * 5;
	const size_t one_minute = five_seconds * 12;
	const size_t five_minute = one_minute * 5;
	const size_t one_hour = five_minute * 12;

	struct SignalTimer{
		boost::asio::deadline_timer m_timer;
		TimerGroup m_timergroup;
		std::size_t m_millis;
		std::shared_ptr<TimerEventSignal> m_signal;
		SignalTimer(const std::shared_ptr<AsioEventLoop> el, const TimerGroup group, const size_t interval);
		~SignalTimer();
		void repeat();
		void cancel();
	};
public:

	EventLoop(Idependencymanager &dp);
	~EventLoop();
	virtual std::shared_ptr<AsioEventLoop> getEventloop() override;
	virtual std::shared_ptr<TimerEventSignal> getPeriodicSignal(const TimerGroup& grp) override;
	virtual void start() override;
	void launch();
private:
	std::shared_ptr<AsioEventLoop> m_asioeventloop;
	SignalTimer m_signaltwohundredmillis;
	SignalTimer m_signalfivehundredmillis;
	SignalTimer m_signalonesecond;
	SignalTimer m_signalfiveseconds;
	SignalTimer m_signaloneminute;
	SignalTimer m_signalfiveminute;
	SignalTimer m_signalonehour;
	std::thread mainloopthread;

};

void EventLoop::start(){
	mainloopthread = std::thread([this](){m_asioeventloop->run();});
}

EventLoop::SignalTimer::SignalTimer(const std::shared_ptr<AsioEventLoop> el,const enum TimerGroup group, const size_t interval):
		m_timer(*el,boost::posix_time::seconds(0)),m_signal(std::make_shared<TimerEventSignal>()),m_millis(interval),m_timergroup(group){

}
void EventLoop::SignalTimer::repeat(){
	m_timer.expires_at(m_timer.expires_at() + boost::posix_time::milliseconds(m_millis));
	m_timer.async_wait([this](const boost::system::error_code& ec){
		if(!ec){
			repeat();
			(*m_signal)(m_timergroup);
		}
	});
}

void EventLoop::SignalTimer::cancel(){
	m_timer.cancel();
}
EventLoop::SignalTimer::~SignalTimer(){
	m_timer.cancel();
}
EventLoop::~EventLoop(){
	if(mainloopthread.joinable())
	{
		mainloopthread.join();
		m_asioeventloop->stop();

	}
}

EventLoop::EventLoop(Idependencymanager &dp):
		m_asioeventloop(std::make_shared<boost::asio::io_service>()),
		m_signaltwohundredmillis(m_asioeventloop,TimerGroup::TWO_HUNDRED_MILLIS,200),
		m_signalfivehundredmillis(m_asioeventloop,TimerGroup::FIVE_HUNDRED_MILLIS,500),
		m_signalonesecond(m_asioeventloop,TimerGroup::ONE_SECOND,1000),
		m_signalfiveseconds(m_asioeventloop,TimerGroup::FIVE_SECONDS,5000),
		m_signaloneminute(m_asioeventloop,TimerGroup::ONE_MINUTE,5000*2),
		m_signalfiveminute(m_asioeventloop,TimerGroup::FIVE_MINUTE,5000*10),
		m_signalonehour(m_asioeventloop,TimerGroup::ONE_HOUR,5000*10*12)
{
	(void)dp;
	m_signaltwohundredmillis.repeat();
	m_signalfivehundredmillis.repeat();
	m_signalonesecond.repeat();
	m_signalfiveseconds.repeat();
	m_signaloneminute.repeat();
	m_signalfiveminute.repeat();
	m_signalonehour.repeat();

}

std::shared_ptr<IEventloop::AsioEventLoop> EventLoop::getEventloop()
{
	return m_asioeventloop;
}

std::shared_ptr<IEventloop::TimerEventSignal> EventLoop::getPeriodicSignal(const TimerGroup& grp)
{
	switch(grp){
	case TimerGroup::TWO_HUNDRED_MILLIS:
		return m_signaltwohundredmillis.m_signal;
	case TimerGroup::FIVE_HUNDRED_MILLIS:
		return m_signalfivehundredmillis.m_signal;
	case TimerGroup::ONE_SECOND:
		return m_signalonesecond.m_signal;
	case TimerGroup::FIVE_SECONDS:
		return m_signalfiveseconds.m_signal;
	case TimerGroup::ONE_MINUTE:
		return m_signaloneminute.m_signal;
	case TimerGroup::FIVE_MINUTE:
		return m_signalfiveminute.m_signal;
	case TimerGroup::ONE_HOUR:
		return m_signalonehour.m_signal;
	}
}




#endif /* SRC_TIMERCOMPONENT_EVENTLOOPTIMER_HPP_ */
