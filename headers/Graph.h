#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include <vector>
#include <set>

using namespace std;

class Graph
{

public:
    //* Atributes ---------------------------------------------------------------
    int order;        //~ Ordem do grafo (total de nós);
    int h = 0;        //~ Número de hotéis extras;
    int d = 0;        //~ Número de viagens;
    int tMax = 0;     //~ Duração máxima do passeio;
    vector<float> td; //~ Vetor contendo a duração de cada viagem;

    Node *first_node; //~ Primeiro nó do grafo;
    Node *last_node;  //~ Último nó do grafo;

    //* Functions ---------------------------------------------------------------
    Graph(int order, int h, int d, int tMax, vector<float> td); //~ Constructor;
    ~Graph();                                                   //~ Destructor;

    Node *get_node(int id);                                        //~ Retorna um nó pelo seu id;
    void insert_node(int id, char type, int points, int x, int y); //~ Insere novo nó;
    void insert_edge(int id, int target_id, float dist);           //~ Insere nova aresta;
    void remove_node(int id);                                      //~ Remove nó pelo seu id;
    bool search_node(int id);                                      //~ Verifica se nó existe;

    vector<pair<int, double>> createCandidates();                                                  //~ Cria conjunto de candidatos;
    vector<int> createHotelsCandidates();                                                          //~ Cria conjunto de candidatos de hoteis;
    vector<pair<int, double>> updateCandidates(vector<pair<int, double>> *candidates, Node *node); //~ Atualiza conjunto de candidatos;
    vector<vector<int>> heuristic();                                                               //~ Função heurística;
    vector<vector<int>> randomizedHeuristic(float alfa, int numIt, int seed);                      //~ Função heurística randomizada;
};

#endif