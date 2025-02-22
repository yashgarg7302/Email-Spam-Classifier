## Spam Email Classifier using Naïve Bayes in C++

1️⃣ Introduction (Problem Statement)
* Spam emails are a significant problem in email communication.
* Manually filtering them is inefficient, so automated classification using machine learning is necessary.
* This project implements a Naïve Bayes Classifier in C++ to classify emails as spam or ham (legitimate emails).
  
2️⃣ Methodology (How It Works)

✅ Dataset Used
* The project uses 4202 emails for training and 401 emails for testing.
  
✅ Preprocessing Steps

* Load the dataset from training_set.data and test_set.data.
* Tokenize email text and extract important words.
* Compute word probabilities using Bayes' Theorem.
* Classify emails based on probability scores.
  
✅ Algorithm Used

Implemented Naïve Bayes Classifier:

![Image](https://github.com/user-attachments/assets/8fee7025-b3fe-4509-a5df-5a2a6e3b4e9f)
​


* P(Spam|Email): Probability that the email is spam
* P(Email|Spam): Probability of the words occurring in a spam email
* P(Spam): Prior probability of spam emails in the dataset
* P(Email): Prior probability of any email
 
✅ Implementation in C++

* The project uses C++ STL (Standard Template Library) for data structures.
* Email.h and Email.cpp handle email processing.
* spam filter.cpp is the main driver code.
  
3️⃣ Results (Model Performance)

The classifier was tested on 401 emails:

* Ham (Legitimate emails) correctly predicted: 150
* Spam correctly predicted: 164
* Spam wrongly classified as Ham (False Negative): 37
* Ham wrongly classified as Spam (False Positive): 50
* Final Accuracy: 78.3%
  
![Image](https://github.com/user-attachments/assets/a0334b7f-f2b9-4576-874e-10801a447e61)


* Precision: 76.5258 %
* Recall: 81.5 %
* F1 Score: 78.9346 %
