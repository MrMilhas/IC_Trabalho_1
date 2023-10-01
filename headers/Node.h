#ifndef NODE_H
#define NODE_H

#include "Edge.h"

using namespace std;

class Node {
    public:
        //* Atributes ---------------------------------------------------------------
        int id;            //~ Id do nó;
        char type;         //~ Tipo do nó (H = Hotel, N = Nó);
        int points;        //~ Pontuação do nó (Se for um hotel, points = 0);
        
        int pos_x;         //~ Posição X do nó;
        int pos_y;         //~ Posição Y do nó;
    
        Edge *first_edge;  //~ Primeira aresta;
        Edge *last_edge;   //~ Última aresta;
        Node *next_node;   //~ Próximo nó; 

        //* Functions ---------------------------------------------------------------
        Node (int id, char type, int points, int x, int y);  //~ Constructor;
        ~Node ();                                            //~ Destructor;

        bool search_edge(int target_id);            //~ Verifica se a aresta já existe;
        void insert_edge(int target_id, float dist);            //~ Insere nova aresta;
        int removeEdge(int id, Node* target_node);  //~ Remove aresta específica;
        void remove_all_edges();                    //~ Remove todas as arestas;
        Edge* get_edge(int target_id);              //~ Retorna aresta alvo;
};

#endif