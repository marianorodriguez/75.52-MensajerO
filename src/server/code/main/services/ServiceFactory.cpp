#include "../../../include/main/services/ServiceFactory.h"
#include "../../../include/main/services/ServiceInterface.h"
#include "../../../include/main/services/NullService.h"

ServiceFactory::ServiceFactory(Database& userDb, Database& chatDb) :
	userDb(userDb), chatDb(chatDb){}


ServiceFactory::~ServiceFactory(){
	std::map<std::string, ServiceCreatorInterface*>::const_iterator it;
	for (it = this->serviceMap.begin(); it != this->serviceMap.end(); ++it){
		delete it->second;
	}
}

ServiceInterface* ServiceFactory::createService(const std::string& serviceName) const{
	std::map<std::string, ServiceCreatorInterface*>::const_iterator it;
	it = this->serviceMap.find(serviceName);
	if (it == this->serviceMap.end()){
		return new NullService();
	} else {
		return it->second->create(this->userDb, this->chatDb);
	}
}

void ServiceFactory::addNewServiceCreator(ServiceCreatorInterface* creator){
	std::map<std::string, ServiceCreatorInterface*>::iterator it;
	ServiceInterface* service = creator->create(userDb, chatDb);
	it = this->serviceMap.find(service->getUri());
	if (it != serviceMap.end()){
		delete it->second;
	}
	std::pair<std::string, ServiceCreatorInterface*> pair(service->getUri(), creator);
	serviceMap.insert(it, pair);
	delete service;
}
