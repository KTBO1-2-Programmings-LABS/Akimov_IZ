#ifndef CLASS_H
#define CLASS_H

#include <string>
#include <vector>

using namespace std;

// Класс, представляющий клиента
class Customer
{
private:
    string name;    // Имя клиента
    float discount; // Величина скидки клиента

public:
    // Конструктор клиента
    Customer(const string& name, float discount);

    // Геттеры для имени и скидки
    string getName() const;
    float getDiscount() const;

    // Сеттеры для имени и скидки
    void setName(const string& newName);
    void setDiscount(float newDiscount);
};

// Класс, представляющий заказ на книги
class Order
{
private:
    int id;            // Идентификатор заказа
    Customer customer; // Клиент, сделавший заказ
    vector<string> books; // Список заказанных книг

public:
    // Конструктор заказа
    Order(int id, const Customer& customer, const vector<string>& books);

    // Геттеры для id, клиента и списка книг
    int getId() const;
    Customer getCustomer() const;
    vector<string> getBooks() const;

    // Метод для добавления книги к заказу
    void addBook(const string& newBook);
};

// Класс, представляющий книжный магазин
class Bookstore
{
private:
    vector<Order> orders; // Список заказов в книжном магазине

public:
    // Методы для управления заказами
    void addOrder(const Order& order); // Добавление заказа в список
    void removeOrder(int orderId);     // Удаление заказа по id
    vector<Order> findOrdersByDiscount(float discount) const; // Поиск заказов по величине скидки

    // Методы для работы с файлами
    void readDataFromFile(const string& filename); // Чтение данных из файла
    void writeOrdersToFile(const string& filename, const vector<Order>& orders, bool append = false) const; // Запись данных в файл
};

// Функции для взаимодействия с пользователем
void addOrderInteractively(Bookstore& bookstore);    // Функция для интерактивного добавления заказа
void removeOrderInteractively(Bookstore& bookstore); // Функция для интерактивного удаления заказа

#endif // CLASS_H
