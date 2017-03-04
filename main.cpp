#include "math.h"
#include "stdio.h"
#include "locale.h"

int getPositiveInteger();
int getBitness(int srcAlphabetLength, int codeAlphabetLength);
float getDouble(double boundLower, double boundUpper);
double getEntropyEq(int n);
double getEntropyNotEq(int n);
double getRedundancy(double entropyEq, double entropy);
double getAverageLenghtCodeword(int n);

int main()
{
    setlocale(LC_CTYPE, "rus");
    int variant = 0, alphabetSrcLenght = 0, alphabetCodeLenght = 0, bitness = 0;
    double entropyEq = 0, entropy = 0, redundancy = 0, avrgLenghtCodeword = 0;

    printf("%s\n", "Введите размер алфавита");
    alphabetSrcLenght = getPositiveInteger();

    do
    {
        printf("%s\n", " -------------------------------");
        printf("%s\n", "|1. Энтропия (равновероятная).  |");
        printf("%s\n", "|2. Энтропия (неравновероятная).|");
        printf("%s\n", "|3. Избыточность.               |");
        printf("%s\n", "|                               |");
        printf("%s\n", "|4. Разрядность.                |");
        printf("%s\n", "|5. Средняя длина код. слова.   |");
        printf("%s\n", "|                               |");
        printf("%s\n", "|6. Выход.                      |");
        printf("%s\n", " -------------------------------");

        printf("%s\n", "Выберите действие: ");
        variant = getPositiveInteger();
        switch(variant)
        {
            case 1:
                entropyEq = getEntropyEq(alphabetSrcLenght);
                printf("Энтропия H = %lf бит/эл\n", entropyEq);
                break;
            case 2:
                entropy = getEntropyNotEq(alphabetSrcLenght);
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
                printf("%s\n", "Введите размер кодового алфавита");
                alphabetCodeLenght = getPositiveInteger();
                bitness = getBitness(alphabetSrcLenght, alphabetCodeLenght);
                printf("Минимальная разрядность кодового слова r = %d симв.\n", bitness);
                break;
            case 5:
                avrgLenghtCodeword = getAverageLenghtCodeword(alphabetSrcLenght);
                printf("Средняя длина кодового слова l = %lf симв.\n", avrgLenghtCodeword);
                break;
            case 6:
                printf("%s\n", "Завершение...");
                break;
            default:
                printf("%s\n", "Введите, пожалуйста, существующий пункт меню.");
        }
    } while(variant != 6);
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

    printf("%s\n", "Введите ....  [пример: 0,09]");
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

double getAverageLenghtCodeword(int n)
{
    double length = 0;

    printf("%s\n", "Введите ....  [пример: 0,09]");
    for (int i = 0; i < n; i++)
    {
        printf("l[%d] = ", i + 1);
        int l = getPositiveInteger();
        printf("p[%d] = ", i + 1);
        double p = getDouble();
        length = length + (l * p);
    }
    return length;
}

int getBitness(int srcAlphabet, int codeAlphabet)
{
    double bit = log(srcAlphabet) / log(codeAlphabet);
    if (bit - (int)bit != 0)
        return (int)bit + 1;
    else
        return bit;
}
