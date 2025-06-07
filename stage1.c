//하는 방법 : gcc stage1.c -o stage1하고 난 뒤 I, II, III가 나오면 II하고 순서대로 1,2,3,...8 입력하고 Y하고 엔터하면 P혹은 F가 나오며, N누르고 엔터를 할 경우 다시 입력 가능.

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 10
#define TRAINING_COUNT 8

// Training status array to track progress
char training_status[TRAINING_COUNT] = {0}; // 0: Not attempted, P: Passed, F: Failed
int current_training = 0; // Tracks progress for sequential training (1 and 2)

// Function prototypes
void display_main_menu();
void 오디션_관리();
void training_management();
void debut_management();
void display_training_menu();
void handle_training(int choice);
void evaluate_training(int training_idx);
int is_training_available(int choice);

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

// Audition Management function
void 오디션_관리() {
    printf("\nAudition Management System\n");
    printf("Functionality to be implemented.\n");
    printf("Press Enter to return to main menu.\n");
    while (getchar() != '\n'); // Clear input buffer
    getchar(); // Wait for Enter
}

// Training Management function
void training_management() {
    char input[MAX_INPUT];
    int choice;

    while (1) {
        display_training_menu();
        fgets(input, MAX_INPUT, stdin);
        if (strlen(input) > 0 && input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0'; // Fixed typo
        }

        if (strlen(input) == 0 || strcmp(input, "0") == 0) {
            while (getchar() != '\n'); // Clear input buffer
            return; // Return to main menu
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
        while (getchar() != '\n'); // Clear input buffer after each iteration
    }
}

// Debut Management function
void debut_management() {
    printf("\nDebut Management System\n");
    printf("Functionality to be implemented.\n");
    printf("Press Enter to return to main menu.\n");
    while (getchar() != '\n'); // Clear input buffer
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
    printf("Do you want to input evaluation results? (Y/N): ");
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
        printf("Invalid input. Please enter Y or N.\n");
    }
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

// Main function
int main() {
    char input[MAX_INPUT];

    while (1) {
        display_main_menu();
        fgets(input, MAX_INPUT, stdin);
        if (strlen(input) > 0 && input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0';
        }

        // Check for exit conditions
        if (strlen(input) == 0 || strcmp(input, "0") == 0 || toupper(input[0]) == 'Q') {
            printf("Exiting Magrathea Program.\n");
            break;
        }

        // Handle main menu choices
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
