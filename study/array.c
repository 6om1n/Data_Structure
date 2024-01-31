#include <stdio.h>
#include <stdlib.h>

//어디가 문제인지 모르겠는 코드 왜 rows와 cols를 인식 못하는거임?

int **make2dArray(int rows, int cols){
    int **x,i;
    x=(int**)malloc(rows*sizeof(int *));
    for(i=0; i<rows; i++){
        *(x+i) = (int *)malloc(sizeof(int)*cols);
    }
    return x;
}

int main(void){
    int **myArray;
    //5*10 짜리 2차원배열을 만들고 싶음
    myArray = make2dArray(5,10);
    myArray[2][4]=6;
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols;j++)
            fprintf(stdout, "%d ", myArray[i][j]);
        fprintf(stdout, "\n");
    }
}

//2차원 malloc 동적할당 코드 rows와 cols를 받았다고 가정했을 때
int **array
**array = (int**)malloc(sizeof(int *)* rows); // 행 만큼 각각의 1차원 배열만 생성한 상태
for(int i=0; i<rows; i++){
    *(array+i) = (int *)malloc(sizeof(int)* cols); //각각의 1차원 배열에서 cols를 추가하여 2차원 배열을 만든 상태 
}

//포인터변수= 포인터를 저장하는 변수, 포인터변수는 주소를 저장하고 있음 따라서 1만큼 증가해도 실제 1이 아닌, 바이트 만큼이 증가
int *p;
char *q;
double *r;

//여러가지의 타입을 담을 수 있는 구조체
struct humanbeing {
    char name[10];
    int age;
    float salary;
};
//구조체를 사용할 때는 반드시 변수이름을 다시 설정해주어야한다.
//.을 사용해서 구조체맴버에 접근한다. 
struct humanbeing person;
strcpy(person.name, "james");
person.age = 10;
person.salary = 35000;

//구조체를 사용하여 사각형을 표현한 예
struct point {
int x;
int y;
};

struct point pt;
pt.x =10;
pt.y=20;

//구조체 안에 구조체를 이용하여 (10,10), (80,50) 두 개의 점을 하나의 구조체 안에 집어넣음
struct rect {
    struct point pt1; (10,10)
    struct point pt2; (80,50)
};

struct rect screen;
screen.pt1.x=10;
screen.pt1.y=10;
screen.pt2.x=80;
screen.pt2.y=50;

//typedef struct는 마지막에 반드시 형태 이름을 저장해야한다. 
typedef struct {
    char name[10];
    int age;
    float salary;
}humanbeing;
//변수를 선언해줄 때 struct 표시를 안해도 된다는 장점이 있음 
humanbeing person1, person2;
//_treenode라고 하는 타입의 구조체 설정
typedef struct _treenode{
    int value;
    struct _treenode *left;
    struct _treenode *right;
}treenode;

//strcmp가 스트링을 비교할 때 사용한다.
//strcmp가 0이 나오면 같다는 의미, 다르면 조건문을 참으로 만들어준다. 
int humanEqual(humanbeing person1, humanbeing person2) {
    if(strcmp(person1.name, person2.name))
        return false;
    if(person1.age != person2.age)
        return false;
    if(person1.salary != person2.salary)
        return false;
}
//공용체 -> 구조체와 비슷하지만, 각각의 맴버들은 메모리 고간을 공용으로 사용한다.
typedef struct {
    enum tagField {female, male} sex;
    union {
        int children;
        int beard;
    } u;
}sexType;

//humanbeing 타입의 구조체
typedef struct {
    char name[10];
    int age;
    float salary;
    sexType sexinfo;
}humanbeing;

humanbeing person1, person2;
person1.sexinfo.sex = male;

