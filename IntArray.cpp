#include "intArray.h"

IntArray::IntArray(const int &size)
{
    arr = new int[size];
    arr_size = size;
}

IntArray::~IntArray()
{
    delete [] arr;
}

void IntArray::fillArray(int min, int max)
{
	srand(time(NULL));

	for (auto i{ 0 }; i < arr_size; i++)
	{
		arr[i] = min + rand() % (abs(min) + abs(max) + 1);
	}
}

void IntArray::printArray(int width)
{
	for (auto i{ 0 }; i < arr_size; i++)
	{
		if (i % width == 0)
			std::cout << std::endl;

		std::cout << std::setw(4) << arr[i] << ',';
	}
}

void IntArray::QsortNoThreads()
{
    std::cout << std::endl << "\033[32m QsortNoThreads\033[0m" << std::endl;
    time_spend(QsortNoThreads, this->arr, 0, this->arr_size);
}

void IntArray::QsortThreads()
{
    std::cout << std::endl << "\033[32m QsortThreads\033[0m" << std::endl;
    time_spend(QsortThreads, this->arr, 0, this->arr_size);
}

void IntArray::QsortThreadsPool()
{
    std::cout << std::endl << "\033[32m QsortThreadsPool\033[0m" << std::endl;
    time_spend(QsortThreadsPool, this->arr, 0, this->arr_size);
}

void IntArray::QsortNoThreads(int *array, long left, long right)
{
    if(left >= right) return;

    long left_bound = left;
    long right_bound = right;
    long middle = array[(left_bound + right_bound) / 2];

    do 
    {
        while(array[left_bound] < middle) 
            left_bound++;

        while(array[right_bound] > middle) 
            right_bound--;

        if (left_bound <= right_bound) 
        {
            std::swap(array[left_bound], array[right_bound]);
            left_bound++;
            right_bound--;
        }
    } 
    while (left_bound <= right_bound);

    QsortNoThreads(array, left, right_bound);
    QsortNoThreads(array, left_bound, right);
}

void IntArray::QsortThreads(int *array, long left, long right)
{
    if (left >= right) return;

    int left_bound = left;
    int right_bound = right;
    int middle = array[(left_bound + right_bound) / 2];

    do
    {
        while (array[left_bound] < middle) 
            left_bound++;

        while (array[right_bound] > middle) 
            right_bound--;

        if (left_bound <= right_bound)
        {
            std::swap(array[left_bound], array[right_bound]);
            left_bound++;
            right_bound--;
        }

    }
    while (left_bound <= right_bound);

    if ((right_bound - left) > PART_SIZE)
    {
        auto f = async(launch::async, [&]() {QsortThreads(array, left, right_bound);});
        QsortThreads(array, left_bound, right);
    }
    else 
    {
        QsortThreads(array, left, right_bound);
        QsortThreads(array, left_bound, right);
    }
}

void IntArray::QsortThreadsPool(int *array, long left, long right)
{
    if (left >= right) return;

    int left_bound = left;
    int right_bound = right;
    int middle = array[(left_bound + right_bound) / 2];

    do
    {
        while (array[left_bound] < middle) 
            left_bound++;

        while (array[right_bound] > middle) 
            right_bound--;

        if (left_bound <= right_bound)
        {
            std::swap(array[left_bound], array[right_bound]);
            left_bound++;
            right_bound--;
        }

    }
    while (left_bound <= right_bound);

    std::shared_ptr<std::promise<void>> promise = std::make_shared<std::promise<void>>();
    if ((right_bound - left) > PART_SIZE)
    {
        rh.pushRequest(&IntArray::quicksort_part, this, std::ref(array), left, right_bound, promise);
        QsortThreadsPool(array, left_bound, right);
    }
    else 
    {
        QsortThreadsPool(array, left, right_bound);
        QsortThreadsPool(array, left_bound, right);
    }
}

void IntArray::quicksort_part(int* array, long left, long right, std::shared_ptr<std::promise<void>> promise)
{
    std::future<void> f = std::async(std::launch::async, [&]() { QsortThreads(arr, left, right); });
    f.wait();
    promise->set_value();
}

void IntArray::time_spend(void (IntArray::*func)(int*, long, long), int* arr, long left, long right)
{
    auto begin = std::chrono::steady_clock::now();
    (this->*func)(arr, left, right);
    auto end = std::chrono::steady_clock::now();

    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(end - begin).count();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();

    std::cout << "Time spended: seconds       = " << seconds << std::endl;
    std::cout << "              milliseconds  = " << milliseconds - seconds * 1000 << std::endl;
    std::cout << "              microseconds  = " << microseconds - milliseconds * 1000 << std::endl;
    std::cout << "              nanoseconds   = " << nanoseconds - microseconds * 1000 << std::endl;
}