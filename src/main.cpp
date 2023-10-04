#include "../headers/Node.h"
#include "../headers/Graph.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <cstring>
#include<conio.h>
#include<math.h>

using namespace std;

/**
 * @brief         Função utilizada para calcular a distância euclidiana entre dois nós; 
 * 
 * @param x1      X do nó origem;
 * @param y1      Y do nó origem;
 * @param x2      X do nó alvo;
 * @param y2      Y do nó alvo;
 * @return float  Retorna a distância euclidiana entre os nós;
 */
float euclidian_dist(int x1, int y1, int x2, int y2){
    float x = x1 - x2;
	float y = y1 - y2;
	float dist;

	dist = pow(x, 2) + pow(y, 2);
	dist = sqrt(dist);                  

	return dist;
}

/**
 * @brief           Função utilizada para construir um grafo completo a partir de uma instância;
 * 
 * @param instance  Arquivo de entrada contendo a instãncia a ser lida; 
 * @return Graph*   Retorna o grafo montado;
 */
Graph *build_graph(ifstream &instance) {
    string line = "";
    int count_line = 0;

    int n = 0;
    int h = 0;
    int d = 0;
    int tMax = 0;
    vector<float> td;

    Graph *new_graph;

    while(!instance.eof()){
        if(count_line == 0){
            std::getline(instance, line);         
            std::stringstream ss(line);
            string aux = "";

            std::getline(ss, aux, ' ');
            n = stoi(aux);
            std::getline(ss, aux, ' ');
            h = stoi(aux);
            std::getline(ss, aux, ' ');
            d = stoi(aux);

            count_line++;
        }
        else{
            if(count_line == 1){
                instance >> tMax;
                count_line++;
            }
            else{
                if(count_line == 2){
                    for(int i=0; i<d; i++){
                        std::getline(instance, line);         
                        std::stringstream ss(line);
                        string aux = "";

                        std::getline(ss, aux, ' ');
                        td.push_back(stoi(aux));
                        std::getline(ss, aux, ' ');
                        td.push_back(stoi(aux));
                    }
                    count_line++;
                }
                else{
                    if(count_line == 3){
                        std::getline(instance, line);         
                        std::stringstream ss(line);
                        count_line++;
                    }
                    else{
                        int x = 0;
                        int y = 0;
                        int sI = 0;
                        int id = 0;
                        new_graph = new Graph(n);

                        if(count_line == 4){
                            std::getline(instance, line);         
                            std::stringstream ss(line);
                            string aux = "";
                            
                            std::getline(ss, aux, ' ');
                            x = stoi(aux);
                            std::getline(ss, aux, ' ');
                            y = stoi(aux);
                            std::getline(ss, aux, ' ');
                            sI = stoi(aux);

                            new_graph->insert_node(id, 'I', sI, x, y);
                            count_line++;
                            id++;
                        }
                        else{
                            if(count_line == 5){
                                std::getline(instance, line);         
                                std::stringstream ss(line);
                                string aux = "";
                                
                                std::getline(ss, aux, ' ');
                                x = stoi(aux);
                                std::getline(ss, aux, ' ');
                                y = stoi(aux);
                                std::getline(ss, aux, ' ');
                                sI = stoi(aux);

                                new_graph->insert_node(id, 'F', sI, x, y);
                                count_line++;
                                id++;
                            }
                            else{
                                if(count_line < (h+5)){
                                    std::getline(instance, line);         
                                    std::stringstream ss(line);
                                    string aux = "";
                                    
                                    std::getline(ss, aux, ' ');
                                    x = stoi(aux);
                                    std::getline(ss, aux, ' ');
                                    y = stoi(aux);
                                    std::getline(ss, aux, ' ');
                                    sI = stoi(aux);

                                    new_graph->insert_node(id, 'H', sI, x, y);
                                    count_line++;
                                    id++;
                                }
                                else{
                                    std::getline(instance, line);         
                                    std::stringstream ss(line);
                                    string aux = "";
                                    
                                    std::getline(ss, aux, ' ');
                                    x = stoi(aux);
                                    std::getline(ss, aux, ' ');
                                    y = stoi(aux);
                                    std::getline(ss, aux, ' ');
                                    sI = stoi(aux);

                                    new_graph->insert_node(id, 'N', sI, x, y);
                                    count_line++;
                                    id++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    for(int i=0; i<new_graph->order; i++){
        for(int j=0; j<new_graph->order; j++){
            if(i!=j){
                Node *node1 = new_graph->get_node(i);
                Node *node2 = new_graph->get_node(j);

                float euclidian = euclidian_dist(node1->pos_x, node1->pos_y, node2->pos_x, node2->pos_y);
                new_graph->insert_edge(i, j, euclidian);
            }
        }
    }

    return new_graph;
}
