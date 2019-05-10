#include <stdio.h>


#if 0
class User {
private:
	int age;
};
#endif


// 아래의 기법은 무조건 사용할 수 있지 않습니다.
//  => pImpl Idioms, 예외 안정성
//     : Exceptional C++ / More Exceptional C++ / Exceptional C++ Style
#define private public
#define class struct
#include "User.h"

int main() {
	User user;
	user.age = 42;
	printf("%d\n", user.age);
}






