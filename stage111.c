//stage111은 stage1과 stage11을 업데이트 한 겁니다. 구별하기 위해서 111 로 저장한것 뿐 이고 몰아서 과제를 제출하다보니 구별하기 위해 한 것 뿐입니다.
//입력 방법은 이전 과 같은데 다만 II 하고 나서 엔터를 한 번 더 해야되는 문제가 있고, 
/* (출력하는 방법을 적은겁니다. 아래는 chcp 65001 and gcc stage111.c -o stage111 and stage111 을 하면 터미널창에 출력된것을 보여준 겁니다.)
=== 마그라테아 프로그램 ===
I. 오디션 관리
II. 훈련
III. 데뷔
선택 (I, II, III, 또는 Q 입력 시 종료): II

=== 훈련 메뉴 ===
1. 신체 및 지식 
2. 자기 관리 및 팀워크 
3. 언어 및 발음 
4. 보컬 
5. 댄스 
6. 비주얼 및 이미지
7. 연기 및 무대 퍼포먼스
8. 팬 소통
선택 (1-8, 0 입력 시 메인 메뉴로 돌아가기): 1

=== 신체 및 지식 메뉴 ===
A. 신체 상태 입력 (입력 안 됨)
B. 신체 상태 조회 (조회 불가능)
C. 운동 루틴 설정 (설정 안 됨)
D. 운동 루틴 조회 (조회 불가능)
선택 (A, B, C, D, 또는 0 입력 시 돌아가기):

=== 훈련 메뉴 ===
1. 신체 및 지식
2. 자기 관리 및 팀워크
3. 언어 및 발음
4. 보컬
5. 댄스
6. 비주얼 및 이미지
7. 연기 및 무대 퍼포먼스
8. 팬 소통
선택 (1-8, 0 입력 시 메인 메뉴로 돌아가기): C
잘못된 입력입니다. 1부터 8 사이의 숫자를 입력하거나 0을 입력하여 돌아가세요.

=== 훈련 메뉴 ===
1. 신체 및 지식
2. 자기 관리 및 팀워크
3. 언어 및 발음
4. 보컬
5. 댄스
6. 비주얼 및 이미지
7. 연기 및 무대 퍼포먼스
8. 팬 소통
선택 (1-8, 0 입력 시 메인 메뉴로 돌아가기): 1

=== 신체 및 지식 메뉴 ===
A. 신체 상태 입력 (입력 안 됨)
B. 신체 상태 조회 (조회 불가능)
C. 운동 루틴 설정 (설정 안 됨)
D. 운동 루틴 조회 (조회 불가능)
선택 (A, B, C, D, 또는 0 입력 시 돌아가기): C
멤버 닉네임을 입력하세요: minhyeok
Minhyeok (닉네임: minhyeok)의 운동 루틴을 설정합니다.
--- 월요일 루틴 ---

사용 가능한 운동 유형:
0. 유산소 (달리기, 사이클, 빠르게 걷기)
1. 전신 근력 (팔굽혀펴기, 스쿼트)
2. 하체 근력 (레그 프레스, 레그 컬)
3. 상체 근력 (턱걸이, 친업)
4. 코어 (플랭크, 크런치) (주당 1회만 할당 가능)
운동 유형 번호 (0-4), 'D' 입력 시 오늘 루틴 완료, 'X' 입력 시 오늘 루틴 재입력:00

이렇게 나오면 그냥 엔터치세요. fget 오류같은데 수정해도 안되서 포기했어요. 00 나오면 그냥 엔터해서 입력하시고. 참고로 이거 월요일부터 토요일까지 다 입력해야 D인 운동루틴 조회가 가능합니다.
*/



#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_INPUT 10
#define TRAINING_COUNT 8
#define MAX_MEMBERS 50
#define MAX_NAME 50
#define MAX_NICKNAME 50
#define MAX_HEALTH_INPUT 256
#define TEST_ITEMS 7
#define DAYS_OF_WEEK 6
#define MAX_EXERCISES_PER_DAY 5

char training_status[TRAINING_COUNT] = {0};
int current_training = 0;

typedef struct {
    char name[MAX_NAME];
    char nickname[MAX_NICKNAME];
    char gender;
} Member;

typedef enum {
    MILE_RUN,
    SPRINT,
    PUSHUP,
    SQUAT,
    PULLUP,
    SWIM,
    WEIGHT_LIFT
} TestItem;

