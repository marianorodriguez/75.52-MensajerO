#include "ServiceCollection.h"
#include "ServiceInterface.h"

ServiceCollection::~ServiceCollection(){
}

void ServiceCollection::addService(ServiceInterface* const service){
	std::map<std::string, ServiceInterface*>::iterator it;
	it = this->serviceMap.find(service->getUri());
	if (it != this->serviceMap.end()){
		delete it->second;
	}
	std::pair<std::string, ServiceInterface*> mapEntry(service->getUri(), service);
	this->serviceMap.insert(it, mapEntry);
}

ServiceInterface* ServiceCollection::getService(const std::string& serviceName) const{
	std::map<std::string, ServiceInterface*>::const_iterator it;
	it = this->serviceMap.find(serviceName);
	return it->second;
}

std::vector<std::string> ServiceCollection::getServiceNameList() const{
	std::vector<std::string> nameList;
	std::map<std::string, ServiceInterface*>::const_iterator it;
	for (it = this->serviceMap.begin(); it != this->serviceMap.end(); ++it){
		nameList.push_back(it->first);
	}
	return nameList;
}
