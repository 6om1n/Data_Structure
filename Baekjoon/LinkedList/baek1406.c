/*한 줄로 된 에디터를 구현한다. 영어 소문자만을 기록할 수 있는 편집기, 최대 600,000글자입력
커서, 문장의 맨 앞, 맨 뒤, 중간에 위치할 수 있음
즉, 문자의 길이가 L일 경우, L+1의 경우에 위치할 수 있음
명령어가 수행되기 전까지는 커서는 문장의 맨 뒤에 위치한다. */
// 모든 명령어를 수행하고 난 후 편집기에 입력되어 있는 문자열을 출력한다.

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    struct node *prev;
    char data;
    struct node *next;
} node;

node *list, *cursor;

// 문자를 연결리스트에 저장한다.
void insert(char c)
{
    node *new = (node *)malloc(sizeof(node));
    new->data = c;

    // 기존에 아무런 값도 들어오지 않은 상태라면
    if (list == NULL)
    {
        list = new; // list는 맨 앞을 나타낸다
        cursor = new;
    }
    if (cursor -> next != NULL) {
        // newNode의 뒤쪽 먼저 링크들을 연결한다.
        new->next = cursor->next;
        cursor->next->prev = new;
        // newNode의 앞쪽 링크들을 연결한다.
        cursor->next = new;
        new->prev = cursor;
        cursor = new; // 나중에 커서의 위치를 변경시킨다.
    }
    else
    {
        new->prev = cursor;
        cursor->next = new;
        new -> next = NULL; //항상 맨 뒤에 있는 건 NULL을 가리켜야한다. 
        cursor = new;
    }
}
// 커서를 왼쪽으로 한 칸 옮김 (커서가 문장의 맨 앞이면 무시한다. )
void left()
{
    if (cursor->prev == NULL)
        return;
    else
        cursor = cursor->prev;
}
// 커서를 오른쪽으로 한 칸 옮김 (커서가 문장의 맨 뒤면 무시된다. )
void right()
{
    if (cursor->next == NULL)
        return;
    else
        cursor = cursor->next;
}
// 커서의 위치로 커서에 있는 노드를 삭제해야한다.
void delete()
{
    // 삭제하고 싶은 노드를 가리키는 포인터를 하나 더 만든다.
    node *delete = cursor;
    if (cursor->prev == NULL)
        return;

    else if(cursor -> next == NULL) {
        delete -> prev -> next = delete ->next;
        cursor = cursor -> prev;
        free(delete);
    }
    else
    {
        delete->prev->next = delete->next;
        delete->next->prev = delete->prev;
        cursor = delete->prev;
        free(delete);
    }
}

void printList(node *list)
{
    node *current = list->next;
    while (current != NULL)
    {
        fprintf(stdout, "%c", current->data);
        current = current->next;
    }
}

int main(int argc, char *argv[])
{
    char editor; // 문자열을 입력한다.
    int M;       // 명령어를 입력할 개수를 받아온다.
    list = (node *)malloc(sizeof(node));
    list->next = NULL;                     // 초기화해준다.
    cursor = (node *)malloc(sizeof(node)); // 움직일 커서를 선택한다.
    cursor = list;

    while ((editor = getchar()) != '\n')
        insert(editor);

    scanf("%d", &M); // 명령어를 입력 할 개수를 받기
    getchar();       // 버퍼비우기
    for (int i = 0; i < M; i++)
    {
        scanf("%c", &editor);
        getchar();
        if (editor == 'L')
            left();
        else if (editor == 'D')
            right();
        else if (editor == 'B')
            delete ();
        else if (editor == 'P')
        {
            char item;
            scanf("%c", &item);
            getchar();
            insert(item);
        }
    }

    printList(list);
    return 0;
}