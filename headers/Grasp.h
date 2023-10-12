#include "./Node.h"
#include "./Graph.h"
#include "./Edge.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <cstring>
#include <math.h>
#include <utility>

using namespace std;

vector<pair<int, float>> initial_solution(Graph* graph){
    vector<pair<int, float>> aux;
    pair<int, float> par(graph->get_node(0)->id, 0.0);
    aux.push_back(par);
    return aux;
}

vector<pair<int, float>> select_possible_moves(int id){

}

vector<int> GRASP(Graph* graph, int iter, float alpha){
    vector<pair<int, float>> s0 = initital_solution(graph);  //~ Definindo solução inicial;
    vector<pair<int, float>> possible_moves;                 //~ Definindo vetor de movimentos possíveis;
    vector<pair<int, float>> restrict_moves;                 //~ Definindo vetor de melhores movimentos possíveis;

    int count_days = 0;  //~ Inicializando contador de dias;
    int count_dist = 0;  //~ Inicializando contador de distância;
    int last_node = 0;   //~ Id do último nó inserido na solução;

    //* Etapa construtiva -------------------------------------------
    for(int i=0; i<iter; i++){
        possible_moves = select_possible_moves(last_node);
    }

    //* Busca local -------------------------------------------------
}
