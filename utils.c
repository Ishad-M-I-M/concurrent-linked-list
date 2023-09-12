#include <math.h>

double average(const double arr[], int length) {
    if (length <= 0) {
        return 0.0;
    }

    double sum = 0.0;
    for (int i = 0; i < length; i++) {
        sum += arr[i];
    }

    return sum / length;
}

double standardDeviation(const double arr[], int length) {
    if (length <= 1) {
        return 0.0;
    }

    double mean = average(arr, length);
    double sumSquaredDiff = 0.0;

    for (int i = 0; i < length; i++) {
        double diff = arr[i] - mean;
        sumSquaredDiff += diff * diff;
    }

    double variance = sumSquaredDiff / (length - 1);
    return sqrt(variance);
}