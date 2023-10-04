#include "../headers/Graph.h"
#include "../headers/Node.h"
#include "../headers/Edge.h"

using namespace std;

//* Constructor and Destructor -------------------------------------------------------------
Graph::Graph(int order){
    this->order = order;
    this->first_node = nullptr;
    this->last_node = nullptr;
}

Graph::~Graph(){
    Node *next_node = this->first_node;

    while (next_node != nullptr){
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
Node* Graph::get_node(int id){
    Node *node = first_node;

    while (node != nullptr){
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
void Graph::insert_node(int id, char type, int points, int x, int y){
    if (first_node != nullptr){
        Node *new_node = new Node(id, type, points, x, y);
        last_node->next_node = new_node;
        last_node = new_node;
    }
    else{
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
void Graph::insert_edge(int id, int target_id, float dist){
    Node *node = get_node(id);
    Node *aux = get_node(target_id);

    if (node != nullptr && aux != nullptr){
        if (!node->search_edge(target_id)){
            node->insert_edge(target_id, dist);

            if (!aux->search_edge(id)){
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
void Graph::remove_node(int id){
    Node *node = get_node(id);

    if (node == nullptr){
        return;
    }
    else if (node == first_node){
        first_node = node->next_node;
    }
    else{
        Node *aux = first_node;

        while (aux->next_node != node){
            aux = aux->next_node;
        }

        if (node == last_node){
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
bool Graph::search_node(int id){
    Node *node = get_node(id);

    if (node == nullptr){
        return false;
    }
    else{
        return true;
    }
}