char* exercise_types[][MAX_EXERCISES_PER_DAY + 1] = {
    {"Running", "Cycling", "Brisk Walking", NULL},
    {"Push-ups", "Squats", NULL},
    {"Leg Press", "Leg Curl", NULL},
    {"Pull-ups", "Chin-ups", NULL},
    {"Plank", "Crunch", NULL}
};
#define NUM_EXERCISE_TYPES 5

Member milliways_members[MAX_MEMBERS];
double health_scores[MAX_MEMBERS][TEST_ITEMS];
int member_count = 0;

char member_routine[MAX_MEMBERS][DAYS_OF_WEEK][MAX_EXERCISES_PER_DAY][MAX_NAME];

void display_main_menu();
void 오디션_관리();
void training_management();
void debut_management();
void display_training_menu();
void handle_training(int choice);
void evaluate_training(int training_idx);
int is_training_available(int choice);
void display_physical_knowledge_menu();
void setHealth();
double* parseHealthInput(const char* input, int member_idx);
void getHealth();
int findMemberIndex(const char* nickname);
void init_members();
void listMembers();
void setExerciseRoutine();
void getExerciseRoutine();

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void init_members() {
    strcpy(milliways_members[0].name, "John Doe");
    strcpy(milliways_members[0].nickname, "JDoe");
    milliways_members[0].gender = 'M';
    strcpy(milliways_members[1].name, "Jane Smith");
    strcpy(milliways_members[1].nickname, "JSmith");
    milliways_members[1].gender = 'F';
    strcpy(milliways_members[2].name, "Alice Brown");
    strcpy(milliways_members[2].nickname, "ABrown");
    milliways_members[2].gender = 'F';
    strcpy(milliways_members[3].name, "Minhyeok");
    strcpy(milliways_members[3].nickname, "minhyeok");
    milliways_members[3].gender = 'M';
    member_count = 4;

    for (int i = 0; i < MAX_MEMBERS; i++) {
        for (int j = 0; j < TEST_ITEMS; j++) {
            health_scores[i][j] = -1;
        }
        for (int j = 0; j < DAYS_OF_WEEK; j++) {
            for (int k = 0; k < MAX_EXERCISES_PER_DAY; k++) {
                member_routine[i][j][k][0] = '\0';
            }
        }
    }
}

void listMembers() {
    printf("등록된 멤버:\n");
    for (int i = 0; i < member_count; i++) {
        printf("- %s (닉네임: %s)\n", milliways_members[i].name, milliways_members[i].nickname);
    }
}

void display_main_menu() {
    printf("\n=== 마그라테아 프로그램 ===\n");
    printf("I. 오디션 관리\n");
    printf("II. 훈련\n");
    printf("III. 데뷔\n");
    printf("선택 (I, II, III, 또는 Q 입력 시 종료): ");
}

void display_training_menu() {
    printf("\n=== 훈련 메뉴 ===\n");
    printf("1. 신체 및 지식 %s\n", training_status[0] == 'P' ? "(통과)" : training_status[0] == 'F' ? "(실패)" : "");
    printf("2. 자기 관리 및 팀워크 %s\n", training_status[1] == 'P' ? "(통과)" : training_status[1] == 'F' ? "(실패)" : "");
    printf("3. 언어 및 발음 %s\n", training_status[2] == 'P' ? "(통과)" : training_status[2] == 'F' ? "(실패)" : "");
    printf("4. 보컬 %s\n", training_status[3] == 'P' ? "(통과)" : training_status[3] == 'F' ? "(실패)" : "");
    printf("5. 댄스 %s\n", training_status[4] == 'P' ? "(통과)" : training_status[4] == 'F' ? "(실패)" : "");
    printf("6. 비주얼 및 이미지 %s\n", training_status[5] == 'P' ? "(통과)" : training_status[5] == 'F' ? "(실패)" : "");
    printf("7. 연기 및 무대 퍼포먼스 %s\n", training_status[6] == 'P' ? "(통과)" : training_status[6] == 'F' ? "(실패)" : "");
    printf("8. 팬 소통 %s\n", training_status[7] == 'P' ? "(통과)" : training_status[7] == 'F' ? "(실패)" : "");
    printf("선택 (1-8, 0 입력 시 메인 메뉴로 돌아가기): ");
}

