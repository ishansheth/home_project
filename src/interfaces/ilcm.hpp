/*
 * ilcm.hpp
 *
 *  Created on: Feb 18, 2017
 *      Author: ishan
 */

#ifndef SRC_INTERFACES_ILCM_HPP_
#define SRC_INTERFACES_ILCM_HPP_

#include "LanguageChangeInterface.hpp"
#include "IsdkComponent.hpp"
class ILCM : public IsdkComponent{
public:
	virtual void registerForLanguageChange(std::string,LanguageChangeInterface &)=0;
	virtual void print_component_map()=0;
	virtual void trigger_changeTransaction()=0;
};




#endif /* SRC_INTERFACES_ILCM_HPP_ */
