#include "dVector.h"
#define LEAF_NODE -1
#define ROOT_NODE 0
#define MAX_LEAVES

class TreeNode {
  dVector center, size;
  int numLeafs;
  void *particles[MAX_LEAVES]; // array of pointers
  TreeNode *children;
  TreeNode *parent; 
public:

  TreeNode() {
    parent = ROOT_NODE;
    children = LEAF_NODE;
  }
 
  TreeNode( TreeNode *par) {
    parent = par;
    children = LEAF_NODE;
  }

  dVector getCenter() { return center;}
  dVector getSize() {return size;}
  void getBox( dVector &lCorner, dVector &rCorner ) {
    lCorner = center - size; rCorner = center + size;
  }
  
  void addParticle( void *add);
  void clearParticles();
  
  
   

};