void display_physical_knowledge_menu() {
    printf("\n=== 신체 및 지식 메뉴 ===\n");
    int has_health_data = 0;
    for (int i = 0; i < member_count; i++) {
        if (health_scores[i][0] != -1) {
            has_health_data = 1;
            break;
        }
    }
    int has_routine_data = 0;
    for (int i = 0; i < member_count; i++) {
        if (member_routine[i][0][0][0] != '\0') {
            has_routine_data = 1;
            break;
        }
    }
    printf("A. 신체 상태 입력 %s\n", has_health_data ? "(입력됨)" : "(입력 안 됨)");
    printf("B. 신체 상태 조회 %s\n", has_health_data ? "(조회 가능)" : "(조회 불가능)");
    printf("C. 운동 루틴 설정 %s\n", has_routine_data ? "(설정됨)" : "(설정 안 됨)");
    printf("D. 운동 루틴 조회 %s\n", has_routine_data ? "(조회 가능)" : "(조회 불가능)");
    printf("선택 (A, B, C, D, 또는 0 입력 시 돌아가기): ");
}

void 오디션_관리() {
    char temp[MAX_INPUT];
    printf("\n오디션 관리 시스템\n");
    printf("기능 구현 예정입니다.\n");
    printf("Enter 키를 눌러 메인 메뉴로 돌아가세요.\n");
    if (fgets(temp, sizeof(temp), stdin) == NULL) {
        return;
    }
    size_t len = strcspn(temp, "\n");
    if (temp[len] != '\n') {
        clear_input_buffer();
    }
    temp[len] = '\0';
}

void training_management() {
    char input[MAX_INPUT];
    int choice;

    while (1) {
        display_training_menu();
        if (fgets(input, MAX_INPUT, stdin) == NULL) {
            return;
        }
        size_t len = strcspn(input, "\n");
        if (input[len] != '\n') {
            clear_input_buffer();
        }
        input[len] = '\0';

        if (strlen(input) == 0 || strcmp(input, "0") == 0) {
            return;
        }

        if (sscanf(input, "%d", &choice) == 1 && choice >= 1 && choice <= 8) {
            if (is_training_available(choice)) {
                handle_training(choice);
            } else {
                printf("훈련을 진행할 수 없습니다. 필요한 훈련을 먼저 완료하거나, 이미 통과한 훈련입니다.\n");
            }
        } else {
            printf("잘못된 입력입니다. 1부터 8 사이의 숫자를 입력하거나 0을 입력하여 돌아가세요.\n");
        }
    }
}

void handle_training(int choice) {
    if (choice == 1) {
        char input[MAX_INPUT];
        while (1) {
            display_physical_knowledge_menu();
            if (fgets(input, MAX_INPUT, stdin) == NULL) {
                return;
            }
            size_t len = strcspn(input, "\n");
            if (input[len] != '\n') {
                clear_input_buffer();
            }
            input[len] = '\0';

            if (strlen(input) == 0 || strcmp(input, "0") == 0) {
                return;
            }

            if (toupper(input[0]) == 'A') {
                setHealth();
            } else if (toupper(input[0]) == 'B') {
                getHealth();
            } else if (toupper(input[0]) == 'C') {
                setExerciseRoutine();
            } else if (toupper(input[0]) == 'D') {
                getExerciseRoutine();
            } else {
                printf("잘못된 입력입니다. A, B, C, D 중 하나를 입력하거나 0을 입력하여 돌아가세요.\n");
            }
        }
    } else {
        char input[MAX_INPUT];
        printf("평가 결과를 입력하시겠습니까? (Y/N): ");
        if (fgets(input, MAX_INPUT, stdin) == NULL) {
            return;
        }
        size_t len = strcspn(input, "\n");
        if (input[len] != '\n') {
            clear_input_buffer();
        }
        input[len] = '\0';

        if (toupper(input[0]) == 'Y') {
            evaluate_training(choice - 1);
        } else if (toupper(input[0]) == 'N') {
            return;
        } else {
            printf("잘못된 입력입니다. Y 또는 N을 입력하세요.\n");
        }
    }
}

