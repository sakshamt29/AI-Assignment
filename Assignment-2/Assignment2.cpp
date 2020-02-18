#include <bits/stdc++.h>
using namespace std;
#define lli long long int
#define V1 4


priority_queue< pair<lli,pair<lli,pair<lli,pair<lli,lli*>>>>,

vector<pair<lli,pair<lli,pair<lli,pair<lli,lli*>>>>>, 

greater<pair<lli,pair<lli,pair<lli,pair<lli,lli*>>>>> > pr;
lli s;

lli heuristic(lli node,lli visited[],lli graph[][V1]);

void tr(lli node,lli cost,lli visited[],lli graph[][V1]);

int main()
{
  s=1;
  //cout<<s<<" 000"<<"    ";;  
  lli visited[V1+1]={0};
 
 
  lli g[][V1] =
{ { 0, 10, 15, 20 }, 
{ 10, 0, 35, 25 }, 
{ 15, 35, 0, 30 }, 
{ 20, 25, 30, 0 } }; 

 
   tr(s,0,visited,g);
 
 
  return 0;  
   
} 
void tr(lli node,lli cost,lli visited[],lli graph[][V1])
{
   lli mx=-1;
   
    for(lli i=1;i<=V1;i++)
   { if(visited[i]>=mx)
     mx=visited[i];
   }
       
       

   visited[node]=mx+1;

   
   
   lli z=0;  
   lli visited1[V1+1][V1+1]={0};
   lli visited2[V1+1][V1+1]={0};
   vector<lli>path1[V1+1];
   
   for(lli i=1;i<=V1;i++)
   {
      if(visited[i]==0)
    {
      for(lli j=1;j<=V1;j++)
      {
          visited1[i][j]=visited[j];
       
          if(visited[j]>=1)
          visited2[i][j]=1;
          else
          visited2[i][j]=0;    
      }
         
      lli heur=heuristic(i,visited2[i],graph);
      lli obj=heur+graph[node-1][i-1]+cost;    
      pr.push({obj,{i,{node,{cost,visited1[i]}}}});          
 
      z=z+1;
    }
       
   }
   

   
   if(z>=1)
   {pair<lli,pair<lli,pair<lli,pair<lli,lli*>>>> p2=pr.top();
    pr.pop();
   
    cost=p2.second.second.second.first + graph[p2.second.second.first-1][p2.second.first-1];
 
   
    tr(p2.second.first,cost,p2.second.second.second.second,graph);
   }
   
   else
   {
     vector<pair<lli,lli>>fp;
       
     cout<<"Path: ";  
     
     for(lli i=1;i<=V1;i++)
     fp.push_back({visited[i],i});
       
     sort(fp.begin(),fp.end());
     
     for(lli i=0;i<fp.size();i++)
     cout<<fp[i].second<<" ";
       

       
     cout<<"1 ";  
     cout<<"\n";
 
     cout<<"Cost: "<<cost+graph[node-1][s-1];
     return;
   }
   
} 

lli heuristic(lli node,lli visited[],lli graph[][V1])
{
       
   visited[node]=1;
   
     
   lli m1=100000,m2=100000;
   lli i,z=0,heu=0;
   


   for(i=1;i<=V1;i++)
   {
      if(visited[i]==0)
    {    
     
       
      if(graph[node-1][i-1]<m1)
      m1=graph[node-1][i-1];
     
      if(graph[i-1][s-1]<m2)
      m2=graph[i-1][s-1];
   
      z=z+1;    
    }
   }    
   
   if(z>=1)  
   heu+=m1+m2;

   return heu;
}
