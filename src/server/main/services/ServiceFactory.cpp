#include <services/SignUpService.h>
#include "ServiceFactory.h"
#include "ServiceInterface.h"

#include "EchoService.h"
#include "NullService.h"

ServiceFactory::ServiceFactory(){
	this->serviceMap[SERVICE_SIGNUP_NAME] = SIGNUP_SERVICE;
	this->serviceMap["echo"] = ECHO_SERVICE;
	this->serviceMap[""] = NULL_SERVICE;
}


ServiceFactory::~ServiceFactory(){
}

ServiceInterface* ServiceFactory::createService(const std::string& serviceName) const{
	std::map<std::string, ServiceInterfaceId>::const_iterator it;
	it = this->serviceMap.find(serviceName);
	if (it == this->serviceMap.end()){
		return createServiceById(NULL_SERVICE);
	} else {
		return createServiceById(it->second);
	}
}

ServiceInterface* ServiceFactory::createServiceById(
	ServiceFactory::ServiceInterfaceId id) const{
	switch(id){
	case SIGNUP_SERVICE:
		return new SignUpService();
	case ECHO_SERVICE:
		return new EchoService();
	case NULL_SERVICE:
	default:
		return new NullService();
	break;
	}
}


std::vector<std::string> ServiceFactory::getServiceNameList() const{
	std::vector<std::string> nameList;
	std::map<std::string, ServiceInterfaceId>::const_iterator it;
	for (it = this->serviceMap.begin(); it != this->serviceMap.end(); ++it){
		nameList.push_back(it->first);
	}
	return nameList;
}
