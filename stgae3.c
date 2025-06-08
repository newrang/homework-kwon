//아래 문서는 터미널창을 복붙한 겁니다. 보면서 따라 하면 됩니다. 참고로 II에서 훈련메뉴 1 통과후 2는 스킵하기 위해 0 Y P를 만들었습니다.
/*
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
B. 트라우마 관리
선택 (A, B, 또는 0 훈련 메뉴로 돌아가기): 0
평가 결과를 입력하시겠습니까? (Y/N): Y
훈련 인증을 통과했습니까? (P/F): P
훈련 2가 통과으로 표시되었습니다.



=== 훈련 메뉴 ===
1. 체력 및 지식 (통과)
2. 자기관리와 팀워크 (통과)
3. 어학 및 발음
4. 보컬
5. 댄스
6. 비주얼 및 이미지
7. 연기 및 무대 퍼포먼스
8. 팬 소통
선택 (1-8, 0 메인 메뉴로 돌아가기): 3

--- 어학 및 발음 서브 메뉴 ---
A. 한국어 퀴즈
선택 (A 또는 0 훈련 메뉴로 돌아가기): A

--- 한국어 퀴즈 세션 ---
최하윤님, 한국어 퀴즈 세션에 오신 걸 환영합니다!

30초 뒤에 한국어 퀴즈가 시작됩니다! 준비하세요./* 

*/

//아래는 코드입니다.

#include <stdio.h>    // printf, fgets, stdin, getchar
#include <string.h>   // strlen, strcmp, strcpy, strchr, strcat
#include <ctype.h>    // toupper
#include <stdlib.h>   // srand, rand, NULL
#include <time.h>     // time, clock_t, clock, CLOCKS_PER_SEC

#define MAX_INPUT 10
#define TRAINING_COUNT 8
#define MAX_TRAINEES 10 // 밀리웨이즈 연습생 수
#define MAX_MENTORS 8
#define MAX_ANSWER_LENGTH 100 // 상담 답변 최대 길이
#define MAX_KEYWORD_LENGTH 10 // "specter" + null terminator

// 훈련 현황을 추적하는 배열
char training_status[TRAINING_COUNT] = {0}; // 0: 시도 안 함, P: 통과, F: 실패
int current_training = 0; // 순차적 훈련(1번, 2번)의 진행 상황을 추적합니다.

// 연습생 데이터 (기존)
char *mill_trainee_nicknames[MAX_TRAINEES] = {
    "Zaphod", "Ford", "Arthur", "Trillian", "Marvin",
    "Slartibartfast", "Agrajag", "Gargravarr", "Krikkit", "DeepThought"
};

// 연습생 이름 (과제 1 데이터 기반)
char *mill_trainee_names[MAX_TRAINEES] = {
    "박지연", "김민준", "이서준", "정유진", "최하윤",
    "강도현", "윤아인", "서은우", "홍지아", "임지호"
};

// 연습생 국적 (과제 1 데이터 기반, 임의 설정)
char *mill_trainee_nationalities[MAX_TRAINEES] = {
    "Korea", "USA", "Japan", "China", "Canada",
    "UK", "Australia", "Germany", "France", "USA"
};


// 멘토 구조체 (기존)
typedef struct {
    int id;
    char name[50];
    int matched_trainee_idx; // -1이면 매칭되지 않음, 그 외에는 연습생의 인덱스
} Mentor;

Mentor mentors[MAX_MENTORS];
int mentor_count = 0;

// 트라우마 구조체 (기존)
typedef struct {
    char nickname[50];
    int age; // 가상의 나이
    char trauma_content[256]; // 트라우마 내용
    int has_trauma; // 트라우마가 입력되었는지 여부 (0: 없음, 1: 있음)
    int has_consultation; // 상담을 완료했는지 여부 (0: 안 함, 1: 완료)
} Trauma;

Trauma trauma_data[MAX_TRAINEES];

// 상담 질문 구조체 (기존)
typedef struct {
    int id;
    char content[256];
} Question;

// 읽기 전용 질문 데이터 (기존)
const Question questions[] = {
    {1, "어떤 상황에서 그 트라우마를 경험하셨나요?"},
    {2, "해당 상황이 어떻게 당신의 일상생활과 감정에 어떤 영향을 미치고 있는지 말씀해주세요."},
    {3, "이 트라우마를 어떻게 극복하려고 노력하셨나요?"},
    {4, "트라우마와 관련하여 어떤 감정을 느끼고 계신가요?"},
    {5, "트라우마를 극복하기 위해 어떤 지원이 필요한 것으로 생각하시나요?"}
};
const int NUM_QUESTIONS = sizeof(questions) / sizeof(questions[0]);

// 상담 구조체 (기존)
typedef struct {
    char nickname[50];
    char question_asked[256];
    char answer[MAX_ANSWER_LENGTH + 1]; // +1 for null terminator
} Consultation;

Consultation consultations[MAX_TRAINEES * 3]; // 각 멤버당 3개의 질문 (최대)
int consultation_count = 0; // 저장된 상담 답변의 개수

// 상담 세션 일시 중지/재개 상태 (기존)
enum ConsultationState {
    CONSULTATION_INACTIVE,
    CONSULTATION_PAUSED,
    CONSULTATION_ACTIVE
};
int consultation_state = CONSULTATION_INACTIVE;
int current_consulting_trainee_idx = -1;
int current_question_num = 0; // 0, 1, 2 for 3 questions
int random_question_indices[3]; // 현재 상담 세션에서 사용할 질문 인덱스

// 이스터 에그 구조체 (기존)
typedef struct {
    char keyword[MAX_KEYWORD_LENGTH];
    char message[512]; // 메시지가 길 수 있으므로 넉넉하게 할당
} EasterEgg;

// 아서의 이스터 에그 데이터 (기존)
EasterEgg arthur_easter_egg = {
    "specter",
    "나는 고백한다. 대학 졸업 후 스타트업 창업이라는 허세에 빠져 치기 어린 행동으로 친구들의 앞길을 막았다. 나는 나의 아이디어가 설득되는 사람이 나 뿐일 때 파괴적인 결과를 보게 된다는 것을 뼈저리게 경험했다. 과거의 아서는 독선과 아집의 망령이다."
};

