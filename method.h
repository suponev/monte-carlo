//Число pi:
    const double pi = 3.1415;
    //Рабочие переменные программы:
    double R, H, V, V0, x, y, z;
    //Число точек N (по каждой из координат)
    //и число внутренних точек n:
    int N = 10, n = 0;
    //Ввод параметров R и H:
    double X, Y, Z;
    double R_O = 60;
    double R_H = 52.9;
    X = 2 * R_H + 2 * 75.754;
    Y = R_O + R_H + 58.708;
    Z = 2 * R_O;
    //Объем параллелепипеда:
    V0 = X * Y * Z;
    //Перебор всех точек:
    for (int i = 0; i <= N; i++)
    {
        x = i * X / N;
        for (int j = 0; j <= N; j++)
        {
            y = j * Y / N;
            for (int k = 0; k <= N; k++)
            {
                z = k * Z / N;
                //Подсчет внутренних точек:
                if (water(x, y, z))
                {
                    n++;
                }
            }
        }
    }
    //Объем тела:
    V = V0 * n / pow(N + 1, 3);
    //Вывод вычисленного и точного значений:
    printf("V = %lf\n", V);
    printf("V_0 = %lf\n", V0);

    return 0;

    bool water(double x, double y, double z)
{
    double R_O = 60;
    double R_H = 52.9;
    if ((x <= 128.654 + R_O) && (x >= 128.654 - R_O))
    {
        if ((y <= 60 + R_O) && (y >= 60 - R_O))
        {
            if ((z <= 60 + R_O) && (z >= 60 - R_O))
            {
                return true;
            }
        }
    }
    return false;
}