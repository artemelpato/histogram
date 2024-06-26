#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include "histogram.h"

int Histogram1D__init(Histogram1D* h, size_t nbins, float xlow, float xhigh) {
    h->nbins = nbins;
    h->edges = malloc((nbins + 1) * sizeof(float));
    h->sumw = malloc(nbins * sizeof(int));
    h->sumw2 = malloc(nbins * sizeof(int));

    if (!h->edges || !h->sumw || !h->sumw2)
        return -1;

    float step = (xhigh - xlow) / nbins;
    h->edges[0] = xlow;
    for (size_t i = 0; i < h->nbins; ++i) {
        h->edges[i + 1] = h->edges[i] + step; 
        h->sumw[i] = 0;
        h->sumw2[i] = 0;
    }

    return 0;
}

void Histogram1D__destroy(Histogram1D* h) {
    free(h->edges);
    free(h->sumw);
    free(h->sumw2);

    h->edges = NULL;
    h->sumw = NULL;
    h->sumw2 = NULL;
    h->nbins = 0;
}

// for now just check all bins, which is ok for small
// histograms, but maybe binary search will be better 
// at big histograms
size_t Histogram1D__find_bin(Histogram1D* h, float x) {
    for (size_t i = 0; i < h->nbins; ++i) {
        if (h->edges[i] <= x && x < h->edges[i + 1]) {
            return i;
        }
    }
    return -1;
}

void Histogram1D__fill(Histogram1D* h, float x) {
    size_t i = Histogram1D__find_bin(h, x);
    if (i < 0 || i >= h->nbins) {
        return;
    }

    h->sumw[i]++;
    h->sumw2[i]++;

    return;
}

void Histogram1D__apply(Histogram1D* h, Histogram1DFunc f) {
    for (size_t i = 0; i < h->nbins; ++i) {
        float tmp = f.f(h->sumw[i], f.params);
        h->sumw[i] = tmp;
        h->sumw2[i] = 0; // currently undefined
    }

    return;
}

void Histogram1D__scale(Histogram1D* h, float scale) {
    for (size_t i = 0; i < h->nbins; ++i) {
        h->sumw[i] *= scale;
        h->sumw2[i] *= scale * scale;
    }

    return;
}

size_t Histogram1D__integral(Histogram1D* h, size_t low_bin, size_t high_bin) {
    size_t integral = 0;
    for (size_t i = low_bin; i <= high_bin; ++i) {
        integral += h->sumw[i];
    }
    return integral;
}

HistogramConsistency Histogram1D__check_consistency(Histogram1D* h1, Histogram1D* h2) { 
    if (h1->nbins != h2->nbins) 
        return HISTOGRAM_DIFF_NBINS;

    for (size_t i = 0; i < h1->nbins + 1; ++i) {
        if (fabs(h1->edges[i] - h2->edges[i]) >= FLT_EPSILON)
            return HISTOGRAM_DIFF_BINS;
    }

    return HISTOGRAM_CONSISTENT;
}

void Histogram1D__add(Histogram1D* h1, Histogram1D* h2, float scale) {
    HistogramConsistency consistency = Histogram1D__check_consistency(h1, h2);

    switch (consistency) {
    case HISTOGRAM_DIFF_NBINS:
        fprintf(stderr, "you can't add histograms with different number of bins!!!\n");
        exit(-1);
        break;

    case HISTOGRAM_DIFF_BINS:
        fprintf(stderr, "you can't add histograms with different bin edges!!!\n");
        exit(-1);
        break;

    case HISTOGRAM_CONSISTENT:
        break;
    }
    
    for (size_t i = 0; i < h1->nbins; ++i) {
        h1->sumw[i] += h2->sumw[i] * scale;
        h1->sumw2[i] += h2->sumw2[i] * scale * scale;
    }

    return;
}

void Histogram1D__copy(Histogram1D* to, Histogram1D* from) {
    HistogramConsistency consistency = Histogram1D__check_consistency(to, from);
    switch (consistency) {
    case HISTOGRAM_DIFF_NBINS:
        fprintf(stderr, "you can't copy histograms with different number of bins!!!\n");
        exit(-1);
        break;

    case HISTOGRAM_DIFF_BINS:
        fprintf(stderr, "you can't copy histograms with different bin edges!!!\n");
        exit(-1);
        break;

    case HISTOGRAM_CONSISTENT:
        break;
    }

    for (size_t i = 0; i < to->nbins; ++i) {
        to->sumw[i] = from->sumw[i];
        to->sumw2[i] = from->sumw2[i];
    }

    return;
}

void Histogram1D__print(Histogram1D* h) {
    printf("nbins %zu from %.2f to %.2f\n", h->nbins, h->edges[0], h->edges[h->nbins]);
    
    for (size_t i = 0; i < h->nbins; ++i) {
        printf("[%.2f - %.2f] -> %d (%d)\n", 
                h->edges[i], h->edges[i + 1], 
                h->sumw[i], h->sumw2[i]);
    }

    return;
}