// 연습생 구조체 (새로 추가)
typedef struct {
    char name[50];
    char nickname[50];
    char nationality[50];
    int quiz_score;
    int is_passed; // 0: 불합격, 1: 합격
} Trainee;

Trainee trainees[MAX_TRAINEES];

// 한국어 문제은행 구조체 (새로 추가)
typedef struct {
    int id;
    char question_content_eng[256]; // 영어 질문
    char correct_answer_kor[256]; // 한국어 정답
} KoreanQuizQuestion;

// 한국어 문제은행 데이터 (10개)
KoreanQuizQuestion korean_quiz_bank[] = {
    {1, "What is 'Hello' in Korean?", "안녕하세요"},
    {2, "What is 'Thank you' in Korean?", "감사합니다"},
    {3, "What is 'Excuse me' in Korean?", "실례합니다"},
    {4, "What is 'Yes' in Korean?", "네"},
    {5, "What is 'No' in Korean?", "아니요"},
    {6, "What is 'I love you' in Korean?", "사랑해요"},
    {7, "What is 'Good night' in Korean?", "안녕히 주무세요"},
    {8, "What is 'How are you?' in Korean?", "잘 지내세요?"},
    {9, "What is 'Sorry' in Korean?", "죄송합니다"},
    {10, "What is 'Where is the bathroom?' in Korean?", "화장실이 어디예요?"}
};
const int NUM_KOREAN_QUIZ_QUESTIONS = sizeof(korean_quiz_bank) / sizeof(korean_quiz_bank[0]);

// 퀴즈 답안지 구조체 (새로 추가)
typedef struct {
    int question_id;
    char correct_or_wrong; // 'O' 또는 'X'
} QuizAnswerSheet;

// QuizAnswerSheet answers[5]; // 5개 문제에 대한 답안지 (퀴즈마다 초기화)

// Function prototypes (기존)
void display_main_menu();
void 오디션_관리();
void training_management();
void debut_management();
void display_training_menu();
void handle_training(int choice);
void evaluate_training(int training_idx);
int is_training_available(int choice);

// New functions for trainee and mentor management (기존)
int parseIntMember(const char *nickname);
int getRandomAbility();
void initialize_trainee_data(); // 기존 연습생 데이터 초기화 + 새로운 Trainee 구조체 초기화
void input_mentor_data();
void matchMentoring();
void assign_mentors();
void display_matched_mentors();

// New functions for trauma management (기존)
void overcomeTrauma();
void fill_trauma_member_info();
void display_trauma_submenu();
void input_trauma();
void start_consultation_session();
void display_consultation_results();
int find_trainee_by_nickname(const char *nickname); // 닉네임으로 연습생 인덱스 찾기
int get_random_unique_questions(int *indices, int count, int max_val); // 중복 없는 랜덤 질문 인덱스 생성
void handle_consultation_resume(); // 일시 중지된 상담 재개 처리

// New functions for Easter Egg (기존)
void find_easter_egg();
int isRightChar(char expected_char, char input_char);
int isEasterEgg(const char *combined_word);
void char_to_binary_string(char c, char *binary_str);
void display_binary_and_get_input(const char *keyword);

// New functions for Korean Quiz (새로 추가)
void testKoreanLang();
int selectRandomTakers(int current_hour);
void serveRandomQuiz(int trainee_idx);
int isAnswer(int question_id, const char *user_answer, const char *correct_answer); // 보너스 적용 전
// int isAnswer(int question_id, const char *user_answer, const char *correct_answer, QuizAnswerSheet *answer_sheet_ptr); // 보너스 적용 후

// Main menu function
void display_main_menu() {
    printf("\n=== 매그라시아 프로그램 ===\n");
    printf("I. 오디션 관리\n");
    printf("II. 훈련\n");
    printf("III. 데뷔\n");
    printf("선택 (I, II, III 또는 Q 종료): ");
}

// Training menu function
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

// Audition Management function
void 오디션_관리() {
    printf("\n오디션 관리 시스템\n");
    printf("기능은 구현될 예정입니다.\n");
    printf("Enter 키를 눌러 메인 메뉴로 돌아갑니다.\n");
    while (getchar() != '\n'); // 입력 버퍼 비우기
    getchar(); // Enter 키 대기
}

