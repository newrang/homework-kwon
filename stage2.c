/* (터미널 창에 입력하는 방법에 대해서 적은 주석입니다.)
=== 매그라시아 프로그램 ===
I. 오디션 관리
II. 훈련
III. 데뷔
선택 (I, II, III 또는 Q 종료): II

=== 훈련 메뉴 ===
1. 체력 및 지식
2. 자기관리와 팀워크
3. 어학 및 발음
4. 보컬
5. 댄스
6. 비주얼 및 이미지
7. 연기 및 무대 퍼포먼스
8. 팬 소통
선택 (1-8, 0 메인 메뉴로 돌아가기): 1
평가 결과를 입력하시겠습니까? (Y/N): Y
훈련 인증을 통과했습니까? (P/F): P
훈련 1가 통과으로 표시되었습니다.

=== 훈련 메뉴 ===
1. 체력 및 지식 (통과)
2. 자기관리와 팀워크
3. 어학 및 발음
4. 보컬
5. 댄스
6. 비주얼 및 이미지
7. 연기 및 무대 퍼포먼스
8. 팬 소통
선택 (1-8, 0 메인 메뉴로 돌아가기): 2

--- 자기관리와 팀워크 서브 메뉴 ---
A. 멘토링
B. 기타 팀워크 활동 (미정)
선택 (A, B, 또는 0 훈련 메뉴로 돌아가기): A
등록된 멘토가 없습니다. 지금 멘토를 등록하시겠습니까? (Y/N): Y

--- 멘토 등록 ---
최대 8명의 멘토를 등록할 수 있습니다.
멘토 1의 이름 입력 (종료하려면 'done' 입력): 1
멘토 2의 이름 입력 (종료하려면 'done' 입력): 2
멘토 3의 이름 입력 (종료하려면 'done' 입력): 3
멘토 4의 이름 입력 (종료하려면 'done' 입력): 4
멘토 5의 이름 입력 (종료하려면 'done' 입력): 5
멘토 6의 이름 입력 (종료하려면 'done' 입력): 6
멘토 7의 이름 입력 (종료하려면 'done' 입력): 7
멘토 8의 이름 입력 (종료하려면 'done' 입력): 8
8명의 멘토가 성공적으로 등록되었습니다.

경고: 모든 연습생(10명)을 위한 멘토(8명)가 충분하지 않습니다. 일부 연습생은 매칭 되지 않을 수 있습니다.

--- 연습생에게 멘토 할당 중 ---
연습생 Agrajag는 멘토와 매칭될 수 없습니다 (모든 멘토가 할당됨).
연습생 Marvin는 멘토와 매칭될 수 없습니다 (모든 멘토가 할당됨).

--- 멘토링 할당 ---
멘토 ID: 1, 멘토 이름: 1 => 연습생: Krikkit (ID: 729)
멘토 ID: 2, 멘토 이름: 2 => 연습생: DeepThought (ID: 1121)
멘토 ID: 3, 멘토 이름: 3 => 연습생: Arthur (ID: 630)
멘토 ID: 4, 멘토 이름: 4 => 연습생: Trillian (ID: 831)
멘토 ID: 5, 멘토 이름: 5 => 연습생: Zaphod (ID: 614)
멘토 ID: 6, 멘토 이름: 6 => 연습생: Slartibartfast (ID: 1478)
멘토 ID: 7, 멘토 이름: 7 => 연습생: Ford (ID: 395)
멘토 ID: 8, 멘토 이름: 8 => 연습생: Gargravarr (ID: 1039)
Enter 키를 눌러 계속합니다.
  
*/

//아래는 코드입니다.

#include <stdio.h>    // printf, fgets, stdin, getchar
#include <string.h>   // strlen, strcmp
#include <ctype.h>    // toupper
#include <stdlib.h>   // srand, rand, NULL (for some compilers, though often in stdio.h or stddef.h)
#include <time.h>     // time

#define MAX_INPUT 10
#define TRAINING_COUNT 8
#define MAX_TRAINEES 10 // 이전 문맥을 바탕으로 연습생 10명으로 가정합니다.
#define MAX_MENTORS 8

