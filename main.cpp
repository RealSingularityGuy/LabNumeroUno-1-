#include <iostream>
#include <cmath>

using namespace std;

struct reg_polygon {
    int count_sides;
    double length;
    double area;
    double perimeter;
    double *x;
    double *y;
};

void area_perimeter(int k ,struct reg_polygon* reg_pol, int amount, int* output);
void SetData(reg_polygon* reg_pol, int amount, int* output);                            //Внесение данных и проверка введённых значений, вычисление площади, периметра
reg_polygon* AddStruct(reg_polygon* reg_polygon, int amount);
int* AddOutput(int amount, int* output);
void menu(reg_polygon* NewPolygon, int PolygonAmount, int* output);                     //Меню
void coordinates(struct reg_polygon* reg_pol, int amount);                              //Вычисление координат
void print(reg_polygon* NewPolygon, int amount, int* output);                           //Вывод
void submenu(reg_polygon* NewPolygon, int PolygonAmount, int* output);                  //Подменю
void check(reg_polygon* NewPolygon, int PolygonAmount, int* output);                    //Подтверждение выхода


int main()
{
    reg_polygon* NewPolygon = 0;
    int PolygonAmount = 0;
    int* output = new int[PolygonAmount];
    output[0] = 1;
    cout << "########    Polygon Calculator    ########" << '\n';
    menu(NewPolygon, PolygonAmount, output);
    return 0;
}

reg_polygon* AddStruct(reg_polygon* reg_pol, int amount)
{
    if (amount == 0)
    {
        reg_pol = new reg_polygon[amount + 1];
    }
    else
    {
        reg_polygon* temp = new reg_polygon[amount + 1];
        for (int i = 0; i < amount; i++)
        {
            temp[i] = reg_pol[i];
        }
        delete[] reg_pol;

        reg_pol = temp;
    }
    return reg_pol;
}

int* AddOutput(int amount, int* output)
{

    if (amount != 0)
    {
        int* temp2 = new int[amount + 1];
        for (int i = 0; i < amount; i++)
        {
            temp2[i] = output[i];
        }
        delete[] output;
        output = temp2;
        output[amount] = 1;
    }
    return output;
}

void SetData(reg_polygon* reg_pol, int amount, int* output)
{
    cout << "Input quantity of the sides:" << '\n';
    cin >> reg_pol[amount].count_sides;

    bool flag = false;
    if (reg_pol[amount].count_sides > 2) flag = true;
    while (flag == false)
    {
        cout << "Haha, " << reg_pol[amount].count_sides << "-sided polygon lmao))" <<'\n';
        cin >> reg_pol[amount].count_sides;
        if (reg_pol[amount].count_sides > 2)
        {
            flag = true;
            break;
        }
    }

    cout << "Input length of the one side:" << '\n';
    cin >> reg_pol[amount].length;
    flag = false;

    if (reg_pol[amount].length > 0) flag = true;
    while (flag == false)
    {
        cout << "You entered the length of the side less than 0. It must be more than 0!" << '\n';
        cin >> reg_pol[amount].count_sides;
        if (reg_pol[amount].length > 0) flag = true;
    }

    //Area
    if (reg_pol[amount].length == 3) reg_pol[amount].area =  pow(reg_pol[amount].length, 2) * sqrt(3) / 4;
    if (reg_pol[amount].length == 4) reg_pol[amount].area = pow(reg_pol[amount].length, 2);
    else
    {
        reg_pol[amount].area = 0.25 * reg_pol[amount].count_sides * reg_pol[amount].length * reg_pol[amount].length * pow(tan(M_PI / ((double)reg_pol[amount].count_sides)), -1.0);
    }
    //Perimeter
    reg_pol[amount].perimeter = reg_pol[amount].count_sides * reg_pol[amount].length;


    cout << "Input coordinates of the first vertex" << '\n';
    reg_pol[amount].x = new double[ reg_pol[amount].count_sides ];
    reg_pol[amount].y = new double[ reg_pol[amount].count_sides ];

    flag = false;
    cout << "Input x:" << '\n';
    cin >> reg_pol[amount].x[0];
    cout << "Input y:" << '/n';
    cin >> reg_pol[amount].y[0];

    double pramaya = pow( pow(reg_pol[amount].x[0], 2) + pow(reg_pol[amount].y[0], 2), 0.5);
    double Radius = reg_pol[amount].length / (2 * sin(M_PI / (reg_pol[amount].count_sides)));
    if ( pramaya - Radius > 0) flag = true;
    while (flag == false)
    {
        cout << "This point should be the farthest" << '/n';
        cout << "Input x:" << '\n';
        cin >> reg_pol[amount].x[ 0];
        cout << "Input y:" << '/n';
        cin >> reg_pol[amount].y[ 0];
        pramaya = pow( pow(reg_pol[amount].x[0], 2) + pow(reg_pol[amount].y[0], 2), 0.5);
        Radius = reg_pol[amount].length / (2 * sin(M_PI / (reg_pol[amount].count_sides)));
        if ( pramaya - Radius > 0) flag = true;
    }
    cout << "It works!" << '/n';


    coordinates(reg_pol, amount);
}