// Training Management function
void training_management() {
    char input[MAX_INPUT];
    int choice;

    while (1) {
        display_training_menu();
        fgets(input, MAX_INPUT, stdin);
        if (strlen(input) > 0 && input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0';
        }

        // 이스터 에그 트리거: 'Arthur' 입력 시
        if (strcmp(input, "Arthur") == 0 || strcmp(input, "arthur") == 0) {
            find_easter_egg();
            // 이스터 에그 후에는 훈련 메뉴로 다시 돌아옴
            while (getchar() != '\n'); // 입력 버퍼 비우기
            continue;
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
                    printf("B. 트라우마 관리\n"); // 트라우마 관리 메뉴 추가
                    printf("선택 (A, B, 또는 0 훈련 메뉴로 돌아가기): ");
                    fgets(sub_input, MAX_INPUT, stdin);
                    if (strlen(sub_input) > 0 && sub_input[strlen(sub_input) - 1] == '\n') {
                        sub_input[strlen(sub_input) - 1] = '\0';
                    }

                    if (toupper(sub_input[0]) == 'A') {
                        matchMentoring();
                    } else if (toupper(sub_input[0]) == 'B') {
                        overcomeTrauma(); // 트라우마 관리 함수 호출
                    } else if (strcmp(sub_input, "0") == 0) {
                        // 훈련 메뉴로 돌아가기, 버퍼는 fgets에 의해 이미 비워졌습니다.
                    } else {
                        printf("잘못된 입력입니다. A, B 또는 0을 입력하세요.\n");
                    }
                    while (getchar() != '\n'); // 서브 메뉴 후 입력 버퍼 비우기
                } else if (choice == 3) { // 어학 및 발음
                    char sub_input[MAX_INPUT];
                    printf("\n--- 어학 및 발음 서브 메뉴 ---\n");
                    printf("A. 한국어 퀴즈\n"); // 한국어 퀴즈 메뉴 추가
                    printf("선택 (A 또는 0 훈련 메뉴로 돌아가기): ");
                    fgets(sub_input, MAX_INPUT, stdin);
                    if (strlen(sub_input) > 0 && sub_input[strlen(sub_input) - 1] == '\n') {
                        sub_input[strlen(sub_input) - 1] = '\0';
                    }

                    if (toupper(sub_input[0]) == 'A') {
                        testKoreanLang(); // 한국어 퀴즈 함수 호출
                    } else if (strcmp(sub_input, "0") == 0) {
                        // 훈련 메뉴로 돌아가기
                    } else {
                        printf("잘못된 입력입니다. A 또는 0을 입력하세요.\n");
                    }
                    while (getchar() != '\n'); // 서브 메뉴 후 입력 버퍼 비우기
                }
                else {
                    handle_training(choice);
                }
            } else {
                printf("훈련을 이용할 수 없습니다. 필요한 훈련을 먼저 완료하거나 이미 통과한 훈련입니다.\n");
            }
        } else {
            printf("잘못된 입력입니다. 1에서 8 사이의 숫자를 입력하거나 'Arthur'를 입력하여 이스터 에그를 찾거나 0을 입력하여 돌아가세요.\n");
        }
        while (getchar() != '\n'); // 각 반복 후 입력 버퍼 비우기
    }
}

// Debut Management function
void debut_management() {
    printf("\n데뷔 관리 시스템\n");
    printf("기능은 구현될 예정입니다.\n");
    printf("Enter 키를 눌러 메인 메뉴로 돌아갑니다.\n");
    while (getchar() != '\n'); // 입력 버퍼 비우기
    getchar();
}

// Check if a training is available
int is_training_available(int choice) {
    int idx = choice - 1;
    // Trainings 1 and 2 must be done sequentially
    if (choice == 1 && training_status[0] == 0) {
        return 1;
    }
    if (choice == 2 && training_status[0] == 'P' && training_status[1] == 0) {
        return 1;
    }
    // Trainings 3-8 require 1 and 2 to be passed
    if (choice >= 3 && training_status[0] == 'P' && training_status[1] == 'P' && training_status[idx] == 0) {
        return 1;
    }
    return 0;
}

// Handle training selection
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
        // Return to training menu
        return;
    } else {
        printf("잘못된 입력입니다. Y 또는 N을 입력하세요.\n");
    }
}

// Evaluate training
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

// --- New Functions Implementation ---

// Converts a trainee's nickname to an integer by summing ASCII values
int parseIntMember(const char *nickname) {
    int sum = 0;
    int i;
    for (i = 0; i < strlen(nickname); i++) {
        sum += (int)nickname[i];
    }
    return sum;
}

// Generates a random ability score between 100 and 1000
int getRandomAbility() {
    return (rand() % 901) + 100; // Generates a number between 0 and 900, then adds 100
}

// Initializes trainee data (parsed IDs and random abilities)
void initialize_trainee_data() {
    int i;
    for (i = 0; i < MAX_TRAINEES; i++) {
        strcpy(trainees[i].name, mill_trainee_names[i]);
        strcpy(trainees[i].nickname, mill_trainee_nicknames[i]);
        strcpy(trainees[i].nationality, mill_trainee_nationalities[i]);
        trainees[i].quiz_score = 0; // 퀴즈 점수 초기화
        trainees[i].is_passed = 0; // 합격 여부 초기화
    }
}

// Allows user to input mentor data
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

        mentors[i].id = i + 1; // Assign unique ID from 1 to 8
        mentors[i].matched_trainee_idx = -1; // Initialize as not matched
        mentor_count++;
    }
    if (mentor_count == 0) {
        printf("등록된 멘토가 없습니다.\n");
    } else {
        printf("%d명의 멘토가 성공적으로 등록되었습니다.\n", mentor_count);
    }
    while (getchar() != '\n'); // Clear input buffer
}

// Handles the mentoring matching process
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
    while (getchar() != '\n'); // Clear input buffer
    getchar();
}

// Assigns mentors to trainees with 1:1 guarantee for available mentors
void assign_mentors() {
    int i;
    int trainee_indices[MAX_TRAINEES];
    int mentor_available[MAX_MENTORS];

    // Initialize trainee indices for shuffling
    for (i = 0; i < MAX_TRAINEES; i++) {
        trainee_indices[i] = i;
    }

    // Initialize all mentors as available and unmatched
    for (i = 0; i < mentor_count; i++) {
        mentors[i].matched_trainee_idx = -1;
        mentor_available[i] = 1; // 1 means available, 0 means assigned
    }

    // Shuffle trainee indices to randomize matching
    for (i = 0; i < MAX_TRAINEES; i++) {
        int j = rand() % MAX_TRAINEES;
        int temp = trainee_indices[i];
        trainee_indices[i] = trainee_indices[j];
        trainee_indices[j] = temp;
    }

    // Assign trainees to mentors
    for (i = 0; i < MAX_TRAINEES; i++) {
        int trainee_idx = trainee_indices[i];
        int target_mentor_id = (trainee_idx % mentor_count) + 1; // Map trainee to mentor based on ID (1-indexed)

        // Find the mentor with the target ID
        int assigned = 0;
        int k;
        for (k = 0; k < mentor_count; k++) {
            if (mentors[k].id == target_mentor_id && mentor_available[k]) {
                mentors[k].matched_trainee_idx = trainee_idx;
                mentor_available[k] = 0; // Mark mentor as unavailable
                assigned = 1;
                break;
            }
        }

        // If direct assignment fails (mentor taken), find the next available mentor
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
        // If still not assigned (should only happen if all mentors are assigned and more trainees exist)
        if (!assigned) {
             printf("연습생 %s는 멘토와 매칭될 수 없습니다 (모든 멘토가 할당됨).\n", trainees[trainee_idx].nickname);
        }
    }
}


