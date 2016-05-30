# Arctic Lime Platformer

Arctic Lime is a 2D platformer framework built with SDL. Its physics system is built from using tile-based collision, (which is based off of a tutorial which I can't find). So far there are three main classes in the framework:

**Player Class:**
In the Player Class is where all of the actual physics are processed. It basically checks if any of the tiles it is next too are solid, and it either stops or adds its x and y velocity to its position. 

**Map Class:**
Inside the Map Class is where you design the map. It contains a tile struct, which contains a texture and a bool, to tell if it is solid. The Player Class uses these in the physics system.

**Droppable Class:**
The Dropabble Class is a pretty simple class and its main purpose is to be inherited by more specialized classes, such as a Gun or Helmet Class, which will be implemented soon.

