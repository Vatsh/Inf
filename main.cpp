#include "math.h"
#include "stdio.h"
#include "locale.h"

// хорошим стилем является наименование функций глаголом. В данном случае название начинается с get
int getPositiveInteger();
float getDouble(double boundLower, double boundUpper);
double getEntropyEq(int n);
double getEntropyNotEq(int n);
double getRedundancy(double entropyEq, double entropy);

int main()
{
    setlocale(LC_CTYPE, "rus");
    int variant = 0, n = 0;
    double entropyEq = 0, entropy = 0, redundancy = 0;

    printf("%s\n", "Введите размер алфавита");
    n = getPositiveInteger();

    do
    {
        printf("%s\n", " -------------------------------");
        printf("%s\n", "|1. Энтропия (равновероятная).  |");
        printf("%s\n", "|2. Энтропия (неравновероятная).|");
        printf("%s\n", "|3. Избыточность.               |");
        printf("%s\n", "|4. Выход.                      |");
        printf("%s\n", " -------------------------------");

        printf("%s\n", "Выберите действие: ");
        variant = getPositiveInteger();
        switch(variant)
        {
            case 1:
                entropyEq = getEntropyEq(n);
                printf("Энтропия H = %lf бит/эл\n", entropyEq);
                break;
            case 2:
                entropy = getEntropyNotEq(n);
                printf("Энтропия H = %lf бит/эл\n", entropy);
                break;
            case 3:
                redundancy = getRedundancy(entropyEq, entropy);
                if (redundancy == -1)
                    printf("%s\n", "Надостаточно данных. Выполните все пункты меню.");
                else
                    printf("Избыточность алфавита: %lf\n", redundancy);
                break;
            case 4:
                printf("%s\n", "Завершение...");
                break;
            default:
                printf("%s\n", "Введите, пожалуйста, существующий пункт меню.");
        }
    } while(variant != 4);
    getchar();

    return 0;
}

int getPositiveInteger()
{
    int number = 0;
    while (scanf("%d", &number) != 1 || number < 1) {
        printf("%s\n", "Введите положительное целое число: ");
        while (getchar() != '\n');
    }
    return number;
}

float getDouble(double boundLower = 1E-100, double boundUpper = 1)
{
    double number = 0;
    while (scanf("%lf", &number) != 1 || number < boundLower || number > boundUpper) {
        printf("Введите число от %lf до %lf: ", boundLower, boundUpper);
        while (getchar() != '\n');
    }
    return number;
}

double getEntropyEq(int n)
{
    return log10(n) / log10(2);
}

double getEntropyNotEq(int n)
{
    double entropy = 0;

    printf("%s\n", "Введите ....  [пример: 0.09]");
    for (int i = 0; i < n; i++)
    {
        printf("p[%d] = ", i + 1);
        double p = getDouble();
        entropy = entropy + (-p * (log10(p) / log10(2)));
    }
    return entropy;
}

double getRedundancy(double entropyEq, double entropy)
{
    if (entropyEq == 0 || entropy == 0)
        return -1;

    return ((entropyEq - entropy) / entropyEq) * 100;
}

