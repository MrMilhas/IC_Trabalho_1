#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include <vector>
#include <set>
#include <string>

using namespace std;

/**
 * @brief Estrutura da partícula;
 *
 */
struct particle
{
    vector<vector<int>> atual_position;                 //& Posição atual da partícula;
    vector<vector<int>> best_local_position;            //& Melhor posição da partícula;
    vector<vector<int>> best_global_position;           //& Melhor posição global;
    vector<vector<pair<string, pair<int, int>>>> speed; //& Velocidade da partícula;

    float points;             //& Pontuação atual da partícula;
    float best_local_points;  //& Melhor pontuação da partícula;
    float best_global_points; //& Melhor pontuação global;
};

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
    vector<vector<int>> createNeighborhood(vector<int> solution, vector<pair<int, double>> cand, vector<int> hotels);
    float get_total_dist(vector<int> solution);
    float get_total_points(vector<int> solution);
    float get_ls_points(vector<int> solution);

    vector<particle> initialize_particles(int n_particles);
    float calculate_points(particle p);
    vector<vector<pair<string, pair<int, int>>>> subtract_positions(vector<vector<int>> p1, vector<vector<int>> p2);
    vector<vector<pair<string, pair<int, int>>>> calculate_speed(particle p, float w, float c1, float c2);
    vector<vector<int>> calculate_position(particle p);

    vector<vector<int>> heuristic();                                          //~ Função heurística;
    vector<vector<int>> randomizedHeuristic(float alfa, int numIt, int seed); //~ Função heurística randomizada;
    vector<vector<int>> simple_grasp();                                       //~ Grasp simples;
    vector<vector<int>> particle_cloud(int max_it, int n_particles, float w, float c1, float c2);
    vector<pair<string, pair<int, int>>> create_rand_moves(const vector<vector<int>> &current_solution);
    int getRandomNode();
    int getRandomHotelNode(vector<vector<int>> current_route);
};

#endif