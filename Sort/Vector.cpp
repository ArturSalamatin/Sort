#include "Vector.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>


Vector::Vector(size_t n)
	:n{ n }
{
	/*vals = new int[n];
	for (int i = 0; i < n; i++)
		vals[i] = 1 + std::rand() / ((RAND_MAX + 1u) / 25);
	vals[0] = 19;*/

	vals = new int[n]{ 64, 42, 80, 20, 69, 63, 14, 84, 76, 22 };
	vals = new int[n] { 5,2,3,1,0,0,0,0,0,0 };
}

Vector::Vector(const Vector& vec)
{
	n = vec.size();
	vals = new int[n];
	for (size_t i = 0; i < n; ++i)
		vals[i] = vec[i];
}

int Vector::operator[] (size_t i) const { return vals[i]; }

std::string Vector::status() const
{
	std::string result;
	for (size_t i = 0; i < n; ++i)
		result += std::to_string(vals[i]) + "; ";
	return result;

	//int* p;
	//p = nullptr;
	//p = NULL;
	//p = 0;

}

void Vector::bubble_sort()
{
	for (size_t i = 1; i < n; i++)
	{
		for (size_t j = 1; j < n - i + 1; j++)
		{
			if (vals[j] < vals[j - 1])
				swap(j, j - 1);
		}
		std::cout << (*this).status() << std::endl;
	}
}

void Vector::shaker_sort()
{
	size_t left = 0;
	size_t right = n;
	size_t control = n;

	while (left < right-1)
	{
		for (size_t i = left+1; i < right; i++)
		{
			if (vals[i - 1] > vals[i])
			{
				swap(i - 1, i);
				control = i;
			}
		}
		std::cout << control << ": " << (*this).status() << std::endl;
		right = control;

		for (size_t i = right-1; i > left; i--)
		{
			if (vals[i - 1] > vals[i]) 
			{
				swap(i - 1, i);
				control = i;
			}
		}
		std::cout << control << ": " << (*this).status() << std::endl;
		left = control;
	}
}

template<typename Functor>
void Vector::quick_sort(Functor f)
{
	qsort_recursive(0, n-1, f);
}

template<typename Functor>
void Vector::qsort_recursive(ptrdiff_t low, ptrdiff_t high, Functor partition_template)
{
	if (low < high)
	{
		std::swap(vals[low + rand() % (high - low + 1)], vals[low]);
		ptrdiff_t p = partition_lomuto(*this, low, high);
		qsort_recursive(low, p - 1ll, partition_template);
		qsort_recursive(p + 1ll, high, partition_template);
	}
}

ptrdiff_t Vector::partition_lomuto(Vector& vec, ptrdiff_t low, ptrdiff_t high)
{
	size_t pivot = vec[high];
	size_t i = low;
	for (size_t j = low; j < high; ++j)
	{
		if (vec[j] < pivot)
		{
			std::swap(vec[i], vec[j]);
			i++;
		}
	}
	std::swap(vec[high], vec[i]);
	return i;
}

ptrdiff_t Vector::partition_hoare(Vector& vec, ptrdiff_t low, ptrdiff_t high)
{
	ptrdiff_t pivot = vec[low];
	ptrdiff_t i = low + 1;
	ptrdiff_t j = high;

	while (true)
	{
		while (pivot < vec[j]) --j;
		while (i < high + 1 && pivot > vec[i]) ++i;

		if (i < j)
		{
			std::swap(vec[i], vec[j]);
			++i; --j;
		}
		else
		{
			std::swap(vec[low], vec[j]);
			return j;
		}
	}
}

