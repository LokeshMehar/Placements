#include <bits/stdc++.h>
using namespace std;

// Build Segment Tree
void buildSumTree(int idx, int low, int high, const vector<int>& arr, vector<int>& seg) {
    if (low == high) 
	{
        seg[idx] = arr[low];
        return;
    }

    int mid = (low + high) / 2;
    buildSumTree(2 * idx + 1, low, mid, arr, seg);
    buildSumTree(2 * idx + 2, mid + 1, high, arr, seg);
    seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
}

void buildMinTree(int idx, int low, int high, const vector<int>& arr, vector<int>& seg) {
    if (low == high) 
	{
        seg[idx] = arr[low];
        return;
    }

    int mid = (low + high) / 2;
    buildMinTree(2 * idx + 1, low, mid, arr, seg);
    buildMinTree(2 * idx + 2, mid + 1, high, arr, seg);
    seg[idx] = min(seg[2 * idx + 1],seg[2 * idx + 2]);
}

void buildMaxTree(int idx, int low, int high, const vector<int>& arr, vector<int>& seg) {
    if (low == high) 
	{
        seg[idx] = arr[low];
        return;
    }

    int mid = (low + high) / 2;
    buildMaxTree(2 * idx + 1, low, mid, arr, seg);
    buildMaxTree(2 * idx + 2, mid + 1, high, arr, seg);
    seg[idx] = max(seg[2 * idx + 1],seg[2 * idx + 2]);
}

void buildMaxIndexTree(int idx, int low, int high, const vector<int>& arr, vector<int>& seg)
{
	if(low == high)
	{
		seg[idx] = low;
		return;
	}
	int mid = low + ((high - low) >> 1);
	buildMaxIndexTree(2*idx + 1,low,mid,arr,seg);
	buildMaxIndexTree(2*idx + 2,mid+1,high,arr,seg);
	if(arr[seg[2*idx + 1]] >= arr[seg[2*idx + 2]])
		seg[idx] = seg[2*idx + 1];
	else
		seg[idx] = seg[2*idx + 2];
}







void updateSumTree(int idx,int low,int high,int targetIdx,int val,const vector<int>& arr, vector<int>& seg)
{
	if (low == high) 
	{
		seg[idx] = val;
		return;
	}
	int mid = (low + high) / 2;
	if(mid>=targetIdx)
    	updateSumTree(2 * idx + 1, low, mid,targetIdx,val, arr, seg);
	else
    	updateSumTree(2 * idx + 2, mid + 1, high,targetIdx,val, arr, seg);
    seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
}

void updateMinTree(int idx,int low,int high,int targetIdx,int val,const vector<int>& arr, vector<int>& seg)
{
	if (low == high) 
	{
		seg[idx] = val;
		return;
    }
	int mid = (low + high) / 2;
	if(mid>=targetIdx)
    	updateMinTree(2 * idx + 1, low, mid,targetIdx,val, arr, seg);
	else
    	updateMinTree(2 * idx + 2, mid + 1, high,targetIdx,val, arr, seg);
    seg[idx]  = min(seg[2 * idx + 1],seg[2 * idx + 2]);
}

void updateMaxTree(int idx,int low,int high,int targetIdx,int val,const vector<int>& arr, vector<int>& seg)
{
	if (low == high) 
	{
		seg[idx] = val;
		return;
    }
	int mid = (low + high) / 2;
	if(mid>=targetIdx)
    	updateMaxTree(2 * idx + 1, low, mid,targetIdx,val, arr, seg);
	else
    	updateMaxTree(2 * idx + 2, mid + 1, high,targetIdx,val, arr, seg);
    seg[idx] = max(seg[2 * idx + 1],seg[2 * idx + 2]);
}


void updateRangeSumTree(int idx,int low,int high,int start,int end,int val,vector<int>& seg,vector<int>& lazy)
{
	if(lazy[idx] != 0)
	{
		seg[idx] += (high - low + 1)*lazy[idx];
		if(low != high)
		{
			lazy[2* idx + 1] += lazy[idx];
			lazy[2* idx + 2] += lazy[idx];

		}
		lazy[idx] = 0;
	}
	if(low > end || high < start )return;
	if(low  >=  start && high <= end)
	{
		seg[idx] += (high - low + 1)*val;
		if(low != high)
		{
			lazy[2* idx + 1] += val;
			lazy[2* idx + 2] += val;

		}
		return;
	}
	int mid = low + ((high - low)>>1);
	updateRangeSumTree(2* idx + 1,low,mid,start,end,val,seg,lazy);
	updateRangeSumTree(2*idx  + 2,mid+1,high,start,end,val,seg,lazy);
	seg[idx] = seg[2*idx + 1] + seg[2*idx + 2];
}

