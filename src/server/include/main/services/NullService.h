#ifndef NULLSERVICE_H
#define NULLSERVICE_H

#include "ServiceInterface.h"

/**
 * Servicio que no hace nada.
 * Se invoca en caso de que el servidor reciba un request para un servicio desconocido.
 */
class NullService: public ServiceInterface {
public:
	virtual std::string getUri() const;
	virtual std::string executeRequest(const Json::Value &paramMap) const;
};

#endif // NULLSERVICE_H
