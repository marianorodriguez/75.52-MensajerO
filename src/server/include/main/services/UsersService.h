#ifndef SERVER_MAIN_SERVICES_USERSSERVICE_H_
#define SERVER_MAIN_SERVICES_USERSSERVICE_H_

#include "../services/ServiceInterface.h"
#include "../database/Database.h"
#include "../user/User.h"
#include "../config.h"

class UsersService: public ServiceInterface {
public:
	virtual std::string getUri() const;
	virtual std::string executeRequest(const Json::Value &paramMap) const;
	Json::Value doUsers(const Json::Value &data) const;
	
private:
	static const std::string serviceName;
};

class UsersServiceCreator: public ServiceCreatorInterface{
	virtual ServiceInterface* create(Database& userDb, Database& chatDb);
};

#endif /* SERVER_MAIN_SERVICES_USERSSERVICE_H_ */
