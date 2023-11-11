#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <set>
#include <queue>
#include <algorithm>    // std::sort
#include "ConnectedComponent.h"
#include "PGMimageProcessor.h"

typedef bool boolean;

namespace MGWTAD001{
    std::vector<ConnectedComponent> Comps;
    ///constrcutor for class, void
    PGMimageProcessor::PGMimageProcessor(void){
        threshold=0;
        imageRows=0;
        imageCols=0;
        minValidSize=1;
        
       
    } 
    //dealloaction of memory in destrucor
    PGMimageProcessor::~PGMimageProcessor(){
        delete[] fullimage;
delete[] grid;
        
        
    }

//copy constrcutor
          PGMimageProcessor::PGMimageProcessor( const PGMimageProcessor& other ){
threshold=other.threshold;
imageRows=other.imageRows;
imageCols=other.imageCols;
for(int i =0;i<imageRows;i++){
    for(int j=0;j<imageCols;j++){
        fullimage[i][j]=other.fullimage[i][j];
    }
}
for(int i =0;i<imageRows;i++){
    for(int j=0;j<imageCols;j++){
        grid[i][j]=other.grid[i][j];
    }
}
for(int i=0;i<imageCols*imageRows;i++){
    binarydataoneD[i]=other.binarydataoneD[i];
}

Components=other.Components;
       }
//move construcor
PGMimageProcessor::PGMimageProcessor(PGMimageProcessor && other){
threshold=std::move(other.threshold);
imageRows=std::move(other.imageRows);
imageCols=std::move(other.imageCols);
for(int i =0;i<imageRows;i++){
    for(int j=0;j<imageCols;j++){
        fullimage[i][j]=other.fullimage[i][j];
    }
}
for(int i =0;i<imageRows;i++){
    for(int j=0;j<imageCols;j++){
        grid[i][j]=other.grid[i][j];
    }
}
for(int i=0;i<imageCols*imageRows;i++){
    binarydataoneD[i]=other.binarydataoneD[i];
}
       
delete[]other.grid;
delete[]other.fullimage;
delete[] other.binarydataoneD;
Components=other.Components;
other.Components.clear();

}
//copy asisngment
PGMimageProcessor& PGMimageProcessor::operator=( const PGMimageProcessor & other){
if(this!=&other){

threshold=other.threshold;
imageRows=other.imageRows;
imageCols=other.imageCols;
for(int i =0;i<imageRows;i++){
    for(int j=0;j<imageCols;j++){
        fullimage[i][j]=other.fullimage[i][j];
    }
}
for(int i =0;i<imageRows;i++){
    for(int j=0;j<imageCols;j++){
        grid[i][j]=other.grid[i][j];
    }
}
for(int i=0;i<imageCols*imageRows;i++){
    binarydataoneD[i]=other.binarydataoneD[i];
}



Components=other.Components;
}

return*this;
} 
//move assingment
 PGMimageProcessor & PGMimageProcessor::operator=(PGMimageProcessor && other){
if(this!=&other){
threshold=std::move(other.threshold);
imageRows=std::move(other.imageRows);
imageCols=std::move(other.imageCols);
for(int i =0;i<imageRows;i++){
    for(int j=0;j<imageCols;j++){
        fullimage[i][j]=other.fullimage[i][j];
    }
}
for(int i =0;i<imageRows;i++){
    for(int j=0;j<imageCols;j++){
        grid[i][j]=other.grid[i][j];
    }
}
for(int i=0;i<imageCols*imageRows;i++){
    binarydataoneD[i]=other.binarydataoneD[i];
}
    //dealloaction of data from obeject that was moved from   
delete[]other.grid;
delete[]other.fullimage;
delete[] other.binarydataoneD;
Components=other.Components;
other.Components.clear();
}
return*this;
 }