void setHealth() {
    char nickname[MAX_NICKNAME];
    char input[MAX_HEALTH_INPUT];

    printf("멤버 닉네임을 입력하세요: ");
    if (fgets(nickname, MAX_NICKNAME, stdin) == NULL) {
        return;
    }
    size_t len_nick = strcspn(nickname, "\n");
    if (nickname[len_nick] != '\n') {
        clear_input_buffer();
    }
    nickname[len_nick] = '\0';

    int idx = findMemberIndex(nickname);
    if (idx == -1) {
        printf("유효하지 않은 닉네임입니다: %s\n", nickname);
        listMembers();
        return;
    }

    printf("멤버: %s (닉네임: %s)\n", milliways_members[idx].name, milliways_members[idx].nickname);
    printf("건강 데이터를 입력하세요 (쉼표로 구분, 7개 항목):\n");
    printf("1마일 달리기 (분), 단거리 (초), 팔굽혀펴기 (분), 스쿼트 (분), 턱걸이 (분), 수영 (분), 역도 (배수)\n");
    printf("예시: 7.0,11.5,1.8,3.0,2.5,9.5,1.6 (역도: 남성 >= 1.5배, 여성 >= 0.75배)\n");
    if (fgets(input, MAX_HEALTH_INPUT, stdin) == NULL) {
        return;
    }
    size_t len_health = strcspn(input, "\n");
    if (input[len_health] != '\n') {
        clear_input_buffer();
    }
    input[len_health] = '\0';

    double* scores = parseHealthInput(input, idx);
    if (scores == NULL) {
        printf("%s (닉네임: %s)의 입력 파싱에 실패했습니다.\n",
                milliways_members[idx].name, milliways_members[idx].nickname);
    } else {
        printf("%s (닉네임: %s)의 건강 데이터가 저장되었습니다.\n",
                milliways_members[idx].name, milliways_members[idx].nickname);
    }
}

double* parseHealthInput(const char* input, int member_idx) {
    if (strlen(input) == 0) {
        printf("오류: 빈 입력입니다.\n");
        return NULL;
    }

    char* input_copy = strdup(input);
    if (input_copy == NULL) {
        perror("메모리 할당 실패");
        return NULL;
    }

    char* token = strtok(input_copy, ",");
    int i = 0;
    double values[TEST_ITEMS];

    while (token != NULL && i < TEST_ITEMS) {
        while (*token == ' ') token++;
        char* end = token + strlen(token) - 1;
        while (end > token && *end == ' ') *end-- = '\0';

        char* endptr;
        values[i] = strtod(token, &endptr);

        if (endptr == token || *endptr != '\0') {
            printf("입력 위치 %d의 숫자 형식이 유효하지 않습니다: '%s'\n", i + 1, token);
            free(input_copy);
            return NULL;
        }
        i++;
        token = strtok(NULL, ",");
    }

    if (i != TEST_ITEMS) {
        printf("잘못된 입력 형식: %d개 항목이 필요하지만, %d개가 입력되었습니다.\n", TEST_ITEMS, i);
        free(input_copy);
        return NULL;
    }

    if (milliways_members[member_idx].gender == 'M' && values[WEIGHT_LIFT] < 1.5) {
        printf("%s (닉네임: %s) 남성의 역도 점수는 체중의 1.5배 이상이어야 합니다.\n",
                milliways_members[member_idx].name, milliways_members[member_idx].nickname);
        free(input_copy);
        return NULL;
    }
    if (milliways_members[member_idx].gender == 'F' && values[WEIGHT_LIFT] < 0.75) {
        printf("%s (닉네임: %s) 여성의 역도 점수는 체중의 0.75배 이상이어야 합니다.\n",
                milliways_members[member_idx].name, milliways_members[member_idx].nickname);
        free(input_copy);
        return NULL;
    }

    for (int j = 0; j < TEST_ITEMS; j++)
        health_scores[member_idx][j] = values[j];

    free(input_copy);
    return health_scores[member_idx];
}

