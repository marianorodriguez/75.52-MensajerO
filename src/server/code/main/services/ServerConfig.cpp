#include "../../../include/main/services/ServerConfig.h"
#include "../../../include/main/services/SendMessageService.h"
#include "../../../include/main/services/CurrentChatsService.h"
#include "../../../include/main/services/LogInService.h"
#include "../../../include/main/services/SignUpService.h"
#include "../../../include/main/services/UserConfigService.h"
#include "../../../include/main/services/UsersService.h"
#include "../../../include/main/services/SomethingForMeService.h"
#include "../../../include/main/services/DeleteChatService.h"

ServerConfig::ServerConfig(const ServerOptions& options) :
	options(options){}

void ServerConfig::configure(RestServer& server) const{
	addServiceCreators(server);
	server.setOptions(options);
}

void ServerConfig::addServiceCreators(RestServer& server) const{
	server.addService(new CurrentChatsServiceCreator());
	server.addService(new DeleteChatServiceCreator());
	server.addService(new LogInServiceCreator());
	server.addService(new SendMessageServiceCreator());
	server.addService(new SignUpServiceCreator());
	server.addService(new SomethingForMeServiceCreator());
	server.addService(new UserConfigServiceCreator());
	server.addService(new UsersServiceCreator());
}
