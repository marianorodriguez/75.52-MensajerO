#include "Connection.h"
#include "mongoose.h"

Connection::Connection(mg_connection* const rawConnection){
	this->rawConnection = rawConnection;
}

std::string Connection::getUri() const{
	return this->rawConnection->uri;
}

mg_connection* Connection::getRawConnection() const{
	return this->getRawConnection();
}
