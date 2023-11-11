#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "ConnectedComponent.h"
#include "ConnectedComponent.cpp"
#include "PGMimageProcessor.cpp"
#include "PGMimageProcessor.h"

TEST_CASE("Connected Component Unit Tests"){
MGWTAD001::PGMimageProcessor imgps;
std::string filename ="chess.pgm";
imgps.threshold=std::stoi("180");
imgps.minValidSize=std::stoi("10");
imgps.maxValidSize=std::stoi("10000");
imgps.readinImage(filename);
imgps.extractComponents(imgps.threshold,imgps.minValidSize);
for (auto a=imgps.Components.begin(); a!=imgps.Components.end(); ++a){
   imgps.compBoundary((*(*(a)).get()));}

    SECTION("Default Constructor"){
        MGWTAD001::ConnectedComponent compo;
        REQUIRE(compo.numberofpixels==0);
        REQUIRE(compo.componentid==0);
        REQUIRE(compo.Pixels.size()==0);
    }
    SECTION("Copy Constructor"){
        MGWTAD001::ConnectedComponent compo;
        compo.numberofpixels=6000;
        compo.componentid=34;

        MGWTAD001::ConnectedComponent other(compo);
        REQUIRE(other.numberofpixels==6000);
        REQUIRE(other.componentid==34);
        REQUIRE(other.Pixels.size()==0);
}
SECTION("Move Constructor"){
        MGWTAD001::ConnectedComponent compo;
        compo.numberofpixels=6000;
        compo.componentid=34;

        MGWTAD001::ConnectedComponent other(std::move(compo));
        REQUIRE(other.numberofpixels==6000);
        REQUIRE(other.componentid==34);
        REQUIRE(other.Pixels.size()==0);
        REQUIRE(compo.numberofpixels==0);
        REQUIRE(compo.componentid==0);
        REQUIRE(compo.Pixels.size()==0);
}
SECTION("Copy Assingment Constructor"){
 MGWTAD001::ConnectedComponent compo;
        compo.numberofpixels=6000;
        compo.componentid=34;
        MGWTAD001::ConnectedComponent other;
        other=compo;
        REQUIRE(other.numberofpixels==6000);
        REQUIRE(other.componentid==34);
        REQUIRE(other.Pixels.size()==0);
}
SECTION("Move Assignement Operator"){
    
     MGWTAD001::ConnectedComponent compo;
        compo.numberofpixels=6000;
        compo.componentid=34;
        MGWTAD001::ConnectedComponent other;
        other=std::move(compo);
        REQUIRE(other.numberofpixels==6000);
        REQUIRE(other.componentid==34);
        REQUIRE(other.Pixels.size()==0);
        REQUIRE(compo.numberofpixels==0);
        REQUIRE(compo.componentid==0);
        REQUIRE(compo.Pixels.size()==0);
        
}
SECTION("addBoundary and AddBoundary"){
auto i = imgps.Components.begin();

 int f = int((*(i)).get()->getBoundary());
 (*(i)).get()->addBoundary();
 int ans =int((*(i)).get()->getBoundary());

 REQUIRE(f==(ans-1));
}

}
TEST_CASE("PGMimageProcessor Methods"){
MGWTAD001::PGMimageProcessor imgps;
std::string filename ="chess.pgm";
imgps.threshold=std::stoi("180");
imgps.minValidSize=std::stoi("10");
imgps.maxValidSize=std::stoi("10000");
imgps.readinImage(filename);
imgps.extractComponents(imgps.threshold,imgps.minValidSize);
int x=0;
for (auto a=imgps.Components.begin(); a!=imgps.Components.end(); ++a){
   imgps.compBoundary((*(*(a)).get()));}


SECTION("COMPBOUNDARY METHOD"){
int y = int((*(imgps.Components.begin())).get()->getBoundary());
REQUIRE(y>x);
//checking to see if the comp boundary method does actually increase the number of boundary elements
}
SECTION("getComponentCount"){
    REQUIRE(imgps.getComponentCount()==imgps.Components.size());
}
SECTION("getLargestSize"){
    int max=0;
for (auto i=imgps.Components.begin(); i!=imgps.Components.end(); ++i){
        int size = (*(i)).get()->numberofpixels;
        if(size>max){
           max=size;
        }
    }

    REQUIRE(imgps.getLargestSize()==max);
}
SECTION("getSmallestSize"){
    int min=999999;
    for (auto i=imgps.Components.begin(); i!=imgps.Components.end(); ++i){
        int size = (*(i)).get()->numberofpixels;
        if(size<min){
           min=size;
        }
    }
    REQUIRE(imgps.getSmallestSize()==min);

}
SECTION("compareComponnents"){
    MGWTAD001::ConnectedComponent rhs =*(*(imgps.Components.begin())).get();
     auto i = imgps.Components.begin();
     ++i;
    MGWTAD001::ConnectedComponent lhs= *(*(i)).get();
          REQUIRE(imgps.compareComponents(rhs,lhs)==true);
}
}