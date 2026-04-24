#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int choice;
    printf(" 1. Area and Volume of Cube \n 2. Area and Volume of Cuboid \n 3. Area and Volume of Sphere \n 4. Area and Volume of Cylinder \n 5. Area and Volume of Cone \n 6. Area and Volume of Hemisphere \n Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        double side;
        printf("Enter a side: ");
        scanf("%lf", &side);
        double area_cube = 6 * side * side;
        double volume_cube = side * side * side;
        printf("Surface area of cube: %lf \n", area_cube);
        printf("Volume of cube: %lf", volume_cube);
    } else if (choice == 2) {
        double length, breadth, height;
        printf("Enter length of cuboid: ");
        scanf("%lf", &length);
        printf("Enter breadth of cuboid: ");
        scanf("%lf", &breadth);
        printf("Enter height of cuboid: ");
        scanf("%lf", &height);
        double area_cuboid = 2 * (length * breadth + breadth * height + length * height);
        double volume_cuboid = length * breadth * height;
        printf("Surface area of cuboid: %lf \n", area_cuboid);
        printf("Volume of cuboid: %lf", volume_cuboid);
    } else if (choice == 3) {
        double radius;
        printf("Enter radius of sphere: ");
        scanf("%lf", &radius);
        double area_sphere = 4 * M_PI * pow(radius, 2);
        double volume_sphere = 4 * M_PI * pow(radius, 3) / 3;
        printf("Surface area of sphere: %lf \n", area_sphere);
        printf("Volume of sphere: %lf", volume_sphere);
    } else if (choice == 4) {
        double radius, height;
        printf("Enter radius of cylinder: ");
        scanf("%lf", &radius);
        printf("Enter height of cylinder: ");
        scanf("%lf", &height);
        double curved_area_cylinder = 2 * M_PI * radius * height;
        double volume_cylinder = M_PI * pow(radius, 2) * height;
        double total_area_cylinder = 2 * M_PI * radius * (height + radius);
        printf("Curved Surface area of cylinder: %lf \n", curved_area_cylinder);
        printf("Total Surface area of cylinder: %lf \n", total_area_cylinder);
        printf("Volume of cylinder: %lf", volume_cylinder);
    } else if (choice == 5){
        double radius, height;
        printf("Enter radius of cone:");
        scanf("%lf", &radius);
        printf("Enter height of cone: ");
        scanf("%lf", &height);
        double slant_height = sqrt(pow(radius,2) + pow(height,2));
        double curved_area_cone = M_PI * radius * slant_height ;
        double total_area_cone = M_PI * radius * (radius + slant_height) ;
        double volume_cone = (M_PI * pow(radius,2) * height)/3;
        printf("Curved Surface area of cone: %lf \n", curved_area_cone);
        printf("Total Surface area of cone: %lf \n", total_area_cone);
        printf("Volume of cone: %lf", volume_cone);

    } else if (choice == 6) {
        double radius;
        printf("Enter radius:");
        scanf("%lf", &radius);
        double curved_area_hemisphere = 2 * M_PI * pow(radius,2);
        double total_area_hemisphere = 3 * M_PI * pow(radius,2);
        double volume_hemisphere = (2 * M_PI * pow(radius,3))/3 ;
        printf("Curved Surface area of hemisphere: %lf \n", curved_area_hemisphere);
        printf("Total Surface area of hemisphere: %lf \n", total_area_hemisphere);
        printf("Volume of hemisphere: %lf", volume_hemisphere);
 
    }
    else {
        printf("Invalid choice, Enter a number between 1 and 4");
    }

    return 0;
}
