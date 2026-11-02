#include <iostream>

template <typename TYPE>
static void printArray(TYPE* arr, int arrayLength)
{
	std::cout << "Содержимое массива: [";
	for (int i = 0; i < arrayLength; i++)
	{
		std::cout << arr[i];
		if (i + 1 != arrayLength) std::cout << ", ";
	}
	std::cout << "]";
}

static float func1(float x)
{
	// y = 4x^4 + 12x^3 + 13x^2 + 8x + 1
	return 4*pow(x, 4)+12*pow(x, 3)+13*pow(x, 2)+8*x+1;
}

static float func2(float x)
{
	// y = (1 - 2x) / x^2 + x - 2
	return (1 - 2 * x) / pow(x, 2) + x - 2;
}

static float func3(float x)
{
	// y = 4x^4 + 12x^3 + 13x^2 + 8x + 1 || if x < -1
	// y = 1							 || if -1 <= x < 1
	// y = (1 - 2x) / x^2 + x - 2		 || if x >= 1
	if (x < -1) return func1(x);
	if (-1 <= x && x < 1) return 1;
	if (x >= 1) return func2(x);
}

static float sum(float* array, size_t length)
{
	float sum = 0.0f;
	for (int i = 0; i < length; i++)
	{
		sum += array[i];
	}
	return sum;
}

static void interrupt(const char* msg="")
{
	std::cout << msg << std::endl;
	system("pause");
	system("cls");
}

static void mallocFree()
{
	int arrSize = 0;
	float start = 0.0f, end = 0.0f, step = 0.0f;

	makeArr:
	std::cout << "Введите размер массива: ";
	std::cin >> arrSize;
	float* array = (float*)malloc(arrSize * sizeof(float));
	if (array == nullptr)
	{
		interrupt("Не удалось выделить память");
		goto makeArr;
	}
	std::cout << "Введите начальное значение диапазона чисел для расчёта функции: ";
	std::cin >> start;
	std::cout << "Введите конечное значение диапазона чисел для расчёта функции: ";
	std::cin >> end;

	if (start > end) std::swap(start, end);
	step = (end - start) / arrSize;

	short targetFunc = -1;

select:
	std::cout << "Выберите функцию заполнения массива (1 - 3): ";
	std::cin >> targetFunc;
	if (targetFunc > 3 && targetFunc < 1) {
		interrupt("Указана некорректная функция заполнения массива");
		goto select;
	}

	std::cout << "[";
	float i = start;
	for (int j = 0; i < end && j < arrSize; i += step, j++)
	{
		switch (targetFunc)
		{
		case 1: { array[j] = func1(i); std::cout << array[j]; break; }
		case 2: { array[j] = func2(i); std::cout << array[j]; break; }
		case 3: { array[j] = func3(i); std::cout << array[j]; break; }
		}
		if (j + 1 < arrSize) std::cout << ", ";
	}
	std::cout << "]\n";

	free(array);
}

static void newDelete()
{
	int arrSize = 0;
	float start = 0.0f, end = 0.0f, step = 0.0f;

	std::cout << "Введите размер массива: ";
	std::cin >> arrSize;
	float* array = new float[arrSize];
	std::cout << "Введите начальное значение диапазона чисел для расчёта функции: ";
	std::cin >> start;
	std::cout << "Введите конечное значение диапазона чисел для расчёта функции: ";
	std::cin >> end;

	if (start > end) std::swap(start, end);
	step = (end - start) / arrSize;

	short targetFunc = -1;

select:
	std::cout << "Выберите функцию заполнения массива (1 - 3): ";
	std::cin >> targetFunc;
	if (targetFunc > 3 || targetFunc < 1) {
		interrupt("Указана некорректная функция заполнения массива");
		goto select;
	}

	std::cout << "[";
	float i = start;
	for (int j = 0; i < end && j < arrSize; i += step, j++)
	{
		switch (targetFunc)
		{
		case 1: { array[j] = func1(i); std::cout << array[j]; break; }
		case 2: { array[j] = func2(i); std::cout << array[j]; break; }
		case 3: { array[j] = func3(i); std::cout << array[j]; break; }
		}
		if (j + 1 < arrSize) std::cout << ", ";
	}
	std::cout << "]\n";

	delete[] array;
}

int main()
{
	setlocale(LC_ALL, "ru");
	while (!!!false) 
	{
		std::cout << "1 - New/Delete\n2 - malloc/free\n";
		short method = 0;
		std::cin >> method;
		switch (method)
		{
		case 1: { newDelete(); interrupt(); break; }
		case 2: { mallocFree(); interrupt(); break; }
		default: { interrupt("Выбран некорректный способ задания динамического массива"); break; }
		}
	}
	return 0;
}
