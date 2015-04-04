#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>

// Forwards
struct mg_connection;

class Connection{
public:
	Connection(mg_connection* const rawConnection);
	std::string getUri() const;
	mg_connection* getRawConnection() const;
private:
	mg_connection* rawConnection;
};

#endif // CONNECTION_H