// Displays the matched trainees and mentors
void display_matched_mentors() {
    int i;
    printf("\n--- 멘토링 할당 ---\n");
    if (mentor_count == 0) {
        printf("등록된 멘토가 없어 할당을 표시할 수 없습니다.\n");
        return;
    }

    for (i = 0; i < mentor_count; i++) {
        if (mentors[i].matched_trainee_idx != -1) {
            printf("멘토 ID: %d, 멘토 이름: %s => 연습생: %s (닉네임: %s)\n",
                   mentors[i].id, mentors[i].name,
                   trainees[mentors[i].matched_trainee_idx].name,
                   trainees[mentors[i].matched_trainee_idx].nickname);
        } else {
            printf("멘토 ID: %d, 멘토 이름: %s => 할당된 연습생 없음\n",
                   mentors[i].id, mentors[i].name);
        }
    }
}

// --- 트라우마 관리 기능 구현 ---

// 트라우마 구조체에 멤버 정보 채우기
void fill_trauma_member_info() {
    int i;
    for (i = 0; i < MAX_TRAINEES; i++) {
        strcpy(trauma_data[i].nickname, trainees[i].nickname); // Trainee 구조체에서 닉네임 가져오기
        trauma_data[i].age = 20 + (rand() % 5); // 20~24세 가상 나이 부여
        trauma_data[i].trauma_content[0] = '\0'; // 트라우마 내용 초기화
        trauma_data[i].has_trauma = 0; // 트라우마 입력 여부 초기화
        trauma_data[i].has_consultation = 0; // 상담 완료 여부 초기화
    }
}

// 닉네임으로 연습생 인덱스 찾기
int find_trainee_by_nickname(const char *nickname) {
    int i;
    for (i = 0; i < MAX_TRAINEES; i++) {
        if (strcmp(trainees[i].nickname, nickname) == 0) {
            return i;
        }
    }
    return -1; // 찾을 수 없음
}

// 트라우마 관리 하위 메뉴 표시
void display_trauma_submenu() {
    printf("\n--- 트라우마 관리 메뉴 ---\n");
    printf("1. 트라우마 입력\n");
    printf("2. 상담 세션 시작\n");
    printf("3. 상담 결과 보기\n");
    if (consultation_state == CONSULTATION_PAUSED) {
        printf("4. 상담 세션 재개\n");
    }
    printf("0. 이전 메뉴로 돌아가기\n");
    printf("선택 (1-4, 0): ");
}

// 트라우마 입력
void input_trauma() {
    char nickname_input[50];
    char trauma_content_input[256];
    int trainee_idx;
    char continue_input[MAX_INPUT];

    while (1) {
        printf("\n--- 트라우마 입력 ---\n");
        printf("트라우마를 입력할 멤버의 닉네임을 입력하세요 (종료하려면 '0' 입력): ");
        fgets(nickname_input, sizeof(nickname_input), stdin);
        if (strlen(nickname_input) > 0 && nickname_input[strlen(nickname_input) - 1] == '\n') {
            nickname_input[strlen(nickname_input) - 1] = '\0';
        }

        if (strcmp(nickname_input, "0") == 0) {
            break; // 트라우마 입력 종료
        }

        trainee_idx = find_trainee_by_nickname(nickname_input);

        // 삼항 연산자 사용
        trainee_idx != -1 ?
            (void)(
                printf("멤버 %s의 트라우마 내용을 입력하세요: ", nickname_input),
                fgets(trauma_content_input, sizeof(trauma_content_input), stdin),
                (strlen(trauma_content_input) > 0 && trauma_content_input[strlen(trauma_content_input) - 1] == '\n' ?
                    (trauma_content_input[strlen(trauma_content_input) - 1] = '\0') : 0),
                strcpy(trauma_data[trainee_idx].trauma_content, trauma_content_input),
                trauma_data[trainee_idx].has_trauma = 1,
                printf("'%s'의 트라우마가 저장되었습니다.\n", nickname_input)
            ) :
            (void)(
                printf("오류: '%s' 닉네임을 가진 멤버를 찾을 수 없습니다. 다시 입력하세요.\n", nickname_input)
            );
        // fgets가 개행 문자를 읽기 때문에, 여기서는 getchar()로 버퍼를 비울 필요 없음.
        // 다만, 이후의 다음 입력을 위해 버퍼가 비워져야 할 때가 있음.
        // 여기서는 fgets가 이미 한 줄을 읽었으므로, 추가적인 getchar()는 필요 없을 수 있으나,
        // 사용자 입력 방식에 따라 다를 수 있으므로 유지.
        // while (getchar() != '\n'); 

        printf("다른 멤버의 트라우마를 입력하시겠습니까? (Y/N): ");
        fgets(continue_input, MAX_INPUT, stdin);
        if (strlen(continue_input) > 0 && continue_input[strlen(continue_input) - 1] == '\n') {
            continue_input[strlen(continue_input) - 1] = '\0';
        }
        if (toupper(continue_input[0]) == 'N') {
            break;
        }
    }
}

// 중복 없는 랜덤 질문 인덱스 생성
int get_random_unique_questions(int *indices, int count, int max_val) {
    if (count > max_val) {
        return 0; // 요청된 질문 수가 전체 질문 수보다 많음
    }
    int selected[max_val];
    int i, j;
    for (i = 0; i < max_val; i++) {
        selected[i] = 0; // 0: 선택되지 않음, 1: 선택됨
    }

    for (i = 0; i < count; i++) {
        int r;
        do {
            r = rand() % max_val;
        } while (selected[r]);
        indices[i] = r;
        selected[r] = 1;
    }
    return 1;
}

