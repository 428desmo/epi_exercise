#include <iostream>
#include <assert.h>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <unordered_set>

int StringHash(const std::string& str, int mod) {
  const int kMult = 997;
  int val = 0;
  for (char c : str)
    val = (val * kMult + c) % mod;
  return val;
}

using std::vector;
using std::string;
vector<vector<string>> FindAnagrams(const vector<string>& dict) {
  std::unordered_map<string, vector<string>> sorted_str_to_anagrams;
  for (const string& s : dict) {
    string sorted_str(s);
    std::sort(sorted_str.begin(), sorted_str.end());
    sorted_str_to_anagrams[sorted_str].emplace_back(s);
  } 
  vector<vector<string>> anagram_groups;
  for (const auto& s : sorted_str_to_anagrams)
    if (s.second.size() > 1)
      anagram_groups.emplace_back(s.second);

  return anagram_groups;
}

using std::unordered_set;
struct ContactList {
  bool operator==(const ContactList& that) const {
    return unordered_set<string>(names.begin(), names.end()) ==
           unordered_set<string>(that.names.begin(), that.names.end());
  }

  ContactList(vector<string> names) : names(names) {}

  vector<string> names;
};

struct HashContactList {
  size_t operator()(const ContactList& contacts) const {
    size_t hash = 0;
//    for (const string& name : unordered_set<string>(contacts.names.begin(), contacts.names.end())) {
    for (auto& name : unordered_set<string>(contacts.names.begin(), contacts.names.end())) {
      static int k = 997;
      hash ^= std::hash<string>()(name);
    }
    return hash;
  }
};

void DumpContactLists(const vector<ContactList>& L)
{
  for (auto& list : L) {
    std::cout << "  ";
    for (auto& name : list.names) {
      std::cout << name << " ";
    }
    std::cout << std::endl;
  }
}


vector<ContactList> MergeContactLists(const vector<ContactList>& contacts) {
  // duplicate contacts wouldn't be added. Duplicate-ness is checked by HashContactList
  unordered_set<ContactList, HashContactList> unique_contacts(contacts.begin(), contacts.end());
  return {unique_contacts.begin(), unique_contacts.end()};
}

int main(int argc, char* argv[])
{
  std::string A("abc"), B("cba"), C("abcd");
  std::cout << A << " mod 256 -> " << StringHash(A, 256) << std::endl;
  std::cout << A << " mod 997 -> " << StringHash(A, 997) << std::endl;
  std::cout << A << " mod 100 -> " << StringHash(A, 100) << std::endl;
  std::cout << B << " mod 256 -> " << StringHash(B, 256) << std::endl;
  std::cout << B << " mod 997 -> " << StringHash(B, 997) << std::endl;
  std::cout << B << " mod 100 -> " << StringHash(B, 100) << std::endl;
  std::cout << C << " mod 256 -> " << StringHash(C, 256) << std::endl;
  std::cout << C << " mod 997 -> " << StringHash(C, 997) << std::endl;
  std::cout << C << " mod 100 -> " << StringHash(C, 100) << std::endl;

  vector<string> D = {"debitcard", "elvis", "silent", "badcredit", "lives", "freedom", "listen", "levis", "money"};
  vector<vector<string>> result = FindAnagrams(D);
  for (vector<string>& v : result) {
    for (string& s : v) {
      std::cout << s << " ";
    }
    std::cout << std::endl;
  }

  ContactList E({string("Alice"), string("Bob"), string("Carol")});
  ContactList F({string("Bob"), string("Alice"), string("Carol")});
  ContactList G({string("Alice"), string("Bob"), string("Carol"), string("David")});
  ContactList H({string("Emma"), string("Furgus"), string("Greg")});

  vector<ContactList> S = {E, F, G, H};
  std::cout << "before merge:" << std::endl;
  DumpContactLists(S);

  vector<ContactList> M = MergeContactLists(S);
  std::cout << "after merge:" << std::endl;
  DumpContactLists(M);

  return 0;
}
