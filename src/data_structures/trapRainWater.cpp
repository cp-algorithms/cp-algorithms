class Solution {
public:
    int trap(vector<int>& height) {
        // OPTIMAL APPROACH
        // TC = O(N) SC = O(1)
        // int n = height.size();
        // int l = 0, r = n-1;
        // int leftMax = 0, rightMax = 0, ans = 0;

        // while(l <= r){
        //     if(height[l] <= height[r]){
        //         leftMax = max(leftMax, height[l]);
        //         ans += (leftMax - height[l]);
        //         l++;
        //     }
        //     else{
        //         rightMax = max(rightMax , height[r]);
        //         ans += (rightMax - height[r]);
        //         r--;
        //     }
        // }

        // return ans;

        // SUB OPTIMAL
        // prefixMax(stored in variable), suffixMax
        // TC = O(2N) SC = O(N)
        // int n = height.size();
        // int ans = 0;

        // vector<int> suffixMax(n, 0);
        // suffixMax[n-1] = height[n-1];
        // for(int i = n-2; i >= 0; i--) suffixMax[i] = max(suffixMax[i+1], height[i]);

        // int leftMax = height[0], rightMax;
        // for(int i = 0; i < n; i++){
        //     leftMax = max(leftMax, height[i]);
        //     rightMax = suffixMax[i];
            
        //     if(height[i] < leftMax && height[i] < rightMax)
        //         ans += (min(leftMax, rightMax) - height[i]);
        // }

        // return ans;

        // BRUTE FORCE
        // prefixMax, suffixMax
        // TC = O(3N) SC = O(2N)
        // int n = height.size();
        // int ans = 0;

        // vector<int> prefixMax(n, 0), suffixMax(n, 0);

        // prefixMax[0] = height[0];
        // suffixMax[n-1] = height[n-1];
        // for(int i = 1; i < n; i++) prefixMax[i] = max(prefixMax[i-1], height[i]);
        // for(int i = n-2; i >= 0; i--) suffixMax[i] = max(suffixMax[i+1], height[i]);

        // for(int i = 0; i < n; i++){
        //     int leftMax = prefixMax[i], rightMax = suffixMax[i];
        //     if(height[i] < leftMax && height[i] < rightMax){
        //         ans += (min(leftMax, rightMax) - height[i]);
        //     }
        // }

        // return ans;

        int n = height.size();
        int l = 0, r = n-1;
        int lmax = 0, rmax = 0, ans = 0;

        while(l <= r){
            if(height[l] <= height[r]){
                lmax = max(lmax, height[l]);
                ans += (lmax - height[l]);
                l++;
            }
            else{
                rmax = max(rmax, height[r]);
                ans += (rmax - height[r]);
                r--;
            }
        }

        return ans;
    }
};
