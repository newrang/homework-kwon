#include <stdio.h>
#include <stdlib.h>

int main() {
    int numberYear, numberMonth, numberDay;
    char name[50];

    printf("[현재 날짜를 'yyyy-mm-dd' 형식으로 입력하세요]: ");
    scanf("%d-%d-%d", &numberYear, &numberMonth, &numberDay);

    printf("[당신의 이름을 입력하세요]: ");
    scanf("%s", name);
    
    printf("**입력이 정상적으로 처리되었습니다~**\n");

    // 3초 대기 (OS에 따라 명령어 변경 필요)
    #ifdef _WIN32
        system("timeout /t 3 >nul");  // Windows용
        system("cls");  // 화면 지우기
    #else
        system("sleep 3");  // Linux/macOS용
        system("clear");  // 화면 지우기
    #endif
    
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    for (int i = 1; i <= 6; i++) {
        for (int j = 0; j < i; j++) {
            printf("*");
        }
        for (int j = 0; j < 50; j++) {
            printf(" ");
        }
        for (int j = 0; j < 6 - i; j++) {
            printf("*");
        }
        printf("\n");
    }
    
    printf("**                        [마그라테아 ver 0.1]                   **\n");
    printf("***  풀 한 포기 없는 황무지에서 반짝이는 행성을 만드는 곳 마그라테아, ***\n");
    printf("****  사람들이 보지 못하는 잠재력을 찾고 전문가의 손길을 더해 보석을 빗는 곳, ***\n");
    printf("*****   마그라테아에 오신 걸 환영합니다~                         ***\n");
    
    for (int i = 6; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            printf("*");
        }
        for (int j = 0; j < 50; j++) {
            printf(" ");
        }
        for (int j = 0; j < 6 - i; j++) {
            printf("*");
        }
        printf("\n");
    }
    
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("[사용자]: %s\n", name);
    printf("[실행 시간]: %04d-%02d-%02d\n", numberYear, numberMonth, numberDay);
    printf("=============================================================\n");
    
    return 0;
}
