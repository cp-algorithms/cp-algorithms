#include <cassert>
#include <vector>
#include <set>
#include <functional>

using namespace std;

#include "centroid_decomposition.h"

void test_centroid_property()
{
    int n = 10;
    vector<vector<int>> adj_vec(n);

    adj_vec[0] = {1, 2, 3};
    adj_vec[1] = {0, 4, 5};
    adj_vec[2] = {0, 6};
    adj_vec[3] = {0, 7, 8};
    adj_vec[4] = {1};
    adj_vec[5] = {1, 9};
    adj_vec[6] = {2};
    adj_vec[7] = {3};
    adj_vec[8] = {3};
    adj_vec[9] = {5};

    for (int i = 0; i < n; i++)
    {
        adj[i].clear();
        for (int u : adj_vec[i])
        {
            adj[i].push_back(u);
        }
        removed[i] = false;
    }

    int tree_size = get_subtree_size(0);
    int centroid = get_centroid(0, tree_size);

    get_subtree_size(centroid);
    for (int u : adj[centroid])
    {
        if (removed[u])
            continue;
        assert(subtree_size[u] * 2 <= tree_size);
    }
}

void test_line_graph()
{
    int n = 7;
    for (int i = 0; i < n; i++)
    {
        adj[i].clear();
        removed[i] = false;
    }

    for (int i = 0; i < n - 1; i++)
    {
        adj[i].push_back(i + 1);
        adj[i + 1].push_back(i);
    }

    int tree_size = get_subtree_size(0);
    int centroid = get_centroid(0, tree_size);

    assert(centroid == 3);
}

void test_star_graph()
{
    int n = 8;
    for (int i = 0; i < n; i++)
    {
        adj[i].clear();
        removed[i] = false;
    }

    for (int i = 1; i < n; i++)
    {
        adj[0].push_back(i);
        adj[i].push_back(0);
    }

    int tree_size = get_subtree_size(0);
    int centroid = get_centroid(0, tree_size);

    assert(centroid == 0);
}

void test_complete_decomposition()
{
    int n = 6;
    for (int i = 0; i < n; i++)
    {
        adj[i].clear();
        removed[i] = false;
    }

    adj[0] = {1, 2};
    adj[1] = {0, 3, 4};
    adj[2] = {0, 5};
    adj[3] = {1};
    adj[4] = {1};
    adj[5] = {2};

    set<int> processed_centroids;

    function<void(int)> decompose_test = [&](int v)
    {
        int tree_size = get_subtree_size(v);
        int centroid = get_centroid(v, tree_size);

        processed_centroids.insert(centroid);
        removed[centroid] = true;

        for (int u : adj[centroid])
        {
            if (!removed[u])
            {
                decompose_test(u);
            }
        }
    };

    decompose_test(0);

    assert(processed_centroids.size() == n);
}

void test_path_counting()
{
    // Test the specific implementation: counting paths of length K
    // Create a simple tree: 0-1-2-3
    int n = 4;
    for (int i = 0; i < n; i++)
    {
        adj[i].clear();
        removed[i] = false;
    }

    // Line graph: 0-1-2-3
    for (int i = 0; i < n - 1; i++)
    {
        adj[i].push_back(i + 1);
        adj[i + 1].push_back(i);
    }

    K = 2;
    answer = 0;
    decompose(0);

    // Paths of length 2: (0,2) and (1,3)
    assert(answer == 2);

    for (int i = 0; i < n; i++)
    {
        removed[i] = false;
    }
    K = 1;
    answer = 0;
    decompose(0);

    // Paths of length 1: (0,1), (1,2), (2,3)
    assert(answer == 3);

    for (int i = 0; i < n; i++)
    {
        removed[i] = false;
    }
    K = 3;
    answer = 0;
    decompose(0);

    // Paths of length 3: (0,3)
    assert(answer == 1);
}

void test_star_path_counting()
{
    // Test path counting on a star graph
    // Tree: center 0 connected to 1, 2, 3, 4
    int n = 5;
    for (int i = 0; i < n; i++)
    {
        adj[i].clear();
        removed[i] = false;
    }

    for (int i = 1; i < n; i++)
    {
        adj[0].push_back(i);
        adj[i].push_back(0);
    }

    K = 1;
    answer = 0;
    decompose(0);

    // Paths of length 1: (0,1), (0,2), (0,3), (0,4)
    assert(answer == 4);

    for (int i = 0; i < n; i++)
    {
        removed[i] = false;
    }
    K = 2;
    answer = 0;
    decompose(0);

    // Paths of length 2: (1,2), (1,3), (1,4), (2,3), (2,4), (3,4) = 6 paths
    assert(answer == 6);
}

void test_single_vertex()
{
    int n = 1;
    adj[0].clear();
    removed[0] = false;

    int tree_size = get_subtree_size(0);
    int centroid = get_centroid(0, tree_size);

    assert(centroid == 0);
    assert(tree_size == 1);
}

void test_two_vertices()
{
    int n = 2;
    adj[0].clear();
    adj[1].clear();
    removed[0] = removed[1] = false;

    adj[0].push_back(1);
    adj[1].push_back(0);

    int tree_size = get_subtree_size(0);
    int centroid = get_centroid(0, tree_size);

    assert(centroid == 0 || centroid == 1);
}

int main()
{
    test_centroid_property();
    test_line_graph();
    test_star_graph();
    test_complete_decomposition();
    test_single_vertex();
    test_two_vertices();
    test_path_counting();
    test_star_path_counting();

    return 0;
}
