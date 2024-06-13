#include "class.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// Конструктор клиента
Customer::Customer(const string& name, float discount)
    : name(name), discount(discount) {}

// Геттер для величины скидки
float Customer::getDiscount() const
{
    return discount;
}

// Геттер для имени клиента
string Customer::getName() const
{
    return name;
}

// Сеттер для имени клиента с проверкой на пустое значение
void Customer::setName(const string& newName)
{
    if (!newName.empty())
    {
        name = newName;
    }
    else
    {
        cerr << "Ошибка: имя не может быть пустым." << endl;
    }
}

// Сеттер для величины скидки с проверкой на отрицательное значение
void Customer::setDiscount(float newDiscount)
{
    if (newDiscount >= 0.0f)
    {
        discount = newDiscount;
    }
    else
    {
        cerr << "Ошибка: скидка не может быть отрицательной." << endl;
    }
}

// Конструктор заказа
Order::Order(int id, const Customer& customer, const vector<string>& books)
    : id(id), customer(customer), books(books) {}

// Геттер для id заказа
int Order::getId() const
{
    return id;
}

// Геттер для клиента, сделавшего заказ
Customer Order::getCustomer() const
{
    return customer;
}

// Геттер для списка заказанных книг
vector<string> Order::getBooks() const
{
    return books;
}

// Метод для добавления книги к заказу
void Order::addBook(const string& newBook)
{
    if (!newBook.empty())
    {
        books.push_back(newBook);
    }
    else
    {
        cerr << "Ошибка: название книги не может быть пустым." << endl;
    }
}

// Добавление заказа в книжный магазин
void Bookstore::addOrder(const Order& order)
{
    orders.push_back(order);
}

// Удаление заказа из книжного магазина по id
void Bookstore::removeOrder(int orderId)
{
    orders.erase(remove_if(orders.begin(), orders.end(), [orderId](const Order& order)
        { return order.getId() == orderId; }),
        orders.end());
}

// Поиск заказов по величине скидки
vector<Order> Bookstore::findOrdersByDiscount(float discount) const
{
    vector<Order> result;
    for (const auto& order : orders)
    {
        if (order.getCustomer().getDiscount() == discount)
        {
            result.push_back(order);
        }
    }
    return result;
}

// Чтение данных из файла и заполнение заказов
void Bookstore::readDataFromFile(const string& filename)
{
    ifstream infile(filename);
    if (!infile.is_open())
    {
        cerr << "Ошибка открытия файла " << filename << endl;
        return;
    }

    orders.clear(); // Очищаем текущие заказы перед загрузкой новых данных

    string line;
    while (getline(infile, line))
    {
        // Используем stringstream для разбора строки по запятым
        stringstream ss(line);
        string segment;
        vector<string> segments;

        while (getline(ss, segment, ','))
        {
            segments.push_back(segment);
        }

        // Проверяем, что мы успешно получили все необходимые сегменты данных
        if (segments.size() < 4)
        {
            cerr << "Ошибка чтения данных из файла: недостаточно данных" << endl;
            continue;
        }

        // Извлекаем данные из сегментов
        int orderId = stoi(segments[0]);
        string name = segments[1];
        float discount = stof(segments[2]);

        // Список заказанных книг начинается с третьего элемента в segments
        vector<string> books;
        for (size_t i = 3; i < segments.size(); ++i)
        {
            books.push_back(segments[i]);
        }

        // Создаем объекты и добавляем в хранилище заказов
        Customer customer(name, discount);
        Order order(orderId, customer, books);
        addOrder(order);
    }

    infile.close(); // Закрываем файл после чтения
}

// Запись данных заказов в файл
void Bookstore::writeOrdersToFile(const string& filename, const vector<Order>& orders, bool append) const
{
    ofstream outfile;
    if (append)
    {
        outfile.open(filename, ios_base::app); // Открыть файл для добавления в конец
    }
    else
    {
        outfile.open(filename); // Перезаписать файл
    }

    for (const auto& order : orders)
    {
        // Записываем id заказа, имя клиента, величину скидки и список книг через пробел
        outfile << order.getId() << " " << order.getCustomer().getName() << " "
            << order.getCustomer().getDiscount() << " ";
        for (const auto& book : order.getBooks())
        {
            outfile << book << " ";
        }
        outfile << endl;
    }
}

// Функция для интерактивного добавления заказа
void addOrderInteractively(Bookstore& bookstore)
{
    int orderId;
    float discount;
    string name, book;
    vector<string> books;

    cout << "Введите ID заказа: ";
    while (!(cin >> orderId))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "Ошибка: введите целое число." << endl;
        cout << "Введите ID заказа: ";
    }
    cin.ignore(); // Очищаем буфер ввода

    cout << "Введите имя клиента: ";
    getline(cin, name);

    cout << "Введите скидку: ";
    while (!(cin >> discount) || discount < 0.0f)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "Ошибка: введите положительное число." << endl;
        cout << "Введите скидку: ";
    }
    cin.ignore(); // Очищаем буфер ввода

    cout << "Введите названия книг (через пробел): ";
    getline(cin, book);
    istringstream iss(book);
    while (iss >> book)
    {
        books.push_back(book);
    }

    Customer customer(name, discount);
    Order order(orderId, customer, books);
    bookstore.addOrder(order);
}

// Функция для интерактивного удаления заказа по ID
void removeOrderInteractively(Bookstore& bookstore)
{
    int orderId;
    cout << "Введите ID заказа для удаления: ";
    while (!(cin >> orderId))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "Ошибка: введите целое число." << endl;
        cout << "Введите ID заказа для удаления: ";
    }
    bookstore.removeOrder(orderId);
}
