#ifndef ConnectedComponent_
#define ConnectedComponent_
#include <iostream>
#include <utility>
#include <string>
#include <vector>
//#include <boost/asio.hpp>
#include "ConnectedComponent.h"

typedef bool boolean;
namespace MGWTAD001{
  
   struct Pixel{
    unsigned char pixel;
    boolean checked;
    int xcord;
    int ycord;
};
    class ConnectedComponent {
      private:
       int boundaryPixels;

        public: 
        void addBoundary();
        
        
        int numberofpixels;
        int componentid;
       std::vector<MGWTAD001::Pixel> Pixels;
        ConnectedComponent(void);
      ~ConnectedComponent();
       
      int getBoundary  () const;
      ConnectedComponent( const ConnectedComponent& other );
        ConnectedComponent(ConnectedComponent && other);
       ConnectedComponent & operator=( const ConnectedComponent & other);
        ConnectedComponent & operator=(ConnectedComponent && other);
        
        
        
}; 
} // end namespace
#endif









