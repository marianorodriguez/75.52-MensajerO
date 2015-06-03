#ifndef NULLSERVICE_H
#define NULLSERVICE_H

#include "ServiceInterface.h"

class NullService : public ServiceInterface{
public:
	virtual std::string getUri() const;
	virtual std::string executeRequest(const Json::Value &paramMap) const;
private:
	static const std::string serviceName;
};

#endif // NULLSERVICE_H
