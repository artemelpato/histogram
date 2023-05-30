#ifndef __HISTOGRAM_H__
#define __HISTOGRAM_H__

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Histogram1D Histogram1D;
struct Histogram1D {
    size_t nbins;
    float* edges;
    int* sumw;
    int* sumw2;
};

Histogram1D histogram_alloc(size_t nbins, float xlow, float xhigh) {
    Histogram1D h = {
        .nbins = nbins,
        .edges = malloc((nbins + 1) * sizeof(float)),
        .sumw = malloc(nbins * sizeof(int)),
        .sumw2 = malloc(nbins * sizeof(int))
    };

    if (!h.edges || !h.sumw || !h.sumw2) {
        fprintf(stderr, "error allocating histogram!\n");
        exit(-1);
    }

    float step = (xhigh - xlow) / nbins;
    h.edges[0] = xlow;
    for (size_t i = 0; i < h.nbins; ++i) {
        h.edges[i + 1] = h.edges[i] + step; 
        h.sumw[i] = 0;
        h.sumw2[i] = 0;
    }

    return h;
}

size_t histogram_find_bin(Histogram1D h, float x) {
    for (size_t i = 0; i < h.nbins; ++i) {
        if (h.edges[i] <= x && x < h.edges[i + 1]) {
            return i;
        }
    }
    return -1;
}

Histogram1D histogram_fill(Histogram1D h, float x) {
    size_t i = histogram_find_bin(h, x);
    h.sumw[i]++;
    h.sumw2[i]++;

    return h;
}

void histogram_print(Histogram1D h) {
    printf("nbins %zu from %.2f to %.2f\n", h.nbins, h.edges[0], h.edges[h.nbins]);
    
    for (size_t i = 0; i < h.nbins; ++i) {
        printf("[%.2f - %.2f] -> %d (%d)\n", 
                h.edges[i], h.edges[i + 1], 
                h.sumw[i], h.sumw2[i]);
    }

    return;
}

Histogram1D histogram_free(Histogram1D h) {
    free(h.edges);
    free(h.sumw);
    free(h.sumw2);

    h.edges = NULL;
    h.sumw = NULL;
    h.sumw2 = NULL;
    h.nbins = 0;

    return h;
}

#endif 
