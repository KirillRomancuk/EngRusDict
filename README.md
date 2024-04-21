# EngRusDict

���������� �������:
1 �������: createDict <name  of new dict>
2 �������: removeDict <name  of new dict>
3 �������: add <dictionary> <key> <translation>
4 �������: remove <dictionary> <key> <translation>
5 �������: addWords <dictionary1> <dictionary2>
6 �������: removeWords <dictionary1> <dictionary2>
7 �������: count <dictionary>
8 �������: countTranslations <dictionary> <key>
9 �������: getIntersection <name  of new dict> <dictionary1> < dictionary2>
10 �������: getDifference <name  of new dict> <dictionary1> <dictionary2>
11 �������: clear <dictionary>
12 �������: display <dictionary>
13 �������: getTranslation <key>
//14 �������: updateTranslation <dictionary> <key>

EngRusDict:

��������� ��������:

	std::string name_
	DictionaryList< std::string > words_;


��������� �������:

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

��������� ��������:
	struct Node
	{
	T data;
	Node* left;
	Node* right;
	size_t height;
	};

	friend std::ostream& operator<<(std::ostream& os, const Node* node);

	Node* root_;

	Node* deepCopy(Node* node);

	Node* insertRecursive(Node* node, const T& value);

	size_t getHeight(Node* node);

	size_t getBalance(Node* node);

	Node* rightRotate(Node* node);
	Node* leftRotate(Node* node);

	void removeSubTree(Node* node);
	Node* searchRecursive(Node* node, const T& value);
	Node* popRecursive(Node* node, const T& value);

	Node* minValueNode(Node* node);
	bool containsRecursive(Node* node, const T& value) const;
	static void mergeRecursive(AVLTree<T>& mergedTree, Node* node); ???

	void display(Node* root, int space);


��������� ��������:

	AVLTree();
	AVLTree(const AVLTree< T >& other);
	AVLTree(AVLTree< T >&& other) noexcept;
	~AVLTree();

	void insert(const T& value);
	void pop(const T& value);
	void addElements(const AVLTree< T >& other);
	void removeElements(const AVLTree< T >& other);

	void clear();
	bool contains(const T& value) const;

	size_t getHeight();
	size_t countElements();

	friend AVLTree<T> getIntersectionTree(const AVLTree<T>& tree1, const AVLTree<T>& tree2);
	friend AVLTree<T> getDifferenceTree(const AVLTree<T>& tree1, const AVLTree<T>& tree2);

	AVLTree<T>& operator=(const AVLTree<T>& other);

	friend std::ostream& operator<<(std::ostream& os, const AVLTree< T >& tree);

	void display();

DictionaryList:

��������� ��������:
struct Node
	{
	Node* next;
	T data;

	Node() : next(nullptr) {}
	Node(const T& data) : data(data), next(nullptr) {}
	};

	Node* _head;


��������� ��������:

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