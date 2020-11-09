#include "test_runner.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
using namespace std;


template <typename Token>
using Sentence = vector<Token>;

//bool IsEndSentencePunctuation() const
/*
template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
	vector<Sentence<Token>> sentences;

    if (tokens.empty())
    {
        return move(sentences);
    }

    Sentence<Token> sentence;
	auto iter = begin(tokens);
    while (iter != end(tokens)) {
        bool IsEndSentencePunctuation = (*iter).IsEndSentencePunctuation();

        if (IsEndSentencePunctuation) {
            do {
                sentence.push_back(move(*iter));
                ++iter;
            } while (iter != end(tokens) && (*iter).IsEndSentencePunctuation());

            sentences.push_back(move(sentence));
        } else {
            sentence.push_back(move(*iter));
            ++iter;
        }
    }

    if (!sentence.empty())  {
        sentences.push_back(move(sentence));
    }

	return move(sentences);
}
*/


template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
	vector<Sentence<Token>> sentences;

    if (tokens.empty())
    {
        return move(sentences);
    }

    Sentence<Token> sentence;
	auto iter = begin(tokens);

    while (iter != end(tokens)) {
    	while(iter != end(tokens) && !(*iter).IsEndSentencePunctuation()) {
            sentence.push_back(move(*iter));
            ++iter;
    	}

    	while(iter != end(tokens) && (*iter).IsEndSentencePunctuation()) {
            sentence.push_back(move(*iter));
            ++iter;
    	}

    	sentences.push_back(move(sentence));
    }

    if (!sentence.empty())  {
        sentences.push_back(move(sentence));
    }

	return move(sentences);
}

int main() {
	return 0;
}
