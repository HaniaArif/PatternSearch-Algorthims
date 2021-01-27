#include <iostream>
#include <string>
#include <math.h>
#include <cmath>
using namespace std;

/******************************************************************************/
/****************************Naive Pattern Search******************************/
/******************************************************************************/
void NaivePatternSearch(string MainS, string PatternS)
{
    // length of the main text
    int mainLen = MainS.length();
    // length of the pattern
    int patternLen = PatternS.length();
    // Slide the pattern over text one by one and check for a match.
    // If a match is found, then slides by 1 again to check for subsequent matches.
    for (int i = 0; i <= mainLen - patternLen; i++)
    {
        int j = 0;
        for (; j < patternLen; j++)
            if (MainS[i + j] != PatternS[j])
                break;
        if (j == patternLen)
            cout << "pattern found at index:(" << i << ")." << endl;
    }
}
/******************************************************************************/
/****************************Rabin-Karp Algorthim******************************/
/******************************************************************************/
void RabinKarpAlgorthim(string MainS, string PatternS, int q, int d)
{
    int mainLen = MainS.length();
    int patternLen = PatternS.length();
    int HashT = 0; // hash value for Text
    int HashP = 0; // hash value for pattern
    int h = 1;
    // int h = ((int)pow(d, patternLen - 1)) % q;
    for (int i = 0; i < patternLen - 1; i++)
        h = (h * d) % q;
    for (int i = 0; i < patternLen; i++)
    {
        HashP = (d * HashP + PatternS[i]) % q;
        HashT = (d * HashT + MainS[i]) % q;
    }
    for (int i = 0; i <= mainLen - patternLen; i++)
    {
        int j;
        if (HashP == HashT)
        {
            for (j = 0; j < patternLen; j++)
                if (MainS[i + j] != PatternS[j])
                    break;
            if (j == patternLen)
                cout << "pattern found at index:(" << i << ")." << endl;
        }
        if (i < mainLen - patternLen)
        {
            HashT = (d * (HashT - MainS[i] * h) + MainS[i + patternLen]) % q;
            if (HashT < 0)
                HashT += q;
        }
    }
}
/******************************************************************************/
/***********************Finite Automata algorithm******************************/
/******************************************************************************/
#define q 256
int getNextState(string patternS, int state, int x)
{
    int patternLen = patternS.length();
    if (state < patternLen && x == patternS[state])
        return state + 1;

    int ns, i;

    for (ns = state; ns > 0; ns--)
    {
        if (patternS[ns - 1] == x)
        {
            for (i = 0; i < ns - 1; i++)
                if (patternS[i] != patternS[state - ns + 1 + i])
                    break;
            if (i == ns - 1)
                return ns;
        }
    }

    return 0;
}
void computeTF(string patternS, int TF[][q])
{
    int patternLen = patternS.length();
    int state, x;
    for (state = 0; state <= patternLen; ++state)
        for (x = 0; x < q; ++x)
            TF[state][x] = getNextState(patternS, state, x);
}
void FiniteAutomataAlgorithm(string MainS, string PatternS)
{
    int mainLen = MainS.length();
    int patternLen = PatternS.length();
    int TF[patternLen + 1][q];
    computeTF(PatternS, TF);
    int i, state = 0;
    for (i = 0; i < mainLen; i++)
    {
        state = TF[state][MainS[i]];
        if (state == patternLen)
            cout << "pattern found at index:(" << i - patternLen + 1 << ")." << endl;
    }
}
/******************************************************************************/
/******************************KMP algorithm***********************************/
/******************************************************************************/
void computeLPSArray(string PatternS, int patternLen, int *lps)
{
    int len = 0;
    lps[0] = 0;
    int i = 1;
    while (i < patternLen)
    {
        if (PatternS[i] == PatternS[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
                len = lps[len - 1];
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}
void KMPSearch(string MainS, string PatternS)
{
    int mainLen = MainS.length();
    int patternLen = PatternS.length();
    int lps[patternLen];
    computeLPSArray(PatternS, patternLen, lps);
    int i = 0;
    int j = 0;
    while (i < mainLen)
    {
        if (PatternS[j] == MainS[i])
        {
            j++;
            i++;
        }
        if (j == patternLen)
        {
            cout << "pattern found at index:(" << i - j << ")." << endl;
            j = lps[j - 1];
        }
        else if (i < mainLen && PatternS[j] != MainS[i])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
}
/******************************************************************************/
/********************************* M*A*I*N ************************************/
/******************************************************************************/
int main()

{

    string MainS = "aaababaabaababaab";
    string PatternS = "aabab";
    cout << "NAIVE PATTERN SEARCH:" << endl;
    NaivePatternSearch(MainS, PatternS);
    cout << "RABIN-KARP PATTERN SEARCH:" << endl;
    RabinKarpAlgorthim(MainS, PatternS, 101, 256);
    cout << "FINITE AUTOMATA PATTERN SEARCH:" << endl;
    FiniteAutomataAlgorithm(MainS, PatternS);
    cout << "KMP PATTERN SEARCH:" << endl;
    KMPSearch(MainS, PatternS);
    return 0;
}