void updateRangeMinTree(int idx,int low,int high,int start,int end,int val,vector<int>& seg,vector<int>& lazy)
{
	if(lazy[idx] != 0)
	{
		seg[idx] = min(seg[idx], lazy[idx]);
		if(low != high)
		{
			if(lazy[2* idx + 1] == 0)
				lazy[2* idx + 1] = lazy[idx];
			else
				lazy[2* idx + 1] = min(lazy[2* idx + 1], lazy[idx]);
			
			if(lazy[2* idx + 2] == 0)
				lazy[2* idx + 2] = lazy[idx];
			else
				lazy[2* idx + 2] = min(lazy[2* idx + 2], lazy[idx]);
		}
		lazy[idx] = 0;
	}
	if(low > end || high < start) return;
	if(low >= start && high <= end)
	{
		seg[idx] = min(seg[idx], val);
		if(low != high)
		{
			if(lazy[2* idx + 1] == 0)
				lazy[2* idx + 1] = val;
			else
				lazy[2* idx + 1] = min(lazy[2* idx + 1], val);
			
			if(lazy[2* idx + 2] == 0)
				lazy[2* idx + 2] = val;
			else
				lazy[2* idx + 2] = min(lazy[2* idx + 2], val);
		}
		return;
	}
	int mid = low + ((high - low)>>1);
	updateRangeMinTree(2* idx + 1, low, mid, start, end, val, seg, lazy);
	updateRangeMinTree(2* idx + 2, mid+1, high, start, end, val, seg, lazy);
	seg[idx] = min(seg[2*idx + 1], seg[2*idx + 2]);
}

void updateRangeMaxTree(int idx,int low,int high,int start,int end,int val,vector<int>& seg,vector<int>& lazy)
{
	if(lazy[idx] != 0)
	{
		seg[idx] = max(seg[idx], lazy[idx]);
		if(low != high)
		{
			if(lazy[2* idx + 1] == 0)
				lazy[2* idx + 1] = lazy[idx];
			else
				lazy[2* idx + 1] = max(lazy[2* idx + 1], lazy[idx]);
			
			if(lazy[2* idx + 2] == 0)
				lazy[2* idx + 2] = lazy[idx];
			else
				lazy[2* idx + 2] = max(lazy[2* idx + 2], lazy[idx]);
		}
	}
	if(low > end || high < start) return;
	if(low >= start && high <= end)
	{
		seg[idx] = max(seg[idx], val);
		if(low != high)
		{
			if(lazy[2* idx + 1] == 0)
				lazy[2* idx + 1] = val;
			else
				lazy[2* idx + 1] = max(lazy[2* idx + 1], val);
			
			if(lazy[2* idx + 2] == 0)
				lazy[2* idx + 2] = val;
			else
				lazy[2* idx + 2] = max(lazy[2* idx + 2], val);
		}
		return;
	}
	int mid = low + ((high - low)>>1);
	updateRangeMaxTree(2* idx + 1, low, mid, start, end, val, seg, lazy);
	updateRangeMaxTree(2* idx + 2, mid+1, high,start, end, val, seg, lazy);
	seg[idx] = max(seg[2*idx + 1], seg[2*idx + 2]);
}




int rangeSum(int idx,int low,int high,int  start,int end,vector<int>& seg)
{
	if( low > end   || high <start)
	{
		return 0;
	}
	if(low >= start && high <=end)
	{ 
		return seg[idx];
	}
	int mid = low + ((high - low)>>1);
	return rangeSum(2* idx + 1,low,mid,start,end,seg) + rangeSum(2* idx + 2,mid+1,high,start,end,seg);
}

int rangeMin(int idx,int low,int high,int  start,int end,vector<int>& seg)
{
	if( low > end   || high <start)
	{
		return INT_MAX;
	}
	if(low >= start && high <=end)return seg[idx];
	int mid = low + ((high - low)>>1);
	return min(rangeMin(2*idx + 1,low,mid,start,end,seg),rangeMin(2*idx + 2,mid + 1,high,start,end,seg));
}

int rangeMax(int idx,int low,int high,int  start,int end,vector<int>& seg)
{
	if( low > end   || high <start)
	{
		return INT_MIN;
	}
	if(low >= start && high <=end)return seg[idx];
	int mid = low + ((high - low)>>1);
	return max(rangeMax(2*idx + 1,low,mid,start,end,seg),rangeMax(2*idx + 2,mid + 1,high,start,end,seg));
}

void buildMaxIndexTree(int idx, int low, int high,vector<int>& arr, vector<int>& seg) 
{
	if (low == high) {
		seg[idx] = low; // Store index of the maximum element
		return;
	}

	int mid = (low + high) / 2;
	buildMaxIndexTree(2 * idx + 1, low, mid, arr, seg);
	buildMaxIndexTree(2 * idx + 2, mid + 1, high, arr, seg);
	
	// Compare the values at the indices stored in the children
	if (arr[seg[2 * idx + 1]] >= arr[seg[2 * idx + 2]]) {
		seg[idx] = seg[2 * idx + 1];
	} else {
		seg[idx] = seg[2 * idx + 2];
	}
}

