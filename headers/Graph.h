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

        Node *get_node(int id);                                         //~ Retorna um nó pelo seu id;
        void insert_node(int id, char type, int points, int x, int y);  //~ Insere novo nó;
        void insert_edge(int id, int target_id, float dist);          //~ Insere nova aresta;
        void remove_node(int id);                                       //~ Remove nó pelo seu id;
        bool search_node(int id);                                       //~ Verifica se nó existe;
};



#endif