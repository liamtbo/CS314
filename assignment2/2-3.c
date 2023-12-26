#include <stdio.h>

int ge(float x, float y) {
    unsigned int ux = *((unsigned int*) &x); // convert x raw bits
    unsigned int uy = *((unsigned int*) &y); // convert y raw bits
    unsigned int sx = ux >> 31; // extract sign bit of ux
    unsigned int sy = uy >> 31; // extract sign bit of uy
    ux &= 0x7FFFFFFF; // drop sign bit of ux
    uy &= 0x7FFFFFFF; // drop sign bit of uy
    // TODO: return using sx, sy, ux, uy
    // printf("%u %u %u %u done\n", sx, ux, sy, uy);
    // printf("%d\n", sx >= sy);
    int c1 = (ux == 0 && uy == 0); // 0, 0
    int c2 = (sx == 1 && sy == 1) && (ux <= uy); // neg, neg, ux less neg then uy
    int c3 = (sx == 0 && sy == 0) && (ux >= uy); // pos,pos, ux bigger
    int c4 = (sx == 0 && sy == 1) && ((ux == 0) ^ (uy == 0)); // pos,neg, one zero
    int c5 = (sx == 0 && sy == 1) && (ux != 0 && uy != 0); // pos, neg, no zero

     return (c1 || c2 || c3 || c4 || c5);
}

int main() { 
    printf("%X %d\n", ge(0.0f, 0.0f), 1);
    printf("%X %d\n", ge(-0.0f, 0.0f), 1);
    printf("%X %d\n", ge(0.0f, -0.0f), 1);
    printf("%X %d\n", ge(-0.0f, -0.0f), 1);
    printf("%X %d\n", ge(-1.0f, -1.0f), 1);
    printf("%X %d\n", ge(-1.0f, -2.0f), 1);
    printf("%X %d\n", ge(-2.0f, -1.0f), 0);
    printf("%X %d\n", ge(1.0f, 1.0f), 1);
    printf("%X %d\n", ge(-1.0f, 1.0f), 0);
    printf("%X %d\n", ge(-1.0f, 0.0f), 0);
    printf("%X %d\n", ge(1.0f, 0.0f), 1);
    printf("%X %d\n", ge(0.0f, 1.0f), 0);
    printf("%X %d\n", ge(1.0f, 2.0f), 0);
    printf("%X %d\n", ge(2.0f, 1.0f), 1);
    printf("%X %d\n", ge(1.0f, -1.0f), 1);
    printf("%X %d\n", ge(0.0f, -1.0f), 1);

}