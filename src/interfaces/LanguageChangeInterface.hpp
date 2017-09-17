/*
 * LanguageChangeInterface.hpp
 *
 *  Created on: Feb 18, 2017
 *      Author: ishan
 */

#ifndef SRC_INTERFACES_LANGUAGECHANGEINTERFACE_HPP_
#define SRC_INTERFACES_LANGUAGECHANGEINTERFACE_HPP_

class LanguageChangeInterface{
public:
	virtual void setLanguage(std::string,std::function<void(std::string)>)=0;
};




#endif /* SRC_INTERFACES_LANGUAGECHANGEINTERFACE_HPP_ */