    //extracts components and puts them into a set, depending on the colour of background
   int PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize){
       if(blackback){
       return wNumComponents(grid);}
       return bNumComponents(grid);
       
        }

      
         //filters array and removes the componets whch do not fit size criteria
        int PGMimageProcessor::FilterComponentsBySize(std::vector<ConnectedComponent> &Comps, int minValidSize, int maxValidSize){
            
            while(true){
                boolean wrongorder=0;
           for(int i=0;i<Comps.size()-1;i++){
               if(Comps.at(i).numberofpixels>Comps.at(i+1).numberofpixels){
                   
                   ConnectedComponent temp=Comps.at(i);
                   
                   Comps.at(i)=Comps.at(i+1);
                   Comps.at(i+1)=temp;
                   }
          
           for(int i =0;i<Comps.size()-1;i++){
               if(Comps.at(i).numberofpixels>Comps.at(i+1).numberofpixels){
                   wrongorder=1;
               }
           }
            
               }
          if(wrongorder==0){
              break;
          }
        
           }
           
           while((Comps.at(0).numberofpixels<minValidSize)||(Comps.at(Comps.size()-1).numberofpixels>maxValidSize)){
          if((Comps.at(0).numberofpixels<minValidSize)){
              Comps.erase(Comps.begin(),Comps.begin()+1);
          }
             
              
           
          if((Comps.at(Comps.size()-1).numberofpixels>maxValidSize)){
              
              Comps.pop_back();
          }
           }

          for(int i=0;i<Comps.size();i++){
               std::shared_ptr<ConnectedComponent> ptr;
                ptr=std::make_shared<ConnectedComponent>(Comps.at(i));
                Components.insert(ptr);


          }return 1;
        }
//loads componts to temporay vector //perfoms the BFS search
int PGMimageProcessor::bNumComponents(Pixel ** &grid){
        if(grid==nullptr){
            return 0;
        }
        int id=1;
        int numComps = 0;
        for(int i=0;i<imageRows;i++){
            for(int j=0;j<imageCols;j++){
                if(grid[i][j].pixel==0){
                   
                    ConnectedComponent connectedComponent;
                 
                    numComps=numComps+bsearch(grid,i,j,connectedComponent.Pixels);

                    connectedComponent.componentid=id;
                    connectedComponent.numberofpixels=connectedComponent.Pixels.size();
                    id++;
                   
                   Comps.push_back(connectedComponent);
                   
            }
            }
        }

              
     
   FilterComponentsBySize(Comps,minValidSize,maxValidSize);
   
   
return Components.size();
    }
//peforms bfs search, flood fill when it finds a pixel that fits the criteria
    int PGMimageProcessor::wNumComponents(Pixel ** &grid){
        if(grid==nullptr){
            return 0;
        }
        int id=1;
        int numComps = 0;
        for(int i=0;i<imageRows;i++){
            for(int j=0;j<imageCols;j++){
                if(grid[i][j].pixel==255){
                   
                    ConnectedComponent connectedComponent;
                    //std::cout<<"creates comp well"<<std::endl;
                   
                    numComps=numComps+wsearch(grid,i,j,connectedComponent.Pixels);

                    connectedComponent.componentid=id;
                    connectedComponent.numberofpixels=connectedComponent.Pixels.size();
                    id++;
                   
                   Comps.push_back(connectedComponent);
                   
            }
            }
        }

              
     
   FilterComponentsBySize(Comps,minValidSize,maxValidSize);
   
   
return Components.size();
    }

  int PGMimageProcessor::wsearch(Pixel** &grid,int i, int j, std::vector<Pixel> &pixels){
if((i<0)||(i>imageRows-1)||(j<0)||(j>imageCols-1)||(int(grid[i][j].pixel)==0)){
    return 0;
    }
    Pixel px;
    px.pixel=grid[i][j].pixel;
    px.xcord=j;
    px.ycord=i;
    px.pixel=255;
    pixels.push_back(px);
    grid[i][j].pixel=0;
    wsearch(grid,i+1,j,pixels);
    wsearch(grid,i-1,j,pixels);
    wsearch(grid,i,j+1,pixels);
    wsearch(grid,i,j-1,pixels);
    return 1;
  }

  int PGMimageProcessor::bsearch(Pixel** &grid,int i, int j, std::vector<Pixel> &pixels){
if((i<0)||(i>imageRows-1)||(j<0)||(j>imageCols-1)||(int(grid[i][j].pixel)==255)){
    return 0;
    }
    Pixel px;
    px.pixel=grid[i][j].pixel;
    px.xcord=j;
    px.ycord=i;
    px.pixel=0;
    pixels.push_back(px);
    grid[i][j].pixel=255;
    bsearch(grid,i+1,j,pixels);
    bsearch(grid,i-1,j,pixels);
    bsearch(grid,i,j+1,pixels);
    bsearch(grid,i,j-1,pixels);
    return 1;
  }







