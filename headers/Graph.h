#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"

using namespace std;

class Graph {

    public:
        //* Atributes ---------------------------------------------------------------
        int order;         //~ Ordem do grafo (total de nós);
        
        Node *first_node;  //~ Primeiro nó do grafo;
        Node *last_node;   //~ Último nó do grafo;

        //* Functions ---------------------------------------------------------------
        Graph(int order);  //~ Constructor;
        ~Graph();          //~ Destructor;

        Node *getNode(int id);                                 //~ Retorna um nó pelo seu id;
        void insertNode(int id);                               //~ Insere novo nó;
        void insertEdge(int id, int target_id, float weight);  //~ Insere nova aresta;
        void removeNode(int id);                               //~ Remove nó pelo seu id;
        bool searchNode(int id);                               //~ Verifica se nó existe;
};



#endif