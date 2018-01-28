#ifndef TREENODE_H
#define TREENODE_H

#include "dVector.h"
#include "Particle.h"
#include <vector>
#define LEAF_NODE -1
#define ROOT_NODE 0
#define NUM_CHILDREN 8
#define MAX_PARTICLES_LEAF 32

class TreeNode {
  dVector center, size;
  int numParticles;
  Particle *particles[MAX_PARTICLES_LEAF]; // array of pointers
  TreeNode *children[NUM_CHILDREN];
  TreeNode *parent; 
public:
  bool isLeaf;

  TreeNode() {
    parent = ROOT_NODE;
    isLeaf = true;
    numParticles = 0;
  }
 
  TreeNode( TreeNode *par, dVector c, dVector s) {
    parent = par;
    isLeaf = true;
    center = c;
    size = s;
    numParticles = 0; 
  }

  dVector getCenter() { return center;}
  dVector getSize() {return size;}
  void getBox( dVector &lCorner, dVector &rCorner ) {
    lCorner = center - size; rCorner = center + size;
  }
  
  void addParticle( Particle *part);
  void divideTree();
  void findParticles(dVector point, double radius, std::vector<Particle*>& pList);

  static TreeNode *root;
  static void initializeTree( double x, double y, double z, 
    double xmax, double ymax, double zmax);
};

#endif
