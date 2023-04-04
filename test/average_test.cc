#include <gtest/gtest.h>

#include "../include/average_thread.h"

TEST(AverageThreadTest, FindArrayAverageUnit) {
    int arr[] = {3, 4, 7, 8};
    const double expected = 5.5;
    int n = sizeof(arr) / sizeof(arr[0]);
    double average = average_thread::FindArrayAverage(arr, n);
    EXPECT_DOUBLE_EQ(average, expected) << "Expected average value to equal " << expected << ", but found " << average;
}

TEST(AverageThreadTest, AverageWorkerIntegration) {
    int arr[] = {3, 4, 7, 9};
    const double expected = 5.75;
    int n = sizeof(arr) / sizeof(arr[0]);
    average_thread::IAverageProps props(arr, n);
    average_thread::IAveragePromise promise;
    boost::thread worker(average_thread::AverageWorker, std::cref(props), std::ref(promise));
    auto future = promise.get_future();
    double average = future.get();
    EXPECT_DOUBLE_EQ(average, expected) << "Expected average value to equal " << expected << ", but found " << average;
}