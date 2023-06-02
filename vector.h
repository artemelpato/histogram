#ifndef __VECTOR_H__
#define __VECTOR_H__

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

#endif
