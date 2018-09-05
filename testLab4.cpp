#include "testLab.h"
#include <stdio.h>
#include <string.h>

static int testN = 0;
static const struct {const char *const in, *const out;} testInOut[] = {
    {"(((((\n", "syntax error"},
    {"1/0\n", "division by zero"},
    {"2*2\n", "4"},
    {"bad input\n", "syntax error"},
    {"2.0*2.0\n", "syntax error"},
    {"123()\n", "syntax error"},
    {"()123\n", "syntax error"},
    {"1*2+3/4\n", "2"},
    {"1*(2+3)/4\n", "1"},
    {"1/2/3/4\n", "0"},
    {"1*2*3/4\n", "1"},
    {"1*2+3*4\n", "14"},
    {"1+2*3+4\n", "11"},
    {"1+3*2/(3-1-2)\n", "division by zero"},
    {"1--\n", "syntax error"},
    {"1-*\n", "syntax error"},
    {"1-1-*1\n", "syntax error"},
    {"--1\n", "syntax error"},
    {"11-\n", "syntax error"},
    {"()\n", "syntax error"},
    {"(-)\n", "syntax error"},
    {"\n", "syntax error"},
    {")\n", "syntax error"},
    {"1+1)(\n", "syntax error"},
    {"1 1\n", "syntax error"},
    {"1234567890\n", "1234567890"},
    {"(1234567890)\n", "1234567890"},
    {"((1234567890))\n", "1234567890"},
    {"1+23+456+7890\n", "8370"},
    {"1-23-456-7890\n", "-8368"},
    {"(1)-(23)-(456)-(7890)\n", "-8368"},
    {"(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "((((((((((((((((((((((((((((((((((((((((\n", "syntax error"},
    {"((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((99"
    ")+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1"
    ")+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1"
    ")+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1"
    ")+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1"
    ")+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1"
    ")+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1"
    ")+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1"
    ")+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1"
    ")+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1"
    ")+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1"
    ")+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1"
    ")+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)\n", "348"},
    {"1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1"
    "+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
    "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1"
    "+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
    "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1"
    "+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
    "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1"
    "+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
    "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1"
    "+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
    "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1"
    "+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
    "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1"
    "+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
    "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1"
    "+1+1+1+1+1+1+1+1+1+1+1+99\n", "598"}
};

static int feederN(void)
{
    FILE *const in = fopen("in.txt", "w+");
    if (!in) {
        printf("can't create in.txt. No space on disk?\n");
        return -1;
    }
    fprintf(in, "%s", testInOut[testN].in);
    fclose(in);
    return 0;
}

static int checkerN(void)
{
    FILE *const out = fopen("out.txt", "r");
    char buf[128] = {0};
    int passed = 1;
    if (!out) {
        printf("can't open out.txt\n");
        testN++;
        return -1;
    }
    if (fgets(buf, sizeof(buf), out) == NULL) {
        printf("no output -- ");
    }
    fclose(out);
    if (strchr(buf, '\n'))
        *strchr(buf, '\n') = 0;
    passed = strnicmp(testInOut[testN].out, buf, strlen(testInOut[testN].out)) == 0;
    if (passed) {
        while (1) {
            char ignored;
            if (fscanf(out, "%c", &ignored) == EOF)
                break;
            if (strchr("\n\t ", ignored))
                continue;
            passed = 0;
            printf("output is too long -- ");
            break;
        }
    } 
    if (passed) {
        printf("PASSED\n");
        testN++;
        return 0;
    } else {
        printf("FAILED\n");
        testN++;
        return 1;
    }
}

const struct labFeedAndCheck labTests[] = {
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN},
    {feederN, checkerN}
};

const int labNTests = sizeof(labTests)/sizeof(labTests[0]);

const char labName[] = "Lab 4 Calc";

int labTimeout = 3000;
size_t labOutOfMemory = 1024*1024*2;
