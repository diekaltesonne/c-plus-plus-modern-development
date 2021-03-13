//#include <stdio.h>
//int main()
//{
//const int ARRAY_SIZE = 5;
//struct student {char first_name; char second_name; int number;};
//struct student* pstudent_info;
//struct student arr[ARRAY_SIZE];
//printf("Enter student's info");
//for (int i = 0; i <= ARRAY_SIZE; i++, pstudent_info++);{
//    struct  student A = {'a','b',3};
//    if (scanf("%d",&n) == 1) {
//    printf("%d", n);
//    } else {
//    printf("Failed to read integer.\n");
//    }
//    arr[0] = A;
//    pstudent_info = arr;
//}

//return 0;

//}

#include <stdio.h>
struct studs {
    char fname[20];
    char lname[20];
    int point;
};

int main() {
    struct studs arr[15], *a;
    int sum, i, n;
    float average;
    printf("Количество студентов: ");
    scanf("%d",&n);
    sum = 0;
    for (i=0, a=arr; i<n; i++, a++) {
    }
    return 0;
}
