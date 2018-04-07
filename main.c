#include <stdio.h>

#define SIZE 1000

void return_exact(char a[][SIZE], int b[][SIZE], int c, int i, int j);

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
//    for (int i = 0; i < SIZE; i++) {
//        printf("%c", char_temp[i]);
//    }
//    printf("\n");

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
//    for (int i = 0; i < count; i++) {
//        printf("%d %d\n", newline_number[i], i);
//    }

    // 카운트 확인용
//    printf("%d\n", count);

    // 마지막 문자 번호 부여
    int last_index = newline_number[count - 1];

    // 마지막 문자 번호 확인
//    printf("%d\n\n", last_index);

    // 문자 배열 선언
    char text[count][SIZE];

    // 문자 배열에 텍스트 할당
    for (int j = 0; j < newline_number[0]; j++) {
        text[0][j] = char_temp[j];
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = newline_number[i] + 1; j < newline_number[i + 1]; j++) {
            text[i + 1][j] = char_temp[j];
        }
    }

    // 문자 배열 확인용
//    for (int i = 0; i < newline_number[0]; i++) {
//        printf("%c", text[0][i]);
//    }
//    printf("\n");
//    for (int i = 1; i < count; i++) {
//        for (int j = newline_number[i - 1] + 1; j < newline_number[i]; j++) {
//            printf("%c", text[i][j]);
//        }
//        printf("\n");
//    }
//    printf("\n");

    // 치환용 배열 및 번호 선언(첫번째 문장과 교환)
    char mod_text[SIZE] = {0};
    int exact_num[count][SIZE];

    // 각 문장별 길이 할당('\n' 제외)
    int length[count];
    for (int i = 0; i < count; i++) {
        if (i == 0) {
            length[i] = newline_number[i];
//            printf("%2d번 문장의 길이: %d\n", i, length[i]);
        } else {
            length[i] = newline_number[i] - newline_number[i - 1] - 1;
//            printf("%2d번 문장의 길이: %d\n", i, length[i]);
        }
    }
    printf("\n");

    // 첫 문장에서 단어 검색 및 위치 저장
    {
        int i = 0;
        while (text[i][newline_number[i] - 1] != '0') {
            printf("%d번째\n", i + 1);
            for (int j = 0; j < newline_number[0]; j++) {
//                if (text[0][j] == text[i + 1][newline_number[i] + 1]) {
//                    printf("%3d ", j);
//                    exact_num[i][j] = 1;
//                    if (text[0][j + 1] == text[i + 1][newline_number[i] + 2]) {
//                        printf("\b+ ");
//                        exact_num[i][j + 1] = 1;
//                    }
//                }
                // 재귀적 구조로 if문 반복
                return_exact(text, exact_num, newline_number[i], i, j);
            }
            printf("\n");
            i += 2;
            if (i >= count - 2) {
                break;
            }
        }
    }
    printf("\n");

    // return_exact로 찾은 일치부분을 숫자로 표시(홀수 부분만)
//    for (int i = 0; i < count - 2; i += 2) {
//        printf("%d\n", i + 1);
//        for (int j = 0; j < newline_number[0]; j++) {
//            printf("%d", exact_num[i][j]);
//        }
//        printf("\n");
//    }
//    printf("\n");

    // exact_num에 저장된 숫자 확인
    for (int i = 0; i < count - 2; i += 2) {
        printf("%d\n", i + 1);
        for (int j = 0; j < newline_number[0]; j++) {
            if (exact_num[i][j] == 1) {
                printf("%d", exact_num[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");

    return 0;
}

void return_exact(char a[][SIZE], int b[][SIZE], int c, int i, int j) {
    int k = c;
    int l = j;

    if (a[0][l] == a[i + 1][k + 1]) {
//        printf("%3d ", l);
//        b[i][l] = 1;
        if (a[0][l + 1] == a[i + 1][k + 2]) {
            printf("%3d ", l);
            b[i][l] = 1;
        }
        k++;
        l++;
        return_exact(a, b, k, i, l);
        // 맨 마지막에 하나 더 추가 필요
    }
}