#include <string>
#include <stdio.h>

struct IFileSystem {
	virtual bool IsValid(const std::string& name) = 0;
	virtual ~IFileSystem() {}
};

class FileSystem : public IFileSystem {
public:
	bool IsValid(const std::string& name) { return false; }
};

class Logger {
public:
	IFileSystem* fs;
	Logger(IFileSystem* p = nullptr) : fs(p) {
		if (fs == nullptr) {
			fs = new FileSystem;
		}
	}

	bool IsValidFilename(const std::string& filename) {
		size_t index = filename.find_last_of(".");
		std::string name = filename.substr(0, index);

		if (name.size() < 5)
			return false;

		return fs->IsValid(filename);
	}
};

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class LoggerTest : public ::testing::Test {
protected:
	virtual void SetUp() override {
	}

	virtual void TearDown() override {
	}
};

class StubFileSystem : public IFileSystem {
public:
	MOCK_METHOD1(IsValid, bool(const std::string& name));
};

using ::testing::Return;
TEST_F(LoggerTest, IsValidFilename_NameShorterThan5Chars_ReturnsFalse) {
	std::string filename = "bad.log";
	StubFileSystem stub;
	ON_CALL(stub, IsValid(filename)).WillByDefault(Return(true)); // !!
	Logger logger(&stub);

	// EXPECT_CALL(stub, IsValid(filename));
	bool actual = logger.IsValidFilename(filename);

	ASSERT_FALSE(actual) << "파일명이 다섯글자보다 짧을 때";
}

TEST_F(LoggerTest, IsValidFilename_NameLongerThan5Chars_ReturnsTrue) {
	std::string filename = "gooood.log";
	StubFileSystem stub;
	ON_CALL(stub, IsValid(filename)).WillByDefault(Return(true));
	Logger logger(&stub);

	EXPECT_CALL(stub, IsValid(filename));

	bool actual = logger.IsValidFilename(filename);
	ASSERT_TRUE(actual) << "파일명이 다섯글자 이상일 때";
}




