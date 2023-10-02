#include "../headers/Edge.h"

using namespace std;

//* Constructor and Destructor -------------------------------------------------------------
Edge::Edge(int target_id){
    this->target_id = target_id;
    this->next_edge = nullptr;
}

Edge::~Edge(){
    if (this->next_edge != nullptr){
        delete this->next_edge;
        this->next_edge = nullptr;
    }
}

//* Other Functions ------------------------------------------------------------------------

