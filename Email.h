

#include <vector>
#include <string>

extern const int WORDS_SET_SIZE;
extern const double OFF_SET;

using std::vector;
using std::string;


class Email{
 private: 
	
	int word_set_size_;  

	vector<double> words_frequency_;  
								 
	int spam_or_ham_;  

	double num_words_;  

public:
	Email();
	~Email();

	int isHam() const;

	double numWords() const; 
	const vector<double>& wordsFrequency() const;
	void setEmailData(string& email_data);
};
