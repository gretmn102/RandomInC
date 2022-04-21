// #pragma warning(disable : 4996)
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <math.h>

//////////////////////////////////////////////////////////////////////////////

/** Возвращает вещественное случайное число, равномерно распределённое на полуоткрытом интервале [a,b).
 *
 * @param a нижняя граница
 * @param b верхняя граница
 *
 * @return Случайное число от a до b (не включая верхнюю границу).
 */
double Random(double a, double b)
{
    return ((double)rand() * (b - a)) / (double)RAND_MAX + a;
}

/**
 * Заполняет массив равномерно распределёнными случайными числами.
 *
 * @param arr массив
 * @param size количество элементов в массиве
 * @param a нижняя граница
 * @param b верхняя граница(не включается в интервал)
 *
 * @see Random()
 */
void FillRandom(double arr[], int size, double a, double b)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = Random(a, b);
    }
}

/**
 * Печатает элементы массива через запятую в фигурных скобках.
 *
 * @param arr массив
 * @param size количество элементов в массиве
 */
void Print(double const arr[], int size)
{
    printf("{ ");

    for (int i = 0; i < size; i++)
    {
        printf("%f", arr[i]);

        if (i < size - 1)
        {
            printf(", ");
        }
    }

    printf(" }\n");
}

/////////////////////////////////////////////////////////////////////////////

/**
 * Строит гистограмму значений элементов массива.
 *
 * Заполняет массив `counters[]` на основании значений элементов массива `arr[]`,
 * подсчитывая, сколько их попало в соответствующий подынтервал
 * полного интервала [a,b). Элементы массива,не попадающие в указанный
 * интервал от a до b игнорируются.
 *
 * @param arr массив
 * @param size количество элементов в массиве
 * @param a нижняя граница
 * @param b верхняя граница (не включается в интервал)
 * @param counters заполняемый массив
 * @param numCounters количество подынтервалов подсчёта
 */
void BuildHistogram(double const arr[], int size,
    double histMin, double histMax, int counters[], int numCounters)
{
    double diff = (histMax - histMin) / (double)numCounters;

    double min, max;
    for (int i = 0; i < numCounters; i++)
    {
        min = histMin + ((double)i * diff);
        max = histMin + ((double)(i + 1) * diff);

        double curr;
        counters[i] = 0;
        for (int j = 0; j < size; j++)
        {
            curr = arr[j];
            if (min <= curr && curr < max)
            {
                counters[i]++;
            }
        }
    }
}

/**
 * Печатает элементы массива через запятую в фигурных скобках.
 *
 * @param counters массив
 * @param numCounters количество элементов в массиве
 */
void PrintHistogram(int counters[], int numCounters)
{
    printf("{ ");

    for (int i = 0; i < numCounters; i++)
    {
        printf("%d", counters[i]);

        if (i < numCounters - 1)
        {
            printf(", ");
        }
    }

    printf(" }\n");
}

#define HIST_CHAR_BAR 'o'
#define HIST_CHAR_SPACE 183

/**
 * Печатает горизонтальную гистограмму значений элементов массива.
 *
 * @param counters массив интервалов,содержащий количество элементов,
 * попавших в соответствующий подынтервал
 * @param numCounters количество подынтервалов подсчёта
 * @param width полная ширина поля вывода гистограммы,в знакоместах
 */
void DrawHistogram(int counters[], int numCounters, int width)
{
    int max = 0;
    for (int i = 0; i < numCounters; i++)
    {
        max = counters[i] > max ? counters[i] : max;
    }

    for (int i = 0; i < numCounters; i++)
    {
        printf("%d ", i);

        int count = counters[i] * width / max;
        for (int i = 0; i < width; i++)
        {
            if (count > 0)
            {
                printf("%c", HIST_CHAR_BAR);
                count--;
            }
            else
            {
                printf("%c", HIST_CHAR_SPACE);
            }
        }
        printf("\n");
    }
}

/**
 * Печатает вертикально гистограмму значений элементов массива.
 *
 * @param counters массив интервалов,содержащий количество элементов,
 * попавших в соответствующий подынтервал
 * @param numCounters количество подынтервалов подсчёта
 * @param width полная высота поля вывода гистограммы,в знакоместах
 */
void DrawHistogramY(int counters[], int numCounters, int height)
{
    int max = 0;
    for (int i = 0; i < numCounters; i++)
    {
        max = counters[i] > max ? counters[i] : max;
    }

    for (int row = height - 1; row >= 0; row--)
    {
        for (int counterIdx = 0; counterIdx < numCounters; counterIdx++)
        {
            int count = counters[counterIdx] * height / max;
            printf("%c ", count - row > 0 ? HIST_CHAR_BAR : HIST_CHAR_SPACE);
        }
        printf("\n");
    }

    for (int i = 0; i < numCounters; i++)
    {
        printf("%d ", i);
    }
    printf("\n");

}

//////////////////////////////////////////////////////////////////////////////

int main(void)
{
	const int PRINT_MAX = 20;
	const double RANDOM_MIN = 0.3;
	const double RANDOM_MAX = 0.75;
	const double HIST_MIN = 0.0;
	const double HIST_MAX = 1.0;
	const int HIST_LINES = 5;
	const int HIST_LENGTH = 16;

	int size = 10;
	double *numbers = NULL;
	int *hist = NULL;

	setlocale(LC_CTYPE, "Russian");

	// При желании можно рандомизировать ГПСЧ текущим числом секунд
	srand((unsigned) time(NULL));

	wprintf(L"\nВведите количество чисел: ");
	scanf("%i", &size);

	// Выделите память
	numbers = malloc(size * sizeof(double));
	hist = malloc(HIST_LINES * sizeof(int));

	// Заполните массивы
	wprintf(L"\nРавномерная СВ (первые %i чисел): \n", PRINT_MAX);
	FillRandom(numbers, size, RANDOM_MIN, RANDOM_MAX);
	Print(numbers, size < PRINT_MAX ? size : PRINT_MAX);

	// Постройте гистограмму равномерной случайной величины
	BuildHistogram(numbers, size, HIST_MIN, HIST_MAX, hist, HIST_LINES);
	PrintHistogram(hist, HIST_LINES);
	// DrawHistogram(hist, HIST_LINES, HIST_LENGTH);
	DrawHistogramY(hist, HIST_LINES, HIST_LENGTH);

	// Освободите память
	free(hist);
	free(numbers);
	return 0;
}
