
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Person {
public:

	Person() {
		name = "", age = 0;
	}
	Person(const string& name) {
		this->name = name;
	}
	Person(const string& _name, const int& _age) {
		name = _name;
		age = _age;
	}
	string& getName()  { return name; }
	string getName () const {
		return name;
	}

	bool operator<(const Person& he) {
		return name < he.name;
	}

	bool operator==(const Person& he) {
		return name == he.name && age == he.age;
	}

	friend class Group;
private:
	string name;
	int age;

};

ostream& operator<<(ostream& out, const Person& p) {
	cout << p.getName();
	return out;
}

class Group {
public:

	Group(int max_lenght)  {
		this->cap = max_lenght;
		this->members = new Person[max_lenght];
		this->size = 0;
	}
	Group (const Group& he) {
		cap = he.cap;
		size = he.size;
		members = new Person[cap];
		for (int i = 0; i < size; i++) {
			members[i] = he.members[i];
		}
	}
	Group& operator=(const Group& he) {
		cap = he.cap;
		size = he.size;
		members = new Person[cap];
		for (int i = 0; i < size; i++) {
			members[i] = he.members[i];
		}
		return *this;
	}
	void add(Person p) {
		if (this->size == this->cap) {
			return;
		}
		this->members[size] = p;
		this->size++;
	}
	void deletePerson(string name) {
		int i;
		for (i = 0; i < size; i++) {
			if(members[i].name == name)
				break;
			
		}
		for (int index = i; index < size - 1; index++) {
			members[index] = members[index + 1];
		}
		size--;
	}

	~Group() {
		delete[] members;
	}

	Group operator+(const Group& he) const {
		Group ret(cap + he.cap);
		ret.size = size + he.size;
		for (int i = 0; i < size; i++) {
			ret.members[i] = members[i];
		}
		for (int i = size; i < size + he.size; i++) {
			ret.members[i] = he.members[i - size];
		}
		return ret;
	}

	Group& operator+=(const Group& he) {
		*this = *this + he;
		return *this;
	}

	Person& operator[](int ind) {
		return members[ind];
	}

	friend bool isGroupFull(Group g);

	friend ostream& operator<<(ostream& out, const Group& p);

private:
	int size;
	int cap;
	Person* members;

};

ostream& operator<<(ostream& out, const Group& p) {
	for (int i = 0; i < p.size; i++) {
		out << p.members[i].getName();
		if (i != p.size - 1) {
			cout << '\t';
		}
	}
	return out;
}

bool isGroupFull(Group g) {
	return (g.size == g.cap);
}

int main()
{
	Person p1("somename");
	Person p2("somename2");
	cout << p1 << p2;
	Group g1(5);
	g1.add({"Erfan" ,20});
	g1.add({"Saba", 20});
	g1.add({"Mahrokh", 20});
	g1.add({"Yasin", 21});
	cout << isGroupFull(g1)<< endl;


	Group g2(g1);
	Group g3(10);
	g2.deletePerson("Erfan");
	cout << g1 << endl; //should cout every person in it with a \t as the separator
	cout << g2 << endl;


	g3 = g1;
	cout << g3 << endl;
	g3 = g2 + g3;//adds members of g2 and g3 to each other
	g3 += g3 += g3 += g3;

	Person persons[10];
	Person Erfan("Erfan",20);
	persons[1]=Erfan;
	for(int i=0;i<10;i++){
		persons[i].getName()=to_string(rand()%100);
	}
	sort(persons,persons+10);//what operator should be overloaded for sort? :)

	for(int i=0;i<10;i++){
		cout<<persons[i].getName()<<' ';
	}

	if (find(persons,persons+10,Erfan) == persons + 10) {
		return 0;
	}
	cout << *find(persons,persons+10,Erfan);
}