#include <stdio.h>
#define MAX_TERMS 200

struct term {
    float coef;
    int expon;
}terms[MAX_TERMS] = {
    {7.0, 6},{5.0, 3},{9.0, 2},{1.0, 0},
    {5.0, 3},{2.0, 2},{1.0, 1},{10.0, 0}
};
int avail = 8;
void print_poly(int s, int e);
void poly_multiply(int As, int Ae, int Bs, int Be, int* Cs, int* Ce);


int main(int argc, char* argv[]) {


    int As = 0, Ae = 3, Bs = 4, Be = 7, Cs, Ce;


    poly_multiply(As, Ae, Bs, Be, &Cs, &Ce);
    print_poly(As, Ae);
    print_poly(Bs, Be);
    printf("-----------------------------\n");
    print_poly(Cs, Ce);

    return 0;
}
void print_poly(int s, int e) {
    for (int i = s; i < e; i++) {
        printf("%3.1fx^%d +", terms[i].coef, terms[i].expon);
    }
    printf("%3.1fx^%d + \n", terms[e].coef, terms[e].expon);
}


void poly_multiply(int as, int ae, int bs, int be, int* cs, int* ce) {
    int i, j, k = avail, l;
    float coef;
    int expon;

    // 다항식 곱셈 수행
    for (i = as; i <= ae; i++) {
        for (j = bs; j <= be; j++) {
            coef = terms[i].coef * terms[j].coef;
            expon = terms[i].expon + terms[j].expon;

            for (l = avail; l <= k; l++) {//i<k이면 x^0이 출력이 안됨
                if (terms[l].expon == expon) {
                    terms[l].coef += coef;
                    break;
                }
            }

            // 동일한 차수의 항이 없으면 새로운 항 추가
            if (terms[l].expon != expon) {
                terms[k].coef = coef;
                terms[k].expon = expon;
                k++;
            }
        }
    }

    // 결과 다항식의 시작 및 종료 인덱스 업데이트
    *cs = avail;
    *ce = k;//k-1이면 x^0이 출력이 안됨

    // 사용 가능한 공간 업데이트
    avail = k;
}