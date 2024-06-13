#ifndef CLASS_H
#define CLASS_H

#include <string>
#include <vector>

using namespace std;

// �����, �������������� �������
class Customer
{
private:
    string name;    // ��� �������
    float discount; // �������� ������ �������

public:
    // ����������� �������
    Customer(const string& name, float discount);

    // ������� ��� ����� � ������
    string getName() const;
    float getDiscount() const;

    // ������� ��� ����� � ������
    void setName(const string& newName);
    void setDiscount(float newDiscount);
};

// �����, �������������� ����� �� �����
class Order
{
private:
    int id;            // ������������� ������
    Customer customer; // ������, ��������� �����
    vector<string> books; // ������ ���������� ����

public:
    // ����������� ������
    Order(int id, const Customer& customer, const vector<string>& books);

    // ������� ��� id, ������� � ������ ����
    int getId() const;
    Customer getCustomer() const;
    vector<string> getBooks() const;

    // ����� ��� ���������� ����� � ������
    void addBook(const string& newBook);
};

// �����, �������������� ������� �������
class Bookstore
{
private:
    vector<Order> orders; // ������ ������� � ������� ��������

public:
    // ������ ��� ���������� ��������
    void addOrder(const Order& order); // ���������� ������ � ������
    void removeOrder(int orderId);     // �������� ������ �� id
    vector<Order> findOrdersByDiscount(float discount) const; // ����� ������� �� �������� ������

    // ������ ��� ������ � �������
    void readDataFromFile(const string& filename); // ������ ������ �� �����
    void writeOrdersToFile(const string& filename, const vector<Order>& orders, bool append = false) const; // ������ ������ � ����
};

// ������� ��� �������������� � �������������
void addOrderInteractively(Bookstore& bookstore);    // ������� ��� �������������� ���������� ������
void removeOrderInteractively(Bookstore& bookstore); // ������� ��� �������������� �������� ������

#endif // CLASS_H
