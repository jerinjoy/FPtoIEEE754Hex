/* Converts IEEE-754 hex representation to decimal and back */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>



void HextoFPString(char *fpString, uint64_t IEEE_hex_value, int isDouble) {

    if (isDouble) {
        double *dblPtr = (double *) &IEEE_hex_value;
        sprintf (fpString, "%f", *dblPtr);
    }
    else {
        float *sglPtr = (float *) &IEEE_hex_value;
        sprintf (fpString, "%f", *sglPtr);
    }

}


void FPtoHexString (char *fpString, double fpVal, int isDouble) {
    if (isDouble) {
        sprintf (fpString, "0x%"PRIx64, *((uint64_t *) &fpVal));
    }
    else {
        float fpSglVal = (float) fpVal;
        sprintf (fpString, "0x%"PRIx32, *((uint32_t *) &fpSglVal));
    }
}


int main(int argc, char *argv[]) {

    char fpString[50];
    char inputString[50];

    if (argc != 2) {
        printf ("No input\n");
        exit(1);
    }

    printf ("<?xml version=\"1.0\"?>\n");
    printf ("<items>\n");

    strcpy (inputString, argv[1]);

    if (inputString[0] == '0' && inputString[1] == 'x') {
        uint64_t fpHex = 0;
        // Hex to FP
        if (sscanf (inputString, "0x%"PRIx64, &fpHex) != 1) {
            printf ("ERROR: Could not read hex operand %s.\n", inputString);
            exit(1);
        }

        if (fpHex & UINT64_C(0xffffffff00000000)) {
            HextoFPString(fpString, fpHex, 1);

            //printf ("Hex to FP (Dbl) = %s\n", fpString);

            printf ("  <item uid=\"dbl\" arg=\"%s\">\n", fpString);
            printf ("    <title>Double %s</title>\n", fpString);
            printf ("    <subtitle>Double-Precision</subtitle>\n");
            printf ("  </item>\n");
        }
        else {
            HextoFPString(fpString, fpHex, 0);

            //printf ("Hex to FP (Sgl) = %s\n", fpString);
            printf ("  <item uid=\"sgl\" arg=\"%s\">\n", fpString);
            printf ("    <title>Single %s</title>\n", fpString);
            printf ("    <subtitle>Single-Precision</subtitle>\n");
            printf ("  </item>\n");
        }
    }
    else {
        // FP to Hex
        double fpVal = 0.0;

        if (sscanf (inputString, "%lf", &fpVal) != 1) {
            printf ("ERROR: Could not read FP operand %s.\n", inputString);
            exit(1);
        }

        FPtoHexString(fpString, fpVal, 1);

        printf ("  <item uid=\"dbl\" arg=\"%s\">\n", fpString);
        printf ("    <title>IEEE-754 %s</title>\n", fpString);
        printf ("    <subtitle>Double-Precision</subtitle>\n");
        printf ("  </item>\n");

        FPtoHexString(fpString, fpVal, 0);

        printf ("  <item uid=\"sgl\" arg=\"%s\">\n", fpString);
        printf ("    <title>IEEE-754 %s</title>\n", fpString);
        printf ("    <subtitle>Single-Precision</subtitle>\n");
        printf ("  </item>\n");
    }

    printf ("</items>\n");

}