//compares wto components and returns 1 is rhs> lhs
bool PGMimageProcessor::compareComponents (const ConnectedComponent & lhs,
const ConnectedComponent & rhs)
{

if(lhs.numberofpixels<rhs.numberofpixels){
    return true;
}
return false;
}


//returns nuumber of compoents
int PGMimageProcessor::getComponentCount(void) const{
    return Components.size();}
//returns largest size of a single component
int PGMimageProcessor::getLargestSize(void) const{
   
    int max=0;
    
    for (auto i=Components.begin(); i!=Components.end(); ++i){
        int size = (*(i)).get()->numberofpixels;
        if(size>max){
           max=size;
        }
    }
    return max;
    }

//returnns smallest size of compnent
int PGMimageProcessor::getSmallestSize(void) const{
    int min=99999;
    
    for (auto i=Components.begin(); i!=Components.end(); ++i){
        int size = (*(i)).get()->numberofpixels;
        if(size<min){
           min=size;
        }
    }
    return min;
}

void PGMimageProcessor::printComponentData(const ConnectedComponent & theComponent) const{
    if(theComponent.getBoundary()>=0){
    std::cout<<"Component ID: "<<theComponent.componentid<<"\n"<<"Number Of Pixels: "<<theComponent.numberofpixels<<"\n"<<"Boundary Pixels: "<<theComponent.getBoundary()<<'\n'<<std::endl;
    }
    else{
        long coomp=(theComponent.getBoundary()*-1);
        std::cout<<"Component ID: "<<theComponent.componentid<<"\n"<<"Number Of Pixels: "<<theComponent.numberofpixels<<"\n"<<"Boundary Pixels: "<<coomp<<'\n'<<std::endl;
    }
}
//finds the number of boundary pixels ina component
void PGMimageProcessor::compBoundary(ConnectedComponent &component){
    int boundary=0;
    
     
    for(int i=0;i<component.Pixels.size();i++){
      //  if((component.Pixels[i].xcord!=0)&&(component.Pixels[i].xcord!=imageCols-1)&&(component.Pixels[i].ycord!=0)&&(component.Pixels[i].ycord!=imageRows-1)){
           if(blackback){
           if((int(fullimage[component.Pixels[i].ycord][component.Pixels[i].xcord+1])==0)||((int(fullimage[component.Pixels[i].ycord][component.Pixels[i].xcord-1])==0))||(int(fullimage[component.Pixels[i].ycord+1][component.Pixels[i].xcord])==0)||(int(fullimage[component.Pixels[i].ycord-1][component.Pixels[i].xcord])==0)){
               component.addBoundary();}
           }
           else{
                if((int(fullimage[component.Pixels[i].ycord][component.Pixels[i].xcord+1])==255)||((int(fullimage[component.Pixels[i].ycord][component.Pixels[i].xcord-1])==255))||(int(fullimage[component.Pixels[i].ycord+1][component.Pixels[i].xcord])==255)||(int(fullimage[component.Pixels[i].ycord-1][component.Pixels[i].xcord])==255)){              
               component.addBoundary();

           
        }
    }
    }
}




