#include <stdio.h>

#define SIZE 1000
#define LENGTH 100

int newline = 0;

int return_exact(char text[SIZE], char odd[][SIZE], int exact[][SIZE], int i, int j, int k, int length_odd[]);

int main() {
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // 문자 입력 관련 변수들 선언
    char char_temp[LENGTH][SIZE] = {{0}};
    int i, j;
    int count = 0;
    char text[SIZE];
    int nth = 0;
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // 문자 입력 및 count 초기화
    for (i = 0; i < LENGTH; i++) {
        fgets(char_temp[i], SIZE, stdin);
        count++;
        if (char_temp[i][0] == '0') {
            break;
        }
    }
    // magic 선언
    int magic = (count - 2) / 2;
    // magic 테스트
//    printf("magic = %d\n", magic);
    // char_temp 테스트
//    for (i = 0; i < magic * 2 + 1; i++) {
//        printf("char_temp[%d]\n", i);
//        for (j = 0; j < SIZE; j++) {
//            printf("%c", char_temp[i][j]);
//        }
//    }
    // newline 초기화
    for (i = 0; i < SIZE; i++) {
        if (char_temp[0][i] == '\n') {
            newline = i;
        }
    }
    // newline 테스트
//    printf("newline = %d\n", newline);
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // 각종 변수들 선언
    char odd[magic][SIZE];
    char even[magic][SIZE];
    int length_odd[magic];
    int length_even[magic];
    int difference[magic];
    int exact[magic][SIZE];
    int target[magic][newline];
    int target_end[magic];
    int line_diff[magic];
    int count4 = 0;
    int t = 0;
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // text에 첫번째 문장 저장
    for (i = 0; i < SIZE; i++) {
        text[i] = char_temp[0][i];
    }
    // text 테스트
//    printf("text : \n");
//    for (i = 0; i < newline + 1; i++) {
//        printf("%c", text[i]);
//    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // odd, even 관련 배열들 채우기
    for (i = 0; i < magic; i++) {
        for (j = 0; j < SIZE; j++) {
            odd[i][j] = char_temp[2 * i + 1][j];
            even[i][j] = char_temp[2 * i + 2][j];
        }
    }
    for (i = 0; i < magic; i++) {
        for (j = 0; j < SIZE; j++) {
            if (odd[i][j] == '\n') {
                length_odd[i] = j;
            }
        }
    }
    for (i = 0; i < magic; i++) {
        for (j = 0; j < SIZE; j++) {
            if (even[i][j] == '\n') {
                length_even[i] = j;
            }
        }
    }
    // odd, even 테스트
//    for (i = 0; i < magic; i++) {
//        printf("\nodd[%d], even[%d]\n", i, i);
//        for (j = 0; j < length_odd[i] + 1; j++) {
//            printf("%c", odd[i][j]);
//        }
//        for (j = 0; j < length_even[i] + 1; j++) {
//            printf("%c", even[i][j]);
//        }
//    }
    // length_odd, length_even 테스트
//    for (i = 0; i < magic; i++) {
//        printf("length_odd[%d] = %d\n", i, length_odd[i]);
//    }
//    for (i = 0; i < magic; i++) {
//        printf("length_even[%d] = %d\n", i, length_even[i]);
//    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // difference 초기화
    for (i = 0; i < magic; i++) {
        difference[i] = length_even[i] - length_odd[i];
    }
    // difference 테스트
//    for (i = 0; i < magic; i++) {
//        printf("difference[%d] = %d\n", i, difference[i]);
//    }
    //////////////////////////////////////////////////////////////////////////////////////////////////



    //////////////////////////////////////////////////////////////////////////////////////////////////
    // exact 초기화
    for (i = 0; i < magic; i++) {
        for (j = 0; j < newline; j++) {
            exact[i][j] = 0;
        }
    }
    for (i = 0; i < magic; i++) {
        for (j = 0; j < newline - length_odd[i]; j++) {
            int real = 0;
            int match[length_odd[i]];
            int tmp = 0;
            for (int t = 0; t < length_odd[i]; t++) {
                match[t] = 0;
            }
            for (int k = 0; k < length_odd[i]; k++) {
                if (text[j + k] == odd[i][j + k]) {
                    match[k] = 1;
                    tmp = real && match[k];
                    real = tmp;
                } else {
                    match[k] = 0;
                    tmp = real && match[k];
                    real = tmp;
                }
                if ((k == length_odd[i] - 1) && (real == 1)) {
                    exact[i][j] = 1;
                }
            }
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // match_exact + return_exact
    for (i = nth; i < magic; i++) {
        for (j = 0; j < newline; j++) {
            int ok = return_exact(text, odd, exact, i, j, 0, length_odd);
            if (ok == 1) {
                j += length_odd[i];
            }
        }
    }
    // exact 테스트
//    for (i = 0; i < magic; i++) {
//        printf("%d\n", i + 1);
//        for (j = 0; j < newline; j++) {
//            printf("%d", exact[i][j]);
//        }
//        printf("\n");
//    }
//    printf("\n");
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // target 초기화
    for (i = nth; i < magic; i++) {
        for (j = 0; j < newline; j++) {
            target[i][j] = 0;
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // target_end 초기화
    for (i = nth; i < magic; i++) {
        target_end[i] = 0;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // target 저장
    for (i = nth; i < magic; i++) {
        int count3 = 0;
        for (j = 0; j < SIZE; j++) {
            int count2 = 0;
            if (exact[i][j] == 1) {
                for (int k = 0; k < length_odd[i]; k++) {
                    if (exact[i][j + k] == 1) {
                        count2++;
                    }
                }
                if (count2 == length_odd[i]) {
                    target[i][count3] = j;
                    count3++;
                } else if (count2 != length_odd[i]) {
                    count2 = 0;
                }
            }
        }
    }
    // target 테스트
//    for (i = 0; i < magic; i++) {
//        printf("target[%d] :\n", i);
//        for (j = 0; j < SIZE; j++) {
//            printf("%d", target[i][j]);
//        }
//        printf("\n");
//    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // target_end 저장
    for (i = nth; i < magic; i++) {
        for (j = 0; j < newline / (length_even[i] + 1); j++) {
            if (target[i][j] != 0) {
                target_end[i]++;
            }
        }
    }
    //target_end 테스트
    for (i = 0; i < magic; i++) {
        printf("target_end[%d] = %d\n", i, target_end[i]);
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // line_diff 저장
    for (i = nth; i < magic; i++) {
        line_diff[i] = target_end[i] * difference[i];
    }
    // line_diff 테스트
//    for (i = 0; i < magic; i++) {
//        printf("line_diff[%d] = %d\n", i, line_diff[i]);
//    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // change
    i = nth;
//        printf("nth = %d\n", i);
//    printf("difference[%d] = %d\n", i, difference[i]);

    count4 = 0;

    newline += line_diff[i];
    printf("newline = %d\n", newline);

    // 루프 수정 필요
    if (difference[i] > 0) {
        count4 = target_end[i];
        for (j = newline; j >= 0; j--) {
            while (count4 > 0) {
                if (target[i][count4 - 1] == j) {
                    count4--;
                }
                text[j + difference[i] * count4] = text[j];
                j--;
            }

        }
    } else if (difference[i] < 0) {
        count4 = 0;
        for (j = 0; j <= newline; j++) {
            while (count4 <= target_end[i]) {
                text[j + difference[i] * count4] = text[j];
                if (target[i][count4] == j) {
                    count4++;
                }
                if (j == newline) {
                    break;
                }
                j++;
            }
        }
    }

    t = 0;
    for (int k = 0; k < newline; k++) {
        if (k == target[i][t] + difference[i] * t) {
            for (j = 0; j < length_even[i]; j++) {
                text[k + j] = even[i][j];
            }
            t++;
            if (t == target_end[i]) {
                break;
            }
        }
    }
    text[newline] = '\n';
//        for (int clear = newline + 1; clear < SIZE; clear++) {
//            text[clear] = 0;
//        }

    for (int k = 0; k < newline; k++) {
        printf("%c", text[k]);
    }
    printf("\n");
    printf("text[newline] = %d\n", text[newline]);
    //////////////////////////////////////////////////////////////////////////////////////////////////
    nth++;
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // exact 초기화
    for (i = 0; i < magic; i++) {
        for (j = 0; j < newline; j++) {
            exact[i][j] = 0;
        }
    }
    for (i = 0; i < magic; i++) {
        for (j = 0; j < newline - length_odd[i]; j++) {
            int real = 0;
            int match[length_odd[i]];
            int tmp = 0;
            for (int t = 0; t < length_odd[i]; t++) {
                match[t] = 0;
            }
            for (int k = 0; k < length_odd[i]; k++) {
                if (text[j + k] == odd[i][j + k]) {
                    match[k] = 1;
                    tmp = real && match[k];
                    real = tmp;
                } else {
                    match[k] = 0;
                    tmp = real && match[k];
                    real = tmp;
                }
                if ((k == length_odd[i] - 1) && (real == 1)) {
                    exact[i][j] = 1;
                }
            }
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // match_exact + return_exact
    for (i = nth; i < magic; i++) {
        for (j = 0; j < newline; j++) {
            int ok = return_exact(text, odd, exact, i, j, 0, length_odd);
            if (ok == 1) {
                j += length_odd[i];
            }
        }
    }
    // exact 테스트
//    for (i = 0; i < magic; i++) {
//        printf("%d\n", i + 1);
//        for (j = 0; j < newline; j++) {
//            printf("%d", exact[i][j]);
//        }
//        printf("\n");
//    }
//    printf("\n");
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // target 초기화
    for (i = nth; i < magic; i++) {
        for (j = 0; j < newline; j++) {
            target[i][j] = 0;
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // target_end 초기화
    for (i = nth; i < magic; i++) {
        target_end[i] = 0;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // target 저장
    for (i = nth; i < magic; i++) {
        int count3 = 0;
        for (j = 0; j < SIZE; j++) {
            int count2 = 0;
            if (exact[i][j] == 1) {
                for (int k = 0; k < length_odd[i]; k++) {
                    if (exact[i][j + k] == 1) {
                        count2++;
                    }
                }
                if (count2 == length_odd[i]) {
                    target[i][count3] = j;
                    count3++;
                } else if (count2 != length_odd[i]) {
                    count2 = 0;
                }
            }
        }
    }
    // target 테스트
//    for (i = 0; i < magic; i++) {
//        printf("target[%d] :\n", i);
//        for (j = 0; j < SIZE; j++) {
//            printf("%d", target[i][j]);
//        }
//        printf("\n");
//    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // target_end 저장
    for (i = nth; i < magic; i++) {
        for (j = 0; j < newline / (length_even[i] + 1); j++) {
            if (target[i][j] != 0) {
                target_end[i]++;
            }
        }
    }
    //target_end 테스트
    for (i = 0; i < magic; i++) {
        printf("target_end[%d] = %d\n", i, target_end[i]);
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // line_diff 저장
    for (i = nth; i < magic; i++) {
        line_diff[i] = target_end[i] * difference[i];
    }
    // line_diff 테스트
//    for (i = 0; i < magic; i++) {
//        printf("line_diff[%d] = %d\n", i, line_diff[i]);
//    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // change
    i = nth;
//        printf("nth = %d\n", i);
//    printf("difference[%d] = %d\n", i, difference[i]);

    count4 = 0;

    newline += line_diff[i];
    printf("newline = %d\n", newline);

    // 루프 수정 필요
    if (difference[i] > 0) {
        count4 = target_end[i];
        for (j = newline; j >= 0; j--) {
            while (count4 > 0) {
                if (target[i][count4 - 1] == j) {
                    count4--;
                }
                text[j + difference[i] * count4] = text[j];
                j--;
            }

        }
    } else if (difference[i] < 0) {
        count4 = 0;
        for (j = 0; j <= newline; j++) {
            while (count4 <= target_end[i]) {
                text[j + difference[i] * count4] = text[j];
                if (target[i][count4] == j) {
                    count4++;
                }
                if (j == newline) {
                    break;
                }
                j++;
            }
        }
    }

    t = 0;
    for (int k = 0; k < newline; k++) {
        if (k == target[i][t] + difference[i] * t) {
            for (j = 0; j < length_even[i]; j++) {
                text[k + j] = even[i][j];
            }
            t++;
            if (t == target_end[i]) {
                break;
            }
        }
    }
    text[newline] = '\n';
//        for (int clear = newline + 1; clear < SIZE; clear++) {
//            text[clear] = 0;
//        }

    for (int k = 0; k < newline; k++) {
        printf("%c", text[k]);
    }
    printf("\n");
    printf("text[newline] = %d\n", text[newline]);
    //////////////////////////////////////////////////////////////////////////////////////////////////
    nth++;
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // exact 초기화
    for (i = 0; i < magic; i++) {
        for (j = 0; j < newline; j++) {
            exact[i][j] = 0;
        }
    }
    for (i = 0; i < magic; i++) {
        for (j = 0; j < newline - length_odd[i]; j++) {
            int real = 0;
            int match[length_odd[i]];
            int tmp = 0;
            for (int t = 0; t < length_odd[i]; t++) {
                match[t] = 0;
            }
            for (int k = 0; k < length_odd[i]; k++) {
                if (text[j + k] == odd[i][j + k]) {
                    match[k] = 1;
                    tmp = real && match[k];
                    real = tmp;
                } else {
                    match[k] = 0;
                    tmp = real && match[k];
                    real = tmp;
                }
                if ((k == length_odd[i] - 1) && (real == 1)) {
                    exact[i][j] = 1;
                }
            }
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // match_exact + return_exact
    for (i = nth; i < magic; i++) {
        for (j = 0; j < newline; j++) {
            int ok = return_exact(text, odd, exact, i, j, 0, length_odd);
            if (ok == 1) {
                j += length_odd[i];
            }
        }
    }
    // exact 테스트
//    for (i = 0; i < magic; i++) {
//        printf("%d\n", i + 1);
//        for (j = 0; j < newline; j++) {
//            printf("%d", exact[i][j]);
//        }
//        printf("\n");
//    }
//    printf("\n");
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // target 초기화
    for (i = nth; i < magic; i++) {
        for (j = 0; j < newline; j++) {
            target[i][j] = 0;
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // target_end 초기화
    for (i = nth; i < magic; i++) {
        target_end[i] = 0;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // target 저장
    for (i = nth; i < magic; i++) {
        int count3 = 0;
        for (j = 0; j < SIZE; j++) {
            int count2 = 0;
            if (exact[i][j] == 1) {
                for (int k = 0; k < length_odd[i]; k++) {
                    if (exact[i][j + k] == 1) {
                        count2++;
                    }
                }
                if (count2 == length_odd[i]) {
                    target[i][count3] = j;
                    count3++;
                } else if (count2 != length_odd[i]) {
                    count2 = 0;
                }
            }
        }
    }
    // target 테스트
//    for (i = 0; i < magic; i++) {
//        printf("target[%d] :\n", i);
//        for (j = 0; j < SIZE; j++) {
//            printf("%d", target[i][j]);
//        }
//        printf("\n");
//    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // target_end 저장
    for (i = nth; i < magic; i++) {
        for (j = 0; j < newline / (length_even[i] + 1); j++) {
            if (target[i][j] != 0) {
                target_end[i]++;
            }
        }
    }
    //target_end 테스트
    for (i = 0; i < magic; i++) {
        printf("target_end[%d] = %d\n", i, target_end[i]);
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // line_diff 저장
    for (i = nth; i < magic; i++) {
        line_diff[i] = target_end[i] * difference[i];
    }
    // line_diff 테스트
//    for (i = 0; i < magic; i++) {
//        printf("line_diff[%d] = %d\n", i, line_diff[i]);
//    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // change
    i = nth;
//        printf("nth = %d\n", i);
//    printf("difference[%d] = %d\n", i, difference[i]);

    count4 = 0;

    newline += line_diff[i];
    printf("newline = %d\n", newline);

    // 루프 수정 필요
    if (difference[i] > 0) {
        count4 = target_end[i];
        for (j = newline; j >= 0; j--) {
            while (count4 > 0) {
                if (target[i][count4 - 1] == j) {
                    count4--;
                }
                text[j + difference[i] * count4] = text[j];
                j--;
            }

        }
    } else if (difference[i] < 0) {
        count4 = 0;
        for (j = 0; j <= newline; j++) {
            while (count4 <= target_end[i]) {
                text[j + difference[i] * count4] = text[j];
                if (target[i][count4] == j) {
                    count4++;
                }
                if (j == newline) {
                    break;
                }
                j++;
            }
        }
    }

    t = 0;
    for (int k = 0; k < newline; k++) {
        if (k == target[i][t] + difference[i] * t) {
            for (j = 0; j < length_even[i]; j++) {
                text[k + j] = even[i][j];
            }
            t++;
            if (t == target_end[i]) {
                break;
            }
        }
    }
    text[newline] = '\n';
//        for (int clear = newline + 1; clear < SIZE; clear++) {
//            text[clear] = 0;
//        }

    for (int k = 0; k < newline; k++) {
        printf("%c", text[k]);
    }
    printf("\n");
    printf("text[newline] = %d\n", text[newline]);
    //////////////////////////////////////////////////////////////////////////////////////////////////
    nth++;
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // exact 초기화
    for (i = 0; i < magic; i++) {
        for (j = 0; j < newline; j++) {
            exact[i][j] = 0;
        }
    }
    for (i = 0; i < magic; i++) {
        for (j = 0; j < newline - length_odd[i]; j++) {
            int real = 0;
            int match[length_odd[i]];
            int tmp = 0;
            for (int t = 0; t < length_odd[i]; t++) {
                match[t] = 0;
            }
            for (int k = 0; k < length_odd[i]; k++) {
                if (text[j + k] == odd[i][j + k]) {
                    match[k] = 1;
                    tmp = real && match[k];
                    real = tmp;
                } else {
                    match[k] = 0;
                    tmp = real && match[k];
                    real = tmp;
                }
                if ((k == length_odd[i] - 1) && (real == 1)) {
                    exact[i][j] = 1;
                }
            }
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // match_exact + return_exact
    for (i = nth; i < magic; i++) {
        for (j = 0; j < newline; j++) {
            int ok = return_exact(text, odd, exact, i, j, 0, length_odd);
            if (ok == 1) {
                j += length_odd[i];
            }
        }
    }
    // exact 테스트
//    for (i = 0; i < magic; i++) {
//        printf("%d\n", i + 1);
//        for (j = 0; j < newline; j++) {
//            printf("%d", exact[i][j]);
//        }
//        printf("\n");
//    }
//    printf("\n");
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // target 초기화
    for (i = nth; i < magic; i++) {
        for (j = 0; j < newline; j++) {
            target[i][j] = 0;
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // target_end 초기화
    for (i = nth; i < magic; i++) {
        target_end[i] = 0;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // target 저장
    for (i = nth; i < magic; i++) {
        int count3 = 0;
        for (j = 0; j < SIZE; j++) {
            int count2 = 0;
            if (exact[i][j] == 1) {
                for (int k = 0; k < length_odd[i]; k++) {
                    if (exact[i][j + k] == 1) {
                        count2++;
                    }
                }
                if (count2 == length_odd[i]) {
                    target[i][count3] = j;
                    count3++;
                } else if (count2 != length_odd[i]) {
                    count2 = 0;
                }
            }
        }
    }
    // target 테스트
//    for (i = 0; i < magic; i++) {
//        printf("target[%d] :\n", i);
//        for (j = 0; j < SIZE; j++) {
//            printf("%d", target[i][j]);
//        }
//        printf("\n");
//    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // target_end 저장
    for (i = nth; i < magic; i++) {
        for (j = 0; j < newline / (length_even[i] + 1); j++) {
            if (target[i][j] != 0) {
                target_end[i]++;
            }
        }
    }
    //target_end 테스트
    for (i = 0; i < magic; i++) {
        printf("target_end[%d] = %d\n", i, target_end[i]);
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // line_diff 저장
    for (i = nth; i < magic; i++) {
        line_diff[i] = target_end[i] * difference[i];
    }
    // line_diff 테스트
//    for (i = 0; i < magic; i++) {
//        printf("line_diff[%d] = %d\n", i, line_diff[i]);
//    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // change
    i = nth;
//        printf("nth = %d\n", i);
//    printf("difference[%d] = %d\n", i, difference[i]);

    count4 = 0;

    newline += line_diff[i];
    printf("newline = %d\n", newline);

    // 루프 수정 필요
    if (difference[i] > 0) {
        count4 = target_end[i];
        for (j = newline; j >= 0; j--) {
            while (count4 > 0) {
                if (target[i][count4 - 1] == j) {
                    count4--;
                }
                text[j + difference[i] * count4] = text[j];
                j--;
            }

        }
    } else if (difference[i] < 0) {
        count4 = 0;
        for (j = 0; j <= newline; j++) {
            while (count4 <= target_end[i]) {
                text[j + difference[i] * count4] = text[j];
                if (target[i][count4] == j) {
                    count4++;
                }
                if (j == newline) {
                    break;
                }
                j++;
            }
        }
    }

    t = 0;
    for (int k = 0; k < newline; k++) {
        if (k == target[i][t] + difference[i] * t) {
            for (j = 0; j < length_even[i]; j++) {
                text[k + j] = even[i][j];
            }
            t++;
            if (t == target_end[i]) {
                break;
            }
        }
    }
    text[newline] = '\n';
//        for (int clear = newline + 1; clear < SIZE; clear++) {
//            text[clear] = 0;
//        }

    for (int k = 0; k < newline; k++) {
        printf("%c", text[k]);
    }
    printf("\n");
    printf("text[newline] = %d\n", text[newline]);
    //////////////////////////////////////////////////////////////////////////////////////////////////
    nth++;
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // exact 초기화
    for (i = 0; i < magic; i++) {
        for (j = 0; j < newline; j++) {
            exact[i][j] = 0;
        }
    }
    for (i = 0; i < magic; i++) {
        for (j = 0; j < newline - length_odd[i]; j++) {
            int real = 0;
            int match[length_odd[i]];
            int tmp = 0;
            for (int t = 0; t < length_odd[i]; t++) {
                match[t] = 0;
            }
            for (int k = 0; k < length_odd[i]; k++) {
                if (text[j + k] == odd[i][j + k]) {
                    match[k] = 1;
                    tmp = real && match[k];
                    real = tmp;
                } else {
                    match[k] = 0;
                    tmp = real && match[k];
                    real = tmp;
                }
                if ((k == length_odd[i] - 1) && (real == 1)) {
                    exact[i][j] = 1;
                }
            }
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // match_exact + return_exact
    for (i = nth; i < magic; i++) {
        for (j = 0; j < newline; j++) {
            int ok = return_exact(text, odd, exact, i, j, 0, length_odd);
            if (ok == 1) {
                j += length_odd[i];
            }
        }
    }
    // exact 테스트
//    for (i = 0; i < magic; i++) {
//        printf("%d\n", i + 1);
//        for (j = 0; j < newline; j++) {
//            printf("%d", exact[i][j]);
//        }
//        printf("\n");
//    }
//    printf("\n");
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // target 초기화
    for (i = nth; i < magic; i++) {
        for (j = 0; j < newline; j++) {
            target[i][j] = 0;
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // target_end 초기화
    for (i = nth; i < magic; i++) {
        target_end[i] = 0;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // target 저장
    for (i = nth; i < magic; i++) {
        int count3 = 0;
        for (j = 0; j < SIZE; j++) {
            int count2 = 0;
            if (exact[i][j] == 1) {
                for (int k = 0; k < length_odd[i]; k++) {
                    if (exact[i][j + k] == 1) {
                        count2++;
                    }
                }
                if (count2 == length_odd[i]) {
                    target[i][count3] = j;
                    count3++;
                } else if (count2 != length_odd[i]) {
                    count2 = 0;
                }
            }
        }
    }
    // target 테스트
//    for (i = 0; i < magic; i++) {
//        printf("target[%d] :\n", i);
//        for (j = 0; j < SIZE; j++) {
//            printf("%d", target[i][j]);
//        }
//        printf("\n");
//    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // target_end 저장
    for (i = nth; i < magic; i++) {
        for (j = 0; j < newline / (length_even[i] + 1); j++) {
            if (target[i][j] != 0) {
                target_end[i]++;
            }
        }
    }
    //target_end 테스트
    for (i = 0; i < magic; i++) {
        printf("target_end[%d] = %d\n", i, target_end[i]);
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // line_diff 저장
    for (i = nth; i < magic; i++) {
        line_diff[i] = target_end[i] * difference[i];
    }
    // line_diff 테스트
//    for (i = 0; i < magic; i++) {
//        printf("line_diff[%d] = %d\n", i, line_diff[i]);
//    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // change
    i = nth;
//        printf("nth = %d\n", i);
//    printf("difference[%d] = %d\n", i, difference[i]);

    count4 = 0;

    newline += line_diff[i];
    printf("newline = %d\n", newline);

    // 루프 수정 필요
    if (difference[i] > 0) {
        count4 = target_end[i];
        for (j = newline; j >= 0; j--) {
            while (count4 > 0) {
                if (target[i][count4 - 1] == j) {
                    count4--;
                }
                text[j + difference[i] * count4] = text[j];
                j--;
            }

        }
    } else if (difference[i] < 0) {
        count4 = 0;
        for (j = 0; j <= newline; j++) {
            while (count4 <= target_end[i]) {
                text[j + difference[i] * count4] = text[j];
                if (target[i][count4] == j) {
                    count4++;
                }
                if (j == newline) {
                    break;
                }
                j++;
            }
        }
    }

    t = 0;
    for (int k = 0; k < newline; k++) {
        if (k == target[i][t] + difference[i] * t) {
            for (j = 0; j < length_even[i]; j++) {
                text[k + j] = even[i][j];
            }
            t++;
            if (t == target_end[i]) {
                break;
            }
        }
    }
    text[newline] = '\n';
//        for (int clear = newline + 1; clear < SIZE; clear++) {
//            text[clear] = 0;
//        }

    for (int k = 0; k < newline; k++) {
        printf("%c", text[k]);
    }
    printf("\n");
    printf("text[newline] = %d\n", text[newline]);
    //////////////////////////////////////////////////////////////////////////////////////////////////
    nth++;
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // exact 초기화
    for (i = 0; i < magic; i++) {
        for (j = 0; j < newline; j++) {
            exact[i][j] = 0;
        }
    }
    for (i = 0; i < magic; i++) {
        for (j = 0; j < newline - length_odd[i]; j++) {
            int real = 0;
            int match[length_odd[i]];
            int tmp = 0;
            for (int t = 0; t < length_odd[i]; t++) {
                match[t] = 0;
            }
            for (int k = 0; k < length_odd[i]; k++) {
                if (text[j + k] == odd[i][j + k]) {
                    match[k] = 1;
                    tmp = real && match[k];
                    real = tmp;
                } else {
                    match[k] = 0;
                    tmp = real && match[k];
                    real = tmp;
                }
                if ((k == length_odd[i] - 1) && (real == 1)) {
                    exact[i][j] = 1;
                }
            }
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // match_exact + return_exact
    for (i = nth; i < magic; i++) {
        for (j = 0; j < newline; j++) {
            int ok = return_exact(text, odd, exact, i, j, 0, length_odd);
            if (ok == 1) {
                j += length_odd[i];
            }
        }
    }
    // exact 테스트
//    for (i = 0; i < magic; i++) {
//        printf("%d\n", i + 1);
//        for (j = 0; j < newline; j++) {
//            printf("%d", exact[i][j]);
//        }
//        printf("\n");
//    }
//    printf("\n");
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // target 초기화
    for (i = nth; i < magic; i++) {
        for (j = 0; j < newline; j++) {
            target[i][j] = 0;
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // target_end 초기화
    for (i = nth; i < magic; i++) {
        target_end[i] = 0;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // target 저장
    for (i = nth; i < magic; i++) {
        int count3 = 0;
        for (j = 0; j < SIZE; j++) {
            int count2 = 0;
            if (exact[i][j] == 1) {
                for (int k = 0; k < length_odd[i]; k++) {
                    if (exact[i][j + k] == 1) {
                        count2++;
                    }
                }
                if (count2 == length_odd[i]) {
                    target[i][count3] = j;
                    count3++;
                } else if (count2 != length_odd[i]) {
                    count2 = 0;
                }
            }
        }
    }
    // target 테스트
//    for (i = 0; i < magic; i++) {
//        printf("target[%d] :\n", i);
//        for (j = 0; j < SIZE; j++) {
//            printf("%d", target[i][j]);
//        }
//        printf("\n");
//    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // target_end 저장
    for (i = nth; i < magic; i++) {
        for (j = 0; j < newline / (length_even[i] + 1); j++) {
            if (target[i][j] != 0) {
                target_end[i]++;
            }
        }
    }
    //target_end 테스트
    for (i = 0; i < magic; i++) {
        printf("target_end[%d] = %d\n", i, target_end[i]);
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // line_diff 저장
    for (i = nth; i < magic; i++) {
        line_diff[i] = target_end[i] * difference[i];
    }
    // line_diff 테스트
//    for (i = 0; i < magic; i++) {
//        printf("line_diff[%d] = %d\n", i, line_diff[i]);
//    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // change
    i = nth;
//        printf("nth = %d\n", i);
//    printf("difference[%d] = %d\n", i, difference[i]);

    count4 = 0;

    newline += line_diff[i];
    printf("newline = %d\n", newline);

    // 루프 수정 필요
    if (difference[i] > 0) {
        count4 = target_end[i];
        for (j = newline; j >= 0; j--) {
            while (count4 > 0) {
                if (target[i][count4 - 1] == j) {
                    count4--;
                }
                text[j + difference[i] * count4] = text[j];
                j--;
            }

        }
    } else if (difference[i] < 0) {
        count4 = 0;
        for (j = 0; j <= newline; j++) {
            while (count4 <= target_end[i]) {
                text[j + difference[i] * count4] = text[j];
                if (target[i][count4] == j) {
                    count4++;
                }
                if (j == newline) {
                    break;
                }
                j++;
            }
        }
    }

    t = 0;
    for (int k = 0; k < newline; k++) {
        if (k == target[i][t] + difference[i] * t) {
            for (j = 0; j < length_even[i]; j++) {
                text[k + j] = even[i][j];
            }
            t++;
            if (t == target_end[i]) {
                break;
            }
        }
    }
    text[newline] = '\n';
//        for (int clear = newline + 1; clear < SIZE; clear++) {
//            text[clear] = 0;
//        }

    for (int k = 0; k < newline; k++) {
        printf("%c", text[k]);
    }
    printf("\n");
    printf("text[newline] = %d\n", text[newline]);
    //////////////////////////////////////////////////////////////////////////////////////////////////
    nth++;
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // exact 초기화
    for (i = 0; i < magic; i++) {
        for (j = 0; j < newline; j++) {
            exact[i][j] = 0;
        }
    }
    for (i = 0; i < magic; i++) {
        for (j = 0; j < newline - length_odd[i]; j++) {
            int real = 0;
            int match[length_odd[i]];
            int tmp = 0;
            for (int t = 0; t < length_odd[i]; t++) {
                match[t] = 0;
            }
            for (int k = 0; k < length_odd[i]; k++) {
                if (text[j + k] == odd[i][j + k]) {
                    match[k] = 1;
                    tmp = real && match[k];
                    real = tmp;
                } else {
                    match[k] = 0;
                    tmp = real && match[k];
                    real = tmp;
                }
                if ((k == length_odd[i] - 1) && (real == 1)) {
                    exact[i][j] = 1;
                }
            }
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // match_exact + return_exact
    for (i = nth; i < magic; i++) {
        for (j = 0; j < newline; j++) {
            int ok = return_exact(text, odd, exact, i, j, 0, length_odd);
            if (ok == 1) {
                j += length_odd[i];
            }
        }
    }
    // exact 테스트
//    for (i = 0; i < magic; i++) {
//        printf("%d\n", i + 1);
//        for (j = 0; j < newline; j++) {
//            printf("%d", exact[i][j]);
//        }
//        printf("\n");
//    }
//    printf("\n");
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // target 초기화
    for (i = nth; i < magic; i++) {
        for (j = 0; j < newline; j++) {
            target[i][j] = 0;
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // target_end 초기화
    for (i = nth; i < magic; i++) {
        target_end[i] = 0;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // target 저장
    for (i = nth; i < magic; i++) {
        int count3 = 0;
        for (j = 0; j < SIZE; j++) {
            int count2 = 0;
            if (exact[i][j] == 1) {
                for (int k = 0; k < length_odd[i]; k++) {
                    if (exact[i][j + k] == 1) {
                        count2++;
                    }
                }
                if (count2 == length_odd[i]) {
                    target[i][count3] = j;
                    count3++;
                } else if (count2 != length_odd[i]) {
                    count2 = 0;
                }
            }
        }
    }
    // target 테스트
//    for (i = 0; i < magic; i++) {
//        printf("target[%d] :\n", i);
//        for (j = 0; j < SIZE; j++) {
//            printf("%d", target[i][j]);
//        }
//        printf("\n");
//    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // target_end 저장
    for (i = nth; i < magic; i++) {
        for (j = 0; j < newline / (length_even[i] + 1); j++) {
            if (target[i][j] != 0) {
                target_end[i]++;
            }
        }
    }
    //target_end 테스트
    for (i = 0; i < magic; i++) {
        printf("target_end[%d] = %d\n", i, target_end[i]);
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // line_diff 저장
    for (i = nth; i < magic; i++) {
        line_diff[i] = target_end[i] * difference[i];
    }
    // line_diff 테스트
//    for (i = 0; i < magic; i++) {
//        printf("line_diff[%d] = %d\n", i, line_diff[i]);
//    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // change
    i = nth;
//        printf("nth = %d\n", i);
//    printf("difference[%d] = %d\n", i, difference[i]);

    count4 = 0;

    newline += line_diff[i];
    printf("newline = %d\n", newline);

    // 루프 수정 필요
    if (difference[i] > 0) {
        count4 = target_end[i];
        for (j = newline; j >= 0; j--) {
            while (count4 > 0) {
                if (target[i][count4 - 1] == j) {
                    count4--;
                }
                text[j + difference[i] * count4] = text[j];
                j--;
            }

        }
    } else if (difference[i] < 0) {
        count4 = 0;
        for (j = 0; j <= newline; j++) {
            while (count4 <= target_end[i]) {
                text[j + difference[i] * count4] = text[j];
                if (target[i][count4] == j) {
                    count4++;
                }
                if (j == newline) {
                    break;
                }
                j++;
            }
        }
    }

    t = 0;
    for (int k = 0; k < newline; k++) {
        if (k == target[i][t] + difference[i] * t) {
            for (j = 0; j < length_even[i]; j++) {
                text[k + j] = even[i][j];
            }
            t++;
            if (t == target_end[i]) {
                break;
            }
        }
    }
    text[newline] = '\n';
//        for (int clear = newline + 1; clear < SIZE; clear++) {
//            text[clear] = 0;
//        }

    for (int k = 0; k < newline; k++) {
        printf("%c", text[k]);
    }
    printf("\n");
    printf("text[newline] = %d\n", text[newline]);
    //////////////////////////////////////////////////////////////////////////////////////////////////
    nth++;


    return 0;
}

int return_exact(char text[SIZE], char odd[][SIZE], int exact[][SIZE], int i, int j, int k, int length_odd[]) {
    int ok = 0;
    if (length_odd[i] >= 4) {
        if (text[j] == odd[i][k]) {
            if (text[j + 1] == odd[i][k + 1]) {
                if (text[j + 2] == odd[i][k + 2]) {
                    exact[i][j] = 1;
                    exact[i][j + 2] = 1;
                    ok = 1;
                }
            }
            j++;
            k++;
            return_exact(text, odd, exact, i, j, k, length_odd);
        }
    } else if (length_odd[i] == 3) {
        if (text[j] == odd[i][k]) {
            if (text[j + 1] == odd[i][k + 1]) {
                if (text[j + 2] == odd[i][k + 2]) {
                    exact[i][j] = 1;
                    exact[i][j + 1] = 1;
                    exact[i][j + 2] = 1;
                    ok = 1;
                }
            }
        }
    } else if (length_odd[i] == 2) {
        if (text[j] == odd[i][k]) {
            if (text[j + 1] == odd[i][k + 1]) {
                exact[i][j] = 1;
                exact[i][j + 1] = 1;
                ok = 1;
            }
        }
    } else if (length_odd[i] == 1) {
        if (text[j] == odd[i][k]) {
            exact[i][j] = 1;
            ok = 1;
        }
    } else if (length_odd[i] == 0) {

    }

    return ok;
}