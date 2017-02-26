/*
 * A very simple program to break the Caesar-cipher for French texts. By adding
 * other language frequency tables, the program can easily be extended to other
 * languages. 
 *
 * Usage: 
 *   breakcaesar  (no arguments, the ciphertext is hardcoded)
 *
 * Marius Kleiner, 31 October 2007
 */

#include <stdio.h>
#include <string.h>
#include <math.h>

#define ALPHABET_SIZE 26

void rotate_string(char d[], const char s[], int n);
double french_score(const char[]);
double mse(const double[], const double[], int);

double french_freq[] = {
        8.147,  /* A */
        0.876,  /* B */
        3.063,  /* C */
        4.125,  /* D */
        17.564, /* E */
        0.959,  /* F */
        1.051,  /* G */
        0.721,  /* H */
        7.559,  /* I */
        .598,   /* J */
        0.041,  /* K */
        5.783,  /* L */
        2.990,  /* M */
        7.322,  /* N */
        5.289,  /* O */
        2.98,   /* P */
        1.361,  /* Q */
        6.291,  /* R */
        8.013,  /* S */
        7.353,  /* T */
        5.991,  /* U */
        1.557,  /* V */
        .02,    /* W */
        0.35,   /* X */
        0.116,  /* Y */
        0.072   /* Z */
};


int main()
{
        char s[] = "TU JEKI BUI FUKFBUI TU BQ WQKBU BUI RUBWUI IEDJ BUI FBKI \
RHQLUI";

        char n[100];

        int i;

        int best_i;
        double min_score = 1000000;

        for (i = 1; i <= 25; i++)
        {
                double score;
                rotate_string(n, s, i);
                score = french_score(n);
                if (score < min_score) {
                        min_score = score;
                        best_i = i;
                }

                printf("%s (%.2f)\n", n, score);
        }

        /* Compute again best string */
        rotate_string(n, s, best_i);
        printf("With a mean square error of %.2f, the best match is\n%s\n",
                        min_score, n);

        return 0;
}


void rotate_string(char d[], const char s[], int n)
{
        int i = 0;

        while (s[i]) {
                if (s[i] >= 'A' && s[i] <= 'Z') {
                        char c = (s[i] - 'A' - n) % ALPHABET_SIZE;
                        if (c < 0) c += ALPHABET_SIZE;
                        d[i] = c + 'A';
                } else {
                        d[i] = s[i];
                }

                i++;
        }
        d[i] = '\0';
}


/* This function computes a score for how well a given string matches french */
double french_score(const char s[])
{
        int i;

        /* Total letter count */
        int tot = strlen(s);
        
        /* Empirical letter frequencies */
        double lf[ALPHABET_SIZE];
        for (i = 0; i < ALPHABET_SIZE; i++)
                lf[i] = 0.0;

        i = 0;
        while (s[i]) {
                char c = s[i];
                if (c >= 'A' && c <= 'Z')
                        lf[c - 'A'] += 100.0/tot;
                i++;
        }

//        for (i = 0; i < ALPHABET_SIZE; i++)
//                printf("freq(%c) = %f\n", i + 'A', lf[i]);

        /* Return the mean squared difference between the two arrays */
        return mse(lf, french_freq, ALPHABET_SIZE);
}


double mse(const double a[], const double b[], int l)
{
        int i;
        double s = 0.0;

        /* Compute sum of squared differences */
        for (i = 0; i < l; i++)
                s += pow(a[i] - b[i], 2.0);

        /* Return average difference */
        return s / l;
}
