#include <string>
#include <iostream>
#include <list>
using namespace std;

class Editor {
public:
  Editor()
  : position_(text_.begin())
  , pos_(0) {}

  void Left() {
	  if(pos_ != 0) {
		  --pos_;
		  --position_;
	  }
  }

  void Right() {
	  if(pos_ < text_.size()) {
		  ++position_;
		  ++pos_;
	  }
  }

  void Insert(char token) {
	  text_.insert(position_, token);
	  ++pos_;
  }

  void Cut(size_t tokens = 1) {
	  buffer.clear();
	  if(tokens != 0) {
		  auto first = position_;
		  auto last = PosLast(tokens);
		  if(pos_ + tokens > text_.size()) {
			  last = text_.end();
		  }
		  buffer = {first, last};
		  position_ = last;
		  text_.erase(first, last);
	  }
  }

  void Copy(size_t tokens = 1) {
	  buffer.clear();
	  auto first = position_;
	  auto last = PosLast(tokens);
	  buffer = {first, last};
  }

  void Paste() {
	  if(!buffer.empty()) {
		  text_.insert(position_, buffer.begin(), buffer.end());
		  pos_ += buffer.size();
	  }
  }

  string GetText() const {
	  return {text_.begin(), text_.end()};
  }

private:
  list<char>::iterator PosLast(size_t tokens = 0) {
	  auto last = position_;
	  for(size_t i = 0; i < tokens; i++) {
		  last++;
	  }

	  return last;
  }
public:
  list<char> text_;
  string buffer;
  list<char>::iterator position_;
  size_t pos_;
};

int main() {
	return 0;
}
