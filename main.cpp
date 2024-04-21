
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <sstream>
#include <string.h>
#include "csvstream.hpp"
#include <map>
#include <set>
#include <cmath>
#include <algorithm>  // For std::set_union
#include <iterator>   // For std::inserter

using namespace std;

// Hand written comments from AG


// //OVERVIEW: This class is used to train a Bayesian trainer
// //         It reads a csv file and trains the model

set<string> unique_words(const string &str) {
    istringstream source(str);
    set<string> words;
    string word;
    while (source >> word) {
        words.insert(word);
    }
    return words;
}

//OVERVIEW: This function calculates the log probability of a word given a label
//          The formula used is:
//          log(Prob(word|label)) = log(num_posts_with_word_label/num_posts_with_label)
//          if this word is not found in the label but found in posts, then the probability is defined as
//          log(Prob(word|label)) = log(num_posts_with_word/totalposts)
//          if this word is never seen, themn we use
//          log(Prob(word|label)) = log(1/totalposts)
double calcprob(int wlp, int lp, int wp, int totalposts){
  if(wlp == 0){
    if(wp == 0){
        return log(1.0/totalposts);
    }
    else{
        return log(1.0*wp/totalposts);
    }
  }

  return log(1.0*wlp/lp);

}

class Bayestrainer{

private:
  string file;
  int totalposts;
  set <string> words;
  bool debug;

  map<string, int> num_posts_with_word;

  map<string, int> num_posts_with_label;

  map<pair<string, string>, int> num_posts_with_label_with_word;

public:

  Bayestrainer(string file, bool debug ): file(file), totalposts(0),  debug(debug){}



  void openfile(string file){
    csvstream csvin(file);

    map<string, string> row;

    if(debug) {
            cout << "training data:" << '\n';
    }

    while(csvin >> row){

        totalposts++;
        string content = row["content"];
        string label = row["tag"];

        count_words(content);
        num_posts_word(content);
        num_posts_label(label);
        num_posts_word_label(content, label);

        if(debug){
          cout << "  label = " << row["tag"] << ", content = " << row["content"] 
                << '\n';
        }
    }


  }

  void train(string file){
    openfile(file);
    cout << "trained on " << totalposts << " examples" << '\n';
    if(debug){
    cout << "vocabulary size = " << words.size() << '\n';
    }
    
    cout << "\n";
    if(debug){
      cout << "classes:" << '\n';
      for(auto &iter: num_posts_with_label) {
          string label = iter.first;
          int numPosts = num_posts_with_label.at(label);
          cout << "  " << label << ", " << numPosts << " examples, log-prior = " 
          << log(1.0*numPosts/totalposts) << '\n';
      }
    }

    if(debug){
        cout << "classifier parameters:" << endl;
        for(auto &iter: num_posts_with_label) {
            string label = iter.first;
            for(string word: words) {
                if(num_posts_with_label_with_word.count({word, label})) {
                    int count = num_posts_with_label_with_word.at({word, label});
                    cout << "  " << label << ":" << word << ", count = " << count
                    << ", log-likelihood = " 
                    << log(1.0*count/num_posts_with_label.at(label)) << '\n';
                }
            }
        }
        cout << '\n';
    }
    
  }

//OVERVIEW: This function calculates the probability of a word given a label
//          Log probability is used to avoid underflow
//          The formula used is:
//          log(Prob(word|label)) = log(num_posts_with_word_label/num_posts_with_label) 
//          if this word is not found in the label but found in posts, then the probability is defined as
//          log(Prob(word|label)) = log(num_posts_with_word/totalposts)
//          if this word is never seen, themn we use
//          log(Prob(word|label)) = log(1/totalwords)

pair<string, double> calc_prob(const string &content) const{
    auto content_words = unique_words(content);
    double max_prob = -numeric_limits<double>::infinity();
    string best_label;
    
    for (const auto &label_count : num_posts_with_label) {
        const string &label = label_count.first;
        double label_prob = log(1.0*label_count.second / totalposts);
        double log_likelihood = label_prob;

        for (const string &word : content_words) {
            int wlp = num_posts_with_label_with_word.count({word, label}) 
            ? num_posts_with_label_with_word.at({word, label}) : 0;

            int wp = num_posts_with_word.count(word) ? num_posts_with_word.at(word) : 0;

            int lp = num_posts_with_label.at(label);

            log_likelihood += calcprob(wlp, lp, wp, totalposts);
            
        }

        if (log_likelihood > max_prob) {
            max_prob = log_likelihood;
            best_label = label;
        }
    }

    return {best_label, max_prob};
  }

private:

//OVERVIEW: This function counts the number of words in the content
//         and stores them in a set
  void count_words(const string &content){
    set<string> uniqcontent = unique_words(content);
    set <string> result;


    std::set_union(words.begin(), words.end(),
                   uniqcontent.begin(), uniqcontent.end(),
                   std::inserter(result, result.begin()));

    words = std::move(result);
  }

//OVERVIEW: This function counts the number of posts with the word
//         and stores them in a map
  void num_posts_word(const string &content){
    set <string> uniqcontent = unique_words(content);
    for(string word: words){
        if(uniqcontent.find(word) != uniqcontent.end()){
            num_posts_with_word[word]++;
        }
    }
  }

//OVERVIEW: This function counts the number of posts with the label
//         and stores them in a map
  void num_posts_label(const string &label){
    num_posts_with_label[label]++;
  }

//OVERVIEW: This function counts the number of posts with the word and label
//         and stores them in a map
  void num_posts_word_label(const string &content, const string &label){
    set <string > uniqcontent = unique_words(content);
    for(string word: uniqcontent){
        num_posts_with_label_with_word[{word, label}]++;
    }
  }


};