int rangeMaxIndexThanMin(int idx,int low,int high,int  start,int end,int target,vector<int>& seg,vector<int>& arr)
{
	if( low > end   || high <start || arr[seg[idx]] < target)
	{
		return -1;
	}
	if(low >= start && high <=end && arr[seg[idx]] >= target)
	{
		if(low == high) return seg[idx]; // If we are at a leaf node, return the index
		int mid = low + ((high - low)>>1);
		int leftIndex = rangeMaxIndexThanMin(2*idx + 1,low,mid,start,end,target,seg,arr);
		if(leftIndex != -1) return leftIndex; // If found in left subtree, return it
		return seg[idx]; // Otherwise, return the current index
	}
	return -1; // mujhe nhi lagta control kabhi yha aayega!!
}


void updateMaxIndexThanMin(int idx,int low,int high,int targetIdx,vector<int>& arr, vector<int>& seg)
{
	if(low == high)
	{
		seg[idx] = -1; // Update the index of the maximum element
		return;
	}
	int mid = low + ((high - low) >> 1);
	if(mid >= targetIdx)
		updateMaxIndexThanMin(2*idx + 1,low,mid,targetIdx,arr,seg);
	else
		updateMaxIndexThanMin(2*idx + 2,mid+1,high,targetIdx,arr,seg);

	if( seg[2*idx + 1] == -1  && seg[2*idx + 2] == -1)
		seg[idx] = -1;
	else if(seg[2*idx + 1] == -1)
		seg[idx] = seg[2*idx + 2];
	else if(seg[2*idx + 2] == -1)
		seg[idx] = seg[2*idx + 1];
	else
	{
		if(arr[seg[2*idx + 1]] >= arr[seg[2*idx + 2]])
			seg[idx] = seg[2*idx + 1];
		else
			seg[idx] = seg[2*idx + 2];
	}
}

int rangeMaxIndex(int idx,int low,int high,int  start,int end,vector<int>& seg,vector<int>& arr)
{
	if( low > end   || high <start)
	{
		return -1;
	}
	if(low >= start && high <=end)return seg[idx];
	int mid = low + ((high - low)>>1);
	int leftIndex = rangeMaxIndex(2*idx + 1,low,mid,start,end,seg);
	int rightIndex = rangeMaxIndex(2*idx + 2,mid + 1,high,start,end,seg);
	if(leftIndex == -1) return rightIndex;
	if(rightIndex == -1) return leftIndex;
	return arr[leftIndex] >= arr[rightIndex] ? leftIndex : rightIndex;
}

void buildMinIndexTree(int idx, int low, int high,vector<int>& arr, vector<int>& seg) 
{
	if (low == high) {
		seg[idx] = low; // Store index of the minimum element
		return;
	}

	int mid = (low + high) / 2;
	buildMinIndexTree(2 * idx + 1, low, mid, arr, seg);
	buildMinIndexTree(2 * idx + 2, mid + 1, high, arr, seg);
	
	// Compare the values at the indices stored in the children
	if (arr[seg[2 * idx + 1]] <= arr[seg[2 * idx + 2]]) {
		seg[idx] = seg[2 * idx + 1];
	} else {
		seg[idx] = seg[2 * idx + 2];
	}
}

int rangeMinIndex(int idx,int low,int high,int  start,int end,vector<int>& seg,vector<int>& arr)
{
	if( low > end   || high <start)
	{
		return -1;
	}
	if(low >= start && high <=end)return seg[idx];
	int mid = low + ((high - low)>>1);
	int leftIndex = rangeMinIndex(2*idx + 1,low,mid,start,end,seg);
	int rightIndex = rangeMinIndex(2*idx + 2,mid + 1,high,start,end,seg);
	if(leftIndex == -1) return rightIndex;
	if(rightIndex == -1) return leftIndex;
	return arr[leftIndex] <= arr[rightIndex] ? leftIndex : rightIndex;
}





// Print Segment Tree in Level Order
void printSegmentTree(const vector<int>& seg) {
    queue<pair<int, int>> qu; // {index, level}
    qu.push({0, 0});
    int prevLevel = -1;

    while (!qu.empty()) {
        auto [idx, level] = qu.front();
        qu.pop();

        if (idx >= seg.size()) continue;

        if (level != prevLevel) {
            cout << "\nLevel " << level << ": ";
            prevLevel = level;
        }

        cout << seg[idx] << " ";

        qu.push({2 * idx + 1, level + 1});
        qu.push({2 * idx + 2, level + 1});
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter Size of Array: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter Array elements:\n";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    vector<int> seg(4 * n); // Safe size for segment tree
    vector<int> lazy(4*n,0);
    buildSumTree(0, 0, n - 1, arr, seg);

    cout << "\nSegment Tree (Level Order):";
    printSegmentTree(seg);

    return 0;
}