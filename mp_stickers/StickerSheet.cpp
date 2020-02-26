#include <iostream>
#include <string>
#include "Image.h"
#include "StickerSheet.h"

namespace cs225{

StickerSheet::StickerSheet(const Image & picture, unsigned max){

  sticker_max = max;
  sticker_count = 0;

  stickers = new Image*[max];
  xp = new unsigned[max];
  yp = new unsigned[max];
  count = new unsigned[max];
  for (unsigned i = 0 ; i < max ; i++){
     xp[i] = 0;
     yp[i] = 0;
     count[i] = 0;
     stickers[i] = NULL;
  }

  this->baseimage = new Image(picture);

}

StickerSheet::~StickerSheet(){
  distroy();
}

StickerSheet::StickerSheet(const StickerSheet &other){
  copy(other);
}

const StickerSheet & StickerSheet::operator= (const StickerSheet &other){

if(this == &other)
  return *this;

  distroy();
  copy(other);
  return *this;
}

void StickerSheet::changeMaxStickers (unsigned max){
  if(sticker_max == max){
    return;
  }
  unsigned sticker2_count = 0;

  Image ** stickers2 = new Image *[max];
  Image * baseimage2 = new Image(*baseimage);

  unsigned * xp2 = new unsigned[max];
  unsigned * yp2 = new unsigned[max];
  unsigned * count2 = new unsigned[max];

  if(max > sticker_max){
    for(unsigned i = 0; i < sticker_max; i++){
      stickers2[i] = NULL;
      count2[i] = 0;
    }
  }

  if(max < sticker_max){
    for(unsigned i = 0; i < sticker_max; i++){
      if(count[i] != 0){
        delete stickers[i];
        stickers[i] = NULL;
        count[i] = 0;
      }
    }
    sticker_max = max;
  }

  for(unsigned i = 0; i < sticker_max; i++){
    if(count[i] != 0){
      stickers2[i] = new Image(*(stickers[i]));
      xp2[i] = xp[i];
      yp2[i] = yp[i];
      count2[i] = count[i];
    }else{
      stickers2[i] = NULL;
      count[i] = 0;
    }
  }

  distroy();

  sticker_max = max;
  sticker_count = sticker2_count;
  stickers = stickers2;
  baseimage = baseimage2;
  xp = xp2;
  yp = yp2;
  count = count2;
}

int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y){
  if(sticker_count < sticker_max){
    for(unsigned i = 0; i < sticker_max; i++ ){
      if(count[i] == 0)
      {
        stickers[i] = new Image(sticker);
        xp[i] = x;
        yp[i] = y;
        count[i] = count[i]+1;
        sticker_count = sticker_count + 1;
        return i;
      }
    }
  }
  return -1;
}

bool StickerSheet::translate (unsigned index, unsigned x, unsigned y){
  if (index >= sticker_max || count[index] == 0){
    return false;
  }else{
    return true;
  }
}

void StickerSheet::removeSticker (unsigned index){
  if(index < sticker_max && count[index] != 0){
    delete stickers[index];
    stickers[index] = NULL;
    sticker_count = 1;
    xp[index] = 0;
    yp[index] = 0;
    count[index] = 0;
  }

}

Image * StickerSheet::getSticker (unsigned index){
  if(index >= sticker_max || count[index] == 0){
    return NULL;
  }
  return stickers[index];
}

Image StickerSheet::render () const{
  unsigned render_x = baseimage->width();
  unsigned render_y = baseimage->height();
  for(unsigned i = 0; i < sticker_count; i++){
    if(count[i] != 0){
      unsigned x = stickers[i]->width() + xp[i];
      unsigned y = stickers[i]->height() + yp[i];
      if(render_x < x){
        render_x = x;
      }
      if(render_y < y){
        render_y = y;
      }
    }
  }
  Image *show = new Image(*baseimage);
  show->resize(render_x,render_y);

  for(unsigned i = 0; i < sticker_max; i++){
    if(count[i] != 0){
      Image sticker = *stickers[i];
      for(unsigned a = xp[i]; a < xp[i]+ sticker.width(); a++){
        for(unsigned b = yp[i]; b < yp[i]+ sticker.height(); b++){
          cs225::HSLAPixel & pixel = sticker.getPixel(a-xp[i], b-yp[i]);
          cs225::HSLAPixel & outpixel = show->getPixel(a, b);

          if(pixel.a != 0){
            outpixel.h = pixel.h;
            outpixel.s = pixel.s;
            outpixel.l = pixel.l;
            outpixel.a = pixel.a;
          }

        }
      }
    }
  }
  Image output = *show;
  delete show;
  show = NULL;
  return output;

}

void StickerSheet::distroy(){
  for (unsigned i = 0; i < sticker_max; i++){
    delete stickers[i];
    stickers[i] = NULL;
  }
  delete [] count;
  count = NULL;
  delete [] baseimage;
  baseimage = NULL;
  delete [] stickers;
  stickers = NULL;
  delete [] xp;
  xp = NULL;
  delete [] yp;
  yp = NULL;
}

void StickerSheet::copy(const StickerSheet &other){
  sticker_max = other.sticker_max;
  sticker_count = other.sticker_count;

  baseimage = new Image(*(other.baseimage));
  stickers = new Image*[sticker_max];
  xp = new unsigned[sticker_max];
  yp = new unsigned[sticker_max];
  count = new unsigned [sticker_max];
  for(unsigned i = 0; i < sticker_max; i++){
    if(other.count[i] != 0)
    {
      count[i] = other.count[i];
      stickers[i] = new Image(*(other.stickers[i]));
      xp[i] = other.xp[i];
      yp[i] = other.yp[i];
    }else{
      count[i] = 0;
      stickers[i] = NULL;
      xp[i] = 0;
      yp[i] = 0;
    }
  }
}

} //this for namespace
