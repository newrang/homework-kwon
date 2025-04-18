#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[30];
    char gender[4];
    char enter[50];
    char job[30];
    char pro[10];
    char mail[70];
    char number[80];
} Judge;

int main(void) {
    Judge judges[5]; // 5명의 심사위원 정보 저장
    char yn; // Y/N 입력
    int i = 0;

    // 심사위원 정보 입력
    while (i < 5) {
        printf("####################################\n");
        printf("#      심사위원 명단 데이터 입력       #\n");
        printf("####################################\n");
        printf("> 참여 프로젝트: 밀리웨이즈\n");
        printf("> 심사 총 인원: 5\n");
        printf("> 선발 멤버 수: 4\n");
        printf("++++++++++++++++++++++++++++++++++++\n");
        printf("5명의 심사위원 정보 입력을 시작합니다.\n");
        printf("++++++++++++++++++++++++++++++++++++\n");

        printf("[%d번 심사위원]\n", i + 1);

        printf("이름: "); scanf("%s", judges[i].name);
        printf("성별: "); scanf("%s", judges[i].gender);
        printf("소속: "); scanf("%s", judges[i].enter);
        printf("직업: "); scanf("%s", judges[i].job);
        printf("전문분야: "); scanf("%s", judges[i].pro);
        printf("이메일: "); scanf("%s", judges[i].mail);
        printf("전화번호: "); scanf("%s", judges[i].number);

        i++;
        printf("\n");
    }

    // 사용자에게 출력 여부 확인
    printf("[PROJECT] 심사위원 정보를 확인할까요? Y/N: ");
    scanf(" %c", &yn); // 공백으로 이전 입력 제거

    if (yn == 'N') {
        printf("프로그램을 종료합니다.\n");
        return 0;
    } else if (yn == 'Y') {
        // 예쁜 출력
        printf("####################################\n");
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
