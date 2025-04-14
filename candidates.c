#include <stdio.h>

// 구조체 정의
typedef struct {
    char name[50];
    int birth_Year;
    int birth_Month;
    int birth_Day;
    char gender[10];
    char email[100];
    char country[10];
    float BMI;
    char main_skill[50];
    char active_skill[50];
    int topic;
    char MBTI[30];
    char introduce[500];
} MemberInfo;

// 만 나이 계산 함수 (이제 출력할 때 나이를 구할 필요 없이 직접 출력)
int calculate_age(int birth_Year) {
    int current_year = 2025;  // 현재 연도를 2025로 설정
    int age = current_year - birth_Year; // 현재 연도 - 출생년도
    return age;
}

int main() {
    int i = 0;
    
    // 구조체 배열 선언
    MemberInfo candidates[6];
    
    // 입력
    while (i < 6) {
        printf("####################################\n");
        printf("     오디션 후보자 데이터 입력       \n");
        printf("####################################\n");
        printf("%d번째 후보자 정보를 입력합니다.\n", i + 1);
        printf("------------------------------------\n");
    
        printf("1. 성명: ");
        scanf("%s", candidates[i].name);
    
        printf("2. 생일 (예: 2006/04/18): ");
        scanf("%d/%d/%d", &candidates[i].birth_Year, &candidates[i].birth_Month, &candidates[i].birth_Day);
    
        printf("3. 성별: ");
        scanf("%s", candidates[i].gender);
    
        printf("4. 메일 주소: ");
        scanf("%s", candidates[i].email);
    
        printf("5. 국적: ");
        scanf("%s", candidates[i].country);
    
        printf("6. BMI: ");
        scanf("%f", &candidates[i].BMI);
    
        printf("7. 주 스킬: ");
        scanf("%s", candidates[i].main_skill);
    
        printf("8. 보조 스킬: ");
        scanf("%s", candidates[i].active_skill);
    
        printf("9. 한국어 등급(TOPIK) 점수: ");
        scanf("%d", &candidates[i].topic);
    
        printf("10. MBTI: ");
        scanf("%s", candidates[i].MBTI);

        printf("11. 소개: ");
        scanf("%s", candidates[i].introduce);

        printf("=================================\n");
        i++;
    }
    
    // 출력
    printf("####################################\n");
    printf("     오디션 후보자 데이터 조회 \n");
    printf("####################################\n");
    printf("=============================================================================================\n");
    printf("성   명 | 생년월일  | 성별 | 메   일            | 국적 | BMI  | 주스킬 | 보조스킬 | TOPIK | MBTI\n");
    printf("=============================================================================================\n");

    for (i = 0; i < 6; i++) {
        int age = calculate_age(candidates[i].birth_Year);
        printf("%s(%d) | %d/%d/%d | %s | %s                  | %s | %f | %s | %s | %d | %s\n",
               candidates[i].name, age, candidates[i].birth_Year, candidates[i].birth_Month, candidates[i].birth_Day,
               candidates[i].gender, candidates[i].email, candidates[i].country, candidates[i].BMI,
               candidates[i].main_skill, candidates[i].active_skill, candidates[i].topic, candidates[i].MBTI);
        printf("-------------------------------------------------------------------------------------\n");
        printf("%s\n", candidates[i].introduce);
        printf("-------------------------------------------------------------------------------------\n");
    }

    return 0;
}

