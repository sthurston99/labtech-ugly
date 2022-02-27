 /* N. L. Tinkham, September 2003
    Simon Thurston, February 2020

   http://elvis.rowan.edu/~nlt/sigcse/ugly/

   Example of ugly coding style.  (Never, never, never write this way!)

   Problem:  Find and print the most frequently occurring character in
             the input.
   Input is a sequence of characters in standard input, ending in ^D
             on a line by itself.
   There is no prompt, making it easier to take input from a pipe or file.
   The output is
	     Most frequent character: _
       where _ is the most frequent character that was found.
   All characters (except the terminating ^D) are counted, including
             spaces, tabs, and newlines.

*/

#include <stdio.h>
#include <ctype.h>

struct cf {
    char ch;
    int fr;
};

int process_data(char lc, struct cf cc[], int s);
void ss(struct cf cc[], int s);

int main() {
    int s = 0;
    struct cf cc[200];
    char lc;
    int i, l;
    int nullndx, lndx;

    while ((lc = getchar()) != EOF) {
        l = process_data(lc, cc, s);
        if(l >= 0) {
            cc[l].ch = lc;
            cc[l].fr++;
        } else {
            cc[s].ch = lc;
            cc[s].fr = 1;
            s++;
        }
    }

    ss(cc, s);
    if(isdigit(cc[0].ch)) {
        printf("Most Frequent Digit: %c\n", cc[0].ch);
    } else {
        printf("Most Frequent Character: %c\n", cc[0].ch);
    }

    for(int i = 0; i < sizeof(cc); i++) {
        if(cc[i].ch == '\0') {
            nullndx = i;
            break;
        }
    }
    for(int i = nullndx; i > 0; i--) {
        if(cc[i].fr == 1) {
            lndx = i;
            break;
        }
    }

    if(isdigit(cc[lndx].ch)) {
        printf("Least Frequent Digit: %c\n", cc[lndx].ch);
    } else {
        printf("Least Frequent Character: %c\n", cc[lndx].ch);
    }

    return 0;

}

int process_data(char lc, struct cf cc[], int s) {
    for(int i = 0; i < s; i++) {
        if(cc[i].ch == lc) {
            return i;
        }
    }
    return -1;
}

void ss(struct cf cc[], int s) {
    int x;
    struct cf X;

    for(int f = 0; f < s - 1; f++) {
        x = f;
        for(int i = f + 1; i < s; i++) {
            if(cc[i].fr > cc[x].fr) {
                x = i;
            }
        }

        X = cc[f];
        cc[f] = cc[x];
        cc[x] = X;
    }
}  