// 상담 세션 시작/재개
void start_consultation_session() {
    char input_nickname[50];
    int trainee_idx = -1;
    char answer_input[MAX_ANSWER_LENGTH + 2]; // +2 for newline and null terminator

    if (consultation_state == CONSULTATION_PAUSED) {
        handle_consultation_resume();
        return;
    }

    printf("\n--- 상담 세션 시작 ---\n");
    printf("트라우마가 입력된 멤버 목록:\n");
    int has_trauma_members = 0;
    int i;
    for (i = 0; i < MAX_TRAINEES; i++) {
        if (trauma_data[i].has_trauma) {
            printf("- %s\n", trauma_data[i].nickname);
            has_trauma_members = 1;
        }
    }

    if (!has_trauma_members) {
        printf("트라우마가 입력된 멤버가 없습니다. 먼저 트라우마를 입력해주세요.\n");
        return;
    }

    while (trainee_idx == -1) {
        printf("상담을 시작할 멤버의 닉네임을 입력하세요 (종료하려면 '0' 입력): ");
        fgets(input_nickname, sizeof(input_nickname), stdin);
        if (strlen(input_nickname) > 0 && input_nickname[strlen(input_nickname) - 1] == '\n') {
            input_nickname[strlen(input_nickname) - 1] = '\0';
        }

        if (strcmp(input_nickname, "0") == 0) {
            return; // 상담 세션 종료
        }

        trainee_idx = find_trainee_by_nickname(input_nickname);
        if (trainee_idx == -1 || !trauma_data[trainee_idx].has_trauma) {
            printf("오류: '%s' 닉네임을 가진 멤버를 찾을 수 없거나 트라우마가 입력되지 않았습니다. 다시 입력하세요.\n", input_nickname);
            trainee_idx = -1; // 다시 입력 받기 위해 초기화
        }
        // while (getchar() != '\n'); // 입력 버퍼 비우기
    }

    current_consulting_trainee_idx = trainee_idx;
    consultation_state = CONSULTATION_ACTIVE;
    current_question_num = 0; // 첫 번째 질문부터 시작

    // 3개의 중복 없는 랜덤 질문 선택
    if (!get_random_unique_questions(random_question_indices, 3, NUM_QUESTIONS)) {
        printf("오류: 질문 선택에 실패했습니다.\n");
        consultation_state = CONSULTATION_INACTIVE;
        return;
    }

    // 상담 세션 진행
    for (i = current_question_num; i < 3; i++) {
        printf("\n--- 상담 진행 중: %s ---\n", trauma_data[current_consulting_trainee_idx].nickname);
        printf("질문 %d: %s\n", i + 1, questions[random_question_indices[i]].content);
        printf("답변 (최대 %d자, 'p' 일시 중지): ", MAX_ANSWER_LENGTH);

        fgets(answer_input, sizeof(answer_input), stdin);
        if (strlen(answer_input) > 0 && answer_input[strlen(answer_input) - 1] == '\n') {
            answer_input[strlen(answer_input) - 1] = '\0';
        }
        // 이스터 에그와 겹치지 않게 'p'는 소문자로만 일시정지로 인식.
        // 여기서는 이스터 에그가 아닌 상담의 기능으로만 사용.
        if (answer_input[0] == 'p' && strlen(answer_input) == 1) { // 소문자 'p'만 일시 중지
            consultation_state = CONSULTATION_PAUSED;
            current_question_num = i; // 현재 질문 번호 저장
            printf("상담 세션이 일시 중지되었습니다.\n");
            return; // 함수 종료 후 재개 메뉴에서 다시 호출
        }

        // 답변 유효성 검사 (빈 값 또는 100자 초과)
        while (strlen(answer_input) == 0 || strlen(answer_input) > MAX_ANSWER_LENGTH) {
            if (strlen(answer_input) == 0) {
                printf("답변은 비워둘 수 없습니다. 다시 입력하세요: ");
            } else { // strlen(answer_input) > MAX_ANSWER_LENGTH
                printf("답변이 너무 깁니다 (최대 %d자). 다시 입력하세요: ", MAX_ANSWER_LENGTH);
            }
            fgets(answer_input, sizeof(answer_input), stdin);
            if (strlen(answer_input) > 0 && answer_input[strlen(answer_input) - 1] == '\n') {
                answer_input[strlen(answer_input) - 1] = '\0';
            }
            // while (getchar() != '\n'); // 입력 버퍼 비우기
        }

        // 상담 내용 저장
        strcpy(consultations[consultation_count].nickname, trauma_data[current_consulting_trainee_idx].nickname);
        strcpy(consultations[consultation_count].question_asked, questions[random_question_indices[i]].content);
        strcpy(consultations[consultation_count].answer, answer_input);
        consultation_count++;
    }

    trauma_data[current_consulting_trainee_idx].has_consultation = 1; // 상담 완료 표시
    consultation_state = CONSULTATION_INACTIVE; // 상담 종료
    current_consulting_trainee_idx = -1; // 초기화
    printf("\n상담 세션이 완료되었습니다.\n");
}

