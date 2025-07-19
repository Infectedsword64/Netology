#include <string>
#include <iostream>
#include <algorithm>

class Text {
public:
    virtual void render(const std::string& data) const {
        std::cout << data;
    }
};

class DecoratedText : public Text {
public:
    explicit DecoratedText(Text* text) : text_(text) {}
    Text* text_;
};

class Paragraph : public DecoratedText {
public:
    explicit Paragraph(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
};

class Reversed : public DecoratedText {
public:
    explicit Reversed(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::string reversed_data = data;
        std::reverse(reversed_data.begin(), reversed_data.end());
        text_->render(reversed_data);
    }
};

class Link : public DecoratedText {
public:
    explicit Link(Text* text) : DecoratedText(text) {}
    void render(const std::string& href, const std::string& data) {
        std::cout << "<a href=" << href << ">";
        text_->render(data);
        std::cout << "</a>";
    }
};

int main() {
    auto paragraph = new Paragraph(new Text());
    paragraph->render("Hello world");
    std::cout << std::endl;

    auto reversed = new Reversed(new Text());
    reversed->render("Hello world");
    std::cout << std::endl;

    auto link = new Link(new Text());
    link->render("netology.ru", "Hello world");
    std::cout << std::endl;

    delete paragraph;
    delete reversed;
    delete link;

    return 0;
}