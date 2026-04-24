#include <stdio.h>
main(){
    int it;
    float ft;
    char cr;
    double db;
    long lg;
    printf("Enter the integer:");
    scanf("%d",&it);
    printf("The size of integer: %d", sizeof(it));
    printf("\nEnter the float:");
    scanf("%f",&ft);
    printf("The size of float: %d", sizeof(ft));
    printf("\nEnter the character:");
    scanf("%c",&cr);
    printf("\nThe size of character: %d", sizeof(cr));
    printf("\nEnter the double:");
    scanf("%f",&db);
    printf("\nThe size of double: %d", sizeof(db));
    printf("\nEnter the long:");
    scanf("%lf",&lg);
    printf("\nThe size of long: %d", sizeof(lg));
}
