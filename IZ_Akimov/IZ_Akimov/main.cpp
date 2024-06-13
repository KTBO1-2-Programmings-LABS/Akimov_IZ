#include <iostream>
#include "class.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian"); // Установка локали для вывода на русском языке
    Bookstore bookstore;
    bookstore.readDataFromFile("input.txt"); // Чтение данных из файла input.txt при запуске программы

    bool running = true;
    while (running)
    {
        // Вывод меню пользователю
        cout << "\nМеню:\n"
            << "1. Найти заказы по скидке\n"
            << "2. Добавить новый заказ\n"
            << "3. Удалить заказ\n"
            << "4. Сохранить и выйти\n"
            << "Выберите опцию: ";

        int choice;
        while (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Ошибка: введите целое число." << endl;
            cout << "Выберите опцию: ";
        }
        cin.ignore(); // Игнорируем символ новой строки после ввода числа

        switch (choice)
        {
        case 1:
        {
            float targetDiscount;
            cout << "Введите значение скидки для поиска заказов: ";
            while (!(cin >> targetDiscount) || targetDiscount < 0.0f)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << "Ошибка: введите положительное число." << endl;
                cout << "Введите значение скидки для поиска заказов: ";
            }
            cin.ignore(); // Игнорируем символ новой строки после ввода числа

            // Поиск заказов по введенной скидке
            auto foundOrders = bookstore.findOrdersByDiscount(targetDiscount);
            if (foundOrders.empty())
            {
                cout << "Заказы с скидкой " << targetDiscount << " не найдены" << endl;
            }
            else
            {
                // Записываем найденные заказы в файл output.txt
                bookstore.writeOrdersToFile("output.txt", foundOrders, false);
                cout << "Заказы с скидкой " << targetDiscount << " записаны в output.txt" << endl;
            }
            break;
        }
        case 2:
            addOrderInteractively(bookstore); // Функция для интерактивного добавления нового заказа
            break;
        case 3:
            removeOrderInteractively(bookstore); // Функция для интерактивного удаления заказа
            break;
        case 4:
            // Записываем все заказы в файл input.txt перед завершением программы
            bookstore.writeOrdersToFile("input.txt", bookstore.findOrdersByDiscount(-1), true);
            running = false; // Выход из цикла, завершение работы программы
            break;
        default:
            cerr << "Недопустимый выбор. Попробуйте снова." << endl;
        }
    }

    return 0;
}
