#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define population 8

vector<vector<int>> form_population;
vector<int> marks_student;
set<int> gr_leader;
vector<vector<int>> groups;
void groups_p();
int fitness(int k, int n, int i);
int crossover(int e_1, int e_2, int k, int g1)
{
 gr_leader.clear();
 int in = k - 1, i;
 for (i = 0; i <= g1; i++)
 {
  gr_leader.insert(form_population[e_1][i]);
 }
 for (int j = i; j < k; j++)
 {
  gr_leader.insert(form_population[e_2][j]);
 }
 if (gr_leader.size() != k)
 {
  return 0;
 }
 else if (gr_leader.size() == k)
 {
  vector<int> temp1;
  for (auto it1 = gr_leader.begin(); it1 != gr_leader.end(); it1++)
  {
   temp1.pb(*it1);
  }
  groups.pb(temp1);
  return 1;
 }
}
void random(int k, int n, int i)
{
 int e, m;
 mt19937 mt_rand(time(0));
 while (gr_leader.size() != k)
 {
  e = rand() % n;
  gr_leader.insert(marks_student[e]);
 }
 m = 0;
 vector<int> temp;
 for (auto j = gr_leader.begin(); j != gr_leader.end(); j++)
 {
  temp.pb(*j);
  m++;
 }
 groups.pb(temp);
}

void groups_p()
{
 for (int i = 0; i < groups.size(); i++)
 {
  for (int j = 0; j < groups[i].size(); j++)
  {
   cout << groups[i][j] << " ";
  }
  cout << endl;
 }
 cout << "************************************"
      << "\n";
 int i = groups.size() - 1;
 int k = 0;
 int min = 0;
 int gr_no = 0;
 for (k = 0; k < marks_student.size(); k++)
 {
  min = 1000000;
  for (int j = 0; j < groups[i].size(); j++)
  {
   int num = (groups[i][j] - marks_student[k]) * (groups[i][j] - marks_student[k]);
   if (num < min)
   {
    min = num;
    gr_no = j + 1;
   }
  }
  cout << marks_student[k] << " in group no." << gr_no << "\n";
 }
}
int fitness(int k, int n, int i)
{
 int dis[k], fitne = 0, in, e;
 int j = 0;
 for (in = 0; in < n; in++)
 {
  auto gr = groups[i].begin();
  for (j = 0; j < k; j++)
  {
   dis[j] = marks_student[in] - (*gr);
   dis[j] = dis[j] * dis[j];
   gr++;
  }
  e = 1000020;
  for (j = 0; j < k; j++)
  {
   if (dis[j] < e)
   {
    e = dis[j];
   }
  }
  fitne = fitne + e;
 }
 return fitne;
}

int main()
{
 int n, k, e;
 cout << "Enter value of n:";
 cin >> n;
 cout << "Enter number of groups:";
 cin >> k;
 cout << "Enter marks of each student:";
 for (int i = 0; i < n; i++)
 {
  cin >> e;
  marks_student.pb(e);
 }
 vector<pair<int, int>> f;
 for (int i = 0; i < population; i++)
 {
  mt19937 mt_rand(time(NULL));
  random(k, n, i);
  gr_leader.clear();
 }
 for (int count1 = 0; count1 < 50; count1++)
 {
  for (int i = 0; i < population; i++)
  {
   int z = fitness(k, n, i);
   f.pb(make_pair(z, i));
  }
  sort(f.rbegin(), f.rend());
  int i = 0;
  mt19937 mt_rand(time(0));
  for (i = 0; i < population; i++)
  {
   e = rand() % 360;
   if (e >= 0 && e <= 10)
   {
    int indexno = f[0].second;
    form_population.pb(groups[indexno]);
   }
   else if (e >= 11 && e <= 30)
   {
    int indexno = f[1].second;
    form_population.pb(groups[indexno]);
   }
   else if (e >= 31 && e <= 60)
   {
    int indexno = f[2].second;
    form_population.pb(groups[indexno]);
   }
   else if (e >= 61 && e <= 100)
   {
    int indexno = f[3].second;
    form_population.pb(groups[indexno]);
   }
   else if (e >= 101 && e <= 150)
   {
    int indexno = f[2].second;
    form_population.pb(groups[indexno]);
   }
   else if (e >= 151 && e <= 210)
   {
    int indexno = f[2].second;
    form_population.pb(groups[indexno]);
   }
   else if (e >= 211 && e <= 280)
   {
    int indexno = f[2].second;
    form_population.pb(groups[indexno]);
   }
   else if (e >= 281 && e <= 360)
   {
    int indexno = f[2].second;
    form_population.pb(groups[indexno]);
   }
  }
  auto it = form_population.begin();
  int cur_pop = 0;
  for (i = 0; i < 4; i++)
  {
   groups[i].clear();
  }
  groups.clear();
  int indexno1 = 0, indexno2 = 1;
  while (cur_pop < population)
  {
   mt19937 mt_rand(time(NULL));
   int e_1 = rand() % 4;
   int e_2 = rand() % 4;
   int indexno = k - 1;
   indexno = rand() % indexno;
   int tell1 = crossover(e_1, e_2, k, indexno);
   int tell2 = crossover(e_2, e_1, k, indexno);
   if (tell1 == 0 || tell2 == 0)
   {
    groups.erase(groups.begin() + indexno1);
    continue;
   }
   else if (tell1 == 1 && tell2 == 1)
   {
    indexno1 = indexno + 2;
    indexno2 = 3;
    gr_leader.clear();
    cur_pop = cur_pop + 2;
   }
  }
 }
 groups_p();
}