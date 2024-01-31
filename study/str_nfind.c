//문자열 패턴 매칭
//스트링 string과 pat이 있을 때, pat은 string을 탐색하기 위한 패턴, 패턴을 매칭하면 시작점을 반환하고, 실패하면 -1을 반환한다.

#include <stdio.h>
#include <string.h>

int nfind(char *string, char *pat);

int main(){
    char pat[] = "aab";
    char string[]="ababbaabaa";
    printf("%s\n%s\nArray[%d]\n", string, pat, nfind(string,pat));
}

int nfind(char *string, char *pat){
    int i, j, start=0;
    int lasts = strlen(string)-1; // 널 문자를 제외한 길이를 반환
    int lastp = strlen(pat)-1; // pat 스트링의 총 문자열 길이
    int endmatch = lastp; // 즉 3이 될거같음
     
    //점점 endmatch의 길이를 늘려나가면서 스트링 탐색을 뒤로 보내는 역할을 한다.
    for(i=0; endmatch <= lasts; endmatch++, start++){
        if(string[endmatch]== pat[lastp])
            for(j=0, i=start; j< lastp && string[i] == pat[j]; i++, j++)
            ;
                if(j==lastp)
                    return start;
    }
    return -1;
}
