
#include <string>
#include <stdio.h>

class User {
	std::string id_;
	int level_;
	int gold_;
public:
	User(const std::string& id, int level, int gold) :
		id_(id), level_(level), gold_(gold) {}
	
	std::string id() const { return id_;  }
	int level() const { return level_; }
	int gold() const  { return gold_;  }
};

struct IDatabase {
public:
	virtual void Save(const std::string& id, User* user) = 0;
	virtual User* Load(const std::string& id) = 0;

	virtual ~IDatabase() {}
};

// 1. 실제 UserManager가 의존하는 객체가 아직 만들어지지 않았다.
// 2. 실제 데이터베이스를 의존할 경우, 검증하기 어렵다.
#if 0
class Database : public IDatabase {
};
#endif

// SUT
class UserManager {
	IDatabase* database;
public:
	UserManager(IDatabase* p) : database(p) {}

	void Save(User *u) {
		database->Save(u->id(), u);
	}

	User* Load(const std::string& id) {
		return database->Load(id);
	}
};

#include <gtest/gtest.h>
#include <map>

class FakeDatabase : public IDatabase {
	std::map<std::string, User *> data;
public:
	virtual void Save(const std::string& id, User* user) {
		data[id] = user;
	}

	virtual User* Load(const std::string& id) {
		return data[id];
	}
};

class UserManagerTest : public ::testing::Test {
};

// ASSERT_EQ / EXPECT_EQ
//  : 사용자 정의 타입에서 사용하기위해서 필요합니다.

bool operator==(const User& lhs, const User& rhs) {
	return lhs.id() == rhs.id() && 
		   lhs.level() == rhs.level() && 
		   lhs.gold() == rhs.gold();
}

TEST_F(UserManagerTest, saveTest) {
	FakeDatabase fake;
	UserManager manager(&fake);
	std::string testId = "test_id";
	int testLevel = 10;
	int testGold = 1000;
	User user(testId, testLevel, testGold);

	manager.Save(&user);
	User* actual = manager.Load(testId);

	// ==
	// 사용자 정의 클래스를 비교하기 위해서는
	// 연산자 오버로딩이 필요합니다.
	EXPECT_EQ(user, *actual);
}

// 개발환경과 운영환경에 차이를 어느 정도 해결하면서 개발하고 싶다.
//  => Docker



































