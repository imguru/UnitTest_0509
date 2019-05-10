#include <stdio.h>
#include <string>
#include <vector>

// SUT
//  DLog <- FileTarget, NetworkTarget
//   => Observer Pattern
enum DLogLevel {
	INFO, WARN, ERROR,
};

struct DLogTarget {
	virtual void Write(DLogLevel level, const std::string& message) = 0;
	virtual ~DLogTarget() {}
};

class DLog {
	std::vector<DLogTarget*> targets;
public:
	void AddTarget(DLogTarget* p) { targets.push_back(p); }

	void Write(DLogLevel level, const std::string& message) {
		for (DLogTarget* e : targets) {
			e->Write(level, message);
		}
	}
};

//------------------------
// Test Spy Pattern
//  : 함수를 호출하였을 때, 발생하는 부수 효과를 관찰할 수 없어서, 테스트 안된 요구사항이 있다.
//  => 목격한 일을 기록해두었다가, 나중에 테스트에서 확인할 수 있도록 만들어진 테스트 대역.


#include <gtest/gtest.h>
#include <algorithm>

class SpyTarget : public DLogTarget {
	std::vector<std::string> logs;
	std::string concat(DLogLevel level, const std::string& message) {
		static const char* level_string[] = {
			"INFO", "WARN", "ERROR", 
		};

		return std::string(level_string[level]) + "@" + message;
	}

public:
	// [Begin, End)
	bool Received(DLogLevel level, const std::string& message) {
		return logs.end() != std::find(logs.begin(), logs.end(), concat(level, message));
	}

	virtual void Write(DLogLevel level, const std::string& message) override {
		std::string log = concat(level, message);
		logs.push_back(log);
	}
};


TEST(DLogTest, writeTest) {
	DLog log;
	SpyTarget spy1, spy2;
	log.AddTarget(&spy1);
	log.AddTarget(&spy2);

	log.Write(INFO, "test_info_message");
	log.Write(ERROR, "test_err_message");

	EXPECT_TRUE(spy1.Received(INFO, "test_info_message"));
	EXPECT_TRUE(spy1.Received(ERROR, "test_err_message"));
	EXPECT_TRUE(spy2.Received(INFO, "test_info_message"));
	EXPECT_TRUE(spy2.Received(ERROR, "test_err_message"));
}



































