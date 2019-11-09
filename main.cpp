#include <iostream>
#include <fstream>
#define VectorSize 50
#define MatrixSize 10
#define ListSize 10
#define GraphSize 10
using namespace std;

ifstream f("input.txt");

class matrix {
	int **a;
	int dim;
public:
	int getDim() {
		return dim;
	}
	void setDim(int value) {
		dim = value;
	}

	int getValue(int i, int j) {
		return a[i][j];
	}
	void setValue(int x, int i, int j) {
		a[i][j] = x;
	}
	int* getLine(int index) {
		if (index < 0 || index > MatrixSize) {
			cout << "Index is out of bounds." << endl;
			return NULL;
		}
		return a[index];
	}
	int** getMatrix() {
		return a;
	}
	matrix() {
		a = NULL ;// null
		dim = 0;
	}
	
	matrix(int n) {
		a = new int*[n];
		dim = n;
		for (int i = 0; i < n; ++i)
			a[i] = new int[n];
		cout << "Constructor" << endl;
	}

	~matrix() {
		for (int i = 0; i < dim; ++i)
			delete[] a[i];
		delete[] a;
		cout << "Destructor Matrix" << endl;
	}

	matrix(const matrix& ob) {
		dim = ob.dim;
		a = new int*[dim];
		for (int i = 0; i < dim; ++i)
		{
			a[i] = new int[dim];
			for (int j = 0; j < dim; ++j)
			{
				a[i][j] = ob.a[i][j];
			}
		}
	}

	friend istream& operator>>(istream&, matrix& ob);
	friend ostream& operator<<(ostream&, matrix ob);
	matrix operator=(matrix);
};

istream& operator>>(istream& in, matrix& ob)
{
	ob.a = new int*[ob.getDim()];
	for (int i = 0; i < ob.getDim(); ++i)
		ob.a[i] = new int[ob.getDim()];

	for (int i = 0; i < ob.getDim(); ++i)
	{
		for (int j = 0; j < ob.getDim(); ++j)
		{
			switch (j) {
			case 0: {
				cout << "The " << j + 1 << "st element from line " << i + 1 << " in the matrix is: ";
				break;
				}
			case 1: {
				cout << "The " << j + 1 << " nd element from line " << i + 1 << " in the matrix is: ";
				break;
				}
			case 2: {
				cout << "The " << j + 1 << " rd element from line " << i + 1 << " in the matrix is: ";
				break;
				}
			default: {
				cout << "The " << j + 1 << " th element from line " << i + 1 << " in the matrix is: ";
				break;
				}
			}
			int value;
			in >> value;
			ob.setValue(value, i, j);
		}
	}
	return in;
}

ostream& operator<<(ostream& out, matrix ob)
{
	for (int i = 0; i < ob.getDim(); ++i)
	{
		for (int j = 0; j < ob.getDim(); ++j)
		{
			cout << ob.getValue(i, j) << " ";
		}
		cout << endl;
	}
	return out;
}

matrix matrix ::operator=(matrix ob) {
	for (int i = 0; i < dim; ++i)
		delete[] a[i];
	delete[] a;

	setDim(ob.getDim());
	a = new int*[getDim()];
	for (int i = 0; i < getDim(); ++i)
	{
		a[i] = new int[ob.getDim()];
		for (int j = 0; j < getDim(); ++j)
			setValue(ob.getValue(i, j), i, j);
	}
	return *this;
}

class vector {
	int *v;
	int dim;
public:
	int getDim() {
		return dim;
	}
	void setDim(int value) {
		dim = value;
	}
	int getValue(int i) {
		if (i >= dim || i < 0) {
			cout << "Index out of bounds!" << endl;
			return -1;
		}
		return v[i];
	}

	void setValue(int x, int i) {
		if (i >= dim || i < 0) {
			cout << "Index out of bounds!" << endl;
			return;
		}
		v[i] = x;
	}

	vector() {
		v = NULL ;//null
		dim = 0;
		//cout << "Constructor" << endl;
	}

	vector(int size) {
		v = new int[size];
		dim = size;
		//cout << "Constructor" << endl;
	}
	
	~vector() {
		delete[] v;
		//cout << "Destructor" << endl;
	}

	vector(const vector& ob) {
		dim = ob.dim;
		v = new int[ob.dim];
		for (int i = 0; i < dim; ++i)
			v[i] = ob.v[i];
	}
	friend istream& operator>>(istream&, vector&);
	friend ostream& operator<<(ostream&, vector);
	vector operator=(vector);
};

