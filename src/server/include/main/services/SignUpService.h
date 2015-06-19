#ifndef SIGNUP_SERVICE_H
#define SIGNUP_SERVICE_H
#include "ServiceInterface.h"
#include "../user/User.h"
#include "../database/Database.h"
#include "../utilities/LocationManager.h"

/**
 * Clase encargada de realizar el servicio de registracion del servidor.
 * Quien use este servicio quedará registrado como usuario del servidor.
 */
class SignUpService: public ServiceInterface {
	friend class SignUpServiceTest;
public:
	virtual std::string getUri() const;
	virtual std::string executeRequest(const Json::Value &paramMap) const;

private:
	/**
	 * Aplica el servicio de registro de un usuario.
	 * @param data informacion del usuario que se desea registrar.
	 * @return informacion sobre el resultado de la operacion.
	 */
	static Json::Value doSignUp(const Json::Value& data);

};

/**
 * creador del servicio de registracion.
 */
class SignUpServiceCreator : public ServiceCreatorInterface{
public:
    virtual ServiceInterface* create();
};

#endif // SIGNUP_SERVICE_H
