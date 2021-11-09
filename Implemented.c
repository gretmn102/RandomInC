// #pragma warning(disable : 4996)
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <math.h>

//////////////////////////////////////////////////////////////////////////////

/** ���������� ������������ ��������� �����, ���������� ������������� �� ������������ ��������� [a,b).
 *
 * @param a ������ �������
 * @param b ������� �������
 *
 * @return ��������� ����� �� a �� b (�� ������� ������� �������).
 */
double Random(double a, double b)
{
    return ((double)rand() * (b - a)) / (double)RAND_MAX + a;
}

/**
 * ��������� ������ ���������� �������������� ���������� �������.
 *
 * @param arr ������
 * @param size ���������� ��������� � �������
 * @param a ������ �������
 * @param b ������� �������(�� ���������� � ��������)
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
 * �������� �������� ������� ����� ������� � �������� �������.
 *
 * @param arr ������
 * @param size ���������� ��������� � �������
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
 * ������ ����������� �������� ��������� �������.
 *
 * ��������� ������ `counters[]` �� ��������� �������� ��������� ������� `arr[]`,
 * �����������, ������� �� ������ � ��������������� �����������
 * ������� ��������� [a,b). �������� �������,�� ���������� � ���������
 * �������� �� a �� b ������������.
 *
 * @param arr ������
 * @param size ���������� ��������� � �������
 * @param a ������ �������
 * @param b ������� ������� (�� ���������� � ��������)
 * @param counters ����������� ������
 * @param numCounters ���������� ������������� ��������
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
 * �������� �������� ������� ����� ������� � �������� �������.
 *
 * @param counters ������
 * @param numCounters ���������� ��������� � �������
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
 * �������� �������������� ����������� �������� ��������� �������.
 *
 * @param counters ������ ����������,���������� ���������� ���������,
 * �������� � ��������������� �����������
 * @param numCounters ���������� ������������� ��������
 * @param width ������ ������ ���� ������ �����������,� �����������
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

	// ��� ������� ����� ��������������� ���� ������� ������ ������
	srand((unsigned) time(NULL));

	printf("\n������� ���������� �����: ");
	scanf("%i", &size);

	// �������� ������
	numbers = malloc(size * sizeof(double));
	hist = malloc(HIST_LINES * sizeof(int));

	// ��������� �������
	printf("\n����������� �� (������ %i �����): \n", PRINT_MAX);
	FillRandom(numbers, size, RANDOM_MIN, RANDOM_MAX);
	Print(numbers, size < PRINT_MAX ? size : PRINT_MAX);

	// ��������� ����������� ����������� ��������� ��������
	BuildHistogram(numbers, size, HIST_MIN, HIST_MAX, hist, HIST_LINES);
	PrintHistogram(hist, HIST_LINES);
	DrawHistogram(hist, HIST_LINES, HIST_LENGTH);

	// ���������� ������
	free(hist);
	free(numbers);
	return 0;
}
