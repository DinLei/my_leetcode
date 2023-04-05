#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {

  vector<int> big_vector = {5, 12, 4, 6, 7, 8, 9, 9, 31, 1, 1, 5, 76, 78, 8};
  vector<int> subvector = {big_vector.begin() + 3, big_vector.end() - 2};
  vector<int> subvector2 = {big_vector.begin() + 3, big_vector.begin() + 5};

  cout << "Big vector: ";
  for_each(big_vector.begin(), big_vector.end(),
           [](int number) { cout << number << ";"; });
  cout << endl << "Subvector: ";
  for_each(subvector.begin(), subvector.end(),
           [](int number) { cout << number << ";"; });

  cout << endl << "Subvector2: ";
  for_each(subvector2.begin(), subvector2.end(),
           [](int number) { cout << number << ";"; });
  cout << endl;
}