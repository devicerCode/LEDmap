//Whole new rewrite of the mapping stuff
//
//Needs to be a class that contains 2d led mappings and performs various functions on them
//to start need to contain mappings, do this as 0-1 range scaling of whatever goes in...

class map2d { 

  PVector[] mapCoords;
  int mapSize = 0;
  int originalWidth;
  int originalHeight;

  map2d(int mapSize, int originalWidth, int originalHeight) {
    this.mapSize = mapSize;
    mapCoords = new PVector[mapSize];
    this.originalWidth = originalWidth;
    this.originalHeight = originalHeight;
  }

  void setCoord(int mapPosition, PVector newCoord) {
    if ((mapPosition < this.mapSize)&&(mapPosition >= 0)) {
      mapCoords[mapPosition] = newCoord;
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


  void saveMappingStructStyle(String filename,int scale) {

    if (mapping != null) {
      String[] fileOutput = new String[4];
      fileOutput[0] = "struct map2d mapping ={";
      String xString = "{";
      for (int i=0; i<mapping.mapSize-1; i++) {
        xString +=int(mapping.mapCoords[i].x*scale);
        xString +=",";
      }
      xString +=int(mapping.mapCoords[mapping.mapSize-1].x*scale);
      xString += "},";
      fileOutput[1] = xString;
      String yString = "{";
      for (int i=0; i<mapping.mapSize-1; i++) {
        yString +=int(mapping.mapCoords[i].y*scale);
        yString +=",";
      }
      yString +=int(mapping.mapCoords[mapping.mapSize-1].y*scale);
      yString += "}";
      fileOutput[2] = yString;
      fileOutput[3] = "};";
      saveStrings(filename, fileOutput);
      //INFO
      println("Mapping file saved as: ", filename);
    }
  }



  void scaleMap() {
    //scale whole map to be 0-1 range
    //need one that preserves aspect and one for each dimension stretch?
    //
  }


  void outputToLights(PImage currentImage) {
    //use current map to put current image onto lights...
  }



  void drawPositions(int outputwidth, int outputheight) {
    //if (mapCoords != null) {
    for (int i =0; i<mapCoords.length; i++) {
      if (mapCoords[i] != null ) {
        if ((mapCoords[i].x >= 0)&&(mapCoords[i].y >= 0)) {
          output.textSize(24);
          output.fill(255, 120, 120);
          output.rect(mapCoords[i].x*outputwidth, mapCoords[i].y*outputheight, 2, 2);
          output.text(i, mapCoords[i].x*outputwidth, mapCoords[i].y*outputheight);
        }
      }
    }
  }
  //}
}