#include <string>

#include <stdio.h>
// SUT
class Database {
public:
	void Connect() {}
	void Disconnect() {}
	
	void Login(const std::string& id, const std::string& password) {}
	void Logout() {}

	bool IsLogin() { return false; }
};

#include <gtest/gtest.h>

class DatabaseTest : public ::testing::Test {
protected:
	Database *database;
	virtual void SetUp() override {
		printf("SetUp()\n");
		database = new Database;
		database->Connect();
	}

	virtual void TearDown() override {
		printf("TearDown()\n");
		database->Disconnect();
		delete database;
	}
};

#if 1
TEST_F(DatabaseTest, loginTest) {
	database->Login("test_id", "test_password");

	ASSERT_TRUE(database->IsLogin()) << "데이터베이스에 로그인 하였을 때";
}

TEST_F(DatabaseTest, logoutTest) {
	database->Login("test_id", "test_password");
	database->Logout();

	ASSERT_FALSE(database->IsLogin()) << "데이터베이스에 로그아웃 하였을 때";
}


#endif
#if 0
TEST_F(DatabaseTest, loginTest) {
	Database *database = new Database;
	database->Connect();

	database->Login("test_id", "test_password");

	ASSERT_TRUE(database->IsLogin()) << "데이터베이스에 로그인 하였을 때";

	database->Disconnect();
	delete database;
}

TEST_F(DatabaseTest, logoutTest) {
	Database *database = new Database;
	database->Connect();

	database->Login("test_id", "test_password");
	database->Logout();

	ASSERT_FALSE(database->IsLogin()) << "데이터베이스에 로그아웃 하였을 때";

	database->Disconnect();
	delete database;
}
#endif

















