#include "ServerConfig.h"
#include "services/SendMessageService.h"
#include "services/CurrentChatsService.h"
#include "services/LogInService.h"
#include "services/ImAliveService.h"
#include "services/SignUpService.h"
#include "services/UserConfigService.h"
#include "services/UsersService.h"
#include "SomethingForMeService.h"

ServerConfig::ServerConfig(const ServerOptions& options){
}

void ServerConfig::configure(RestServer& server){
	addServiceCreators(server);
}

void ServerConfig::addServiceCreators(RestServer& server){
	server.addService(new CurrentChatsServiceCreator());
	server.addService(new ImAliveServiceCreator());
	server.addService(new LogInServiceCreator());
	server.addService(new SendMessageServiceCreator());
	server.addService(new SignUpServiceCreator());
	server.addService(new SomethingForMeServiceCreator());
	server.addService(new UserConfigServiceCreator());
	server.addService(new UsersServiceCreator());
}
