#include <iostream>

using namespace std;
class Drugs_Box
{
private:
    string name;
    double length, width, hight;

public:
    Drugs_Box() { length = 1; width = 1; hight = 1; name = "Drug"; }
    Drugs_Box(string name) { length = 1; width = 1; hight = 1; this->name = name; }

    double Get_Length() { return length; }
    double Get_Width() { return width; }
    double Get_Higth() { return hight; }
    double Get_Volume() { return length * width * hight; }

    void Set_Length(double length) { 
        this->length = length; }
    void Set_Width(double width) { 
        this->width = width; }
    void Set_Higth(double hight) {
        this->hight = hight; }

    void Input()
    {
        cout << "\t" << this->name << endl;
        cout << "Length: ";
        cin >> this->length;

        cout << "Width: ";
        cin >> this->width;

        cout << "Hight: ";
        cin >> this->hight;
    }
};


class Botteled_Drugs_Box : public Drugs_Box
{
private:
    double weigth_bottle;
    double weigth_liquid;

public:

    Botteled_Drugs_Box() : Drugs_Box()
    {
        weigth_bottle = 1;
        weigth_liquid = 1;
    }

    Botteled_Drugs_Box(string name) : Drugs_Box(name)
    {
        weigth_bottle = 1;
        weigth_liquid = 1;
    }

    void Set_Weight_Bottle(double weight_of_bottle)
    {
        this->weigth_bottle = weight_of_bottle;
    }

    void Set_Weight_Liquid(double weight_of_substance)
    {
        this->weigth_liquid = weight_of_substance;
    }

    double Get_Weight_Bottle() { return weigth_bottle; }
    double Get_Weight_Liquid() { return weigth_liquid; }

    void Input()
    {
        Drugs_Box::Input();
        cout << "Weight of bottle: ";
        cin >> this->weigth_bottle;

        cout << "Weight of liquid: ";
        cin >> this->weigth_liquid;
    }
};

class Placing
{
private:
    Drugs_Box* drugs;
    Botteled_Drugs_Box* drugs_in_bot;
    int num_of_elem_drug;
    int num_of_elem_bot;
    double all_weight = 0;
    double all_volume = 0;
    double max_weight;
    double max_volume;

public:
    Placing(int num_of_elem_drug = 0, int num_of_elem_bot = 0)
    {
        drugs_in_bot = new Botteled_Drugs_Box[num_of_elem_bot];
        drugs = new Drugs_Box[num_of_elem_drug];
        this->num_of_elem_bot = num_of_elem_bot;
        this->num_of_elem_drug = num_of_elem_drug;
    }
    ~Placing() { delete[] drugs_in_bot; delete[] drugs; }

    void Set_Max_Weight(double weight)
    {
        max_weight = weight;
    }

    void Set_Max_Volume(double volume)
    {
        max_volume = volume;
    }

    void Place_Drugs(Drugs_Box obj, ...)
    {
        Drugs_Box* p;
        int i = 0;

        for (i = 0, p = &obj; i < num_of_elem_drug; p++, i++)
        {
            drugs[i] = *p;
            all_volume += drugs[i].Get_Volume();
        }

    }

    void Place_Botteled_Drugs(Botteled_Drugs_Box obj, ...)
    {
        Botteled_Drugs_Box* p;
        int i;

        for (i = 0, p = &obj; i < num_of_elem_bot; i++, p++)
        {
            drugs_in_bot[i] = *p;
            all_weight += drugs_in_bot[i].Get_Weight_Bottle();
            all_weight += drugs_in_bot[i].Get_Weight_Liquid();
            all_volume += drugs_in_bot[i].Get_Volume();
        }
    }

    double Get_Max_Weight() { return max_weight; }
    double Get_Max_Volume() { return max_volume; }
    double Get_All_Weight() { return all_weight; }
    double Get_All_Volume() { return all_volume; }

    bool Can_Be_Placed()
    {
        if ((all_volume <= max_volume) && (all_weight <= max_weight))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

typedef Botteled_Drugs_Box BDB;

int main()
{
    BDB a;
    BDB drug_1("Solpadein");
    Drugs_Box drug_2("Astra");
    Drugs_Box drug_3("Nurofen");
    BDB drug_4("Antimigren");
    BDB drug_5("Dodecacelatein");
    Placing place(2, 3);


    drug_1.Input();
    drug_2.Input();
    drug_3.Input();
    drug_4.Input();
    drug_5.Input();
    place.Set_Max_Weight(8);
    place.Set_Max_Volume(50);
    place.Place_Drugs(drug_2, drug_3);
    place.Place_Botteled_Drugs(drug_1, drug_4, drug_5);

    if (place.Can_Be_Placed())
    {
        cout << endl;
        cout << "\tDrugs CAN be placed here" << endl;
    }
    else
    {
        cout << endl;
        cout << "\tDrugs CAN NOT be placed here" << endl;
    }

    cout << "\n\nMax Weight: " << place.Get_Max_Weight() << endl;
    cout << "All Weight: " << place.Get_All_Weight() << endl << endl;
    cout << "Max Volume: " << place.Get_Max_Volume() << endl;
    cout << "All Volume: " << place.Get_All_Volume() << endl;
}
//Створити базовий клас УПАКУВАННЯ ДЛЯ ЛІКІВ(задаються назва, розмір упакування(ширина, довжина, висота).
//Створити похідний клас УПАКУВАННЯ ДЛЯ ЛІКІВ У ФЛАКОНАХ(задаються вага речовини, вага флакону).
//Для введених даних про різні ліки, наявні в аптеці, 
//обчислити їх сумарну вагу та сумарний об’єм і визначити чи можна розмістити ці ліки у певній тарі із заданим максимально можливим об’ємом.