#include "TreeNode.h"
#include "dVector.h"
#include <math.h>

#define SQRT_THREE 1.73205

TreeNode* TreeNode::root = 0;

void TreeNode::initializeTree( double x, double y, double z, 
    double xmax, double ymax, double zmax) {
  TreeNode::root = new TreeNode();
  root->center[0] = x; root->center[1] = y; root->center[2] = z;
  root->size[0] = xmax; root->size[1] = ymax; root->size[2] = zmax;
}

void TreeNode::divideTree() {
  isLeaf = false; numParticles = 0;
  dVector childSize = size*0.5;
  dVector childCenter[NUM_CHILDREN];  
  // bottom
  childCenter[0] = center - childSize;
  childCenter[1] = childCenter[0];
  childCenter[1][0] += size[0];
  childCenter[2] = childCenter[0];
  childCenter[2][1] += size[1];
  childCenter[3] = childCenter[2];
  childCenter[3][0] += size[0];
  // top
  childCenter[4] = childCenter[0];
  childCenter[4][2] += size[2];
  childCenter[5] = childCenter[4];
  childCenter[5][0] += size[0];
  childCenter[6] = childCenter[4];
  childCenter[6][1] += size[1];
  childCenter[7] = childCenter[6];
  childCenter[7][0] += size[0];
  
  for( int i = 0; i < NUM_CHILDREN; i++) { 
    children[i] = new TreeNode(this, childCenter[i], childSize);
  } 

}

void TreeNode::addParticle( Particle *part) {
  // walk tree
  dVector delta = part->getPosition() - center;
  if( abs(delta[0]) > size[0] || abs(delta[1]) > size[1] || abs(delta[2]) > size[2])
    return; //not this node or children

  if( isLeaf) {
    if( numParticles < MAX_PARTICLES_LEAF) 
      particles[numParticles++] = part;     
    else {
      divideTree();
      for( int i = 0; i < MAX_PARTICLES_LEAF; i++) {
        addParticle( particles[i]);
      }
      addParticle( part);
    }
  } 
  else {
    for(int i = 0; i < NUM_CHILDREN; i++) 
      children[i] -> addParticle( part);
  }
}

void TreeNode::findParticles(dVector point, double radius, std::vector<Particle*>& pList){
  dVector delta = point - center;
  double rsize = sqrt(dotProduct(size,size));
  double maxRadius = (radius+SQRT_THREE*rsize);
  if( dotProduct( delta, delta) > maxRadius*maxRadius)
    return;

  if( isLeaf) {
    double r2 = radius*radius;
    for( int i = 0; i < numParticles; i++) {
      dVector dp = particles[i]->getPosition() - point;
      if( dotProduct(dp,dp) < r2) {
        pList.push_back( particles[i]);
      }
    }
  }
  else {
    for(int i = 0; i < NUM_CHILDREN; i++) 
      children[i] -> findParticles( point, radius, pList);
  }
}

