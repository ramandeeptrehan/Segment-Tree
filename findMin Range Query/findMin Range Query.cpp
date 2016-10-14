//
//  findMin Range Query.cpp
//  Segment Tree
//
//  Created by Ramandeep Singh Trehan on 14/10/16.
//  Copyright © 2016 Ramandeep Singh Trehan. All rights reserved.
//

#include <stdio.h>
#include <limits>
#include <iostream>

using namespace std;

void buildTree(int arr[], int segTree[], int low, int high, int pos);
int minRangeQuery(int segTree[] , int qlow, int qhigh, int low, int high, int pos);

int main()
{
    int n;
    cout<<"Enter the size of input array: \n";
    cin>>n;
    int input[n];
    
    cout<<"Enter the elements in array: \n";
    for(int i=0; i<n; i++)
        cin>>input[i];
    
    int segTree[4*n];
    memset(segTree, INT_MAX, sizeof(segTree));
    
    // Building the segment tree
    buildTree(input, segTree, 0, n-1, 0);
    cout<<"\nSegment tree has been built\n\n";
    
    // Range Query
    int qlow, qhigh;
    cout<<"RANGE QUERY PROCESSING:\n\n";
    cout<<"Enter the query range(u v):\n";
    
    cin>>qlow>>qhigh;
    int min = minRangeQuery(segTree, qlow, qhigh, 0, n-1, 0);
    cout<<"\nMinimum in range ["<<qlow<< ", "<<qhigh<<"] is "<<min<<endl;

}

void buildTree(int arr[], int segTree[], int low, int high, int pos)
{
    if(low==high)
    {
        segTree[pos] = arr[low];
        return;
    }
    
    int mid = (low+high)/2;
    
    buildTree(arr, segTree, low, mid, 2*pos + 1);
    buildTree(arr, segTree, mid+1, high, 2*pos + 2);
    
    segTree[pos] = min(segTree[2*pos + 1], segTree[2*pos + 2]);

}

int minRangeQuery(int segTree[], int qlow, int qhigh, int low, int high, int pos)
{
    if(qlow>high || qhigh<low) //no overlap
        return INT_MAX;
    
    if(qlow<=low && qhigh>=high) //total overlap
        return segTree[pos];
    
    //partial overlap
    int mid = (low+high)/2;
    
    return min(minRangeQuery(segTree, qlow, qhigh, low, mid, 2*pos + 1), minRangeQuery(segTree, qlow, qhigh, mid + 1, high, 2*pos + 2));
    
}