istream& operator>>(istream& in, vector &ob)
{
	int size;
	in >> size;
	ob.setDim(size + 1);
	ob.v = new int[size + 1];
	for (int i = 1; i < ob.getDim(); ++i)
	{
		switch(i) {
			case 1 : {
				cout << "The " << i << " st adjacent node is: ";
				break;
			}
			case 2 : {
				cout << "The " << i << " nd adjacent node is: ";
				break;
			}
			case 3 : {
				cout << "The " << i << " rd adjacent node is: ";
				break;
			}
		default: {
			cout << "The " << i << " th adjacent node is: ";
			break;
		}
		}
		int value;
		in >> value;
		ob.setValue(value, i);
	}
	return in;
}

ostream& operator<<(ostream& out, vector ob)
{
	for (int i = 0; i < ob.getDim(); ++i)
	{
		out << ob.getValue(i) << " ";
	}
	out << endl;
	return out;
}

vector vector :: operator=(vector ob)
{
	delete[] v;
	setDim(ob.getDim());
	v = new int[getDim()];
	for (int i = 0; i < getDim(); ++i)
	{
		setValue(ob.getValue(i), i);
	}
	return *this;
}

class list{
	vector *l;
	int dim_list;
public:
	int getDim() {
		return dim_list;
	}
	void setDim(int value) {
		dim_list = value;
		l = new vector[dim_list];
	}
	vector getVector(int node) {
		if (node < 0 || node > VectorSize) {
			cout << "Node is out of bounds." << endl;
			return l[0];
		}
		return l[node];
	}
	void setVector(const vector& ob, int poz) {
		if (poz < 0 || poz > dim_list) {
			cout << "Index is out of bounds." << endl;
			return;
		}
		l[poz] = ob;
	}
	int getNode(int poz_i, int poz_j) {
		if (poz_i >= dim_list || poz_i < 0) {
			cout << "Index for vector is out of bounds." << endl;
			return -1;
		}
		if (poz_j >= l[poz_i].getDim() || poz_j < 0) {
			cout << "Index for node is out of bounds. " << endl;
			return -1;
		}
		return l[poz_i].getValue(poz_j);
	}
	void setNode(int node, int poz_i, int poz_j) {
		if (poz_i >= dim_list || poz_i < 0) {
			cout << "Index for vector is out of bounds." << endl;
			return;
		}
		if (poz_j >= l[poz_i].getDim() || poz_j < 0) {
			cout << "Index for node is out of bounds. " << endl;
			return;
		}
		l[poz_i].setValue(node, poz_j);
	}

	list() {
		dim_list = 0;
		l = NULL ;
		//cout << "Constructors whitout parameters for list class" << endl;
	}

	list(int size) {
		dim_list = size;
		l = new vector[dim_list];
		//cout << "Constructor for list class." << endl;
	}

	~list() {
		delete[] l;
		//cout << "Destructor for list class." << endl;
	}
	list(const list& ob) {
		dim_list = ob.dim_list;
		l = new vector[dim_list];
		for (int i = 0; i < dim_list; ++i) {
			l[i] = ob.l[i];
		}
	}

	friend istream& operator>>(istream&, list&);
	friend ostream& operator<<(ostream&, list);
	list operator=(const list&);
	vector operator[](int index);
};

list list :: operator=(const list& ob) {
	delete[] l;
	dim_list = ob.dim_list;
	l = new vector[dim_list];
	for (int i = 0; i < dim_list; ++i)
	{
		l[i] = ob.l[i];
	}
	return *this;
}

vector list :: operator[](int index) {
	if (index > dim_list || index < 0)
	{
		cout << "Index out of bounds.";
		//	return the first element
		return *l;
	}
	return *(l + index);
}

istream& operator>>(istream& in, list& ob)
{
	int nrNodes;
	cout << "The number of nodes in the adjacency list is: ";
	in >> nrNodes;
	ob.setDim(nrNodes);
	ob.l = new vector[ob.getDim()];
	for (int i = 0; i < ob.getDim(); ++i)
	{
		cout << "How many adjacent nodes does node " << i + 1 << " have: ";
		in >> ob.l[i];
		ob.l[i].setValue(i + 1, 0);
	}
	return in;
}

ostream& operator<<(ostream& out, list ob)
{
	out << "The adjacency list is composed of: " << endl;
	for (int i = 0; i < ob.dim_list; ++i)
	{
		out << ob.l[i];
	}
	return out;
}

class graph {
	int nr_nodes;
public:
	int getNrNodes() const {
		return nr_nodes;
	}
	void setNrNodes(int value) {
		nr_nodes = value;
	}
	graph() {
		nr_nodes = 0;
		cout << "Constructor for graph class." << endl;
	}
	graph(int size) {
		nr_nodes = size;
		cout << "Constructor with parameters for graph class." << endl;
	}
	~graph() {
		cout << "Destructor for graph class." << endl;
	}
	graph(const graph& ob) {
		nr_nodes = ob.nr_nodes;
	}

