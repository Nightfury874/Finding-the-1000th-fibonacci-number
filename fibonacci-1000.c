#include<stdio.h>
#include<string.h>

const int len = 1001;

void mul(int a[2][2][len], int b[2][2][len]) {
    
    int c[2][2][len];
    memset(c, 0, sizeof c);
    
    int l[len], r[len];
    int carry = 0;
    
    //c[0][0]
    for(int x = 0; x < 2; x++) {
        for(int y = 0; y < 2; y++) {
            
            memset(l, 0, sizeof l);
            memset(r, 0, sizeof r);
            
            for(int i = 0; i < len; i++) {
                carry = 0;
                for(int j = 0; j < len; j++) {
                    int t = (a[x][0][j]*b[0][y][i] + carry + l[i+j]);
                    l[i+j] = t % 10;
                    carry = t / 10;
                }
            }
        
            for(int i = 0; i < len; i++) {
                carry = 0;
                for(int j = 0; j < len; j++) {
                    int t = (a[x][1][j]*b[1][y][i] + carry + r[i+j]);
                    r[i+j] = t % 10;
                    carry = t / 10;
                }
            }
            
            carry = 0;
            for(int i = 0; i < len; i++) {
                int t = (l[i] + r[i] + carry);
                c[x][y][i] = t % 10;
                carry = t / 10;
            }    
            
        }
    }

    memset(a, 0, sizeof(a));
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            for(int k = 0; k < len; k++) {
                a[i][j][k] = c[i][j][k]; 
            }
        }
    }
    
}

void matexp(int a[2][2][len], int n) { 
    
    if(n == 1) {
        return;
    }

    int b[2][2][len];
    memset(b, 0, sizeof b);
    
    b[0][0][0] = a[0][0][0];
    b[0][1][0] = a[0][1][0];
    b[1][0][0] = a[1][0][0];
    b[1][1][0] = a[1][1][0];
    
    matexp(a, n/2);
    
    mul(a, a);

    if(n % 2) {
        mul(a, b);
    }

} 

int main() {
    
    int n; scanf("%d", &n);
    if(n == 1) {
        printf("1");
        return 0;
    }
    
    int a[2][2][len];
    int f[2][2][len];
    memset(a, 0, sizeof a);
        
    a[0][0][0] = 1;
    a[0][1][0] = 1;
    a[1][0][0] = 1;
    a[1][1][0] = 0;

    f[0][0][0] = 1;
    f[0][1][0] = 0;
    f[1][0][0] = 0;
    f[1][1][0] = 0;
        
    matexp(a, n-1);
    
    mul(f, a);

    int fl = 0;    
    for(int k = len-1; k >= 0; --k) {
        if(f[0][0][k]) fl = 1;
        if(fl) {printf("%d", f[0][0][k]);}
    }
    
}
    
