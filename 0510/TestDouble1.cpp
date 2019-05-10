// 테스트 대역
//   목적
//    : SUT를 최대한 격리하여, 원하는 포인터를 검증한다.
#include <string>
#include <stdio.h>

class FileSystem {
public:
	bool IsValid(const std::string& name) { return false; }
};

class Logger {
public:
	// filename: hello.log
	//   => 확장자를 제외한 파일의 이름이 반드시 5글자 이상이어야 한다.
	bool IsValidFilename(const std::string& filename) {
		//------------------------------------
		// 1. 파일 이름 길이를 체크하는 로직.
		size_t index = filename.find_last_of(".");
		std::string name = filename.substr(0, index);

		if (name.size() < 5)
			return false;
		//------------------------------------

		// 2. 파일 시스템에서 체크
		FileSystem *fs = new FileSystem;
		return fs->IsValid(filename);
	}
};

#include <gtest/gtest.h>

class LoggerTest : public ::testing::Test {
protected:
	virtual void SetUp() override {
	}

	virtual void TearDown() override {
	}
};

TEST_F(LoggerTest, IsValidFilename_NameShorterThan5Chars_ReturnsFalse) {
	Logger logger;
	std::string filename = "bad.log";

	bool actual = logger.IsValidFilename(filename);

	ASSERT_FALSE(actual) << "파일명이 다섯글자보다 짧을 때";
}

TEST_F(LoggerTest, IsValidFilename_NameLongerThan5Chars_ReturnsTrue) {
	Logger logger;
	std::string filename = "gooood.log";

	bool actual = logger.IsValidFilename(filename);

	ASSERT_TRUE(actual) << "파일명이 다섯글자 이상일 때";
}
