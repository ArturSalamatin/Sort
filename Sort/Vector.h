#pragma once
#include <string>
#include <algorithm>

class Vector
{
	size_t n = 0;
	int* vals; // dynamic array

public:
	Vector(size_t n);
	Vector(const Vector& vec); // copy-constructor creates a deep copy of vec and saves it to other object. Also copies the vals elements.
	std::string status() const;
	size_t size() const { return n; }
	int operator[] (size_t) const;
	int& operator[] (size_t i) { return vals[i]; };
	void swap(size_t i, size_t j);

	// https://airtucha.github.io/SortVis/
	void sort() { std::sort(vals, vals + n); }; // C++ built-in sorting algorithm
	// https://ru.wikipedia.org/wiki/%D0%A1%D0%BE%D1%80%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%BA%D0%B0_%D0%BF%D1%83%D0%B7%D1%8B%D1%80%D1%8C%D0%BA%D0%BE%D0%BC
	void bubble_sort();
	// https://ru.wikipedia.org/wiki/%D0%A1%D0%BE%D1%80%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%BA%D0%B0_%D0%BF%D0%B5%D1%80%D0%B5%D0%BC%D0%B5%D1%88%D0%B8%D0%B2%D0%B0%D0%BD%D0%B8%D0%B5%D0%BC
	void shaker_sort();
	//https://stackoverflow.com/questions/1174169/function-passed-as-template-argument
	template<typename Functor>
	void quick_sort(Functor);

	static ptrdiff_t partition_lomuto(Vector&, ptrdiff_t, ptrdiff_t);
	static ptrdiff_t partition_hoare(Vector&, ptrdiff_t, ptrdiff_t);
	template<typename Functor>
	void qsort_recursive(ptrdiff_t, ptrdiff_t, Functor);

	void merge_sort();
private:
	Vector* merge(Vector* B, Vector* C);
};

class test_vector
{
public:
	static void test_1();
};

