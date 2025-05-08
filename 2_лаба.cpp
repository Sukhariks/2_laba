#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <string>
#include <set>
#include <sstream>

using namespace std;

class Element {
public:
    virtual ~Element() = default;
    virtual bool equals(const Element& other) const = 0;
    virtual void print(int indent = 0) const = 0;
    virtual unique_ptr<Element> clone() const = 0;
    virtual string toString() const = 0;
};

class IntElement : public Element {
    int value;
public:
    IntElement(int v) : value(v) {}

    bool equals(const Element& other) const override {
        if (auto p = dynamic_cast<const IntElement*>(&other))
            return value == p->value;
        return false;
    }

    void print(int indent = 0) const override {
        cout << string(indent, ' ') << value;
    }

    unique_ptr<Element> clone() const override {
        return make_unique<IntElement>(value);
    }

    string toString() const override {
        return to_string(value);
    }
};

class StringElement : public Element {
    string value;
public:
    StringElement(const string& v) : value(v) {}

    bool equals(const Element& other) const override {
        if (auto p = dynamic_cast<const StringElement*>(&other))
            return value == p->value;
        return false;
    }

    void print(int indent = 0) const override {
        cout << string(indent, ' ') << "\"" << value << "\"";
    }

    unique_ptr<Element> clone() const override {
        return make_unique<StringElement>(value);
    }

    string toString() const override {
        return "\"" + value + "\"";
    }
};

class SetElement : public Element {
    multiset<string> elements;
public:
    void add(unique_ptr<Element> elem) {
        elements.insert(elem->toString());
    }

    bool equals(const Element& other) const override {
        if (auto p = dynamic_cast<const SetElement*>(&other)) {
            return elements == p->elements;
        }
        return false;
    }

    void print(int indent = 0) const override {
        cout << string(indent, ' ') << "< ";
        for (const auto& elem : elements) {
            cout << elem << " ";
        }
        cout << ">";
    }

    unique_ptr<Element> clone() const override {
        auto new_set = make_unique<SetElement>();
        new_set->elements = elements;
        return new_set;
    }

    string toString() const override {
        stringstream ss;
        ss << "< ";
        for (const auto& elem : elements) {
            ss << elem << " ";
        }
        ss << ">";
        return ss.str();
    }

    const multiset<string>& getElements() const { return elements; }
};

unique_ptr<SetElement> multiset_difference(const SetElement& A, const SetElement& B) {
    auto result = make_unique<SetElement>();
    multiset<string> b_elements = B.getElements();

    for (const auto& elem_a : A.getElements()) {
        auto it = b_elements.find(elem_a);
        if (it != b_elements.end()) {
            b_elements.erase(it);
        }
        else {
            result->add(make_unique<StringElement>(elem_a));
        }
    }

    return result;
}

unique_ptr<Element> input_element() {
    char c;
    while (cin >> c && c == ' ') {}

    if (c == '<') {
        auto set = make_unique<SetElement>();
        while (true) {
            auto elem = input_element();
            set->add(move(elem));

            while (cin >> c && c == ' ') {}
            if (c == '>') break;
            if (c != ',') {
                cerr << "Ошибка ввода: ожидалась ',' или '>'\n";
                exit(1);
            }
        }
        return set;
    }
    else if (c == '"') {
        string s;
        while (cin.get(c) && c != '"') {
            s += c;
        }
        return make_unique<StringElement>(s);
    }
    else {
        cin.putback(c);
        int num;
        if (!(cin >> num)) {
            cerr << "Ошибка ввода: ожидалось число\n";
            exit(1);
        }
        return make_unique<IntElement>(num);
    }
}

int main() {
    system("chcp 1251>nul");
    cout << "Введите первое множество (формат: <1, <2, 3>, \"text\", 4>): ";
    auto A = unique_ptr<SetElement>(dynamic_cast<SetElement*>(input_element().release()));

    cout << "Введите второе множество: ";
    auto B = unique_ptr<SetElement>(dynamic_cast<SetElement*>(input_element().release()));

    if (!A || !B) {
        cerr << "Ошибка: введенные данные не являются множествами\n";
        return 1;
    }

    auto difference = multiset_difference(*A, *B);

    cout << "Разность множеств:\n";
    difference->print();
    cout << endl;

    return 0;
}
