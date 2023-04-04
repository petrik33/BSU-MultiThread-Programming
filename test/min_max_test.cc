#include "../include/min_max.h"

#include <gtest/gtest.h>

TEST(MinMaxThreadTest, LocateMinMaxUnit) {
    int arr[] = {4, 5, 6, 7, 8, 9, 10, 1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    min_max_thread::min_max_location_pair result = min_max_thread::LocateMinMax(arr, n);
    EXPECT_EQ(arr[result.first], 1) << "Expected min value at index " << result.first << ", but found " << arr[result.first];
    EXPECT_EQ(arr[result.second], 10) << "Expected max value at index " << result.second << ", but found " << arr[result.second];
}

TEST(MinMaxThreadTest, MinMaxWorkerIntegration) {
    int arr[] = {3, 5, 1, 4, 10, -5, 15, 0, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    min_max_thread::IMinMaxProps props(arr, n);
    min_max_thread::IMinMaxPromise promise;
    boost::thread worker(min_max_thread::MinMaxWorker, std::cref(props), std::ref(promise));
    auto future = promise.get_future();
    min_max_thread::min_max_location_pair result = future.get();
    EXPECT_EQ(arr[result.first], -5) << "Expected min value at index " << result.first << ", but found " << arr[result.first];
    EXPECT_EQ(arr[result.second], 15) << "Expected max value at index " << result.second << ", but found " << arr[result.second];
}