Vector* Vector::merge(Vector* B, Vector* C)
{
	size_t i = 0, j = 0, k = 0;
	size_t p = B->size();
	size_t q = C->size();
	Vector* A = new Vector(p + q);
	while (i < p && j < q)
	{
		if (B->vals[i] < C->vals[j])
		{
			A->vals[k] = B->vals[i];
			i++;
		}
		else
		{
			A->vals[k] = C->vals[j];
			j++;
		}
		k++;
	}
	while (i < p)
	{
		A->vals[k] = B->vals[i];
		i++;
	}
	while (j < q)
	{
		A->vals[k] = C->vals[j];
		j++;
	}
	return A;
}
void Vector::merge_sort()
{
	/*if (n > 1)
	{
		Vector* B = new Vector(vals, n / 2);
		Vector* C = new Vector(vals + n / 2, n / 2 + (n % 2 == 0 ? 0 : 1));

		std::cout << '\n' « B->status() « '\n' « C->status();
		B->merge_sort();
		C->merge_sort();
		*this = *(Vector().merge(B, C));
	}*/
}




void Vector::swap(size_t i, size_t j)
{
	int temp = vals[i];
	vals[i] = vals[j];
	vals[j] = temp;
}

void test_vector::test_1()
{
	Vector my_vector(10);
	std::cout << "First vector: " << std::endl  
		<<my_vector.status() << std::endl;

	Vector my_vector_copy{ my_vector };
	std::cout << "Copy through initializer list: " << std::endl 
		<< my_vector_copy.status() << std::endl;

	std::cout << "\nC++ built-in sort: " << std::endl;
	Vector vec{ my_vector };
	std::cout << "Initial state: " << std::endl;
	std::cout << vec.status() << std::endl;
	vec.sort();
	std::cout << "Sorted vector: " << std::endl;
	std::cout << vec.status() << std::endl;

	std::cout << "\nPerform bubble sort: \n";
	vec = Vector{ my_vector };
	std::cout << "Initial state: " << std::endl;
	std::cout << vec.status() << std::endl;
	std::cout << "Bubble sort steps: " << std::endl;
	vec.bubble_sort();

	std::cout << "\nPerform shaker sort: \n";
	vec = Vector{ my_vector };
	std::cout << "Initial state: " << std::endl;
	std::cout << vec.status() << std::endl;
	std::cout << "Shaker sort steps: " << std::endl;
	vec.shaker_sort();

	std::cout << "\nPerform partition Lomuto: \n";
	vec = Vector{ my_vector };
	std::cout << "Initial state: " << std::endl;
	std::cout << vec.status() << std::endl;
	std::cout << "Lomuto partitioned array from 0 to " << vec.size() << ": " << std::endl;
	size_t j = Vector::partition_lomuto(vec, 0, vec.size());
	std::cout << "with pivot at position j = " << j << std::endl;
	std::cout << "Lomuto partitioned array from " << 0 << " to " << j << ": " << std::endl;
	j = Vector::partition_lomuto(vec, 0, j);
	std::cout << "with pivot at position j = " << j << std::endl;



	std::cout << "\nPerform partition Hoare: \n";
	vec = Vector{ my_vector };
	std::cout << "Initial state: " << std::endl;
	std::cout << vec.status() << std::endl;
	std::cout << "Hoare partitioned array from 0 to " << vec.size() << ": " << std::endl;
	j = Vector::partition_hoare(vec, 0, vec.size());
	std::cout << "with pivot at position j = " << j << std::endl;
	std::cout << "Hoare partitioned array from " << j+1 << " to " << vec.size() << ": " << std::endl;
	j = Vector::partition_hoare(vec, j, vec.size());
	std::cout << "with pivot at position j = " << j << std::endl;


	std::cout << "\nPerform quick sort: \n";
	vec = Vector{ my_vector };
	std::cout << "Initial state: " << std::endl;
	std::cout << vec.status() << std::endl;
	std::cout << "Quick sort steps with Lomuto partition: " << std::endl;
	vec.quick_sort(Vector::partition_lomuto);

	std::cout << "\nPerform quick sort: \n";
	vec = Vector{ my_vector };
	std::cout << "Initial state: " << std::endl;
	std::cout << vec.status() << std::endl;
	std::cout << "Quick sort steps with Hoare partition: " << std::endl;
	vec.quick_sort(Vector::partition_hoare);

}


