//Whole new rewrite of the mapping stuff
//
//Needs to be a class that contains 2d led mappings and performs various functions on them
//to start need to contain mappings, do this as 0-1 range scaling of whatever goes in...
//then functions to ouput 0-255 scaled (byte-scaled) versions for 8bitters (and also just more efficient for small maps)
//and one that does it as 16bit output
//can later add generators? 
//Also need constructor that takes in an image? 
//actually no, just want to do add() and remove() things for it?

class map2d { 

  PVector[] mapCoords;
  int mapSize = 0;

  map2d(int mapSize) {
    this.mapSize = mapSize;
    mapCoords = new PVector[mapSize];
  }


  void setCoord(int mapPosition, PVector newCoord) {
    if ((mapPosition < this.mapSize)&&(mapPosition >= 0)) {
      mapCoords[mapPosition] = newCoord;
      //mapCoords[mapPosition] = new PVector(newCoord.x,newCoord.y);
    }
  }


  PVector getCoord(int mapPosition) {

    if ((mapPosition < mapSize)&&(mapPosition >=0)) {
      return mapCoords[mapPosition];
    } else {
      return new PVector(-1, -1);
    }
  }



  map2d(String filename) {
    //load mapping file
    //
    //need to check it fits in numleds size etc...
  }

  void scaleMap() {
    //scale whole map to be 0-1 range
    //need one that preserves aspect and one for each dimension stretch?
    //
  }


  void outputToLights(PImage currentImage) {
    //use current map to put current image onto lights...
  }



  void drawPositions(int outputwidth,int outputheight) {
    //if (mapCoords != null) {
      for (int i =0; i<mapCoords.length; i++) {
        if (mapCoords[i] != null ) {
          if ((mapCoords[i].x >= 0)&&(mapCoords[i].y >= 0)) {
            //output.strokeWeight(2);
            //output.stroke(120,120,120);
            output.textSize(24);
            output.fill(255,120,120);
            output.rect(mapCoords[i].x*outputwidth,mapCoords[i].y*outputheight,2,2);
            output.text(i, mapCoords[i].x*outputwidth, mapCoords[i].y*outputheight);
          }
        }
      }
    }
  //}
}