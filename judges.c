#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[30];
    char gender[10];
    char enter[50];
    char job[30];
    char pro[30];
    char mail[70];
    char number[80];
} Judge;

// 문자열 입력 함수: 공백 포함해서 입력받고 줄바꿈 제거
void input(char* prompt, char* buffer, int size) {
    printf("%s", prompt);
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // 개행 문자 제거
}

int main(void) {
    Judge judges[5]; // 5명의 심사위원 정보 저장
    char yn; // Y/N 입력
    int i = 0;

    // 심사위원 정보 입력
    printf("####################################\n");
    printf("#      심사위원 명단 데이터 입력       #\n");
    printf("####################################\n");
    printf("> 참여 프로젝트: 밀리웨이즈\n");
    printf("> 심사 총 인원: 5\n");
    printf("> 선발 멤버 수: 4\n");
    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("5명의 심사위원 정보 입력을 시작합니다.\n");
    printf("++++++++++++++++++++++++++++++++++++\n");

    while (i < 5) {
        printf("\n[%d번 심사위원]\n", i + 1);

        input("이름: ", judges[i].name, sizeof(judges[i].name));
        input("성별: ", judges[i].gender, sizeof(judges[i].gender));
        input("소속: ", judges[i].enter, sizeof(judges[i].enter));
        input("직업: ", judges[i].job, sizeof(judges[i].job));
        input("전문분야: ", judges[i].pro, sizeof(judges[i].pro));
        input("이메일: ", judges[i].mail, sizeof(judges[i].mail));
        input("전화번호: ", judges[i].number, sizeof(judges[i].number));

        i++;
    }

    // 사용자에게 출력 여부 확인
    printf("\n[PROJECT] 심사위원 정보를 확인할까요? Y/N: ");
    scanf(" %c", &yn);
    getchar(); // 버퍼에 남은 개행 제거

    if (yn == 'N' || yn == 'n') {
        printf("프로그램을 종료합니다.\n");
        return 0;
    } else if (yn == 'Y' || yn == 'y') {
        // 출력
        printf("\n####################################\n");
        printf("#        심사위원 데이터 출력        #\n");
        printf("####################################\n");

        for (i = 0; i < 5; i++) {
            printf("[심사위원 %d]\n", i + 1);
            printf("이름: %s\n", judges[i].name);
            printf("성별: %s\n", judges[i].gender);
            printf("소속: %s\n", judges[i].enter);
            printf("직함: %s\n", judges[i].job);
            printf("전문분야: %s\n", judges[i].pro);
            printf("메일: %s\n", judges[i].mail);
            printf("전화: %s\n", judges[i].number);
            printf("-----------------------------------\n");
        }
    } else {
        printf("잘못된 입력입니다. 프로그램을 종료합니다.\n");
    }

    return 0;
}
