#include "../headers/Node.h"
#include "../headers/Graph.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <cstring>
#include <math.h>
#include <time.h>
#include <chrono>

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
float euclidian_dist(int x1, int y1, int x2, int y2)
{
    float x = abs(x2 - x1);
    float y = abs(y2 - y1);
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
Graph *build_graph(ifstream &instance)
{
    string line = "";   //~ Variável auxiliar para ler cada linha do arquivo;
    int count_line = 0; //~ Contador de linha do arquivo de entrada;

    int n = 0;        //~ Número de vértices;
    int h = 0;        //~ Número de hotéis extras;
    int d = 0;        //~ Número de viagens;
    int tMax = 0;     //~ Duração máxima do passeio;
    vector<float> td; //~ Vetor contendo a duração de cada viagem;

    float x = 0;  //~ Posição X inicial dos nós;
    float y = 0;  //~ Posição Y inicial dos nós;
    float sI = 0; //~ Pontuação inicial dos nós;
    int id = 0;   //~ Id inicial dos nós;

    int count = 0; //~ Contador auxiliar para os hotéis extras;

    Graph *new_graph = new Graph(n, h, d, tMax, td); //~ Grafo que será montado;

    //& Percorre o arquivo de entrada lendo os dados da instância e adicionando os nós no grafo;
    while (!instance.eof())
    {
        if (count_line == 0)
        {
            getline(instance, line);
            std::stringstream ss(line);
            string aux = "";

            getline(ss, aux, '	');
            n = stoi(aux);
            getline(ss, aux, '	');
            h = stoi(aux);
            getline(ss, aux, '\n');
            d = stoi(aux);

            count_line++;
        }
        else
        {
            if (count_line == 1)
            {
                getline(instance, line);
                std::stringstream ss(line);
                string aux = "";

                getline(ss, aux, '\n');
                tMax = stoi(aux);
                count_line++;
            }
            else
            {
                if (count_line == 2)
                {
                    getline(instance, line);
                    std::stringstream ss(line);
                    string aux = " ";
                    float num;

                    for (int k = 0; k < d; k++)
                    {
                        getline(ss, aux, '	');
                        num = std::stof(aux);
                        td.push_back(num);
                    }
                    count_line++;
                }
                else
                {
                    if (count_line == 3)
                    {
                        new_graph->order = n;
                        new_graph->h = h;
                        new_graph->d = d;
                        new_graph->tMax = tMax;
                        new_graph->td = td;

                        getline(instance, line);
                        std::stringstream ss(line);
                        count_line++;
                    }
                    else
                    {
                        if (count_line == 4)
                        {
                            getline(instance, line);
                            std::stringstream ss(line);
                            string aux = "";

                            getline(ss, aux, '	');
                            x = stof(aux);
                            getline(ss, aux, '	');
                            y = stof(aux);
                            getline(ss, aux, '\n');
                            sI = stof(aux);

                            new_graph->insert_node(id, 'I', sI, x, y);
                            count_line++;
                            id++;
                        }
                        else
                        {
                            if (count_line == 5)
                            {
                                getline(instance, line);
                                std::stringstream ss(line);
                                string aux = "";

                                getline(ss, aux, '	');
                                x = stoi(aux);
                                getline(ss, aux, '	');
                                y = stoi(aux);
                                getline(ss, aux, '\n');
                                sI = stoi(aux);

                                new_graph->insert_node(id, 'F', sI, x, y);
                                count_line++;
                                id++;
                            }
                            else
                            {

                                if (count < h)
                                {
                                    getline(instance, line);
                                    std::stringstream ss(line);
                                    string aux = "";

                                    getline(ss, aux, '	');
                                    x = stoi(aux);
                                    getline(ss, aux, '	');
                                    y = stoi(aux);
                                    getline(ss, aux, '\n');
                                    sI = stoi(aux);

                                    new_graph->insert_node(id, 'H', sI, x, y);
                                    count_line++;
                                    id++;
                                    count++;
                                }
                                else
                                {
                                    getline(instance, line);
                                    std::stringstream ss(line);
                                    string aux = "";

                                    if (id < n)
                                    {
                                        getline(ss, aux, '	');
                                        x = stoi(aux);
                                        getline(ss, aux, '	');
                                        y = stoi(aux);
                                        getline(ss, aux, '\n');
                                        sI = stoi(aux);

                                        new_graph->insert_node(id, 'N', sI, x, y);
                                    }
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

    //& Percorre o grafo adicionando as arestas em cada nó (grafo completo);
    for (int i = 0; i < new_graph->order; i++)
    {
        for (int j = 0; j < new_graph->order; j++)
        {
            if (i != j)
            {
                Node *node1 = new_graph->get_node(i);
                Node *node2 = new_graph->get_node(j);
                float euclidian = euclidian_dist(node1->pos_x, node1->pos_y, node2->pos_x, node2->pos_y);
                new_graph->insert_edge(i, j, euclidian);
            }
        }
    }

    //& Retorna o grafo construído;
    return new_graph;
}

int main(int argc, char const *argv[])
{
    srand(time(0));
    cout << "######################################### BEM VINDO #########################################" << endl;
    cout << "_____________________________________________________________________________________________" << endl;

    cout << "-> Abrindo arquivo de entrada..." << endl;

    //& Abrindo arquivo da instância;

    if (argc < 2)
    {
        cout << "-> Erro: Nenhum arquivo de entrada foi passado!" << endl;
        cout << "-> Encerrando programa..." << endl;
        return 1;
    }
    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;
    using std::chrono::milliseconds;

    string instance_path(argv[1]);
    ifstream instance_file;
    instance_file.open(argv[1], ios::in);

    if (instance_file.is_open())
    {
        cout << "-> Arquivo aberto com sucesso!" << endl;
        cout << "____________________________________________________" << endl;

        cout << "-> Iniciando construção do grafo..." << endl;
        Graph *new_graph = build_graph(instance_file);

        cout << "-> Grafo construído com sucesso!" << endl;
        cout << "____________________________________________________" << endl;

        cout << "-> Iniciando busca heurística..." << endl;
        auto t1 = high_resolution_clock::now();
        // Setando a seed para o random
        vector<vector<int>> solution = new_graph->randomizedHeuristic(0.15, 100, 42);
        auto t2 = high_resolution_clock::now();

        duration<float, std::milli> ms_double = t2 - t1;

        cout << "-> Printando solução..." << endl;
        cout << "____________________________________________________" << endl;

        cout << "-> Solução encontrada: " << endl;
        float benefit = 0;
        float duration = 0;
        for (int i = 0; i < solution.size(); i++)
        {
            cout << "-> Dia " << i + 1 << ": ";
            for (int j = 0; j < solution[i].size(); j++)
            {
                cout << solution[i][j] << " ";
                if (j != 0)
                {
                    benefit += new_graph->get_node(solution[i][j])->points;
                    if (j < (solution[i].size() - 2))
                    {
                        duration += new_graph->get_node(solution[i][j])->get_edge(solution[i][j + 1])->dist;
                    }
                }
            }
            cout << endl;
        }

        cout << "-> Pontuação total: " << benefit << endl;
        cout << "-> Duração total do passeio: " << duration << endl;
        cout << "-> Tempo de execução (ms): " << ms_double.count() << endl;
    }
    else
    {
        return 1;
    }
    cout << "_____________________________________________________________________________________________" << endl;
    cout << "###############################################################1##############################" << endl;

    return 0;
}
