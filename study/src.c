#include <stdio.h>
#include <string.h>

int main() {
    char originalStr[100] = "world"; // 예제에서는 "world"로 초기화
    char resultStr[100];

    // 괄호 추가
    strcpy(resultStr, "( ");
    strcat(resultStr, originalStr);

    // 결과 출력
    printf("Result: %s\n", resultStr);

    return 0;
}
