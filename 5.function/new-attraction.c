// =====================================
// 함수 생성용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================


#include <stdio.h>


// 함수 선언:
//   반환값의타입  함수명(입력값의타입);


// 결과 출력하기:
void printResult(double mass1, double mass2,
                 double distance, double force);


// 만유 인력 계산:
double getAttractionForce(double G,
    double mass1, double mass2, double distance);




int main() {
    double G = 6.67428e-11;  // 중력 상수 G
    double mass1 = 0;  // m1 의 질량
    double mass2 = 0;  // m2 의 질량
    double distance = 0;  // m1 과 m2 사이의 거리 r
    double force = 0;  // m1 과 m2 사이에 작용하는 인력 f
 
    printf("[만유인력 계산 프로그램]\n\n");
    // m1, m2, r 입력받기
    printf("물체1의 질량은(단위: 킬로그램) ?\n");
    scanf("%lf", &mass1);
    printf("물체2의 질량은(단위: 킬로그램) ?\n");
    scanf("%lf", &mass2);
    printf("두 물체 사이의 거리는(단위:미터) ?\n");
    scanf("%lf", &distance);
 
    // 만유인력 계산식
    // f = G * ( (m1 * m2) / (r * r) );  // better
    force = getAttractionForce(G, mass1, mass2, distance);
 
    // 결과 출력하기
    printResult(mass1, mass2, distance, force);


    return 0;
}




// 함수 정의:
//   함수의 원형 {
//       // 떼어 낸 소스 코드를 집어 넣을 위치
//   }


// 결과 출력하기:
void printResult(double mass1, double mass2,
                 double distance, double force) {


    printf("----------------------------------------\n");
    printf("물체1의 질량 : %f kg\n", mass1);
    printf("물체2의 질량 : %f kg\n", mass2);
    printf("물체 간 거리 : %f m\n", distance);
    printf("----------------------------------------\n");
    printf("물체 간 인력 : %f N(뉴튼)\n", force);
}


// 만유 인력 계산:
double getAttractionForce(double G,
    double mass1, double mass2, double distance) {
   
    double result = G * ( (mass1 * mass2) / (distance * distance) );


    return result;
}
