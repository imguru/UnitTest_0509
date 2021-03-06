#include <exception>

class IOException : public std::exception {
public:
	virtual const char* what() {
		return "Bad connection";
	}
};

class User;
struct IConnection {
	virtual void Move(int x, int y) = 0;
	virtual void Attack(User* p) = 0;

	virtual ~IConnection() {}
};

class User {
	IConnection *connection;
public:
	User(IConnection* p) : connection(p) {}

	void Move(int x, int y) {
		connection->Move(x, y);
	}

	void Attack(User* user) {
		connection->Attack(user);
	}
};
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class StubConnection : public IConnection {
public:
	MOCK_METHOD2(Move, void(int, int));
	MOCK_METHOD1(Attack, void(User*));
}

using ::testing::Throw;
TEST(UserTest, moveTest) {
	StubConnection stub;
	ON_CALL(stub, Move(10, 20)).WillRepeatedly(Throw(IOException()));
	User user(&stub);

	EXPECT_THROW(user.Move(10, 20), IOException);
}





















