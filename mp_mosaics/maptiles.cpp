/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    MosaicCanvas * myCanvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    vector<Point<3>> myPoints;
    map<Point<3>, TileImage*> mytileMap;

    for(TileImage & tile: theTiles){
        LUVAPixel myPixel = tile.getAverageColor();
        Point<3> xyz = convertToXYZ(myPixel);
        myPoints.push_back(xyz);
        mytileMap[xyz] = &tile;
    }

    KDTree<3> * tree = new KDTree<3>(myPoints);
    for(int i = 0; i < theSource.getRows(); i++){
      for(int j = 0; j < theSource.getColumns(); j++){
          LUVAPixel color = theSource.getRegionColor(i, j);
          Point<3> xyz = convertToXYZ(color);
          Point<3> nearest = tree->findNearestNeighbor(xyz);
          myCanvas->setTile(i, j, mytileMap[nearest]);
      }
    }
    delete tree;
    tree = NULL;
    return myCanvas;
    // return NULL;
}
