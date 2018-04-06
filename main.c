#include <stdio.h>

#define SIZE 1000

int main() {
    // 임시 문자 배열 선언
    char char_temp[SIZE] = {0};

//    for (int i = 0; i < SIZE; i++) {
//        char_temp[i] = '\0';
//    }

//    fgets(name, 2000, stdin);
//
//    printf("%s\n", name);
//
//    printf("\n");

    // 텍스트 입력
    scanf("%[0-9a-zA-Z.\n ]", char_temp);

    // 입력 확인용
    for (int i = 0; i < SIZE; i++) {
        printf("%c", char_temp[i]);
    }
    printf("\n\n");

    // 테스트용 임시배열 선언
    char tmp[SIZE];

    for (int i = 0; i < SIZE; i++) {
        tmp[i] = char_temp[i];
    }

    // 임시 줄바꿈 배열 선언
    int num_temp[] = {0};

    int count = 0;

    // "\n" 찾아 할당
    // 버그의 온상
    for (int i = 0; i < SIZE; i++) {
        if (tmp[i] == '\n') {
            num_temp[count] = i;
            count += 1;
        }
    }

    // 줄바꿈 배열 선언
    int newline_number[count];

    // 줄바꿈 배열에 위치 할당
    for (int i = 0; i < count; i++) {
        newline_number[i] = num_temp[i];
    }

    // 숫자 확인용
    for (int i = 0; i < count; i++) {
        printf("%d %d\n", newline_number[i], i);
    }

    // 카운트 확인용
    printf("%d\n", count);

    // 마지막 문자 번호 부여
    int last_index = newline_number[count - 1];

    // 마지막 문자 번호 확인
    printf("%d\n", last_index);

    // 문자 배열 선언
    char text[count][last_index];

    // 문자 배열에 텍스트 할당
    for (int j = 0; j < newline_number[0]; j++) {
        text[0][j] = char_temp[j];
    }

    for (int i = 0; i < count-1; i++) {
        for (int j = newline_number[i] + 1; j < newline_number[i + 1]; j++) {
            text[i + 1][j] = char_temp[j];
        }
    }

    // 문자 배열 확인용
    for (int i = 0; i < SIZE; i++) {
        printf("%c", text[0][i]);
    }

    return 0;
}