//reads in image and makes bits either 0s or 255s
    void PGMimageProcessor::readinImage(std::string filename){
         boolean rfile=false;
    std::ifstream infile;
    int maxIntensity=0;
    int rows;
    int cols;
    infile.open(filename,std::ios::binary);
    std::string inputLine="";
    std::vector<int> flags;
    int numChars=0;
    if(infile.is_open()){
        while(getline(infile,inputLine)){
            if((inputLine=="P5")&&(flags.size()==0)){
            rfile=true;
            numChars=numChars+inputLine.length();
            flags.push_back(1);
        }
        else if((inputLine[0]!='#')&&(rfile)&&(inputLine!="255") &&(flags.size()==1)){
            std::istringstream iss (inputLine);
            while(!iss.eof()) {

                iss>> cols>>std::ws>>rows;
            }
            numChars=numChars+inputLine.length();
            flags.push_back(1);
        }
        else if(inputLine=="255" &&rfile&&flags.size()==2){

            maxIntensity =atoi(inputLine.c_str()); //
            numChars=numChars+inputLine.length();
            flags.push_back(1);
        }
        else if(inputLine[0]=='#'){
            numChars=numChars+inputLine.length();
        }
        else if(flags.size()==3){
            int numPixels = cols*rows;
            binarydataoneD=new unsigned char[numPixels];
            infile.seekg(numChars+3,std::ios::beg);
            int size=infile.tellg();
            infile.read(reinterpret_cast<char *> (binarydataoneD), (numPixels)*sizeof(unsigned char));

            if(infile){
                std::cout<<"File has been read and image is now being processed.."<<std::endl;
            }
            else{std::cout<<"Error at in reading in image";}


            
            //std::cout<<"Done"<<std::endl;
            break;
        }


        }





    }
    fullimage =new unsigned char*[rows];
    grid= new Pixel*[rows];
    //std::cout<<cols<<" "<<rows<<std::endl;
    imageRows=rows; 
    std::cout<<"length "<<rows<<" width "<<cols<<std::endl;
    imageCols=cols;
    int pixelcount=0;
    for(int i=0;i<rows;i++){
        fullimage[i]=new unsigned char[cols];
        grid[i]=new Pixel[cols];
       
        for(int j=0;j<cols;j++){
            //low is darks
            if((int)binarydataoneD[i*cols+j]<threshold){
            fullimage[i][j]=0;}
            else{
                fullimage[i][j]=255;
            }
            Pixel px;
            px.checked=false;
            if(int(binarydataoneD[i*cols+j])<threshold){
            px.pixel=0;}
            else{
                px.pixel=255;
            }
            px.ycord=i;
            px.xcord=j;
        
            grid[i][j]=px;
            pixelcount++;
        }

    }
    int black=0;
    int white=0;
    for(int i=0;i<imageRows;i++){
        for(int j=0;j<imageCols;j++){
            if(int(grid[i][j].pixel)==255){
                white++;
            }
            if(int(grid[i][j].pixel)==0){
                black++;
            }


        }
    }
    if(white>black){
        std::cout<<"White Background"<<std::endl;
        blackback=0;
    }
    else{
        std::cout<<"Black Background"<<std::endl;
        blackback=1;
    }
    delete [] binarydataoneD;
    std::cout<<"Pixel count "<<pixelcount<<std::endl;
    }
    bool PGMimageProcessor::writeComponents(const std::string & outFileName){
//writes componets on a few file           

  unsigned char ** frame= new unsigned char*[imageRows*imageCols];
  for(int i=0;i<imageRows;i++){
        frame[i]=new unsigned char[imageCols];
        //std::cout<<"row "<<i<<" /"<<rows<<std::endl;
        for(int j=0;j<imageCols;j++){
            frame[i][j]=0;

        }

  }
         for(int i=0;i<Components.size();i++){
             //replace with iterator
     for (auto a=Components.begin(); a!=Components.end(); ++a){
        std::vector<Pixel> list = (*(a)).get()->Pixels;
        for(int o=0;o<list.size();o++ ){
        frame[list.at(o).ycord][list.at(o).xcord]=255;
        }  }        }

       unsigned char * buffer = new unsigned char[imageCols*imageCols];
             for(int i=0;i<imageRows;i++){
        for(int j=0;j<imageCols;j++){
            
           
            buffer[i*imageCols+j] =frame[i][j];
        }
    }

std::ofstream infile(outFileName+".pgm",std::ios::binary);
        int n=imageCols*imageCols;
          infile<<"P5\n";
    infile<<imageCols<<" "<<imageRows<<"\n";
    infile<<255<<"\n"<<"\n";
infile.write( reinterpret_cast<char *>(buffer),(n)*sizeof(unsigned char));
    
           
            

delete [] buffer;
delete [] frame;
if(infile){
        return true;
        infile.close();
    }
    return false;

    
    }

}








    


















