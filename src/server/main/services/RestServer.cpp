#include <cstdio>
#include <cstring>

#include "RestServer.h"
#include "mongoose.h"

static int ev_handler(struct mg_connection *conn, enum mg_event ev) {
	RestServer* server = static_cast<RestServer*>(conn->server_param);
	Connection connectionWrap(conn);
	switch (ev) {
		case MG_AUTH:
			return MG_TRUE;
		case MG_REQUEST:
			server->handleConnection(connectionWrap);
			return MG_TRUE;
		default:
			return MG_FALSE;
	}
}

/**
 * Constructor
 */
RestServer::RestServer(){
	this->server = mg_create_server(this, ev_handler);
	mg_set_option(this->server, "listening_port", "8081");
	for (;;) {
		mg_poll_server(server, 1000);
	}
}

/**
 * Destructor
 */
RestServer::~RestServer(){
	shutdownServer();
}

void RestServer::handleConnection(const Connection& connection) const{
}

/**
 * Apago el servidor
 */
int RestServer::shutdownServer(){
	mg_destroy_server(&this->server);
}
