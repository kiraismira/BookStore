#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

const int MAX_BOOKS = 1000;

//БАЗА ДАНИХ
string titles[MAX_BOOKS];
string authors[MAX_BOOKS];
string categories[MAX_BOOKS];
double prices[MAX_BOOKS];
int quantities[MAX_BOOKS];
int bookCount = 0;

//СТРУКТУРА ДЛЯ ЧЕКУ
struct Purchase
{
    string title;
    int quantity;
    double price;
    double total;
};
Purchase purchases[MAX_BOOKS];
int purchaseCount = 0;

//ФУНКЦІЇ БАЗИ
bool isDuplicate(const string& title)
{
    for (int i = 0; i < bookCount; i++)
        if (titles[i] == title)
            return true;
    return false;
}

void addBook()
{
    if (bookCount >= MAX_BOOKS)
    {
        cout << "Помилка: перевищено максимальну кількість книг!\n";
        return;
    }

    cin.ignore();
    string title, author, category;
    double price;
    int qty;

    // Перевірка назви книги
    do
    {
        cout << "Назва книги: ";
        getline(cin, title);

        if (title.empty())
        {
            cout << "Назва книги не може бути порожньою\n";
            continue;
        }

        if (isDuplicate(title))
        {
            cout << "Помилка: така книга вже існує!\n";
            title = ""; // щоб повторити запит
        }

    } while (title.empty());

    // Перевірка автора
    do
    {
        cout << "Автор: ";
        getline(cin, author);
        if (author.empty())
            cout << "Автор не може бути порожнім\n";
    } while (author.empty());

    // Перевірка категорії
    do
    {
        cout << "Категорія: ";
        getline(cin, category);
        if (category.empty())
            cout << "Категорія не може бути порожньою.\n";
    } while (category.empty());

    // Ціна
    do
    {
        cout << "Ціна: ";
        cin >> price;

        if (!cin || price <= 0) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "Ціна має бути більшою за 0! Спробуйте ще раз: ";
            cin >> price;
        }

        if (price <= 0)
        {
            cout << "Ціна має бути більшою за 0!\n";
        }

    } while (price <= 0);


    // Кількість
    do
    {
        cout << "Кількість: ";
        cin >> qty;
        if (qty <= 0) cout << "Кількість має бути більшою за 0!\n";
    } while (qty <= 0);

    titles[bookCount] = title;
    authors[bookCount] = author;
    categories[bookCount] = category;
    prices[bookCount] = price;
    quantities[bookCount] = qty;
    bookCount++;

    cout << "Книга успішно додана!\n";
}

void showBooks()
{
    cout << "\n=== СПИСОК КНИГ ===\n";
    if (bookCount == 0)
    {
        cout << "База даних порожня.\n";
        return;
    }

    for (int i = 0; i < bookCount; i++)
    {
        cout << i + 1 << ". " << titles[i]
            << " | Автор: " << authors[i]
            << " | Категорія: " << categories[i]
            << " | Ціна: " << prices[i]
            << " грн | Кількість: " << quantities[i] << endl;
    }
}

void editBook()
{
    showBooks();
    if (bookCount == 0) return;

    int index;
    cout << "Введіть номер книги для редагування: ";
    cin >> index;
    if (index < 1 || index > bookCount)
    {
        cout << "Невірний номер.\n";
        return;
    }

    int i = index - 1;
    cin.ignore();
    double newPrice;

    // Перевірка нової назви
    do
    {
        cout << "Нова назва: ";
        getline(cin, titles[i]);

        if (titles[i].empty())
        {
            cout << "Назва книги не може бути порожньою.\n";
            continue;
        }

        if (isDuplicate(titles[i]) && titles[i] != titles[i]) // не дублювати себе
        {
            cout << "Помилка: така книга вже існує!\n";
            titles[i] = "";
        }

    } while (titles[i].empty());

    // Перевірка нового автора
    do
    {
        cout << "Новий автор: ";
        getline(cin, authors[i]);
        if (authors[i].empty())
            cout << "Автор не може бути порожнім.\n";
    } while (authors[i].empty());

    // Перевірка нової категорії
    do
    {
        cout << "Нова категорія: ";
        getline(cin, categories[i]);
        if (categories[i].empty())
            cout << "Категорія не може бути порожньою.\n";
    } while (categories[i].empty());

    // Ціна
    do
    {
        cout << "Ціна: ";
        cin >> newPrice;

        if (!cin || newPrice <= 0) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "Ціна має бути більшою за 0! Спробуйте ще раз: ";
            cin >> newPrice;
        }

        if (newPrice <= 0)
        {
            cout << "Ціна має бути більшою за 0!\n";
        }

    } while (newPrice <= 0);

    // Кількість
    do
    {
        cout << "Нова кількість: ";
        cin >> quantities[i];
        if (quantities[i] <= 0) cout << "Кількість має бути більшою за 0!\n";
    } while (quantities[i] <= 0);

    cout << "Дані оновлено!\n";
}


