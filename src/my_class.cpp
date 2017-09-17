#include <iostream>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <list>
#include <chrono>
#include <vector>
#include <memory>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <cassert>
#include <type_traits>
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Navsdk/Navsdk.hpp"


//========================================================================================================================

std::vector<std::string> names;

std::string namefromIdx(int idx){
	return "sheth";
}

template<typename T>
void logAndAdd(T&& name)
{
	auto now = std::chrono::system_clock::now();
	std::cout<<"logging:"<<std::endl;
	names.emplace_back(std::forward<T>(name));
}

void logAndAdd(int idx){
	std::cout<<idx<<std::endl;
	names.emplace_back(namefromIdx(idx));
}
//========================================================================================================================

class A{
	int i;
public:
	template<typename T>
	explicit A(T&& a)
	: i(std::forward<T>(a))
	{

	}
};
//========================================================================================================================

std::string intToHexString(int val){
	std::string hexstr;
	std::stringstream sstream;
	sstream<<"0x"<<std::setfill('0')<<std::setw(2)<<std::hex<<int(val);
	hexstr = sstream.str();
	return hexstr;
}
//========================================================================================================================

// tag dispatch example for boost::optional
template<typename T>
struct optional{
public:
	explicit operator bool() const {return false;}

	T value() const {throw int();}

	template<typename U>
	T value_or(U const& v) const
	{
		return value_or_(v,std::is_convertible<U,T>());
	}

private:
	template<typename V>
	void createLogImpl(V&& name, std::false_type)
	{
		std::cout<<"logging:"<<name<<std::endl;
		names.emplace_back(std::forward<T>(name));
	}

	void createLogImpl(int idx, std::true_type)
	{
		createLogEntry(namefromIdx(idx));
	}

	template<typename V>
	void createLogEntry(V&& name)
	{
		createLogImpl(std::forward<T>(name),std::is_integral<T>());
	}

	template<typename U>
	T value_or_(U const& v, std::true_type) const
	{
			return v;
	}
	template<typename F>
	T value_or_(F const& f,std::false_type) const
	{
			return f();
	}
};
//========================================================================================================================

int def(){return -1;}

class Person{
public:
	// when input parameter is same as another person with const/non-const, volatile/non-volatile,
	// this will not be invoked,instead auto generated constructors will be used
	// we also have to check if they are not integral type, so std::string is allowed to be passed
	// in the constructor and this will be invoked
	template<typename T,typename U, typename X = typename std::enable_if<
											!std::is_base_of<Person,typename std::decay<T>::type>::value
											&&
											!std::is_integral<std::remove_reference<T>>::value>::type
											>
	explicit Person(T&& n):name(std::forward<T>(n))
	{
		// static assert is required because when false parameters are given to the ctor, then compiler will print this message ,
		// but at the end, after forward has happened. Otherwise error message will be so long that you cant see it
		static_assert(std::is_constructible<std::string,T>::value,"Parameter cant be used to generate string");
	}
private:
	std::vector<int> ages;
	std::string name;
};
//========================================================================================================================
class SpecialPerson : public Person
{
public:

	SpecialPerson(const SpecialPerson& rhs) : Person(rhs){}
	SpecialPerson(SpecialPerson&& rhs) : Person(std::move(rhs)){}
};

using FilterContainer = std::vector<std::function<bool(int)>>;
FilterContainer filters;

void addDivisor(int i){

	auto divisor = 10*i;
	//if by reference capture is used, then it will be segmentation fault
	filters.emplace_back([=](int val){return val % divisor == 0;});
}

using Time = std::chrono::steady_clock::time_point;
enum class sound{Beep,Siren,Whistle};
enum class volume{Normal,Loud,LoudPlus};
using Duration = std::chrono::steady_clock::duration;

void setAlarm(Time t,sound s, Duration d)
{
	std::cout<<"Alarm set"<<std::endl;
}

void setAlarm(Time t, sound s,Duration d, volume v)
{
}

auto setSoundL = [](sound s){
	using namespace std::chrono;
	setAlarm(steady_clock::now()+hours(1),s,seconds(30));
};

//========================================================================================================================
template<typename T>
std::string to_string_impl(const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

template<typename ... Param>
std::vector<std::string> myto_string(const Param& ... param)
{
	return {to_string_impl(param)...};
}
//========================================================================================================================
template<typename Only>
auto min(Only only)
{
	return only;
}

template<typename First, typename Second,typename...Tail>
auto min(First&& first,Second&& second,Tail&&... ts)
{
	return (std::forward<First>(first) < std::forward<Second>(second)) ?
			min(std::forward<First>(first),std::forward<Tail>(ts)...) :
			min(std::forward<Second>(second),std::forward<Tail>(ts)...);
}
//========================================================================================================================
template<typename Only>
void bar(Only only)
{
	std::cout<<only<<std::endl;
}
template<typename...Args>
void swallow(Args&& ...){

}

template<typename...Args>
void foo(Args... args)
{
//	swallow((bar(std::forward<Args>(args)),0)...);
	(void)std::initializer_list<int>{(bar(args),0)...};
}
//========================================================================================================================


int main()
{
	int x = 5;
	//without the const specifier, it wont compile because of the universal reference
	const A a(x);
	A b(a);

	auto uPTR(std::make_unique<SpecialPerson>());

	std::string petname("darla");
	logAndAdd(petname);
	logAndAdd(std::string("ishan"));

	//if you put short instead of int, then it wont compile
	int y = 5;
	logAndAdd(y);

	std::string s = "ishansheth";
	std::string& c = s;

	std::string hexstring = intToHexString(14);
	std::cout<<"Hexvalue:"<<hexstring;

	optional<int> oi;
	assert(oi.value_or(1) == 1);
	assert(oi.value_or(&def) == -1);

	addDivisor(1);
	addDivisor(2);
	addDivisor(3);

	int i = 1;
	for(auto const& element:filters)
	{
		element(i);
		i++;
	}
	setSoundL(sound::Beep);
	const auto vec = myto_string("hello",1,1,3);
	for(const auto & o:vec)
	{
		std::cout<<o<<"\n";
	}
	auto xx = min(1.1,2,3,4,5);
	std::cout<<"Min value:"<<xx<<&std::endl;

	foo(1,1.3,"ishan");

	return 0;
}
