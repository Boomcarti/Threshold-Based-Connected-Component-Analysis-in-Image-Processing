#ifndef imageProcessor_
#define imageProcessor_

#include <iostream>
#include <stack>
#include <string>
#include <memory>
#include <vector>
#include "ConnectedComponent.h"
#include <set>

typedef bool boolean;
namespace MGWTAD001{ // in namespace
    class PGMimageProcessor{
      
      

        public: 
        //std::vector<ConnectedComponent>Com;
        
        unsigned char threshold;
        int imageRows;
        int imageCols;
        PGMimageProcessor(void);
        unsigned char **fullimage;
        Pixel **grid;
        int minValidSize;
        boolean componetsextracted=0;
        unsigned char * binarydataoneD;
        void readinImage(std::string filename);
        int bNumComponents(Pixel ** &grid);
        int wNumComponents(Pixel ** &grid);
        int wsearch(Pixel** &grid,int i,int j,std::vector<Pixel> &Pixels);
        int bsearch(Pixel** &grid,int i, int j, std::vector<Pixel> &pixels);
      

      //write a porper function to determinebackground
        int maxValidSize;
       
        
        void compBoundary(ConnectedComponent &connectedComponent);
        
        boolean blackback;
     
     std::multiset<std::shared_ptr<ConnectedComponent>> Components;
    
           PGMimageProcessor( const PGMimageProcessor& other );
        PGMimageProcessor(PGMimageProcessor && other);
      PGMimageProcessor & operator=( const PGMimageProcessor & other);
       PGMimageProcessor & operator=(PGMimageProcessor && other);
            ~PGMimageProcessor();
        int extractComponents(unsigned char threshold, int minValidSize);
        int getComponentCount(void) const;
        int getLargestSize(void) const;
        int getSmallestSize(void) const;
        void printComponentData(const ConnectedComponent & theComponent) const;
        bool writeComponents(const std::string & outFileName);
        int FilterComponentsBySize(std::vector<ConnectedComponent> &Comps,int minValidSize,int maxValidSize);
        bool compareComponents (const ConnectedComponent & lhs,const ConnectedComponent & rhs);
        void findBoundary(ConnectedComponent &connectedComponent);
}; 
} // end namespace
#endif