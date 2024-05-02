#ifndef PATHVERTEXINFO_H
#define PATHVERTEXINFO_H

#include <limits>
#include <vector>
#include "Graph.h"

class PathVertexInfo {
public:
   Vertex* vertex;
   double distance;
   Vertex* predecessor;
   
   PathVertexInfo(Vertex* vertex = nullptr) {
      this->vertex = vertex;
      distance = std::numeric_limits<double>::infinity();
      predecessor = nullptr;
   }

   // Utility function to remove and return the PathVertexInfo from the vector 
   // that has the minimum distance
   static PathVertexInfo* RemoveMin(std::vector<PathVertexInfo*>& items) {
      if (0 == items.size()) {
         return nullptr;
      }

      int minIndex = 0;
      for (int i = 1; i < items.size(); i++) {
         if (items[i]->distance < items[minIndex]->distance) {
            minIndex = i;
         }
      }
      
      // Get the info with the minimum distance
      PathVertexInfo* infoWithMinDistance = items[minIndex];
      
      // Remove the info with the minimum distance
      items.erase(items.begin() + minIndex);
      
      return infoWithMinDistance;
   }
};

#endif