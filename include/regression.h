#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

namespace regression {

using Data = vector<vector<double>>;

Data read_database(string filepath);
double hypothesis(vector<double> theta, vector<double> x);

double cost_function(Data dataset, vector<double> theta);

inline Data read_database(string filepath) {
  string line, word;
  ifstream myfile(filepath);
  vector<vector<double>> data;
  // cout << myfile.good() << endl;
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      stringstream str(line);
      vector<double> row;
      row.push_back(1.0);
      while (getline(str, word, ',')) {
        row.push_back(stod(word));
      }
      // cout << row.size() << endl;
      data.push_back(row);
    }
    myfile.close();
  } else {
    throw std::runtime_error("Unable to open");
  }
  return data;
}

inline double hypothesis(vector<double> theta, vector<double> x) {
  double ans = 0;
  if (theta.size() == x.size()) {
    for (int i = 0; i < theta.size(); i++) {
      //cout << theta[i]* x[i] << endl;
      ans += (theta[i] * x[i]);
    }
  } else {
    throw std::logic_error("error message");
  }
  return ans;
}

inline double cost_function(Data dataset, vector<double> theta) {
  double cost= 0;
  for (int i = 0; i < dataset.size(); i++) {
    vector<double> tmpvector;
    tmpvector.push_back(dataset[i][0]);
    tmpvector.push_back(dataset[i][1]);
    tmpvector.push_back(dataset[i][2]);
    tmpvector.push_back(dataset[i][3]);
    cost += (hypothesis(theta, tmpvector) - dataset[i][4]) *
            (hypothesis(theta, tmpvector) - dataset[i][4]);
  };
  cost = cost / 2;
  return cost;
}

// inline vector<double> update(Data dataset, vector<double> theta, double lr) {
//   vector<double> &ans = theta;
//   for (int i = 0; i < ans.size(); i++) {
//     ans[i] = ans[i] - lr * cost_function(dataset, theta);
//   }
//   return ans;
// }

// inline vector<double> linear_regression(Data dataset, vector<double>
// init_theta,
//                                         double lr) {

//                                         }

} // namespace regression