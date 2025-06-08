//코디세이에서 stage1 기존에 있는 파일에서 수정하라했는데 지금 몰아서 하는 상황에서 수정을 해버리면 평가를 이어서 못해서 stage11.c로 파일을 만들었습니다.
//실행방법은 이전처럼 II 를 엔터 후 1누르고 A엔터 후 닉네임에 minhyeok 하고 엔터, 
//Example: 7.0,11.5,1.8,3.0,2.5,9.5,1.6 (Weight Lift >= 1.5 for male, >= 0.75 for female) 그럼 이렇게 뜨는데
//7.0,11.5,1.8,3.0,2.5,9.5,1.6 이 부분을 복붙해서 넣는다.
//그리고 엔터 한 뒤 또 다시 A, B중에서 이번엔 B를 엔터 후 3엔터, minhyeok을 쓰면 1~7중에 숫자를 입력하면
//아까 넣은 7.0,11.5,1.8,3.0,2.5,9.5,1.6 이것중 해당하는것이 출력될 것이다.
//참고로 안에 존재하는 닉네임은 JDoe, JSmith, ABrown, minhyeok 그 중 minhyeok을 선택한 이유는 단순 본인 이름이라.

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

// Training status array to track progress
char training_status[TRAINING_COUNT] = {0}; // 0: Not attempted, P: Passed, F: Failed
int current_training = 0; // Tracks progress for sequential training (1 and 2)

// Member structure for milliways_members
typedef struct {
    char name[MAX_NAME];
    char nickname[MAX_NICKNAME];
    char gender; // 'M' or 'F' for male or female
} Member;

// Health test items enum
typedef enum {
    MILE_RUN, SPRINT, PUSHUP, SQUAT, PULLUP, SWIM, WEIGHT_LIFT
} TestItem;

// Global variables for health management
Member milliways_members[MAX_MEMBERS];
double health_scores[MAX_MEMBERS * TEST_ITEMS]; // 1D array
int member_count = 0;

// Function prototypes
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
void parseHealthInput(const char* input, int member_idx);
void getHealth();
int findMemberIndex(const char* nickname);
void init_members();
void listMembers();

// Initialize example members
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

    for (int i = 0; i < MAX_MEMBERS * TEST_ITEMS; i++)
        health_scores[i] = -1;
}

// List all members with name and nickname
void listMembers() {
    printf("Available members:\n");
    for (int i = 0; i < member_count; i++) {
        printf("- %s (Nickname: %s)\n", milliways_members[i].name, milliways_members[i].nickname);
    }
}

// Main menu function
void display_main_menu() {
    printf("\n=== Magrathea Program ===\n");
    printf("I. Audition Management\n");
    printf("II. Training\n");
    printf("III. Debut\n");
    printf("Enter choice (I, II, III, or Q to quit): ");
}

// Training menu function
void display_training_menu() {
    printf("\n=== Training Menu ===\n");
    printf("1. Physical and Knowledge %s\n", training_status[0] == 'P' ? "(Passed)" : training_status[0] == 'F' ? "(Failed)" : "");
    printf("2. Self-Management and Teamwork %s\n", training_status[1] == 'P' ? "(Passed)" : training_status[1] == 'F' ? "(Failed)" : "");
    printf("3. Language and Pronunciation %s\n", training_status[2] == 'P' ? "(Passed)" : training_status[2] == 'F' ? "(Failed)" : "");
    printf("4. Vocal %s\n", training_status[3] == 'P' ? "(Passed)" : training_status[3] == 'F' ? "(Failed)" : "");
    printf("5. Dance %s\n", training_status[4] == 'P' ? "(Passed)" : training_status[4] == 'F' ? "(Failed)" : "");
    printf("6. Visual and Image %s\n", training_status[5] == 'P' ? "(Passed)" : training_status[5] == 'F' ? "(Failed)" : "");
    printf("7. Acting and Stage Performance %s\n", training_status[6] == 'P' ? "(Passed)" : training_status[6] == 'F' ? "(Failed)" : "");
    printf("8. Fan Communication %s\n", training_status[7] == 'P' ? "(Passed)" : training_status[7] == 'F' ? "(Failed)" : "");
    printf("Enter choice (1-8, 0 to return to main menu): ");
}

