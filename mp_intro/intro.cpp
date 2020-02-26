#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>
#include <cmath>

void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  cs225::PNG image;

  image.readFromFile(inputFile);
  // cs225::PNG imagein = image(image.width(), image.height());
  cs225::PNG imageout (image.width(), image.height());

  for (int x = 0; x < image.width(); x++){
    for (int y = 0; y < image.height(); y++){
       cs225::HSLAPixel & Pixelin = image.getPixel(image.width()-x-1, image.height()-y-1);
       cs225::HSLAPixel & Pixelout = imageout.getPixel(x,y);
       Pixelout = Pixelin;
    }
  }

  imageout.writeToFile(outputFile);

}

  cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3

  for(int x = 0; x < png.width(); x++){
    for(int y = 0; y < 400; y++){
      cs225::HSLAPixel newpixel(250, 1, 0.5);
      cs225::HSLAPixel & pixel = png.getPixel(x,y);
      pixel = newpixel;
    }
  }

  for(int x = 0; x < png.width(); x++){
    for(int y = 400; y < 800; y++){
      cs225::HSLAPixel newpixel(16, 1, 0.5);
      cs225::HSLAPixel & pixel = png.getPixel(x,y);
      pixel = newpixel;
    }
  }


//we start to play the pixels
  for(int x = 250; x < 549; x++){
      for(int y = 200; y < 203; y++){
      cs225::HSLAPixel newpixel(11, 1, 0.5);
      cs225::HSLAPixel & pixel = png.getPixel(x,y);
      pixel = newpixel;
    }
  }

  for(int x = 250; x < 549; x++){
      for(int y = 600; y < 603; y++){
      cs225::HSLAPixel newpixel(11, 1, 0.5);
      cs225::HSLAPixel & pixel = png.getPixel(x,y);
      pixel = newpixel;
    }
  }

  for(int x = 250; x < 334; x++){
      for(int y = 280; y < 283; y++){
      cs225::HSLAPixel newpixel(11, 1, 0.5);
      cs225::HSLAPixel & pixel = png.getPixel(x,y);
      pixel = newpixel;
    }
  }

  for(int x = 465; x < 549; x++){
      for(int y = 280; y < 283; y++){
      cs225::HSLAPixel newpixel(11, 1, 0.5);
      cs225::HSLAPixel & pixel = png.getPixel(x,y);
      pixel = newpixel;
    }
  }

  for(int x = 250; x < 334; x++){
      for(int y = 517; y < 520; y++){
      cs225::HSLAPixel newpixel(11, 1, 0.5);
      cs225::HSLAPixel & pixel = png.getPixel(x,y);
      pixel = newpixel;
    }
  }

  for(int x = 465; x < 549; x++){
      for(int y = 517; y < 520; y++){
      cs225::HSLAPixel newpixel(11, 1, 0.5);
      cs225::HSLAPixel & pixel = png.getPixel(x,y);
      pixel = newpixel;
    }
  }

  for(int x = 250; x < 253; x++){
      for(int y = 200; y < 280; y++){
      cs225::HSLAPixel newpixel(11, 1, 0.5);
      cs225::HSLAPixel & pixel = png.getPixel(x,y);
      pixel = newpixel;
    }
  }

  for(int x = 250; x < 253; x++){
      for(int y = 520; y < 600; y++){
      cs225::HSLAPixel newpixel(11, 1, 0.5);
      cs225::HSLAPixel & pixel = png.getPixel(x,y);
      pixel = newpixel;
    }
  }

  for(int x = 546; x < 549; x++){
      for(int y = 200; y < 280; y++){
      cs225::HSLAPixel newpixel(11, 1, 0.5);
      cs225::HSLAPixel & pixel = png.getPixel(x,y);
      pixel = newpixel;
    }
  }

  for(int x = 334; x < 337 ; x++){
      for(int y = 280; y < 521; y++){
      cs225::HSLAPixel newpixel(11, 1, 0.5);
      cs225::HSLAPixel & pixel = png.getPixel(x,y);
      pixel = newpixel;
    }
  }

  for(int x = 462; x < 465 ; x++){
      for(int y = 280; y < 521; y++){
      cs225::HSLAPixel newpixel(11, 1, 0.5);
      cs225::HSLAPixel & pixel = png.getPixel(x,y);
      pixel = newpixel;
    }
  }

  for(int x = 546; x < 549 ; x++){
      for(int y = 520; y < 600; y++){
      cs225::HSLAPixel newpixel(11, 1, 0.5);
      cs225::HSLAPixel & pixel = png.getPixel(x,y);
      pixel = newpixel;
    }
  }

//now we try to color inside I
//use three for loops to fill three regions

for(int x = 250; x < 550 ; x++){
    for(int y = 200; y < 283; y++){
    cs225::HSLAPixel newpixel((x+y)/10, 1, 0.5);
    cs225::HSLAPixel & pixel = png.getPixel(x,y);
    pixel = newpixel;
  }
}

for(int x = 334; x < 466 ; x++){
    for(int y = 283; y < 520; y++){
    cs225::HSLAPixel newpixel((x+y)/8, 1, 0.5);
    cs225::HSLAPixel & pixel = png.getPixel(x,y);
    pixel = newpixel;
  }
}

for(int x = 250; x < 550 ; x++){
    for(int y = 520; y < 600; y++){
    cs225::HSLAPixel newpixel((x+y)/5, 1, 0.5);
    cs225::HSLAPixel & pixel = png.getPixel(x,y);
    pixel = newpixel;
  }
}



  return png;
}
