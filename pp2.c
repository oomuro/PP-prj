#include <stdio.h>

#define SIZE 1000
#define LENGTH 100

int newline = 0;

void return_exact(char text[SIZE], char odd[][SIZE], int exact[][SIZE], int i, int j, int k);

void match_exact(char text[SIZE], char odd[][SIZE], int magic, int exact[][SIZE], int nth, int j);

void change(char text[SIZE], char odd[][SIZE], char even[][SIZE], int magic, int exact[][SIZE], int j, int i,
            int length_odd[], int length_even[], int difference[]);

int main() {
    char char_temp[LENGTH][SIZE] = {{0}};
    int i, j;
    int count = 0;
    char text[SIZE];

    count = 0;
    for (i = 0; i < LENGTH; i++) {
        fgets(char_temp[i], SIZE, stdin);
        count++;
        if (char_temp[i][0] == '0') {
            break;
        }
    }

    for (i = 0; i < SIZE; i++) {
        if (char_temp[0][i] == '\n') {
            newline = i;
        }
    }

    int magic = (count - 2) / 2;
    char odd[magic][SIZE];
    char even[magic][SIZE];

    for (i = 0; i < SIZE; i++) {
        text[i] = char_temp[0][i];
    }

    for (i = 0; i < magic; i++) {
        for (j = 0; j < SIZE; j++) {
            odd[i][j] = char_temp[2 * i + 1][j];
            even[i][j] = char_temp[2 * i + 2][j];
        }
    }

    int length_odd[magic];
    for (i = 0; i < magic; i++) {
        for (j = 0; j < SIZE; j++) {
            if (odd[i][j] == '\n') {
                length_odd[i] = j;
            }
        }
    }

    int length_even[magic];
    for (i = 0; i < magic; i++) {
        for (j = 0; j < SIZE; j++) {
            if (even[i][j] == '\n') {
                length_even[i] = j;
            }
        }
    }

    int difference[magic];
    for (i = 0; i < magic; i++) {
        difference[i] = length_even[i] - length_odd[i];
    }

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
                }
            }


        }
    }

    change(text, odd, even, magic, exact, j, 0, length_odd, length_even, difference);
    change(text, odd, even, magic, exact, j, 1, length_odd, length_even, difference);
    change(text, odd, even, magic, exact, j, 2, length_odd, length_even, difference);

//    for (i = 0; i < SIZE; i++) {
//        printf("%c", text[i]);
//    }
//    printf("\n");

    return 0;
}

void return_exact(char text[SIZE], char odd[][SIZE], int exact[][SIZE], int i, int j, int k) {
    if (text[j] == odd[i][k]) {
        if (text[j + 1] == odd[i][k + 1]) {
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

void change(char text[SIZE], char odd[][SIZE], char even[][SIZE], int magic, int exact[][SIZE], int j, int i,
            int length_odd[], int length_even[], int difference[]) {
    printf("i = %d\n", i);

    int nth = 0;
    match_exact(text, odd, magic, exact, nth, j);

    int target[magic][newline];
//    for (i = 0; i < magic; i++) {
    for (j = 0; j < newline; j++) {
        target[i][j] = 0;
    }
//    }

//    for (i = 0; i < magic; i++) {
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
//    }

    int target_end[magic];
//    for (i = 0; i < magic; i++) {
    target_end[i] = 0;
//    }
//    for (i = 0; i < magic; i++) {
    for (j = 0; j < newline; j++) {
        if (target[i][j] != 0) {
            target_end[i]++;
        }
    }
//    }

    int line_diff[magic];
//    for (i = 0; i < magic; i++) {
    line_diff[i] = target_end[i] * difference[i];
//    }

    char temp[SIZE];
//    for (i = 0; i < SIZE; i++) {
    temp[i] = text[i];
//    }
    int count4 = 0;

    newline += line_diff[i];

    // 루프 수정 필요
    if (difference[i] > 0) {
        count4 = target_end[i];
        for (j = newline - 1; j >= 0; j--) {
            while (count4 != 0) {
                text[j + difference[i] * (target_end[i] - count4)] = text[j];
                if (target[i][target_end[i]] == j) {
                    count4--;
                }
            }
        }
    }
//    else if (difference[i] < 0) {
//        count4 = target_end[i];
//        for (j = 0; j < newline; j++) {
//            while (count4 != 0) {
//                text[j + ]
//            }
//        }
//    }

    for (int k = 0; k < SIZE; k++) {
        int t = 0;
        if (k == target[i][t]) {
            for (j = 0; j < length_odd[i]; j++) {
                text[k + j] = even[i][j];
            }
            t++;
            if (t == target_end[i]) {
                break;
            }
        }
    }

    for (int k = 0; k < newline; k++) {
        printf("%c", text[k]);
    }
    printf("\n");
}

void match_exact(char text[SIZE], char odd[][SIZE], int magic, int exact[][SIZE], int nth, int j) {
    for (int i = nth; i < magic; i++) {
        for (int j = 0; j < newline; j++) {
            return_exact(text, odd, exact, i, j, 0);
        }
    }
}
