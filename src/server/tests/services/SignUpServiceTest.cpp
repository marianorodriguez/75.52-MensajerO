#include "SignUpServiceTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(SignUpServiceTest);

void SignUpServiceTest::should_create_new_user(){

	mg_connection* con;

	Connection connection(con);

	connection.paramMap[SERVICE_SIGNUP_USERNAME] = "username_test";
	connection.paramMap[SERVICE_SIGNUP_PASSWORD] = "encrypted_pwd";

	SignUpService service;
	service.executeRequest(connection);

	Database* DB = new Database();
	vector<string> key;
	key.push_back("username_test");
	string username = DB->read(key);

	//comparar el response de la connection con username
	//CPPUNIT_ASSERT(username == connection.getRawConnection()->callback_param);

	DB->erase(key);
	delete DB;
}

void SignUpServiceTest::user_should_already_exist(){

	Database* DB = new Database();
	vector<string> key;
	key.push_back("user1");
	DB->write(key, "value1");

	mg_connection* con;
	Connection connection(con);
	SignUpService service;
	bool usernameExists;

	service.checkusernameExists("user1", connection, usernameExists);

	CPPUNIT_ASSERT(usernameExists);

	DB->erase(key);
	delete DB;
}
