#include <stdio.h>

int main(void){
    int age;
    char name[30] = {0};

    printf("나이 입력해주세요 : ");
    scanf("%d%*c", &age);
    printf("이름 입력해주세요 : ");
    gets(name);

    printf("나이 : %d, 이름 : %s", age, name);

    return 0;
}