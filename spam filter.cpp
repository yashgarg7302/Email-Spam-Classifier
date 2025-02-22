#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<math.h>
#include<vector>
#include"Email.h"

using namespace std;

const int WORDS_SET_SIZE = 57;   
const double OFF_SET = 1.0/4000;  
vector<double> operator+(vector<double>& A, const vector<double>& B);

int main(){
    vector<double> num_words_spam(WORDS_SET_SIZE, 0);  
    vector<double> num_words_ham(WORDS_SET_SIZE, 0);
    int num_spam = 0, num_ham = 0; 
    vector<double> word_probability_spam(WORDS_SET_SIZE, 0);  
    vector<double> word_probability_ham(WORDS_SET_SIZE, 0);   

    ifstream file("training_set.data");
    if(!file){ cerr << "File cannot be opened"; exit(1); }

    Email* my_email = new Email();
    string email_data;
    while(getline(file, email_data)){
        my_email->setEmailData(email_data);
        if(my_email->isHam() == 0){
            num_spam++;
            num_words_spam = num_words_spam + my_email->wordsFrequency();
        } else {
            num_ham++;
            num_words_ham = num_words_ham + my_email->wordsFrequency();
        }
    }
    file.close();

    double total_words_spam = 0, total_words_ham = 0;
    for(int i=0; i<WORDS_SET_SIZE; i++){
        total_words_spam += num_words_spam[i];
        total_words_ham += num_words_ham[i];
    }
    for(int i=0; i<WORDS_SET_SIZE; i++){
        word_probability_spam[i] = log(num_words_spam[i] / total_words_spam);
        word_probability_ham[i] = log(num_words_ham[i] / total_words_ham);
    }

    ifstream test("test_set.data");
    if(!test){ cerr << "Cannot open test set"; exit(1); }

    int num_test_email = 0, num_ham_in_test = 0, num_spam_in_test = 0;
    int ham_predict_as_ham = 0, spam_predict_as_spam = 0;
    int ham_predict_as_spam = 0, spam_predict_as_ham = 0;

    while(getline(test, email_data)){
        my_email->setEmailData(email_data);
        num_test_email++;
        double log_ratio = 0;
        for(int i=0; i<WORDS_SET_SIZE; i++){
            log_ratio += my_email->wordsFrequency()[i] * (word_probability_spam[i] - word_probability_ham[i]);
        }
        log_ratio += log((double)num_spam) - log((double)num_ham);

        bool isActualSpam = !my_email->isHam();
        bool isPredictedSpam = log_ratio > 0;
        
        if (isActualSpam) num_spam_in_test++;
        else num_ham_in_test++;

        if(isPredictedSpam && isActualSpam) spam_predict_as_spam++; // TP
        else if(isPredictedSpam && !isActualSpam) ham_predict_as_spam++; // FP
        else if(!isPredictedSpam && isActualSpam) spam_predict_as_ham++; // FN
        else ham_predict_as_ham++; // TN
    }
    test.close();

    cout << "The training set has " << (num_ham + num_spam) << " emails" << endl;
    cout << "Spam emails: " << num_spam << endl;
    cout << "Ham emails: " << num_ham << endl;
    
    cout << "The test set has " << num_test_email << " emails" << endl;
    cout << "Spam emails: " << num_spam_in_test << endl;
    cout << "Ham emails: " << num_ham_in_test << endl;
    cout << "Ham predicted as ham: " << ham_predict_as_ham << endl;
    cout << "Spam predicted as spam: " << spam_predict_as_spam << endl;
    cout << "Spam predicted as ham: " << spam_predict_as_ham << endl;
    cout << "Ham predicted as spam: " << ham_predict_as_spam << endl;
    cout << "The prediction accuracy is: " << (ham_predict_as_ham + spam_predict_as_spam) * 1.0 / num_test_email * 100 << " percents" << endl;

    cout << "Confusion Matrix:\n";
    cout << "                Predicted Ham   Predicted Spam\n";
    cout << "Actual Ham   |    " << ham_predict_as_ham << "          " << ham_predict_as_spam << "\n";
    cout << "Actual Spam  |    " << spam_predict_as_ham << "          " << spam_predict_as_spam << "\n\n";

    double precision = (spam_predict_as_spam == 0) ? 0.0 : (double)spam_predict_as_spam / (spam_predict_as_spam + ham_predict_as_spam);
    double recall = (spam_predict_as_spam == 0) ? 0.0 : (double)spam_predict_as_spam / (spam_predict_as_spam + spam_predict_as_ham);
    double f1_score = (precision + recall == 0) ? 0.0 : 2 * (precision * recall) / (precision + recall);

    cout << "Precision: " << precision * 100 << " %\n";
    cout << "Recall: " << recall * 100 << " %\n";
    cout << "F1 Score: " << f1_score * 100 << " %\n";

    return 0;
}

vector<double> operator+(vector<double>& A, const vector<double>& B){
    if(A.size() != B.size()) throw "Vector size mismatch";
    vector<double> ans;
    for(size_t i = 0; i < A.size(); i++) ans.push_back(A[i] + B[i]);
    return ans;
}
