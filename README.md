# EngRusDict

Консольные команды:
1 Команда: createDict <name  of new dict>
2 Команда: removeDict <name  of new dict>
3 Команда: add <dictionary> <key> <translation>
4 Команда: remove <dictionary> <key> <translation>
5 Команда: addWords <dictionary1> <dictionary2>
6 Команда: removeWords <dictionary1> <dictionary2>
7 Команда: count <dictionary>
8 Команда: countTranslations <dictionary> <key>
9 Команда: getIntersection <name  of new dict> <dictionary1> < dictionary2>
10 Команда: getDifference <name  of new dict> <dictionary1> <dictionary2>
11 Команда: clear <dictionary>
12 Команда: display <dictionary>
13 Команда: getTranslation <key>
14 Команда: readDict <"путо к файлу">
//14 Команда: updateTranslation <dictionary> <key>

В планах:
	Функция для дерева позволяющая вывести элементы  с определённым  разделителем - YES
	Может стоит запретить повтор имени класса словаря ?
	Может стоит переделать/добавить метод позволяющий добавить новое слово?

EngRusDict:

Приватные элементы:

	std::string name_
	DictionaryList< std::string > words_;


Публичные функции:

	EngRusDict(std::string name);
	EngRusDict(EngRusDict& other);
	EngRusDict(EngRusDict&& other) noexcept;
	~EngRusDict();
	void clear();

	void addWord(WordPair wp);
	void removeWord(std::string keyEng);

	void addWordFromEngRusDict(EngRusDict& other);
	void removeWordFromEngRusDict(EngRusDict& other);

	friend EngRusDict getIntersectionWithEngRusDict(EngRusDict& erd1, EngRusDict& erd2);
	friend EngRusDict getDifferenceWithEngRusDict(EngRusDict& erd1, EngRusDict& erd2);

	size_t getCountWords();
	size_t getCountTranslations();
	//WordPair searchWordPair(std::string keyEng);
	DictionaryList<std::string> getTranslations(std::string keyEng);

	void display();


WordPair:

	std::string english;
	DictionaryList< std::string > translations;

	WordPair(const std::string& eng);

	void addTranslation(const std::string& rus);

	bool operator<(const WordPair& other) const;
	bool operator>(const WordPair& other) const;
	bool operator==(const WordPair& other) const;

	void addTranslations(WordPair& other);
	void removeTranslations(WordPair& other);

	friend WordPair getIntersectionTranslations(const WordPair& lhs, const WordPair& rhs);
	friend WordPair getDifferenceTranslations(const WordPair& lhs, const WordPair& rhs);

	friend std::ostream& operator<<(std::ostream& os, const WordPair& wp);


AVLTree:

Приватные элементы:
	 struct Node
	 {
	   T data_;
	   Node* left_;
	   Node* right_;
	   size_t height_;

	   Node();
	   Node(const T& data);
	 };

	 Node* root_;

	 Node* deepCopy(Node* node);

	 Node* insertRecursive(Node* node, const T& value);

	 Node* removeRecursive(Node* node, const T& value);

	 void addElementsRecursive(Node* node);

	 void removeElementsRecursive(Node* thisNode, Node* otherNode);

	 size_t getCountElementsRecursive(Node* node) const;

	 size_t getHeight(Node* node) const;

	 static void getIntersectionTreeRecursive(Node* node, const AVLTree< T >& tree, AVLTree< T >& intersectionTree);

	 static void getDifferenceTreeRecursive(Node* node, const AVLTree< T >& tree, AVLTree< T >& differenceTree);

	 size_t getBalance(Node* node) const;

	 Node* rightRotate(Node* node);

	 Node* leftRotate(Node* node);

	 void removeSubTree(Node* node);

	 Node* searchRecursive(Node* node, const T& value) const;

	 Node* getMinValueNode(Node* node) const;

	 bool containsRecursive(Node* node, const T& value) const;


Публичные элементы:

	 AVLTree() : root_(nullptr) {}
	 AVLTree(const AVLTree< T other);
	 AVL(AVLTree< T >&& other) : root_(other.root_);
	 ~AVLTree();
	 
	 void clear();
	 void insert(const T& value);
	 void remove(const& value);
	 void addElements(const AVLTree< T >& other);
	 void removeElements(const AVLTree< T >& other);

	 bool contains(const T& value) const;
	 T search(const T& value) const;

	 size_t getCountElements() const;
	 size_t getHeight() const;

	 friend AVLTree< T > getIntersectionTree(const AVLTree< T >& tree1, const AVLTree< T >& tree2);
	 friend AVLTree< T > getDifferenceTree(const AVLTree< T >& tree1, const AVLTree< T >& tree2);

	 AVLTree< T >& operator=(const AVLTree< T >& other);

	 friend std::ostream& operator<<(std::ostream& os, const AVL< T >& tree);
	 void display() const;

DictionaryList:

Приватные элементы:
struct Node
	{
	Node* next;
	T data;

	Node() : next(nullptr) {}
	Node(const T& data) : data(data), next(nullptr) {}
	};

	Node* _head;


Публичные элементы:

	DictionaryList();
	DictionaryList(DictionaryList&& other);
	DictionaryList& operator=(DictionaryList&& other);
	DictionaryList(const DictionaryList< T >& other);
	DictionaryList& operator=(const DictionaryList< T >& other);
	~DictionaryList();
	void clear();
	void insert(const T& newData);
	void remove(const T& key);
	T search(const T& key)
	void addElements(DictionaryList< T >& other);
	void removeElements(const AVLTree< T >& other);

	friend DictionaryList<T> getIntersectionDictList(const DictionaryList<T>& tree1, const DictionaryList<T>& tree2);
	friend DictionaryList<T> getDifferenceDictList(const DictionaryList<T>& tree1, const DictionaryList<T>& tree2

	void display()