void menu(reg_polygon* NewPolygon, int PolygonAmount, int* output)
{
    int chosenForDelete = 0;
    cout << '\n' << "MENU" << '\n' << '\n';
    cout << "Choose the point" << '\n';
    cout << "1 - Add polygon" << '\n';
    cout << "2 - Show polygons" << '\n';
    cout << "3 - Delete polygon" << '\n';
    cout << "4 - Area and perimeter" << '\n';
    cout << "5 - Close the program" << '\n';
    cout << '\n' << "Your input: ";

    char choice = '0';
    cin >> choice;
    int choose = int(choice)-48;
    cout << '\n';
    switch (choose)
    {
        case 1:
            NewPolygon = AddStruct(NewPolygon, PolygonAmount);
            output = AddOutput(PolygonAmount, output);
            SetData(NewPolygon, PolygonAmount, output);
            PolygonAmount++;
            break;
        case 2:
            cout << '\n';

            cout << "OK, let's look" << '\n';
                print(NewPolygon, PolygonAmount, output);
            break;
        case 3:
            cout << "Which polygon you want to delete? Input number of it: " << '\n';
            cin >> chosenForDelete;
            if (chosenForDelete > PolygonAmount)
            {
                cout << "There is no such polygon yet :( " << '\n';
            }
            else if (chosenForDelete < 1)
            {
                cout << "Error: try again! " << '\n';
            }
            else
            {
                cout << "It works!" << '\n';
                output[chosenForDelete - 1] = 0;

            }
            break;
        case 4:
            submenu(NewPolygon, PolygonAmount, output);
            break;
        case 5:
            check(NewPolygon, PolygonAmount, output);
            return;
            break;
        default:
            cout << "Not correct! Try it again" << '\n';
            break;
    }
    menu(NewPolygon, PolygonAmount, output);
    return;
}

void area_perimeter(int k ,struct reg_polygon* reg_pol, int amount, int* output)
{
    int i_max = 0;
    if (k == 1)
    {
        if (amount == 0) cout << "There are no polygons" << '/n';
        else
        {

            for (int i = 0; i < amount; i++)
            {
                if (((reg_pol[i].area - reg_pol[i_max].area) > 0) && (output[i] == 1 )) i_max = i;
            }
            for (int i = i_max; i < amount; i++)
            {
                if (((reg_pol[i].area - reg_pol[i_max].area) == 0) && (output[i] == 1 ))
                {
                    cout << i + 1 << '\t';
                }
            }
            cout << '/n';
        }
    }
    else if (k == 2)
    {
        if (amount == 0) cout << "There are no polygons" << '/n';
        else
        {
            for (int i = 0; i < amount; i++)
            {
                if (((reg_pol[i].perimeter - reg_pol[i_max].perimeter) > 0) && (output[i] == 1 )) i_max = i;
            }
            for (int i = i_max; i < amount; i++)
            {
                if (((reg_pol[i].perimeter - reg_pol[i_max].perimeter) == 0) && (output[i] == 1 ))
                {
                    cout << i + 1 << '\t';
                }
            }
            cout << '/n';
        }
    }

}

