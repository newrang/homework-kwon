#include <stdio.h>
#include <ctype.h>  // toupper()
#include <string.h> // fgets 사용 시 필요

#define MAX_STR 30

// 위치 구조체
typedef struct {
    int x;
    int y;
} Car;

// 자동차 번호 구조체
typedef struct {
    int carNumber;
} CarInfo;

// 자동차 기종 구조체
typedef struct {
    char model[MAX_STR];
} CarModel;

// 자동차 색상 구조체
typedef struct {
    char color[MAX_STR];
} CarColor;

int main() {
    Car car = {0, 0};
    CarInfo info = {0};
    CarModel model = {""};
    CarColor color = {""};
    int targetX = 0, targetY = 0;
    char choice;

    while (1) {
        printf("\n=== 매그라시아 프로그램 ===\n");
        printf("0. 자동차 위치 초기화\n");
        printf("1. 자동차 번호 입력\n");
        printf("2. 차 기종 입력\n");
        printf("3. 차 색상 입력\n");
        printf("4. 목적 좌표 입력 (x, y)\n");
        printf("5. 좌표로 이동 실행\n");
        printf("Q. 종료\n");
        printf("선택 (0~5 또는 Q): ");
        
        scanf(" %c", &choice);
        choice = toupper(choice);

        if (choice == 'Q') {
            printf("프로그램을 종료합니다.\n");
            break;
        }

        switch (choice) {
            case '0':
                car.x = 0;
                car.y = 0;
                printf("자동차 위치가 초기화되었습니다. (0, 0)\n");
                break;

            case '1':
                printf("자동차 번호를 입력하세요: ");
                scanf("%d", &info.carNumber);
                printf("입력된 자동차 번호: %d\n", info.carNumber);
                break;

            case '2':
                printf("자동차 기종을 입력하세요: ");
                scanf(" %[^\n]", model.model);  // 공백 포함 입력
                printf("입력된 기종: %s\n", model.model);
                break;

            case '3':
                printf("자동차 색상을 입력하세요: ");
                scanf(" %[^\n]", color.color);
                printf("입력된 색상: %s\n", color.color);
                break;

            case '4':
                printf("도착할 x 좌표를 입력하세요: ");
                scanf("%d", &targetX);
                printf("도착할 y 좌표를 입력하세요: ");
                scanf("%d", &targetY);
                printf("저장된 도착 좌표: (%d, %d)\n", targetX, targetY);
                break;

            case '5':
                printf("\n--- 이동 시작 ---\n");
                printf("자동차 번호: %d\n", info.carNumber);
                printf("기종: %s\n", model.model);
                printf("색상: %s\n", color.color);
                printf("목표 좌표: (%d, %d)\n", targetX, targetY);

                // x 이동
                while (car.x < targetX) {
                    printf("이동 중... 현재 위치: (%d, %d)\n", car.x, car.y);
                    car.x++;
                }
                while (car.x > targetX) {
                    printf("이동 중... 현재 위치: (%d, %d)\n", car.x, car.y);
                    car.x--;
                }

                // y 이동
                while (car.y < targetY) {
                    printf("이동 중... 현재 위치: (%d, %d)\n", car.x, car.y);
                    car.y++;
                }
                while (car.y > targetY) {
                    printf("이동 중... 현재 위치: (%d, %d)\n", car.x, car.y);
                    car.y--;
                }

                printf("도착! 최종 위치: (%d, %d)\n", car.x, car.y);
                break;

            default:
                printf("잘못된 입력입니다. 다시 선택해주세요.\n");
        }
    }

    return 0;
}
