#include "HumanPyramids.h"
#include "GUI/SimpleTest.h"
#include "map.h"
using namespace std;

/* This function calculates the weight distributed for each human in a human pyramid assuming each human weighs 160 pounds each */

double weightOnBackOfRec(int row, int col, int pyramidHeight, Map<string, double>& pyramidWeight) {
    /* This is the recursive call of the wrapper function below */

    string location = integerToString(row) + ' ' + integerToString(col);
    double weight = 0;

    if (row < 0 || col < 0 || col > row || row > (pyramidHeight - 1) || pyramidHeight <= 0) {
        // This portion of the function returns an error if the input is out of bounds
        error("Not in bounds.");
    }

    if (row == 0) {
        // This is the base case
        return 0;

    } else if (pyramidWeight.containsKey(location)) {
        // This portion is memoization to check if the function already recursively called this location
        return pyramidWeight[location];

    }
    else {
        if (col != 0) {
            // If the location is not on the left side
            weight += weightOnBackOfRec(row - 1, col - 1, pyramidHeight, pyramidWeight)/2 + 80;

        } if (col != row) {
            // If the location is not on the right side
            weight += weightOnBackOfRec(row - 1, col, pyramidHeight, pyramidWeight)/2 + 80;
        }
    }
    pyramidWeight[location] = weight;
    // This adds the location and weight to a map for memoization

    return weight;
}

double weightOnBackOf(int row, int col, int pyramidHeight) {
    /* This is the wrapper function so that we can have more paramters to recursively call */

    Map<string, double> pyramidWeight;
    // This is the map we make for memoization

    return weightOnBackOfRec(row, col, pyramidHeight, pyramidWeight);

}





/* * * * * * Test Cases * * * * * */
STUDENT_TEST("Person D should not be the same as Person E.") {
    /* Person D is located at row 2, column 0 while Person E is located at row 2, column 1. */
    EXPECT(weightOnBackOf(2, 0, 3) != weightOnBackOf(2, 1, 3));
}

STUDENT_TEST("Negative row, col, height") {
    EXPECT_ERROR(weightOnBackOf(-1, 0, 10));
    EXPECT_ERROR(weightOnBackOf(0, -3, 10));
    EXPECT_ERROR(weightOnBackOf(0, 0, -20));
}
STUDENT_TEST("Out of bound") {
    EXPECT_ERROR(weightOnBackOf(6, 0, 2));
    EXPECT_ERROR(weightOnBackOf(0, 8, 4));
    EXPECT_ERROR(weightOnBackOf(7, 3, 1));
}

STUDENT_TEST("All check points from the handout") {
    EXPECT_EQUAL(weightOnBackOf(0, 0, 5), 0);
    EXPECT_EQUAL(weightOnBackOf(1, 0, 5), 80);
    EXPECT_EQUAL(weightOnBackOf(1, 1, 5), 80);
    EXPECT_EQUAL(weightOnBackOf(2, 0, 5), 120);
    EXPECT_EQUAL(weightOnBackOf(2, 1, 5), 240);
    EXPECT_EQUAL(weightOnBackOf(2, 2, 5), 120);
    EXPECT_EQUAL(weightOnBackOf(3, 0, 5), 140);
    EXPECT_EQUAL(weightOnBackOf(3, 1, 5), 340);
    EXPECT_EQUAL(weightOnBackOf(3, 2, 5), 340);
    EXPECT_EQUAL(weightOnBackOf(3, 3, 5), 140);
}

PROVIDED_TEST("Check Person E from the handout.") {
    /* Person E is located at row 2, column 1. */
    EXPECT_EQUAL(weightOnBackOf(2, 1, 5), 240);
}

PROVIDED_TEST("Function reports errors in invalid cases.") {
    EXPECT_ERROR(weightOnBackOf(-1, 0, 10));
    EXPECT_ERROR(weightOnBackOf(10, 10, 5));
    EXPECT_ERROR(weightOnBackOf(-1, 10, 20));
}

PROVIDED_TEST("Stress test: Memoization is implemented.") {
    /* TODO: Yes, we are asking you to make a change to this test case! Delete the
     * line immediately after this one - the one that starts with SHOW_ERROR - once
     * you have implemented memoization to test whether it works correctly.
     */


    /* Do not delete anything below this point. :-) */

    /* This will take a LONG time to complete if memoization isn't implemented.
     * We're talking "heat death of the universe" amounts of time. :-)
     */
    EXPECT(weightOnBackOf(100, 50, 200) >= 10000);
}

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */
