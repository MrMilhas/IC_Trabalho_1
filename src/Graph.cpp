#include "../headers/Graph.h"
#include "../headers/Node.h"
#include "../headers/Edge.h"
#include <iostream>
#include <set>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <cstring>
#include <math.h>
#include <random>

using namespace std;

//* Constructor and Destructor -------------------------------------------------------------
Graph::Graph(int order, int h, int d, int tMax, vector<float> td)
{
    this->order = order;
    this->h = h;
    this->d = d;
    this->tMax = tMax;
    this->td = td;
    this->first_node = nullptr;
    this->last_node = nullptr;
}

Graph::~Graph()
{
    Node *next_node = this->first_node;

    while (next_node != nullptr)
    {
        next_node->remove_all_edges();
        Node *aux_node = next_node->next_node;
        delete next_node;
        next_node = aux_node;
    }
}

//* Other Functions ------------------------------------------------------------------------
/**
 * @brief         Função utilizada para retornar um nó pelo seu id;
 *
 * @param id      Id do nó que deseja retornar;
 * @return Node*  Retorna o ponteiro para o nó;
 */
Node *Graph::get_node(int id)
{
    Node *node = first_node;

    while (node != nullptr)
    {
        if (node->id == id)
            return node;
        node = node->next_node;
    }
    return nullptr;
}

/**
 * @brief Função utilizada para inserir um novo nó no grafo;
 *
 * @param id      Id do nó a ser inserido;
 * @param type    Tipo do nó (Hotel ou nó padrão);
 * @param points  Pontuação Si do nó;
 * @param x       Posição X do nó;
 * @param y       Posição Y do nó;
 */
void Graph::insert_node(int id, char type, int points, int x, int y)
{
    if (first_node != nullptr)
    {
        Node *new_node = new Node(id, type, points, x, y);
        last_node->next_node = new_node;
        last_node = new_node;
    }
    else
    {
        Node *new_node = new Node(id, type, points, x, y);
        first_node = new_node;
        last_node = new_node;
    }
}

/**
 * @brief            Função utilizada para inserir uma nova aresta no grafo;
 *
 * @param id         Id da aresta a ser inserida;
 * @param target_id  Id do nó alvo da aresta;
 * @param weight     Peso da aresta a ser inserida (distância entre os nós);
 */
void Graph::insert_edge(int id, int target_id, float dist)
{
    Node *node = get_node(id);
    Node *aux = get_node(target_id);

    if (node != nullptr && aux != nullptr)
    {
        if (!node->search_edge(target_id))
        {
            node->insert_edge(target_id, dist);

            if (!aux->search_edge(id))
            {
                aux->insert_edge(id, dist);
            }
        }
    }
}

/**
 * @brief     Função utilizada para remover um nó do grafo pelo seu Id;
 *
 * @param id  Id do nó a ser removido;
 */
void Graph::remove_node(int id)
{
    Node *node = get_node(id);

    if (node == nullptr)
    {
        return;
    }
    else if (node == first_node)
    {
        first_node = node->next_node;
    }
    else
    {
        Node *aux = first_node;

        while (aux->next_node != node)
        {
            aux = aux->next_node;
        }

        if (node == last_node)
        {
            last_node = aux;
        }

        aux->next_node = node->next_node;
    }
    delete node;
}

/**
 * @brief         Função utilizda para procurar uma nó no grafo pelo seu Id;
 *
 * @param id      Id do nó a ser procurado no grafo;
 * @return true   Retorna verdadeiro se encontrar o nó;
 * @return false  Retorna falso se não encontrar o nó;
 */
bool Graph::search_node(int id)
{
    Node *node = get_node(id);

    if (node == nullptr)
    {
        return false;
    }
    else
    {
        return true;
    }
}

//* GRASP and Local Search ========================================================================================
//* ===============================================================================================================

/**
 * @brief         Função utilizada para criar o vetor de candidatos do problema;
 *
 * @return vector<pair<int, double>>  Retorna o conjunto de pontos candidatos, com o id do nó e a razão entre os pontos e a distância;
 */
vector<pair<int, double>> Graph::createCandidates()
{
    vector<pair<int, double>> candidates;

    Node *node = first_node->next_node;

    while (node != nullptr)
    {
        if (node->type == 'N')
        {
            candidates.push_back(make_pair(node->id, ((node->points / (node->get_edge(first_node->id)->dist)))));
        }
        node = node->next_node;
    }

    // Ordenar o vetor pelo segundo elemento
    sort(candidates.begin(), candidates.end(), [](const pair<int, float> &a, const pair<int, float> &b)
         { return a.second > b.second; });

    return candidates;
}

