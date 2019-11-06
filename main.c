#include <stdio.h>
#include "vector.h"
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

bool is_space(char a) {
    if ((a == ' ') || (a == '\n') || (a == '\t') || (a == '\0')) {
        return true;
    } else {
        return false;
    }
}

bool is_power_0f_two(int n) {
    bool flag;
    if ((n & (n - 1)) == 0) {
        flag = true;
    } else {
        flag = false;
    }
    return flag;
}

int main() {
    char a[1];
    vector *v = v_create();
    ssize_t y;
    int b;
    bool flag = false;
    int c[10];
    int r = 0;
    read(0, a, 1);
    while (is_space(a[0])) {
        a[0] = 0;
        y = read(0, a, 1);
        if (y <= 0) {
            break;
        }
    }
    while (!is_space(a[0])) {
        b = a[0] - '0';
        if ((b > 1) || (b < 0)) {
            flag = true;
        }
        v_push(v, b);
        a[0] = 0;
        y = read(0, a, 1);
        if (y <= 0) {
            break;
        }
    }
    if (flag == true) {
        write(1, "Неверный ввод\n", 27);
    } else {
        write(1, "Введите колличество контрольных разрядов:\n", 80);
        while (is_space(a[0])) {
            a[0] = 0;
            y = read(0, a, 1);
            if (y <= 0) {
                break;
            }
        }
        int i = 0;
        while (!is_space(a[0])) {
            c[i] = a[0] - '0';
            a[0] = 0;
            y = read(0, a, 1);
            if (y <= 0) {
                break;
            }
            ++i;
        }
        c[i] = '\0';
        int g = 1;
        int j = 0;
        while (c[j] != '\0') {
            g = g * 10;
            ++j;
        }
        g = g / 10;
        j = 0;
        while (g > 0) {
            r = r + c[j] * g;
            g = g / 10;
            ++j;
        }
        int n, m, k;
        k = r;
        n = 1;
        while (k > 0) {
            n = n * 2;
            k = k - 1;
        }
        n = n - 1;
        m = 1;
        k = r;
        while (k > 0) {
            m = m * 2;
            k = k - 1;
        }
        m = m - r - 1;
        int d[m][r];
        int l[m][m];
        int p = 0;
        for (int i1 = 0; i1 < m; ++i1) {
            for (int k1 = 0; k1 < m; ++k1) {
                if (k1 == p) {
                    l[i1][k1] = 1;
                } else {
                    l[i1][k1] = 0;
                }
            }
            ++p;
        }
        int x;
        int q = 0;
        int w = r - 1;
        for (int l1 = n; l1 >= 1; --l1) {
            if (!is_power_0f_two(l1)) {
                x = l1;
                for (int i1 = 0; i1 < r; ++i1) {
                    d[q][w] = x % 2;
                    x = x / 2;
                    --w;
                }
                ++q;
                w = r - 1;
            }
        }
        int res[m][n];
        for (int m1 = 0; m1 < m; ++m1) {
            for (int i1 = 0; i1 < n; ++i1) {
                if (i1 < m) {
                    res[m1][i1] = l[m1][i1];
                } else {
                    res[m1][i1] = d[m1][i1 - m];
                }
            }
        }
        vector *cod_word = v_create();
        int a1;
        int b1;
        int size_of_v=v_get_size(v);
        int m1=0;
        bool flag=false;
        while(m1<size_of_v) {
            for (int n1 = 0; n1 < n; ++n1) {
                a1 = 0;
                for (int i1 = 0; i1 < m; ++i1) {
                    b1 = v_get(v, i1+m1);
                    a1 = a1 + b1 * res[i1][n1];
                }
                if ((a1 % 2) != 0) {
                    v_push(cod_word, 1);
                } else {
                    v_push(cod_word, 0);
                }
            }
            m1=m1+m;
            if(size_of_v-m1<m){
                if(size_of_v-m1!=0){
                    flag=true;
                }
                break;
            }
        }
        if(flag==true){
            write(1, "Нельзя закодировать\n", 40);
        }else {
            char charo[1];
            int o;
            for (int l = 0; l < cod_word->size; ++l) {
                o=v_get(cod_word,l);
                charo[0]=(char)o;
                charo[0]=charo[0]+48;
                write(1,charo, 1);
            }
            write(1,"\n", sizeof("\n"));
        }
    }
    return 0;
}