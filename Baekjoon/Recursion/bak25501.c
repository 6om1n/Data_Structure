/*백준 25501번 (재귀) -> 아래는 앞에서부터 읽었을 때와 뒤에서부터 읽었을 때가 같은 팰린드롬을 판별하는 함수 
다행히 한 번에 성공...ㅠ
*/
#include <stdio.h>
#include <string.h>
// 개수를 셀 수 있는 count 변수
int count =0;
char string[1000];
/*처음 문자열 맨 뒤와 맨 앞을 가리킨 다음에 같으면 앞에서는 한 칸씩 넘어오고, 뒤에서는 한 칸씩 앞으로 오면서
각각의 문자가 같은지를 확인한다. */
int recursion(const char *s, int l, int r){
    count++;
    if (l >= r) return 1;
    else if(s[l] != s[r]) return 0;
    else return recursion(s, l+1, r-1); // 같은 경우 recursion 함수를 계속 호출한다. 
}

int isPalindrome(const char *s){
    return recursion(s,0, strlen(s)-1);
}

int main() {
    int T=0;
    scanf("%d", &T);
    for(int i=0; i<T; i++){
        scanf("%s", &string);
        int result = isPalindrome(string);
        printf("%d %d\n",result, count);
        count =0;

    }
}