/**
 * @brief         Função utilizada para criar o vetor de candidatos dos hotéis do problema;
 *
 * @return vector<int>  Retorna o conjunto de hotéis candidatos;
 */
vector<int> Graph::createHotelsCandidates()
{
    vector<int> candidates;

    Node *node = first_node;

    for (int i = 0; i < h + 2; i++)
    {
        if (i == 1)
        {
            node = node->next_node;
            continue;
        }
        candidates.push_back(node->id);
        node = node->next_node;
    }

    candidates.push_back(first_node->next_node->id); // O último hotel fica no final do vetor

    return candidates;
}

/**
 * @brief         Função utilizada para atualizar o vetor de candidatos do problema em cada iteração;
 *
 * @param node    Nó que foi inserido na solução;
 * @return vector<pair<int, double>>  Retorna o conjunto de pontos candidatos, com o id do nó e a razão entre os pontos e a distância;
 */
vector<pair<int, double>> Graph::updateCandidates(vector<pair<int, double>> *candidates, Node *node)
{
    vector<pair<int, double>> aux;

    for (int i = 0; i < candidates->size(); i++)
    {
        Node *nodeAux = this->get_node(candidates->at(i).first);
        aux.push_back(make_pair(candidates->at(i).first, (((nodeAux->points) / (nodeAux->get_edge(node->id)->dist)))));
    }

    // Ordenar o vetor pelo segundo elemento
    sort(aux.begin(), aux.end(), [](const pair<int, float> &a, const pair<int, float> &b)
         { return a.second > b.second; });

    return aux;
}

