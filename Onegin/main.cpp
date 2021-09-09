/**
 * @file main.cpp
 *
 * @author Stas Goryainov
 * @date 04/09/2021
 * @version 2.0
 */

#include <stdio.h>
#include "HamletSort.h"

int main() {

//    char str1[] = "sdfsdfsdf\n";
//    char str2[] = "kjkjljlkj\n";
//    swapStrings(str1, str2);
//    printf("%d", compareStrings(str1, str2));
//    printf("%s %s\n", str1, str2);

    char filePath[100] = {};
    printf("Enter the file path (to read): ");

    if (!scanf("%s", filePath)) {
        printf("Ooops.. Something went wrong( Try again");
    }

    int nStrings = countStrings(filePath);
    int nSymbols = countSymbols(filePath);

    char* textHamlet = readHamlet(filePath, nSymbols);
    bubbleHamletSort(textHamlet, nStrings);

    printf("Enter the file path (to write in): ");

    if (!scanf("%s", filePath)) {
        printf("Ooops.. Something went wrong( Try again");
    }

    writeHamlet(filePath, textHamlet, nSymbols);

    return 0;
}
