//문자열 -> 배열의 원소가 문자인 데이터 타입
//c언어에서의 문자열은 널 문자로 끝나는 것임, 문자열과 관련된 함수는 string.h에 정의되어있음
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

//strcat, strncat : 연결, 앞에 있는 캐릭터 값으로 반환된다.  strncat의 경우 뒤에 있는 것 n개의 문자와 앞에 있는 걸 연결해서 앞의 문자로 반환한다. 
int main(int argc, char *argv[]){
fprintf(stdout, "strcat 예제입니다. \n");
char origin[50] = {"blackcat"};
char dest[50]={"aaabbb"};
strncat(dest, origin,5); // origin에 5글자가 더 붙어 출력되는 것을 볼 수 있음 
fprintf(stdout,"%s\n", dest); // 앞에 붙여진 채 출력되는 것을 볼 수 있음
fprintf(stdout,"%s\n", origin);

//strcmp : 비교, 앞의 값이 더 크면 양수반환, 뒤에 있는 값이 더 크면 음수 반환. strncmp의 경우 앞에서 n개의 문자만 비교하여 출력
fprintf(stdout, "strcmp 예제입니다. \n");
char str1[] = "helloworld"; // 제일 앞 아스키 코드 값이 더 커서 이게 더 큰 값으로 인식할 것임
char str2[] = "hellobyeworld";   
int result = strncmp(str1, str2,5);

if(result ==0)
    fprintf(stdout, "두 변수는 같은 값을 가지고 있습니다.\n");
else if (result >0)
    fprintf(stdout,"두 변수 중 앞의 변수가 더 큰 값을 가지고 있습니다.\n");
else 
    fprintf(stdout, "두 변수 중 뒤의 값이 더 큰 값을 가지고 있습니다.\n");


//strcpy : 복사, 뒤에 있는 변수의 스트링을 앞에 있는 변수의 값으로 넣어준다., strncpy -> n개의 값만 복사해서 넣어준다.
//그래도 값을 복사해서 넣어준다는 특징이 있다. 더 긴 배열에 작은 스트링을 그대로 넣어줄 경우 널문자도 같이 들어가게 되어 작은 문자 스트링만 나올 수 있다. (작은 문자의 널문자를 끝으로 인식했기 때문  
//빈 배열에 복사를 해서 넣어주었으므로 c1과 c2가 같은 값이 저장되있음을 확인할 수 있다. 
//strlen : 길이를 반환해서 준다.
fprintf(stdout, "strcpy 예제입니다. \n");
char c1[30]="oslab";
char c2[]="8864777";
strncpy(c1,c2,4);
fprintf(stdout, "%s\n", c1);
fprintf(stdout, "%s\n", c2);
fprintf(stdout, "%lu\n", strlen(c1)); //c1의 길이 반환
fprintf(stdout, "%lu", strlen(c2)); //c2의 길이 반환


//strchr 앞의 내용 중에서 뒤의 내용이 처음 나오는 곳의 포인터 반환, 없으면 null의 값을 반환해준다.
//strrchr는 마지막에 나오는 곳의 포인터를 반환해준다. 
fprintf(stdout, "\nstrchr 예제입니다.\n");
char str5[]="Hello Wecome to the World"; // 대상 문자열
char *ptr = strrchr(str5, 'W'); // W가 처음 나온 곳의 포인터 반환
fprintf(stdout, "search 문자열 : %s\n", ptr); // 처음 나온 곳부터 끝까지 문자를 반환한다. 

//strtok는 구분자를 기준으로 문자열을 단어마다 자르는 것을 의미한다. 첫번째만 해당 문자열을 넣어주고, 그 다음부터는 null문자를 넣어주면 된다.
//null문자를 넣어준다는 것은 이전에 찾은 문자열 그 다음부터 계속해서 찾아달라는 것을 의미한다.
fprintf(stdout, "strtok 예제입니다.\n ");
char str6[]="kim,park,lee,choi,hwang";
char *ptr2=strtok(str6,","); // ,를 구분자로 끊어라
while(ptr2 != NULL){
    fprintf(stdout, "%s\n", ptr2); // 자른 문자열을 출력한다.
    ptr2 = strtok(NULL,",");
}
return 0;
}
//strstr은 왼쪽 변수 중에서 오른쪽의 시작을 가리키는 포인터를 반환한다. 오른쪽으로 시작하는 것을 찾으면 된다고 생각.
 