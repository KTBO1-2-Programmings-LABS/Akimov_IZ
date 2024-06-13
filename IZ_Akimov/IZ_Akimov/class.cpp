#include "class.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// ����������� �������
Customer::Customer(const string& name, float discount)
    : name(name), discount(discount) {}

// ������ ��� �������� ������
float Customer::getDiscount() const
{
    return discount;
}

// ������ ��� ����� �������
string Customer::getName() const
{
    return name;
}

// ������ ��� ����� ������� � ��������� �� ������ ��������
void Customer::setName(const string& newName)
{
    if (!newName.empty())
    {
        name = newName;
    }
    else
    {
        cerr << "������: ��� �� ����� ���� ������." << endl;
    }
}

// ������ ��� �������� ������ � ��������� �� ������������� ��������
void Customer::setDiscount(float newDiscount)
{
    if (newDiscount >= 0.0f)
    {
        discount = newDiscount;
    }
    else
    {
        cerr << "������: ������ �� ����� ���� �������������." << endl;
    }
}

// ����������� ������
Order::Order(int id, const Customer& customer, const vector<string>& books)
    : id(id), customer(customer), books(books) {}

// ������ ��� id ������
int Order::getId() const
{
    return id;
}

// ������ ��� �������, ���������� �����
Customer Order::getCustomer() const
{
    return customer;
}

// ������ ��� ������ ���������� ����
vector<string> Order::getBooks() const
{
    return books;
}

// ����� ��� ���������� ����� � ������
void Order::addBook(const string& newBook)
{
    if (!newBook.empty())
    {
        books.push_back(newBook);
    }
    else
    {
        cerr << "������: �������� ����� �� ����� ���� ������." << endl;
    }
}

// ���������� ������ � ������� �������
void Bookstore::addOrder(const Order& order)
{
    orders.push_back(order);
}

// �������� ������ �� �������� �������� �� id
void Bookstore::removeOrder(int orderId)
{
    orders.erase(remove_if(orders.begin(), orders.end(), [orderId](const Order& order)
        { return order.getId() == orderId; }),
        orders.end());
}

// ����� ������� �� �������� ������
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

// ������ ������ �� ����� � ���������� �������
void Bookstore::readDataFromFile(const string& filename)
{
    ifstream infile(filename);
    if (!infile.is_open())
    {
        cerr << "������ �������� ����� " << filename << endl;
        return;
    }

    orders.clear(); // ������� ������� ������ ����� ��������� ����� ������

    string line;
    while (getline(infile, line))
    {
        // ���������� stringstream ��� ������� ������ �� �������
        stringstream ss(line);
        string segment;
        vector<string> segments;

        while (getline(ss, segment, ','))
        {
            segments.push_back(segment);
        }

        // ���������, ��� �� ������� �������� ��� ����������� �������� ������
        if (segments.size() < 4)
        {
            cerr << "������ ������ ������ �� �����: ������������ ������" << endl;
            continue;
        }

        // ��������� ������ �� ���������
        int orderId = stoi(segments[0]);
        string name = segments[1];
        float discount = stof(segments[2]);

        // ������ ���������� ���� ���������� � �������� �������� � segments
        vector<string> books;
        for (size_t i = 3; i < segments.size(); ++i)
        {
            books.push_back(segments[i]);
        }

        // ������� ������� � ��������� � ��������� �������
        Customer customer(name, discount);
        Order order(orderId, customer, books);
        addOrder(order);
    }

    infile.close(); // ��������� ���� ����� ������
}

// ������ ������ ������� � ����
void Bookstore::writeOrdersToFile(const string& filename, const vector<Order>& orders, bool append) const
{
    ofstream outfile;
    if (append)
    {
        outfile.open(filename, ios_base::app); // ������� ���� ��� ���������� � �����
    }
    else
    {
        outfile.open(filename); // ������������ ����
    }

    for (const auto& order : orders)
    {
        // ���������� id ������, ��� �������, �������� ������ � ������ ���� ����� ������
        outfile << order.getId() << " " << order.getCustomer().getName() << " "
            << order.getCustomer().getDiscount() << " ";
        for (const auto& book : order.getBooks())
        {
            outfile << book << " ";
        }
        outfile << endl;
    }
}

// ������� ��� �������������� ���������� ������
void addOrderInteractively(Bookstore& bookstore)
{
    int orderId;
    float discount;
    string name, book;
    vector<string> books;

    cout << "������� ID ������: ";
    while (!(cin >> orderId))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "������: ������� ����� �����." << endl;
        cout << "������� ID ������: ";
    }
    cin.ignore(); // ������� ����� �����

    cout << "������� ��� �������: ";
    getline(cin, name);

    cout << "������� ������: ";
    while (!(cin >> discount) || discount < 0.0f)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "������: ������� ������������� �����." << endl;
        cout << "������� ������: ";
    }
    cin.ignore(); // ������� ����� �����

    cout << "������� �������� ���� (����� ������): ";
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

// ������� ��� �������������� �������� ������ �� ID
void removeOrderInteractively(Bookstore& bookstore)
{
    int orderId;
    cout << "������� ID ������ ��� ��������: ";
    while (!(cin >> orderId))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "������: ������� ����� �����." << endl;
        cout << "������� ID ������ ��� ��������: ";
    }
    bookstore.removeOrder(orderId);
}
