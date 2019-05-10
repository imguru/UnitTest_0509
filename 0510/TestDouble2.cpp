// 테스트 대역
//  => 무조건 적용할 수 있지 않습니다.
//  => 제품 코드가 테스트 대역을 받아들이는 설계이어야 합니다.

#include <string>
#include <stdio.h>

// 아래 코드 문제점
//   Logger와 FileSystem이 강한 결합으로 설계되어 있다.
//   => 강한 결합
//      한 클래스가 다른 클래스를 이용할 때, 구체적인 타입을 직접 사용하는 것.

//   => 느슨한 결합(약한 결합)
//     : 인터페이스나 추상 클래스 기반으로 다른 클래스를 이용해야 합니다.
//       절대 직접 생성해서 사용하면 안됩니다 !!!
//       생성된 객체를 외부에서 전달 받아야 합니다.
//        => DI(Dependency Injection)
//        1) 생성자 주입
//         : 의존하는 객체가 반드시 필요한 객체일 때.
//        2) 메소드 주입
//         : 의존하는 객체가 메소드 호출시에만 필요할 때.
//        문제점
//         -> 보일러플레이트가 발생한다.
//            (반드시 필요하지만 반복되는 코드)
//        
//        User(new NetworkManager(), new UserManager(), new Level());
//         : 위처럼 직접 의존 객체를 생성해서 주입하는 방식
//         => 가난한 자의 의존성 주입
//         => 보일러플레이트를 없앨 수 있는 의존성 주입 라이브러리를 적극적으로 활용하는 것이 좋다.
//            : Dagger2

// C++ 인터페이스
struct IFileSystem {
	virtual bool IsValid(const std::string& name) = 0;
	virtual ~IFileSystem() {}
};

class FileSystem : public IFileSystem {
public:
	bool IsValid(const std::string& name) { return false; }
	// NTFS, ext4, xfs ...
};

class Logger {
public:
	IFileSystem* fs;
	Logger(IFileSystem* p = nullptr) : fs(p) {
		// 기존에 객체를 생성해서 사용하던 방식이 변경되지 않도록 하는 것이 좋습니다.
		if (fs == nullptr) {
			fs = new FileSystem;
		}
	}

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
		// IFileSystem *fs = new FileSystem;
		return fs->IsValid(filename);
	}
};

#include <gtest/gtest.h>

class StubFileSystem : public IFileSystem {
public:
	virtual bool IsValid(const std::string& name) {
		return true;
	}
};


class LoggerTest : public ::testing::Test {
protected:
	virtual void SetUp() override {
	}

	virtual void TearDown() override {
	}
};

TEST_F(LoggerTest, IsValidFilename_NameShorterThan5Chars_ReturnsFalse) {
	StubFileSystem stub;
	Logger logger(&stub);
	std::string filename = "bad.log";

	bool actual = logger.IsValidFilename(filename);

	ASSERT_FALSE(actual) << "파일명이 다섯글자보다 짧을 때";
}

TEST_F(LoggerTest, IsValidFilename_NameLongerThan5Chars_ReturnsTrue) {
	StubFileSystem stub;
	Logger logger(&stub);
	std::string filename = "gooood.log";

	bool actual = logger.IsValidFilename(filename);

	ASSERT_TRUE(actual) << "파일명이 다섯글자 이상일 때";
}




