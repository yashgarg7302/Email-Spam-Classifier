#include "Email.h"
#include<iostream>
#include<sstream>

using std::vector;
using std::string;
using std::stringstream;

Email::Email(){
	word_set_size_ = WORDS_SET_SIZE;
	vector<double> tmp(WORDS_SET_SIZE,0);
	words_frequency_ = tmp;
	spam_or_ham_ = 0;
	num_words_ = 0;
}

Email::~Email(){}

int Email::isHam() const{ return spam_or_ham_; }

double Email::numWords() const {return num_words_; }

const vector<double>& Email::wordsFrequency() const{
	return words_frequency_;
}

void Email::setEmailData(string& email_data){

	stringstream ss(email_data);
	
	string s;
	for(int i=0;i<word_set_size_+1;i++){
		
		getline(ss,s,',');
		
		stringstream toNumber(s);
		if(i == word_set_size_){
			
			toNumber>>spam_or_ham_; 
		}else{
			
			toNumber>>words_frequency_[i];
			
			words_frequency_[i] += OFF_SET; 
			
			num_words_ += words_frequency_[i];
		}
	}	
}