void getHealth() {
    char input[MAX_INPUT];
    printf("옵션을 선택하세요:\n");
    printf("1. 모든 건강 데이터 조회\n");
    printf("2. 한 멤버의 모든 데이터 조회\n");
    printf("3. 한 멤버의 특정 데이터 조회\n");
    printf("선택 (1-3, 또는 0 입력 시 돌아가기): ");
    if (fgets(input, MAX_INPUT, stdin) == NULL) {
        return;
    }
    size_t len = strcspn(input, "\n");
    if (input[len] != '\n') {
        clear_input_buffer();
    }
    input[len] = '\0';

    if (strcmp(input, "0") == 0) return;

    int choice;
    if (sscanf(input, "%d", &choice) != 1 || choice < 1 || choice > 3) {
        printf("잘못된 선택입니다.\n");
        return;
    }

    if (choice == 1) {
        for (int i = 0; i < member_count; i++) {
            if (health_scores[i][0] == -1) continue;
            printf("\n멤버: %s (닉네임: %s)\n", milliways_members[i].name, milliways_members[i].nickname);
            printf("1마일 달리기: %.2f분, 단거리: %.2f초, 팔굽혀펴기: %.2f분, 스쿼트: %.2f분, 턱걸이: %.2f분, 수영: %.2f분, 역도: %.2f배\n",
                   health_scores[i][MILE_RUN], health_scores[i][SPRINT],
                   health_scores[i][PUSHUP], health_scores[i][SQUAT],
                   health_scores[i][PULLUP], health_scores[i][SWIM],
                   health_scores[i][WEIGHT_LIFT]);
        }
    } else if (choice == 2) {
        char nickname[MAX_NICKNAME];
        printf("멤버 닉네임을 입력하세요: ");
        if (fgets(nickname, MAX_NICKNAME, stdin) == NULL) {
            return;
        }
        size_t len_nick = strcspn(nickname, "\n");
        if (nickname[len_nick] != '\n') {
            clear_input_buffer();
        }
        nickname[len_nick] = '\0';

        int idx = findMemberIndex(nickname);
        if (idx == -1) {
            printf("유효하지 않은 닉네임입니다: %s\n", nickname);
            listMembers();
            return;
        }
        if (health_scores[idx][0] == -1) {
            printf("%s (닉네임: %s)의 건강 데이터가 없습니다.\n",
                    milliways_members[idx].name, milliways_members[idx].nickname);
            return;
        }

        printf("\n멤버: %s (닉네임: %s)\n", milliways_members[idx].name, milliways_members[idx].nickname);
        printf("1마일 달리기: %.2f분, 단거리: %.2f초, 팔굽혀펴기: %.2f분, 스쿼트: %.2f분, 턱걸이: %.2f분, 수영: %.2f분, 역도: %.2f배\n",
               health_scores[idx][MILE_RUN], health_scores[idx][SPRINT],
               health_scores[idx][PUSHUP], health_scores[idx][SQUAT],
               health_scores[idx][PULLUP], health_scores[idx][SWIM],
               health_scores[idx][WEIGHT_LIFT]);
    } else if (choice == 3) {
        char nickname[MAX_NICKNAME];
        printf("멤버 닉네임을 입력하세요: ");
        if (fgets(nickname, MAX_NICKNAME, stdin) == NULL) {
            return;
        }
        size_t len_nick = strcspn(nickname, "\n");
        if (nickname[len_nick] != '\n') {
            clear_input_buffer();
        }
        nickname[len_nick] = '\0';

        int idx = findMemberIndex(nickname);
        if (idx == -1) {
            printf("유효하지 않은 닉네임입니다: %s\n", nickname);
            listMembers();
            return;
        }
        if (health_scores[idx][0] == -1) {
            printf("%s (닉네임: %s)의 건강 데이터가 없습니다.\n",
                    milliways_members[idx].name, milliways_members[idx].nickname);
            return;
        }

        printf("건강 항목을 선택하세요 (1-7):\n");
        printf("1. 1마일 달리기, 2. 단거리, 3. 팔굽혀펴기, 4. 스쿼트, 5. 턱걸이, 6. 수영, 7. 역도\n");
        if (fgets(input, MAX_INPUT, stdin) == NULL) {
            return;
        }
        size_t len = strcspn(input, "\n");
        if (input[len] != '\n') {
            clear_input_buffer();
        }
        input[len] = '\0';

        int item_idx;
        if (sscanf(input, "%d", &item_idx) != 1 || item_idx < 1 || item_idx > 7) {
            printf("유효하지 않은 항목 번호입니다.\n");
            return;
        }
        item_idx--;

        printf("\n멤버: %s (닉네임: %s)\n", milliways_members[idx].name, milliways_members[idx].nickname);
        switch (item_idx) {
            case MILE_RUN: printf("1마일 달리기: %.2f분\n", health_scores[idx][MILE_RUN]); break;
            case SPRINT: printf("단거리: %.2f초\n", health_scores[idx][SPRINT]); break;
            case PUSHUP: printf("팔굽혀펴기: %.2f분\n", health_scores[idx][PUSHUP]); break;
            case SQUAT: printf("스쿼트: %.2f분\n", health_scores[idx][SQUAT]); break;
            case PULLUP: printf("턱걸이: %.2f분\n", health_scores[idx][PULLUP]); break;
            case SWIM: printf("수영: %.2f분\n", health_scores[idx][SWIM]); break;
            case WEIGHT_LIFT: printf("역도: %.2f배\n", health_scores[idx][WEIGHT_LIFT]); break;
        }
    }
}

