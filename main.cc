#include "Particle.h"
#include "TreeNode.h"
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;

#define NUM_PARTS 1000000

int main(void) {
  double xc = 0.,yc = 0., zc = 0.;
  double xs = 2., ys = 2., zs = 2.;

  TreeNode::initializeTree(xc,yc,zc,xs,ys,zs);
  
  Particle *particles[NUM_PARTS];
  for( int i=0; i < NUM_PARTS; i++) {
    double x = xs*rand()/RAND_MAX - xs*0.5;
    double y = ys*rand()/RAND_MAX - ys*0.5;
    double z = zs*rand()/RAND_MAX - zs*0.5;

    particles[i] = new Particle(i,x,y,z);
  }
  
  for( int i=0; i < NUM_PARTS; i++) {
    TreeNode::root->addParticle( particles[i]);
    if( i % 100000 == 0) 
      printf("Adding particle\n");
  }
  
  std::vector<Particle *> pList;
  dVector point(xc,yc,zc);
  double radius = 0.05;
  TreeNode::root->findParticles( point, radius, pList);

  cout << "pList size: " << pList.size() << endl;
  /*
  for( Particle *part : pList) {
    cout << "id: " << part->getId() << endl;
  }
  */
  int total = 0;
  double r2 = radius*radius;
  for( int i; i < NUM_PARTS; i++) {
    dVector dp = particles[i] -> getPosition() - point;
    if( dotProduct(dp,dp) < r2) { 
      total++;
      //cout << "id: " << particles[i]->getId() << endl;    
    }
  }

  cout << "Brute force size: " << total << endl;
  
  
  return 0;
}