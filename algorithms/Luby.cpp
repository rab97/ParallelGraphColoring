//
// Created by marta on 15/01/22.
//
#include "Luby.h"
#include <condition_variable>
#include <numeric>
#include <algorithm>


mutex I_mutex, remainingNode_mutex;
mutex mutex_color;
condition_variable mis_cond_var;
int semMIS;

Luby::Luby() {}

Luby::Luby(int num_threads) : num_threads(num_threads), random(123) {}


void Luby::algorithmSolver(Graph &graph) {

    std::set <std::set<int>> mis;
    std::set<int> I;

    int num_vertices = graph.num_vertices();
    int max_color = 0;
    int running_threads = num_threads;

    std::vector <Vertex> *verticesList = graph.getVerticesList();


    vector<int> assigned_vertices(num_vertices);
    for (int i = 0; i < num_vertices; i++) {
        assigned_vertices.at(i) = (verticesList->at(i).getId());
    }
    semMIS = num_threads;
    std::iota(assigned_vertices.begin(), assigned_vertices.end(), 0);
    std::shuffle(assigned_vertices.begin(), assigned_vertices.end(), random);

    if (num_threads > std::thread::hardware_concurrency())
        throw std::runtime_error("Hardware concurrency exceeded: please use at most " +
                                 std::to_string(std::thread::hardware_concurrency()) + " threads");

    Splitter s(num_vertices, num_threads);
    std::vector <std::thread> threads;

    //Part 1 : assign all vertices a random permutation and then find all MIS in the graph
    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back(
                std::thread([&graph, &mis, &I, &assigned_vertices, &max_color, &running_threads, this, s, i]() {
                    int from = s.get_min(i), to = s.get_max(i);
                    find_MIS_Parallel(from, to, max_color, running_threads, mis, I, assigned_vertices, graph);

                }));
    }
    for (auto &thread: threads) {
        thread.join();
    }
}


void Luby::find_MIS_Parallel(int from, int to, int &max_color, int &running_threads, std::set <std::set<int>> &mis,
                             std::set<int> &I,
                             vector<int> &assigned_vertices, Graph &graph) {

    int num_remain = to - from;
    std::set<int> nodes_remain;
    std::set<int> neighbors;
    std::vector <Vertex> *verticesList = graph.getVerticesList();
    running_threads = num_threads;

    for (int i = from; i < to; i++) {
        nodes_remain.emplace(i);
    }

    int cur_node_id;
    std::vector <Vertex> neighborList;

    while (num_remain > 0) {

        for (int j = from; j < to; j++) {

            cur_node_id = j;

            if (nodes_remain.find(j) != nodes_remain.end()) {

                bool isMax = isMax_between_neighbor(verticesList->at(j), j, assigned_vertices);
                if (isMax) {
                    //vertex is colored and inserted into the indipendent set
                    I_mutex.lock();
                    I.insert(cur_node_id);
                    //graph.colorVertex(&verticesList->at(j), max_color);
                    assigned_vertices[cur_node_id] = -1;       //the next iteration it won't be the max
                    I_mutex.unlock();

                    //remove neighbors from nodes_remain if they belong to the interval [from, to)
                    neighborList = verticesList->at(j).getNeighborList();
                    int neighbor_id;
                    for (int k = 0; k < neighborList.size(); k++) { //for each neighbor of that node

                        neighbor_id = neighborList[k].getId() - 1;


                        if (nodes_remain.find(neighbor_id) != nodes_remain.end()) {
                            num_remain--;
                            neighbors.insert(neighbor_id);
                            nodes_remain.erase(neighbor_id);
                        }
                    }

                    //remove cur_node_id from nodes_remain
                    num_remain--;
                    nodes_remain.erase(cur_node_id);

                } else {
                    neighbors.insert(cur_node_id);
                }

            }

        }


        //at this point a MIS is found
        std::unique_lock <std::mutex> lock(I_mutex);
        semMIS--;

        if (semMIS <= 0) {
            //Insertion of indipendent set into mis
            mis.insert(I);
            graph.addColor(max_color);
            max_color++;
            I.clear();
            if (num_remain == 0) {
                running_threads--;
            }
            semMIS = running_threads;
            mis_cond_var.notify_all();

        } else {

            if (num_remain == 0) {
                running_threads--;
            }
            mis_cond_var.wait(lock);
        }

        num_remain = neighbors.size();
        nodes_remain = neighbors;
        neighbors.clear();
    }
}


bool Luby::isMax_between_neighbor(Vertex v, int id, std::vector<int> &assigned_vertices) {

    std::vector <Vertex> neighbor = v.getNeighborList();
    int value = assigned_vertices[id];
    int neighbor_id;

    for (int i = 0; i < neighbor.size(); i++) {

        neighbor_id = id;

        if (assigned_vertices[neighbor_id] > value) {
            //found a neighbor with higher value
            return false;

        } else if (assigned_vertices[neighbor_id] == value) {
            //if they have the same random value look at the id
            if (neighbor_id > id) {
                return false;
            }
        }
    }
    //if we're at this point, we've not found a neighbor
    // with a major rand value
    return true;
}


std::string Luby::name() const {
    return "Luby (" + std::to_string(num_threads) + " threads)";
};