// CppChessKnightProject.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <iomanip>

const int size{ 8 };

const int offset[8][2]
{
    {-2, 1},
    {-1, 2},
    {1, 2},
    {2, 1},
    {2, -1},
    {1, -2},
    {-1, -2},
    {-2, -1}
};

void DeskPrint(int desk[][size]);
bool InDesk(int row, int column);
int WeightCalculate(int desk[][size], int row, int column);
int WeightMin(int weights[], int size);

void KnightRiding(int rowCurrent, int columnCurrent);


int main()
{
    int desk[size][size]{};
    DeskPrint(desk);
    
    int vars{};

    for(int row{}; row < size; row++)
        for (int column{}; column < size; column++)
        {
            std::cout << "----- " << ++vars << " -----\n";
            KnightRiding(row, column);
            std::cout << "\n";
        }

    
}


void DeskPrint(int desk[][size])
{
    for (int row{}; row < size; row++)
    {
        for (int column{}; column < size; column++)
            std::cout << std::setw(3) << desk[row][column];
        std::cout << "\n";
    }
        
    std::cout << "\n";
}

bool InDesk(int row, int column)
{
    return row >= 0 && row < size 
        && column >= 0 && column < size;
}

int WeightCalculate(int desk[][size], int row, int column)
{
    int weight{};

    for (int i{}; i < 8; i++)
    {
        int rowOffset{ row + offset[i][0] };
        int columnOffset{ column + offset[i][1] };
        if (InDesk(rowOffset, columnOffset))
            if (!desk[rowOffset][columnOffset])
                weight++;
    }

    return weight;
}

int WeightMin(int weights[], int size)
{
    int index;
    
    for (index = 0; index < size; index++)
        if (weights[index])
            break;
    for (int i{ index + 1 }; i < size; i++)
        if (weights[i] != 0)
            if(weights[i] <= weights[index])
                index = i;
    
    return index;
}

void KnightRiding(int rowCurrent, int columnCurrent)
{
    int desk[size][size]{};
    int step{};

    desk[rowCurrent][columnCurrent] = ++step;

    while (step < 63)
    {
        int weights[8]{};
        for (int i{}; i < 8; i++)
        {
            int rowOffset = rowCurrent + offset[i][0];
            int columnOffset = columnCurrent + offset[i][1];

            if (InDesk(rowOffset, columnOffset))
            {
                if (!desk[rowOffset][columnOffset])
                    weights[i] = WeightCalculate(desk, rowOffset, columnOffset);
            }
        }
        int indexMin{ WeightMin(weights, 8) };

        rowCurrent += offset[indexMin][0];
        columnCurrent += offset[indexMin][1];
        desk[rowCurrent][columnCurrent] = ++step;
    }

    for (int i{}; i < 8; i++)
    {
        int rowOffset = rowCurrent + offset[i][0];
        int columnOffset = columnCurrent + offset[i][1];

        if (InDesk(rowOffset, columnOffset))
            if (!desk[rowOffset][columnOffset])
            {
                desk[rowOffset][columnOffset] = ++step;
                break;
            }
    }

    DeskPrint(desk);
}