int findMemberIndex(const char* nickname) {
    for (int i = 0; i < member_count; i++) {
        if (strcmp(milliways_members[i].nickname, nickname) == 0)
            return i;
    }
    return -1;
}

void evaluate_training(int training_idx) {
    char input[MAX_INPUT];
    printf("훈련 인증을 통과했습니까? (P/F): ");
    if (fgets(input, MAX_INPUT, stdin) == NULL) {
        return;
    }
    size_t len = strcspn(input, "\n");
    if (input[len] != '\n') {
        clear_input_buffer();
    }
    input[len] = '\0';

    if (toupper(input[0]) == 'P' || toupper(input[0]) == 'F') {
        training_status[training_idx] = toupper(input[0]);
        if (training_idx < 2 && toupper(input[0]) == 'P') {
            current_training++;
        }
        printf("훈련 %d가 %s으로 표시되었습니다.\n", training_idx + 1, toupper(input[0]) == 'P' ? "통과" : "실패");
    } else {
        printf("잘못된 입력입니다. P 또는 F를 입력하세요.\n");
    }
}

int is_training_available(int choice) {
    int idx = choice - 1;

    if (choice == 1 && training_status[0] == 0) {
        return 1;
    }
    if (choice == 2 && training_status[0] == 'P' && training_status[1] == 0) {
        return 1;
    }
    if (choice >= 3 && training_status[0] == 'P' && training_status[1] == 'P' && training_status[idx] == 0) {
        return 1;
    }
    return 0;
}