void coordinates(struct reg_polygon* reg_polygon, int amount)
{
    long double Radius = reg_polygon[amount].length / (2 * sin(M_PI / (reg_polygon[amount].count_sides)));
    long double alpha = 2 * M_PI / reg_polygon[amount].count_sides;

    if ((reg_polygon[amount].x[0] > 0) && (reg_polygon[amount].y[0] > 0))
    {
        long double phi = atan(reg_polygon[amount].y[0]/reg_polygon[amount].x[0]);
        long double Rx = Radius*cos(phi);
        long double Ry = Radius*sin(phi);
        long double O_x = reg_polygon[amount].x[0] - Rx;
        long double O_y = reg_polygon[amount].y[0] - Ry;
        for (int i = 1; i < reg_polygon[amount].count_sides; i++)
        {
            reg_polygon[amount].x[i] = O_x + Radius * cos(phi + i * alpha);
            reg_polygon[amount].y[i] = O_y + Radius * sin(phi + i * alpha);
        }
    }
    else if ((reg_polygon[amount].x[0] < 0) && (reg_polygon[amount].y[0] < 0))
    {
        long double phi = atan(reg_polygon[amount].y[0]/reg_polygon[amount].x[0]);
        long double Rx = Radius*cos(phi);
        long double Ry = Radius*sin(phi);
        long double O_x = reg_polygon[amount].x[0] + Rx;
        long double O_y = reg_polygon[amount].y[0] + Ry;
        for (int i = 1; i < reg_polygon[amount].count_sides; i++)
        {
            reg_polygon[amount].x[i] = O_x - Radius * cos(phi + i * alpha);
            reg_polygon[amount].y[i] = O_y - Radius * sin(phi + i * alpha);
        }
    }
    else if ((reg_polygon[amount].x[0] < 0 ) && (reg_polygon[amount].y[0] > 0))
    {
        long double phi = M_PI/2 + atan(reg_polygon[amount].y[0]/reg_polygon[amount].x[0]);
        long double Rx = Radius*cos(phi);
        long double Ry = Radius*sin(phi);
        long double O_x = reg_polygon[amount].x[0] + Rx;
        long double O_y = reg_polygon[amount].y[0] - Ry;
        for (int i = 1; i < reg_polygon[amount].count_sides; i++)
        {
            reg_polygon[amount].x[i] = O_x - Radius * cos(phi - i * alpha);
            reg_polygon[amount].y[i] = O_y + Radius * sin(phi - i * alpha);
        }
    }
    else if ((reg_polygon[amount].x[0] > 0) && (reg_polygon[amount].y[0] < 0))
    {
        long double phi = M_PI/2 + atan(reg_polygon[amount].y[0]/reg_polygon[amount].x[0]);
        long double Rx = Radius*cos(phi);
        long double Ry = Radius*sin(phi);
        long double O_x = reg_polygon[amount].x[0] - Rx;
        long double O_y = reg_polygon[amount].y[0] + Ry;
        for (int i = 1; i < reg_polygon[amount].count_sides; i++)
        {
            reg_polygon[amount].x[i] = O_x + Radius * cos(phi - i * alpha);
            reg_polygon[amount].y[i] = O_y - Radius * sin(phi - i * alpha);
        }
    }

    return;
}

void print(reg_polygon* reg_polygon, int amount, int* output)
{
    for (int i = 0; i < amount; i++)
    {
        if (output[i] == 1)
        {
            cout << "Polygon serial number: " << i + 1 << '\n';

            cout << "Quantity of the vertices: ";
            cout << reg_polygon[i].count_sides << '\n';

            cout << "Coordinates of vertexes: " << '\n';
            for (int j = 0; j < reg_polygon[i].count_sides; j++)
            {
                cout << "x" << j << ": " << reg_polygon[i].x[j] << '\n';
                cout << "y" << j << ": " << reg_polygon[i].y[j] << '\n' << '\n';
            }

            cout << "Area = " << reg_polygon[i].area << '\n';
            cout << "Perimeter= " << reg_polygon[i].perimeter << '\n';

            cout << "It works!" << '\n' << '\n' << '\n';
        }
        else
        {
            for (int i = 0; i < 7; i++) cout << '\n';
        }
    }
    return;
}

void submenu(reg_polygon* NewPolygon, int PolygonAmount, int* output)
{
    int k;
    cout << "What are you going to do?" << '\n';
    cout << "1 - Max Area" << '/n' << "2 - Max Perimeter"  << '/n' << "3 - quit" << '/n';
    cin >> k;

    switch (k)
    {
        case 1:
            cout << "Let's look" << '/n' << "-----------------------" << '/n';
            area_perimeter(k , NewPolygon, PolygonAmount, output);
            cout << "That's all" << '\n';
            break;
        case 2:
            cout << "Let's look" << '/n' << "-----------------------" << '/n';
            area_perimeter(k , NewPolygon, PolygonAmount, output);
            cout << "That's all" << '\n';

            break;
        case 3:
            break;
        default:
            cout << "Incorrect! Try again" << '\n';
            submenu(NewPolygon, PolygonAmount, output);
            break;
    }
    return;
}

void check(reg_polygon* NewPolygon, int PolygonAmount, int* output)
{
    cout << "Are you sure that you want to quit? (1 - yes; 0 - no)" << '\n';
    int k;
    cin >> k;
    switch (k)
    {
        case 1:
            return;
            break;
        case 0:
            menu(NewPolygon, PolygonAmount, output);
            break;
        default:
            cout << "Incorrect! Try again" << '\n';
            check(NewPolygon, PolygonAmount, output);
            break;
    }
    return;
}
