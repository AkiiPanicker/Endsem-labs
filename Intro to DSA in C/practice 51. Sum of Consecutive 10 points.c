double calculateDistance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int main() {
    int numPoints = 10;
    double x, y, totalDistance = 0;
    
    // Input coordinates for the first point
    printf("Enter the x-coordinate of the first point: ");
    scanf("%lf", &x);
    printf("Enter the y-coordinate of the first point: ");
    scanf("%lf", &y);
    
    double prevX = x;
    double prevY = y;
    
    for (int i = 1; i < numPoints; i++) {
        printf("Enter the x-coordinate of point %d: ", i + 1);
        scanf("%lf", &x);
        printf("Enter the y-coordinate of point %d: ", i + 1);
        scanf("%lf", &y);
        
        // Calculate the distance between consecutive points and add to total
        totalDistance += calculateDistance(prevX, prevY, x, y);
        
        prevX = x;
        prevY = y;
    }
    
    printf("Total distance from the first point to the last point: %.2lf\n", totalDistance);
    
    return 0;
}
