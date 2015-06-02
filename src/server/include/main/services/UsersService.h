#ifndef SERVER_MAIN_SERVICES_USERSSERVICE_H_
#define SERVER_MAIN_SERVICES_USERSSERVICE_H_

#include "../services/ServiceInterface.h"
#include "../database/Database.h"
#include "../user/User.h"
#include "../config.h"

class UsersService: public ServiceInterface {
	friend class UsersServiceTest;
public:

	virtual std::string getUri() const;
	virtual std::string executeRequest(const Json::Value &paramMap) const;

private:

	static const std::string serviceName;
	static Json::Value doUsers(const Json::Value &data);

};

class UsersServiceCreator: public ServiceCreatorInterface{
	virtual ServiceInterface* create();
};

#endif /* SERVER_MAIN_SERVICES_USERSSERVICE_H_ */
