#include "hilbert.h"

Hilbert::Hilbert(const int order){
  len = order;
  const float epi = 535.49; //pow(e,pi)
  Icoef = new float[len*2];
  Qcoef = new float[len*2];
  Imem = new float[len*2];
  Qmem = new float[len*2];

  // Create coeffecients
  for( int i = 0; i<len; ++i ){
    Icoef[i] = powf(epi, powf(2,-i*2));
    Qcoef[i] = powf(epi, powf(2,-i*2-1));
    Icoef[i+len] = 1/Icoef[i];
    Qcoef[i+len] = 1/Qcoef[i];
  }
}

Hilbert::Hilbert(const Hilbert &copy){
  len = copy.len;
  Icoef = new float[len*2];
  Qcoef = new float[len*2];
  Imem = new float[len*2];
  Qmem = new float[len*2];
  for( int i = 0; i<len*2; ++i ){
    Icoef[i] = copy.Icoef[i];
    Qcoef[i] = copy.Qcoef[i];
  }
}

float Hilbert::ProcessI(float sample){
  float result = simple_iir(sample, Icoef, Imem);
  // Correct the gain
  result *= 1./4000;
  return result;
}

float Hilbert::ProcessQ(float sample){
  float result = simple_iir(sample, Qcoef, Qmem);
  // Correct the gain
  result *= 1./60;
  return result;
}

Hilbert::~Hilbert(void){
  delete Icoef;
  delete Qcoef;
  delete Imem;
  delete Qmem;
}

float Hilbert::simple_iir(float in, float * coef, float * mem ){
  for( int i = 0; i < len; ++i ){
    in += mem[i] * coef[i+len];
    float out = in - mem[i] * coef[i];
    mem[i] = in;
    in = out;
  }
  return in;
}
