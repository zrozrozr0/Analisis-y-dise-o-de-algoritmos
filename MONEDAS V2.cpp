// MakeCoinChange.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <algorithm>
using namespace std;

void PrintChanges(int arr[], int coin_change[], int coin_index, int change_index, int max_index, int amount_req)
{
	if (amount_req == 0)
	{
		for (int i = 0; i < change_index; i++)
		{
			cout << coin_change[i] << " ";
		}
		cout << endl;
		return;
	}
	else if (amount_req < 0)
	{
		//not feasible using this config so return
		return;
	}
	else if (coin_index > max_index)
	{
		//again not feasible so return
		return;
	}
	else
	{
		//i will use this coin but next time also i can use it so do not change coin index
		coin_change[change_index] = arr[coin_index];
		PrintChanges(arr, coin_change, coin_index,change_index++, max_index, amount_req - arr[coin_index]);
		//i not going to use this coin at all 
		PrintChanges(arr, coin_change, coin_index++, change_index, max_index, amount_req);
	}
}
void MakeCoinChange(int arr[], int amount)
{
	if (amount <= 0) return;

	int n = sizeof(arr) / sizeof(arr[0]); 

	int* coin_change = new int[n];
	PrintChanges(arr, coin_change, 0, 0, n - 1, amount);
	delete coin_change;
}

int main()
{
	int arr[] = {1,2,3};
	MakeCoinChange(arr,4);
    return 0;
}