void deleteBook()
{
    showBooks();
    if (bookCount == 0) return;

    int index;
    cout << "Введіть номер книги для видалення: ";
    cin >> index;
    if (index < 1 || index > bookCount)
    {
        cout << "Невірний номер.\n";
        return;
    }

    for (int j = index - 1; j < bookCount - 1; j++)
    {
        titles[j] = titles[j + 1];
        authors[j] = authors[j + 1];
        categories[j] = categories[j + 1];
        prices[j] = prices[j + 1];
        quantities[j] = quantities[j + 1];
    }
    bookCount--;

    cout << "Книга успішно видалена!\n";
}

//ЧЕК

void createReceipt()
{
    if (bookCount == 0)
    {
        cout << "База даних порожня — немає що продавати.\n";
        return;
    }

    purchaseCount = 0;
    char choice;
    do
    {
        showBooks();
        cout << "\nВведіть номер книги, яку купує клієнт: ";
        int index;
        cin >> index;

        if (index < 1 || index > bookCount)
        {
            cout << "Невірний номер книги!\n";
            continue;
        }

        int qty;
        cout << "Скільки одиниць?: ";
        cin >> qty;

        if (qty <= 0)
        {
            cout << "Невірна кількість!\n";
            continue;
        }

        if (qty > quantities[index - 1])
        {
            cout << "Недостатньо на складі! Доступно: " << quantities[index - 1] << endl;
            continue;
        }

        // Додаємо покупку до чеку
        purchases[purchaseCount].title = titles[index - 1];
        purchases[purchaseCount].price = prices[index - 1];  // ціна з бази даних
        purchases[purchaseCount].quantity = qty;
        purchases[purchaseCount].total = prices[index - 1] * qty;
        purchaseCount++;

        // Зменшуємо кількість на складі
        quantities[index - 1] -= qty;

        cout << "Додано до чеку: " << titles[index - 1] << " x" << qty << endl;

        cout << "Додати ще одну книгу? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    // Виведення готового чеку
    if (purchaseCount > 0)
    {
        double totalSum = 0;
        cout << "\n===== ЕЛЕКТРОННИЙ ЧЕК =====\n";
        for (int i = 0; i < purchaseCount; i++)
        {
            cout << i + 1 << ". " << purchases[i].title << endl;
            cout << " | Кількість: " << purchases[i].quantity << endl;
            cout << " | Ціна: " << purchases[i].price <<" грн"<< endl;
            cout<<  " | Сума: " << purchases[i].total << " грн"<<endl;
            totalSum += purchases[i].total;
        }
        cout << "-----------------------------\n";
        cout << "ЗАГАЛЬНА СУМА: " << totalSum << " грн\n";
    }
    else
    {
        cout << "Чек порожній.\n";
    }
}

//МЕНЮ
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;
    do
    {
        cout << "\n=== ГОЛОВНЕ МЕНЮ ===\n";
        cout << "1 - Додати книгу\n";
        cout << "2 - Редагувати книгу\n";
        cout << "3 - Видалити книгу\n";
        cout << "4 - Показати всі книги\n";
        cout << "5 - Сформувати чек\n";
        cout << "0 - Вийти\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice)
        {
        case 1: addBook(); break;
        case 2: editBook(); break;
        case 3: deleteBook(); break;
        case 4: showBooks(); break;
        case 5: createReceipt(); break;
        case 0: cout << "Вихід з програми.\n"; break;
        default: cout << "Невірний вибір!\n";
        }
    } while (choice != 0);

    return 0;
}