// 훈련 현황을 추적하는 배열
char training_status[TRAINING_COUNT] = {0}; // 0: 시도 안 함, P: 통과, F: 실패
int current_training = 0; // 순차적 훈련(1번, 2번)의 진행 상황을 추적합니다.

// 연습생 데이터
char *mill_trainee_nicknames[MAX_TRAINEES] = {
    "Zaphod", "Ford", "Arthur", "Trillian", "Marvin",
    "Slartibartfast", "Agrajag", "Gargravarr", "Krikkit", "DeepThought"
};
int trainee_parsed_ids[MAX_TRAINEES];
int trainee_abilities[MAX_TRAINEES];

// 멘토 구조체
typedef struct {
    int id;
    char name[50];
    int matched_trainee_idx; // -1이면 매칭되지 않음, 그 외에는 연습생의 인덱스
} Mentor;

Mentor mentors[MAX_MENTORS];
int mentor_count = 0;

// 함수 원형들 (main 함수보다 먼저 선언되어야 합니다)
void display_main_menu();
void 오디션_관리();
void training_management();
void debut_management();
void display_training_menu();
void handle_training(int choice);
void evaluate_training(int training_idx);
int is_training_available(int choice);

// 연습생 및 멘토 관리를 위한 새로운 함수들
int parseIntMember(const char *nickname);
int getRandomAbility();
void initialize_trainee_data();
void input_mentor_data();
void matchMentoring();
void assign_mentors();
void display_matched_mentors();

// 메인 메뉴 함수
void display_main_menu() {
    printf("\n=== 매그라시아 프로그램 ===\n");
    printf("I. 오디션 관리\n");
    printf("II. 훈련\n");
    printf("III. 데뷔\n");
    printf("선택 (I, II, III 또는 Q 종료): ");
}

// 훈련 메뉴 함수
void display_training_menu() {
    printf("\n=== 훈련 메뉴 ===\n");
    printf("1. 체력 및 지식 %s\n", training_status[0] == 'P' ? "(통과)" : training_status[0] == 'F' ? "(실패)" : "");
    printf("2. 자기관리와 팀워크 %s\n", training_status[1] == 'P' ? "(통과)" : training_status[1] == 'F' ? "(실패)" : "");
    printf("3. 어학 및 발음 %s\n", training_status[2] == 'P' ? "(통과)" : training_status[2] == 'F' ? "(실패)" : "");
    printf("4. 보컬 %s\n", training_status[3] == 'P' ? "(통과)" : training_status[3] == 'F' ? "(실패)" : "");
    printf("5. 댄스 %s\n", training_status[4] == 'P' ? "(통과)" : training_status[4] == 'F' ? "(실패)" : "");
    printf("6. 비주얼 및 이미지 %s\n", training_status[5] == 'P' ? "(통과)" : training_status[5] == 'F' ? "(실패)" : "");
    printf("7. 연기 및 무대 퍼포먼스 %s\n", training_status[6] == 'P' ? "(통과)" : training_status[6] == 'F' ? "(실패)" : "");
    printf("8. 팬 소통 %s\n", training_status[7] == 'P' ? "(통과)" : training_status[7] == 'F' ? "(실패)" : "");
    printf("선택 (1-8, 0 메인 메뉴로 돌아가기): ");
}

// 오디션 관리 함수
void 오디션_관리() {
    printf("\n오디션 관리 시스템\n");
    printf("기능은 구현될 예정입니다.\n");
    printf("Enter 키를 눌러 메인 메뉴로 돌아갑니다.\n");
    while (getchar() != '\n'); // 입력 버퍼 비우기
    getchar(); // Enter 키 대기
}

