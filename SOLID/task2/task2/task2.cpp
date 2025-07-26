#include <iostream>
#include <fstream>
#include <memory>
#include <string>

class IHTMLPrintable {
public:
    virtual ~IHTMLPrintable() = default;
    virtual std::string printAsHTML() const = 0;
};

class ITextPrintable {
public:
    virtual ~ITextPrintable() = default;
    virtual std::string printAsText() const = 0;
};

class IJSONPrintable {
public:
    virtual ~IJSONPrintable() = default;
    virtual std::string printAsJSON() const = 0;
};

class Data {
protected:
    std::string data_;

public:
    explicit Data(std::string data) : data_(std::move(data)) {}
    virtual ~Data() = default;

    const std::string& getRawData() const { return data_; }
};

class HTMLData : public Data, public IHTMLPrintable {
public:
    using Data::Data;

    std::string printAsHTML() const override {
        return "<html>" + data_ + "</html>";
    }
};

class TextData : public Data, public ITextPrintable {
public:
    using Data::Data;

    std::string printAsText() const override {
        return data_;
    }
};

class JSONData : public Data, public IJSONPrintable {
public:
    using Data::Data;

    std::string printAsJSON() const override {
        return "{ \"data\": \"" + data_ + "\" }";
    }
};

void saveTo(std::ofstream& file, const ITextPrintable& printable) {
    file << printable.printAsText();
}

void saveTo(std::ofstream& file, const IHTMLPrintable& printable) {
    file << printable.printAsHTML();
}

void saveTo(std::ofstream& file, const IJSONPrintable& printable) {
    file << printable.printAsJSON();
}

int main() {
    std::ofstream htmlFile("output.html");
    std::ofstream textFile("output.txt");
    std::ofstream jsonFile("output.json");

    HTMLData htmlData("<body>Hello World</body>");
    TextData textData("Hello World");
    JSONData jsonData("Hello World");

    // Каждый объект сохраняется в соответствующем формате
    saveTo(htmlFile, htmlData);
    saveTo(textFile, textData);
    saveTo(jsonFile, jsonData);

    // Также можно работать через базовые интерфейсы
    IHTMLPrintable& htmlPrintable = htmlData;
    saveTo(htmlFile, htmlPrintable);

    return 0;
}