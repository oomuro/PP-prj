#include <stdio.h>

#define SIZE 1000
#define LENGTH 100

int newline = 0;

void return_exact(char text[SIZE], char odd[][SIZE], int exact[][SIZE], int i, int j, int k);

void match_exact(char text[SIZE], char odd[][SIZE], int magic, int exact[][SIZE], int nth, int j);

int main() {
    char char_temp[LENGTH][SIZE] = {{0}};
    int i, j;
    int count = 0;
    char text[SIZE];

    count = 0;
    for (i = 0; i < LENGTH; i++) {
        fgets(char_temp[i], SIZE, stdin);
//        printf("%s", char_temp[i]);
        count++;
        if (char_temp[i][0] == '0') {
            break;
        }
    }
//    printf("%d\n", count);

    for (i = 0; i < SIZE; i++) {
        if (char_temp[0][i] == '\n') {
            newline = i;
        }
    }
//    printf("%d\n", newline);

    int magic = (count - 2) / 2;
    char odd[magic][SIZE];
    char even[magic][SIZE];

    for (i = 0; i < SIZE; i++) {
        text[i] = char_temp[0][i];
    }
//    printf("%s", text);

    for (i = 0; i < magic; i++) {
        for (j = 0; j < SIZE; j++) {
            odd[i][j] = char_temp[2 * i + 1][j];
            even[i][j] = char_temp[2 * i + 2][j];
        }
    }
//    for (i = 0; i < magic; i++) {
//        printf("%s", odd[i]);
//        printf("%s", even[i]);
//    }

    int length_odd[magic];
    for (i = 0; i < magic; i++) {
        for (j = 0; j < SIZE; j++) {
            if (odd[i][j] == '\n') {
                length_odd[i] = j;
//                printf("%d\n", length_odd[i]);
            }
        }
    }

    int length_even[magic];
    for (i = 0; i < magic; i++) {
        for (j = 0; j < SIZE; j++) {
            if (even[i][j] == '\n') {
                length_even[i] = j;
//                printf("%d\n", length_even[i]);
            }
        }
    }

    int difference[magic];
    for (i = 0; i < magic; i++) {
        difference[i] = length_even[i] - length_odd[i];
    }
    for (i = 0; i < magic; i++) {
//        printf("%d ", difference[i]);
    }
//    printf("\n");

    int exact[magic][SIZE];
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
//                    printf("exact[%d][%d] = %d\n", i, j, exact[i][j]);
                }
            }


        }
    }

    ///////////////////////////////////////////////////////////////////////

    int nth = 0; // 실행시 증가시켜나갈 예정
    match_exact(text, odd, magic, exact, nth, j);

//    for (i = 0; i < magic; i++) {
//        printf("%d\n", i + 1);
//        for (j = 0; j < newline; j++) {
//            printf("%d", exact[i][j]);
//        }
//        printf("\n");
//    }
//    printf("\n");

    int target[magic][newline];
    for (i = 0; i < magic; i++) {
        for (j = 0; j < newline; j++) {
            target[i][j] = 0;
//            printf("%d", target[i][j]);
        }
    }

    for (i = 0; i < magic; i++) {
//        printf("%d번째\n", i + 1);
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
//                    printf("length_odd[%d] = %d, %d가 시작점\n", i, length_odd[i], j);
                    target[i][count3] = j;
                    count3++;
                } else if (count2 != length_odd[i]) {
                    count2 = 0;
                }
            }
        }
    }

    int target_end[magic];
    for (i = 0; i < magic; i++) {
        target_end[i] = 0;
    }
    for (i = 0; i < magic; i++) {
        for (j = 0; j < newline; j++) {
//            printf("%d", target[i][j]);
            if (target[i][j] != 0) {
                target_end[i]++;
            }
        }
//        printf("\n");
    }
    for (i = 0; i < magic; i++) {
//        printf("%d ", target_end[i]);
    }
//    printf("\n");

    int line_diff[magic];
    for (i = 0; i < magic; i++) {
        line_diff[i] = target_end[i] * difference[i];
    }

    char temp[SIZE];
    for (i = 0; i < SIZE; i++) {
        temp[i] = text[i];
    }
    int count4 = 0;
    newline += line_diff[0];
    if (difference > 0) {
        for (i = newline - 1; i >= 0; i--) {

        }
    } else if (difference < 0) {
        for (i = 0; i < newline; i++) {

        }
    }

    for (i = 0; i < SIZE; i++) {
        int t = 0;
        if (i == target[0][t]) {
            for (j = 0; j < length_odd[0]; j++) {
                text[i + j] = even[0][j];
            }
            t++;
            if (t == target_end[0]) {
                break;
            }
        }
    }

    for (i = 0; i < newline; i++) {
        printf("%c", text[i]);
    }
    printf("\n");

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void return_exact(char text[SIZE], char odd[][SIZE], int exact[][SIZE], int i, int j, int k) {
    if (text[j] == odd[i][k]) {
        if (text[j + 1] == odd[i][k + 1]) {
//            printf("%3d ", j);
            exact[i][j] = 1;
            if (text[j + 2] == odd[i][k + 2]) {
                exact[i][j + 2] = 1;
            }
        }
        j++;
        k++;
        return_exact(text, odd, exact, i, j, k);
    }
}

void match_exact(char text[SIZE], char odd[][SIZE], int magic, int exact[][SIZE], int nth, int j) {
    for (int i = nth; i < magic; i++) {
//        printf("%d번쨰\n", i + 1);
        for (int j = 0; j < newline; j++) {
            return_exact(text, odd, exact, i, j, 0);
        }
//        printf("\n");
    }
}