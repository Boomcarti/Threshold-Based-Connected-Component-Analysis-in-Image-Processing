#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "ConnectedComponent.h"
typedef bool boolean;


namespace MGWTAD001{

   //defualt construcor
ConnectedComponent::ConnectedComponent(void){
         numberofpixels=0;
         componentid=0;
     }

ConnectedComponent::~ConnectedComponent(){
}
void ConnectedComponent::addBoundary(){
    boundaryPixels++;
}

int ConnectedComponent::getBoundary () const{
  return boundaryPixels;
}

ConnectedComponent::ConnectedComponent( const ConnectedComponent& other ):Pixels(other.Pixels),numberofpixels(other.numberofpixels),componentid(other.componentid){}

ConnectedComponent::ConnectedComponent(ConnectedComponent && other):Pixels(other.Pixels),numberofpixels(other.numberofpixels),componentid(other.componentid){
    other.componentid=0;
    other.numberofpixels=0;
    other.Pixels.clear();

}

ConnectedComponent& ConnectedComponent::operator=( const ConnectedComponent & other){
    if(this !=&other){
        this->Pixels = other.Pixels;
        this->componentid = other.componentid;
        this->numberofpixels= other.numberofpixels;

    }
    return*this;
    

}
 ConnectedComponent& ConnectedComponent::operator=(ConnectedComponent && other){
if(this!=&other){
  this->Pixels = other.Pixels;
        this->componentid = other.componentid;
        this->numberofpixels= other.numberofpixels;
        other.componentid=0;
        other.numberofpixels=0;
        
}
return*this;
}
}