// Physical and Knowledge submenu
void display_physical_knowledge_menu() {
    printf("\n=== Physical and Knowledge Menu ===\n");
    int has_data = 0;
    for (int i = 0; i < member_count; i++) {
        if (health_scores[i * TEST_ITEMS] != -1) {
            has_data = 1;
            break;
        }
    }
    printf("A. Enter Physical Condition %s\n", has_data ? "(Entered)" : "(Not Entered)");
    printf("B. View Physical Condition %s\n", has_data ? "(Available)" : "(Not Available)");
    printf("Enter choice (A, B, or 0 to return): ");
}

// Audition Management function
void 오디션_관리() {
    printf("\nAudition Management System\n");
    printf("Functionality to be implemented.\n");
    printf("Press Enter to return to main menu.\n");
    while (getchar() != '\n');
    getchar();
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

        if (strlen(input) == 0 || strcmp(input, "0") == 0) {
            while (getchar() != '\n');
            return;
        }

        if (sscanf(input, "%d", &choice) == 1 && choice >= 1 && choice <= 8) {
            if (is_training_available(choice)) {
                handle_training(choice);
            } else {
                printf("Training not available. Complete required trainings first or this training is already passed.\n");
            }
        } else {
            printf("Invalid input. Please enter a number between 1 and 8, or 0 to return.\n");
        }
        while (getchar() != '\n');
    }
}

// Handle training selection
void handle_training(int choice) {
    if (choice == 1) {
        char input[MAX_INPUT];
        while (1) {
            display_physical_knowledge_menu();
            fgets(input, MAX_INPUT, stdin);
            if (strlen(input) > 0 && input[strlen(input) - 1] == '\n') {
                input[strlen(input) - 1] = '\0';
            }

            if (strlen(input) == 0 || strcmp(input, "0") == 0) {
                while (getchar() != '\n');
                return;
            }

            if (toupper(input[0]) == 'A') {
                setHealth();
            } else if (toupper(input[0]) == 'B') {
                getHealth();
            } else {
                printf("Invalid input. Please enter A, B, or 0 to return.\n");
            }
            while (getchar() != '\n');
        }
    } else {
        char input[MAX_INPUT];
        printf("Do you want to input evaluation results? (Y/N): ");
        fgets(input, MAX_INPUT, stdin);
        if (strlen(input) > 0 && input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0';
        }

        if (toupper(input[0]) == 'Y') {
            evaluate_training(choice - 1);
        } else if (toupper(input[0]) == 'N') {
            return;
        } else {
            printf("Invalid input. Please enter Y or N.\n");
        }
    }
}

// Set health data
void setHealth() {
    char nickname[MAX_NICKNAME], input[MAX_HEALTH_INPUT];
    printf("Enter member nickname: ");
    fgets(nickname, MAX_NICKNAME, stdin);
    nickname[strcspn(nickname, "\n")] = 0;

    int idx = findMemberIndex(nickname);
    if (idx == -1) {
        printf("Invalid nickname: %s\n", nickname);
        listMembers();
        return;
    }

    printf("Member: %s (Nickname: %s)\n", milliways_members[idx].name, milliways_members[idx].nickname);
    printf("Enter health data (comma-separated, 7 items):\n");
    printf("Mile Run (min), Sprint (sec), Pushup (min), Squat (min), Pullup (min), Swim (min), Weight Lift (multiple)\n");
    fgets(input, MAX_HEALTH_INPUT, stdin);
    input[strcspn(input, "\n")] = 0;
    parseHealthInput(input, idx);
}