// 일시 중지된 상담 재개 처리
void handle_consultation_resume() {
    int i;
    char answer_input[MAX_ANSWER_LENGTH + 2];

    if (consultation_state != CONSULTATION_PAUSED) {
        printf("재개할 상담 세션이 없습니다.\n");
        return;
    }

    printf("\n--- 상담 세션 재개 중: %s ---\n", trauma_data[current_consulting_trainee_idx].nickname);
    consultation_state = CONSULTATION_ACTIVE;

    for (i = current_question_num; i < 3; i++) {
        printf("\n질문 %d: %s\n", i + 1, questions[random_question_indices[i]].content);
        printf("답변 (최대 %d자, 'p' 일시 중지): ", MAX_ANSWER_LENGTH);

        fgets(answer_input, sizeof(answer_input), stdin);
        if (strlen(answer_input) > 0 && answer_input[strlen(answer_input) - 1] == '\n') {
            answer_input[strlen(answer_input) - 1] = '\0';
        }
        if (answer_input[0] == 'p' && strlen(answer_input) == 1) { // 소문자 'p'만 일시 중지
            consultation_state = CONSULTATION_PAUSED;
            current_question_num = i; // 현재 질문 번호 저장
            printf("상담 세션이 일시 중지되었습니다.\n");
            return; // 함수 종료 후 재개 메뉴에서 다시 호출
        }

        while (strlen(answer_input) == 0 || strlen(answer_input) > MAX_ANSWER_LENGTH) {
            if (strlen(answer_input) == 0) {
                printf("답변은 비워둘 수 없습니다. 다시 입력하세요: ");
            } else {
                printf("답변이 너무 깁니다 (최대 %d자). 다시 입력하세요: ", MAX_ANSWER_LENGTH);
            }
            fgets(answer_input, sizeof(answer_input), stdin);
            if (strlen(answer_input) > 0 && answer_input[strlen(answer_input) - 1] == '\n') {
                answer_input[strlen(answer_input) - 1] = '\0';
            }
            // while (getchar() != '\n'); // 입력 버퍼 비우기
        }

        strcpy(consultations[consultation_count].nickname, trauma_data[current_consulting_trainee_idx].nickname);
        strcpy(consultations[consultation_count].question_asked, questions[random_question_indices[i]].content);
        strcpy(consultations[consultation_count].answer, answer_input);
        consultation_count++;
    }

    trauma_data[current_consulting_trainee_idx].has_consultation = 1; // 상담 완료 표시
    consultation_state = CONSULTATION_INACTIVE; // 상담 종료
    current_consulting_trainee_idx = -1; // 초기화
    printf("\n상담 세션이 완료되었습니다.\n");
}


// 상담 결과 보기
void display_consultation_results() {
    char input_nickname[50];
    int trainee_idx;
    int found_consultations = 0;
    int i;

    printf("\n--- 상담 결과 보기 ---\n");
    printf("상담을 완료한 멤버 목록:\n");
    for (i = 0; i < MAX_TRAINEES; i++) {
        if (trauma_data[i].has_consultation) {
            printf("- %s\n", trauma_data[i].nickname);
            found_consultations = 1;
        }
    }

    if (!found_consultations) {
        printf("완료된 상담이 없습니다.\n");
        return;
    }

    printf("결과를 볼 멤버의 닉네임을 입력하세요 (종료하려면 '0' 입력): ");
    fgets(input_nickname, sizeof(input_nickname), stdin);
    if (strlen(input_nickname) > 0 && input_nickname[strlen(input_nickname) - 1] == '\n') {
        input_nickname[strlen(input_nickname) - 1] = '\0';
    }

    if (strcmp(input_nickname, "0") == 0) {
        return;
    }

    trainee_idx = find_trainee_by_nickname(input_nickname);
    if (trainee_idx == -1 || !trauma_data[trainee_idx].has_consultation) {
        printf("오류: '%s' 닉네임을 가진 멤버를 찾을 수 없거나 상담을 완료하지 않았습니다.\n", input_nickname);
        return;
    }
    // while (getchar() != '\n'); // 입력 버퍼 비우기

    printf("\n--- %s의 상담 결과 ---\n", trauma_data[trainee_idx].nickname);
    printf("나이: %d\n", trauma_data[trainee_idx].age);
    printf("트라우마: %s\n", trauma_data[trainee_idx].trauma_content);

    found_consultations = 0;
    for (i = 0; i < consultation_count; i++) {
        if (strcmp(consultations[i].nickname, input_nickname) == 0) {
            printf("\n질문: %s\n", consultations[i].question_asked);
            printf("답변: %s\n", consultations[i].answer);
            found_consultations = 1;
        }
    }

    if (!found_consultations) {
        printf("저장된 상담 내용이 없습니다.\n");
    }
}

// 트라우마 관리 메인 함수
void overcomeTrauma() {
    char input[MAX_INPUT];
    int choice;

    while (1) {
        display_trauma_submenu();
        fgets(input, MAX_INPUT, stdin);
        if (strlen(input) > 0 && input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0';
        }

        if (strlen(input) == 0 || strcmp(input, "0") == 0) {
            // while (getchar() != '\n'); // 입력 버퍼 비우기
            return; // 이전 메뉴로 돌아가기
        }

        if (sscanf(input, "%d", &choice) == 1) {
            switch (choice) {
                case 1:
                    input_trauma();
                    break;
                case 2:
                    start_consultation_session();
                    break;
                case 3:
                    display_consultation_results();
                    break;
                case 4:
                    if (consultation_state == CONSULTATION_PAUSED) {
                        handle_consultation_resume();
                    } else {
                        printf("재개할 상담 세션이 없습니다.\n");
                    }
                    break;
                default:
                    printf("잘못된 입력입니다. 1-4 사이의 숫자를 입력하거나 0을 입력하여 돌아가세요.\n");
                    break;
            }
        } else {
            printf("잘못된 입력입니다. 1-4 사이의 숫자를 입력하거나 0을 입력하여 돌아가세요.\n");
        }
        // while (getchar() != '\n'); // 각 반복 후 입력 버퍼 비우기
    }
}

// --- 이스터 에그 기능 구현 ---

// 문자를 8비트 이진수 문자열로 변환
void char_to_binary_string(char c, char *binary_str) {
    int i;
    for (i = 7; i >= 0; i--) {
        binary_str[7 - i] = ((c >> i) & 1) ? '1' : '0';
    }
    binary_str[8] = '\0';
}

