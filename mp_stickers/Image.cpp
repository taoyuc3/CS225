#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <iostream>
#include <cstdlib>
using namespace std;

namespace cs225 {

void Image::lighten(){
  for (unsigned x = 0; x < width(); x++) {
     for (unsigned y = 0; y < height(); y++) {
         HSLAPixel & pixel = getPixel(x, y);
         pixel.l = pixel.l + 0.1;
         if (pixel.l > 1) {
           pixel.l = 1;
          }
      }
  }
}

void Image::lighten(double amount){
  for (unsigned x = 0; x < width(); x++) {
     for (unsigned y = 0; y < height(); y++) {
         HSLAPixel & pixel = getPixel(x, y);
         pixel.l = pixel.l + amount;
         if (pixel.l > 1) {
           pixel.l = 1;
         }
         if (pixel.l < 0) {
           pixel.l = 0;
         }
      }
  }
}

void Image::darken(){
  for (unsigned x = 0; x < width(); x++) {
     for (unsigned y = 0; y < height(); y++) {
         HSLAPixel & pixel = getPixel(x, y);
         pixel.l = pixel.l - 0.1 ;
         if (pixel.l < 0) {
           pixel.l = 0;
         }
      }
  }
}

void Image::darken(double amount){
  for (unsigned x = 0; x < width(); x++) {
     for (unsigned y = 0; y < height(); y++) {
         HSLAPixel & pixel = getPixel(x, y);
         pixel.l = pixel.l - amount;
         if (pixel.l < 0) {
           pixel.l = 0;
         }
         if (pixel.l > 1) {
           pixel.l = 1;
         }
      }
  }
}

void Image::saturate(){
  for (unsigned x = 0; x < width(); x++) {
     for (unsigned y = 0; y < height(); y++) {
         HSLAPixel & pixel = getPixel(x, y);
         pixel.s = pixel.s + 0.1;
         if (pixel.s > 1) {
           pixel.s = 1;
         }
      }
  }
}

void Image::saturate(double amount){
  for (unsigned x = 0; x < width(); x++) {
     for (unsigned y = 0; y < height(); y++) {
         HSLAPixel & pixel = getPixel(x, y);
         pixel.s = pixel.s + amount;
         if (pixel.s > 1) {
           pixel.s = 1;
         }
         if (pixel.s < 0) {
           pixel.s = 0;
         }
       }
  }
}

void Image::desaturate(){
  for (unsigned x = 0; x < width(); x++) {
     for (unsigned y = 0; y < height(); y++) {
         HSLAPixel & pixel = getPixel(x, y);
         pixel.s = pixel.s - 0.1;
         if (pixel.s < 0) {
           pixel.s = 0;
         }
      }
  }
}

void Image::desaturate(double amount){
  for (unsigned x = 0; x < width(); x++) {
     for (unsigned y = 0; y < height(); y++) {
         HSLAPixel & pixel = getPixel(x, y);
         pixel.s = pixel.s - amount;
         if (pixel.s < 0) {
           pixel.s = 0;
         }
         if (pixel.s > 1) {
           pixel.s = 1;
         }
      }
  }

}

void Image::grayscale(){
  for (unsigned x = 0; x < width(); x++) {
     for (unsigned y = 0; y < height(); y++) {
         HSLAPixel & pixel = getPixel(x, y);
         pixel.s = 0;
         }
      }
}

void Image::rotateColor(double degrees){
  for (unsigned x = 0; x < width(); x++) {
     for (unsigned y = 0; y < height(); y++) {
         HSLAPixel & pixel = getPixel(x, y);
         pixel.h = pixel.h + degrees;
         if(pixel.h > 360){
           pixel.h = pixel.h - 360;
         }
         if(pixel.h < 0){
           pixel.h = pixel.h + 360;
         }
        }
      }
}

void Image::illinify(){
  for (unsigned x = 0; x < width(); x++) {
     for (unsigned y = 0; y < height(); y++) {
         HSLAPixel & pixel = getPixel(x, y);
         if(pixel.h <= 294 && pixel.h >= 114){
             pixel.h = 216;
         }
         else{
             pixel.h = 11;
         }
      }
  }

}

void Image::scale(double factor){

  PNG * copy = new PNG(width(), height());

  for (unsigned x = 0; x < width(); x++) {
     for (unsigned y = 0; y < height(); y++) {
       HSLAPixel & pixel = getPixel(x,y);
       HSLAPixel & copypixel = copy->getPixel(x,y);
       copypixel.h = pixel.h;
       copypixel.s = pixel.s;
       copypixel.l = pixel.l;
       copypixel.a = pixel.a;
    }
  }

  resize(unsigned(factor*width()), unsigned(factor*height()));

  for (unsigned x = 0; x < width(); x++) {
     for (unsigned y = 0; y < height(); y++) {
        unsigned newx = x / factor;
        unsigned newy = y / factor;
        HSLAPixel & pixel = getPixel(x,y);
        HSLAPixel & copypixel = copy->getPixel(newx,newy);
            pixel.h = copypixel.h;
            pixel.s = copypixel.s;
            pixel.l = copypixel.l;
            pixel.a = copypixel.a;
      }
  }

  int i = (rand()%41)+180;
  if(getPixel(100,20).h < 180 || getPixel(100,20).h > 220 )
  {
    getPixel(100,20).h = i;
  }

  delete copy;
  copy = NULL;
}

void Image::scale (unsigned w, unsigned h){
  double factor_w = (w*1.0) / width();
  double factor_h = (h*1.0) / height();

      if (factor_w < factor_h){
        scale(factor_w);
      }else{
        scale(factor_h);
      }
      // if (factor_w < 1 && factor_h < 1){
      //   scale(factor_h);
      // }
}


}
