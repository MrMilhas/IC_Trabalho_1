#ifndef EDGE_H
#define EDGE_H

using namespace std;

class Edge{
    public:
        //* Atributes ---------------------------------------------------------------
        int target_id;    //~ Id do nó alvo;
        float dist;       //~ Peso da aresta (distância entre os nós);
        
        Edge* next_edge;  //~ Próxima aresta do nó;

        //* Functions ---------------------------------------------------------------
        Edge(int target_id);  //~ Constructor;
        ~Edge();              //~ Destructor;
}; 

#endif