	virtual void read(istream& in) {
		int value;
		in >> value;
		setNrNodes(value);
	}
	virtual void print(ostream& out) {
		out << getNrNodes();
	}

	friend istream& operator>>(istream&, graph&); 
	friend ostream& operator<<(ostream&, graph);
	graph operator=(graph);
};

istream& operator>>(istream& in, graph& ob) {
	cout << "The number of nodes in the graph is: ";
	ob.read(in);
	return in;
}

ostream& operator<<(ostream& out, graph ob) {
	out << "Number of nodes in the graph: ";
	ob.print(out);
	out << endl;
	return out;
}

graph graph :: operator=(graph ob) {
	setNrNodes(ob.getNrNodes());
	return *this;
}

// graf neorientat
class undirected_graph : virtual protected graph{
	list L;
public:
	list getList() {
		return L;
	}
	undirected_graph() : graph() {
		L.setDim(0);
	}
	undirected_graph(int nrNodes) : graph(nrNodes) {
		L.setDim(nrNodes);
	}
	~undirected_graph() {
		cout << "Deconstructor for undirected graph class." << endl;
	}
	undirected_graph(const undirected_graph& ob) : graph(ob) {
		L = ob.L;
	}
	void read(istream& in) {
		cout << "The number of nodes in the undirected graph is: ";
		this->graph::read(in);
		L.setDim(getNrNodes());
		in >> L;
	}
	void print(ostream& out) {
		out << "Number of nodes in the undirected graph is: ";
		this->graph::print(out);
		out << endl;
	}

	undirected_graph operator=(const undirected_graph&);
	friend istream& operator>>(istream&, undirected_graph&);
	friend ostream& operator<<(ostream&, undirected_graph);
};

undirected_graph undirected_graph :: operator=(const undirected_graph& ob) {
	setNrNodes(ob.getNrNodes());
	L = ob.L;
	return *this;
}

istream& operator>>(istream& in, undirected_graph& ob) {
	ob.read(in);
	return in;
}

ostream& operator<<(ostream& out, undirected_graph ob) {
	ob.print(out);
	out << "The adjacency list for the undirected graph is: " << endl;
	out << ob.getList();
	return out;
}

// graf orientat
class directed_graph : virtual protected graph{
	matrix A;
public:
	matrix getMatrix() {
		return A;
	}
	directed_graph() : graph() {
		A.setDim(0);
	}
	directed_graph(int nrNodes) : graph(nrNodes) {
		A.setDim(nrNodes);
	}
	~directed_graph() {
		cout << "Decontructor for directed_graph class." << endl;
	}
	directed_graph(const directed_graph& ob) : graph(ob) {
		A = ob.A;
	}
	void read(istream& in) {
		cout << "The number of nodes in the directed graph is: ";
		this->graph::read(in);
		A.setDim(getNrNodes());
		in >> A;
	}
	void print(ostream& out) {
		out << "Number of nodes in the directed graph is: ";
		this ->graph::print(out);
		out << endl;
	}
	directed_graph operator=(const directed_graph&);
	friend istream& operator>>(istream&, directed_graph&);
	friend ostream& operator<<(ostream&, directed_graph);
	int conex(int node);
};

directed_graph directed_graph :: operator=(const directed_graph& ob) {
	for (int i = 0; i < getNrNodes(); ++i)
		delete[] A.getLine(i);
	delete[] A.getMatrix();
	setNrNodes(ob.getNrNodes());
	A = ob.A;
	return *this;
}

istream& operator>>(istream& in, directed_graph& ob) {
	ob.read(in);
	return in;
}

ostream& operator<<(ostream& out, directed_graph ob) {
	ob.print(out);
	out << "The adjacency matrix for the directed graph is: " << endl;
	out << ob.getMatrix();
	return out;
}

/*int directed_graph::conex(int node) {
	int *visit, *arcs;
	int size = getNrNodes();
	visit = new int[size + 1];
	arcs = new int[size + 1];
	int first = 1, last = 1;
	int nodesVisited = 1;
	visit[node] = 1;
	arcs[first] = node;
	while (first <= last) {
		for (int i = 0; i < size; ++i) {

		}
	}
}*/

int main()
{
	undirected_graph gr;
	cin >> gr;
	undirected_graph gr1;
	gr1 = gr;
	cout << gr1;
	cout << endl;
	directed_graph graf;
	cin >> graf;
	cout << graf;
	directed_graph copy;
	copy = graf;
	cout << copy;
	system("pause");
	return 0;
}