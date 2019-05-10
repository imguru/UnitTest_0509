#include <stdio.h>

// 클래스의 모든 필드는 private 좋다.
// protected는 자식간의 강한 결합을 만든다.
//  => 해당 필드에 자식 클래스가 의존할 수 있기 때문에, 절대 사용하지 말자.
class User {
protected:
	int age;
};

class TestUser : public User {
public:
	using User::age; // 부모의 protected 를 public으로 변경하는 기법.
};

int main() {
	TestUser user;
	user.age = 42;
	printf("%d\n", user.age);
}