// 훈련 관리 함수
void training_management() {
    char input[MAX_INPUT];
    int choice;

    while (1) {
        display_training_menu();
        fgets(input, MAX_INPUT, stdin);
        if (strlen(input) > 0 && input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0';
        }

        if (strlen(input) == 0 || strcmp(input, "0") == 0) {
            while (getchar() != '\n'); // 입력 버퍼 비우기
            return; // 메인 메뉴로 돌아가기
        }

        if (sscanf(input, "%d", &choice) == 1 && choice >= 1 && choice <= 8) {
            if (is_training_available(choice)) {
                if (choice == 2) { // 자기관리와 팀워크
                    char sub_input[MAX_INPUT];
                    printf("\n--- 자기관리와 팀워크 서브 메뉴 ---\n");
                    printf("A. 멘토링\n");
                    printf("B. 기타 팀워크 활동 (미정)\n");
                    printf("선택 (A, B, 또는 0 훈련 메뉴로 돌아가기): ");
                    fgets(sub_input, MAX_INPUT, stdin);
                    if (strlen(sub_input) > 0 && sub_input[strlen(sub_input) - 1] == '\n') {
                        sub_input[strlen(sub_input) - 1] = '\0';
                    }

                    if (toupper(sub_input[0]) == 'A') {
                        matchMentoring();
                    } else if (toupper(sub_input[0]) == 'B') {
                        printf("기타 팀워크 활동 기능은 구현될 예정입니다.\n");
                    } else if (strcmp(sub_input, "0") == 0) {
                        // 훈련 메뉴로 돌아가기, 버퍼는 fgets에 의해 이미 비워졌습니다.
                    } else {
                        printf("잘못된 입력입니다. A, B 또는 0을 입력하세요.\n");
                    }
                    while (getchar() != '\n'); // 서브 메뉴 후 입력 버퍼 비우기
                } else {
                    handle_training(choice);
                }
            } else {
                printf("훈련을 이용할 수 없습니다. 필요한 훈련을 먼저 완료하거나 이미 통과한 훈련입니다.\n");
            }
        } else {
            printf("잘못된 입력입니다. 1에서 8 사이의 숫자를 입력하거나 0을 입력하여 돌아가세요.\n");
        }
        while (getchar() != '\n'); // 각 반복 후 입력 버퍼 비우기
    }
}

// 데뷔 관리 함수
void debut_management() {
    printf("\n데뷔 관리 시스템\n");
    printf("기능은 구현될 예정입니다.\n");
    printf("Enter 키를 눌러 메인 메뉴로 돌아갑니다.\n");
    while (getchar() != '\n'); // 입력 버퍼 비우기
    getchar();
}

// 훈련이 가능한지 확인
int is_training_available(int choice) {
    int idx = choice - 1;
    // 1번과 2번 훈련은 순차적으로 진행해야 합니다.
    if (choice == 1 && training_status[0] == 0) {
        return 1;
    }
    if (choice == 2 && training_status[0] == 'P' && training_status[1] == 0) {
        return 1;
    }
    // 3번-8번 훈련은 1번과 2번이 통과되어야 합니다.
    if (choice >= 3 && training_status[0] == 'P' && training_status[1] == 'P' && training_status[idx] == 0) {
        return 1;
    }
    return 0;
}

// 훈련 선택 처리
void handle_training(int choice) {
    char input[MAX_INPUT];
    printf("평가 결과를 입력하시겠습니까? (Y/N): ");
    fgets(input, MAX_INPUT, stdin);
    if (strlen(input) > 0 && input[strlen(input) - 1] == '\n') {
        input[strlen(input) - 1] = '\0';
    }

    if (toupper(input[0]) == 'Y') {
        evaluate_training(choice - 1);
    } else if (toupper(input[0]) == 'N') {
        // 훈련 메뉴로 돌아가기
        return;
    } else {
        printf("잘못된 입력입니다. Y 또는 N을 입력하세요.\n");
    }
}

// 훈련 평가
void evaluate_training(int training_idx) {
    char input[MAX_INPUT];
    printf("훈련 인증을 통과했습니까? (P/F): ");
    fgets(input, MAX_INPUT, stdin);
    if (strlen(input) > 0 && input[strlen(input) - 1] == '\n') {
        input[strlen(input) - 1] = '\0';
    }

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

// --- 새로운 함수 구현 ---

// 연습생 닉네임을 ASCII 값의 합으로 정수 변환
int parseIntMember(const char *nickname) {
    int sum = 0;
    int i;
    for (i = 0; i < strlen(nickname); i++) {
        sum += (int)nickname[i];
    }
    return sum;
}

// 100에서 1000 사이의 무작위 능력치 생성
int getRandomAbility() {
    return (rand() % 901) + 100; // 0에서 900 사이의 숫자를 생성한 다음 100을 더합니다.
}

// 연습생 데이터 초기화 (변환된 ID와 무작위 능력치)
void initialize_trainee_data() {
    int i;
    for (i = 0; i < MAX_TRAINEES; i++) {
        trainee_parsed_ids[i] = parseIntMember(mill_trainee_nicknames[i]);
        trainee_abilities[i] = getRandomAbility();
    }
}

// 사용자로부터 멘토 데이터 입력받기
void input_mentor_data() {
    char input[MAX_INPUT];
    int i;

    printf("\n--- 멘토 등록 ---\n");
    printf("최대 %d명의 멘토를 등록할 수 있습니다.\n", MAX_MENTORS);

    for (i = 0; i < MAX_MENTORS; i++) {
        printf("멘토 %d의 이름 입력 (종료하려면 'done' 입력): ", i + 1);
        fgets(mentors[i].name, sizeof(mentors[i].name), stdin);
        if (strlen(mentors[i].name) > 0 && mentors[i].name[strlen(mentors[i].name) - 1] == '\n') {
            mentors[i].name[strlen(mentors[i].name) - 1] = '\0';
        }

        if (strcmp(mentors[i].name, "done") == 0 || strcmp(mentors[i].name, "DONE") == 0) {
            break;
        }

        mentors[i].id = i + 1; // 1부터 8까지의 고유 ID 할당
        mentors[i].matched_trainee_idx = -1; // 매칭되지 않은 상태로 초기화
        mentor_count++;
    }
    if (mentor_count == 0) {
        printf("등록된 멘토가 없습니다.\n");
    } else {
        printf("%d명의 멘토가 성공적으로 등록되었습니다.\n", mentor_count);
    }
    while (getchar() != '\n'); // 입력 버퍼 비우기
}

// 멘토링 매칭 과정 처리
void matchMentoring() {
    if (mentor_count == 0) {
        char input[MAX_INPUT];
        printf("등록된 멘토가 없습니다. 지금 멘토를 등록하시겠습니까? (Y/N): ");
        fgets(input, MAX_INPUT, stdin);
        if (strlen(input) > 0 && input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0';
        }

        if (toupper(input[0]) == 'Y') {
            input_mentor_data();
            if (mentor_count == 0) {
                printf("등록된 멘토 없이는 멘토링을 진행할 수 없습니다.\n");
                return;
            }
        } else {
            printf("멘토링이 취소되었습니다. 매칭할 멘토가 없습니다.\n");
            return;
        }
    }

    if (mentor_count < MAX_TRAINEES) {
        printf("경고: 모든 연습생(%d명)을 위한 멘토(%d명)가 충분하지 않습니다. 일부 연습생은 매칭되지 않을 수 있습니다.\n", MAX_TRAINEES, mentor_count);
    }

    printf("\n--- 연습생에게 멘토 할당 중 ---\n");
    assign_mentors();
    display_matched_mentors();
    printf("Enter 키를 눌러 계속합니다.\n");
    while (getchar() != '\n'); // 입력 버퍼 비우기
    getchar();
}

// 사용 가능한 멘토에 대해 1:1 보장을 통해 멘토를 연습생에게 할당
void assign_mentors() {
    int i;
    int trainee_indices[MAX_TRAINEES];
    int mentor_available[MAX_MENTORS];

    // 섞기(셔플)를 위해 연습생 인덱스 초기화
    for (i = 0; i < MAX_TRAINEES; i++) {
        trainee_indices[i] = i;
    }

    // 모든 멘토를 사용 가능 및 매칭되지 않은 상태로 초기화
    for (i = 0; i < mentor_count; i++) {
        mentors[i].matched_trainee_idx = -1;
        mentor_available[i] = 1; // 1은 사용 가능, 0은 할당됨
    }

    // 매칭을 무작위화하기 위해 연습생 인덱스 섞기
    for (i = 0; i < MAX_TRAINEES; i++) {
        int j = rand() % MAX_TRAINEES;
        int temp = trainee_indices[i];
        trainee_indices[i] = trainee_indices[j];
        trainee_indices[j] = temp;
    }

    // 연습생을 멘토에게 할당
    for (i = 0; i < MAX_TRAINEES; i++) {
        int trainee_idx = trainee_indices[i];
        int target_mentor_id = (trainee_idx % mentor_count) + 1; // ID를 기반으로 연습생을 멘토에 매핑 (1부터 시작)

        // 대상 ID를 가진 멘토 찾기
        int assigned = 0;
        int k;
        for (k = 0; k < mentor_count; k++) {
            if (mentors[k].id == target_mentor_id && mentor_available[k]) {
                mentors[k].matched_trainee_idx = trainee_idx;
                mentor_available[k] = 0; // 멘토를 사용 불가로 표시
                assigned = 1;
                break;
            }
        }

        // 직접 할당에 실패한 경우 (멘토가 이미 배정된 경우), 다음 사용 가능한 멘토를 찾습니다.
        if (!assigned) {
            for (k = 0; k < mentor_count; k++) {
                if (mentor_available[k]) {
                    mentors[k].matched_trainee_idx = trainee_idx;
                    mentor_available[k] = 0;
                    assigned = 1;
                    break;
                }
            }
        }
        // 여전히 할당되지 않은 경우 (모든 멘토가 할당되었고 더 많은 연습생이 있는 경우에만 발생해야 함)
        if (!assigned) {
             printf("연습생 %s는 멘토와 매칭될 수 없습니다 (모든 멘토가 할당됨).\n", mill_trainee_nicknames[trainee_idx]);
        }
    }
}


// 매칭된 연습생과 멘토 출력
void display_matched_mentors() {
    int i;
    printf("\n--- 멘토링 할당 ---\n");
    if (mentor_count == 0) {
        printf("등록된 멘토가 없어 할당을 표시할 수 없습니다.\n");
        return;
    }

    for (i = 0; i < mentor_count; i++) {
        if (mentors[i].matched_trainee_idx != -1) {
            printf("멘토 ID: %d, 멘토 이름: %s => 연습생: %s (ID: %d)\n",
                   mentors[i].id, mentors[i].name,
                   mill_trainee_nicknames[mentors[i].matched_trainee_idx],
                   trainee_parsed_ids[mentors[i].matched_trainee_idx]);
        } else {
            printf("멘토 ID: %d, 멘토 이름: %s => 할당된 연습생 없음\n",
                   mentors[i].id, mentors[i].name);
        }
    }
}

// 메인 함수
int main() {
    char input[MAX_INPUT];
    srand((unsigned int)time(NULL)); // 난수 생성기 시드 설정

    initialize_trainee_data(); // 시작 시 연습생 데이터 초기화

    while (1) {
        display_main_menu();
        fgets(input, MAX_INPUT, stdin);
        if (strlen(input) > 0 && input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0';
        }

        // 종료 조건 확인
        if (strlen(input) == 0 || strcmp(input, "0") == 0 || toupper(input[0]) == 'Q') {
            printf("매그라시아 프로그램을 종료합니다.\n");
            break;
        }

        // 메인 메뉴 선택 처리
        if (strcmp(input, "I") == 0 || strcmp(input, "i") == 0) {
            오디션_관리();
        } else if (strcmp(input, "II") == 0 || strcmp(input, "ii") == 0) {
            training_management();
        } else if (strcmp(input, "III") == 0 || strcmp(input, "iii") == 0) { // 이 줄이 수정되었습니다.
            debut_management();
        } else {
            printf("잘못된 입력입니다. I, II, III 또는 Q를 입력하여 종료하세요.\n");
        }
    }

    return 0;
}
