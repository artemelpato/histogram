#ifndef __HISTOGRAM_H__
#define __HISTOGRAM_H__

#include <stddef.h>

typedef struct Histogram1D_s {
    size_t nbins;
    float* edges;
    int*   sumw;
    int*   sumw2;
} Histogram1D;

typedef struct FuncParams_s {
    size_t n;
    float* params;
} FuncParams;

typedef float (*Func)(float, FuncParams);

typedef enum HistogramConsistency_e {
    HISTOGRAM_DIFF_NBINS,
    HISTOGRAM_DIFF_BINS,
    HISTOGRAM_CONSISTENT
} HistogramConsistency;

int                  Histogram1D__init(Histogram1D* h, size_t nbins, float xlow, float xhigh);
void                 Histogram1D__destroy(Histogram1D* h);
size_t               Histogram1D__find_bin(Histogram1D* h, float x);
void                 Histogram1D__fill(Histogram1D* h, float x);
void                 Histogram1D__apply(Histogram1D* h, Func f, FuncParams pars);
void                 Histogram1D__scale(Histogram1D* h, float scale);
size_t               Histogram1D__integral(Histogram1D* h, size_t low_bin, size_t high_bin);
HistogramConsistency Histogram1D__check_consistency(Histogram1D* h1, Histogram1D* h2) ;
void                 Histogram1D__add(Histogram1D* h1, Histogram1D* h2, float scale);
void                 Histogram1D__copy(Histogram1D* to, Histogram1D* from);
void                 Histogram1D__print(Histogram1D* h);


#endif 
