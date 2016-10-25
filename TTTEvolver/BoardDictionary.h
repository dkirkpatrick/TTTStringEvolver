#include <map>
#include <vector>

class BoardDictionary {
public: 
	BoardDictionary() {
		initDictionary(); 
	}; 
	
	std::map<int, std::pair<int, std::vector<int>>> dict() {
		return transformationDictionary;
	}
private: 
	void initDictionary(); 
	std::map<int, std::pair<int, std::vector<int>>> transformationDictionary; 
};


class AccessDictionary{
public:
	static BoardDictionary& getBoardDictionary() {
		static BoardDictionary staticStuff; // constructor runs once, when someone first needs it 
		return staticStuff; 
	} 
};
