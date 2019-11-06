#include <stdio.h>
#include "vector.h"
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
int counter=0;

struct args1 {
    vector *v;
    int start;
    int n;
    int r;
    int **h_matr;
    int i1;
    int j1;
    int **res;
    int j2;
};

void *matr_multiply(void *args) {
    pthread_mutex_lock(&mutex);
    struct args1 *arg = (struct args1 *) args;
    int res = 0;
    for (int i = 0; i < arg->n; ++i) {
        res = res + arg->v->body[i+arg->start] * arg->h_matr[i][arg->j1];
    }
    res = res % 2;
    arg->res[0][arg->j2] = res;
    ++arg->j1;
    ++arg->j2;
    ++counter;
    pthread_mutex_unlock(&mutex);
    return EXIT_SUCCESS;
}

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

int what_string(int n,int r,int h_matr[n][r], int res[1][r]){
    bool flag=false;
    int g=0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < r; ++j) {
            if(h_matr[i][j]!=res[0][j]){
                break;
            }else{
                if(j==r-1){
                    flag=true;
                }
            }
        }
        if(flag==true){
            break;
        }
        ++g;
    }
    if(flag==true){
        return g;
    }else{
        return -1;
    }
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
        int l[r][r];
        int p = 0;
        for (int i1 = 0; i1 < r; ++i1) {
            for (int k1 = 0; k1 < r; ++k1) {
                if (k1 == p) {
                    l[i1][k1] = 1;
                } else {
                    l[i1][k1] = 0;
                }
            }
            ++p;
        }
        int d[m][r];
        int x;
        int q = n;
        for (int i1 = 0; i1 < m; ++i1) {
            x = q;
            for (int k1 = r - 1; k1 >= 0; --k1) {
                d[i1][k1] = x % 2;
                x = x / 2;
            }
            q = q - 1;
            if (is_power_0f_two(q)) {
                q = q - 1;
            }
        }
        int h_matr[n][r];
        for (int m1 = 0; m1 < n; ++m1) {
            for (int i1 = 0; i1 < r; ++i1) {
                if (m1 < m) {
                    h_matr[m1][i1] = d[m1][i1];
                } else {
                    h_matr[m1][i1] = l[m1 - m][i1];
                }
            }
        }
        int n1 = 0;
        bool flag = false;
        struct args1 *arg = malloc(sizeof(struct args1));
        int res[1][r];
        vector *decod_word = v_create();
        arg->res=(int **)malloc(sizeof(int *));
        for (int j2 = 0; j2 < 1; ++j2) {
            arg->res[j2] = (int *) malloc(sizeof(int) * r);
        }
        arg->h_matr=(int **)malloc(sizeof(int *)*n);
        for (int k2 = 0; k2 < n; ++k2) {
            arg->h_matr[k2] = (int *) malloc(sizeof(int) * r);
        }
        for (int i1 = 0; i1 < n; ++i1) {
            for (int k1 = 0; k1 < r; ++k1) {
                arg->h_matr[i1][k1]=h_matr[i1][k1];
            }
        }
        pthread_mutex_init(&mutex,NULL);
        while (n1 < v->size) {
            arg->start = n1;
            arg->i1 = 0;
            arg->j1 = 0;
            arg->n = n;
            arg->r = r;
            arg->v = v;
            arg->j2 = 0;
            for (int l = 0; l < r; ++l) {
                pthread_t thread;
                int status;
                status = pthread_create(&thread, NULL, matr_multiply, arg);
                if (status != 0) {
                    exit(EXIT_FAILURE);
                }
                pthread_join(thread,NULL);
            }
            for (int l1 = 0; l1 < 1; ++l1) {
                for (int i1 = 0; i1 < r; ++i1) {
                    res[l1][i1]=arg->res[l1][i1];
                }
            }
            int results = 0;
            for (int i1 = 0; i1 < r; ++i1) {
                results = results + pow(2, r-i1-1) * res[0][i1];
            }
            if (results != 0) {
                int f=what_string(n,r,h_matr,res);
                if(is_power_0f_two(results)){
                    v->body[n1 + f] = (v->body[n1 + f] + 1) % 2;
                }else {
                    v->body[n1 + f] = (v->body[n1 + f] + 1) % 2;
                }
            }
            for (int k1 = 0; k1 < m; ++k1) {
                v_push(decod_word, v->body[n1 + k1]);
            }
            n1 = n1 + n;
            if (v->size - n1 < n) {
                if (v->size - n1 != 0) {
                    flag = true;
                }
                free(arg);
                break;
            }
        }
        if (flag == true) {
            write(1, "Нельзя декодировать\n", 40);
        }else {
            pthread_mutex_destroy(&mutex);
            char charo[1];
            int o;
            for (int l = 0; l < decod_word->size; ++l) {
                o=v_get(decod_word,l);
                charo[0]=(char)o;
                charo[0]=charo[0]+48;
                write(1,charo, 1);
            }
            write(1,"\n", sizeof("\n"));
            write(1,&counter, 8);
        }
    }
    return 0;
}