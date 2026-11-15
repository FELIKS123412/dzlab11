#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#define COUNT 3 

struct Busroute {
    int number;
    char startroad[30];
    char stoproad[30];
    double length;
    int stopcount;
};

double calculate_distance(double length, int stopcount);
void print_route(struct Busroute r, double distance);
void process_routes(struct Busroute routes[], int count, double threshold);

int main() {
    struct Busroute routes[COUNT];
    double treshholdvalue;
    int i;

    setlocale(LC_ALL, "RUS");

    printf("Программа для учёта автобусных маршрутов\n\n");

    for (i = 0; i < COUNT; i++) {
        printf("Ввод данных для маршрута %d:\n", i + 1);
        printf("Введите номер маршрута: ");
        scanf("%d", &routes[i].number);

        printf("Введите начальную остановку: ");
        scanf("%29s", routes[i].startroad);

        printf("Введите конечную остановку: ");
        scanf("%29s", routes[i].stoproad);

        printf("Введите длину маршрута (км): ");
        scanf("%lf", &routes[i].length);

        printf("Введите количество остановок: ");
        scanf("%d", &routes[i].stopcount);
        printf("\n");
    }

    printf("Введите значение среднего расстояния в км: ");
    scanf("%lf", &treshholdvalue);
    printf("\n");

    process_routes(routes, COUNT, treshholdvalue);

    return 0;
}

double calculate_distance(double length, int stopcount) {
    if (stopcount <= 1) {
        return 0.0;
    }

    return length / (double)(stopcount - 1);
}

void print_route(struct Busroute r, double distance) {
    printf("  Номер маршрута: %d\n", r.number);
    printf("  Начальная остановка: %s\n", r.startroad);
    printf("  Конечная остановка: %s\n", r.stoproad);
    printf("  Длина маршрута: %.2lf км\n", r.length);
    printf("  Количество остановок: %d\n", r.stopcount);
    printf("  Среднее расстояние между остановками: %.2lf км\n", distance);
}

void process_routes(struct Busroute routes[], int count, double threshold) {
    int i;
    int found = 0;
    double dist;

    printf("--- Все записи маршрутов ---\n");
    for (i = 0; i < count; i++) {
        dist = calculate_distance(routes[i].length, routes[i].stopcount);
        printf("\nМаршрут %d:\n", i + 1);
        print_route(routes[i], dist);
    }

    printf("\n--- Маршруты, где среднее расстояние меньше %.2lf км ---\n", threshold);
    for (i = 0; i < count; i++) {
        
        dist = calculate_distance(routes[i].length, routes[i].stopcount);

        if (dist < threshold && routes[i].stopcount > 1) {
            printf("\nМаршрут %d:\n", i + 1);
            print_route(routes[i], dist);
            found++;
        }
    }

    if (found == 0) {
        printf("Маршрутов, удовлетворяющих заданному условию, не найдено.\n");
    }
}