#pragma once

// only included in case there's a C++11 compiler out there that doesn't support `#pragma once`
#ifndef DKM_KMEANS_H
#define DKM_KMEANS_H

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <random>
#include <tuple>
#include <type_traits>
#include <vector>
#include <immintrin.h>

/*
DKM - A k-means implementation that is generic across variable data dimensions.
*/
namespace dkm {

/*
These functions are all private implementation details and shouldn't be referenced outside of this
file.
*/
namespace details {

/*
Calculate the square of the distance between two points.
*/
template <typename T>
T distance_squared(const std::vector<T>& point_a, const std::vector<T>& point_b) {
	T d_squared = T();

    for (typename std::vector<T>::size_type i = 0; i < point_a.size(); ++i) {
		auto delta = point_a[i] - point_b[i];
		d_squared += delta * delta;
	}
	return d_squared;
}

// Helper function to perform horizontal sum for 8 floats
static inline float hadd_avx(__m256 vec) {
    __m256 hadd = _mm256_hadd_ps(vec, vec);  // Horizontal add
    __m128 low = _mm256_castps256_ps128(hadd);  // Lower 128 bits
    __m128 high = _mm256_extractf128_ps(hadd, 1);  // Upper 128 bits
    __m128 sum = _mm_add_ps(low, high);  // Add the two parts
    return sum[0] + sum[1];  // Return the final sum
}

// Helper function to perform horizontal sum for 4 doubles
static inline double hadd_avx(__m256d vec) {
    __m256d hadd = _mm256_hadd_pd(vec, vec);  // Horizontal add
    __m128d low = _mm256_castpd256_pd128(hadd);  // Lower 128 bits
    __m128d high = _mm256_extractf128_pd(hadd, 1);  // Upper 128 bits
    __m128d sum = _mm_add_pd(low, high);  // Add the two parts
    return sum[0] + sum[1];  // Return the final sum
}

// SIMD for float type (AVX2)
template <>
float distance_squared(const std::vector<float>& point_a, const std::vector<float>& point_b) {
    float d_squared = 0.0f;
    size_t size = point_a.size();
    
    size_t i = 0;
    for (; i + 7 < size; i += 8) {
        __m256 a_vals = _mm256_loadu_ps(&point_a[i]);  // 加载 8 个 float 元素
        __m256 b_vals = _mm256_loadu_ps(&point_b[i]);
        __m256 diff = _mm256_sub_ps(a_vals, b_vals);   // 计算差
        __m256 diff_squared = _mm256_mul_ps(diff, diff); // 差的平方
        d_squared += hadd_avx(diff_squared); // 求和
    }

    // 处理剩余的元素（如果有的话）
    for (; i < size; ++i) {
        float delta = point_a[i] - point_b[i];
        d_squared += delta * delta;
    }
    
    return d_squared;
}

// SIMD for double type (AVX2)
template <>
double distance_squared(const std::vector<double>& point_a, const std::vector<double>& point_b) {
    double d_squared = 0.0;
    size_t size = point_a.size();
    
    size_t i = 0;
    for (; i + 3 < size; i += 4) {
        __m256d a_vals = _mm256_loadu_pd(&point_a[i]);  // 加载 4 个 double 元素
        __m256d b_vals = _mm256_loadu_pd(&point_b[i]);
        __m256d diff = _mm256_sub_pd(a_vals, b_vals);   // 计算差
        __m256d diff_squared = _mm256_mul_pd(diff, diff); // 差的平方
        d_squared += hadd_avx(diff_squared); // 求和
    }

    // 处理剩余的元素（如果有的话）
    for (; i < size; ++i) {
        double delta = point_a[i] - point_b[i];
        d_squared += delta * delta;
    }
    
    return d_squared;
}


template <typename T>
T distance(const std::vector<T>& point_a, const std::vector<T>& point_b) {
	return std::sqrt(distance_squared(point_a, point_b));
}

/*
Calculate the smallest distance between each of the data points and any of the input means.
*/
template <typename T>
std::vector<T> closest_distance(
    const std::vector<std::vector<T>>& means, const std::vector<std::vector<T>>& data) {
	std::vector<T> distances(data.size());
	#pragma omp parallel for
	for (size_t i = 0; i < data.size(); ++i) {
		T closest = distance_squared(data[i], means[0]);
		for (const auto& m : means) {
			T distance = distance_squared(data[i], m);
			if (distance < closest)
				closest = distance;
		}
		distances[i] = closest;
	}
	return distances;
}

/*
This is an alternate initialization method based on the [kmeans++](https://en.wikipedia.org/wiki/K-means%2B%2B)
initialization algorithm.
*/
template <typename T>
std::vector<std::vector<T>> random_plusplus(const std::vector<std::vector<T>>& data, uint32_t k) {
	assert(k > 0);
	assert(data.size() > 0);
    using input_size_t = typename std::vector<T>::size_type;
    std::vector<std::vector<T>> means;
	// Using a very simple PRBS generator, parameters selected according to
	// https://en.wikipedia.org/wiki/Linear_congruential_generator#Parameters_in_common_use
	std::random_device rand_device;
	std::linear_congruential_engine<uint64_t, 6364136223846793005, 1442695040888963407, UINT64_MAX> rand_engine(
		rand_device());

	// Select first mean at random from the set
	{
		std::uniform_int_distribution<input_size_t> uniform_generator(0, data.size() - 1);
		means.push_back(data[uniform_generator(rand_engine)]);
	}

	for (uint32_t count = 1; count < k; ++count) {
		// Calculate the distance to the closest mean for each data point
		auto distances = details::closest_distance(means, data);
		// Pick a random point weighted by the distance from existing means
		// TODO: This might convert floating point weights to ints, distorting the distribution for small weights
#if !defined(_MSC_VER) || _MSC_VER >= 1900
		std::discrete_distribution<input_size_t> generator(distances.begin(), distances.end());
#else  // MSVC++ older than 14.0
		input_size_t i = 0;
		std::discrete_distribution<input_size_t> generator(distances.size(), 0.0, 0.0, [&distances, &i](double) { return distances[i++]; });
#endif
		means.push_back(data[generator(rand_engine)]);
	}
	return means;
}

/*
Calculate the index of the mean a particular data point is closest to (euclidean distance)
*/
template <typename T>
uint32_t closest_mean(const std::vector<T>& point, const std::vector<std::vector<T>>& means) {
    assert(!means.empty());

	T smallest_distance = distance_squared(point, means[0]);
    typename std::vector<T>::size_type index = 0;
	T distance;
	for (size_t i = 1; i < means.size(); ++i) {
		distance = distance_squared(point, means[i]);
		if (distance < smallest_distance) {
			smallest_distance = distance;
			index = i;
		}
	}
	return index;
}

/*
Calculate the index of the mean each data point is closest to (euclidean distance).
*/
template <typename T>
std::vector<uint32_t> calculate_clusters(
    const std::vector<std::vector<T>>& data, const std::vector<std::vector<T>>& means) {
	std::vector<uint32_t> clusters(data.size(), 0);
	#pragma omp parallel for
	for (size_t i = 0; i < data.size(); ++i) {
		clusters[i] = closest_mean(data[i], means);
	}
	return clusters;
}

/*
Calculate means based on data points and their cluster assignments.
*/
template <typename T>
std::vector<std::vector<T>> calculate_means(const std::vector<std::vector<T>>& data,
	const std::vector<uint32_t>& clusters,
    const std::vector<std::vector<T>>& old_means,
	uint32_t k) {
	size_t size = data[0].size();
    std::vector<std::vector<T>> means(k, std::vector<T>(size,0));

	std::vector<T> count(k, T());
	for (size_t i = 0; i < std::min(clusters.size(), data.size()); ++i) {
		auto& mean = means[clusters[i]];
		count[clusters[i]] += 1;
        for (size_t j = 0; j < std::min(data[i].size(), mean.size()); ++j) {
			mean[j] += data[i][j];
		}
	}
	for (size_t i = 0; i < k; ++i) {
		if (count[i] == 0) {
			means[i] = old_means[i];
		} else {
			for (size_t j = 0; j < means[i].size(); ++j) {
				means[i][j] /= count[i];
			}
		}
	}
	return means;
}

} // namespace details


/*
Implementation of k-means generic across the data type and the dimension of each data item. Expects
the data to be a vector of fixed-size arrays. Generic parameters are the type of the base data (T)
and the dimensionality of each data point (N). All points must have the same dimensionality.

e.g. points of the form (X, Y, Z) would be N = 3.

Returns a std::tuple containing:
  0: A vector holding the means for each cluster from 0 to k-1.
  1: A vector containing the cluster number (0 to k-1) for each corresponding element of the input
	 data vector.

Implementation details:
This implementation of k-means uses [Lloyd's Algorithm](https://en.wikipedia.org/wiki/Lloyd%27s_algorithm)
with the [kmeans++](https://en.wikipedia.org/wiki/K-means%2B%2B)
used for initializing the means.
*/
template <typename T>
std::tuple<std::vector<std::vector<T>>, std::vector<uint32_t>> kmeans_lloyd(
    const std::vector<std::vector<T>>& data, uint32_t k) {
	static_assert(std::is_arithmetic<T>::value && std::is_signed<T>::value,
		"kmeans_lloyd requires the template parameter T to be a signed arithmetic type (e.g. float, double, int)");
	assert(k > 0); // k must be greater than zero
	assert(data.size() >= k); // there must be at least k data points
    std::vector<std::vector<T>> means = details::random_plusplus(data, k);

    std::vector<std::vector<T>> old_means;
    std::vector<std::vector<T>> old_old_means;
	std::vector<uint32_t> clusters;
	// Calculate new means until convergence is reached
	int count = 0;
	do {
		clusters = details::calculate_clusters(data, means);
		old_old_means = old_means;
		old_means = means;
		means = details::calculate_means(data, clusters, old_means, k);
		++count;
	} while (means != old_means && means != old_old_means);

    return std::tuple<std::vector<std::vector<T>>, std::vector<uint32_t>>(means, clusters);
}

} // namespace dkm

#endif /* DKM_KMEANS_H */
