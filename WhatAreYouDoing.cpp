#include "WhatAreYouDoing.h"
#include "GUI/SimpleTest.h"
#include "strlib.h"
#include <cctype>
using namespace std;

Set<string> emphasesOf(const Vector<string>& input) {
    /* This is the recursive call of the function below where instead we are given an input of tokens and we utilize
     * it to output a set of strings that are emphasized differently */

    if (input.size() == 0) {
        //Base Case where there is no sentence inserted
        return {""};
    }
    else {
        string initial = input[0];
        char ch = initial[0];
        //This obtains what the first character of the word is and whether it will be a word or not

        Set<string> partialSet = emphasesOf(input.subList(1));
        //Recursive portion of this function

        Set<string> finalSet = {};

        if (isalpha(ch)) {
            //If this string is a word
            for (string i : partialSet) {
                finalSet.add(toUpperCase(initial) + i);
                //Add uppercase version to final set
                finalSet.add(toLowerCase(initial) + i);
                //Add lowercase version to final set
            }
            return finalSet;
        }
        else {
            //If the string is not a word
            for (string i : partialSet) {
                finalSet.add(initial + i);
                //No need to find uppercase and lowercase version
            }
            return finalSet;
        }
    }
}


Set<string> allEmphasesOf(const string& sentence) {
    /* This is the wrapper function where we change the paramters for the recursive call. In this program,
     * we are outputing all of the different emphases sentence combinations as a set of strings. */

    Vector<string> input = tokenize(sentence);
    Set<string> sentenceCombinations = emphasesOf(input);
    return sentenceCombinations;

}


/* * * * * * Test Cases * * * * * */

STUDENT_TEST("Case where there are only numbers present.") {
    Set<string> expected = {
        "6192837198237"
    };

    EXPECT_EQUAL(allEmphasesOf("6192837198237"), expected);
}

STUDENT_TEST("Case where initial capitalization does not matter.") {
    Set<string> expected = {
        "NICE SHOES",
        "nice SHOES",
        "NICE shoes",
        "nice shoes"
    };

    EXPECT_EQUAL(allEmphasesOf("nICE shOeS"), expected);
}

STUDENT_TEST("null input") {
    Set<string> expected = {
        ""
    };

    EXPECT_EQUAL(allEmphasesOf(""), expected);
}

STUDENT_TEST("Numbers non-alhpabets mixed") {
    Set<string> expected = {
        "$3 + $4 = seven",
        "$3 + $4 = SEVEN"
    };

    EXPECT_EQUAL(allEmphasesOf("$3 + $4 = seven"), expected);
}

PROVIDED_TEST("Provided Test: Enumerates all options in a simple case.") {
    Set<string> expected = {
        "hello",
        "HELLO",
    };

    EXPECT_EQUAL(allEmphasesOf("Hello"), expected);
}

PROVIDED_TEST("Provided Test: Each option has the right length.") {
    string sentence = "Hello, world!";
    for (string option: allEmphasesOf(sentence)) {
        EXPECT_EQUAL(option.length(), sentence.length());
    }
}

PROVIDED_TEST("Provided Test: Enumerates all options in a more typical case.") {
    Set<string> expected = {
        "you are?",
        "you ARE?",
        "YOU are?",
        "YOU ARE?"
    };

    EXPECT_EQUAL(allEmphasesOf("You Are?"), expected);
}

PROVIDED_TEST("Provided Test: Stress Test: Recursion only branches on words.") {
    /* We're producing a string consisting of fifty copies of the * character. This tokenizes
     * into fifty separate stars. A star is the same whether or not you capitalize it - there
     * is no such thing as an "upper-case" or "lower-case" star. Therefore, your code should
     * not try to form two versions of the sentence, one with the star capitalized and one
     * without, because the two versions will end up being the same and the work to compute
     * both options will dramatically increase the runtime.
     *
     * For reference, if you do try branching the recursion and checking what happens both if
     * you capitalize the star and if you don't, you'll try exploring 2^50 different possible
     * capitalizations. That's 1,125,899,906,842,624 options, and even doing a billion of
     * these a second is going to take over two years to generate them all! And of course,
     * that's all wasted work, since there's only one way to capitalize this sentence, and
     * that's just to leave it as-is.
     *
     * If your code is hanging when this test is running, it likely means that your code is
     * trying to enumerate all of these options. See if you can edit your code so that, if
     * you're given a non-word token, you just leave it as-is and don't change anything.
     */
    string punctuation(50, '*'); // 50 copies of *

    /* The only emphasis is itself. */
    Set<string> expected = {
        punctuation
    };

    EXPECT_EQUAL(allEmphasesOf(punctuation), expected);
}