// 보너스: keyword의 글자를 섞어서 8비트 이진수로 각 글자 표시
void display_binary_and_get_input(const char *keyword) {
    int len = strlen(keyword);
    char shuffled_keyword[MAX_KEYWORD_LENGTH];
    char reversed_keyword[MAX_KEYWORD_LENGTH];
    char odd_chars[MAX_KEYWORD_LENGTH];
    char even_chars[MAX_KEYWORD_LENGTH];
    char binary_str[9];
    int i;
    char input_char_str[MAX_INPUT];
    char current_char;

    // 1. 역순으로 바꾸기
    for (i = 0; i < len; i++) {
        reversed_keyword[i] = keyword[len - 1 - i];
    }
    reversed_keyword[len] = '\0';

    // 2. 홀수 번째 글자를 모으고 다음으로 짝수 번째 글자를 모은다. (0-indexed)
    // 예: "specter" 역순 -> "retceps"
    // 홀수 (1,3,5...) -> e, c, p
    // 짝수 (0,2,4,6...) -> r, t, e, s
    int odd_idx = 0;
    int even_idx = 0;
    for (i = 0; i < len; i++) {
        if (i % 2 != 0) { // 홀수 번째 (0-indexed)
            odd_chars[odd_idx++] = reversed_keyword[i];
        } else { // 짝수 번째 (0-indexed)
            even_chars[even_idx++] = reversed_keyword[i];
        }
    }
    odd_chars[odd_idx] = '\0';
    even_chars[even_idx] = '\0';

    // 섞인 키워드 생성: 홀수 번째 + 짝수 번째
    strcpy(shuffled_keyword, odd_chars);
    strcat(shuffled_keyword, even_chars);

    printf("8비트 이진수에 해당하는 글자를 입력하세요.\n");
    printf("정답은 총 %d 글자입니다.\n", len);

    // 섞인 키워드의 각 글자에 대해 이진수 제시 및 입력 받기
    for (i = 0; i < len; i++) {
        current_char = shuffled_keyword[i];
        char_to_binary_string(current_char, binary_str);
        printf("이진수: %s -> 해당 글자를 입력하세요: ", binary_str);

        while (1) {
            fgets(input_char_str, sizeof(input_char_str), stdin);
            if (strlen(input_char_str) > 0 && input_char_str[strlen(input_char_str) - 1] == '\n') {
                input_char_str[strlen(input_char_str) - 1] = '\0';
            }
            // while (getchar() != '\n'); // 입력 버퍼 비우기

            if (strlen(input_char_str) == 1) { // 한 글자만 입력했는지 확인
                if (isRightChar(current_char, input_char_str[0])) {
                    printf("정확합니다!\n");
                    break; // 다음 글자로 진행
                } else {
                    printf("틀렸습니다. 다시 입력하세요: ");
                }
            } else {
                printf("한 글자만 입력해야 합니다. 다시 입력하세요: ");
            }
        }
    }
    printf("\n모든 글자를 올바르게 입력했습니다! 이제 단어 조합을 입력하세요.\n");
}

// 입력한 글자가 이진수에 해당하는 올바른 글자인지 확인
int isRightChar(char expected_char, char input_char) {
    return (expected_char == input_char);
}

// 사용자가 조합한 단어와 이스터 에그 키워드를 비교
int isEasterEgg(const char *combined_word) {
    return (strcmp(combined_word, arthur_easter_egg.keyword) == 0);
}

// 이스터 에그를 찾는 함수
void find_easter_egg() {
    char combined_word_input[MAX_KEYWORD_LENGTH];
    printf("\n<<아서의 이스터에그>>\n");

    // 보너스 기능: 섞인 이진수 제시 및 글자 입력 받기
    display_binary_and_get_input(arthur_easter_egg.keyword);

    // 단어 조합 입력 프롬프트
    printf("글자를 조합하여 단어를 입력하세요: ");
    fgets(combined_word_input, sizeof(combined_word_input), stdin);
    if (strlen(combined_word_input) > 0 && combined_word_input[strlen(combined_word_input) - 1] == '\n') {
        combined_word_input[strlen(combined_word_input) - 1] = '\0';
    }
    // while (getchar() != '\n'); // 입력 버퍼 비우기

    if (isEasterEgg(combined_word_input)) {
        printf("##이스터에그 발견!$$\n");
        printf("%s\n", arthur_easter_egg.message);
    } else {
        printf("올바른 단어가 아닙니다. 이스터에그를 찾지 못했습니다.\n");
    }
    printf("\nEnter 키를 눌러 훈련 메뉴로 돌아갑니다.\n");
    // while (getchar() != '\n'); // 입력 버퍼 비우기
    getchar(); // Enter 키 대기
}

// --- 한국어 퀴즈 기능 구현 ---

// 퀴즈에 응시할 연습생을 임의로 선택
int selectRandomTakers(int current_hour) {
    // 현재 시간을 시드 값으로 사용하면 특정 시간에 특정 연습생이 선택될 가능성이 높아짐
    // 따라서, 단순히 퀴즈를 시작한 시간 값을 활용하여 (예: %10) 연습생을 선택하도록 합니다.
    // 하지만, 진정한 "임의" 선택이 되려면 srand를 한 번만 호출하고, rand()를 활용하는 것이 좋습니다.
    // 여기서는 current_hour를 '활용'하는 예시로 제공합니다.

    int selected_trainee_idx = -1;
    int attempts = 0;
    int random_start_idx;

    // 현재 시간의 몫을 이용해 랜덤 시작 인덱스를 결정
    // 이 방법은 `time(NULL)`로 시드가 이미 설정되어 있기 때문에
    // `rand()`의 결과를 시간에 따라 다르게 만드는 하나의 방법으로 해석될 수 있습니다.
    random_start_idx = (current_hour + rand()) % MAX_TRAINEES;

    printf("\n--- 한국어 퀴즈 세션 ---\n");

    do {
        // 현재 인덱스부터 순회하며 한국인이 아닌 연습생을 찾습니다.
        // 이는 모든 연습생을 공정하게 선택하고 한국인 제외 조건을 만족시키기 위함입니다.
        // 단순 rand() % MAX_TRAINEES는 무한 루프에 빠질 수 있으므로,
        // 모든 후보를 탐색하는 방식으로 변경합니다.
        int check_idx = (random_start_idx + attempts) % MAX_TRAINEES;

        if (strcmp(trainees[check_idx].nationality, "Korea") != 0) {
            selected_trainee_idx = check_idx;
            break;
        }
        attempts++;
    } while (attempts < MAX_TRAINEES); // 모든 연습생을 시도

    if (selected_trainee_idx != -1) {
        printf("%s님, 한국어 퀴즈 세션에 오신 걸 환영합니다!\n", trainees[selected_trainee_idx].name);
        return selected_trainee_idx;
    } else {
        printf("퀴즈에 응시할 비한국인 연습생을 찾을 수 없습니다.\n");
        return -1;
    }
}

