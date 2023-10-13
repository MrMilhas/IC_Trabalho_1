#include "../headers/Node.h"
#include "../headers/Edge.h"

using namespace std;

//* Constructor and Destructor -------------------------------------------------------------
Node::Node(int id, char type, int points, int x, int y)
{
    this->id = id;
    this->type = type;
    this->points;
    this->pos_x = x;
    this->pos_y = y;
}

Node::~Node()
{
    Edge *edge = this->first_edge;

    while (edge != nullptr)
    {
        Edge *aux_edge = edge->next_edge;
        delete edge;
        edge = aux_edge;
    }
}

//* Other Functions ------------------------------------------------------------------------
/**
 * @brief            Função utilizada para procurar uma aresta no nó;
 *
 * @param target_id  Id da aresta que deseja encontrar;
 * @return true      Encontrou a aresta;
 * @return false     Não encontrou a aresta;
 */
bool Node::search_edge(int target_id)
{
    if (this->first_edge != nullptr)
    {
        for (Edge *aux = this->first_edge; aux != nullptr; aux = aux->next_edge)
        {
            if (aux->target_id == target_id)
            {
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief            Função utilizada para inserir nova aresta no nó;
 *
 * @param target_id  Id do nó alvo;
 * @param dist       Distância até o nó alvo;
 */
void Node::insert_edge(int target_id, float dist)
{
    if (this->first_edge != nullptr)
    {
        Edge *edge = new Edge(target_id);
        edge->dist = dist;
        this->last_edge->next_edge = edge;
        this->last_edge = edge;
    }
    else
    {
        this->first_edge = new Edge(target_id);
        this->first_edge->dist = dist;
        this->last_edge = this->first_edge;
    }
}

/**
 * @brief  Função utilizada para remover todas as arestas do nó;
 *
 */
void Node::remove_all_edges()
{
    if (this->first_edge != nullptr)
    {
        Edge *next = nullptr;
        Edge *aux = this->first_edge;
        while (aux != nullptr)
        {
            next = aux->next_edge;
            delete aux;
        }
    }
    this->first_edge = this->last_edge = nullptr;
}

Edge *Node::get_edge(int target_id)
{
    if (this->first_edge != nullptr)
    {
        for (Edge *aux = this->first_edge; aux != nullptr; aux = aux->next_edge)
        {
            if (aux->target_id == target_id)
            {
                return aux;
            }
        }
    }
    return nullptr;
}