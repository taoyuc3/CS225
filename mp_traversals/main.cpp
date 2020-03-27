
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  PNG png = PNG();
  MyColorPicker color_ = MyColorPicker();

  png.readFromFile("Mario.png");
  FloodFilledImage image(png);


  BFS bfs1(png, Point(10,10), 0.2);
  image.addFloodFill(bfs1, color_);

  // Animation animation = image.animate(1000);

  BFS bfs2(png, Point(1,1), 0.1);
  image.addFloodFill(bfs2, color_);
  //
  BFS bfs3(png, Point(249,382), 0.5);
  image.addFloodFill(bfs3, color_);
  //
  BFS bfs4(png, Point(30,30), 0.5);
  image.addFloodFill(bfs4, color_);

  // BFS bfs5(png, Point(50,100), 0.5);
  // image.addFloodFill(bfs5, color_);

  // BFS bfs6(png, Point(150,150), 0.05);
  // image.addFloodFill(bfs6, color_);


  DFS dfs(png, Point(200,150), 0.5);
  image.addFloodFill(dfs, color_);
  //
  // DFS dfs2(png, Point(200,50), 0.2);
  // image.addFloodFill(dfs2, color_);

  Animation animation = image.animate(1000);


  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");

  return 0;
}
