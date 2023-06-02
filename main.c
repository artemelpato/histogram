#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include "histogram.h"
#include "vector.h"

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

    histogram_fill(h, 1.5);
    histogram_fill(h, 2.5);
    histogram_fill(h, 4.5);
    histogram_fill(h, 1.5);
    histogram_fill(h, 1.5);
    histogram_fill(h, 20.0);
    histogram_print(h);

    printf("integral is %zu\n", histogram_integral(h, 0, h.nbins - 1));

    float params[] = {4.0f};
    histogram_apply(h, multiply, (FuncParams){.n = 1, .params = params});
    histogram_print(h);

    Histogram1D g = histogram_alloc(10, 0.0f, 10.0f);
    histogram_add(g, h, 3);
    histogram_print(g);
    printf("integral is %zu\n", histogram_integral(g, 0, g.nbins - 1));

    h = histogram_free(h);

    return 0;
}