// Parse health input
void parseHealthInput(const char* input, int member_idx) {
    char* input_copy = strdup(input);
    char* token = strtok(input_copy, ",");
    int i = 0;
    double values[TEST_ITEMS];
    while (token && i < TEST_ITEMS) {
        while (*token == ' ') token++;
        char* end = token + strlen(token) - 1;
        while (end > token && *end == ' ') *end-- = 0;
        values[i++] = atof(token);
        token = strtok(NULL, ",");
    }
    if (i != TEST_ITEMS) {
        printf("Invalid input format or insufficient data for %s (Nickname: %s).\n", 
               milliways_members[member_idx].name, milliways_members[member_idx].nickname);
        for (int j = 0; j < TEST_ITEMS; j++) 
            health_scores[member_idx * TEST_ITEMS + j] = -1;
        free(input_copy);
        return;
    }

    // Validate weight lift based on gender
    if (milliways_members[member_idx].gender == 'M' && values[WEIGHT_LIFT] < 1.5) {
        printf("Weight Lift for male must be at least 1.5x body weight for %s (Nickname: %s).\n", 
               milliways_members[member_idx].name, milliways_members[member_idx].nickname);
        for (int j = 0; j < TEST_ITEMS; j++) 
            health_scores[member_idx * TEST_ITEMS + j] = -1;
        free(input_copy);
        return;
    }
    if (milliways_members[member_idx].gender == 'F' && values[WEIGHT_LIFT] < 0.75) {
        printf("Weight Lift for female must be at least 0.75x body weight for %s (Nickname: %s).\n", 
               milliways_members[member_idx].name, milliways_members[member_idx].nickname);
        for (int j = 0; j < TEST_ITEMS; j++) 
            health_scores[member_idx * TEST_ITEMS + j] = -1;
        free(input_copy);
        return;
    }

    // Store valid data
    for (int j = 0; j < TEST_ITEMS; j++) 
        health_scores[member_idx * TEST_ITEMS + j] = values[j];
    
    printf("Health data saved for %s (Nickname: %s).\n", 
           milliways_members[member_idx].name, milliways_members[member_idx].nickname);
    free(input_copy);
}

// Get health data
void getHealth() {
    char input[MAX_INPUT];
    printf("Select option:\n");
    printf("1. View all health data\n");
    printf("2. View all data for one member\n");
    printf("3. View specific data for one member\n");
    printf("Enter choice (1-3, or 0 to return): ");
    fgets(input, MAX_INPUT, stdin);
    input[strcspn(input, "\n")] = 0;

    if (strcmp(input, "0") == 0) return;

    int choice;
    if (sscanf(input, "%d", &choice) != 1 || choice < 1 || choice > 3) {
        printf("Invalid choice.\n");
        return;
    }

    if (choice == 1) {
        for (int i = 0; i < member_count; i++) {
            if (health_scores[i * TEST_ITEMS] == -1) continue;
            printf("\nMember: %s (Nickname: %s)\n", milliways_members[i].name, milliways_members[i].nickname);
            printf("Mile Run: %.2f min, Sprint: %.2f sec, Pushup: %.2f min, Squat: %.2f min, Pullup: %.2f min, Swim: %.2f min, Weight Lift: %.2f multiple\n",
                   health_scores[i * TEST_ITEMS + MILE_RUN], health_scores[i * TEST_ITEMS + SPRINT], 
                   health_scores[i * TEST_ITEMS + PUSHUP], health_scores[i * TEST_ITEMS + SQUAT], 
                   health_scores[i * TEST_ITEMS + PULLUP], health_scores[i * TEST_ITEMS + SWIM], 
                   health_scores[i * TEST_ITEMS + WEIGHT_LIFT]);
        }
    } else if (choice == 2) {
        char nickname[MAX_NICKNAME];
        printf("Enter member nickname: ");
        fgets(nickname, MAX_NICKNAME, stdin);
        nickname[strcspn(nickname, "\n")] = 0;

        int idx = findMemberIndex(nickname);
        if (idx == -1) {
            printf("Invalid nickname: %s\n", nickname);
            listMembers();
            return;
        }
        if (health_scores[idx * TEST_ITEMS] == -1) {
            printf("No health data for %s (Nickname: %s).\n", 
                   milliways_members[idx].name, milliways_members[idx].nickname);
            return;
        }

        printf("\nMember: %s (Nickname: %s)\n", milliways_members[idx].name, milliways_members[idx].nickname);
        printf("Mile Run: %.2f min, Sprint: %.2f sec, Pushup: %.2f min, Squat: %.2f min, Pullup: %.2f min, Swim: %.2f min, Weight Lift: %.2f multiple\n",
               health_scores[idx * TEST_ITEMS + MILE_RUN], health_scores[idx * TEST_ITEMS + SPRINT], 
               health_scores[idx * TEST_ITEMS + PUSHUP], health_scores[idx * TEST_ITEMS + SQUAT], 
               health_scores[idx * TEST_ITEMS + PULLUP], health_scores[idx * TEST_ITEMS + SWIM], 
               health_scores[idx * TEST_ITEMS + WEIGHT_LIFT]);
    } else if (choice == 3) {
        char nickname[MAX_NICKNAME];
        printf("Enter member nickname: ");
        fgets(nickname, MAX_NICKNAME, stdin);
        nickname[strcspn(nickname, "\n")] = 0;

        int idx = findMemberIndex(nickname);
        if (idx == -1) {
            printf("Invalid nickname: %s\n", nickname);
            listMembers();
            return;
        }
        if (health_scores[idx * TEST_ITEMS] == -1) {
            printf("No health data for %s (Nickname: %s).\n", 
                   milliways_members[idx].name, milliways_members[idx].nickname);
            return;
        }

        printf("Select health item (1-7):\n");
        printf("1. Mile Run, 2. Sprint, 3. Pushup, 4. Squat, 5. Pullup, 6. Swim, 7. Weight Lift\n");
        fgets(input, MAX_INPUT, stdin);
        input[strcspn(input, "\n")] = 0;

        int item_idx;
        if (sscanf(input, "%d", &item_idx) != 1 || item_idx < 1 || item_idx > 7) {
            printf("Invalid item number.\n");
            return;
        }
        item_idx--; // Adjust to 0-based index

        printf("\nMember: %s (Nickname: %s)\n", milliways_members[idx].name, milliways_members[idx].nickname);
        switch (item_idx) {
            case MILE_RUN: printf("Mile Run: %.2f min\n", health_scores[idx * TEST_ITEMS + MILE_RUN]); break;
            case SPRINT: printf("Sprint: %.2f sec\n", health_scores[idx * TEST_ITEMS + SPRINT]); break;
            case PUSHUP: printf("Pushup: %.2f min\n", health_scores[idx * TEST_ITEMS + PUSHUP]); break;
            case SQUAT: printf("Squat: %.2f min\n", health_scores[idx * TEST_ITEMS + SQUAT]); break;
            case PULLUP: printf("Pullup: %.2f min\n", health_scores[idx * TEST_ITEMS + PULLUP]); break;
            case SWIM: printf("Swim: %.2f min\n", health_scores[idx * TEST_ITEMS + SWIM]); break;
            case WEIGHT_LIFT: printf("Weight Lift: %.2f multiple\n", health_scores[idx * TEST_ITEMS + WEIGHT_LIFT]); break;
        }
    }
}