// 정답 여부를 체크해 기록 (보너스: isAnswer 함수를 한 번만 호출하도록 개선)
// 이 함수는 단순히 정답 여부만 반환하고, 답안지 저장은 serveRandomQuiz에서 일괄 처리합니다.
int isAnswer(int question_id, const char *user_answer, const char *correct_answer) {
    // 사용자 답변과 정답을 비교 (대소문자 구분 없이 비교하려면 tolower 또는 toupper 사용)
    // 여기서는 정확히 일치해야 정답으로 간주합니다.
    return (strcmp(user_answer, correct_answer) == 0);
}


// 퀴즈를 임의로 출제하고 채점
void serveRandomQuiz(int trainee_idx) {
    if (trainee_idx == -1) {
        return; // 응시할 연습생이 없으면 종료
    }

    int selected_questions_indices[5];
    char user_answers[5][256]; // 5개 문제에 대한 사용자 답변
    int total_score = 0;
    int i;
    time_t start_time, current_time;
    QuizAnswerSheet quiz_answers[5]; // 퀴즈 답지 배열

    // 5개의 중복 없는 랜덤 문제 선택
    if (!get_random_unique_questions(selected_questions_indices, 5, NUM_KOREAN_QUIZ_QUESTIONS)) {
        printf("오류: 퀴즈 문제 선택에 실패했습니다.\n");
        return;
    }

    printf("\n30초 뒤에 한국어 퀴즈가 시작됩니다! 준비하세요.\n");
    time(&start_time); // 현재 시간 기록

    // 30초 대기
    do {
        time(&current_time);
    } while (difftime(current_time, start_time) < 30);
    // (Alternative for more precise blocking wait for Windows/Linux:
    // #ifdef _WIN32
    // Sleep(30000); // milliseconds
    // #else
    // sleep(30); // seconds
    // #endif
    // )

    printf("\n퀴즈 시작!\n");

    for (i = 0; i < 5; i++) {
        int q_idx = selected_questions_indices[i];
        printf("\n문제 %d (20점): %s\n", i + 1, korean_quiz_bank[q_idx].question_content_eng);
        printf("답변을 입력하세요: ");

        fgets(user_answers[i], sizeof(user_answers[i]), stdin);
        if (strlen(user_answers[i]) > 0 && user_answers[i][strlen(user_answers[i]) - 1] == '\n') {
            user_answers[i][strlen(user_answers[i]) - 1] = '\0';
        }
        // while (getchar() != '\n'); // 입력 버퍼 비우기 (fgets가 이미 비웠을 수도 있음)

        // 답안지 구조체에 문제 ID 저장
        quiz_answers[i].question_id = korean_quiz_bank[q_idx].id;

        if (strlen(user_answers[i]) == 0) { // 빈 값인 경우
            printf("답변이 없어 0점 처리됩니다.\n");
            quiz_answers[i].correct_or_wrong = 'X';
        } else if (isAnswer(korean_quiz_bank[q_idx].id, user_answers[i], korean_quiz_bank[q_idx].correct_answer_kor)) {
            printf("정답입니다! (+20점)\n");
            total_score += 20;
            quiz_answers[i].correct_or_wrong = 'O';
        } else {
            printf("오답입니다. (정답: %s)\n", korean_quiz_bank[q_idx].correct_answer_kor);
            quiz_answers[i].correct_or_wrong = 'X';
        }
    }

    // 최종 점수 저장 및 합격 여부 결정
    trainees[trainee_idx].quiz_score = total_score;
    trainees[trainee_idx].is_passed = (total_score >= 80) ? 1 : 0;

    printf("\n--- 퀴즈 종료 ---\n");
    printf("%s님의 퀴즈 결과:\n", trainees[trainee_idx].name);
    printf("총점: %d점\n", trainees[trainee_idx].quiz_score);
    printf("합격 여부: %s\n", trainees[trainee_idx].is_passed ? "합격" : "불합격");

    printf("\n--- 정답지 ---\n");
    for (i = 0; i < 5; i++) {
        printf("문제 ID: %d, 당신의 답변: '%s', 정답: '%s', 결과: %c\n",
               quiz_answers[i].question_id,
               user_answers[i],
               korean_quiz_bank[selected_questions_indices[i]].correct_answer_kor,
               quiz_answers[i].correct_or_wrong);
    }
    printf("Enter 키를 눌러 훈련 메뉴로 돌아갑니다.\n");
    // while (getchar() != '\n'); // 입력 버퍼 비우기
    getchar(); // Enter 키 대기
}

// 한국어 퀴즈 메인 함수
void testKoreanLang() {
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime); // 현재 로컬 시간 가져오기
    int current_hour = info->tm_hour; // 현재 시간 (시)

    int taker_idx = selectRandomTakers(current_hour);
    if (taker_idx != -1) {
        serveRandomQuiz(taker_idx);
    } else {
        printf("한국어 퀴즈를 진행할 수 없습니다.\n");
    }
}


// Main function
int main() {
    char input[MAX_INPUT];
    srand((unsigned int)time(NULL)); // 난수 생성기 시드 설정 (한 번만 호출)

    initialize_trainee_data(); // 기존 연습생 데이터 초기화 + 새로운 Trainee 구조체 초기화
    fill_trauma_member_info(); // 트라우마 구조체에 멤버 정보 채우기 (Trainee 구조체 기반)

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
        } else if (strcmp(input, "III") == 0 || strcmp(input, "iii") == 0) {
            debut_management();
        } else {
            printf("잘못된 입력입니다. I, II, III 또는 Q를 입력하여 종료하세요.\n");
        }
    }

    return 0;
}
