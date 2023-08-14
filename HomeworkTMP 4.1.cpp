#include <iostream>
#include <fstream>
#include <vector>

class Printable
{
private:
    std::vector<Printable*> printables_;
protected:
    std::string type_;
    virtual std::string print(const std::string& message) {
        return "Error job";
    }
public:
    Printable() = default;
    ~Printable() = default;
    void AddPrintable(Printable* obs) {
        printables_.push_back(obs);
    }

    void save(std::ofstream& file, const std::string& message, const std::string& type) {
        if (file.is_open()) {
            for (int i = 0; i < printables_.size(); i++) {
                if (printables_[i]->type_ == type) {
                    file << printables_[i]->print(message);
                }
            }
        }
        else {
            std::cout << "file is close.";
        }
    };
};

class SaveToAsHTML : public Printable {
public:
    SaveToAsHTML(std::string type) : Printable() { type_ = type; };
    std::string print(const std::string& message) override{
        return "<html>" + message + "<html/>\n";
    }
};

class SaveToAsJSON : public Printable {
public:
    SaveToAsJSON(std::string type) : Printable() { type_ = type; };
    std::string print(const std::string& message) override {
        return "{ \"data\": \"" + message + "\"}\n";
    }
};

class SaveToAsText : public Printable {
public:
    SaveToAsText(std::string type) : Printable() { type_ = type; };
    std::string print(const std::string& message) override {
        return message + "\n";
    }
};


int main()
{
    std::ofstream save_file("Save.txt", std::ios::app);
    auto tabl = new Printable();
    auto asHTML = new SaveToAsHTML("HTML"); tabl->AddPrintable(asHTML);
    auto asJSON = new SaveToAsJSON("JSON"); tabl->AddPrintable(asJSON);
    auto asTEXT = new SaveToAsText("TEXT"); tabl->AddPrintable(asTEXT);
    tabl->save(save_file, "Check HTML", "HTML");
    tabl->save(save_file, "Check JSON", "JSON");
    tabl->save(save_file, "Check TEXT", "TEXT");
    save_file.close();
    std::cout << "End.\n";
    return 0;
}