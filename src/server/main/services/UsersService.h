#ifndef SERVER_MAIN_SERVICES_USERSSERVICE_H_
#define SERVER_MAIN_SERVICES_USERSSERVICE_H_

#include "services/ServiceInterface.h"
#include "database/Database.h"
#include "user/User.h"
#include "config.h"

class UsersService: public ServiceInterface {
public:

	virtual std::string getUri() const;
	virtual void executeRequest(const Connection& connection) const;

private:

	static const std::string serviceName;
};

class UsersServiceCreator: public ServiceCreatorInterface{
	virtual ServiceInterface* create();
};

#endif /* SERVER_MAIN_SERVICES_USERSSERVICE_H_ */