// Find member index by nickname
int findMemberIndex(const char* nickname) {
    for (int i = 0; i < member_count; i++) {
        if (strcmp(milliways_members[i].nickname, nickname) == 0)
            return i;
    }
    return -1;
}

// Evaluate training
void evaluate_training(int training_idx) {
    char input[MAX_INPUT];
    printf("Did you pass the training certification? (P/F): ");
    fgets(input, MAX_INPUT, stdin);
    if (strlen(input) > 0 && input[strlen(input) - 1] == '\n') {
        input[strlen(input) - 1] = '\0';
    }

    if (toupper(input[0]) == 'P' || toupper(input[0]) == 'F') {
        training_status[training_idx] = toupper(input[0]);
        if (training_idx < 2 && toupper(input[0]) == 'P') {
            current_training++;
        }
        printf("Training %d marked as %s.\n", training_idx + 1, toupper(input[0]) == 'P' ? "Passed" : "Failed");
    } else {
        printf("Invalid input. Please enter P or F.\n");
    }
}

// Check if a training is available
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

// Debut Management function
void debut_management() {
    printf("\nDebut Management System\n");
    printf("Functionality to be implemented.\n");
    printf("Press Enter to return to main menu.\n");
    while (getchar() != '\n');
    getchar();
}

// Main function
int main() {
    char input[MAX_INPUT];
    init_members();

    while (1) {
        display_main_menu();
        fgets(input, MAX_INPUT, stdin);
        if (strlen(input) > 0 && input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0';
        }

        if (strlen(input) == 0 || strcmp(input, "0") == 0 || toupper(input[0]) == 'Q') {
            printf("Exiting Magrathea Program.\n");
            break;
        }

        if (strcmp(input, "I") == 0 || strcmp(input, "i") == 0) {
            오디션_관리();
        } else if (strcmp(input, "II") == 0 || strcmp(input, "ii") == 0) {
            training_management();
        } else if (strcmp(input, "III") == 0 || strcmp(input, "iii") == 0) {
            debut_management();
        } else {
            printf("Invalid input. Please enter I, II, III, or Q to quit.\n");
        }
    }

    return 0;
}
