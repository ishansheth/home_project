#include <iostream>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <list>
#include <chrono>
#include <vector>
#include <memory>
#include <tuple>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <cassert>
#include <iostream>
#include <sstream>
#include "Navsdk/Navsdk.hpp"
#include "Navsdk/componentnames.hpp"


int main()
{
	std::shared_ptr<Navsdk> navSdkPtr = std::make_shared<Navsdk>();
	navSdkPtr->startApplication();
}
