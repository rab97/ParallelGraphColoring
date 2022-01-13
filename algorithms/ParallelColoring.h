//
// Created by rab97 on 30/12/21.
//

#ifndef PARALLELGRAPHCOLORING_PARALLELCOLORING_H
#define PARALLELGRAPHCOLORING_PARALLELCOLORING_H

#include <functional>
#include <vector>
#include <mutex>
#include <thread>
#include <pthread.h>
#include <semaphore.h>
#include <optional>
#include <iostream>

template<typename T>
class ParallelColoring {
public:
    using callback_t = void(T);

private:
    std::vector <T> data;
    bool stopped;

    std::mutex mutex;
    sem_t sem;

    std::vector <std::thread> threads;

public:
    ParallelColoring() : stopped(false) {
        sem_init(&sem, 0, 0);
    }

    ParallelColoring(std::vector <T> &&_data) : data(std::move(_data)), stopped(false) {
        sem_init(&sem, 0, data.size());
    }

    ~ParallelColoring() {
        sem_destroy(&sem);
    }

    void push(const T &val) {
        if (stopped)
            throw std::runtime_error("Writing to stopped queue");
        mutex.lock();
        data.emplace_back(val);
        mutex.unlock();
        sem_post(&sem);
    }

    T pop() {
        sem_wait(&sem);
        if (stopped) {
            sem_post(&sem);
        }
        std::unique_lock lock(mutex);
        T result = data.back();
        data.pop_back();
        return result;
    }

    void stop() {
        stopped = true;
        sem_post(&sem);
    }

    void join() {
        for (auto &t: threads)
            t.join();
    }

    void onReceive(int thread_numbers, std::function <callback_t> callback) {
        for (int i = 0; i < thread_numbers; i++)
            threads.emplace_back([=](ParallelColoring<T> &queue, int i) {
                std::cout << "Thread " << i;
                while (T data = queue.pop()) {
                    callback(data);
                }
            }, std::ref(*this), i);
    }
};

#endif //PARALLELGRAPHCOLORING_PARALLELCOLORING_H