class Classifier {

private:
  bool debug;

  Bayestrainer model;

  string testfile;

  string trainfile;

  int correct;

  int total;

public:

    Classifier(bool debug, string testfile, string trainfile): debug(debug), model(trainfile, debug),
    testfile(testfile), trainfile(trainfile), correct(0), total(0){}

//OVERVIEW: This function trains the model
    void modelinit(){
        model = Bayestrainer(trainfile, debug);
    }

    void train(){
        model.train(trainfile);
    }


//OVERVIEW: This function tests the model
//          It reads a csv file and tests the model
//          It calculates the probability of each label for each post
//          It returns the label with the highest probability
//          The formula for log-likelihood of a label given a post is:
//          log(Prob(label|post)) = log(Prob(label)) + sum(log(Prob(word|label)))



  void test(){
    csvstream csvin(testfile);
    map<string, string> row;
    cout << "test data:" << '\n';

    while(csvin >> row){
        total++;
        string content = row["content"];
        string label = row["tag"];

        pair<string, double > bestpred = model.calc_prob(content);

        if(label == bestpred.first){
            correct++;
        }
        cout << "  correct = " << label << ", predicted = " << 
            bestpred.first << ", log-probability score = " <<
            bestpred.second << endl;
            cout << "  content = " << row["content"] << '\n' << '\n';
    }
    cout << "performance: " << correct << " / " << total << 
     " posts predicted correctly" << '\n';
}



};


int main(int argc, char* argv[]){
    cout.precision(3);

    bool debug = false;

    string testfile;
    string trainfile;

    if(argc != 3 && argc != 4){
      cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
      return 10086;
    }

    if(argc == 4 && !strcmp(argv[3], " --debug")){
      cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
      return 10086;
    }
    
    if(argc == 4){
      debug = true;
    }
    
    trainfile = argv[1];
    testfile = argv[2];

    try { csvstream csvin(trainfile); }
    catch (const std::exception &e) {
         cout << "Error opening file: " << trainfile << endl; return 10086;
    }

    try { csvstream csvin(testfile); }
    catch (const std::exception &e) {
         cout << "Error opening file: " << testfile << endl; return 10086;
    }

    Classifier Alex(debug, testfile, trainfile);

    Alex.modelinit();

    Alex.train();
    Alex.test();

}