void setExerciseRoutine() {
    char nickname[MAX_NICKNAME];
    printf("멤버 닉네임을 입력하세요: ");
    if (fgets(nickname, MAX_NICKNAME, stdin) == NULL) {
        return;
    }
    size_t len_nick = strcspn(nickname, "\n");
    if (nickname[len_nick] != '\n') {
        clear_input_buffer();
    }
    nickname[len_nick] = '\0';

    int member_idx = findMemberIndex(nickname);
    if (member_idx == -1) {
        printf("유효하지 않은 닉네임입니다: %s\n", nickname);
        listMembers();
        return;
    }

    if (member_routine[member_idx][0][0][0] != '\0') {
        printf("죄송합니다. %s (닉네임: %s)의 운동 루틴은 이미 설정되어 수정할 수 없습니다.\n",
               milliways_members[member_idx].name, milliways_members[member_idx].nickname);
        return;
    }

    printf("\n%s (닉네임: %s)의 운동 루틴을 설정합니다.\n", milliways_members[member_idx].name, milliways_members[member_idx].nickname);

    char* days[] = {"월요일", "화요일", "수요일", "목요일", "금요일", "토요일"};
    int core_exercise_assigned_this_week = 0;

    for (int day_idx = 0; day_idx < DAYS_OF_WEEK; day_idx++) {
        printf("\n--- %s 루틴 ---\n", days[day_idx]);
        int cardio_selected_for_day = 0;
        int strength_or_core_selected_for_day = 0;
        int current_exercises_count = 0;
        int core_chosen_for_this_day = 0;

        for (int i = 0; i < MAX_EXERCISES_PER_DAY; i++) {
            member_routine[member_idx][day_idx][i][0] = '\0';
        }

        while (1) {
            printf("\n사용 가능한 운동 유형:\n");
            printf("0. 유산소 (달리기, 사이클, 빠르게 걷기)\n");
            printf("1. 전신 근력 (팔굽혀펴기, 스쿼트)\n");
            printf("2. 하체 근력 (레그 프레스, 레그 컬)\n");
            printf("3. 상체 근력 (턱걸이, 친업)\n");
            printf("4. 코어 (플랭크, 크런치) (주당 1회만 할당 가능)\n");
            printf("운동 유형 번호 (0-4), 'D' 입력 시 오늘 루틴 완료, 'X' 입력 시 오늘 루틴 재입력: ");

            char input_str[MAX_INPUT];
            
            if (fgets(input_str, MAX_INPUT, stdin) == NULL) {
                printf("입력 오류가 발생했습니다.\n");
                return;
            }
            size_t len = strcspn(input_str, "\n");
            if (input_str[len] != '\n') {
                clear_input_buffer();
            }
            input_str[len] = '\0';

            if (strlen(input_str) == 0) {
                printf("입력이 없습니다. 다시 입력해 주세요.\n");
                continue;
            }

            // 첫 번째 문자를 기준으로 판단
            char first_char = toupper(input_str[0]);

            if (first_char == 'D') {
                if (cardio_selected_for_day && strength_or_core_selected_for_day) {
                    if (core_chosen_for_this_day) {
                        core_exercise_assigned_this_week = 1;
                    }
                    printf("%s 루틴이 완료되었습니다.\n", days[day_idx]);
                    break;
                } else {
                    printf("오류: 각 요일 루틴에는 최소 하나의 유산소 운동과 하나의 근력/코어 운동이 포함되어야 합니다.\n");
                    continue;
                }
            } else if (first_char == 'X') {
                printf("%s의 모든 운동을 다시 입력합니다.\n", days[day_idx]);
                cardio_selected_for_day = 0;
                strength_or_core_selected_for_day = 0;
                current_exercises_count = 0;
                core_chosen_for_this_day = 0;
                for (int i = 0; i < MAX_EXERCISES_PER_DAY; i++) {
                    member_routine[member_idx][day_idx][i][0] = '\0';
                }
                continue;
            } else if (isdigit(first_char)) { // 첫 문자가 숫자인 경우
                int type_choice = first_char - '0'; // 첫 문자만 숫자로 변환

                if (type_choice >= 0 && type_choice < NUM_EXERCISE_TYPES) {
                    if (current_exercises_count >= MAX_EXERCISES_PER_DAY) {
                        printf("하루 최대 운동 개수(%d개)에 도달했습니다. 오늘 루틴을 확정('D')하거나 다시 입력('X')하세요.\n", MAX_EXERCISES_PER_DAY);
                        continue;
                    }

                    if (type_choice == 4) {
                        if (core_exercise_assigned_this_week && !core_chosen_for_this_day) {
                            printf("코어 운동은 이번 주 다른 요일에 이미 할당되었습니다. 다시 할당할 수 없습니다.\n");
                            continue;
                        }
                        core_chosen_for_this_day = 1;
                    }

                    printf("  유형 %d의 운동 목록:\n", type_choice);
                    int exercise_num = 1;
                    while (exercise_types[type_choice][exercise_num - 1] != NULL) {
                        printf("  %d. %s\n", exercise_num, exercise_types[type_choice][exercise_num - 1]);
                        exercise_num++;
                    }
                    printf("  %s 운동 번호를 입력하세요 (0 입력 시 이 유형 건너뛰기): ",
                           (type_choice == 0 ? "유산소" :
                            type_choice == 1 ? "전신 근력" :
                            type_choice == 2 ? "하체 근력" :
                            type_choice == 3 ? "상체 근력" :
                            "코어"));
                    
                    char specific_exercise_input[MAX_INPUT];
                    if (fgets(specific_exercise_input, MAX_INPUT, stdin) == NULL) {
                        printf("입력 오류가 발생했습니다.\n");
                        return;
                    }
                    size_t len_specific = strcspn(specific_exercise_input, "\n");
                    if (specific_exercise_input[len_specific] != '\n') {
                        clear_input_buffer();
                    }
                    specific_exercise_input[len_specific] = '\0';

                    // 세부 운동 번호도 첫 번째 문자만 숫자로 변환
                    if (strlen(specific_exercise_input) == 0 || !isdigit(specific_exercise_input[0])) {
                        printf("유효하지 않은 입력입니다. 숫자를 입력하세요.\n");
                        continue;
                    }
                    int specific_exercise_choice = specific_exercise_input[0] - '0';

                    if (specific_exercise_choice > 0 && specific_exercise_choice < exercise_num) {
                        strcpy(member_routine[member_idx][day_idx][current_exercises_count], exercise_types[type_choice][specific_exercise_choice - 1]);
                        current_exercises_count++;

                        if (type_choice == 0) cardio_selected_for_day = 1;
                        if (type_choice >= 1 && type_choice <= 4) strength_or_core_selected_for_day = 1;
                        printf("추가됨: %s\n", exercise_types[type_choice][specific_exercise_choice - 1]);
                    } else if (specific_exercise_choice != 0) {
                        printf("유형 %d에 대한 유효하지 않은 운동 번호입니다. 이 운동을 건너뜁니다.\n", type_choice);
                    }
                } else {
                    printf("잘못된 입력입니다. 0에서 %d 사이의 숫자를 입력하거나, 'D' 또는 'X'를 입력하세요.\n", NUM_EXERCISE_TYPES - 1);
                }
            } else { // 첫 문자가 숫자나 'D', 'X'가 아닌 경우
                printf("잘못된 입력입니다. 0에서 %d 사이의 숫자를 입력하거나, 'D' 또는 'X'를 입력하세요.\n", NUM_EXERCISE_TYPES - 1);
            }
        }
    }
    printf("%s (닉네임: %s)의 운동 루틴이 설정되었습니다.\n", milliways_members[member_idx].name, milliways_members[member_idx].nickname);
}

