#include <stdio.h>
#include <stdlib.h>

//Struktura liczby Kolosalnej

typedef struct Liczba {
    struct Liczba **cyfry;
    int n;
} Liczba;

//stos
typedef struct Wezel {
    Liczba *liczba;
    struct Wezel *nastepny;
} Wezel;

//Podstawowe Operacje

Liczba *nowa_liczba(void) {
    Liczba *x = malloc(sizeof(Liczba));
    x->cyfry = NULL;
    x->n = 0;
    return x;
}

void usun_liczbe(Liczba *x) {
    if (!x) return;
    for (int i = 0; i < x->n; i++)
        usun_liczbe(x->cyfry[i]);
    free(x->cyfry);
    free(x);
}

void dodaj_cyfre(Liczba *l, Liczba *c) {
    Liczba **tmp = realloc(l->cyfry, sizeof(Liczba *) * (size_t) (l->n + 1));
    if (!tmp) {
        usun_liczbe(c);
        usun_liczbe(l);
        exit(1);
    }
    l->cyfry = tmp;
    l->cyfry[l->n++] = c;
}

Liczba *kolosalna_jeden(void) {
    Liczba *x = nowa_liczba();
    dodaj_cyfre(x, nowa_liczba());
    return x;
}

Liczba *kopia(const Liczba *x) {
    Liczba *r = nowa_liczba();
    for (int i = 0; i < x->n; i++)
        dodaj_cyfre(r, kopia(x->cyfry[i]));
    return r;
}

//wejście i wyjście

Liczba *czytaj(void) {
    Liczba *x = nowa_liczba();
    int c;
    while ((c = getchar()) == '1')
        dodaj_cyfre(x, czytaj());
    return x;
}

void wypisz(const Liczba *x) {
    for (int i = 0; i < x->n; i++) {
        putchar('1');
        wypisz(x->cyfry[i]);
    }
    putchar('0');
}

Liczba *scalanie(const Liczba *a, const Liczba *b) {
    Liczba *w = nowa_liczba();
    for (int i = 0; i < a->n; i++)
        dodaj_cyfre(w, kopia(a->cyfry[i]));
    for (int i = 0; i < b->n; i++)
        dodaj_cyfre(w, kopia(b->cyfry[i]));
    return w;
}

//porównanie liczb kolosalnych

int cmp_liczby(const Liczba *x, const Liczba *y) {
    if (x == y) return 0;
    // Porównujemy od największych cyfr
    int i = 0;
    while (i < x->n && i < y->n) {
        int r = cmp_liczby(x->cyfry[i], y->cyfry[i]);
        if (r != 0) return r;
        i++;
    }
    if (x->n > y->n) return 1; // x ma więcej cyfr = x większe
    if (x->n < y->n) return -1; // y ma więcej cyfr = y większe
    return 0;
}

int cmp_qsort(const void *a, const void *b) {
    const Liczba *x = *(const Liczba **) a;
    const Liczba *y = *(const Liczba **) b;
    return -cmp_liczby(x, y);
}

//normalizacja liczb kolosalnych

Liczba *sum(const Liczba *a, const Liczba *b);

void normalizacja(Liczba *x) {
    if (!x || x->n <= 1) return;

    for (int i = 0; i < x->n; i++)
        normalizacja(x->cyfry[i]);

    qsort(x->cyfry, (size_t) x->n, sizeof(Liczba *), cmp_qsort);
    for (int i = x->n - 1; i > 0;) {
        if (cmp_liczby(x->cyfry[i], x->cyfry[i - 1]) == 0) {
            Liczba *jeden = kolosalna_jeden();
            Liczba *nowa = sum(x->cyfry[i - 1], jeden);
            usun_liczbe(jeden);
            usun_liczbe(x->cyfry[i]);
            usun_liczbe(x->cyfry[i - 1]);

            x->cyfry[i - 1] = nowa;
            for (int j = i + 1; j < x->n; j++)
                x->cyfry[j - 1] = x->cyfry[j];
            x->n--;
            if (x->n == 0) {
                free(x->cyfry);
                x->cyfry = NULL;
            } else {
                Liczba **tmp = realloc(x->cyfry, sizeof *x->cyfry * (size_t) x->n);
                if (!tmp) exit(1);
                x->cyfry = tmp;
            }
            qsort(x->cyfry, (size_t) x->n, sizeof(Liczba *), cmp_qsort);
            i = x->n - 1;
        } else i--;
    }
}

//operacje arytmetyczne na liczbach kolosalnych

Liczba *pow2(const Liczba *x) {
    Liczba *y = nowa_liczba();
    dodaj_cyfre(y, kopia(x));
    return y;
}

Liczba *sum(const Liczba *a, const Liczba *b) {
    Liczba *z = scalanie(a, b);
    normalizacja(z);
    return z;
}

Liczba *mnoz(const Liczba *a, const Liczba *b) {
    Liczba *w = nowa_liczba();
    for (int i = 0; i < a->n; i++) {
        for (int j = 0; j < b->n; j++) {
            Liczba *wyk = scalanie(a->cyfry[i], b->cyfry[j]);
            normalizacja(wyk);
            dodaj_cyfre(w, wyk);
        }
    }
    normalizacja(w);
    return w;
}

//operacje na stosie

void push(Wezel **s, Liczba *x) {
    Wezel *w = malloc(sizeof(Wezel));
    w->liczba = x;
    w->nastepny = *s;
    *s = w;
}

Liczba *pop(Wezel **s) {
    if (!*s) return NULL;
    Wezel *w = *s;
    Liczba *x = w->liczba;
    *s = w->nastepny;
    free(w);
    return x;
}

void zwolnij_stos(Wezel **s) {
    while (*s)
        usun_liczbe(pop(s));
}

int main(void) {
    Wezel *stos = NULL;
    int ch;
    while ((ch = getchar()) != EOF) {
        switch (ch) {
            case '0':
            case '1': {
                ungetc(ch, stdin);
                Liczba *x = czytaj();
                normalizacja(x);
                push(&stos, x);
                break;
            }
            case '.': {
                Liczba *x = pop(&stos);
                if (x) {
                    wypisz(x);
                    putchar('\n');
                    usun_liczbe(x);
                }
                break;
            }
            case ':': {
                Liczba *x = pop(&stos);
                if (x) {
                    push(&stos, kopia(x));
                    push(&stos, x);
                }
                break;
            }
            case '+': {
                Liczba *b = pop(&stos);
                Liczba *a = pop(&stos);
                push(&stos, sum(a, b));
                usun_liczbe(a);
                usun_liczbe(b);
                break;
            }
            case '*': {
                Liczba *b = pop(&stos);
                Liczba *a = pop(&stos);
                push(&stos, mnoz(a, b));
                usun_liczbe(a);
                usun_liczbe(b);
                break;
            }
            case '^': {
                Liczba *x = pop(&stos);
                push(&stos, pow2(x));
                usun_liczbe(x);
                break;
            }
            default:
                break;
        }
    }
    zwolnij_stos(&stos);
    return 0;
}
