#include <string>
#include <fstream>
#include <iostream>

#include <iostream>


#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "PGMimageProcessor.h"
typedef bool boolean;



int main(int argc, char *argv[])
{
std::cout<<"Welcome to The PGMimageProcessor"<<"\n"<<std::endl;
std::cout<<"Please run program in the following format:\n"<<std::endl;
std::cout<<"findcomp -s <miValidsize> <maxValidSize> -t <threshold>  (-p) (-w) outputfilename INPUTFILE.pgm"<<std::endl;
int sindex ;
int tindex;
int windex;
int pindex;
for(int i=0; i<argc;i++){
    std::string command=argv[i];
    if(command=="-s"){
        sindex=i;
    }
    if(command=="-t"){
        tindex=i;
    }
    if(command=="-p"){
        pindex=i;
    }
    if(command=="-w"){
        windex=i;
    }
    }


std::string filename =argv[argc-1];
MGWTAD001::PGMimageProcessor imgps;
imgps.threshold=std::stoi(argv[tindex+1]);
imgps.minValidSize=std::stoi(argv[sindex+1]);
imgps.maxValidSize=std::stoi(argv[sindex+2]);
imgps.readinImage(filename);
std::cout<<"File Read in"<<std::endl;
//std::cout<<"Number of Components raw"<<imgps.NumIslands(imgps.grid)<<std::endl;
std::cout<<"Number of Components after filtering : "<<imgps.extractComponents(imgps.threshold,imgps.minValidSize)<<std::endl;

//comments!!!!

if((pindex!=0)&&(sindex!=0)&&(tindex!=0)){
    std::cout<<" "<<std::endl;
            std::cout<<"The Components:..."<<std::endl;
            
            int s=0;
        for (auto a=imgps.Components.begin(); a!=imgps.Components.end(); ++a){
            
            imgps.compBoundary((*(*(a)).get()));
           
   
        imgps.printComponentData(*(*(a)).get());

        s++;}}
if((windex!=0)&&(sindex!=0)&&(tindex!=0)){
    imgps.writeComponents(argv[windex+1]);
}

}