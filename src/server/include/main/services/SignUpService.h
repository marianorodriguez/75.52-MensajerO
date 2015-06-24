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
public:
	SignUpService(Database& database);
	/**
	 * Devuelve el nombre del servicio: createUser
	 */
	virtual std::string getUri() const;
	virtual std::string executeRequest(const std::string &paramMap) const;
	/**
	 * Valida si existe un usuario registrado con ese nombre
	 */
	bool checkUsernameExists(const std::string& username) const;
	/**
	 * Aplica el servicio de registro de un usuario.
	 * @param data informacion del usuario que se desea registrar.
	 * @return informacion sobre el resultado de la operacion.
	 */
	std::string doSignUp(const std::string& data) const;

private:
	static const std::string serviceName;
	Database& userDb;
};

/**
 * creador del servicio de registracion.
 */
class SignUpServiceCreator : public ServiceCreatorInterface{
public:
	virtual ServiceInterface* create(Database& userDb, Database& chatDb);
};

#endif // SIGNUP_SERVICE_H
