// =====================================
// pointer용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <stdio.h>


// 10배 반환 함수
int mul10(int *valuePointer);


// 값을 서로 바꾸는 함수
void swap(int *aPointer, int *bPointer);




int main() {


    int age = 77;


    // 주소 연산자 & 사용법:
    // &변수명
    printf("age 의 값   = %d\n", age);
    printf("age 의 주소 = 0x%p\n", &age);


    // 일반적인 변수 선언법:
    //     타입   변수명;


    // 포인터 변수 선언법:
    //     타입  *변수명;
    // 또는
    //     타입*  변수명;


    int *p;


    p = &age;  // 변수 age 의 주소값을 포인터 변수 p 에 저장
    printf("p 의 값 = 0x%p\n", p);


    // C 언어에서는 "주소가 가리키는 곳" 을 포인터 라고 부르고
    // 포인터연산자 기호는 * 을 사용합니다.
    printf("p 가 가리키는 상자의 값 = %d\n", *p);




    // 포인터 변수를 선언할 때 사용하는 * 기호와
    //   int *p;
    // '주소가 가리키는 곳'에 저장된 값을 사용할 때 쓰는 * 기호,
    // 그리고 곱셈 연산자용 * 기호는 기호는 같지만 사용하는 위치와 용도가 다릅니다:
    age = *p * 2;  // *p 는 변수 age 를 간접 참조하므로 계산식은 77 * 2 가 됨.
    printf("age = %d, *p = %d\n", age, *p);




    // 직접 접근해서 값을 증가한 경우 :
    age++;


    // 주소를 이용해 간접적으로 값을 증가한 경우 :
    (*p)++;
    printf("age = %d, *p = %d\n", age, *p);


    // 특별한 void 포인터 타입:
    void  *voidPointer;
    short *shortPointer;
    shortPointer = p;  // <<< 포인터 타입 호환안됨 warning
    voidPointer  = p;
    printf( "*voidPointer = %d\n", *((int *)voidPointer) );



   
    int value = 10;
    int result = 0;


    printf("[main] mul10 호출 전 : value = %d, result = %d\n", value, result);
    result = mul10(&value);  // 주소값의 복사본이 함수에 전달됨
    printf("[main] mul10 호출 후 : value = %d, result = %d\n", value, result);


    // mul10 함수 호출시 아규먼트(argument) 와 파라미터(parameter) 예시:
    //   아규먼트(argument) : main  함수 내의 value 변수
    //   파라미터(parameter): mul10 함수 내의 value 변수


    // swap:
    // ----
    int a = 10;
    int b = 20;


    // // wrong swap code:
    // a = b;  // <<< b 값으로 덮여져서 원래 a 값은 사라졌음.
    // b = a;
 
    // swap 함수 호출:
    printf("swap 호출 전: a,b=%d,%d\n", a, b);
    swap(&a, &b);  // wrong: 변수 a 와 b 의 복사본이 전달됨
    printf("swap 호출 후: a,b=%d,%d\n", a, b);


    // NULL 상수로 초기화
    int *pointer = NULL;  // 포인터 선언과 동시에 NULL 포인터 상수로 초기화
    // int *pointer = 0;  // 포인터 선언과 동시에 0 으로 초기화 (두 표현은 동일함)


    // 포인터 연산: 포인터 덧셈과 뺄셈만 가능합니다.
    // ==========
    int *aPointer = &a;
    int *bPointer = &b;


    // bPointer = bPointer + aPointer;  // compile error
    // bPointer++;
    // // or
    printf("before + 1 : address of bPointer=%p\n", bPointer);
    // sample1: 포인터 덧셈
    bPointer++;
    printf("after  + 1 : address of bPointer=%p\n", bPointer);


    // sample2: 포인터 뺄셈
    short x = 10;
    short y = 20;


    short *yPointer = &y;
    yPointer--;


}


// 값을 서로 바꾸는 함수
void swap(int *aPointer, int *bPointer) {
    // right swap code:
    int temp = *aPointer;  // 원래 a 값 임시보관용 변수가 필요함.
    *aPointer = *bPointer;
    *bPointer = temp;
}




// 10배 반환 함수
int mul10(int *valuePointer) {
    printf("[mul10] 값 수정전 : value = %d\n", *valuePointer);
    *valuePointer = (*valuePointer) * 10;
    printf("[mul10] 값 수정후 : value = %d\n", *valuePointer);
    printf("[mul10] 주소값    : valuePointer = 0x%p\n", valuePointer);
   
    return *valuePointer;
}