void getExerciseRoutine() {
    char nickname[MAX_NICKNAME];
    printf("멤버 닉네임을 입력하세요: ");
    if (fgets(nickname, MAX_NICKNAME, stdin) == NULL) {
        return;
    }
    size_t len_nick = strcspn(nickname, "\n");
    if (nickname[len_nick] != '\n') {
        clear_input_buffer();
    }
    nickname[len_nick] = '\0';

    int member_idx = findMemberIndex(nickname);
    if (member_idx == -1) {
        printf("유효하지 않은 닉네임입니다: %s\n", nickname);
        listMembers();
        return;
    }

    printf("\n--- %s (닉네임: %s)의 운동 루틴 ---\n", milliways_members[member_idx].name, milliways_members[member_idx].nickname);

    char* days[] = {"월요일", "화요일", "수요일", "목요일", "금요일", "토요일"};

    int routine_exists = 0;
    for (int day_idx = 0; day_idx < DAYS_OF_WEEK; day_idx++) {
        if (member_routine[member_idx][day_idx][0][0] != '\0') {
            routine_exists = 1;
            break;
        }
    }

    if (!routine_exists) {
        printf("이 멤버의 운동 루틴이 아직 설정되지 않았습니다.\n");
        return;
    }

    for (int day_idx = 0; day_idx < DAYS_OF_WEEK; day_idx++) {
        printf("%s: ", days[day_idx]);
        int exercises_found = 0;
        for (int i = 0; i < MAX_EXERCISES_PER_DAY; i++) {
            if (member_routine[member_idx][day_idx][i][0] != '\0') {
                printf("%s", member_routine[member_idx][day_idx][i]);
                exercises_found = 1;
                if (member_routine[member_idx][day_idx][i+1][0] != '\0') {
                    printf(", ");
                }
            }
        }
        if (!exercises_found) {
            printf("계획된 운동 없음.");
        }
        printf("\n");
    }
}

void debut_management() {
    char temp[MAX_INPUT];
    printf("\n데뷔 관리 시스템\n");
    printf("기능 구현 예정입니다.\n");
    printf("Enter 키를 눌러 메인 메뉴로 돌아가세요.\n");
    if (fgets(temp, sizeof(temp), stdin) == NULL) {
        return;
    }
    size_t len = strcspn(temp, "\n");
    if (temp[len] != '\n') {
        clear_input_buffer();
    }
    temp[len] = '\0';
}

int main() {
    char input[MAX_INPUT];
    init_members();

    while (1) {
        display_main_menu();
        if (fgets(input, MAX_INPUT, stdin) == NULL) {
            return 1;
        }
        size_t len = strcspn(input, "\n");
        if (input[len] != '\n') {
            clear_input_buffer();
        }
        input[len] = '\0';

        if (strlen(input) == 0 || strcmp(input, "0") == 0 || toupper(input[0]) == 'Q') {
            printf("마그라테아 프로그램을 종료합니다.\n");
            break;
        }

        if (strcmp(input, "I") == 0 || strcmp(input, "i") == 0) {
            오디션_관리();
        } else if (strcmp(input, "II") == 0 || strcmp(input, "ii") == 0) {
            training_management();
        } else if (strcmp(input, "III") == 0 || strcmp(input, "iii") == 0) {
            debut_management();
        } else {
            printf("잘못된 입력입니다. I, II, III 중 하나를 입력하거나 Q를 입력하여 종료하세요.\n");
        }
    }

    return 0;
}
