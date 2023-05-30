#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "histogram.h"

typedef struct {
    size_t size;
    size_t cap;
    float* data;
} Vector;

Vector vector_alloc(size_t init_cap) {
    if (init_cap < 1) {
        fprintf(stderr, "init capacity is less than 1... you can't do that!\n");
        exit(-1);
    }

    Vector v = {
        .size = 0,
        .cap = init_cap,
        .data = malloc(init_cap * sizeof(float))
    };

    if (!v.data) {
        fprintf(stderr, "allocation failed!\n");
        exit(-1);
    }

    return v;
}

Vector vector_realloc(Vector v, size_t cap) {
    v.cap = cap;
    v.data = realloc(v.data, v.cap * sizeof(float));
    if (!v.data) {
        fprintf(stderr, "realloc failed!\n");
        exit(-1);
    }

    return v;
}

Vector vector_append(Vector v, float x) {
    if (v.size + 1 > v.cap) {
        v = vector_realloc(v, 2 * v.cap);
    }

    v.data[v.size++] = x;

    return v;
}

Vector vector_resize(Vector v, size_t size) {
    if (size > v.cap) {
        v = vector_realloc(v, size);
    }

    v.size = size;
    return v;
}

Vector vector_clear(Vector v) {
    // memset(v->data, 0, v->cap); TOO BAD, DOESN'T CLEAN SHIT
    for (size_t i = 0; i < v.cap; ++i) {
        v.data[i] = 0;
    }
    v.size = 0;
    return v;
}

Vector vector_fill_rand(Vector v) {
    for (size_t i = 0; i < v.size; ++i) {
        v.data[i] = (float) rand() / (float) RAND_MAX;
    }

    return v;
}

Vector vector_free(Vector v) {
    free(v.data);
    v.data = NULL;
    v.size = 0;
    v.cap = 0;

    return v;
}

void vector_print(Vector v) {
    printf("vec size: %zu, vec cap: %zu\n", v.size, v.cap);
    printf("(");
    for (size_t i = 0; i < v.size; ++i) {
        printf("%f ", v.data[i]);
    }
    printf(")\n");
}

float multiply(float x, FuncParams pars) {
    return x * pars.params[0];
}

int main(void) {
    /*Vector v = vector_alloc(1);*/
    /*v = vector_resize(v, 20);*/
    /*vector_print(v);*/

    /*v = vector_fill_rand(v);*/
    /*vector_print(v);*/

    /*v = vector_append(v, 228.0f); */
    /*vector_print(v);*/

    /*v = vector_clear(v);*/
    /*vector_print(v);*/

    /*v = vector_free(v);*/

    Histogram1D h = histogram_alloc(10, 0.0f, 10.0f); 
    histogram_print(h);

    h = histogram_fill(h, 1.5);
    h = histogram_fill(h, 2.5);
    h = histogram_fill(h, 4.5);
    h = histogram_fill(h, 1.5);
    h = histogram_fill(h, 1.5);
    h = histogram_fill(h, 20.0);
    histogram_print(h);

    printf("integral is %zu\n", histogram_integral(h, 0, h.nbins - 1));

    float params[] = {4.0f};
    h = histogram_apply(h, multiply, (FuncParams){.n = 1, .params = params});
    histogram_print(h);

    h = histogram_free(h);

    return 0;
}
