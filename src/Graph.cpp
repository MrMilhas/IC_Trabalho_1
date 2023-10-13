#include "../headers/Graph.h"
#include "../headers/Node.h"
#include "../headers/Edge.h"
#include <iostream>
#include <set>
#include <algorithm>

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

vector<pair<int, float>> Graph::createCandidates()
{
    vector<pair<int, float>> candidates;

    Node *node = first_node->next_node;

    while (node != nullptr)
    {
        if (node->type == 'N')
        {
            candidates.push_back(make_pair(node->id, (node->points / node->get_edge(first_node->id)->dist)));
        }
        node = node->next_node;
    }

    // Ordenar o vetor pelo segundo elemento
    sort(candidates.begin(), candidates.end(), [](const pair<int, float> &a, const pair<int, float> &b)
         { return a.second > b.second; });

    return candidates;
}

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

    candidates.push_back(first_node->next_node->id);

    cout << "h: " << h << endl;
    cout << "Hoteis: ";
    for (int i = 0; i < candidates.size(); i++)
    {
        cout << candidates[i] << " ";
    }

    return candidates;
}

vector<pair<int, float>> Graph::updateCandidates(vector<pair<int, float>> *candidates, Node *node)
{
    vector<pair<int, float>> aux;

    for (int i = 0; i < candidates->size(); i++)
    {
        Node *nodeAux = this->get_node(candidates->at(i).first);
        aux.push_back(make_pair(candidates->at(i).first, (nodeAux->points / nodeAux->get_edge(node->id)->dist)));
    }

    // Ordenar o vetor pelo segundo elemento
    sort(aux.begin(), aux.end(), [](const pair<int, float> &a, const pair<int, float> &b)
         { return a.second > b.second; });

    return aux;
}

vector<vector<int>> Graph::createNeighborhood(vector<int> solution){
    vector<vector<int>> neighborhood;
    
    Node *node = this->get_node(solution[solution.size()-3]);
    Edge *edge = node->first_edge;
        
    while(edge != nullptr){
        vector<int> aux_sol = solution;                  //~ Inicializa solução auxiliar;
        aux_sol[(solution.size()-2)] = edge->target_id;  //~ Adiciona na solução auxliar o alvo da aresta;

        Edge *aux_edge = this->get_node(aux_sol[(aux_sol.size()-2)])->first_edge;
        while(aux_edge!=nullptr){
            aux_sol[(solution.size()-1)] = aux_edge->target_id;
            neighborhood.push_back(aux_sol);
            aux_edge = aux_edge->next_edge;
        }
        
        edge = edge->next_edge;
    }
    return neighborhood;
}

int Graph::get_total_dist(vector<int> solution){
    int dist = 0;
    for(int i=0; i<(solution.size()-2); i++){
        dist += this->get_node(solution[i])->get_edge(solution[i+1])->dist;
    }
    return dist;
}

int Graph::get_total_points(vector<int> solution){
    int pts = 0;
    for(int i=0; i<solution.size(); i++){
        pts += this->get_node(i)->points;
    }
    return pts;
}

float Graph::get_ls_points(vector<int> solution){
    float points_1 = this->get_total_points(solution)/ this->get_total_dist(solution);
    float points_2 = -9999999;
    
    Edge *edge = this->get_node(solution[solution.size()-1])->first_edge;

    while(edge != nullptr){
        float aux = this->get_node(edge->target_id)->points / edge->dist;
        if(aux > points_2){
            points_2 = aux;
        }
        edge = edge->next_edge;
    }
    return points_1 + points_2;
}

vector<vector<int>> Graph::heuristic()
{
    vector<vector<vector<int>>> solutions;
    vector<vector<int>> solution;
    vector<pair<int, float>> candidates = this->createCandidates();
    vector<int> hotelsCandidates = this->createHotelsCandidates();

    int days = td.size();

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

        while (t < td[i])
        {
            aux.push_back(candidates[0].first);
            t += this->get_node(candidates[0].first)->get_edge(first_node->id)->dist; // Somar o tempo da viagem

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

            candidates.erase(candidates.begin());
            candidates = this->updateCandidates(&candidates, this->get_node(aux[aux.size() - 1]));
        }
        //* Local Search -------------------------------------------------------------
        if(i < days -1){
            vector<int> best_aux = aux;
            vector<vector<int>> neighborhood = this->createNeighborhood(aux);
            
            long long int bad_iter = 0;        //~ Contador de iterações que não conseguiram melhorar a solução;
            long long int max_bad_iter = 900;  //~ Máximo de iterações ruins;
            long long int k = 0;
            
            while((bad_iter < max_bad_iter) && (k < neighborhood.size())){
                int t_ls = get_total_dist(neighborhood[k]);
                if(t_ls<td[i]){
                    int best_points = get_ls_points(best_aux);  //~ Pontuação da melhor solução atual;
                    int pts = get_ls_points(neighborhood[k]);   //~ Pontuação da solução da iteração atual;

                    if(pts > best_points){
                        best_aux = neighborhood[k];
                        bad_iter = 0;
                    }
                    else{
                        bad_iter++;
                    }
                }
                else{
                    bad_iter++;
                }
                k++;
            }
            aux = best_aux;
        }
        
        t = 0;
        solution.push_back(aux);
    }

    return solution;
}
