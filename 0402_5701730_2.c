#include <stdio.h>
#define MAX_TERMS 200
//terms: 최대 200개의 항을 저장할 수 있는 구조체 배열
struct term {
    float coef;//항의 계수를 저장
    int expon;//항의 지수를 저장
}terms[MAX_TERMS] = {
    {7.0, 6},{5.0, 3},{9.0, 2},{1.0, 0},
    {5.0, 3},{2.0, 2},{1.0, 1},{10.0, 0}
};
int avail = 8;//사용 가능한 항의 인덱스를 나타내는 변수 초기화, 현재 사용 가능한 항의 인덱스를 나타내는 변수
void print_poly(int s, int e);
void poly_multiply(int As, int Ae, int Bs, int Be, int* Cs, int* Ce);

//main 함수는 두개의 다항식의 시작 및 종료 인덱스를 설정하고 poly_multiply 함수를 호출하여 곱셈을 수행
int main(int argc, char* argv[]) {


    int As = 0, Ae = 3, Bs = 4, Be = 7, Cs, Ce;


    poly_multiply(As, Ae, Bs, Be, &Cs, &Ce);
    print_poly(As, Ae);
    print_poly(Bs, Be);
    printf("-----------------------------\n");
    print_poly(Cs, Ce);

    return 0;
}
//print_poly 함수는 주어진 시작 및 종료 인덱스 사이의 항들을 차례로 출력한다.
void print_poly(int s, int e) {
    for (int i = s; i < e; i++) {
        printf("%3.1fx^%d +", terms[i].coef, terms[i].expon);
    }
    printf("%3.1fx^%d + \n", terms[e].coef, terms[e].expon);
}

// As: 첫 번째 다항식의 시작 인덱스, Ae: 첫 번째 다항식의 종료 인덱스,
// Bs: 두 번째 다항식의 시작 인덱스, Be: 두 번째 다항식의 종료 인덱스,
// Cs: 결과 다항식의 시작 인덱스를 저장할 포인터
// Ce: 결과 다항식의 종료 인덱스를 저장할 포인터
void poly_multiply(int as, int ae, int bs, int be, int* cs, int* ce) {
    int i, j, k = avail, l;//k는 결과 다항식에 새 항을 추가할 때 사용하는 인덱스 변수
    //l은 동일한 지수를 가진 항을 찾는 for루프의 반복 변수이다.
    float coef;
    int expon;

    // 다항식 곱셈 수행
    for (i = as; i <= ae; i++) {
        for (j = bs; j <= be; j++) {
            coef = terms[i].coef * terms[j].coef;//a의 계수와 b의 계수를 곱함 그 결과 값을 coef에 넣음
            expon = terms[i].expon + terms[j].expon;//a의 지수와 b의 지수를 더함 그 결과 값을 expon에 넣음

            for (l = avail; l <= k; l++) {//ㅣ<k이면 x^0이 출력이 안됨
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