int verify_visited(int id, vector<int> solution)
{
    for (int i = 0; i < solution.size(); i++)
    {
        if (solution[i] == id)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief         Função utilizada para gerar um número aleatório dentro de um intervalo;
 *
 * @param min     Valor mínimo do intervalo;
 * @param max     Valor máximo do intervalo;
 * @return int    Retorna o número aleatório gerado;
 */
int randomRange(int min, int max)
{
    return min + rand() % (max - min + 1);
}

vector<vector<int>> Graph::createNeighborhood(vector<int> solution, vector<pair<int, double>> cand, vector<int> hotels)
{
    vector<vector<int>> neighborhood;
    vector<pair<int, double>> aux_cands = cand;
    vector<int> aux_solution = solution;

    for (int r = 1; r < (aux_solution.size() - 1); r++)
    {
        for (int w = 0; w < cand.size(); w++)
        {
            aux_solution[r] = aux_cands[w].first;
            aux_cands.erase(aux_cands.begin() + w);

            for (int k = 0; k < hotels.size(); k++)
            {
                if ((hotels[k] != 0) && (hotels[k] != 1))
                {
                    aux_solution[aux_solution.size() - 1] = hotels[k];
                    neighborhood.push_back(aux_solution);
                }
            }
            aux_cands = cand;
        }
        aux_solution = solution;
    }
    return neighborhood;
}

float Graph::get_total_dist(vector<int> solution)
{
    float dist = 0;
    for (int i = 0; i < (solution.size() - 2); i++)
    {
        dist += this->get_node(solution[i])->get_edge(solution[i + 1])->dist;
    }
    return dist;
}

float Graph::get_total_points(vector<int> solution)
{
    float pts = 0.0;
    for (int i = 0; i < solution.size() - 1; i++)
    {
        pts += ((this->get_node(solution[i])->points));
    }
    return pts;
}

float Graph::get_ls_points(vector<int> solution)
{
    float points_1 = this->get_total_points(solution);
    float points_2 = -9999999;

    Edge *edge = this->get_node(solution[solution.size() - 1])->first_edge;

    while (edge != nullptr)
    {
        float aux = ((this->get_node(edge->target_id)->points));
        if (aux > points_2)
        {
            points_2 = aux;
        }
        edge = edge->next_edge;
    }
    return points_1 + points_2;
}

/**
 * @brief         Algoritmo randomizado adaptativo, junto com a busca local;
 *
 * @param alfa    Parâmetro de aleatoriedade;
 * @param numIt   Número de iterações;
 * @param seed    Semente para o gerador de números aleatórios;
 */
vector<vector<int>> Graph::randomizedHeuristic(float alfa, int numIt, int seed)
{
    vector<int> visiteds;
    vector<vector<int>> solution;
    vector<vector<int>> bestSolution;
    float bestScore = 0;
    float auxScore = 0;

    int it = 0;

    while (it < numIt)
    {
        vector<pair<int, double>> candidates = this->createCandidates();
        vector<int> hotelsCandidates = this->createHotelsCandidates();
        int pos = randomRange(0, static_cast<int>(candidates.size() - 1) * alfa);

        // if (it == 0)
        //     // cout << "Pos: " << pos << endl;

        int days = this->td.size();

        // Cada dia gera uma solução diferente, a solução final é um conjunto de soluções
        for (int i = 0; i < days; i++)
        {
            vector<int> aux;
            if (solution.size() == 0) // O primeiro dia começa do primeiro hotel
            {
                aux.push_back(hotelsCandidates[0]);
            }
            else
            {
                aux.push_back(solution[i - 1].back()); // Se não for o primeiro dia, os demais começam com o hotel do dia anterior
            }

            float t = 0; // Tempo total da viagem
            int count_index_aux = 0;
            while (t < td[i])
            {
                // Corrigir aqui: Verificar se a solução do dia atual esta vazia ->
                pos = randomRange(0, static_cast<int>(candidates.size() - 1) * alfa);
                aux.push_back(candidates.at(pos).first);
                count_index_aux++;
                t += this->get_node(aux[count_index_aux - 1])->get_edge(aux[count_index_aux])->dist; // Corrigir a contagem de distância;
                auxScore += this->get_node(candidates.at(pos).first)->points;

                if (t > td[i]) // Se o tempo da viagem for maior que o tempo disponível, remover o nó e inserir
                {
                    aux.pop_back();

                    // Buscar o hotel mais próximo
                    float min = 999999999;
                    Node *hotel = nullptr;

                    if (i == days - 1)
                    {
                        aux.push_back(hotelsCandidates.back());
                        break;
                    }
                    else
                    {

                        for (int i = 0; i < hotelsCandidates.size(); i++)
                        {
                            Node *nodeAux = this->get_node(hotelsCandidates[i]);
                            float dist = this->get_node(aux[aux.size() - 1])->get_edge(nodeAux->id)->dist;

                            if (dist < min)
                            {
                                min = dist;
                                hotel = nodeAux;
                            }
                        }
                        aux.push_back(hotel->id);
                    }
                    t = 0;
                    break;
                }
                else
                {
                    candidates.erase(candidates.begin() + pos);
                }
                candidates = this->updateCandidates(&candidates, this->get_node(aux[aux.size() - 1]));
            }
            //* Local Search -------------------------------------------------------------
            if (i < days - 1)
            {
                vector<int> best_aux = aux;
                vector<vector<int>> neighborhood = this->createNeighborhood(aux, candidates, hotelsCandidates);

                float bad_iter = 0;        //~ Contador de iterações que não conseguiram melhorar a solução;
                float max_bad_iter = 1000; //~ Máximo de iterações ruins;
                float k = 0;

                while ((bad_iter < max_bad_iter) && (k < neighborhood.size()))
                {
                    int t_ls = get_total_dist(neighborhood[k]);
                    if (t_ls < td[i])
                    {
                        int best_points = get_ls_points(best_aux); //~ Pontuação da melhor solução atual;
                        int pts = get_ls_points(neighborhood[k]);  //~ Pontuação da solução da iteração atual;

                        if (pts > best_points)
                        {
                            best_aux = neighborhood[k];
                            bad_iter = 0;
                        }
                        else
                        {
                            bad_iter++;
                        }
                    }
                    else
                    {
                        bad_iter++;
                    }
                    k++;
                }
                aux = best_aux;
            }

            t = 0;
            solution.push_back(aux);
        }

        if (auxScore > bestScore)
        {
            bestScore = auxScore;
            bestSolution = solution;
        }

        auxScore = 0;
        solution.clear();
        it++;
    }
    return bestSolution;
}

//* Nuvem de Partículas ===========================================================================================
//* ===============================================================================================================

/**
 * @brief Estrutura da partícula;
 * 
 */
struct particle {
    vector<vector<int>> atual_position;        //& Posição atual da partícula;
    vector<vector<int>> best_local_position;   //& Melhor posição da partícula;
    vector<vector<int>> best_global_position;  //& Melhor posição global;
    vector<vector<pair<int, int>>> speed;      //& Velocidade da partícula;

    float points;              //& Pontuação atual da partícula;
    float best_local_points;   //& Melhor pontuação da partícula;
    float best_global_points;  //& Melhor pontuação global;
};

/**
 * @brief Função para inicializar o conjunto de partículas;
 * 
 * @param n_particles       Número de partículas a serem criadas;
 * @return vector<particle> Retorna o conjunto de partículas;
 */
vector<particle> initialize_particles (int n_particles){
    vector<particle> particles;

    for(int i=0; i<n_particles; i++){
        //^ Rodar um grasp simples (sem busca local) para cada partícula de forma
        //^ a obter a solução inicial de cada uma;
    }

    return particles;
}

/**
 * @brief Função utilizada para calcular a pontuação atual da partícula;
 * 
 * @param p      Partícula p;
 * @return float Retorna a pontuação da partícula p;
 */
float calculate_points (particle p){
    float points;
    
    return points;
}

/**
 * @brief Função para calcular a distância (Hamming) entre duas partículas (p2 - p1);
 * 
 * @param p1                              Partícula base;
 * @param p2                              Partícula alvo;
 * @return vector<vector<pair<int, int>>> Retorna a velocidade necessária para ir de p1 para p2;
 */
vector<vector<pair<int, int>>> subtract_positions (vector<vector<int>> p1, vector<vector<int>> p2){
    vector<vector<pair<int, int>>> speed;

    return speed;
}

/**
 * @brief Função aleatória que definirá se uma componente será usada ou não na iteração atual;
 * 
 * @return int Retorna 1 ou 0;
 */
int rand (){
    int state;
    
    return state;
}

/**
 * @brief Função para calcular a velocidade da partícula;
 * 
 * @param p                               Partícula que irá atualizar sua velocidade;
 * @param w                               Coeficiente de inércia;
 * @param c1                              Componente cognitiva;
 * @param c2                              Componente social;
 * @return vector<vector<pair<int, int>>> Retorna a nova velocidade da partícula;
 */
vector<vector<pair<int, int>>> calculate_speed (particle p, float w, float c1, float c2){
    vector<vector<pair<int, int>>> new_speed;
    
    return new_speed;
}

/**
 * @brief Função utilizada para atualizar a posição da partícula;
 * 
 * @param p                    Partícula;
 * @return vector<vector<int>> Retorna a posição calculada da partícula;
 */
vector<vector<int>> calculate_position (particle p){
    vector<vector<int>> position;
    //^ Otimizar a seleção de hotéis aqui nesta função;
    return position;
}

vector<vector<int>> particle_cloud (int max_it, int n_particles, float w, float c1, float c2){
    //^ ETAPA 0: Inicializar variáveis globais ==>
    float best_global_points = -999;           //& Melhor pontuação global;
    vector<vector<int>> best_global_position;  //& Melhor posição global;
    
    //^ ETAPA 1: Inicializar as partículas ==>
    vector<particle> particles = initialize_particles(n_particles);  //& Conjunto de partículas;

    //^ ETAPA 2: Executar iterações do algoritmo ==>
    for (int i=0; i<max_it; i++){
        //^ 2.1: Atualizar pontuações das partículas -->
        for (int j=0; j<particles.size(); j++){
            particles[j].points = calculate_points(particles[j]);

            if(particles[j].points > particles[j].best_local_points){
                particles[j].best_local_points = particles[j].points;
                particles[j].best_local_position = particles[j].atual_position;
            }
        }

        //^ 2.2: Atualizar melhor pontuação global -->
        for (int j=0; j<particles.size(); j++){
            if(particles[j].best_local_points > best_global_points){
                best_global_points = particles[j].best_local_points;
                best_global_position = particles[j].best_local_position;
                
                particles[j].best_global_points = best_global_points;
                particles[j].best_global_position = best_global_position;
            }
        }

        //^ 2.3: Atualizar velocidades e calcular posições -->
        for (int j=0; j<particles.size(); j++){
            particles[j].speed = calculate_speed(particles[j], w, c1, c2);
            particles[j].atual_position = calculate_position(particles[j]);
        }
    }

    //^ ETAPA 3: Retornar a melhor solução ==>
    return best_global_position;
}
