#include <stdio.h>
#include <math.h>

int main() {
    int pin[4];
    int numInstructions;

    // Read the PIN from the user
    printf("Enter the 4-digit PIN (use only digits 1, 2, 3, and 4):\n");
    for (int i = 0; i < 4; i++) {
        scanf("%d", &pin[i]);
    }

    // Read the number of instructions
    printf("Enter the number of navigational instructions:\n");
    scanf("%d", &numInstructions);

    int totalDistance = 0;
    int displacementX = 0, displacementY = 30;  // Set displacement to (0, 30)

    for (int i = 0; i < numInstructions; i++) {
        int direction, distance;
        printf("Enter direction and distance for instruction %d:\n", i + 1);
        scanf("%d %d", &direction, &distance);

        totalDistance += distance;

        if (direction == 1) {
            displacementY += distance;
        } else if (direction == 2) {
            displacementY -= distance;
        } else if (direction == 3) {
            displacementX += distance;
        } else if (direction == 4) {
            displacementX -= distance;
        }
    }

    // Calculate quadrant
    int quadrant = -1;
    if (displacementX == 0 && displacementY == 30) {
        quadrant = -1;  // No quadrant defined
    } else if (displacementX == 0) {
        quadrant = (displacementY > 0) ? 1 : 3;
    } else if (displacementY == 30) {
        quadrant = 2;
    } else if (displacementX > 0 && displacementY > 0) {
        quadrant = 1;
    } else if (displacementX < 0 && displacementY > 0) {
        quadrant = 2;
    } else if (displacementX < 0 && displacementY < 0) {
        quadrant = 3;
    } else if (displacementX > 0 && displacementY < 0) {
        quadrant = 4;
    }

    printf("Total distance travelled: %d\n", totalDistance);
    printf("Displacement from starting point: (%d, %d)\n", displacementX, displacementY);
    printf("Quadrant: %d\n", quadrant);

    return 0;
}
