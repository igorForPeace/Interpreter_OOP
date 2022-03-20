#include <iostream>
#include <vector>
using namespace std;

class Memento
{
private:
    int state;
    friend class Originator; // доступен только другу - создателю class Originator
    Memento(const int s) : state(s) {}

    void setState(const int s)
    {
        state = s;
    }

    int getState()
    {
        return state;
    }
};

class Originator // «Cоздатель», который использует объект «Xранитель».
{
public:
    void setState(const int s) // установили состояние на текущий момент
    {
        state = s;
        cout << "Set state to " << s << "\n";       
    }

    int getState()
    {
        return state;
    }

    void setMemento(Memento* const m) 
    {
        state = m->getState();
    }

    Memento* createMemento()
    {
        return new Memento(state);
    }

private:
    int state;
};

class CareTaker // "Хранитель" отвечает за сохранность сувенира
{
public:
    CareTaker(Originator* const o) : originator(o) {}

    ~CareTaker()

    {
        for (unsigned int i = 0; i < history.size(); i++)
        {
            delete history.at(i);
        }
        
        history.clear();
    }

    void save()   // cохраняет текущее состояние внутри снимка
    {
        cout << "Save state" << "\n";
        history.push_back(originator->createMemento());
    }

    void undo()  // возвращаемся к прежнему состоянию
    {
        if (history.empty())
        {
            cout << "Unable to undo state." << "\n";
            return;
        }
        Memento* m = history.back();
        originator->setMemento(m);
        cout << "Undo state" << "\n";
        history.pop_back();
        delete m;
    }

private:
    Originator* originator;
    vector<Memento*> history;
};

int main()
{
    Originator* originator = new Originator();
    CareTaker* caretaker = new CareTaker(originator);

    originator->setState(1);
    caretaker->save();

    originator->setState(2);
    caretaker->save();

    originator->setState(3);
    caretaker->undo();

    cout << "Actual state is " << originator->getState() << ".\n";

    delete originator;
    delete caretaker;
}
