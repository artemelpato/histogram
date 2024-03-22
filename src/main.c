#include <stdio.h>
#include "histogram.h"

float multiply(float x, float* pars) {
    return x * pars[0];
}

int main(void) {
    Histogram1D h;
    Histogram1D__init(&h, 10, 0.0f, 10.0f);
    Histogram1D__print(&h);

    Histogram1D__fill(&h, 1.5f);
    Histogram1D__fill(&h, 2.5f);
    Histogram1D__fill(&h, 4.5f);
    Histogram1D__fill(&h, 1.5f);
    Histogram1D__fill(&h, 1.5f);
    Histogram1D__fill(&h, 20.0f);
    Histogram1D__print(&h);

    printf("integral is %zu\n", Histogram1D__integral(&h, 0, h.nbins - 1));

    Histogram1DFunc func;
    func.f = multiply;
    func.n = 1;
    func.params[0] = 4.0f;

    Histogram1D__apply(&h, func);
    Histogram1D__print(&h);

    Histogram1D g;
    Histogram1D__init(&g, 10, 0.0f, 10.0f);
    Histogram1D__add(&g, &h, 3);
    Histogram1D__print(&g);

    printf("integral is %zu\n", Histogram1D__integral(&g, 0, g.nbins - 1));

    Histogram1D__destroy(&g);
    Histogram1D__destroy(&h);

    return 0;
}
