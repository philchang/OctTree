#include "Particle.h"
#include "TreeNode.h"
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>
#include <chrono>  // for high_resolution_clock
using namespace std;

#define NUM_PARTS 10000000


int main(void) {
  double xc = 0.,yc = 0., zc = 0.;
  double xs = 2., ys = 2., zs = 2.;

  TreeNode::initializeTree(xc,yc,zc,xs,ys,zs);
  // Record start time
  auto start = chrono::high_resolution_clock::now();
  cout << "Starting particle population ";

  Particle *particles[NUM_PARTS];
  for( int i=0; i < NUM_PARTS; i++) {
    double x = xs*rand()/RAND_MAX - xs*0.5;
    double y = ys*rand()/RAND_MAX - ys*0.5;
    double z = zs*rand()/RAND_MAX - zs*0.5;

    particles[i] = new Particle(i,x,y,z);
  }

  // Record end time
  auto finish = chrono::high_resolution_clock::now();
  chrono::duration<double> elapsed = finish - start;

  cout << "Elapsed time: " << elapsed.count() << " s\n";

  cout << "Adding Particles ";
  start = chrono::high_resolution_clock::now();

  for( int i=0; i < NUM_PARTS; i++) {
    TreeNode::root->addParticle( particles[i]);
  }

  // Record end time
  finish = chrono::high_resolution_clock::now();
  elapsed = finish - start;

  cout << "took time: " << elapsed.count() << " s\n";

  
  std::vector<Particle *> pList;
  double radius = 0.05;

  cout << "TreeSearch Particles ";
  start = chrono::high_resolution_clock::now();

  for( int i = 0; i < 1000; i++) { 
    dVector point = particles[i]->getPosition();
    pList.clear();
    TreeNode::root->findParticles( point, radius, pList);
  }
  // Record end time
  finish = chrono::high_resolution_clock::now();
  elapsed = finish - start;

  cout << "took time: " << elapsed.count() << " s\n";

  cout << "pList size: " << pList.size() << endl;
  /*
  for( Particle *part : pList) {
    cout << "id: " << part->getId() << endl;
  }
  */
  int total = 0;
  double r2 = radius*radius;
  cout << "BruteSearch Particles ";
  start = chrono::high_resolution_clock::now();

  for( int j = 0; j < 1000; j++) { 
    dVector point = particles[j]->getPosition();
    total = 0;
    for( int i = 0; i < NUM_PARTS; i++) {
     dVector dp = particles[i] -> getPosition() - point;
      if( dotProduct(dp,dp) < r2) { 
        total++;
        //cout << "id: " << particles[i]->getId() << endl;    
      }
    }
  }
  // Record end time
  finish = chrono::high_resolution_clock::now();
  elapsed = finish - start;

  cout << "took time: " << elapsed.count() << " s\n";

  cout << "Brute force size: " << total << endl;
  
  
  return 0;
}
